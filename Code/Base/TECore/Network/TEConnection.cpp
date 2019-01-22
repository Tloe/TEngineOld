#include "TEConnection.h"
#include <assert.h>
#include <iostream>

TE::Net::Connection::Connection(Socket & socket, const Address & address, U32 timeout , Connection::Mode connectionMode)
    : m_socket(socket)
    , m_address(address)
	, m_timeout(timeout)
    , m_mode(connectionMode)
    , m_running(true)
    , m_timeoutAccumulator(0)
    , m_state(Connection::State::Connecting)
{
    m_socket.NewConnection(address);
}

TE::Net::Connection::~Connection()
{
    if(IsConnected())
        OnDisconnect();
    OnStop();
}

bool TE::Net::Connection::IsRunning() const
{
	return m_running;
}

bool TE::Net::Connection::IsConnecting() const
{
	return m_state == Connection::State::Connecting;
}

bool TE::Net::Connection::ConnectFailed() const
{
	return m_state == Connection::State::ConnectFail;
}

bool TE::Net::Connection::IsConnected() const
{
	return m_state == Connection::State::Connected;
}

TE::Net::Connection::Mode TE::Net::Connection::GetMode() const
{
	return m_mode;
}

void TE::Net::Connection::Update( U64 deltaTime )
{
	assert( m_running );
	m_timeoutAccumulator += deltaTime;
	if ( m_timeoutAccumulator > m_timeout )
	{
		if(m_state == Connection::State::Connecting)
		{
			printf( "connect timed out\n" );
			ClearData();
			m_state = Connection::State::ConnectFail;
			OnDisconnect();
		}
		else if(m_state == Connection::State::Connected)
		{
			printf( "connection timed out\n" );
			ClearData();
			OnDisconnect();
		}
	}
}

bool TE::Net::Connection::SendPacket( Packet& packet )
{
	assert( m_running );
	if(m_state != Connection::State::Connected &&
	   m_state != Connection::State::Connecting)
	{
		return false;
    }
		
    return m_socket.SendTo(m_address, packet);
}

bool TE::Net::Connection::ReceivePacket( Packet& packet )
{
	assert( m_running );
	
    if(!m_socket.GetReceivedPacketFrom(m_address, packet))
        return false;

    if ( m_state == Connection::State::Connecting )
	{
        m_state = Connection::State::Connected;
		OnConnect();
	}
	m_timeoutAccumulator = 0;

    return true;
}

void TE::Net::Connection::ClearData()
{
    m_socket.ConnectionTimeout(m_address);
	m_state = Connection::State::Disconnected;
	m_timeoutAccumulator = 0;
	m_address = Address();
}
