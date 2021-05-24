#ifndef TECONNECTION_H
#define TECONNECTION_H

#include "TEAddress.h"
#include "TEDataTypes.h"
#include "TESocket.h"

namespace TE::Net {
  class Packet;

  class Connection {
  public:
    enum class Mode { NotSet, Client, Server };

    enum class State { Disconnected, Connecting, ConnectFail, Connected };

    Connection(Net::Socket &socket,
               const Address &address,
               U32 timeout,
               Connection::Mode connectionMode);
    virtual ~Connection();

    void Cleanup();
    bool IsRunning() const;
    void Listen();
    void Connect(const Address &address);
    bool IsConnecting() const;
    bool ConnectFailed() const;
    bool IsConnected() const;
    bool IsListening() const;
    Connection::Mode GetMode() const;
    virtual void Update(U64 deltaTime);
    virtual bool SendPacket(Net::Packet &packet);
    virtual bool ReceivePacket(Net::Packet &packet);

  protected:
    virtual void OnStop() {}
    virtual void OnConnect() {}
    virtual void OnDisconnect() {}

  private:
    void ClearData();

    Net::Socket &m_socket;
    Address m_address;
    U32 m_timeout;
    Connection::Mode m_mode;
    bool m_running;
    U64 m_timeoutAccumulator;
    Connection::State m_state;
  };
}

#endif
