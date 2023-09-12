#include "Server.h"
#include <vector>
#include <algorithm>

using opcua::CreateMonitoredItemsRequest;
using opcua::DeleteMonitoredItemsRequest;
using opcua::ActivateSessionRequest;
using opcua::CreateSessionRequest;
using opcua::Server;

void Server::createMonitoredItemsRequest(
    const UA_CreateMonitoredItemsRequest *req) {
  CreateMonitoredItemsRequest r{req};
  m_pendingCreateMonitoredItemsRequests.add(r);

  m_logger.log() << "createMonitoredItemsRequest" << std::endl;

}

void Server::createMonitoredItemsResponse(
    const UA_CreateMonitoredItemsResponse *resp) {
  auto req = m_pendingCreateMonitoredItemsRequests.get(resp->responseHeader.requestHandle);
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

    if (resp.responseHeader.serviceResult != UA_STATUSCODE_GOOD)
    {
        m_logger.log() << "ERROR" << std::endl;
    }

  // TODO: check statuscodes of response, resultsSize must be the same as requestSize ...
  for (auto i = 0u; i < req.raw()->itemsToCreateSize; ++i) {
    MonitoredItem m{req.raw()->subscriptionId,
                    req.raw()->itemsToCreate[i].itemToMonitor.nodeId, resp.results[i].monitoredItemId};
    m_monitoredItems.push_back(m);
    if (resp.results[i].statusCode != UA_STATUSCODE_GOOD)
    {
        m_logger.log() << "ERROR" << std::endl;
    }
  }

  printMonitoredItems();
}

void Server::printMonitoredItems() {
  m_logger.log() << "MonitoredItems: " << std::endl;
  for (const auto &m : m_monitoredItems) {
    m_logger.log() << m << std::endl;
  }
}

void Server::deleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest *req)
{
  DeleteMonitoredItemsRequest r{req};
  m_pendingDeleteMonitoredItemsRequests.add(r);
  m_logger.log() << "deleteMonitoredItemsRequest" << std::endl;
}
void Server::deleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse *resp)
{
  auto req = m_pendingDeleteMonitoredItemsRequests.get(resp->responseHeader.requestHandle);
  if (!req) {
    m_logger.log() << "request not found" << std::endl;
    return;
  }
  handleDeleteMonitoredItems(*req, *resp);
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

void Server::activateSessionRequest(
    const UA_ActivateSessionRequest *req) {
  ActivateSessionRequest r{req};
  m_pendingActivateSessionRequests.add(r);
}

void Server::activateSessionResponse(
    const UA_ActivateSessionResponse *resp) {
  auto req = m_pendingActivateSessionRequests.get(resp->responseHeader.requestHandle);
  if (!req) {
    m_logger.log() << "request not found" << std::endl;
    return;
  }
  handleActivateSession(*req, *resp);
}

void Server::handleActivateSession(
    const ActivateSessionRequest &req,
    const UA_ActivateSessionResponse &resp) {

    m_logger.log() << "Activate Session" << std::endl;
    m_logger.log() << "locale ids: " << std::endl;

  // TODO: check statuscodes of response, resultsSize must be the same as
  // requestSize ...
  for(auto i=0u; i<req.raw()->localeIdsSize; ++i)
  {
    std::string id{(char*)req.raw()->localeIds[i].data, req.raw()->localeIds[i].length};
    m_logger.log() << id << ", ";
  }
  m_logger.log() << std::endl;
  
}

void Server::createSessionRequest(
    const UA_CreateSessionRequest *req) {
  CreateSessionRequest r{req};
  m_pendingCreateSessionRequests.add(r);
}

void Server::createSessionResponse(
    const UA_CreateSessionResponse *resp) {
  auto req = m_pendingCreateSessionRequests.get(resp->responseHeader.requestHandle);
  if (!req) {
    m_logger.log() << "request not found" << std::endl;
    return;
  }
  handleCreateSession(*req, *resp);
}

void Server::handleCreateSession(const CreateSessionRequest& req,
                                  const UA_CreateSessionResponse& resp)
{
  m_logger.log() << "createSessionRequest" << std::endl;
  std::string appUri{(char*)req.raw()->clientDescription.applicationUri.data, req.raw()->clientDescription.applicationUri.length};
  m_logger.log() << "applicationUri: " << appUri << std::endl;
  
  auto sessionId = resp.sessionId;
  UA_String sessionIdString;
  UA_String_init(&sessionIdString);
  UA_NodeId_print(&sessionId, &sessionIdString);
  std::string sid{(char*)sessionIdString.data, sessionIdString.length};
  m_logger.log() << "sessionId: " << sid << std::endl;
  UA_String_clear(&sessionIdString);
}

void Server::readRequest(const UA_ReadRequest* req)
{
    m_pendingReadRequests.add(req);
}

void Server::readResponse(const UA_ReadResponse* resp)
{
    auto req = m_pendingReadRequests.get(resp->responseHeader.requestHandle);
    if (!req) {
        m_logger.log() << "request not found" << std::endl;
        return;
    }
    handleReadRequest(*req, *resp);
}

void Server::handleReadRequest(const ReadRequest& req,
    const UA_ReadResponse& resp)
{
    m_logger.log() << "read request" << std::endl;
    for (auto i = 0u; i < req.raw()->nodesToReadSize; ++i)
    {
        UA_String id;
        UA_String_init(&id);
        UA_NodeId_print(&req.raw()->nodesToRead[i].nodeId, &id);
        std::string sid{ (char*)id.data, id.length };
        m_logger.log() << "nodeId: " << sid << std::endl;
        UA_String_clear(&id);        
    }
}