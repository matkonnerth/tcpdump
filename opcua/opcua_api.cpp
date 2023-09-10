#include "opcua_api.h"
#include <iostream>
#include "Server.h"

opcua::Server myServer{};

void opcua_process_CreateMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest* req)
{
    myServer.createMonitoredItemsRequest(req);
};

void opcua_process_CreateMonitoredItemsResponse(const UA_CreateMonitoredItemsResponse* resp)
{
    myServer.createMonitoredItemsResponse(resp);
};

void opcua_process_DeleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest* req)
{
  myServer.deleteMonitoredItemsRequest(req);
}

void opcua_process_DeleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse* resp)
{
  myServer.deleteMonitoredItemsResponse(resp);
}

void opcua_process_ActivateSessionRequest(const UA_ActivateSessionRequest *req)
{
  myServer.activateSessionRequest(req);
}
void opcua_process_ActivateSessionResponse(const UA_ActivateSessionResponse *resp)
{
  myServer.activateSessionResponse(resp);
}