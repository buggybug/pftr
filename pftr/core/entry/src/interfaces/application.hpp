#ifndef APPLICATION_HPP__39898FB4_5FF4_40E0_A798_387043F19B00__INCLUDED_
#define APPLICATION_HPP__39898FB4_5FF4_40E0_A798_387043F19B00__INCLUDED_

#include <memory>
#include <pftr/pftr_def.hpp>

namespace pftr
{
    namespace core
    {
        namespace interfaces
        {
            class IApplication
            {
            public:
                virtual ~IApplication() noexcept = default;

                virtual Status run() = 0;
                virtual Status stop(Status exitStatus) = 0;
                virtual Status terminate(Status exitStatus) = 0;
            };
        }; // namespace interfaces
    }; // namespace core
}; // namespace pftr

#endif // APPLICATION_HPP__39898FB4_5FF4_40E0_A798_387043F19B00__INCLUDED_
