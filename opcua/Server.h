#pragma once
#include <Types.h>
#include <optional>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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

template <typename T>
class RequestContainer
{
public:
  void add(const T& request)
  {
    m_requests.push_back(request);
  }

  std::optional<T> get(UA_UInt32 requestHandle)
  {
    // get the request
    for (const auto &req : m_requests) {
      if (req.raw()->requestHeader.requestHandle == requestHandle) {
        return req;
      }
    }
    return std::nullopt;
  }


private:
  std::vector<T> m_requests{};
};

class Server {
public:
  void createMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest *);
  void createMonitoredItemsResponse(const UA_CreateMonitoredItemsResponse *);

  void deleteMonitoredItemsRequest(const UA_DeleteMonitoredItemsRequest *);
  void deleteMonitoredItemsResponse(const UA_DeleteMonitoredItemsResponse *);

  void createSessionRequest(const UA_CreateSessionRequest *);
  void createSessionResponse(const UA_CreateSessionResponse *);

  void activateSessionRequest(const UA_ActivateSessionRequest *);
  void activateSessionResponse(const UA_ActivateSessionResponse *);

  void readRequest(const UA_ReadRequest*);
  void readResponse(const UA_ReadResponse*);

private:
  Logger m_logger{};
  
  void handleCreateMonitoredItems(const CreateMonitoredItemsRequest&, const UA_CreateMonitoredItemsResponse&);
  void handleDeleteMonitoredItems(const DeleteMonitoredItemsRequest &,
                                  const UA_DeleteMonitoredItemsResponse &);
  void handleActivateSession(const ActivateSessionRequest &,
                                  const UA_ActivateSessionResponse &);
  void handleCreateSession(const CreateSessionRequest &,
                                  const UA_CreateSessionResponse &);
  void handleReadRequest(const ReadRequest&,
      const UA_ReadResponse&);
  void printMonitoredItems();
  RequestContainer<CreateMonitoredItemsRequest> m_pendingCreateMonitoredItemsRequests{};
  RequestContainer<DeleteMonitoredItemsRequest> m_pendingDeleteMonitoredItemsRequests{};
  RequestContainer<ActivateSessionRequest> m_pendingActivateSessionRequests{};
  RequestContainer<CreateSessionRequest> m_pendingCreateSessionRequests{};
  RequestContainer<ReadRequest> m_pendingReadRequests{};
  std::vector<MonitoredItem> m_monitoredItems{};
};
}; // namespace opcua