/*
 * Definitions for Unix library
 *
 * Copyright (C) 2025 Asela Fernando
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/*
NOTES:
 *   Proxy libftd2xx manager.  This manager delegates all ftd2xx.dll
 *   calls to a real libftd2xx.so
*/

#ifndef __UNIXLIB_H
#define __UNIXLIB_H

#include <stdarg.h>
#include <stdint.h>
//#include <windef.h> //Included in ftd2xx.h

typedef const char                *LPCTSTR;
#include "ftd2xx.h"

#ifndef WINE_NTSTATUS_DECLARED
#define WINE_NTSTATUS_DECLARED
typedef long NTSTATUS;
#endif

#define STATUS_SUCCESS                   ((NTSTATUS) 0x00000000)
#define STATUS_UNSUCCESSFUL              ((NTSTATUS) 0xC0000001)

typedef uint64_t unixlib_handle_t;

#ifdef WINE_UNIX_LIB

typedef NTSTATUS (*unixlib_entry_t)( void *args );

extern __attribute__((visibility ("default"))) const unixlib_entry_t __wine_unix_call_funcs[];
extern __attribute__((visibility ("default"))) const unixlib_entry_t __wine_unix_call_wow64_funcs[];

#else

NTSYSAPI NTSTATUS WINAPI __wine_unix_call( unixlib_handle_t handle, unsigned int code, void *args );
extern unixlib_handle_t __wine_unixlib_handle;
extern NTSTATUS (WINAPI *__wine_unix_call_dispatcher)( unixlib_handle_t, unsigned int, void * );
extern NTSTATUS WINAPI __wine_init_unix_call(void);

#define WINE_UNIX_CALL(code,args) __wine_unix_call_dispatcher( __wine_unixlib_handle, (code), (args) )

#endif

struct prm_FT_SetVIDPID { DWORD dwVID; DWORD dwPID; FT_STATUS ret; };
struct p32_FT_SetVIDPID { DWORD dwVID; DWORD dwPID; FT_STATUS ret; };

struct prm_FT_GetVIDPID { DWORD * pdwVID; DWORD * pdwPID; FT_STATUS ret; };
struct p32_FT_GetVIDPID { uint32_t pdwVID; uint32_t pdwPID; FT_STATUS ret; };

struct prm_FT_CreateDeviceInfoList { LPDWORD lpdwNumDevs; FT_STATUS ret; };
struct p32_FT_CreateDeviceInfoList { uint32_t lpdwNumDevs; FT_STATUS ret; };

struct prm_FT_GetDeviceInfoList { FT_DEVICE_LIST_INFO_NODE *pDest; LPDWORD lpdwNumDevs; FT_STATUS ret; };
struct p32_FT_GetDeviceInfoList { uint32_t pDest; uint32_t lpdwNumDevs; FT_STATUS ret; };

struct prm_FT_GetDeviceInfoDetail { DWORD dwIndex; LPDWORD lpdwFlags; LPDWORD lpdwType; LPDWORD lpdwID; LPDWORD lpdwLocId; LPVOID lpSerialNumber; LPVOID lpDescription; FT_HANDLE *pftHandle; FT_STATUS ret; };
struct p32_FT_GetDeviceInfoDetail { DWORD dwIndex; uint32_t lpdwFlags; uint32_t lpdwType; uint32_t lpdwID; uint32_t lpdwLocId; uint32_t lpSerialNumber; uint32_t lpDescription; uint32_t pftHandle; FT_STATUS ret; };

struct prm_FT_ListDevices { PVOID pvArg1; PVOID pvArg2; DWORD dwFlags; FT_STATUS ret; };
struct p32_FT_ListDevices { uint32_t pvArg1; uint32_t pvArg2; DWORD dwFlags; FT_STATUS ret; };

struct prm_FT_Open { int deviceNumber; FT_HANDLE *pHandle; FT_STATUS ret; };
struct p32_FT_Open { int deviceNumber; uint32_t pHandle; FT_STATUS ret; };

struct prm_FT_OpenEx { PVOID pvArg1; DWORD dwFlags; FT_HANDLE *pHandle; FT_STATUS ret; };
struct p32_FT_OpenEx { uint32_t pvArg1; DWORD dwFlags; uint32_t pHandle; FT_STATUS ret; };

struct prm_FT_Close { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_Close { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_Read { FT_HANDLE ftHandle; LPVOID lpBuffer; DWORD dwBytesToRead; LPDWORD lpdwBytesReturned; FT_STATUS ret; };
struct p32_FT_Read { uint32_t ftHandle; uint32_t lpBuffer; DWORD dwBytesToRead; uint32_t lpdwBytesReturned; FT_STATUS ret; };

struct prm_FT_Write { FT_HANDLE ftHandle; LPVOID lpBuffer; DWORD dwBytesToWrite; LPDWORD lpdwBytesWritten; FT_STATUS ret; };
struct p32_FT_Write { uint32_t ftHandle; uint32_t lpBuffer; DWORD dwBytesToWrite; uint32_t lpdwBytesWritten; FT_STATUS ret; };

struct prm_FT_SetBaudRate { FT_HANDLE ftHandle; ULONG dwBaudRate; FT_STATUS ret; };
struct p32_FT_SetBaudRate { uint32_t ftHandle; ULONG dwBaudRate; FT_STATUS ret; };

struct prm_FT_SetDivisor { FT_HANDLE ftHandle; USHORT usDivisor; FT_STATUS ret; };
struct p32_FT_SetDivisor { uint32_t ftHandle; USHORT usDivisor; FT_STATUS ret; };

struct prm_FT_SetDataCharacteristics { FT_HANDLE ftHandle; UCHAR uWordLength; UCHAR uStopBits; UCHAR uParity; FT_STATUS ret; };
struct p32_FT_SetDataCharacteristics { uint32_t ftHandle; UCHAR uWordLength; UCHAR uStopBits; UCHAR uParity; FT_STATUS ret; };

struct prm_FT_SetTimeouts { FT_HANDLE ftHandle; ULONG dwReadTimeout; ULONG dwWriteTimeout; FT_STATUS ret; };
struct p32_FT_SetTimeouts { uint32_t ftHandle; ULONG dwReadTimeout; ULONG dwWriteTimeout; FT_STATUS ret; };

struct prm_FT_SetFlowControl { FT_HANDLE ftHandle; USHORT usFlowControl; UCHAR uXonChar; UCHAR uXoffChar; FT_STATUS ret; };
struct p32_FT_SetFlowControl { uint32_t ftHandle; USHORT usFlowControl; UCHAR uXonChar; UCHAR uXoffChar; FT_STATUS ret; };

struct prm_FT_SetDtr { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_SetDtr { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_ClrDtr { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_ClrDtr { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_SetRts { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_SetRts { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_ClrRts { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_ClrRts { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_GetModemStatus { FT_HANDLE ftHandle; ULONG *lpdwModemStatus; FT_STATUS ret; };
struct p32_FT_GetModemStatus { uint32_t ftHandle; uint32_t lpdwModemStatus; FT_STATUS ret; };

struct prm_FT_GetQueueStatus { FT_HANDLE ftHandle; DWORD *lpdwAmountInRxQueue; FT_STATUS ret; };
struct p32_FT_GetQueueStatus { uint32_t ftHandle; uint32_t lpdwAmountInRxQueue; FT_STATUS ret; };

struct prm_FT_GetDeviceInfo { FT_HANDLE ftHandle; FT_DEVICE *lpftDevice; LPDWORD lpdwID; PCHAR pcSerialNumber; PCHAR pcDescription; LPVOID pvDummy; FT_STATUS ret; };
struct p32_FT_GetDeviceInfo { uint32_t ftHandle; uint32_t lpftDevice; uint32_t lpdwID; uint32_t pcSerialNumber; uint32_t pcDescription; uint32_t pvDummy; FT_STATUS ret; };

struct prm_FT_GetDeviceLocId { FT_HANDLE ftHandle; LPDWORD lpdwLocId; FT_STATUS ret; };
struct p32_FT_GetDeviceLocId { uint32_t ftHandle; uint32_t lpdwLocId; FT_STATUS ret; };

struct prm_FT_GetDriverVersion { FT_HANDLE ftHandle; LPDWORD lpdwDriverVersion; FT_STATUS ret; };
struct p32_FT_GetDriverVersion { uint32_t ftHandle; uint32_t lpdwDriverVersion; FT_STATUS ret; };

struct prm_FT_GetLibraryVersion { LPDWORD lpdwDLLVersion; FT_STATUS ret; };
struct p32_FT_GetLibraryVersion { uint32_t lpdwDLLVersion; FT_STATUS ret; };

struct prm_FT_GetComPortNumber { FT_HANDLE ftHandle; LPLONG lplComPortNumber; FT_STATUS ret; };
struct p32_FT_GetComPortNumber { uint32_t ftHandle; uint32_t lplComPortNumber; FT_STATUS ret; };

struct prm_FT_GetStatus { FT_HANDLE ftHandle; DWORD *lpdwAmountInRxQueue; DWORD *lpdwAmountInTxQueue; DWORD *lpdwEventStatus; FT_STATUS ret; };
struct p32_FT_GetStatus { uint32_t ftHandle; uint32_t lpdwAmountInRxQueue; uint32_t lpdwAmountInTxQueue; uint32_t lpdwEventStatus; FT_STATUS ret; };

struct prm_FT_SetEventNotification { FT_HANDLE ftHandle; DWORD dwEventMask; PVOID pvArg; FT_STATUS ret; };
struct p32_FT_SetEventNotification { uint32_t ftHandle; DWORD dwEventMask; uint32_t pvArg; FT_STATUS ret; };

struct prm_FT_SetChars { FT_HANDLE ftHandle; UCHAR uEventChar; UCHAR uEventCharEnabled; UCHAR uErrorChar; UCHAR uErrorCharEnabled; FT_STATUS ret; };
struct p32_FT_SetChars { uint32_t ftHandle; UCHAR uEventChar; UCHAR uEventCharEnabled; UCHAR uErrorChar; UCHAR uErrorCharEnabled; FT_STATUS ret; };

struct prm_FT_SetBreakOn { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_SetBreakOn { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_SetBreakOff { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_SetBreakOff { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_Purge { FT_HANDLE ftHandle; ULONG ulMask; FT_STATUS ret; };
struct p32_FT_Purge { uint32_t ftHandle; ULONG ulMask; FT_STATUS ret; };

struct prm_FT_ResetDevice { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_ResetDevice { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_ResetPort { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_ResetPort { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_CyclePort { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_CyclePort { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_Rescan { FT_STATUS ret; };
struct p32_FT_Rescan { FT_STATUS ret; };

struct prm_FT_Reload { WORD wVID; WORD wPID; FT_STATUS ret; };
struct p32_FT_Reload { WORD wVID; WORD wPID; FT_STATUS ret; };

struct prm_FT_SetResetPipeRetryCount { FT_HANDLE ftHandle; DWORD dwCount; FT_STATUS ret; };
struct p32_FT_SetResetPipeRetryCount { uint32_t ftHandle; DWORD dwCount; FT_STATUS ret; };

struct prm_FT_StopInTask { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_StopInTask { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_RestartInTask { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_RestartInTask { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_SetDeadmanTimeout { FT_HANDLE ftHandle; ULONG ulDeadmanTimeout; FT_STATUS ret; };
struct p32_FT_SetDeadmanTimeout { uint32_t ftHandle; ULONG ulDeadmanTimeout; FT_STATUS ret; };

struct prm_FT_IoCtl { FT_HANDLE ftHandle; DWORD dwIoControlCode; LPVOID lpInBuf; DWORD nInBufSize; LPVOID lpOutBuf; DWORD nOutBufSize; LPDWORD lpBytesReturned; LPOVERLAPPED lpOverlapped; FT_STATUS ret; };
struct p32_FT_IoCtl { uint32_t ftHandle; DWORD dwIoControlCode; uint32_t lpInBuf; DWORD nInBufSize; uint32_t lpOutBuf; DWORD nOutBufSize; uint32_t lpBytesReturned; uint32_t lpOverlapped; FT_STATUS ret; };

struct prm_FT_SetWaitMask { FT_HANDLE ftHandle; DWORD Mask; FT_STATUS ret; };
struct p32_FT_SetWaitMask { uint32_t ftHandle; DWORD Mask; FT_STATUS ret; };

struct prm_FT_WaitOnMask { FT_HANDLE ftHandle; DWORD *Mask; FT_STATUS ret; };
struct p32_FT_WaitOnMask { uint32_t ftHandle; uint32_t Mask; FT_STATUS ret; };

struct prm_FT_GetEventStatus { FT_HANDLE ftHandle; DWORD *dwEventDWord; FT_STATUS ret; };
struct p32_FT_GetEventStatus { uint32_t ftHandle; uint32_t dwEventDWord; FT_STATUS ret; };

struct prm_FT_ReadEE { FT_HANDLE ftHandle; DWORD dwWordOffset; LPWORD lpwValue; FT_STATUS ret; };
struct p32_FT_ReadEE { uint32_t ftHandle; DWORD dwWordOffset; uint32_t lpwValue; FT_STATUS ret; };

struct prm_FT_WriteEE { FT_HANDLE ftHandle; DWORD dwWordOffset; WORD wValue; FT_STATUS ret; };
struct p32_FT_WriteEE { uint32_t ftHandle; DWORD dwWordOffset; WORD wValue; FT_STATUS ret; };

struct prm_FT_EraseEE { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_EraseEE { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_EE_Read { FT_HANDLE ftHandle; PFT_PROGRAM_DATA pData; FT_STATUS ret; };
struct p32_FT_EE_Read { uint32_t ftHandle; uint32_t pData; FT_STATUS ret; };

struct prm_FT_EE_ReadEx { FT_HANDLE ftHandle; PFT_PROGRAM_DATA pData; char *Manufacturer; char *ManufacturerId; char *Description; char *SerialNumber; FT_STATUS ret; };
struct p32_FT_EE_ReadEx { uint32_t ftHandle; uint32_t pData; uint32_t Manufacturer; uint32_t ManufacturerId; uint32_t Description; uint32_t SerialNumber; FT_STATUS ret; };

struct prm_FT_EE_Program { FT_HANDLE ftHandle; PFT_PROGRAM_DATA pData; FT_STATUS ret; };
struct p32_FT_EE_Program { uint32_t ftHandle; uint32_t pData; FT_STATUS ret; };

struct prm_FT_EE_ProgramEx { FT_HANDLE ftHandle; PFT_PROGRAM_DATA pData; char *Manufacturer; char *ManufacturerId; char *Description; char *SerialNumber; FT_STATUS ret; };
struct p32_FT_EE_ProgramEx { uint32_t ftHandle; uint32_t pData; uint32_t Manufacturer; uint32_t ManufacturerId; uint32_t Description; uint32_t SerialNumber; FT_STATUS ret; };

struct prm_FT_EE_UASize { FT_HANDLE ftHandle; LPDWORD lpdwSize; FT_STATUS ret; };
struct p32_FT_EE_UASize { uint32_t ftHandle; uint32_t lpdwSize; FT_STATUS ret; };

struct prm_FT_EE_UARead { FT_HANDLE ftHandle; PUCHAR pucData; DWORD dwDataLen; LPDWORD lpdwBytesRead; FT_STATUS ret; };
struct p32_FT_EE_UARead { uint32_t ftHandle; uint32_t pucData; DWORD dwDataLen; uint32_t lpdwBytesRead; FT_STATUS ret; };

struct prm_FT_EE_UAWrite { FT_HANDLE ftHandle; PUCHAR pucData; DWORD dwDataLen; FT_STATUS ret; };
struct p32_FT_EE_UAWrite { uint32_t ftHandle; uint32_t pucData; DWORD dwDataLen; FT_STATUS ret; };

struct prm_FT_EEPROM_Read { FT_HANDLE ftHandle; void *eepromData; DWORD eepromDataSize; char *Manufacturer; char *ManufacturerId; char *Description; char *SerialNumber; FT_STATUS ret; };
struct p32_FT_EEPROM_Read { uint32_t ftHandle; uint32_t eepromData; DWORD eepromDataSize; uint32_t Manufacturer; uint32_t ManufacturerId; uint32_t Description; uint32_t SerialNumber; FT_STATUS ret; };

struct prm_FT_EEPROM_Program { FT_HANDLE ftHandle; void *eepromData; DWORD eepromDataSize; char *Manufacturer; char *ManufacturerId; char *Description; char *SerialNumber; FT_STATUS ret; };
struct p32_FT_EEPROM_Program { uint32_t ftHandle; uint32_t eepromData; DWORD eepromDataSize; uint32_t Manufacturer; uint32_t ManufacturerId; uint32_t Description; uint32_t SerialNumber; FT_STATUS ret; };

struct prm_FT_SetLatencyTimer { FT_HANDLE ftHandle; UCHAR ucLatency; FT_STATUS ret; };
struct p32_FT_SetLatencyTimer { uint32_t ftHandle; UCHAR ucLatency; FT_STATUS ret; };

struct prm_FT_GetLatencyTimer { FT_HANDLE ftHandle; PUCHAR pucLatency; FT_STATUS ret; };
struct p32_FT_GetLatencyTimer { uint32_t ftHandle; uint32_t pucLatency; FT_STATUS ret; };

struct prm_FT_SetBitMode { FT_HANDLE ftHandle; UCHAR ucMask; UCHAR ucEnable; FT_STATUS ret; };
struct p32_FT_SetBitMode { uint32_t ftHandle; UCHAR ucMask; UCHAR ucEnable; FT_STATUS ret; };

struct prm_FT_GetBitMode { FT_HANDLE ftHandle; PUCHAR pucMode; FT_STATUS ret; };
struct p32_FT_GetBitMode { uint32_t ftHandle; uint32_t pucMode; FT_STATUS ret; };

struct prm_FT_SetUSBParameters { FT_HANDLE ftHandle; ULONG ulInTransferSize; ULONG ulOutTransferSize; FT_STATUS ret; };
struct p32_FT_SetUSBParameters { uint32_t ftHandle; ULONG ulInTransferSize; ULONG ulOutTransferSize; FT_STATUS ret; };

struct prm_FT_W32_CreateFile { LPCTSTR lpszName; DWORD dwAccess; DWORD dwShareMode; LPSECURITY_ATTRIBUTES lpSecurityAttributes; DWORD dwCreate; DWORD dwAttrsAndFlags; HANDLE hTemplate; FT_HANDLE ret; };
struct p32_FT_W32_CreateFile { uint32_t lpszName; DWORD dwAccess; DWORD dwShareMode; uint32_t lpSecurityAttributes; DWORD dwCreate; DWORD dwAttrsAndFlags; HANDLE hTemplate; FT_HANDLE ret; };

struct prm_FT_W32_CloseHandle { FT_HANDLE ftHandle; BOOL ret; };
struct p32_FT_W32_CloseHandle { uint32_t ftHandle; BOOL ret; };

struct prm_FT_W32_ReadFile { FT_HANDLE ftHandle; LPVOID lpBuffer; DWORD nBufferSize; LPDWORD lpdwBytesReturned; LPOVERLAPPED lpOverlapped; BOOL ret; };
struct p32_FT_W32_ReadFile { uint32_t ftHandle; uint32_t lpBuffer; DWORD nBufferSize; uint32_t lpdwBytesReturned; uint32_t lpOverlapped; BOOL ret; };

struct prm_FT_W32_WriteFile { FT_HANDLE ftHandle; LPVOID lpBuffer; DWORD nBufferSize; LPDWORD lpdwBytesWritten; LPOVERLAPPED lpOverlapped; BOOL ret; };
struct p32_FT_W32_WriteFile { uint32_t ftHandle; uint32_t lpBuffer; DWORD nBufferSize; uint32_t lpdwBytesWritten; uint32_t lpOverlapped; BOOL ret; };

struct prm_FT_W32_GetOverlappedResult { FT_HANDLE ftHandle; LPOVERLAPPED lpOverlapped; LPDWORD lpdwBytesTransferred; BOOL bWait; BOOL ret; };
struct p32_FT_W32_GetOverlappedResult { uint32_t ftHandle; uint32_t lpOverlapped; uint32_t lpdwBytesTransferred; BOOL bWait; BOOL ret; };

struct prm_FT_W32_EscapeCommFunction { FT_HANDLE ftHandle; DWORD dwFunc; BOOL ret; };
struct p32_FT_W32_EscapeCommFunction { uint32_t ftHandle; DWORD dwFunc; BOOL ret; };

struct prm_FT_W32_GetCommModemStatus { FT_HANDLE ftHandle; LPDWORD lpdwModemStatus; BOOL ret; };
struct p32_FT_W32_GetCommModemStatus { uint32_t ftHandle; uint32_t lpdwModemStatus; BOOL ret; };

struct prm_FT_W32_SetupComm { FT_HANDLE ftHandle; DWORD dwReadBufferSize; DWORD dwWriteBufferSize; BOOL ret; };
struct p32_FT_W32_SetupComm { uint32_t ftHandle; DWORD dwReadBufferSize; DWORD dwWriteBufferSize; BOOL ret; };

struct prm_FT_W32_SetCommState { FT_HANDLE ftHandle; LPFTDCB lpftDcb; BOOL ret; };
struct p32_FT_W32_SetCommState { uint32_t ftHandle; uint32_t lpftDcb; BOOL ret; };

struct prm_FT_W32_GetCommState { FT_HANDLE ftHandle; LPFTDCB lpftDcb; BOOL ret; };
struct p32_FT_W32_GetCommState { uint32_t ftHandle; uint32_t lpftDcb; BOOL ret; };

struct prm_FT_W32_SetCommTimeouts { FT_HANDLE ftHandle; FTTIMEOUTS *pftTimeouts; BOOL ret; };
struct p32_FT_W32_SetCommTimeouts { uint32_t ftHandle; uint32_t pftTimeouts; BOOL ret; };

struct prm_FT_W32_GetCommTimeouts { FT_HANDLE ftHandle; FTTIMEOUTS *pftTimeouts; BOOL ret; };
struct p32_FT_W32_GetCommTimeouts { uint32_t ftHandle; uint32_t pftTimeouts; BOOL ret; };

struct prm_FT_W32_SetCommBreak { FT_HANDLE ftHandle; BOOL ret; };
struct p32_FT_W32_SetCommBreak { uint32_t ftHandle; BOOL ret; };

struct prm_FT_W32_ClearCommBreak { FT_HANDLE ftHandle; BOOL ret; };
struct p32_FT_W32_ClearCommBreak { uint32_t ftHandle; BOOL ret; };

struct prm_FT_W32_SetCommMask { FT_HANDLE ftHandle; ULONG ulEventMask; BOOL ret; };
struct p32_FT_W32_SetCommMask { uint32_t ftHandle; ULONG ulEventMask; BOOL ret; };

struct prm_FT_W32_WaitCommEvent { FT_HANDLE ftHandle; PULONG pulEvent; LPOVERLAPPED lpOverlapped; BOOL ret; };
struct p32_FT_W32_WaitCommEvent { uint32_t ftHandle; uint32_t pulEvent; uint32_t lpOverlapped; BOOL ret; };

struct prm_FT_W32_PurgeComm { FT_HANDLE ftHandle; DWORD dwMask; BOOL ret; };
struct p32_FT_W32_PurgeComm { uint32_t ftHandle; DWORD dwMask; BOOL ret; };

struct prm_FT_W32_ClearCommError { FT_HANDLE ftHandle; LPDWORD lpdwErrors; LPFTCOMSTAT lpftComstat; BOOL ret; };
struct p32_FT_W32_ClearCommError { uint32_t ftHandle; uint32_t lpdwErrors; uint32_t lpftComstat; BOOL ret; };

struct prm_FT_W32_CancelIo { FT_HANDLE ftHandle; BOOL ret; };
struct p32_FT_W32_CancelIo { uint32_t ftHandle; BOOL ret; };

struct prm_FT_EE_ReadConfig { FT_HANDLE ftHandle; UCHAR ucAddress; PUCHAR pucValue; FT_STATUS ret; };
struct p32_FT_EE_ReadConfig { uint32_t ftHandle; UCHAR ucAddress; uint32_t pucValue; FT_STATUS ret; };

struct prm_FT_EE_WriteConfig { FT_HANDLE ftHandle; UCHAR ucAddress; UCHAR ucValue; FT_STATUS ret; };
struct p32_FT_EE_WriteConfig { uint32_t ftHandle; UCHAR ucAddress; UCHAR ucValue; FT_STATUS ret; };

struct prm_FT_EE_ReadECC { FT_HANDLE ftHandle; UCHAR ucOption; LPWORD lpwValue; FT_STATUS ret; };
struct p32_FT_EE_ReadECC { uint32_t ftHandle; UCHAR ucOption; uint32_t lpwValue; FT_STATUS ret; };

struct prm_FT_GetQueueStatusEx { FT_HANDLE ftHandle; DWORD *dwRxBytes; FT_STATUS ret; };
struct p32_FT_GetQueueStatusEx { uint32_t ftHandle; uint32_t dwRxBytes; FT_STATUS ret; };

struct prm_FT_ComPortIdle { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_ComPortIdle { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_ComPortCancelIdle { FT_HANDLE ftHandle; FT_STATUS ret; };
struct p32_FT_ComPortCancelIdle { uint32_t ftHandle; FT_STATUS ret; };

struct prm_FT_VendorCmdGet { FT_HANDLE ftHandle; UCHAR Request; UCHAR *Buf; USHORT Len; FT_STATUS ret; };
struct p32_FT_VendorCmdGet { uint32_t ftHandle; UCHAR Request; uint32_t Buf; USHORT Len; FT_STATUS ret; };

struct prm_FT_VendorCmdSet { FT_HANDLE ftHandle; UCHAR Request; UCHAR *Buf; USHORT Len; FT_STATUS ret; };
struct p32_FT_VendorCmdSet { uint32_t ftHandle; UCHAR Request; uint32_t Buf; USHORT Len; FT_STATUS ret; };

struct prm_FT_VendorCmdGetEx { FT_HANDLE ftHandle; USHORT wValue; UCHAR *Buf; USHORT Len; FT_STATUS ret; };
struct p32_FT_VendorCmdGetEx { uint32_t ftHandle; USHORT wValue; uint32_t Buf; USHORT Len; FT_STATUS ret; };

struct prm_FT_VendorCmdSetEx { FT_HANDLE ftHandle; USHORT wValue; UCHAR *Buf; USHORT Len; FT_STATUS ret; };
struct p32_FT_VendorCmdSetEx { uint32_t ftHandle; USHORT wValue; uint32_t Buf; USHORT Len; FT_STATUS ret; };

enum unix_func {
    unix_FT_SetVIDPID,
    unix_FT_GetVIDPID,
    unix_FT_CreateDeviceInfoList,
    unix_FT_GetDeviceInfoList,
    unix_FT_GetDeviceInfoDetail,
    unix_FT_ListDevices,
    unix_FT_Open,
    unix_FT_OpenEx,
    unix_FT_Close,
    unix_FT_Read,
    unix_FT_Write,
    unix_FT_SetBaudRate,
    unix_FT_SetDivisor,
    unix_FT_SetDataCharacteristics,
    unix_FT_SetTimeouts,
    unix_FT_SetFlowControl,
    unix_FT_SetDtr,
    unix_FT_ClrDtr,
    unix_FT_SetRts,
    unix_FT_ClrRts,
    unix_FT_GetModemStatus,
    unix_FT_GetQueueStatus,
    unix_FT_GetDeviceInfo,
    unix_FT_GetDeviceLocId,
    unix_FT_GetDriverVersion,
    unix_FT_GetLibraryVersion,
    unix_FT_GetComPortNumber,
    unix_FT_GetStatus,
    unix_FT_SetEventNotification,
    unix_FT_SetChars,
    unix_FT_SetBreakOn,
    unix_FT_SetBreakOff,
    unix_FT_Purge,
    unix_FT_ResetDevice,
    unix_FT_ResetPort,
    unix_FT_CyclePort,
    unix_FT_Rescan,
    unix_FT_Reload,
    unix_FT_SetResetPipeRetryCount,
    unix_FT_StopInTask,
    unix_FT_RestartInTask,
    unix_FT_SetDeadmanTimeout,
    unix_FT_IoCtl,
    unix_FT_SetWaitMask,
    unix_FT_WaitOnMask,
    unix_FT_GetEventStatus,
    unix_FT_ReadEE,
    unix_FT_WriteEE,
    unix_FT_EraseEE,
    unix_FT_EE_Read,
    unix_FT_EE_ReadEx,
    unix_FT_EE_Program,
    unix_FT_EE_ProgramEx,
    unix_FT_EE_UASize,
    unix_FT_EE_UARead,
    unix_FT_EE_UAWrite,
    unix_FT_EEPROM_Read,
    unix_FT_EEPROM_Program,
    unix_FT_SetLatencyTimer,
    unix_FT_GetLatencyTimer,
    unix_FT_SetBitMode,
    unix_FT_GetBitMode,
    unix_FT_SetUSBParameters,
    unix_FT_W32_CreateFile,
    unix_FT_W32_CloseHandle,
    unix_FT_W32_ReadFile,
    unix_FT_W32_WriteFile,
    unix_FT_W32_GetOverlappedResult,
    unix_FT_W32_EscapeCommFunction,
    unix_FT_W32_GetCommModemStatus,
    unix_FT_W32_SetupComm,
    unix_FT_W32_SetCommState,
    unix_FT_W32_GetCommState,
    unix_FT_W32_SetCommTimeouts,
    unix_FT_W32_GetCommTimeouts,
    unix_FT_W32_SetCommBreak,
    unix_FT_W32_ClearCommBreak,
    unix_FT_W32_SetCommMask,
    unix_FT_W32_WaitCommEvent,
    unix_FT_W32_PurgeComm,
    unix_FT_W32_ClearCommError,
    unix_FT_W32_CancelIo,
    unix_FT_EE_ReadConfig,
    unix_FT_EE_WriteConfig,
    unix_FT_EE_ReadECC,
    unix_FT_GetQueueStatusEx,
    unix_FT_ComPortIdle,
    unix_FT_ComPortCancelIdle,
    unix_FT_VendorCmdGet,
    unix_FT_VendorCmdSet,
    unix_FT_VendorCmdGetEx,
    unix_FT_VendorCmdSetEx,
};

#endif
