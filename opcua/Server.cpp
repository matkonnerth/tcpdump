#include "Server.h"
#include <iostream>
#include <vector>

using opcua::CreateMonitoredItemsRequest;
using opcua::Server;

void Server::createMonitoredItemsRequest(
    const UA_CreateMonitoredItemsRequest *req) {
  CreateMonitoredItemsRequest r{req};
  m_pendingCreateMonitoredsRequests.push_back(r);
}

std::optional<CreateMonitoredItemsRequest>
Server::getCreateMonitoredItemsRequest(UA_UInt32 requestHandle) {
  // get the request
  for (const auto &req : m_pendingCreateMonitoredsRequests) {
    if (req.raw()->requestHeader.requestHandle == requestHandle) {
      return req;
    }
  }
  return std::nullopt;
}

void Server::createMonitoredItemsResponse(
    const UA_CreateMonitoredItemsResponse *resp) {
  auto req = getCreateMonitoredItemsRequest(resp->responseHeader.requestHandle);
  if (!req) {
    std::cout << "request not found"
              << "\n";
    return;
  }
  handleCreateMonitoredItems(*req, *resp);
}

void Server::handleCreateMonitoredItems(
    const CreateMonitoredItemsRequest &req,
    const UA_CreateMonitoredItemsResponse &resp) {

  // TODO: check statuscodes of response, resultsSize must be the same as requestSize ...
  for (auto i = 0u; i < req.raw()->itemsToCreateSize; ++i) {
    MonitoredItem m{req.raw()->subscriptionId,
                    req.raw()->itemsToCreate[i].itemToMonitor.nodeId, resp.results[i].monitoredItemId};
    m_monitoredItems.push_back(m);
  }

  printMonitoredItems();
}

void Server::printMonitoredItems() {
  std::cout << "\nMonitoredItems: " << "\n";
  for (const auto &m : m_monitoredItems) {
    std::cout << m;
  }
}

void Server::deleteMonitoredItemsRequest(){};
