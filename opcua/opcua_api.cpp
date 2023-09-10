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
  std::cout << "deleteMonitoredItemsRequest" << "\n";
}

void opcua_process_DeleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse* req)
{
  std::cout << "deleteMonitoredItemsRequest" << "\n";
}