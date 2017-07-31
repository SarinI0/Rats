#include "stdafx.h"
#include <atlstr.h>

#pragma comment(lib, "wtsapi32")
#pragma comment(linker,"/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

BOOL IsSystemSid(PSID sid) {
	return ::IsWellKnownSid(sid, WinLocalSystemSid);
}

HANDLE OpenSystemProcessToken() {
	PWTS_PROCESS_INFO pInfo;
	DWORD count;
	if (!::WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pInfo, &count)) {
		return nullptr;
	}

	HANDLE hToken{};
	for (DWORD i = 0; i < count && !hToken; i++) {
		if (pInfo[i].SessionId == 0 && IsSystemSid(pInfo[i].pUserSid)) {
			auto hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pInfo[i].ProcessId);
			if (hProcess) {
				::OpenProcessToken(hProcess, TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_QUERY | TOKEN_IMPERSONATE, &hToken);
				::CloseHandle(hProcess);
			}
		}
	}

	::WTSFreeMemory(pInfo);
	return hToken;
}

BOOL SetPrivilege(HANDLE hToken, PCTSTR lpszPrivilege, bool bEnablePrivilege) {
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!::LookupPrivilegeValue(nullptr, lpszPrivilege, &luid))
		return FALSE;

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if (!::AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr)) {
		return FALSE;
	}

	if (::GetLastError() == ERROR_NOT_ALL_ASSIGNED)
		return FALSE;

	return TRUE;
}

LPWSTR ConvertToLPWSTR(const std::string& s)
{
	LPWSTR ws = new wchar_t[s.size() + 1];
	copy(s.begin(), s.end(), ws);
	ws[s.size()] = 0;
	return ws;
}

BOOL EnableDebugPrivilege(void) {
	HANDLE hToken;
	BOOL result;
	if (!::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return FALSE;
	}
	result = SetPrivilege(hToken, SE_DEBUG_NAME, TRUE);
	::CloseHandle(hToken);
	return result;
}

int InQuota(LPWSTR Su, LPCTSTR P) {

	if (FALSE == EnableDebugPrivilege()) {
		return 1;
	}

	auto hToken = OpenSystemProcessToken();
	if (!hToken) {
		return 1;
	}

	HANDLE hDupToken, hPrimary;
	::DuplicateTokenEx(hToken, TOKEN_DUPLICATE | TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_PRIVILEGES,
		nullptr, SecurityImpersonation, TokenImpersonation, &hDupToken);
	::DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, nullptr, SecurityImpersonation, TokenPrimary, &hPrimary);
	::CloseHandle(hToken);

	if (hDupToken == nullptr) {
		return 1;
	}

	STARTUPINFO si = { sizeof(si) };
	si.lpDesktop = L"Winsta0\\default";

	PROCESS_INFORMATION pi;

	BOOL impersonated = ::SetThreadToken(nullptr, hDupToken);
	assert(impersonated);
	if (!impersonated) {
		return 1;
	}

	HANDLE hCurrentToken;
	DWORD session = 0, len = sizeof(session);
	::OpenProcessToken(::GetCurrentProcess(), TOKEN_ALL_ACCESS, &hCurrentToken);
	::GetTokenInformation(hCurrentToken, TokenSessionId, &session, len, &len);
	::CloseHandle(hCurrentToken);

	if (!SetPrivilege(hDupToken, SE_ASSIGNPRIMARYTOKEN_NAME, TRUE) ||
		!SetPrivilege(hDupToken, SE_INCREASE_QUOTA_NAME, TRUE)) {
		return 1;
	}

	BOOL ok = ::SetTokenInformation(hPrimary, TokenSessionId, &session, sizeof(session));

	::CreateProcessAsUser(hPrimary, nullptr, Su, nullptr, nullptr, FALSE, 0, nullptr, P, &si, &pi);

	return 0;
}

VOID main(int argc, char* argv[]) {
	using namespace std;
	string MemExe = (string)argv[0];
	string Ptr = "";
	string pa = "";
	string Wp = "";
	auto Wpr = nullptr;
	for (int j = 0; j < MemExe.length() - 12; j++) {
		if (MemExe[j] == *"\\") {
			Ptr += "\\";
			pa += "\\";
			Wp += "\\";
		}
		Wp += MemExe[j];
		Ptr += MemExe[j];
		pa += MemExe[j];
	}
	Ptr += "\\"; pa += "\\";
	Ptr += "\\"; pa += "\\";
	Ptr += "CMake.exe"; pa += "installer.exe";
	LPWSTR Cl0 = ConvertToLPWSTR(Ptr);
	LPWSTR Cl1 = ConvertToLPWSTR(pa);
	auto h = InQuota(Cl0, nullptr);
	auto i = InQuota(Cl1, ConvertToLPWSTR(Wp));

}
