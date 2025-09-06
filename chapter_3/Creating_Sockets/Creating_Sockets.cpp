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

	// Create a SocketAddress using the factory method
	SocketAddressFactory factory;
	auto factoryCreatedSocket = factory.CreateIPv4FromString("192.168.1.3:7000");
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
