#pragma once
#include <string>
#include <Windows.h>
#include <experimental/filesystem>

class Application {

	std::string applicationName;
	std::string applicationPath;

	// Used for process
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	void GetApplicationDir();
public:
	Application(std::string applicationName);
	~Application();
	void Launch(std::string commands = "");
	void Kill();
	
};