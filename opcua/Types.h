#pragma once
#include <iostream>
#include <open62541/types.h>

namespace opcua {

class MonitoredItem {
public:
  MonitoredItem(UA_UInt32 subscriptionId, const UA_NodeId &id,
                UA_UInt32 monitoredItemId)
      : m_subscriptionId{subscriptionId}, m_monitoredItemId{monitoredItemId} {
    UA_NodeId_copy(&id, &m_nodeId);
  }

  MonitoredItem(const MonitoredItem &other)
      : m_subscriptionId{other.m_subscriptionId}, m_monitoredItemId{
                                                      other.m_monitoredItemId} {
    UA_NodeId_copy(&other.m_nodeId, &m_nodeId);
  }

  MonitoredItem &operator=(const MonitoredItem &other) {
    UA_NodeId_clear(&m_nodeId);
    m_subscriptionId = other.m_subscriptionId;
    m_monitoredItemId = other.m_monitoredItemId;
    UA_NodeId_copy(&other.m_nodeId, &m_nodeId);
    return *this;
  }

  ~MonitoredItem() { UA_NodeId_clear(&m_nodeId); }

  friend std::ostream &operator<<(std::ostream &os, const MonitoredItem &m) {
    UA_String s;
    UA_String_init(&s);
    UA_NodeId_print(&m.m_nodeId, &s);

    os << "MonitoredItem: ";
    os.write((char *)s.data, s.length);
    os << ", ";
    os << "SubscriptionId: " << std::to_string(m.m_subscriptionId) << ", ";
    os << "ItemId: " << std::to_string(m.m_monitoredItemId) << "\n";
    UA_String_clear(&s);
    return os;
  }

private:
  UA_UInt32 m_subscriptionId;
  UA_NodeId m_nodeId;
  UA_UInt32 m_monitoredItemId;
};

class CreateMonitoredItemsRequest {
public:
  CreateMonitoredItemsRequest(const UA_CreateMonitoredItemsRequest *raw) {
    UA_CreateMonitoredItemsRequest_copy(raw, &m_raw);
  }
  ~CreateMonitoredItemsRequest() {
    UA_CreateMonitoredItemsRequest_clear(&m_raw);
  }

  const UA_CreateMonitoredItemsRequest *raw() const { return &m_raw; }

  CreateMonitoredItemsRequest(const CreateMonitoredItemsRequest &other) {
    UA_CreateMonitoredItemsRequest_copy(&other.m_raw, &m_raw);
  }

  CreateMonitoredItemsRequest &
  operator=(const CreateMonitoredItemsRequest &other) {
    UA_CreateMonitoredItemsRequest_clear(&m_raw);
    UA_CreateMonitoredItemsRequest_copy(&other.m_raw, &m_raw);
    return *this;
  }

private:
  UA_CreateMonitoredItemsRequest m_raw;
};
} // namespace opcua