#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif // WIN32

#ifdef WIN32
_Use_decl_annotations_ int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
#else // ! WIN32
int main(int argc, char *argv[], char *envp[])
#endif // WIN32
{
    return 0;
}
