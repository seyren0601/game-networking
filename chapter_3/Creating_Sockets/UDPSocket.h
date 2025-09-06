#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <memory>
#include "SocketAddress.h"

class UDPSocket {
public:
	~UDPSocket();
	int Bind(const SocketAddress& inBindAddress);
	int SendTo(const void *inData, int inLen, const SocketAddress &inTo);
	int ReceiveFrom(void *inBuffer, int inLen, SocketAddress &outFrom);
private:
	friend class SocketUtil;
	SOCKET mSocket;

	// Initializer list 
	// <class_name>(<param1>, <param2>) : <mem_var1>(<param1>), <mem_var2>(<param2>) { }
	UDPSocket(SOCKET inSocket) : mSocket(inSocket) { }
};
typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

enum SocketAddressFamily {
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketUtil {
private:
public:
	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily);
	static void ReportError(const std::wstring error);
	static int GetLastError();
};