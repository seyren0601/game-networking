// Creating_Sockets.cpp : Defines the entry point for the application.
//

#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "UDPSocket.h"
#include "SocketUtil.h"
#include <WinSock2.h>
#include <iostream>

using namespace std;

int main()
{
	WSAData data;
	int startupResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (startupResult != 0) {
		cerr << "WSAStartup failed with error: " << SOCKET_ERROR << endl;
		cerr << "Last error code: " << WSAGetLastError() << endl;
		return 1;
	}

	// Create a SocketAddress using the factory method
	SocketAddressFactory factory;
	auto ptrSocketAddress = factory.CreateIPv4FromString("192.168.1.3:7000");
	auto udpSocket = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
	if (!udpSocket) {
		cerr << "Failed to create UDP socket." << endl;
		return 1;
	}


	int closeResult = WSACleanup();
	if (closeResult != 0) {
		cerr << "WSACleanup failed with error: " << SOCKET_ERROR << endl;
		cerr << "Last error code: " << WSAGetLastError() << endl;
		return 1;
	}
	return 0;
}
