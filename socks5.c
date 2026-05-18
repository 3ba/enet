/**
 @file  socks5.c
 @brief ENet SOCKS5 protocol functions
*/
#include <string.h>
#define ENET_BUILDING_LIB 1
#include "enet/types.h"
#include "enet/address.h"
#include "enet/socks5.h"

static size_t
enet_socks5_copy_credential (enet_uint8 * destination, const char * source)
{
    size_t length = 0;

    if (source == NULL)
      return 0;

    length = strlen (source);
    if (length > 255)
      length = 255;

    if (length > 0)
      memcpy (destination, source, length);

    return length;
}

void
enet_socks5_set_address (ENetSocks5ProxyInfo * proxyInfo, ENetAddress address)
{
    if (proxyInfo == NULL)
      return;

    proxyInfo -> address = address;
}

void
enet_socks5_set_auth (ENetSocks5ProxyInfo * proxyInfo, const char * username, const char * password)
{
    if (proxyInfo == NULL)
      return;

    memset (proxyInfo -> username, 0, sizeof (proxyInfo -> username));
    memset (proxyInfo -> password, 0, sizeof (proxyInfo -> password));

    enet_socks5_copy_credential (proxyInfo -> username, username);
    enet_socks5_copy_credential (proxyInfo -> password, password);
}
