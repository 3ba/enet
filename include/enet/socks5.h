/** 
 @file  socks5.h
 @brief ENet SOCKS5 protocol extension
*/
#ifndef __ENET_SOCKS5_H__
#define __ENET_SOCKS5_H__

#include "enet/types.h"
#include "enet/address.h"

enum
{
   ENET_SOCKS5_VERSION_NUMBER = 5,
   ENET_SOCKS5_USER_PASSWORD_VERSION_NUMBER = 1
};

typedef enum _ENetSocks5State
{
   ENET_SOCKS5_STATE_DISCONNECTED = 0,
   ENET_SOCKS5_STATE_SEND_GREETING_REQUEST = 1,
   ENET_SOCKS5_STATE_RECEIVE_GREETING_RESPONSE = 2,
   ENET_SOCKS5_STATE_SEND_AUTH_REQUEST = 3,
   ENET_SOCKS5_STATE_RECEIVE_AUTH_RESPONSE = 4,
   ENET_SOCKS5_STATE_SEND_CONNECT_REQUEST = 5,
   ENET_SOCKS5_STATE_RECEIVE_CONNECT_RESPONSE = 6,
   ENET_SOCKS5_STATE_CONNECTED = 7,
   ENET_SOCKS5_STATE_VERSION_MISMATCH = 8,
   ENET_SOCKS5_STATE_AUTH_METHOD_NOT_SUPPORTED = 9,
   ENET_SOCKS5_STATE_AUTH_FAILURE = 10,
   ENET_SOCKS5_STATE_ADDRESS_TYPE_NOT_SUPPORTED = 11,
   ENET_SOCKS5_STATE_CONNECT_FAILURE = 12
} ENetSocks5State;

typedef enum _ENetSocks5AuthMethod
{
   ENET_SOCKS5_AUTH_METHOD_NONE = 0,
   ENET_SOCKS5_AUTH_METHOD_GSSAPI = 1,
   ENET_SOCKS5_AUTH_METHOD_USERNAME_PASSWORD = 2
} ENetSocks5AuthMethod;

typedef enum _ENetSocks5Command
{
   ENET_SOCKS5_COMMAND_CONNECT = 1,
   ENET_SOCKS5_COMMAND_BIND = 2,
   ENET_SOCKS5_COMMAND_UDP_ASSOCIATE = 3
} ENetSocks5Command;

typedef enum _ENetSocks5AddressType
{
   ENET_SOCKS5_ADDRESS_TYPE_IPV4 = 1,
   ENET_SOCKS5_ADDRESS_TYPE_DOMAINNAME = 3,
   ENET_SOCKS5_ADDRESS_TYPE_IPV6 = 4
} ENetSocks5AddressType;

#ifdef _MSC_VER
#pragma pack(push, 1)
#define ENET_PACKED
#elif defined(__GNUC__) || defined(__clang__)
#define ENET_PACKED __attribute__ ((packed))
#else
#define ENET_PACKED
#endif

typedef struct _ENetSocks5Ipv4Address
{
   enet_uint32 host;
   enet_uint16 port; /**< port in network byte order */
} ENET_PACKED ENetSocks5Ipv4Address;

typedef struct _ENetSocks5GreetingRequest
{
   enet_uint8 version;
   enet_uint8 nmethods;
   enet_uint8 methods [255];
} ENET_PACKED ENetSocks5GreetingRequest;

typedef struct _ENetSocks5GreetingResponse
{
   enet_uint8 version;
   enet_uint8 method;
} ENET_PACKED ENetSocks5GreetingResponse;

typedef struct _ENetSocks5AuthUserPasswordRequest
{
   enet_uint8 version;
   enet_uint8 usernameLength;
   enet_uint8 username [255];
   enet_uint8 passwordLength;
   enet_uint8 password [255];
} ENET_PACKED ENetSocks5AuthUserPasswordRequest;

typedef struct _ENetSocks5AuthUserPasswordResponse
{
   enet_uint8 authVersion;
   enet_uint8 status;
} ENET_PACKED ENetSocks5AuthUserPasswordResponse;

typedef struct _ENetSocks5ConnectRequest
{
   enet_uint8 version;
   enet_uint8 command;
   enet_uint8 reserved;
   enet_uint8 addressType;
   ENetSocks5Ipv4Address address;
} ENET_PACKED ENetSocks5ConnectRequest;

typedef struct _ENetSocks5ConnectResponse
{
   enet_uint8 version;
   enet_uint8 status;
   enet_uint8 reserved;
   enet_uint8 addressType;
   ENetSocks5Ipv4Address address;
} ENET_PACKED ENetSocks5ConnectResponse;

typedef struct _ENetSocks5IPv4Header
{
   enet_uint16 reserved;
   enet_uint8 fragment;
   enet_uint8 addressType;
   ENetSocks5Ipv4Address address;
} ENET_PACKED ENetSocks5IPv4Header;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

typedef struct _ENetSocks5ProxyInfo
{
   ENetAddress address;
   enet_uint8 username [255];
   enet_uint8 password [255];
} ENetSocks5ProxyInfo;

typedef struct _ENetSocks5Proxy
{
   ENetSocks5ProxyInfo info;
   ENetSocks5State state;
} ENetSocks5Proxy;

#ifndef ENET_API
#define ENET_API extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @defgroup ENet SOCKS5 ENet SOCKS5 helpers
    @{
*/

/** Sets the proxy server address on a proxy info structure.
    @param proxyInfo proxy info to initialize
    @param address proxy server host and port
*/
ENET_API void enet_socks5_set_address (ENetSocks5ProxyInfo * proxyInfo, ENetAddress address);

/** Sets SOCKS5 username/password credentials on a proxy info structure.
    @param proxyInfo proxy info to initialize
    @param username user name, or NULL to clear
    @param password password, or NULL to clear
    @remarks credentials are stored as null-terminated byte strings (max 255 bytes each)
*/
ENET_API void enet_socks5_set_auth (ENetSocks5ProxyInfo * proxyInfo, const char * username, const char * password);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __ENET_SOCKS5_H__ */

