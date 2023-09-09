#include "opcua_api.h"
#include <iostream>

void opcua_process_CreateMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest* req)
{
    std::cout << "createMonitoredItemsRequest" << "\n";
};

void opcua_process_CreateMonitoredItemsResponse(const UA_CreateMonitoredItemsResponse* resp)
{
    std::cout << "createMonitoredItemsRequest" << "\n";
};

void opcua_process_DeleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest* req)
{
  std::cout << "deleteMonitoredItemsRequest" << "\n";
}

void opcua_process_DeleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse* req)
{
  std::cout << "deleteMonitoredItemsRequest" << "\n";
}