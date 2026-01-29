#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define FT_LIST_NUMBER_ONLY			0x80000000

typedef ULONG	FT_STATUS;

typedef FT_STATUS(__stdcall* _FT_ListDevices)(PVOID pArg1, PVOID pArg2, DWORD Flags);
typedef FT_STATUS(__stdcall* _FT_GetLibraryVersion)(LPDWORD lpdwDLLVersion);

int main()
{
    HINSTANCE hFTD = 0;
    ULONG numDevs = 0;
    FT_STATUS result = 0;
    DWORD lpdwDLLVersion = 0;

    _FT_ListDevices FT_ListDevices = NULL;
    _FT_GetLibraryVersion FT_GetLibraryVersion = NULL;

    printf("Attempting to load ftd2xx.dll\n");
    hFTD = LoadLibrary("ftd2xx.dll");
    if (hFTD == NULL) {
        printf("Failed to load ftd2xx.dll\n");
        return GetLastError();
    }

    printf("Loaded ftd2xx.dll\nObtaining function pointers..\n");

    if ((FT_ListDevices = (_FT_ListDevices)GetProcAddress(hFTD, "FT_ListDevices")) == NULL) {
        printf("Failed to get function FT_ListDevices\n");
        FreeLibrary(hFTD);
        return GetLastError();
    }

    if ((FT_GetLibraryVersion = (_FT_GetLibraryVersion)GetProcAddress(hFTD, "FT_GetLibraryVersion")) == NULL) {
        printf("Failed to get function FT_GetLibraryVersion\n");
        FreeLibrary(hFTD);
        return GetLastError();
    }

    printf("Got function pointers\n");

    result = FT_GetLibraryVersion(&lpdwDLLVersion);
    printf("FT_GetLibraryVersion result %lu\n", result);
    if(!result)
        printf("FTDI Version: %lu\n",lpdwDLLVersion);

    result = FT_ListDevices(&numDevs, NULL, FT_LIST_NUMBER_ONLY);
    printf("FT_ListDevices result %lu\n", result);
    if(!result)
        printf("Num FTDI Devices: %lu\n", numDevs);

    printf("Unloading ftd2xx.dll\n");

    FreeLibrary(hFTD);

    printf("Exiting..\n");

    return 0;
}
