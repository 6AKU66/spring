/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "LoopbackConnection.h"
#include "Net/Protocol/NetMessageTypes.h"

#include <tracy/Tracy.hpp>

namespace netcode {

void CLoopbackConnection::SendData(std::shared_ptr<const RawPacket> pkt) {
	//ZoneScoped;
	numPings += (pkt->data[0] == NETMSG_PING);
	pktQueue.push_back(pkt);
}

std::shared_ptr<const RawPacket> CLoopbackConnection::Peek(unsigned ahead) const {
	//ZoneScoped;
	if (ahead >= pktQueue.size())
		return {};

	return pktQueue[ahead];
}

void CLoopbackConnection::DeleteBufferPacketAt(unsigned index) {
	//ZoneScoped;
	if (index >= pktQueue.size())
		return;

	numPings -= (pktQueue[index]->data[0] == NETMSG_PING);
	pktQueue.erase(pktQueue.begin() + index);
}

std::shared_ptr<const RawPacket> CLoopbackConnection::GetData() {
	//ZoneScoped;
	if (pktQueue.empty())
		return {};

	numPings -= (pktQueue[0]->data[0] == NETMSG_PING);

	std::shared_ptr<const RawPacket> next = pktQueue.front();
	pktQueue.pop_front();
	return next;
}

} // namespace netcode

