#ifndef SOURCE_UTIL_ZIP_H_
#define SOURCE_UTIL_ZIP_H_

#include <minizip/zip.h>
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

        auto filePath = fs::path{fileName};

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


}

#endif