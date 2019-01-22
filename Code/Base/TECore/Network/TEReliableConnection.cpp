#include "TEReliableConnection.h"
#include "TEPacket.h"
#include <iostream>
#include <assert.h>

TE::Net::ReliableConnection::ReliableConnection(Socket & socket, const Address &address, U32 timeout, Connection::Mode connectionMode, U32 maxSequence )
    : Connection(socket, address, timeout, connectionMode)
    , m_reliabilityControl(maxSequence)
    , m_previousReceivedSeqNo(-1)
{

}

TE::Net::ReliableConnection::~ReliableConnection()
{

}

bool TE::Net::ReliableConnection::SendPacket( Net::Packet& packet )
{
    U32 sequenceNo = m_reliabilityControl.GetLocalSequence();
    U32 ack = m_reliabilityControl.GetRemoteSequence();
    U32 ackBits = m_reliabilityControl.GenerateAckBits();

	packet.WriteSequenceNo(sequenceNo);
    packet.WriteAck(ack);
    packet.WriteAckBits(ackBits);

	if (!Connection::SendPacket(packet))
		return false;
    m_reliabilityControl.PacketSent(packet.GetLength() - packet.GetHeaderSize());
	return true;
}

bool TE::Net::ReliableConnection::ReceivePacket( Net::Packet & packet )
{
	if(!Connection::ReceivePacket(packet))
		return false;
	
	U32 sequenceNo = 0;
	U32 ack = 0;
	U32 ackBits = 0;

	packet.ReadSequenceNo(sequenceNo);
	packet.ReadAck(ack);
	packet.ReadAckBits(ackBits);

    if(!Net::SequenceNumberMoreRecent(sequenceNo, m_previousReceivedSeqNo))
    {
        return false;
    }

    m_previousReceivedSeqNo = sequenceNo;

    m_reliabilityControl.PacketReceived(sequenceNo, packet.GetLength() - packet.GetHeaderSize());
    m_reliabilityControl.ProcessAck(ack, ackBits);
	
	return true;
}

void TE::Net::ReliableConnection::Update( U64 deltaTime )
{
	Connection::Update(deltaTime);
    m_reliabilityControl.Update(deltaTime);
}

TE::Net::ReliabilityControl & TE::Net::ReliableConnection::GetReliabilityControl()
{
    return m_reliabilityControl;
}

void TE::Net::ReliableConnection::OnStop()
{
	ClearData();
}

void TE::Net::ReliableConnection::OnDisconnect()
{
	ClearData();
}

void TE::Net::ReliableConnection::ClearData()
{
    m_reliabilityControl.Reset();
}

