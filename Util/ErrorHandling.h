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

        static error make_error(const char* message, errorType error_type)
        {
            error e{"", error_type};
            std::snprintf(e.message, sizeof e.message, "%s", message); // prevents overflow
            return e;
        }

    #if __cplusplus__
    }
    #endif 

    class Exception : public std::exception
    {

    public: 
        
        explicit Exception(const error& err) noexcept 
        : message{err.message}, error_type{err.type} {}

        Exception(const char* what_arg, errorType err_type) noexcept
        : message{what_arg}, error_type{err_type} {}

        virtual const char* what() const noexcept final { return message.data(); }
        errorType type() const noexcept { return error_type; }

    private: 

        std::string message;
        errorType error_type;
        
    };

    template <typename F>
    void ErrorToException(F&& f)
    {
        error err = f();

        if(err.type != error_type_success)
        {
            throw Exception(err);
        }	
    }

    template <typename F>
    error ExceptionToError(F&& f)
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