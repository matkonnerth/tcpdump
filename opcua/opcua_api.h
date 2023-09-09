#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct opcua_string
{
  uint32_t length;
  char* data;
};

struct opcua_nodeId
{
  uint8_t encoding; //0..numeric, 3..string
  uint16_t nsIx;
  union
  {
    uint16_t numeric;
    struct opcua_string string;
  }id;
};

void opcua_process_CreateMonitoredItemsRequest(struct opcua_nodeId* ids, int idsSize);
void opcua_process_DeleteMonitoredItemsRequest(uint32_t* ids, int idsSize);
#ifdef __cplusplus
}
#endif