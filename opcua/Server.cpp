#include "Server.h"
#include <iostream>
#include <vector>
#include <algorithm>

using opcua::CreateMonitoredItemsRequest;
using opcua::DeleteMonitoredItemsRequest;
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

void Server::deleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest *req)
{
  DeleteMonitoredItemsRequest r{req};
  m_pendingDeleteMonitoredsRequests.push_back(r);
}
void Server::deleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse *resp)
{
  auto req = getDeleteMonitoredItemsRequest(resp->responseHeader.requestHandle);
  if (!req) {
    std::cout << "request not found"
              << "\n";
    return;
  }
  handleDeleteMonitoredItems(*req, *resp);
}

std::optional<DeleteMonitoredItemsRequest>
Server::getDeleteMonitoredItemsRequest(UA_UInt32 requestHandle) {
  // get the request
  for (const auto &req : m_pendingDeleteMonitoredsRequests) {
    if (req.raw()->requestHeader.requestHandle == requestHandle) {
      return req;
    }
  }
  return std::nullopt;
}

void Server::handleDeleteMonitoredItems(
    const DeleteMonitoredItemsRequest &req,
    const UA_DeleteMonitoredItemsResponse &resp) {

  // TODO: check statuscodes of response, resultsSize must be the same as
  // requestSize ...
  for (auto i = 0u; i < req.raw()->monitoredItemIdsSize; ++i) {
    auto idToErase = req.raw()->monitoredItemIds[i];
    m_monitoredItems.erase(std::remove_if(m_monitoredItems.begin(), m_monitoredItems.end(),
                           [&idToErase](const MonitoredItem& i) {
                             return i.Id()==idToErase;
                           }),
            m_monitoredItems.end());
  }

  printMonitoredItems();
}