#include <windows.h>
#include <cassert>
#include <vector>
#include <string>

int WINAPI wWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PWSTR pCmdLine, int nCmdShow)
{
	std::wstring newCommandLine{L"emacsclientw.exe --alternate-editor=runemacs.exe --no-wait "};
	newCommandLine.append(pCmdLine);

	// In the case of no arguments to this program, we pass a blank argument to emacsclient.
	// This will start an empty emacs instance instead of showing an error message.
	if (wcslen(pCmdLine) == 0) {
		newCommandLine.append(LR"("")");
	}

	// CreateProcessW modifies the command line argument, so we need a writable buffer
	std::vector<wchar_t> commandLineBuffer;
	commandLineBuffer.resize(newCommandLine.length() + 1);
	wcsncpy(commandLineBuffer.data(), newCommandLine.data(), commandLineBuffer.size());

	STARTUPINFOW si{};
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi{};

	BOOL retval = CreateProcessW(
		NULL,
		commandLineBuffer.data(),
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_PROCESS_GROUP,
		NULL,
		NULL,
		&si,
		&pi);
	assert(retval);

	return 0;
}