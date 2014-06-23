#include <windows.h>
#include <process.h>
#include <cassert>
#include <cerrno>
#include <vector>
#include <string>
#include <fstream>

void launchProcess(std::vector<std::wstring> &arguments)
{
	std::vector<wchar_t const *> processArgs;

	for (std::vector<std::wstring>::const_iterator it = arguments.begin();
		 it != arguments.end();
		 ++it)
	{
		processArgs.push_back(it->c_str());
	}
	processArgs.push_back(NULL);

	intptr_t processHandle = _wspawnvp(_P_NOWAIT, processArgs[0], &processArgs[0]);
	if (processHandle == -1)
	{
		int lastErrno = errno;
		// Do something with the error.
		assert(0);
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	std::vector<std::wstring> stringArgs;
	INT numOriginalArgs = 0;
	LPWSTR *originalArgv = CommandLineToArgvW(GetCommandLineW(), &numOriginalArgs);

	
	stringArgs.push_back(L"emacsclientw.exe");
	stringArgs.push_back(L"--alternate-editor=runemacs.exe");
	stringArgs.push_back(L"--no-wait");
	if (numOriginalArgs > 1)
	{
		for (INT i = 1; i < numOriginalArgs; ++i)
		{
			// Add quotes around an argument containing a space
			std::wstring argument(originalArgv[i]);
			if (argument.find(L" ") != std::wstring::npos)
			{
				argument.insert(0, L"\"");
				argument.append(L"\"");
			}
			stringArgs.push_back(argument);
		}
	}
	else
	{
		// Adding an empty quotes string seems to do the right thing
		// when there are no arguments to this wrapper.
		stringArgs.push_back(L"\"\"");
	}

#ifdef _DEBUG
	std::wstring logFilename(originalArgv[0]);
	logFilename.append(L".log");
	std::wofstream logFile;

	logFile.open(logFilename.c_str());
	for (std::vector<std::wstring>::const_iterator it = stringArgs.begin();
		 it != stringArgs.end();
		 ++it)
	{
		logFile << *it << L"\n";
	}
	logFile.close();
#endif

	launchProcess(stringArgs);

	return 0;
}