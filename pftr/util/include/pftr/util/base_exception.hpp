#ifndef BASE_EXCEPTION_HPP__308835CE_8AC1_4C9E_BCC7_B7E7F4532BA8__INCLUDED_
#define BASE_EXCEPTION_HPP__308835CE_8AC1_4C9E_BCC7_B7E7F4532BA8__INCLUDED_

#include <exception>
#include <string>
#include "interfaces/exception.hpp"

namespace pftr
{
    namespace util
    {
        class BaseException
            : public interfaces::IException,
              public std::exception
        {
        public:
            virtual ~BaseException() noexcept;

            Status getStatus() const noexcept override;
            std::string_view getDescription() const noexcept override;

            char const *what() const noexcept override;

            BaseException() = delete;

        protected:
            BaseException(Status status, std::string const &description);
            BaseException(Status status, std::string &&description);
            BaseException(Status status, char const *description = nullptr);

        private:
            std::string const m_description;
            Status const m_status;
        };
    }; // namespace util
}; // namespace pftr

#endif // BASE_EXCEPTION_HPP__308835CE_8AC1_4C9E_BCC7_B7E7F4532BA8__INCLUDED_
