#pragma once
#include "SocketAddress.h"
#include "SocketUtil.h"
#include <memory>

class TCPSocket {
public:
	~TCPSocket();
	int Connect(const SocketAddress& inAddress);
	int Bind(const SocketAddress& inToAddress);
	int Listen(int inBackLog = 32);
	shared_ptr<TCPSocket> Accept(SocketAddress& outFrom);
	int Send(const void* inData, int inLen);
	int Receive(void* inBuffer, int inLen);
private:
	friend class SocketUtil;
	SOCKET mSocket;
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}
};
typedef shared_ptr<TCPSocket> TCPSocketPtr;