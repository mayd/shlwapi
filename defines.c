#include <stdio.h>

#include "./shlwapi.h"

int main(int argc, char *argv[]) {

#ifdef _INC_SHLWAPI
  printf("_INC_SHLWAPI is defined\n");
#else
  printf("_INC_SHLWAPI is not defined\n");
#endif

#ifdef NO_SHLWAPI
  printf("NO_SHLWAPI is defined\n");
#else
  printf("NO_SHLWAPI is not defined\n");
#endif

#ifdef UNICODE
  printf("UNICODE is defined\n");
#else
  printf("UNICODE is not defined\n");
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
  printf("WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) is TRUE\n");
#else
  printf("WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) is FALSE\n");
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_SYSTEM)
  printf("WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_SYSTEM) is TRUE\n");
#else
  printf("WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_SYSTEM) is FALSE\n");
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
  printf("WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) is TRUE\n");
#else
  printf("WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) is FALSE\n");
#endif

#ifdef WINSHLWAPI
  printf("WINSHLWAPI is defined\n");
#else
  printf("WINSHLWAPI is not defined\n");
#endif

#ifdef _SHLWAPI_
  printf("_SHLWAPI_ is defined\n");
#else
  printf("_SHLWAPI_ is not defined\n");
#endif

#ifdef _WINRESRC_
  printf("_WINRESRC_ is defined\n");
#else
  printf("_WINRESRC_ is not defined\n");
#endif

#ifdef _WIN32_WINNT
  printf("_WIN32_WINNT=0x0%x\n", _WIN32_WINNT);
#else
  printf("_WIN32_WINNT is not defined\n");
#endif

#ifdef NTDDI_VERSION
  printf("NTDDI_VERSION=0x0%x\n", _WIN32_WINNT);
#else
  printf("NTDDI_VERSION is not defined\n");
#endif

#ifdef _WIN32_IE
  printf("_WIN32_IE=0x0%x\n", _WIN32_IE);
#else
  printf("_WIN32_IE is not defined\n");
#endif

#ifdef NO_SHLWAPI_STRFCNS
  printf("NO_SHLWAPI_STRFCNS is defined\n");
#else
  printf("NO_SHLWAPI_STRFCNS is not defined\n");
#endif

#ifdef NO_SHLWAPI_PATH
   printf("NO_SHLWAPI_PATH is defined\n");
#else
  printf("NO_SHLWAPI_PATH is not defined\n");
#endif
  
#ifdef NO_SHLWAPI_REG
   printf("NO_SHLWAPI_REG is defined\n");
#else
  printf("NO_SHLWAPI_REG is not defined\n");
#endif
  
#ifdef NO_SHLWAPI_STREAM
   printf("NO_SHLWAPI_STREAM is defined\n");
#else
  printf("NO_SHLWAPI_STREAM is not defined\n");
#endif
  
#ifdef NO_SHLWAPI_GDI
   printf("NO_SHLWAPI_GDI is defined\n");
#else
  printf("NO_SHLWAPI_GDI is not defined\n");
#endif
  
#ifdef NO_SHLWAPI_HTTP
   printf("NO_SHLWAPI_HTTP is defined\n");
#else
  printf("NO_SHLWAPI_HTTP is not defined\n");
#endif

#ifdef NO_SHLWAPI_STOPWATCH
  printf("NO_SHLWAPI_STOPWATCH is defined\n");
#else
  printf("NO_SHLWAPI_STOPWATCH is not defined\n");
#endif

#ifdef NO_SHLWAPI_ISOS
  printf("NO_SHLWAPI_ISOS is defined\n");
#else
  printf("NO_SHLWAPI_ISOS is not defined\n");
#endif

  return 0;
}
