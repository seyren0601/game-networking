#include "SocketUtil.h"

void SocketUtil::ReportError(const wstring error) {
	std::wcerr << error;
}

int SocketUtil::GetLastError() {
	return WSAGetLastError();
}

UDPSocketPtr SocketUtil::CreateUDPSocket(SocketAddressFamily inFamily) {
	SOCKET retSocket = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
	if (retSocket != INVALID_SOCKET) {
		return UDPSocketPtr(new UDPSocket(retSocket));
	}
	return nullptr;
}