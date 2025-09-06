#include "SocketUtil.h"

void SocketUtil::ReportError(const wstring error) {
	std::wcerr << error;
}

int SocketUtil::GetLastError() {
	return WSAGetLastError();
}

UDPSocketPtr SocketUtil::CreateUDPSocket(SocketAddressFamily inFamily) {
	SOCKET retSocket = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
	if (retSocket == INVALID_SOCKET) {
		return nullptr;
	}
	return UDPSocketPtr(new UDPSocket(retSocket));
}

TCPSocketPtr SocketUtil::CreateTCPSocket(SocketAddressFamily inFamily) {
	SOCKET retSocket = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);
	if (retSocket == INVALID_SOCKET) {
		return nullptr;
	}
	return TCPSocketPtr(new TCPSocket(retSocket));
}