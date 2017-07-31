

#include <ntddk.h>
#include <wdf.h>
#include <initguid.h>

#include "device.h"
#include "queue.h"
#include "trace.h"

EXTERN_C_START


DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD ds64bEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP ds64bEvtDriverContextCleanup;

EXTERN_C_END
