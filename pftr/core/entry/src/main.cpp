#include <exception>
#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif // WIN32
#include "interfaces/application.hpp"

#ifdef WIN32
_Use_decl_annotations_ int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
#else // ! WIN32
int main(int argc, char *argv[], char *envp[])
#endif // WIN32
{
    try
    {
        auto &application = pftr::core::interfaces::IApplication::createInstance();
        return static_cast<int>(application.run());
    }
    catch ([[maybe_unused]] std::exception const &e)
    {
        return -1;
    }
}
