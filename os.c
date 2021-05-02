/* Tests for SHLWAPI IsOS functions */

#include <stdio.h>
#include <stdarg.h>
#include <processthreadsapi.h>

#define COBJMACROS
#define CONST_VTABLE

#include "windef.h"
#include "winbase.h"
#include "winerror.h"
#include "ole2.h"
#include "shlwapi.h"

#include "wine/test.h"

static WINBOOL(WINAPI *pIsOS)(DWORD);

static void test_IsOS(void)
{
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
}

START_TEST(thread)
{
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
