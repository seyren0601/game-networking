#pragma once
#include <cstdint>
#include <Winsock2.h>
#include <memory>
#include <ws2tcpip.h>

using namespace std;

class SocketAddress {
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort) {
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_port = htons(inPort);
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
		memset(&GetAsSockAddrIn()->sin_zero, 0, sizeof(GetAsSockAddrIn()->sin_zero));
	};

	SocketAddress(const sockaddr& inSockAddr) {
		memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
	};

	SocketAddress(const char* inAddress, uint16_t inPort) {
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_port = htons(inPort);
		inet_pton(AF_INET, inAddress, &GetAsSockAddrIn()->sin_addr);
		memset(&GetAsSockAddrIn()->sin_zero, 0, sizeof(GetAsSockAddrIn()->sin_zero));
	};

	size_t GetSize() const { return sizeof(sockaddr); }
	sockaddr_in* GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&mSockAddr); }

private:
	friend class UDPSocket;
	sockaddr mSockAddr;
};
typedef shared_ptr<SocketAddress> SocketAddressPtr;