#ifndef SOURCE_UTIL_ZIP_H_
#define SOURCE_UTIL_ZIP_H_

#include <minizip/zip.h>
#include <minizip/unzip.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>

#if __has_include(<filesystem>)
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif

namespace Util
{

    /**
     * @brief Create a zip file of a directory
     * 
     * @param dir Directory to zip.
     * @param fileName Destination file: if the file's directory doesn't exist nothing happens.
     *
     * @return true if the zip file has been created successfully
     * @return false if the zip file's folder doesn't exist (not file created)
     */
    inline bool ZipDir(const std::string& dir, const std::string& fileName)
    {

        const auto filePath = fs::path{fileName};

        const auto absFilePath = fs::absolute(filePath).parent_path();

        if(!fs::exists(absFilePath))
        {
            return false;
        }

        auto zf = zipOpen(fileName.data(), APPEND_STATUS_CREATE);

        for(const fs::path& path : fs::recursive_directory_iterator(dir))
        {
            if(fs::is_regular_file(path))
            {

                std::fstream file(path.c_str(), std::ios::binary | std::ios::in);

                // Check file validity
                if(!file.good())
                {
                    continue;
                }

                std::vector<char> buffer(fs::file_size(path));

                // Read file contents
                file.read(buffer.data(), buffer.size());

                // Get filename and directory structure
                const auto dirName = fs::path{dir}.filename();
                const auto dirIt = std::find_if(path.begin(), path.end(), [&](const auto& d) { return d.c_str() == dirName; });
                const auto zipFilePath = std::accumulate(std::next(dirIt), path.end(), fs::path{}, std::divides<fs::path>());

                // Zip file
                zip_fileinfo zfi{};
                if(Z_OK == zipOpenNewFileInZip(zf, zipFilePath.c_str(), &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION))
                {
                    zipWriteInFileInZip(zf, buffer.data(), buffer.size());
                    zipCloseFileInZip(zf);
                }
            }
        }

        zipClose(zf, NULL);
        return true;
    }

    /**
     * @brief Unzip a compressed directory into a given folder.
     * 
     * @param zipFile Zip file location
     * @param outputDir Output directory (where the file is extracted).
     * @param replace Whether to replace existing files or not.
     * @return true File unzipped successfully.
     * @return false Could not unzip file (invalid file, or the file doesn't exist).
     */
    inline bool UnzipDir(const std::string& zipFile, const std::string& outputDir, bool replace)
    {

        // Open the zip file
        unzFile zipfile = unzOpen(zipFile.data());
        if(zipfile == NULL)
        {
            return false;
        }

        // Get info about the zip file
        unz_global_info global_info;
        unzGetGlobalInfo(zipfile, &global_info);

        // Loop to extract all files
        for(size_t i = 0; i < global_info.number_entry; ++i)
        {
            // Get info about current file.
            unz_file_info file_info;
            std::string filename(256, '\0');
            unzGetCurrentFileInfo(zipfile, &file_info, (char*)filename.data(), filename.size(), NULL, 0, NULL, 0);

            // Update string's size to match its length
            filename = filename.data();

            //std::cout << "File name = " << filename << std::endl;
            //std::cout << "Size uncompressed = " << file_info.uncompressed_size << std::endl;

            // Create parent directories of the file
            fs::path filePath{filename};
            fs::create_directories(fs::path{outputDir} / filePath.parent_path());

            const auto outputPath = fs::path{outputDir} / fs::path{filename};

            try
            {
                const auto outFileExists = fs::exists(outputPath);
                if(outFileExists && !replace)
                {
                    // Go the the next entry listed in the zip file.
                    unzGoToNextFile(zipfile);
                    continue;
                }
            }
            catch(const fs::filesystem_error& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
            

            // Select file
            unzOpenCurrentFile(zipfile);

            // Create buffer to hold data
            std::vector<char> buffer(file_info.uncompressed_size);
            unzReadCurrentFile(zipfile, buffer.data(), buffer.size());

            // Write to file
            std::ofstream file(outputPath.string(), std::ios::out | std::ios::binary);
            file.write(buffer.data(), buffer.size());

            unzCloseCurrentFile(zipfile);

            // Go the the next entry listed in the zip file.
            unzGoToNextFile(zipfile);
        }

        unzClose(zipfile);

        return true;
    }


}

#endif
