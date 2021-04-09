//void startup(LPCSTR lpApplicationName)
//{
//    // additional information
//    STARTUPINFOA si;
//    PROCESS_INFORMATION pi;
//
//    // set the size of the structures
//    ZeroMemory(&si, sizeof(si));
//    si.cb = sizeof(si);
//    ZeroMemory(&pi, sizeof(pi));
//
//    // start the program up
//    CreateProcessA
//    (
//        lpApplicationName,   // the path
//        argv[1],                // Command line
//        NULL,                   // Process handle not inheritable
//        NULL,                   // Thread handle not inheritable
//        FALSE,                  // Set handle inheritance to FALSE
//        CREATE_NEW_CONSOLE,     // Opens file in a separate console
//        NULL,           // Use parent's environment block
//        NULL,           // Use parent's starting directory 
//        &si,            // Pointer to STARTUPINFO structure
//        &pi           // Pointer to PROCESS_INFORMATION structure
//    );
//    // Close process and thread handles. 
//    CloseHandle(pi.hProcess);
//    CloseHandle(pi.hThread);
//}

#include "applicationmanip.h"



Application::Application(std::string applicationName)
{
	this->applicationName = applicationName;
}

Application::~Application()
{

}

void Application::Launch(std::string commands)
{

    GetApplicationDir();

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    LPSTR str = const_cast<char*>(commands.c_str());

    // start the program up
    CreateProcessA
    (
        applicationPath.c_str(),    // the path
        str,                        // Command line
        NULL,                       // Process handle not inheritable
        NULL,                       // Thread handle not inheritable
        FALSE,                      // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,         // Opens file in a separate console
        NULL,                       // Use parent's environment block
        NULL,                       // Use parent's starting directory 
        &si,                        // Pointer to STARTUPINFO structure
        &pi                         // Pointer to PROCESS_INFORMATION structure
    );

}

void Application::Kill()
{
    
   TerminateProcess(pi.hProcess, 1);

   // Close process and thread handles. 
   CloseHandle(pi.hProcess);
   CloseHandle(pi.hThread);

}

void Application::GetApplicationDir() {
    
    auto path = std::experimental::filesystem::current_path();
    applicationPath = path.generic_string() + "//Client//" + applicationName;
}