

#include "public.h"

EXTERN_C_START


typedef struct _DEVICE_CONTEXT
{
    ULONG PrivateDeviceData;  

} DEVICE_CONTEXT, *PDEVICE_CONTEXT;


WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)


NTSTATUS
ds64bCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    );

EXTERN_C_END
