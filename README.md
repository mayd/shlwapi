# shlwapi.h 

This repository contains my version of the C include file `shlwapi.h` for use with MSYS2/MinGW and some unit test code.

The definitive documentation for the SHLWAPI library is [shlwapi.h header](https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/).

My version of `shlwapi.h` is based on the MSYS2 version with additions from the Wine Project version and the official 
Microsoft documentation and the implementation provided in Microsoft SDK version 10.0.16299.0.

The unit tests here were adapted from the unit tests for [The Wine Project](https://www.winehq.org/) implementation of SHLWAPI:

  * [assoc.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/assoc.c)
  * [clist.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/clist.c)
  * [clsid.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/clsid.c)
  * [generated.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/generated.c)
  * [istream.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/istream.c)
  * [ordinal.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/ordinal.c)
  * [path.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/path.c)
  * [shreg.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/shreg.c)
  * [string.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/string.c)
  * [thread.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/thread.c)
  * [url.c](https://github.com/wine-mirror/wine/blob/master/dlls/shlwapi/tests/url.c)

The Wine Project unit tests were modified to link functions from shlwapi.dll at compile time rather than dynamic loading at run time.

To run the SHLWAPI unit tests run the following commands:

  1. `make`
  2. `make test`

This version of `shlwapi.h` was also used to build the `MovieShow` sample app from the [Win32++ Project](http://win32-framework.sourceforge.net/).
