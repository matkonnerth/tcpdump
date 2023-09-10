#pragma once
#include <Types.h>
#include <optional>
#include <vector>

namespace opcua {
class Server {
public:
  void createMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest *);
  void createMonitoredItemsResponse(const UA_CreateMonitoredItemsResponse *);

  void deleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest *);
  void deleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse *);

private:
  std::optional<CreateMonitoredItemsRequest>
  getCreateMonitoredItemsRequest(UA_UInt32 requestHandle);
  std::optional<DeleteMonitoredItemsRequest>
  getDeleteMonitoredItemsRequest(UA_UInt32 requestHandle);
  void handleCreateMonitoredItems(const CreateMonitoredItemsRequest&, const UA_CreateMonitoredItemsResponse&);
  void handleDeleteMonitoredItems(const DeleteMonitoredItemsRequest &,
                                  const UA_DeleteMonitoredItemsResponse &);
  void printMonitoredItems();
  std::vector<CreateMonitoredItemsRequest> m_pendingCreateMonitoredsRequests{};
  std::vector<DeleteMonitoredItemsRequest> m_pendingDeleteMonitoredsRequests{};
  std::vector<MonitoredItem> m_monitoredItems{};
};



}; // namespace opcua