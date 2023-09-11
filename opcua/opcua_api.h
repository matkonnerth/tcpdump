#pragma once
#include <open62541/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void opcua_process_CreateMonitoredItemsRequest(
    const UA_CreateMonitoredItemsRequest *);
void opcua_process_CreateMonitoredItemsResponse(
    const UA_CreateMonitoredItemsResponse *);
void opcua_process_DeleteMonitoredItemsRequest(
    const UA_DeleteMonitoredItemsRequest *);
void opcua_process_DeleteMonitoredItemsResponse(
    const UA_DeleteMonitoredItemsResponse *);
void opcua_process_ActivateSessionRequest(const UA_ActivateSessionRequest *);
void opcua_process_ActivateSessionResponse(const UA_ActivateSessionResponse *);
void opcua_process_CreateSessionRequest(const UA_CreateSessionRequest*);
void opcua_process_CreateSessionResponse(const UA_CreateSessionResponse*);
#ifdef __cplusplus
}
#endif