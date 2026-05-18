/** 
 @file  address.h
 @brief ENet Address structure
*/
#ifndef __ENET_ADDRESS_H__
#define __ENET_ADDRESS_H__

#include "enet/types.h"

/**
 * Portable internet address structure. 
 *
 * The host must be specified in network byte-order, and the port must be in host 
 * byte-order. The constant ENET_HOST_ANY may be used to specify the default 
 * server host. The constant ENET_HOST_BROADCAST may be used to specify the
 * broadcast address (255.255.255.255).  This makes sense for enet_host_connect,
 * but not for enet_host_create.  Once a server responds to a broadcast, the
 * address is updated from ENET_HOST_BROADCAST to the server's actual IP address.
 */
 typedef struct _ENetAddress
 {
    enet_uint32 host;
    enet_uint16 port;
 } ENetAddress;

 #endif /* __ENET_ADDRESS_H__ */

