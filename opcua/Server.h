#pragma once
#include <Types.h>
#include <optional>
#include <vector>

namespace opcua {
class Server {
public:
  void createMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest *);
  void createMonitoredItemsResponse(const UA_CreateMonitoredItemsResponse *);

  void deleteMonitoredItemsRequest();
  void deleteMonitoredItemsResponse();

private:
  std::optional<CreateMonitoredItemsRequest>
  getCreateMonitoredItemsRequest(UA_UInt32 requestHandle);
  void handleCreateMonitoredItems(const CreateMonitoredItemsRequest&, const UA_CreateMonitoredItemsResponse&);
  void printMonitoredItems();
  std::vector<CreateMonitoredItemsRequest> m_pendingCreateMonitoredsRequests{};
  std::vector<MonitoredItem> m_monitoredItems{};
};



}; // namespace opcua