// Creating_Sockets.cpp : Defines the entry point for the application.
//

#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "Creating_Sockets.h"
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


	// Manually socket creation using WinSock API
	SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	closesocket(udpSocket);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(5000);
	serverAddress.sin_addr.S_un.S_un_b.s_b1 = 192;
	serverAddress.sin_addr.S_un.S_un_b.s_b2 = 168;
	serverAddress.sin_addr.S_un.S_un_b.s_b3 = 1;
	serverAddress.sin_addr.S_un.S_un_b.s_b4 = 1;
	memset(&serverAddress.sin_zero, 0, sizeof(serverAddress.sin_zero));

	cout << "Server address: " << static_cast<int>(serverAddress.sin_addr.S_un.S_un_b.s_b1) << "."
		 << static_cast<int>(serverAddress.sin_addr.S_un.S_un_b.s_b1) << "."
		 << static_cast<int>(serverAddress.sin_addr.S_un.S_un_b.s_b2) << "."
		<< static_cast<int>(serverAddress.sin_addr.S_un.S_un_b.s_b3) << endl;

	// Create a SocketAddress object
	SocketAddressPtr socketAddress = make_shared<SocketAddress>("192.168.1.2", 6000);

	cout << "SocketAddress created with address: "
		 << static_cast<int>(socketAddress->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b1) << "."
		 << static_cast<int>(socketAddress->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b2) << "."
		 << static_cast<int>(socketAddress->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b3) << "."
		 << static_cast<int>(socketAddress->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b4)
		<< " and port: " << ntohs(socketAddress->GetAsSockAddrIn()->sin_port) << endl;

	// Create a SocketAddress using the factory method
	SocketAddressFactory factory;
	auto futureSocket = factory.CreateIPv4FromString("192.168.1.3:7000");
	SocketAddressPtr factoryCreatedSocket = futureSocket.get();
	cout << "Factory created SocketAddress with address: "
		 << static_cast<int>(factoryCreatedSocket->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b1) << "."
		 << static_cast<int>(factoryCreatedSocket->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b2) << "."
		 << static_cast<int>(factoryCreatedSocket->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b3) << "."
		 << static_cast<int>(factoryCreatedSocket->GetAsSockAddrIn()->sin_addr.S_un.S_un_b.s_b4)
		<< " and port: " << ntohs(factoryCreatedSocket->GetAsSockAddrIn()->sin_port) << endl;


	int closeResult = WSACleanup();
	if (closeResult != 0) {
		cerr << "WSACleanup failed with error: " << SOCKET_ERROR << endl;
		cerr << "Last error code: " << WSAGetLastError() << endl;
		return 1;
	}
	return 0;
}
