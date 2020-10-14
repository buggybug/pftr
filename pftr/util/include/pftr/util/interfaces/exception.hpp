#ifndef EXCEPTION_HPP__19C8A82D_2EFA_4E70_BC64_F0EA4D4DBA5F__INCLUDED_
#define EXCEPTION_HPP__19C8A82D_2EFA_4E70_BC64_F0EA4D4DBA5F__INCLUDED_

#include <string_view>
#include <pftr/pftr_def.hpp>

namespace pftr
{
    namespace util
    {
        namespace interfaces
        {
            class IException
            {
            public:
                virtual ~IException() noexcept = default;

                virtual Status getStatus() const = 0;
                virtual std::string_view getDescription() const = 0;

            protected:
                IException() = default;
                IException(IException const &) = default;
                IException &operator=(IException const &) = default;
            };
        }; // namespace interfaces
    }; // namespace util
}; // namespace pftr

#endif // EXCEPTION_HPP__19C8A82D_2EFA_4E70_BC64_F0EA4D4DBA5F__INCLUDED_
