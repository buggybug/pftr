#include <exception>
#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif // WIN32
#include <pftr/util/interfaces/exception.hpp>
#include "application_statics.hpp"

namespace
{
    /// \brief Allocates and initializes all primary global objects and variables.
    ///        This kind of objects can be safely accessed once the function returns.
    void createGlobalObjects()
    {
        pftr::core::createApplication();
    }
}; // anonymous namespace

#ifdef WIN32
_Use_decl_annotations_ int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
#else // ! WIN32
int main(int argc, char *argv[], char *envp[])
#endif // WIN32
{
    pftr::Status status;
    try
    {
        createGlobalObjects();

        status = pftr::core::getApplication()->run();
    }
    // Catch only expected exceptions that the PFTR API is supposed to throw.
    catch (pftr::util::interfaces::IException const &e)
    {
        status = e.getStatus();
    }
    catch (std::bad_alloc const &)
    {
        status = pftr::Status::eOutOfMemory;
    }
    return static_cast<int>(status);
}
