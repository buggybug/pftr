/// \file application_statics.cpp
/// \brief This module defines the application singleton class that simply stores the
///        corresponding IApplication interface implementation. It also implements the
///        API that wraps singleton functions and provides an access to the underlying
///        pointer to the application object.

#include "application_statics.hpp"
#include <pftr/util/singleton.hpp>
#ifdef WIN32
#include "windows/windows_application.hpp"
#else // ! WIN32
#include "linux/linux_application.hpp"
#endif // WIN32

namespace
{
    // The IApplication interface configuration specific implementation type.
#ifdef WIN32
    using ApplicationImpl = pftr::core::WindowsApplication;
#else // ! WIN32
    using ApplicationImpl = pftr::core::LinuxApplication;
#endif // WIN32

    /// \brief Defines the application storage as a singleton. See \ref IApplication
    ///        interface for the public API reference and \ref ApplicationImpl for the
    ///        configuration specific implementation.
    class ApplicationSingleton : public pftr::util::Singleton<pftr::core::interfaces::IApplication> {};
}; // anonymous namespace


namespace pftr
{
    namespace core
    {
        interfaces::IApplication *createApplication()
        {
            if (!ApplicationSingleton::isValid()) [[likely]]
            {
                return ApplicationSingleton::createInstance<ApplicationImpl>();
            }
            else [[unlikely]]
            {
                return ApplicationSingleton::getInstance();
            }
        }


        interfaces::IApplication *getApplication() noexcept
        {
            return ApplicationSingleton::getInstance();
        }
    }; // namespace core
}; // namespace pftr
