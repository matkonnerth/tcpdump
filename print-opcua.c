/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code
 * distributions retain the above copyright notice and this paragraph
 * in its entirety, and (2) distributions including binary code include
 * the above copyright notice and this paragraph in its entirety in
 * the documentation or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND
 * WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT
 * LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE.
 */

/* \summary: Hypertext Transfer Protocol (HTTP) printer */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "netdissect-stdinc.h"

#include "extract.h"
#include "netdissect.h"
#include <assert.h>
#include <opcua/opcua_api.h>
#include <open62541/types.h>
#include <stdlib.h>

struct opcua_message_header {
  uint32_t messageType; // ascii
  uint32_t size;
};

static void handleOpcUaService(netdissect_options *ndo, const u_char *pptr,
                               u_int len) {
  // opcua service
  // type id : Expanded NodeId
  pptr += 1; // numeric
  pptr += 1; // nsidx
  uint16_t idNumeric = GET_LE_U_2(pptr);
  ND_PRINT(", service.identifier.numeric: %u", idNumeric);
  pptr += 2; // identifier numeric

  UA_ByteString bs;
  bs.data = pptr;
  bs.length = len;

  switch (idNumeric) {
  case 452:
  {
      UA_CloseSecureChannelRequest req;
      UA_CloseSecureChannelRequest_init(&req);
      UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_CLOSESECURECHANNELREQUEST],
          NULL);
      //opcua_process_ReadRequest(&req);
      UA_CloseSecureChannelRequest_clear(&req);
  }
  break;
  case 631:
    {
        UA_ReadRequest req;
        UA_ReadRequest_init(&req);
        UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_READREQUEST],
            NULL);
        opcua_process_ReadRequest(&req);
        UA_ReadRequest_clear(&req);
    }
    break;
  case 634:
    {
        UA_ReadResponse req;
        UA_ReadResponse_init(&req);
        UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_READRESPONSE],
            NULL);
        opcua_process_ReadResponse(&req);
        UA_ReadResponse_clear(&req);
    }
    break;
  case 751: {
    UA_CreateMonitoredItemsRequest req;
    UA_CreateMonitoredItemsRequest_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_CREATEMONITOREDITEMSREQUEST],
                    NULL);
    opcua_process_CreateMonitoredItemsRequest(&req);
    UA_CreateMonitoredItemsRequest_clear(&req);
  } break;
  case 754: {
    UA_CreateMonitoredItemsResponse req;
    UA_CreateMonitoredItemsResponse_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_CREATEMONITOREDITEMSRESPONSE],
                    NULL);
    opcua_process_CreateMonitoredItemsResponse(&req);
    UA_CreateMonitoredItemsResponse_clear(&req);
  } break;
  case 781: {
    UA_DeleteMonitoredItemsRequest req;
    UA_DeleteMonitoredItemsRequest_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_DELETEMONITOREDITEMSREQUEST],
                    NULL);
    opcua_process_DeleteMonitoredItemsRequest(&req);
    UA_DeleteMonitoredItemsRequest_clear(&req);
  } break;
  case 784: {
    UA_DeleteMonitoredItemsResponse req;
    UA_DeleteMonitoredItemsResponse_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_DELETEMONITOREDITEMSRESPONSE],
                    NULL);
    opcua_process_DeleteMonitoredItemsResponse(&req);
    UA_DeleteMonitoredItemsResponse_clear(&req);
  } break;
  case 467: {
    UA_ActivateSessionRequest req;
    UA_ActivateSessionRequest_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_ACTIVATESESSIONREQUEST],
                    NULL);
    opcua_process_ActivateSessionRequest(&req);
    UA_ActivateSessionRequest_clear(&req);
  } break;
  case 470: {
    UA_ActivateSessionResponse req;
    UA_ActivateSessionResponse_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_ACTIVATESESSIONRESPONSE],
                    NULL);
    opcua_process_ActivateSessionResponse(&req);
    UA_ActivateSessionResponse_clear(&req);
  } break;
  case 461: {
    UA_CreateSessionRequest req;
    UA_CreateSessionRequest_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_CREATESESSIONREQUEST],
                    NULL);
    opcua_process_CreateSessionRequest(&req);
    UA_CreateSessionRequest_clear(&req);
  } break;
  case 464: {
    UA_CreateSessionResponse req;
    UA_CreateSessionResponse_init(&req);
    UA_decodeBinary(&bs, &req, &UA_TYPES[UA_TYPES_CREATESESSIONRESPONSE],
                    NULL);
    opcua_process_CreateSessionResponse(&req);
    UA_CreateSessionResponse_clear(&req);
  } break;
  default:
    ND_PRINT(", UNHANDLED REQUEST");
    break;
  }
}

void opcua_print(netdissect_options *ndo, const u_char *pptr, u_int len) {
  ndo->ndo_protocol = "opcua";
  //ND_PRINT("opcua, size: %u", len);

  

  int actLength = 0;

  while (actLength < len)
  {
      const u_char* actPtr = pptr + actLength;
      struct opcua_message_header hdr;
      ND_PRINT("MSG: %c%c%c%c", actPtr[0], actPtr[1], actPtr[2], actPtr[3]);
      if (actPtr[0] != 77)
      {
          return;
      }
      if (actPtr[1] != 83)
      {
          return;
      }

      if (actPtr[2] != 71)
      {
          return;
      }

      if (actPtr[3] != 70)
      {
          return;
      }



      actPtr += 4; // messageType
      hdr.size = GET_LE_U_4(actPtr);
      ND_PRINT(", size %u", hdr.size);

      actPtr += 4; // messageSize
      actPtr += 4; // secure channelid
      actPtr += 4; // security token id
      actPtr += 4; // security sequence number
      actPtr += 4; // security request id

      handleOpcUaService(ndo, actPtr, hdr.size);
      actLength += hdr.size;
  }

  
}