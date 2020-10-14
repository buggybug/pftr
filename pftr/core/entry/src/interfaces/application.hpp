#ifndef APPLICATION_HPP__39898FB4_5FF4_40E0_A798_387043F19B00__INCLUDED_
#define APPLICATION_HPP__39898FB4_5FF4_40E0_A798_387043F19B00__INCLUDED_

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
                static IApplication &createInstance();
                static IApplication &getInstance();

                virtual Status run() = 0;
                virtual Status stop(Status exitStatus) = 0;
                virtual Status terminate(Status exitStatus) = 0;

                IApplication(IApplication const &) = delete;
                IApplication(IApplication &&) = delete;
                IApplication &operator=(IApplication const &) = delete;
                IApplication &operator=(IApplication &&) = delete;

            protected:
                IApplication() noexcept = default;
                virtual ~IApplication() noexcept = default;
            };
        }; // namespace interfaces
    }; // namespace core
}; // namespace pftr

#endif // APPLICATION_HPP__39898FB4_5FF4_40E0_A798_387043F19B00__INCLUDED_
