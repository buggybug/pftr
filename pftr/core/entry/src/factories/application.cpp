#ifdef WIN32
#include "windows/windows_application.hpp"
#else // ! WIN32
#include "linux/linux_application.hpp"
#endif // WIN32

namespace pftr
{
    namespace core
    {
        namespace interfaces
        {
#ifdef WIN32
            using ApplicationFactory = WindowsApplication;
#else // ! WIN32
            using ApplicationFactory = LinuxApplication;
#endif // WIN32
            IApplication &IApplication::createInstance()
            {
                static ApplicationFactory application;
                return application;
            }


            IApplication &IApplication::getInstance()
            {
                return createInstance();
            }
        }; // namespace interfaces
    }; // namespace core
}; // namespace pftr
