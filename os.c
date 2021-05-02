/* Tests for SHLWAPI IsOS functions */

#include <stdio.h>
#include <stdarg.h>
#include <processthreadsapi.h>
//#include <lsalookup.h>
#include <ntsecapi.h>

#define COBJMACROS
#define CONST_VTABLE

#include "windef.h"
#include "winbase.h"
#include "winerror.h"
#include "ole2.h"
#include "shlwapi.h"

#include "wine/test.h"

static WINBOOL(WINAPI *pIsOS)(DWORD);

WINBOOL Is_WinVer_or_Later (DWORD dwOSMajor, DWORD dwOSMinor, DWORD wSPMajor, DWORD wSPMinor, BYTE bProdType) {
  // Based on code from <https://docs.microsoft.com/en-us/windows/win32/sysinfo/verifying-the-system-version>

  OSVERSIONINFOEX osvi;
  DWORDLONG dwlConditionMask = 0;
  int op=VER_GREATER_EQUAL;

  // Initialize the OSVERSIONINFOEX structure.

  ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
  osvi.dwMajorVersion = dwOSMajor;
  osvi.dwMinorVersion = dwOSMinor;
  osvi.wServicePackMajor = wSPMajor;
  osvi.wServicePackMinor = wSPMinor;
  osvi.wProductType = bProdType;

  // Initialize the condition mask.

  VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, op );
  VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
  VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
  VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );

  // Perform the test.

  return VerifyVersionInfo(
    &osvi, 
    VER_MAJORVERSION | VER_MINORVERSION | 
    VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
    dwlConditionMask);
}

WINBOOL ComputerBelongsToDomain() {
  // Code copied from <https://stackoverflow.com/questions/206172/how-do-you-programmatically-determine-whether-a-windows-computer-is-a-member-of>
  WINBOOL ret = FALSE;

  LSA_OBJECT_ATTRIBUTES objectAttributes;
  LSA_HANDLE policyHandle;
  NTSTATUS status;
  PPOLICY_PRIMARY_DOMAIN_INFO info;

  // Object attributes are reserved, so initialize to zeros.
  ZeroMemory(&objectAttributes, sizeof(objectAttributes));
  status = LsaOpenPolicy(NULL, &objectAttributes, GENERIC_READ | POLICY_VIEW_LOCAL_INFORMATION, &policyHandle);
  if (!status) {
    status = LsaQueryInformationPolicy(policyHandle, PolicyPrimaryDomainInformation, (LPVOID*)&info);
    if (!status) {
      if (info->Sid)
          ret = TRUE;
      LsaFreeMemory(info);
    }
    LsaClose(policyHandle);
  }

  return ret;
}

static void test_IsOS(void) {
  HANDLE hProcess;
  BOOL bWow64Process;

  ok (IsOS(OS_WINDOWS) == FALSE, "IsOS: OS_WINDOWS failed\n");
  ok (IsOS(OS_NT) == TRUE, "IsOS: OS_NT failed\n");
  ok (IsOS(OS_WIN95ORGREATER) == FALSE, "IsOS: OS_WIN95ORGREATER failed\n");
  ok (IsOS(OS_NT4ORGREATER) == FALSE, "IsOS: OS_NT4ORGREATER failed\n");
  ok (IsOS(OS_WIN98ORGREATER) == FALSE, "IsOS: OS_WIN98ORGREATER failed\n");
  ok (IsOS(OS_WIN98_GOLD) == FALSE, "IsOS: OS_WIN98_GOLD failed\n");
  ok (IsOS(OS_WIN95_GOLD) == FALSE, "IsOS: OS_WIN95_GOLD failed\n");
  ok (IsOS(OS_MEORGREATER) == FALSE, "IsOS: OS_MEORGREATER failed\n");
  ok (IsOS(OS_XPORGREATER) == FALSE, "IsOS: OS_XPORGREATER failed\n");
  ok (IsOS(OS_HOME) == FALSE, "IsOS: OS_HOME failed\n");
  ok (IsOS(OS_WELCOMELOGONUI) == FALSE, "IsOS: OS_WELCOMELOGONUI failed\n");
  ok (IsOS(OS_WEBSERVER) == FALSE, "IsOS: OS_WEBSERVER failed\n");
  hProcess = GetCurrentProcess();
  if (!IsWow64Process(hProcess, &bWow64Process)) {
    win_skip("IsWow64Process() failed.");
  } else {
    ok (IsOS(OS_WOW6432) == bWow64Process, "IsOS: OS_WOW6432 failed\n");
  }
  ok (IsOS(OS_WIN2000ORGREATER) == Is_WinVer_or_Later(5, 0, 0, 0, VER_NT_SERVER), "IsOS: OS_WIN2000ORGREATER failed\n");
  ok (IsOS(OS_DOMAINMEMBER) == ComputerBelongsToDomain(), "IsOS: OS_DOMAINMEMBER failed\n");
}

START_TEST(thread) {
    HMODULE hshlwapi = GetModuleHandleA("shlwapi.dll");
    if (!hshlwapi)
      hshlwapi = LoadLibrary(TEXT("shlwapi.dll"));
    if (!hshlwapi) {
      win_skip("Failed to load library 'shlwapi.dll'.");
    return;
    }

#ifdef TEST_SHLWAPI_H
    pIsOS = IsOS;
#else
    pIsOS = (void *)GetProcAddress(hshlwapi, "IsOS");
#endif

    test_IsOS();
}
