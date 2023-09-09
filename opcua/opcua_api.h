#pragma once
#include <stdint.h>
#include <open62541/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void opcua_process_CreateMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest*);
void opcua_process_CreateMonitoredItemsResponse(const UA_CreateMonitoredItemsResponse*);
void opcua_process_DeleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest*);
void opcua_process_DeleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse*);
#ifdef __cplusplus
}
#endif