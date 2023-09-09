#include "opcua_api.h"
#include <iostream>

void opcua_process_CreateMonitoredItemsRequest(opcua_nodeId* ids, int size)
{
    std::cout << "createMonitoredItemsRequest" << "\n";
};

void opcua_process_DeleteMonitoredItemsRequest(uint32_t* ids, int idsSize)
{
  std::cout << "deleteMonitoredItemsRequest" << "\n";
}