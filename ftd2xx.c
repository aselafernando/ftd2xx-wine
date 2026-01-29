#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <windef.h>

#ifdef __WINESRC__
#include "unixlib.h"

#include "xftd2xx.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(ftd2xx);
//#define Trace(...) //TRACE(__VA_ARGS__)
#define Trace(...) WINE_TRACE(__VA_ARGS__)

//a list of FTD product ids to access (in hexidecimal)
#define FTDprodVar "FTDID"

FT_STATUS FT_SetVIDPID(DWORD dwVID, DWORD dwPID);

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    char *end = NULL;
    char *cursor = NULL;
    unsigned int vendor = 0;
    unsigned int product = 0;
    unsigned int prod2 = 0;

    Trace("reason=%lu\n", fdwReason);
    switch(fdwReason) {
        case DLL_PROCESS_ATTACH: {
            if( __wine_init_unix_call() )
                return FALSE;
            cursor = getenv(FTDprodVar);
            if (cursor) {
                vendor = 0x403;
                product = strtoul(cursor, &end, 16);
                if (product && end && *end) {
                    prod2 = strtoul(end+1, &end, 16);
                    if (prod2) {
                        vendor = product;
                        product = prod2;
                    }
                }
                if (FT_SetVIDPID(vendor, product))
                    return FALSE;
                Trace("Seeking vendor:product 0x%04x:0x%04x\n", vendor, product);
            }
        }
    }
    return TRUE;
}

FT_STATUS FT_SetVIDPID(
        DWORD dwVID,
        DWORD dwPID
        ){
    struct prm_FT_SetVIDPID a = {.dwVID=dwVID, .dwPID=dwPID};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetVIDPID, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS FT_GetVIDPID(
        DWORD * pdwVID,
        DWORD * pdwPID
        ){
    struct prm_FT_GetVIDPID a = {.pdwVID=pdwVID, .pdwPID=pdwPID};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetVIDPID, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_CreateDeviceInfoList(
        LPDWORD lpdwNumDevs
        ){
    struct prm_FT_CreateDeviceInfoList a = {.lpdwNumDevs=lpdwNumDevs};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_CreateDeviceInfoList, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetDeviceInfoList(
        FT_DEVICE_LIST_INFO_NODE *pDest,
        LPDWORD lpdwNumDevs
        ){
    struct prm_FT_GetDeviceInfoList a = {.pDest=pDest, .lpdwNumDevs=lpdwNumDevs};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetDeviceInfoList, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetDeviceInfoDetail(
        DWORD dwIndex,
        LPDWORD lpdwFlags,
        LPDWORD lpdwType,
        LPDWORD lpdwID,
        LPDWORD lpdwLocId,
        LPVOID lpSerialNumber,
        LPVOID lpDescription,
        FT_HANDLE *pftHandle
        ){
    struct prm_FT_GetDeviceInfoDetail a = {.dwIndex=dwIndex, .lpdwFlags=lpdwFlags, .lpdwType=lpdwType, .lpdwID=lpdwID, .lpdwLocId=lpdwLocId, .lpSerialNumber=lpSerialNumber, .lpDescription=lpDescription, .pftHandle=pftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetDeviceInfoDetail, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ListDevices(
        PVOID pvArg1,
        PVOID pvArg2,
        DWORD dwFlags
        ){
    struct prm_FT_ListDevices a = {.pvArg1=pvArg1, .pvArg2=pvArg2, .dwFlags=dwFlags};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ListDevices, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_Open(
        int deviceNumber,
        FT_HANDLE *pHandle
        ){
    struct prm_FT_Open a = {.deviceNumber=deviceNumber, .pHandle=pHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_Open, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_OpenEx(
        PVOID pvArg1,
        DWORD dwFlags,
        FT_HANDLE *pHandle
        ){
    struct prm_FT_OpenEx a = {.pvArg1=pvArg1, .dwFlags=dwFlags, .pHandle=pHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_OpenEx, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_Close(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_Close a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_Close, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_Read(
        FT_HANDLE ftHandle,
        LPVOID lpBuffer,
        DWORD dwBytesToRead,
        LPDWORD lpdwBytesReturned
        ){
    struct prm_FT_Read a = {.ftHandle=ftHandle, .lpBuffer=lpBuffer, .dwBytesToRead=dwBytesToRead, .lpdwBytesReturned=lpdwBytesReturned};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_Read, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_Write(
        FT_HANDLE ftHandle,
        LPVOID lpBuffer,
        DWORD dwBytesToWrite,
        LPDWORD lpdwBytesWritten
        ){
    struct prm_FT_Write a = {.ftHandle=ftHandle, .lpBuffer=lpBuffer, .dwBytesToWrite=dwBytesToWrite, .lpdwBytesWritten=lpdwBytesWritten};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_Write, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetBaudRate(
        FT_HANDLE ftHandle,
        ULONG dwBaudRate
        ){
    struct prm_FT_SetBaudRate a = {.ftHandle=ftHandle, .dwBaudRate=dwBaudRate};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetBaudRate, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetDivisor(
        FT_HANDLE ftHandle,
        USHORT usDivisor
        ){
    struct prm_FT_SetDivisor a = {.ftHandle=ftHandle, .usDivisor=usDivisor};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetDivisor, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetDataCharacteristics(
        FT_HANDLE ftHandle,
        UCHAR uWordLength,
        UCHAR uStopBits,
        UCHAR uParity
        ){
    struct prm_FT_SetDataCharacteristics a = {.ftHandle=ftHandle, .uWordLength=uWordLength, .uStopBits=uStopBits, .uParity=uParity};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetDataCharacteristics, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetTimeouts(
        FT_HANDLE ftHandle,
        ULONG dwReadTimeout,
        ULONG dwWriteTimeout
        ){
    struct prm_FT_SetTimeouts a = {.ftHandle=ftHandle, .dwReadTimeout=dwReadTimeout, .dwWriteTimeout=dwWriteTimeout};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetTimeouts, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetFlowControl(
        FT_HANDLE ftHandle,
        USHORT usFlowControl,
        UCHAR uXonChar,
        UCHAR uXoffChar
        ){
    struct prm_FT_SetFlowControl a = {.ftHandle=ftHandle, .usFlowControl=usFlowControl, .uXonChar=uXonChar, .uXoffChar=uXoffChar};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetFlowControl, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetDtr(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_SetDtr a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetDtr, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ClrDtr(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_ClrDtr a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ClrDtr, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetRts(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_SetRts a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetRts, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ClrRts(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_ClrRts a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ClrRts, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetModemStatus(
        FT_HANDLE ftHandle,
        ULONG *lpdwModemStatus
        ){
    struct prm_FT_GetModemStatus a = {.ftHandle=ftHandle, .lpdwModemStatus=lpdwModemStatus};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetModemStatus, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetQueueStatus(
        FT_HANDLE ftHandle,
        DWORD *lpdwAmountInRxQueue
        ){
    struct prm_FT_GetQueueStatus a = {.ftHandle=ftHandle, .lpdwAmountInRxQueue=lpdwAmountInRxQueue};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetQueueStatus, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetDeviceInfo(
        FT_HANDLE ftHandle,
        FT_DEVICE *lpftDevice,
        LPDWORD lpdwID,
        PCHAR pcSerialNumber,
        PCHAR pcDescription,
        LPVOID pvDummy
        ){
    struct prm_FT_GetDeviceInfo a = {.ftHandle=ftHandle, .lpftDevice=lpftDevice, .lpdwID=lpdwID, .pcSerialNumber=pcSerialNumber, .pcDescription=pcDescription, .pvDummy=pvDummy};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetDeviceInfo, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetDeviceLocId(
        FT_HANDLE ftHandle,
        LPDWORD lpdwLocId
        ){
    struct prm_FT_GetDeviceLocId a = {.ftHandle=ftHandle, .lpdwLocId=lpdwLocId};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetDeviceLocId, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetDriverVersion(
        FT_HANDLE ftHandle,
        LPDWORD lpdwDriverVersion
        ){
    struct prm_FT_GetDriverVersion a = {.ftHandle=ftHandle, .lpdwDriverVersion=lpdwDriverVersion};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetDriverVersion, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetLibraryVersion(
        LPDWORD lpdwDLLVersion
        ){
    struct prm_FT_GetLibraryVersion a = {.lpdwDLLVersion=lpdwDLLVersion};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetLibraryVersion, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetComPortNumber(
        FT_HANDLE ftHandle,
        LPLONG    lplComPortNumber
        ){
    struct prm_FT_GetComPortNumber a = {.ftHandle=ftHandle, .lplComPortNumber=lplComPortNumber};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetComPortNumber, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetStatus(
        FT_HANDLE ftHandle,
        DWORD *lpdwAmountInRxQueue,
        DWORD *lpdwAmountInTxQueue,
        DWORD *lpdwEventStatus
        ){
    struct prm_FT_GetStatus a = {.ftHandle=ftHandle, .lpdwAmountInRxQueue=lpdwAmountInRxQueue, .lpdwAmountInTxQueue=lpdwAmountInTxQueue, .lpdwEventStatus=lpdwEventStatus};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetStatus, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetEventNotification(
        FT_HANDLE ftHandle,
        DWORD dwEventMask,
        PVOID pvArg
        ){
    struct prm_FT_SetEventNotification a = {.ftHandle=ftHandle, .dwEventMask=dwEventMask, .pvArg=pvArg};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetEventNotification, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetChars(
        FT_HANDLE ftHandle,
        UCHAR uEventChar,
        UCHAR uEventCharEnabled,
        UCHAR uErrorChar,
        UCHAR uErrorCharEnabled
        ){
    struct prm_FT_SetChars a = {.ftHandle=ftHandle, .uEventChar=uEventChar, .uEventCharEnabled=uEventCharEnabled, .uErrorChar=uErrorChar, .uErrorCharEnabled=uErrorCharEnabled};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetChars, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetBreakOn(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_SetBreakOn a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetBreakOn, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetBreakOff(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_SetBreakOff a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetBreakOff, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_Purge(
        FT_HANDLE ftHandle,
        ULONG ulMask
        ){
    struct prm_FT_Purge a = {.ftHandle=ftHandle, .ulMask=ulMask};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_Purge, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ResetDevice(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_ResetDevice a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ResetDevice, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ResetPort(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_ResetPort a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ResetPort, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_CyclePort(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_CyclePort a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_CyclePort, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_Rescan(
        void
        ){
    struct prm_FT_Rescan a = {};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_Rescan, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_Reload(
        WORD wVID,
        WORD wPID
        ){
    struct prm_FT_Reload a = {.wVID=wVID, .wPID=wPID};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_Reload, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetResetPipeRetryCount(
        FT_HANDLE ftHandle,
        DWORD dwCount
        ){
    struct prm_FT_SetResetPipeRetryCount a = {.ftHandle=ftHandle, .dwCount=dwCount};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetResetPipeRetryCount, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_StopInTask(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_StopInTask a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_StopInTask, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_RestartInTask(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_RestartInTask a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_RestartInTask, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetDeadmanTimeout(
        FT_HANDLE ftHandle,
        ULONG ulDeadmanTimeout
        ){
    struct prm_FT_SetDeadmanTimeout a = {.ftHandle=ftHandle, .ulDeadmanTimeout=ulDeadmanTimeout};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetDeadmanTimeout, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_IoCtl(
        FT_HANDLE ftHandle,
        DWORD dwIoControlCode,
        LPVOID lpInBuf,
        DWORD nInBufSize,
        LPVOID lpOutBuf,
        DWORD nOutBufSize,
        LPDWORD lpBytesReturned,
        LPOVERLAPPED lpOverlapped
        ){
    struct prm_FT_IoCtl a = {.ftHandle=ftHandle, .dwIoControlCode=dwIoControlCode, .lpInBuf=lpInBuf, .nInBufSize=nInBufSize, .lpOutBuf=lpOutBuf, .nOutBufSize=nOutBufSize, .lpBytesReturned=lpBytesReturned, .lpOverlapped=lpOverlapped};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_IoCtl, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetWaitMask(
        FT_HANDLE ftHandle,
        DWORD Mask
        ){
    struct prm_FT_SetWaitMask a = {.ftHandle=ftHandle, .Mask=Mask};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetWaitMask, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_WaitOnMask(
        FT_HANDLE ftHandle,
        DWORD *Mask
        ){
    struct prm_FT_WaitOnMask a = {.ftHandle=ftHandle, .Mask=Mask};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_WaitOnMask, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetEventStatus(
        FT_HANDLE ftHandle,
        DWORD *dwEventDWord
        ){
    struct prm_FT_GetEventStatus a = {.ftHandle=ftHandle, .dwEventDWord=dwEventDWord};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetEventStatus, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ReadEE(
        FT_HANDLE ftHandle,
        DWORD dwWordOffset,
        LPWORD lpwValue
        ){
    struct prm_FT_ReadEE a = {.ftHandle=ftHandle, .dwWordOffset=dwWordOffset, .lpwValue=lpwValue};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ReadEE, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_WriteEE(
        FT_HANDLE ftHandle,
        DWORD dwWordOffset,
        WORD wValue
        ){
    struct prm_FT_WriteEE a = {.ftHandle=ftHandle, .dwWordOffset=dwWordOffset, .wValue=wValue};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_WriteEE, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EraseEE(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_EraseEE a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EraseEE, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_Read(
        FT_HANDLE ftHandle,
        PFT_PROGRAM_DATA pData
        ){
    struct prm_FT_EE_Read a = {.ftHandle=ftHandle, .pData=pData};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_Read, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_ReadEx(
        FT_HANDLE ftHandle,
        PFT_PROGRAM_DATA pData,
        char *Manufacturer,
        char *ManufacturerId,
        char *Description,
        char *SerialNumber
        ){
    struct prm_FT_EE_ReadEx a = {.ftHandle=ftHandle, .pData=pData, .Manufacturer=Manufacturer, .ManufacturerId=ManufacturerId, .Description=Description, .SerialNumber=SerialNumber};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_ReadEx, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_Program(
        FT_HANDLE ftHandle,
        PFT_PROGRAM_DATA pData
        ){
    struct prm_FT_EE_Program a = {.ftHandle=ftHandle, .pData=pData};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_Program, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_ProgramEx(
        FT_HANDLE ftHandle,
        PFT_PROGRAM_DATA pData,
        char *Manufacturer,
        char *ManufacturerId,
        char *Description,
        char *SerialNumber
        ){
    struct prm_FT_EE_ProgramEx a = {.ftHandle=ftHandle, .pData=pData, .Manufacturer=Manufacturer, .ManufacturerId=ManufacturerId, .Description=Description, .SerialNumber=SerialNumber};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_ProgramEx, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_UASize(
        FT_HANDLE ftHandle,
        LPDWORD lpdwSize
        ){
    struct prm_FT_EE_UASize a = {.ftHandle=ftHandle, .lpdwSize=lpdwSize};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_UASize, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_UARead(
        FT_HANDLE ftHandle,
        PUCHAR pucData,
        DWORD dwDataLen,
        LPDWORD lpdwBytesRead
        ){
    struct prm_FT_EE_UARead a = {.ftHandle=ftHandle, .pucData=pucData, .dwDataLen=dwDataLen, .lpdwBytesRead=lpdwBytesRead};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_UARead, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_UAWrite(
        FT_HANDLE ftHandle,
        PUCHAR pucData,
        DWORD dwDataLen
        ){
    struct prm_FT_EE_UAWrite a = {.ftHandle=ftHandle, .pucData=pucData, .dwDataLen=dwDataLen};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_UAWrite, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EEPROM_Read(
        FT_HANDLE ftHandle,
        void *eepromData,
        DWORD eepromDataSize,
        char *Manufacturer,
        char *ManufacturerId,
        char *Description,
        char *SerialNumber
        ){
    struct prm_FT_EEPROM_Read a = {.ftHandle=ftHandle, .eepromData=eepromData, .eepromDataSize=eepromDataSize, .Manufacturer=Manufacturer, .ManufacturerId=ManufacturerId, .Description=Description, .SerialNumber=SerialNumber};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EEPROM_Read, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EEPROM_Program(
        FT_HANDLE ftHandle,
        void *eepromData,
        DWORD eepromDataSize,
        char *Manufacturer,
        char *ManufacturerId,
        char *Description,
        char *SerialNumber
        ){
    struct prm_FT_EEPROM_Program a = {.ftHandle=ftHandle, .eepromData=eepromData, .eepromDataSize=eepromDataSize, .Manufacturer=Manufacturer, .ManufacturerId=ManufacturerId, .Description=Description, .SerialNumber=SerialNumber};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EEPROM_Program, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetLatencyTimer(
        FT_HANDLE ftHandle,
        UCHAR ucLatency
        ){
    struct prm_FT_SetLatencyTimer a = {.ftHandle=ftHandle, .ucLatency=ucLatency};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetLatencyTimer, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetLatencyTimer(
        FT_HANDLE ftHandle,
        PUCHAR pucLatency
        ){
    struct prm_FT_GetLatencyTimer a = {.ftHandle=ftHandle, .pucLatency=pucLatency};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetLatencyTimer, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetBitMode(
        FT_HANDLE ftHandle,
        UCHAR ucMask,
        UCHAR ucEnable
        ){
    struct prm_FT_SetBitMode a = {.ftHandle=ftHandle, .ucMask=ucMask, .ucEnable=ucEnable};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetBitMode, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetBitMode(
        FT_HANDLE ftHandle,
        PUCHAR pucMode
        ){
    struct prm_FT_GetBitMode a = {.ftHandle=ftHandle, .pucMode=pucMode};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetBitMode, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_SetUSBParameters(
        FT_HANDLE ftHandle,
        ULONG ulInTransferSize,
        ULONG ulOutTransferSize
        ){
    struct prm_FT_SetUSBParameters a = {.ftHandle=ftHandle, .ulInTransferSize=ulInTransferSize, .ulOutTransferSize=ulOutTransferSize};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_SetUSBParameters, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_HANDLE WINAPI FT_W32_CreateFile(
        LPCTSTR                    lpszName,
        DWORD                    dwAccess,
        DWORD                    dwShareMode,
        LPSECURITY_ATTRIBUTES    lpSecurityAttributes,
        DWORD                    dwCreate,
        DWORD                    dwAttrsAndFlags,
        HANDLE                    hTemplate
        ){
    struct prm_FT_W32_CreateFile a = {.lpszName=lpszName, .dwAccess=dwAccess, .dwShareMode=dwShareMode, .lpSecurityAttributes=lpSecurityAttributes, .dwCreate=dwCreate, .dwAttrsAndFlags=dwAttrsAndFlags, .hTemplate=hTemplate};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_CreateFile, &a );
    Trace("Returned\n");
    return a.ret;
}

BOOL WINAPI FT_W32_CloseHandle(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_W32_CloseHandle a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_CloseHandle, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_ReadFile(
        FT_HANDLE ftHandle,
        LPVOID lpBuffer,
        DWORD nBufferSize,
        LPDWORD lpdwBytesReturned,
        LPOVERLAPPED lpOverlapped
        ){
    struct prm_FT_W32_ReadFile a = {.ftHandle=ftHandle, .lpBuffer=lpBuffer, .nBufferSize=nBufferSize, .lpdwBytesReturned=lpdwBytesReturned, .lpOverlapped=lpOverlapped};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_ReadFile, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_WriteFile(
        FT_HANDLE ftHandle,
        LPVOID lpBuffer,
        DWORD nBufferSize,
        LPDWORD lpdwBytesWritten,
        LPOVERLAPPED lpOverlapped
        ){
    struct prm_FT_W32_WriteFile a = {.ftHandle=ftHandle, .lpBuffer=lpBuffer, .nBufferSize=nBufferSize, .lpdwBytesWritten=lpdwBytesWritten, .lpOverlapped=lpOverlapped};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_WriteFile, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_GetOverlappedResult(
        FT_HANDLE ftHandle,
        LPOVERLAPPED lpOverlapped,
        LPDWORD lpdwBytesTransferred,
        BOOL bWait
        ){
    struct prm_FT_W32_GetOverlappedResult a = {.ftHandle=ftHandle, .lpOverlapped=lpOverlapped, .lpdwBytesTransferred=lpdwBytesTransferred, .bWait=bWait};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_GetOverlappedResult, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_EscapeCommFunction(
        FT_HANDLE ftHandle,
        DWORD dwFunc
        ){
    struct prm_FT_W32_EscapeCommFunction a = {.ftHandle=ftHandle, .dwFunc=dwFunc};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_EscapeCommFunction, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_GetCommModemStatus(
        FT_HANDLE ftHandle,
        LPDWORD lpdwModemStatus
        ){
    struct prm_FT_W32_GetCommModemStatus a = {.ftHandle=ftHandle, .lpdwModemStatus=lpdwModemStatus};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_GetCommModemStatus, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_SetupComm(
        FT_HANDLE ftHandle,
        DWORD dwReadBufferSize,
        DWORD dwWriteBufferSize
        ){
    struct prm_FT_W32_SetupComm a = {.ftHandle=ftHandle, .dwReadBufferSize=dwReadBufferSize, .dwWriteBufferSize=dwWriteBufferSize};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_SetupComm, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_SetCommState(
        FT_HANDLE ftHandle,
        LPFTDCB lpftDcb
        ){
    struct prm_FT_W32_SetCommState a = {.ftHandle=ftHandle, .lpftDcb=lpftDcb};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_SetCommState, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_GetCommState(
        FT_HANDLE ftHandle,
        LPFTDCB lpftDcb
        ){
    struct prm_FT_W32_GetCommState a = {.ftHandle=ftHandle, .lpftDcb=lpftDcb};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_GetCommState, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_SetCommTimeouts(
        FT_HANDLE ftHandle,
        FTTIMEOUTS *pftTimeouts
        ){
    struct prm_FT_W32_SetCommTimeouts a = {.ftHandle=ftHandle, .pftTimeouts=pftTimeouts};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_SetCommTimeouts, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_GetCommTimeouts(
        FT_HANDLE ftHandle,
        FTTIMEOUTS *pftTimeouts
        ){
    struct prm_FT_W32_GetCommTimeouts a = {.ftHandle=ftHandle, .pftTimeouts=pftTimeouts};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_GetCommTimeouts, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_SetCommBreak(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_W32_SetCommBreak a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_SetCommBreak, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_ClearCommBreak(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_W32_ClearCommBreak a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_ClearCommBreak, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_SetCommMask(
        FT_HANDLE ftHandle,
        ULONG ulEventMask
        ){
    struct prm_FT_W32_SetCommMask a = {.ftHandle=ftHandle, .ulEventMask=ulEventMask};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_SetCommMask, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_WaitCommEvent(
        FT_HANDLE ftHandle,
        PULONG pulEvent,
        LPOVERLAPPED lpOverlapped
        ){
    struct prm_FT_W32_WaitCommEvent a = {.ftHandle=ftHandle, .pulEvent=pulEvent, .lpOverlapped=lpOverlapped};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_WaitCommEvent, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_PurgeComm(
        FT_HANDLE ftHandle,
        DWORD dwMask
        ){
    struct prm_FT_W32_PurgeComm a = {.ftHandle=ftHandle, .dwMask=dwMask};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_PurgeComm, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_ClearCommError(
        FT_HANDLE ftHandle,
        LPDWORD lpdwErrors,
        LPFTCOMSTAT lpftComstat
        ){
    struct prm_FT_W32_ClearCommError a = {.ftHandle=ftHandle, .lpdwErrors=lpdwErrors, .lpftComstat=lpftComstat};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_ClearCommError, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

BOOL WINAPI FT_W32_CancelIo(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_W32_CancelIo a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_W32_CancelIo, &a );
    Trace("Return %d\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_ReadConfig(
        FT_HANDLE ftHandle,
        UCHAR ucAddress,
        PUCHAR pucValue
        ){
    struct prm_FT_EE_ReadConfig a = {.ftHandle=ftHandle, .ucAddress=ucAddress, .pucValue=pucValue};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_ReadConfig, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_WriteConfig(
        FT_HANDLE ftHandle,
        UCHAR ucAddress,
        UCHAR ucValue
        ){
    struct prm_FT_EE_WriteConfig a = {.ftHandle=ftHandle, .ucAddress=ucAddress, .ucValue=ucValue};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_WriteConfig, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_EE_ReadECC(
        FT_HANDLE ftHandle,
        UCHAR ucOption,
        LPWORD lpwValue
        ){
    struct prm_FT_EE_ReadECC a = {.ftHandle=ftHandle, .ucOption=ucOption, .lpwValue=lpwValue};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_EE_ReadECC, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_GetQueueStatusEx(
        FT_HANDLE ftHandle,
        DWORD *dwRxBytes
        ){
    struct prm_FT_GetQueueStatusEx a = {.ftHandle=ftHandle, .dwRxBytes=dwRxBytes};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_GetQueueStatusEx, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ComPortIdle(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_ComPortIdle a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ComPortIdle, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_ComPortCancelIdle(
        FT_HANDLE ftHandle
        ){
    struct prm_FT_ComPortCancelIdle a = {.ftHandle=ftHandle};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_ComPortCancelIdle, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_VendorCmdGet(
        FT_HANDLE ftHandle,
        UCHAR Request,
        UCHAR *Buf,
        USHORT Len
        ){
    struct prm_FT_VendorCmdGet a = {.ftHandle=ftHandle, .Request=Request, .Buf=Buf, .Len=Len};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_VendorCmdGet, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_VendorCmdSet(
        FT_HANDLE ftHandle,
        UCHAR Request,
        UCHAR *Buf,
        USHORT Len
        ){
    struct prm_FT_VendorCmdSet a = {.ftHandle=ftHandle, .Request=Request, .Buf=Buf, .Len=Len};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_VendorCmdSet, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_VendorCmdGetEx(
        FT_HANDLE ftHandle,
        USHORT wValue,
        UCHAR *Buf,
        USHORT Len
        ){
    struct prm_FT_VendorCmdGetEx a = {.ftHandle=ftHandle, .wValue=wValue, .Buf=Buf, .Len=Len};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_VendorCmdGetEx, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

FT_STATUS WINAPI FT_VendorCmdSetEx(
        FT_HANDLE ftHandle,
        USHORT wValue,
        UCHAR *Buf,
        USHORT Len
        ){
    struct prm_FT_VendorCmdSetEx a = {.ftHandle=ftHandle, .wValue=wValue, .Buf=Buf, .Len=Len};
    Trace("Entering\n");
    WINE_UNIX_CALL( unix_FT_VendorCmdSetEx, &a );
    Trace("Return %lu\n", a.ret);
    return a.ret;
}

#else

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    return TRUE;
}

#endif
