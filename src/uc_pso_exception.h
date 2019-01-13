#pragma once

#include <exception>

#include "uc_error_messages.h"

namespace uc
{
    namespace pso
    {
        class exception : public std::exception
        {
            using base = std::exception;

            private:

            std::string describe(error_category e)
            {
                switch (e)
                {
                    case error_category::general:           return std::string("pso_exception_general");
                    case error_category::io:                return std::string("pso_exception_io");
                    case error_category::phase_1:           return std::string("pso_exception_phase_1");
                    case error_category::phase_2:           return std::string("pso_exception_phase_2");
                    case error_category::input_parameters:  return std::string("pso_exception_input_parameters");
                    default:                                return std::string("pso_exception");
                }
            }

            public:

            exception( error_category category ) : base("pso_exception")
            , m_category(category)
            {
                m_text = describe(category);
            }

            const char* what() const override
            {
                return m_text.c_str();
            }

            private:
            error_category m_category;
            std::string    m_text;
        };

        class file_not_found_exception : public exception
        {
            using base = exception;

        public:

            file_not_found_exception(const std::string& file_name) : base(error_category::io)
                , m_file_name(file_name)
            {
                m_file_name = std::string("Cannot find file ") + m_file_name;
            }

            const std::string& file_name() const
            {
                return m_file_name;
            }

            const char* what() const override
            {
                return m_text.c_str();
            }

        private:
            std::string m_file_name;
            std::string m_text;
        };

        class input_exception : public exception
        {
            using base = exception;

            public:

            input_exception( const std::string& o) : base(error_category::input_parameters)
            , m_option(o)
            {

            }

            const std::string& option() const
            {
                return m_option;
            }

            private:
            std::string m_option;
            std::string m_text;

        };

        class missing_input_exception : public exception
        {
            using base = exception;

        public:
            enum struct missing_part
            {
                pipeline_state_object,
                rasterizer_description,
                blend_description,
                depth_stencil_description
            };

            missing_input_exception( missing_part part ) : base(error_category::input_parameters)
            , m_part(part)
            {

            }

            missing_part part() const
            {
                return m_part;
            }

            private:
            missing_part    m_part;
            std::string     m_text;
        };

        class missing_variable_input_exception : public missing_input_exception
        {
            using base = missing_input_exception;

        public:

            missing_variable_input_exception( missing_input_exception::missing_part part, const std::string& variable ) : base( part)
            , m_variable(variable)
            {

            }

            const std::string& variable() const
            {
                return m_variable;
            }

        private:
            std::string m_variable;
            std::string m_text;
        };

        inline void raise_error(error_category category)
        {
            throw exception(category);
        }

        inline void raise_error()
        {
            throw exception(error_category::general);
        }

        template <typename e, typename ...args > void raise_error( args&&... a )
        {
            throw e(std::forward<args>(a)...);
        }
    }
}
