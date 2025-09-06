#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
class UDPSocket;
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

#include "UDPSocket.h"