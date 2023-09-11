#pragma once
#include <Types.h>
#include <optional>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace opcua {

class Logger
{
public:
  Logger()
  {
    logfile.open("./opcua.log", std::ios::out);
  }

  std::ofstream& log()
  {
    return logfile;
  }

  ~Logger()
  {
    logfile.close();
  }

private:
  std::ofstream logfile;
};

class Server {
public:
  void createMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest *);
  void createMonitoredItemsResponse(const UA_CreateMonitoredItemsResponse *);

  void deleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest *);
  void deleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse *);

  void activateSessionRequest(const UA_ActivateSessionRequest *);
  void activateSessionResponse(const UA_ActivateSessionResponse *);

private:
  Logger m_logger{};
  std::optional<CreateMonitoredItemsRequest>
  getCreateMonitoredItemsRequest(UA_UInt32 requestHandle);
  std::optional<DeleteMonitoredItemsRequest>
  getDeleteMonitoredItemsRequest(UA_UInt32 requestHandle);
  std::optional<ActivateSessionRequest>
  getActivateSessionRequest(UA_UInt32 requestHandle);
  void handleCreateMonitoredItems(const CreateMonitoredItemsRequest&, const UA_CreateMonitoredItemsResponse&);
  void handleDeleteMonitoredItems(const DeleteMonitoredItemsRequest &,
                                  const UA_DeleteMonitoredItemsResponse &);
  void handleActivateSession(const ActivateSessionRequest &,
                                  const UA_ActivateSessionResponse &);
  void printMonitoredItems();
  std::vector<CreateMonitoredItemsRequest> m_pendingCreateMonitoredsRequests{};
  std::vector<DeleteMonitoredItemsRequest> m_pendingDeleteMonitoredsRequests{};
  std::vector<ActivateSessionRequest> m_pendingActivateSessionRequests{};
  std::vector<MonitoredItem> m_monitoredItems{};
};
}; // namespace opcua