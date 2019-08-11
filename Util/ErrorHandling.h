#ifndef LIBEXADRUMS_SOURCE_UTIL_ERROR_HANDLING_H_
#define LIBEXADRUMS_SOURCE_UTIL_ERROR_HANDLING_H_

#include <stdexcept>
#include <cstdio>

namespace Util
{

    #if __cplusplus__
    extern "C"
    {
    #endif 

        enum errorType : int32_t
        {  
            error_type_success = 0,
            error_type_warning = 1, 
            error_type_question = 2, 
            error_type_error = 3,
            error_type_other = 4
        };

        typedef struct _error
        {
            char message[255];
            int32_t type;
        } error;

        inline error make_error(const char* message, errorType error_type)
        {
            error e{"", error_type};
            std::snprintf(e.message, sizeof e.message, "%s", message); // prevents overflow
            return e;
        }

        /**
         * @brief Merge two errors together
         * 
         * @param e1 first erorr
         * @param e2 second error
         * @return error merged error
         */
        inline error merge_errors(const error& e1, const error& e2)
        {
            error merged_error;

            if(e1.type >= e2.type)
            {
                std::snprintf(merged_error.message, sizeof merged_error.message, "%s", e1.message);
                merged_error.type = e1.type;
            }
            else
            {
                std::snprintf(merged_error.message, sizeof merged_error.message, "%s", e2.message);
                merged_error.type = e2.type;
            }


            return merged_error;
        }

        /**
         * @brief Update an error using another, newer, error.
         * 
         * @param e error to be updated
         * @param new_error another error that alters the state of e
         * @return errorType error type
         */
        inline errorType update_error(error& e, const error& new_error)
        {
            e = merge_errors(e, new_error);
            return errorType{static_cast<errorType>(e.type)};
        }

    #if __cplusplus__
    }
    #endif 

    class Exception : public std::exception
    {

    public: 
        
        /**
         * @brief Construct a new Exception object from an error type.
         * 
         * @param err 
         */
        explicit Exception(const error& err) noexcept 
        : message{err.message}, error_type{static_cast<errorType>(err.type)} {}

        Exception(const char* what_arg, errorType err_type) noexcept
        : message{what_arg}, error_type{err_type} {}

        Exception(std::string&& what_arg, errorType err_type) noexcept
        : message{std::move(what_arg)}, error_type{err_type} {}

        virtual const char* what() const noexcept final { return message.data(); }
        errorType type() const noexcept { return error_type; }

    private: 

        std::string message;
        errorType error_type;
        
    };

    /**
     * @brief Convert an error to an Exception. Throws if the error type is not error_type_success.
     * 
     * @tparam F A callable type.
     * @param f A callable that returns an error.
     */
    template <typename F>
    void ErrorToException(F&& f)
    {
        error err = f();

        if(err.type != error_type_success)
        {
            throw Exception(err);
        }	
    }

    /**
     * @brief Convert an Exception to an error.
     * 
     * @tparam F A callable type.
     * @param f A callable that throws the Exception that is to be converted.
     * @return error The error that corresponds to the Exception that has been thrown from the callable, or success if no exception was thrown.
     */
    template <typename F>
    error ExceptionToError(F&& f) noexcept
    {
        try
        {
            f();
        }
        catch(const Exception& except)
        {
            return make_error(except.what(), except.type());
        }
        catch(...)
        {
            return make_error("Unknown error.", error_type_error);
        }
        
        return error{"", error_type_success};
    }

}

#endif