# ftd2xx-wine

This project builds FTD2XX drivers (32 and 64 bit) to be used under Wine (WoW64). It bridges Windows applications to Unix-native functionality using Wine's thunking mechanism.
The DLL is invoked by native Windows binaries, but the actual implementation resides in a Unix `.so` library.

---

## Project Overview

* Cross-platform thunking: `ftd2xx.dll` is compiled as a Wine DLL (32 & 64 bit), which internally invokes a Unix `.so` using Wine internals.
* Architecture support: Fully supports both `i386`, `x86_64`, and `aarch64` targets without the need for multilib on the host
* Box64 & Hangover support: For running `i386` and `x86_64` Windows applications needing FTD2XX on `aarch64`

# Requirements
 - Wine 9.0+ (Wow64)
 - Clang

## Build Instructions

To download the FTD2XX library and build everything (libraries + test apps):

```
make
```

You must install the built DLLs both into Wine's system folders and your current wineprefix.
This is handled by `make install` target.

```
make install WINEPREFIX=~/.wine
```

To uninstall the DLLs

```
make uninstall WINEPREFIX=~/.wine
```

To clean all generated files:

```
make clean
```

## File Structure and Purpose

| Path                             | Description                                                           |
| -------------------------------- | --------------------------------------------------------------------- |
| `unixlib.c`                      | Unix-side implementation (.so file).  Conventional name for Wine.     |
| `ftd2xx.spec`                    | Wine `.spec` file defining exported functions and calling convention. |
| `ftd2xx.c`                       | DLL entry point and thunk setup, acting as Windows stub.              |
| `testapp.c`                      | Native Windows test application.                                      |
| `Makefile`                       | Handles all builds: `.so`, `.dll`, `.a`, `.exe`, install.             |
| `i386-windows/`                  | Output directory for 32-bit Windows build artifacts.                  |
| `[x86_64 or aarch64]-windows/ `  | Output directory for 64-bit WIndows build artifacts.                  |
| `[x86_64 or aarch64]-unix/ `     | Output directory for Unix-side shared object.                         |
| `gen.py`                         | Script used to help automate the creation of source code. Not used    |

## Test Output

To run the 64 and 32 bit test applications

```
make run_testapps
```

After running the test applications, you should see:

```
wine i386-windows/testapp.exe
Attempting to load ftd2xx.dll
Loaded ftd2xx.dll
Obtaining function pointers..
Got function pointers
FT_GetLibraryVersion result 0
FTDI Version: 66612
FT_ListDevices result 0
Num FTDI Devices: 0
Unloading ftd2xx.dll
Exiting..
wine x86_64-windows/testapp.exe
Attempting to load ftd2xx.dll
Loaded ftd2xx.dll
Obtaining function pointers..
Got function pointers
FT_GetLibraryVersion result 0
FTDI Version: 66612
FT_ListDevices result 0
Num FTDI Devices: 0
Unloading ftd2xx.dll
Exiting..
```

If you have an FTDI device plugged in then you will see 

```
Num FTDI Devices: X
```

where X is the number of devices plugged in

If you get errors that ftd2xx.dll cannot be found, please ensure you run `make install` before trying `make run_testapps`

## Debug & Trace

Trace information is available under the channel ftd2xx

```
WINEDEBUG=+ftd2xx wine testapp.exe
```

## Wine Thunk Communication

The core of this project relies on Wine’s Unix call thunking mechanism to bridge Windows and Unix spaces.

Functions used:

* `__wine_init_unix_call()`
  Initializes thunk dispatch and must be called early (typically from `DllMain`).

* `__wine_unix_call_funcs`, `__wine_unix_call_wow64_funcs`
  Internal tables storing pointers to thunkable Unix functions for x86_64 (64 bit) and WoW64 (32 bit) respectively.

* `WINE_UNIX_CALL(func)`
  Macro that wraps thunked calls from Windows to Unix implementation.

* Native FTD2XX library is built 64 bit.
* 32 bit functions (`__wine_unix_call_wow64_funcs`) uses different structure because of pointer size (32 vs 64 bit)
* When 32 bit thunk DLL calls it's functions, the pointer size must be converted, then the value accessed as usual.

Communication Flow:

1. Native Windows app calls a function like `FT_ListDevices()` from the DLL.
2. The DLL uses `WINE_UNIX_CALL()` to forward the call.
3. Wine transparently dispatches it into the Unix `.so` (`unixlib.c`).
4. The result is passed back to the Windows app.

## License

This project is licensed under the GNU General Public License v2 (GPLv2).
