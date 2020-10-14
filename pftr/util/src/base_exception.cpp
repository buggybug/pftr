#include "pftr/util/base_exception.hpp"

namespace pftr
{
    namespace util
    {
        BaseException::~BaseException() noexcept
        {
        }


        Status BaseException::getStatus() const noexcept
        {
            return m_status;
        }


        std::string_view BaseException::getDescription() const noexcept
        {
            return std::string_view(m_description);
        }


        char const *BaseException::what() const noexcept
        {
            return m_description.c_str();
        }


        BaseException::BaseException(Status status, std::string const &description)
            : m_description(description),
              m_status(status)
        {
        }


        BaseException::BaseException(Status status, std::string &&description)
            : m_description(std::move(description)),
              m_status(status)
        {
        }


        BaseException::BaseException(Status status, char const *description)
            : m_description(nullptr != description ? description : getStatusDescription(status)),
              m_status(status)
        {
        }
    }; // namespace util
}; // namespace pftr
