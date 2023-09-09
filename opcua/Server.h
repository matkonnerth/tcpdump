#pragma once


namespace opcua
{
class Server
{
public:
    void createSession();
    void closeSession();
    void createSubscription();
    void deleteSubscription();
    void createMonitoredItems();
    void deleteMonitoredItems();
};

};