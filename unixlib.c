/*
 * FTD2XX Wine Unix library
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

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "unixlib.h"

static inline void *ULongToPtr(uint32_t ul)
{
    return (void *)(uint64_t)ul;
}

NTSTATUS wrap_FT_SetVIDPID(void *args) {
    struct prm_FT_SetVIDPID *a = args;
    a->ret = FT_SetVIDPID(a->dwVID, a->dwPID);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetVIDPID(void *args) {
    struct p32_FT_SetVIDPID *a = args;
    a->ret = FT_SetVIDPID(a->dwVID, a->dwPID);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetVIDPID(void *args) {
    struct prm_FT_GetVIDPID *a = args;
    a->ret = FT_GetVIDPID(a->pdwVID, a->pdwPID);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetVIDPID(void *args) {
    struct p32_FT_GetVIDPID *a = args;
    a->ret = FT_GetVIDPID((DWORD *)ULongToPtr(a->pdwVID), (DWORD *)ULongToPtr(a->pdwPID));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_CreateDeviceInfoList(void *args) {
    struct prm_FT_CreateDeviceInfoList *a = args;
    a->ret = FT_CreateDeviceInfoList(a->lpdwNumDevs);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_CreateDeviceInfoList(void *args) {
    struct p32_FT_CreateDeviceInfoList *a = args;
    a->ret = FT_CreateDeviceInfoList((LPDWORD)ULongToPtr(a->lpdwNumDevs));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetDeviceInfoList(void *args) {
    struct prm_FT_GetDeviceInfoList *a = args;
    a->ret = FT_GetDeviceInfoList(a->pDest, a->lpdwNumDevs);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetDeviceInfoList(void *args) {
    struct p32_FT_GetDeviceInfoList *a = args;
    a->ret = FT_GetDeviceInfoList((FT_DEVICE_LIST_INFO_NODE*)ULongToPtr(a->pDest), (LPDWORD)ULongToPtr(a->lpdwNumDevs));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetDeviceInfoDetail(void *args) {
    struct prm_FT_GetDeviceInfoDetail *a = args;
    a->ret = FT_GetDeviceInfoDetail(a->dwIndex, a->lpdwFlags, a->lpdwType, a->lpdwID, a->lpdwLocId, a->lpSerialNumber, a->lpDescription, a->pftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetDeviceInfoDetail(void *args) {
    struct p32_FT_GetDeviceInfoDetail *a = args;
    a->ret = FT_GetDeviceInfoDetail(a->dwIndex, (LPDWORD)ULongToPtr(a->lpdwFlags), (LPDWORD)ULongToPtr(a->lpdwType), (LPDWORD)ULongToPtr(a->lpdwID), (LPDWORD)ULongToPtr(a->lpdwLocId), (LPVOID)ULongToPtr(a->lpSerialNumber), (LPVOID)ULongToPtr(a->lpDescription), (FT_HANDLE*)ULongToPtr(a->pftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ListDevices(void *args) {
    struct prm_FT_ListDevices *a = args;
    a->ret = FT_ListDevices(a->pvArg1, a->pvArg2, a->dwFlags);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ListDevices(void *args) {
    struct p32_FT_ListDevices *a = args;
    a->ret = FT_ListDevices((PVOID)ULongToPtr(a->pvArg1), (PVOID)ULongToPtr(a->pvArg2), a->dwFlags);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_Open(void *args) {
    struct prm_FT_Open *a = args;
    a->ret = FT_Open(a->deviceNumber, a->pHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_Open(void *args) {
    struct p32_FT_Open *a = args;
    a->ret = FT_Open(a->deviceNumber, (FT_HANDLE*)ULongToPtr(a->pHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_OpenEx(void *args) {
    struct prm_FT_OpenEx *a = args;
    a->ret = FT_OpenEx(a->pvArg1, a->dwFlags, a->pHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_OpenEx(void *args) {
    struct p32_FT_OpenEx *a = args;
    a->ret = FT_OpenEx((PVOID)ULongToPtr(a->pvArg1), a->dwFlags, (FT_HANDLE*)ULongToPtr(a->pHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_Close(void *args) {
    struct prm_FT_Close *a = args;
    a->ret = FT_Close(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_Close(void *args) {
    struct p32_FT_Close *a = args;
    a->ret = FT_Close((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_Read(void *args) {
    struct prm_FT_Read *a = args;
    a->ret = FT_Read(a->ftHandle, a->lpBuffer, a->dwBytesToRead, a->lpdwBytesReturned);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_Read(void *args) {
    struct p32_FT_Read *a = args;
    a->ret = FT_Read((FT_HANDLE)ULongToPtr(a->ftHandle), (LPVOID)ULongToPtr(a->lpBuffer), a->dwBytesToRead, (LPDWORD)ULongToPtr(a->lpdwBytesReturned));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_Write(void *args) {
    struct prm_FT_Write *a = args;
    a->ret = FT_Write(a->ftHandle, a->lpBuffer, a->dwBytesToWrite, a->lpdwBytesWritten);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_Write(void *args) {
    struct p32_FT_Write *a = args;
    a->ret = FT_Write((FT_HANDLE)ULongToPtr(a->ftHandle), (LPVOID)ULongToPtr(a->lpBuffer), a->dwBytesToWrite, (LPDWORD)ULongToPtr(a->lpdwBytesWritten));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetBaudRate(void *args) {
    struct prm_FT_SetBaudRate *a = args;
    a->ret = FT_SetBaudRate(a->ftHandle, a->dwBaudRate);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetBaudRate(void *args) {
    struct p32_FT_SetBaudRate *a = args;
    a->ret = FT_SetBaudRate((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwBaudRate);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetDivisor(void *args) {
    struct prm_FT_SetDivisor *a = args;
    a->ret = FT_SetDivisor(a->ftHandle, a->usDivisor);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetDivisor(void *args) {
    struct p32_FT_SetDivisor *a = args;
    a->ret = FT_SetDivisor((FT_HANDLE)ULongToPtr(a->ftHandle), a->usDivisor);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetDataCharacteristics(void *args) {
    struct prm_FT_SetDataCharacteristics *a = args;
    a->ret = FT_SetDataCharacteristics(a->ftHandle, a->uWordLength, a->uStopBits, a->uParity);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetDataCharacteristics(void *args) {
    struct p32_FT_SetDataCharacteristics *a = args;
    a->ret = FT_SetDataCharacteristics((FT_HANDLE)ULongToPtr(a->ftHandle), a->uWordLength, a->uStopBits, a->uParity);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetTimeouts(void *args) {
    struct prm_FT_SetTimeouts *a = args;
    a->ret = FT_SetTimeouts(a->ftHandle, a->dwReadTimeout, a->dwWriteTimeout);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetTimeouts(void *args) {
    struct p32_FT_SetTimeouts *a = args;
    a->ret = FT_SetTimeouts((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwReadTimeout, a->dwWriteTimeout);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetFlowControl(void *args) {
    struct prm_FT_SetFlowControl *a = args;
    a->ret = FT_SetFlowControl(a->ftHandle, a->usFlowControl, a->uXonChar, a->uXoffChar);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetFlowControl(void *args) {
    struct p32_FT_SetFlowControl *a = args;
    a->ret = FT_SetFlowControl((FT_HANDLE)ULongToPtr(a->ftHandle), a->usFlowControl, a->uXonChar, a->uXoffChar);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetDtr(void *args) {
    struct prm_FT_SetDtr *a = args;
    a->ret = FT_SetDtr(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetDtr(void *args) {
    struct p32_FT_SetDtr *a = args;
    a->ret = FT_SetDtr((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ClrDtr(void *args) {
    struct prm_FT_ClrDtr *a = args;
    a->ret = FT_ClrDtr(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ClrDtr(void *args) {
    struct p32_FT_ClrDtr *a = args;
    a->ret = FT_ClrDtr((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetRts(void *args) {
    struct prm_FT_SetRts *a = args;
    a->ret = FT_SetRts(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetRts(void *args) {
    struct p32_FT_SetRts *a = args;
    a->ret = FT_SetRts((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ClrRts(void *args) {
    struct prm_FT_ClrRts *a = args;
    a->ret = FT_ClrRts(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ClrRts(void *args) {
    struct p32_FT_ClrRts *a = args;
    a->ret = FT_ClrRts((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetModemStatus(void *args) {
    struct prm_FT_GetModemStatus *a = args;
    a->ret = FT_GetModemStatus(a->ftHandle, a->lpdwModemStatus);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetModemStatus(void *args) {
    struct p32_FT_GetModemStatus *a = args;
    a->ret = FT_GetModemStatus((FT_HANDLE)ULongToPtr(a->ftHandle), (ULONG*)ULongToPtr(a->lpdwModemStatus));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetQueueStatus(void *args) {
    struct prm_FT_GetQueueStatus *a = args;
    a->ret = FT_GetQueueStatus(a->ftHandle, a->lpdwAmountInRxQueue);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetQueueStatus(void *args) {
    struct p32_FT_GetQueueStatus *a = args;
    a->ret = FT_GetQueueStatus((FT_HANDLE)ULongToPtr(a->ftHandle), (DWORD*)ULongToPtr(a->lpdwAmountInRxQueue));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetDeviceInfo(void *args) {
    struct prm_FT_GetDeviceInfo *a = args;
    a->ret = FT_GetDeviceInfo(a->ftHandle, a->lpftDevice, a->lpdwID, a->pcSerialNumber, a->pcDescription, a->pvDummy);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetDeviceInfo(void *args) {
    struct p32_FT_GetDeviceInfo *a = args;
    a->ret = FT_GetDeviceInfo((FT_HANDLE)ULongToPtr(a->ftHandle), (FT_DEVICE*)ULongToPtr(a->lpftDevice), (LPDWORD)ULongToPtr(a->lpdwID), (PCHAR)ULongToPtr(a->pcSerialNumber), (PCHAR)ULongToPtr(a->pcDescription), (LPVOID)ULongToPtr(a->pvDummy));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetDeviceLocId(void *args) {
    struct prm_FT_GetDeviceLocId *a = args;
    a->ret = FT_GetDeviceLocId(a->ftHandle, a->lpdwLocId);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetDeviceLocId(void *args) {
    struct p32_FT_GetDeviceLocId *a = args;
    a->ret = FT_GetDeviceLocId((FT_HANDLE)ULongToPtr(a->ftHandle), (LPDWORD)ULongToPtr(a->lpdwLocId));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetDriverVersion(void *args) {
    struct prm_FT_GetDriverVersion *a = args;
    a->ret = FT_GetDriverVersion(a->ftHandle, a->lpdwDriverVersion);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetDriverVersion(void *args) {
    struct p32_FT_GetDriverVersion *a = args;
    a->ret = FT_GetDriverVersion((FT_HANDLE)ULongToPtr(a->ftHandle), (LPDWORD)ULongToPtr(a->lpdwDriverVersion));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetLibraryVersion(void *args) {
    struct prm_FT_GetLibraryVersion *a = args;
    a->ret = FT_GetLibraryVersion(a->lpdwDLLVersion);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetLibraryVersion(void *args) {
    struct p32_FT_GetLibraryVersion *a = args;
    a->ret = FT_GetLibraryVersion((LPDWORD)ULongToPtr(a->lpdwDLLVersion));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetComPortNumber(void *args) {
    struct prm_FT_GetComPortNumber *a = args;
    a->ret = FT_GetComPortNumber(a->ftHandle, a->lplComPortNumber);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetComPortNumber(void *args) {
    struct p32_FT_GetComPortNumber *a = args;
    a->ret = FT_GetComPortNumber((FT_HANDLE)ULongToPtr(a->ftHandle), (LPLONG)ULongToPtr(a->lplComPortNumber));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetStatus(void *args) {
    struct prm_FT_GetStatus *a = args;
    a->ret = FT_GetStatus(a->ftHandle, a->lpdwAmountInRxQueue, a->lpdwAmountInTxQueue, a->lpdwEventStatus);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetStatus(void *args) {
    struct p32_FT_GetStatus *a = args;
    a->ret = FT_GetStatus((FT_HANDLE)ULongToPtr(a->ftHandle), (DWORD*)ULongToPtr(a->lpdwAmountInRxQueue), (DWORD*)ULongToPtr(a->lpdwAmountInTxQueue), (DWORD*)ULongToPtr(a->lpdwEventStatus));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetEventNotification(void *args) {
    struct prm_FT_SetEventNotification *a = args;
    a->ret = FT_SetEventNotification(a->ftHandle, a->dwEventMask, a->pvArg);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetEventNotification(void *args) {
    struct p32_FT_SetEventNotification *a = args;
    a->ret = FT_SetEventNotification((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwEventMask, (PVOID)ULongToPtr(a->pvArg));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetChars(void *args) {
    struct prm_FT_SetChars *a = args;
    a->ret = FT_SetChars(a->ftHandle, a->uEventChar, a->uEventCharEnabled, a->uErrorChar, a->uErrorCharEnabled);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetChars(void *args) {
    struct p32_FT_SetChars *a = args;
    a->ret = FT_SetChars((FT_HANDLE)ULongToPtr(a->ftHandle), a->uEventChar, a->uEventCharEnabled, a->uErrorChar, a->uErrorCharEnabled);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetBreakOn(void *args) {
    struct prm_FT_SetBreakOn *a = args;
    a->ret = FT_SetBreakOn(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetBreakOn(void *args) {
    struct p32_FT_SetBreakOn *a = args;
    a->ret = FT_SetBreakOn((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetBreakOff(void *args) {
    struct prm_FT_SetBreakOff *a = args;
    a->ret = FT_SetBreakOff(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetBreakOff(void *args) {
    struct p32_FT_SetBreakOff *a = args;
    a->ret = FT_SetBreakOff((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_Purge(void *args) {
    struct prm_FT_Purge *a = args;
    a->ret = FT_Purge(a->ftHandle, a->ulMask);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_Purge(void *args) {
    struct p32_FT_Purge *a = args;
    a->ret = FT_Purge((FT_HANDLE)ULongToPtr(a->ftHandle), a->ulMask);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ResetDevice(void *args) {
    struct prm_FT_ResetDevice *a = args;
    a->ret = FT_ResetDevice(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ResetDevice(void *args) {
    struct p32_FT_ResetDevice *a = args;
    a->ret = FT_ResetDevice((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ResetPort(void *args) {
    struct prm_FT_ResetPort *a = args;
    a->ret = FT_ResetPort(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ResetPort(void *args) {
    struct p32_FT_ResetPort *a = args;
    a->ret = FT_ResetPort((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_CyclePort(void *args) {
    struct prm_FT_CyclePort *a = args;
    a->ret = FT_CyclePort(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_CyclePort(void *args) {
    struct p32_FT_CyclePort *a = args;
    a->ret = FT_CyclePort((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_Rescan(void *args) {
    struct prm_FT_Rescan *a = args;
    a->ret = FT_Rescan();
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_Rescan(void *args) {
    struct p32_FT_Rescan *a = args;
    a->ret = FT_Rescan();
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_Reload(void *args) {
    struct prm_FT_Reload *a = args;
    a->ret = FT_Reload(a->wVID, a->wPID);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_Reload(void *args) {
    struct p32_FT_Reload *a = args;
    a->ret = FT_Reload(a->wVID, a->wPID);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetResetPipeRetryCount(void *args) {
    struct prm_FT_SetResetPipeRetryCount *a = args;
    a->ret = FT_SetResetPipeRetryCount(a->ftHandle, a->dwCount);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetResetPipeRetryCount(void *args) {
    struct p32_FT_SetResetPipeRetryCount *a = args;
    a->ret = FT_SetResetPipeRetryCount((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwCount);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_StopInTask(void *args) {
    struct prm_FT_StopInTask *a = args;
    a->ret = FT_StopInTask(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_StopInTask(void *args) {
    struct p32_FT_StopInTask *a = args;
    a->ret = FT_StopInTask((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_RestartInTask(void *args) {
    struct prm_FT_RestartInTask *a = args;
    a->ret = FT_RestartInTask(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_RestartInTask(void *args) {
    struct p32_FT_RestartInTask *a = args;
    a->ret = FT_RestartInTask((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetDeadmanTimeout(void *args) {
    struct prm_FT_SetDeadmanTimeout *a = args;
    a->ret = FT_SetDeadmanTimeout(a->ftHandle, a->ulDeadmanTimeout);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetDeadmanTimeout(void *args) {
    struct p32_FT_SetDeadmanTimeout *a = args;
    a->ret = FT_SetDeadmanTimeout((FT_HANDLE)ULongToPtr(a->ftHandle), a->ulDeadmanTimeout);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_IoCtl(void *args) {
    struct prm_FT_IoCtl *a = args;
    a->ret = FT_IoCtl(a->ftHandle, a->dwIoControlCode, a->lpInBuf, a->nInBufSize, a->lpOutBuf, a->nOutBufSize, a->lpBytesReturned, a->lpOverlapped);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_IoCtl(void *args) {
    struct p32_FT_IoCtl *a = args;
    a->ret = FT_IoCtl((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwIoControlCode, (LPVOID)ULongToPtr(a->lpInBuf), a->nInBufSize, (LPVOID)ULongToPtr(a->lpOutBuf), a->nOutBufSize, (LPDWORD)ULongToPtr(a->lpBytesReturned), (LPOVERLAPPED)ULongToPtr(a->lpOverlapped));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetWaitMask(void *args) {
    struct prm_FT_SetWaitMask *a = args;
    a->ret = FT_SetWaitMask(a->ftHandle, a->Mask);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetWaitMask(void *args) {
    struct p32_FT_SetWaitMask *a = args;
    a->ret = FT_SetWaitMask((FT_HANDLE)ULongToPtr(a->ftHandle), a->Mask);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_WaitOnMask(void *args) {
    struct prm_FT_WaitOnMask *a = args;
    a->ret = FT_WaitOnMask(a->ftHandle, a->Mask);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_WaitOnMask(void *args) {
    struct p32_FT_WaitOnMask *a = args;
    a->ret = FT_WaitOnMask((FT_HANDLE)ULongToPtr(a->ftHandle), (DWORD*)ULongToPtr(a->Mask));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetEventStatus(void *args) {
    struct prm_FT_GetEventStatus *a = args;
    a->ret = FT_GetEventStatus(a->ftHandle, a->dwEventDWord);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetEventStatus(void *args) {
    struct p32_FT_GetEventStatus *a = args;
    a->ret = FT_GetEventStatus((FT_HANDLE)ULongToPtr(a->ftHandle), (DWORD*)ULongToPtr(a->dwEventDWord));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ReadEE(void *args) {
    struct prm_FT_ReadEE *a = args;
    a->ret = FT_ReadEE(a->ftHandle, a->dwWordOffset, a->lpwValue);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ReadEE(void *args) {
    struct p32_FT_ReadEE *a = args;
    a->ret = FT_ReadEE((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwWordOffset, (LPWORD)ULongToPtr(a->lpwValue));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_WriteEE(void *args) {
    struct prm_FT_WriteEE *a = args;
    a->ret = FT_WriteEE(a->ftHandle, a->dwWordOffset, a->wValue);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_WriteEE(void *args) {
    struct p32_FT_WriteEE *a = args;
    a->ret = FT_WriteEE((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwWordOffset, a->wValue);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EraseEE(void *args) {
    struct prm_FT_EraseEE *a = args;
    a->ret = FT_EraseEE(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EraseEE(void *args) {
    struct p32_FT_EraseEE *a = args;
    a->ret = FT_EraseEE((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_Read(void *args) {
    struct prm_FT_EE_Read *a = args;
    a->ret = FT_EE_Read(a->ftHandle, a->pData);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_Read(void *args) {
    struct p32_FT_EE_Read *a = args;
    a->ret = FT_EE_Read((FT_HANDLE)ULongToPtr(a->ftHandle), (PFT_PROGRAM_DATA)ULongToPtr(a->pData));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_ReadEx(void *args) {
    struct prm_FT_EE_ReadEx *a = args;
    a->ret = FT_EE_ReadEx(a->ftHandle, a->pData, a->Manufacturer, a->ManufacturerId, a->Description, a->SerialNumber);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_ReadEx(void *args) {
    struct p32_FT_EE_ReadEx *a = args;
    a->ret = FT_EE_ReadEx((FT_HANDLE)ULongToPtr(a->ftHandle), (PFT_PROGRAM_DATA)ULongToPtr(a->pData), (char*)ULongToPtr(a->Manufacturer), (char*)ULongToPtr(a->ManufacturerId), (char*)ULongToPtr(a->Description), (char*)ULongToPtr(a->SerialNumber));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_Program(void *args) {
    struct prm_FT_EE_Program *a = args;
    a->ret = FT_EE_Program(a->ftHandle, a->pData);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_Program(void *args) {
    struct p32_FT_EE_Program *a = args;
    a->ret = FT_EE_Program((FT_HANDLE)ULongToPtr(a->ftHandle), (PFT_PROGRAM_DATA)ULongToPtr(a->pData));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_ProgramEx(void *args) {
    struct prm_FT_EE_ProgramEx *a = args;
    a->ret = FT_EE_ProgramEx(a->ftHandle, a->pData, a->Manufacturer, a->ManufacturerId, a->Description, a->SerialNumber);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_ProgramEx(void *args) {
    struct p32_FT_EE_ProgramEx *a = args;
    a->ret = FT_EE_ProgramEx((FT_HANDLE)ULongToPtr(a->ftHandle), (PFT_PROGRAM_DATA)ULongToPtr(a->pData), (char*)ULongToPtr(a->Manufacturer), (char*)ULongToPtr(a->ManufacturerId), (char*)ULongToPtr(a->Description), (char*)ULongToPtr(a->SerialNumber));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_UASize(void *args) {
    struct prm_FT_EE_UASize *a = args;
    a->ret = FT_EE_UASize(a->ftHandle, a->lpdwSize);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_UASize(void *args) {
    struct p32_FT_EE_UASize *a = args;
    a->ret = FT_EE_UASize((FT_HANDLE)ULongToPtr(a->ftHandle), (LPDWORD)ULongToPtr(a->lpdwSize));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_UARead(void *args) {
    struct prm_FT_EE_UARead *a = args;
    a->ret = FT_EE_UARead(a->ftHandle, a->pucData, a->dwDataLen, a->lpdwBytesRead);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_UARead(void *args) {
    struct p32_FT_EE_UARead *a = args;
    a->ret = FT_EE_UARead((FT_HANDLE)ULongToPtr(a->ftHandle), (PUCHAR)ULongToPtr(a->pucData), a->dwDataLen, (LPDWORD)ULongToPtr(a->lpdwBytesRead));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_UAWrite(void *args) {
    struct prm_FT_EE_UAWrite *a = args;
    a->ret = FT_EE_UAWrite(a->ftHandle, a->pucData, a->dwDataLen);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_UAWrite(void *args) {
    struct p32_FT_EE_UAWrite *a = args;
    a->ret = FT_EE_UAWrite((FT_HANDLE)ULongToPtr(a->ftHandle), (PUCHAR)ULongToPtr(a->pucData), a->dwDataLen);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EEPROM_Read(void *args) {
    struct prm_FT_EEPROM_Read *a = args;
    a->ret = FT_EEPROM_Read(a->ftHandle, a->eepromData, a->eepromDataSize, a->Manufacturer, a->ManufacturerId, a->Description, a->SerialNumber);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EEPROM_Read(void *args) {
    struct p32_FT_EEPROM_Read *a = args;
    a->ret = FT_EEPROM_Read((FT_HANDLE)ULongToPtr(a->ftHandle), (void*)ULongToPtr(a->eepromData), a->eepromDataSize, (char*)ULongToPtr(a->Manufacturer), (char*)ULongToPtr(a->ManufacturerId), (char*)ULongToPtr(a->Description), (char*)ULongToPtr(a->SerialNumber));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EEPROM_Program(void *args) {
    struct prm_FT_EEPROM_Program *a = args;
    a->ret = FT_EEPROM_Program(a->ftHandle, a->eepromData, a->eepromDataSize, a->Manufacturer, a->ManufacturerId, a->Description, a->SerialNumber);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EEPROM_Program(void *args) {
    struct p32_FT_EEPROM_Program *a = args;
    a->ret = FT_EEPROM_Program((FT_HANDLE)ULongToPtr(a->ftHandle), (void*)ULongToPtr(a->eepromData), a->eepromDataSize, (char*)ULongToPtr(a->Manufacturer), (char*)ULongToPtr(a->ManufacturerId), (char*)ULongToPtr(a->Description), (char*)ULongToPtr(a->SerialNumber));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetLatencyTimer(void *args) {
    struct prm_FT_SetLatencyTimer *a = args;
    a->ret = FT_SetLatencyTimer(a->ftHandle, a->ucLatency);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetLatencyTimer(void *args) {
    struct p32_FT_SetLatencyTimer *a = args;
    a->ret = FT_SetLatencyTimer((FT_HANDLE)ULongToPtr(a->ftHandle), a->ucLatency);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetLatencyTimer(void *args) {
    struct prm_FT_GetLatencyTimer *a = args;
    a->ret = FT_GetLatencyTimer(a->ftHandle, a->pucLatency);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetLatencyTimer(void *args) {
    struct p32_FT_GetLatencyTimer *a = args;
    a->ret = FT_GetLatencyTimer((FT_HANDLE)ULongToPtr(a->ftHandle), (PUCHAR)ULongToPtr(a->pucLatency));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetBitMode(void *args) {
    struct prm_FT_SetBitMode *a = args;
    a->ret = FT_SetBitMode(a->ftHandle, a->ucMask, a->ucEnable);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetBitMode(void *args) {
    struct p32_FT_SetBitMode *a = args;
    a->ret = FT_SetBitMode((FT_HANDLE)ULongToPtr(a->ftHandle), a->ucMask, a->ucEnable);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetBitMode(void *args) {
    struct prm_FT_GetBitMode *a = args;
    a->ret = FT_GetBitMode(a->ftHandle, a->pucMode);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetBitMode(void *args) {
    struct p32_FT_GetBitMode *a = args;
    a->ret = FT_GetBitMode((FT_HANDLE)ULongToPtr(a->ftHandle), (PUCHAR)ULongToPtr(a->pucMode));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_SetUSBParameters(void *args) {
    struct prm_FT_SetUSBParameters *a = args;
    a->ret = FT_SetUSBParameters(a->ftHandle, a->ulInTransferSize, a->ulOutTransferSize);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_SetUSBParameters(void *args) {
    struct p32_FT_SetUSBParameters *a = args;
    a->ret = FT_SetUSBParameters((FT_HANDLE)ULongToPtr(a->ftHandle), a->ulInTransferSize, a->ulOutTransferSize);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_CreateFile(void *args) {
    struct prm_FT_W32_CreateFile *a = args;
    a->ret = FT_W32_CreateFile(a->lpszName, a->dwAccess, a->dwShareMode, a->lpSecurityAttributes, a->dwCreate, a->dwAttrsAndFlags, a->hTemplate);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_CreateFile(void *args) {
    struct p32_FT_W32_CreateFile *a = args;
    a->ret = FT_W32_CreateFile((LPCTSTR)ULongToPtr(a->lpszName), a->dwAccess, a->dwShareMode, (LPSECURITY_ATTRIBUTES)ULongToPtr(a->lpSecurityAttributes), a->dwCreate, a->dwAttrsAndFlags, a->hTemplate);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_CloseHandle(void *args) {
    struct prm_FT_W32_CloseHandle *a = args;
    a->ret = FT_W32_CloseHandle(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_CloseHandle(void *args) {
    struct p32_FT_W32_CloseHandle *a = args;
    a->ret = FT_W32_CloseHandle((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_ReadFile(void *args) {
    struct prm_FT_W32_ReadFile *a = args;
    a->ret = FT_W32_ReadFile(a->ftHandle, a->lpBuffer, a->nBufferSize, a->lpdwBytesReturned, a->lpOverlapped);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_ReadFile(void *args) {
    struct p32_FT_W32_ReadFile *a = args;
    a->ret = FT_W32_ReadFile((FT_HANDLE)ULongToPtr(a->ftHandle), (LPVOID)ULongToPtr(a->lpBuffer), a->nBufferSize, (LPDWORD)ULongToPtr(a->lpdwBytesReturned), (LPOVERLAPPED)ULongToPtr(a->lpOverlapped));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_WriteFile(void *args) {
    struct prm_FT_W32_WriteFile *a = args;
    a->ret = FT_W32_WriteFile(a->ftHandle, a->lpBuffer, a->nBufferSize, a->lpdwBytesWritten, a->lpOverlapped);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_WriteFile(void *args) {
    struct p32_FT_W32_WriteFile *a = args;
    a->ret = FT_W32_WriteFile((FT_HANDLE)ULongToPtr(a->ftHandle), (LPVOID)ULongToPtr(a->lpBuffer), a->nBufferSize, (LPDWORD)ULongToPtr(a->lpdwBytesWritten), (LPOVERLAPPED)ULongToPtr(a->lpOverlapped));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_GetOverlappedResult(void *args) {
    struct prm_FT_W32_GetOverlappedResult *a = args;
    a->ret = FT_W32_GetOverlappedResult(a->ftHandle, a->lpOverlapped, a->lpdwBytesTransferred, a->bWait);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_GetOverlappedResult(void *args) {
    struct p32_FT_W32_GetOverlappedResult *a = args;
    a->ret = FT_W32_GetOverlappedResult((FT_HANDLE)ULongToPtr(a->ftHandle), (LPOVERLAPPED)ULongToPtr(a->lpOverlapped), (LPDWORD)ULongToPtr(a->lpdwBytesTransferred), a->bWait);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_EscapeCommFunction(void *args) {
    struct prm_FT_W32_EscapeCommFunction *a = args;
    a->ret = FT_W32_EscapeCommFunction(a->ftHandle, a->dwFunc);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_EscapeCommFunction(void *args) {
    struct p32_FT_W32_EscapeCommFunction *a = args;
    a->ret = FT_W32_EscapeCommFunction((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwFunc);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_GetCommModemStatus(void *args) {
    struct prm_FT_W32_GetCommModemStatus *a = args;
    a->ret = FT_W32_GetCommModemStatus(a->ftHandle, a->lpdwModemStatus);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_GetCommModemStatus(void *args) {
    struct p32_FT_W32_GetCommModemStatus *a = args;
    a->ret = FT_W32_GetCommModemStatus((FT_HANDLE)ULongToPtr(a->ftHandle), (LPDWORD)ULongToPtr(a->lpdwModemStatus));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_SetupComm(void *args) {
    struct prm_FT_W32_SetupComm *a = args;
    a->ret = FT_W32_SetupComm(a->ftHandle, a->dwReadBufferSize, a->dwWriteBufferSize);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_SetupComm(void *args) {
    struct p32_FT_W32_SetupComm *a = args;
    a->ret = FT_W32_SetupComm((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwReadBufferSize, a->dwWriteBufferSize);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_SetCommState(void *args) {
    struct prm_FT_W32_SetCommState *a = args;
    a->ret = FT_W32_SetCommState(a->ftHandle, a->lpftDcb);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_SetCommState(void *args) {
    struct p32_FT_W32_SetCommState *a = args;
    a->ret = FT_W32_SetCommState((FT_HANDLE)ULongToPtr(a->ftHandle), (LPFTDCB)ULongToPtr(a->lpftDcb));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_GetCommState(void *args) {
    struct prm_FT_W32_GetCommState *a = args;
    a->ret = FT_W32_GetCommState(a->ftHandle, a->lpftDcb);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_GetCommState(void *args) {
    struct p32_FT_W32_GetCommState *a = args;
    a->ret = FT_W32_GetCommState((FT_HANDLE)ULongToPtr(a->ftHandle), (LPFTDCB)ULongToPtr(a->lpftDcb));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_SetCommTimeouts(void *args) {
    struct prm_FT_W32_SetCommTimeouts *a = args;
    a->ret = FT_W32_SetCommTimeouts(a->ftHandle, a->pftTimeouts);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_SetCommTimeouts(void *args) {
    struct p32_FT_W32_SetCommTimeouts *a = args;
    a->ret = FT_W32_SetCommTimeouts((FT_HANDLE)ULongToPtr(a->ftHandle), (FTTIMEOUTS*)ULongToPtr(a->pftTimeouts));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_GetCommTimeouts(void *args) {
    struct prm_FT_W32_GetCommTimeouts *a = args;
    a->ret = FT_W32_GetCommTimeouts(a->ftHandle, a->pftTimeouts);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_GetCommTimeouts(void *args) {
    struct p32_FT_W32_GetCommTimeouts *a = args;
    a->ret = FT_W32_GetCommTimeouts((FT_HANDLE)ULongToPtr(a->ftHandle), (FTTIMEOUTS*)ULongToPtr(a->pftTimeouts));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_SetCommBreak(void *args) {
    struct prm_FT_W32_SetCommBreak *a = args;
    a->ret = FT_W32_SetCommBreak(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_SetCommBreak(void *args) {
    struct p32_FT_W32_SetCommBreak *a = args;
    a->ret = FT_W32_SetCommBreak((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_ClearCommBreak(void *args) {
    struct prm_FT_W32_ClearCommBreak *a = args;
    a->ret = FT_W32_ClearCommBreak(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_ClearCommBreak(void *args) {
    struct p32_FT_W32_ClearCommBreak *a = args;
    a->ret = FT_W32_ClearCommBreak((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_SetCommMask(void *args) {
    struct prm_FT_W32_SetCommMask *a = args;
    a->ret = FT_W32_SetCommMask(a->ftHandle, a->ulEventMask);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_SetCommMask(void *args) {
    struct p32_FT_W32_SetCommMask *a = args;
    a->ret = FT_W32_SetCommMask((FT_HANDLE)ULongToPtr(a->ftHandle), a->ulEventMask);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_WaitCommEvent(void *args) {
    struct prm_FT_W32_WaitCommEvent *a = args;
    a->ret = FT_W32_WaitCommEvent(a->ftHandle, a->pulEvent, a->lpOverlapped);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_WaitCommEvent(void *args) {
    struct p32_FT_W32_WaitCommEvent *a = args;
    a->ret = FT_W32_WaitCommEvent((FT_HANDLE)ULongToPtr(a->ftHandle), (PULONG)ULongToPtr(a->pulEvent), (LPOVERLAPPED)ULongToPtr(a->lpOverlapped));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_PurgeComm(void *args) {
    struct prm_FT_W32_PurgeComm *a = args;
    a->ret = FT_W32_PurgeComm(a->ftHandle, a->dwMask);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_PurgeComm(void *args) {
    struct p32_FT_W32_PurgeComm *a = args;
    a->ret = FT_W32_PurgeComm((FT_HANDLE)ULongToPtr(a->ftHandle), a->dwMask);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_ClearCommError(void *args) {
    struct prm_FT_W32_ClearCommError *a = args;
    a->ret = FT_W32_ClearCommError(a->ftHandle, a->lpdwErrors, a->lpftComstat);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_ClearCommError(void *args) {
    struct p32_FT_W32_ClearCommError *a = args;
    a->ret = FT_W32_ClearCommError((FT_HANDLE)ULongToPtr(a->ftHandle), (LPDWORD)ULongToPtr(a->lpdwErrors), (LPFTCOMSTAT)ULongToPtr(a->lpftComstat));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_W32_CancelIo(void *args) {
    struct prm_FT_W32_CancelIo *a = args;
    a->ret = FT_W32_CancelIo(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_W32_CancelIo(void *args) {
    struct p32_FT_W32_CancelIo *a = args;
    a->ret = FT_W32_CancelIo((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_ReadConfig(void *args) {
    struct prm_FT_EE_ReadConfig *a = args;
    a->ret = FT_EE_ReadConfig(a->ftHandle, a->ucAddress, a->pucValue);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_ReadConfig(void *args) {
    struct p32_FT_EE_ReadConfig *a = args;
    a->ret = FT_EE_ReadConfig((FT_HANDLE)ULongToPtr(a->ftHandle), a->ucAddress, (PUCHAR)ULongToPtr(a->pucValue));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_WriteConfig(void *args) {
    struct prm_FT_EE_WriteConfig *a = args;
    a->ret = FT_EE_WriteConfig(a->ftHandle, a->ucAddress, a->ucValue);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_WriteConfig(void *args) {
    struct p32_FT_EE_WriteConfig *a = args;
    a->ret = FT_EE_WriteConfig((FT_HANDLE)ULongToPtr(a->ftHandle), a->ucAddress, a->ucValue);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_EE_ReadECC(void *args) {
    struct prm_FT_EE_ReadECC *a = args;
    a->ret = FT_EE_ReadECC(a->ftHandle, a->ucOption, a->lpwValue);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_EE_ReadECC(void *args) {
    struct p32_FT_EE_ReadECC *a = args;
    a->ret = FT_EE_ReadECC((FT_HANDLE)ULongToPtr(a->ftHandle), a->ucOption, (LPWORD)ULongToPtr(a->lpwValue));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_GetQueueStatusEx(void *args) {
    struct prm_FT_GetQueueStatusEx *a = args;
    a->ret = FT_GetQueueStatusEx(a->ftHandle, a->dwRxBytes);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_GetQueueStatusEx(void *args) {
    struct p32_FT_GetQueueStatusEx *a = args;
    a->ret = FT_GetQueueStatusEx((FT_HANDLE)ULongToPtr(a->ftHandle), (DWORD*)ULongToPtr(a->dwRxBytes));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ComPortIdle(void *args) {
    struct prm_FT_ComPortIdle *a = args;
    a->ret = FT_ComPortIdle(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ComPortIdle(void *args) {
    struct p32_FT_ComPortIdle *a = args;
    a->ret = FT_ComPortIdle((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_ComPortCancelIdle(void *args) {
    struct prm_FT_ComPortCancelIdle *a = args;
    a->ret = FT_ComPortCancelIdle(a->ftHandle);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_ComPortCancelIdle(void *args) {
    struct p32_FT_ComPortCancelIdle *a = args;
    a->ret = FT_ComPortCancelIdle((FT_HANDLE)ULongToPtr(a->ftHandle));
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_VendorCmdGet(void *args) {
    struct prm_FT_VendorCmdGet *a = args;
    a->ret = FT_VendorCmdGet(a->ftHandle, a->Request, a->Buf, a->Len);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_VendorCmdGet(void *args) {
    struct p32_FT_VendorCmdGet *a = args;
    a->ret = FT_VendorCmdGet((FT_HANDLE)ULongToPtr(a->ftHandle), a->Request, (UCHAR*)ULongToPtr(a->Buf), a->Len);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_VendorCmdSet(void *args) {
    struct prm_FT_VendorCmdSet *a = args;
    a->ret = FT_VendorCmdSet(a->ftHandle, a->Request, a->Buf, a->Len);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_VendorCmdSet(void *args) {
    struct p32_FT_VendorCmdSet *a = args;
    a->ret = FT_VendorCmdSet((FT_HANDLE)ULongToPtr(a->ftHandle), a->Request, (UCHAR*)ULongToPtr(a->Buf), a->Len);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_VendorCmdGetEx(void *args) {
    struct prm_FT_VendorCmdGetEx *a = args;
    a->ret = FT_VendorCmdGetEx(a->ftHandle, a->wValue, a->Buf, a->Len);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_VendorCmdGetEx(void *args) {
    struct p32_FT_VendorCmdGetEx *a = args;
    a->ret = FT_VendorCmdGetEx((FT_HANDLE)ULongToPtr(a->ftHandle), a->wValue, (UCHAR*)ULongToPtr(a->Buf), a->Len);
    return STATUS_SUCCESS;
}

NTSTATUS wrap_FT_VendorCmdSetEx(void *args) {
    struct prm_FT_VendorCmdSetEx *a = args;
    a->ret = FT_VendorCmdSetEx(a->ftHandle, a->wValue, a->Buf, a->Len);
    return STATUS_SUCCESS;
}

NTSTATUS wow64_wrap_FT_VendorCmdSetEx(void *args) {
    struct p32_FT_VendorCmdSetEx *a = args;
    a->ret = FT_VendorCmdSetEx((FT_HANDLE)ULongToPtr(a->ftHandle), a->wValue, (UCHAR*)ULongToPtr(a->Buf), a->Len);
    return STATUS_SUCCESS;
}

const unixlib_entry_t __wine_unix_call_funcs[] =
{
    wrap_FT_SetVIDPID,
    wrap_FT_GetVIDPID,
    wrap_FT_CreateDeviceInfoList,
    wrap_FT_GetDeviceInfoList,
    wrap_FT_GetDeviceInfoDetail,
    wrap_FT_ListDevices,
    wrap_FT_Open,
    wrap_FT_OpenEx,
    wrap_FT_Close,
    wrap_FT_Read,
    wrap_FT_Write,
    wrap_FT_SetBaudRate,
    wrap_FT_SetDivisor,
    wrap_FT_SetDataCharacteristics,
    wrap_FT_SetTimeouts,
    wrap_FT_SetFlowControl,
    wrap_FT_SetDtr,
    wrap_FT_ClrDtr,
    wrap_FT_SetRts,
    wrap_FT_ClrRts,
    wrap_FT_GetModemStatus,
    wrap_FT_GetQueueStatus,
    wrap_FT_GetDeviceInfo,
    wrap_FT_GetDeviceLocId,
    wrap_FT_GetDriverVersion,
    wrap_FT_GetLibraryVersion,
    wrap_FT_GetComPortNumber,
    wrap_FT_GetStatus,
    wrap_FT_SetEventNotification,
    wrap_FT_SetChars,
    wrap_FT_SetBreakOn,
    wrap_FT_SetBreakOff,
    wrap_FT_Purge,
    wrap_FT_ResetDevice,
    wrap_FT_ResetPort,
    wrap_FT_CyclePort,
    wrap_FT_Rescan,
    wrap_FT_Reload,
    wrap_FT_SetResetPipeRetryCount,
    wrap_FT_StopInTask,
    wrap_FT_RestartInTask,
    wrap_FT_SetDeadmanTimeout,
    wrap_FT_IoCtl,
    wrap_FT_SetWaitMask,
    wrap_FT_WaitOnMask,
    wrap_FT_GetEventStatus,
    wrap_FT_ReadEE,
    wrap_FT_WriteEE,
    wrap_FT_EraseEE,
    wrap_FT_EE_Read,
    wrap_FT_EE_ReadEx,
    wrap_FT_EE_Program,
    wrap_FT_EE_ProgramEx,
    wrap_FT_EE_UASize,
    wrap_FT_EE_UARead,
    wrap_FT_EE_UAWrite,
    wrap_FT_EEPROM_Read,
    wrap_FT_EEPROM_Program,
    wrap_FT_SetLatencyTimer,
    wrap_FT_GetLatencyTimer,
    wrap_FT_SetBitMode,
    wrap_FT_GetBitMode,
    wrap_FT_SetUSBParameters,
    wrap_FT_W32_CreateFile,
    wrap_FT_W32_CloseHandle,
    wrap_FT_W32_ReadFile,
    wrap_FT_W32_WriteFile,
    wrap_FT_W32_GetOverlappedResult,
    wrap_FT_W32_EscapeCommFunction,
    wrap_FT_W32_GetCommModemStatus,
    wrap_FT_W32_SetupComm,
    wrap_FT_W32_SetCommState,
    wrap_FT_W32_GetCommState,
    wrap_FT_W32_SetCommTimeouts,
    wrap_FT_W32_GetCommTimeouts,
    wrap_FT_W32_SetCommBreak,
    wrap_FT_W32_ClearCommBreak,
    wrap_FT_W32_SetCommMask,
    wrap_FT_W32_WaitCommEvent,
    wrap_FT_W32_PurgeComm,
    wrap_FT_W32_ClearCommError,
    wrap_FT_W32_CancelIo,
    wrap_FT_EE_ReadConfig,
    wrap_FT_EE_WriteConfig,
    wrap_FT_EE_ReadECC,
    wrap_FT_GetQueueStatusEx,
    wrap_FT_ComPortIdle,
    wrap_FT_ComPortCancelIdle,
    wrap_FT_VendorCmdGet,
    wrap_FT_VendorCmdSet,
    wrap_FT_VendorCmdGetEx,
    wrap_FT_VendorCmdSetEx,
};

const unixlib_entry_t __wine_unix_call_wow64_funcs[] =
{
    wow64_wrap_FT_SetVIDPID,
    wow64_wrap_FT_GetVIDPID,
    wow64_wrap_FT_CreateDeviceInfoList,
    wow64_wrap_FT_GetDeviceInfoList,
    wow64_wrap_FT_GetDeviceInfoDetail,
    wow64_wrap_FT_ListDevices,
    wow64_wrap_FT_Open,
    wow64_wrap_FT_OpenEx,
    wow64_wrap_FT_Close,
    wow64_wrap_FT_Read,
    wow64_wrap_FT_Write,
    wow64_wrap_FT_SetBaudRate,
    wow64_wrap_FT_SetDivisor,
    wow64_wrap_FT_SetDataCharacteristics,
    wow64_wrap_FT_SetTimeouts,
    wow64_wrap_FT_SetFlowControl,
    wow64_wrap_FT_SetDtr,
    wow64_wrap_FT_ClrDtr,
    wow64_wrap_FT_SetRts,
    wow64_wrap_FT_ClrRts,
    wow64_wrap_FT_GetModemStatus,
    wow64_wrap_FT_GetQueueStatus,
    wow64_wrap_FT_GetDeviceInfo,
    wow64_wrap_FT_GetDeviceLocId,
    wow64_wrap_FT_GetDriverVersion,
    wow64_wrap_FT_GetLibraryVersion,
    wow64_wrap_FT_GetComPortNumber,
    wow64_wrap_FT_GetStatus,
    wow64_wrap_FT_SetEventNotification,
    wow64_wrap_FT_SetChars,
    wow64_wrap_FT_SetBreakOn,
    wow64_wrap_FT_SetBreakOff,
    wow64_wrap_FT_Purge,
    wow64_wrap_FT_ResetDevice,
    wow64_wrap_FT_ResetPort,
    wow64_wrap_FT_CyclePort,
    wow64_wrap_FT_Rescan,
    wow64_wrap_FT_Reload,
    wow64_wrap_FT_SetResetPipeRetryCount,
    wow64_wrap_FT_StopInTask,
    wow64_wrap_FT_RestartInTask,
    wow64_wrap_FT_SetDeadmanTimeout,
    wow64_wrap_FT_IoCtl,
    wow64_wrap_FT_SetWaitMask,
    wow64_wrap_FT_WaitOnMask,
    wow64_wrap_FT_GetEventStatus,
    wow64_wrap_FT_ReadEE,
    wow64_wrap_FT_WriteEE,
    wow64_wrap_FT_EraseEE,
    wow64_wrap_FT_EE_Read,
    wow64_wrap_FT_EE_ReadEx,
    wow64_wrap_FT_EE_Program,
    wow64_wrap_FT_EE_ProgramEx,
    wow64_wrap_FT_EE_UASize,
    wow64_wrap_FT_EE_UARead,
    wow64_wrap_FT_EE_UAWrite,
    wow64_wrap_FT_EEPROM_Read,
    wow64_wrap_FT_EEPROM_Program,
    wow64_wrap_FT_SetLatencyTimer,
    wow64_wrap_FT_GetLatencyTimer,
    wow64_wrap_FT_SetBitMode,
    wow64_wrap_FT_GetBitMode,
    wow64_wrap_FT_SetUSBParameters,
    wow64_wrap_FT_W32_CreateFile,
    wow64_wrap_FT_W32_CloseHandle,
    wow64_wrap_FT_W32_ReadFile,
    wow64_wrap_FT_W32_WriteFile,
    wow64_wrap_FT_W32_GetOverlappedResult,
    wow64_wrap_FT_W32_EscapeCommFunction,
    wow64_wrap_FT_W32_GetCommModemStatus,
    wow64_wrap_FT_W32_SetupComm,
    wow64_wrap_FT_W32_SetCommState,
    wow64_wrap_FT_W32_GetCommState,
    wow64_wrap_FT_W32_SetCommTimeouts,
    wow64_wrap_FT_W32_GetCommTimeouts,
    wow64_wrap_FT_W32_SetCommBreak,
    wow64_wrap_FT_W32_ClearCommBreak,
    wow64_wrap_FT_W32_SetCommMask,
    wow64_wrap_FT_W32_WaitCommEvent,
    wow64_wrap_FT_W32_PurgeComm,
    wow64_wrap_FT_W32_ClearCommError,
    wow64_wrap_FT_W32_CancelIo,
    wow64_wrap_FT_EE_ReadConfig,
    wow64_wrap_FT_EE_WriteConfig,
    wow64_wrap_FT_EE_ReadECC,
    wow64_wrap_FT_GetQueueStatusEx,
    wow64_wrap_FT_ComPortIdle,
    wow64_wrap_FT_ComPortCancelIdle,
    wow64_wrap_FT_VendorCmdGet,
    wow64_wrap_FT_VendorCmdSet,
    wow64_wrap_FT_VendorCmdGetEx,
    wow64_wrap_FT_VendorCmdSetEx,
};
