#include <iostream>
#include "TEHost.h"
#include <winbase.h>
#include "TEPacking.h"
#include "TEEventHandler.h"
#include "TEVector3D.h"
#include "TEMathBase.h"
#include "TEVector2D.h"
#include "TEMatrix3D.h"
#include "TEMatrix4D.h"
#include "TEQuaternion.h"

namespace ServerEvent
{
	enum
	{
		None,
		Ping,
		LoginResult,
		StateUpdate,
		Chat
	};
}
namespace ClientEvent
{
	enum
	{
		None,
		Pong,
		Login,
		Input,
		Chat
	};
}

class ChatMsg : public TE::Network::Packable
{
public:
	ChatMsg(const std::string &msg)
	{
		m_msg = msg;
	}

	void pack(TE::Network::Packet &packet)
	{
		packet.BeginPacket();
		packet.WriteEventID(ClientEvent::Chat);
		packet.WriteString(m_msg);
		packet.EndPacket();
	}

	void unpack(TE::Network::Packet &packet)
	{
		packet.ReadString(m_msg);
	}

private:
	std::string m_msg;
};

enum Events
{
	explosion,
	aBomb
};

class ExplosionEvent : public TE::Event
{
public:
	ExplosionEvent(float pos) 
		: Event(explosion), m_pos(pos), m_radius(10)
	{}

	float getPos() const
	{
		return m_pos;
	}
	float getRadius() const
	{
		return m_radius;
	}
private:
	float m_pos;
	float m_radius;
};

class ABombEvent : public TE::Event
{
public:
	ABombEvent(float pos)
		: Event(aBomb), m_pos(pos), m_radius(1000)
	{}

	float getPos() const
	{
		return m_pos;
	}
	float getRadius() const
	{
		return m_radius;
	}
private:
	float m_pos;
	float m_radius;
};

class Monster : public TE::EventHandler
{
public:
	Monster(float pos)
		: m_pos(pos)
	{
		registerSubscription(explosion,this, &Monster::onExplosion);
		registerSubscription(aBomb,this, &Monster::onAbomb);
	}

	void onExplosion(const ExplosionEvent &event)
	{
		if (fabs(m_pos - event.getPos()) < event.getRadius())
		{
			std::cout << "Monster at position " << m_pos << " died!" << std::endl;
		}
		else
		{
			std::cout << "Monster at position " << m_pos << " survived!" << std::endl;
		}
	}
	
	void onAbomb(const ABombEvent &event)
	{
		if (fabs(m_pos - event.getPos()) < event.getRadius())
		{
			std::cout << "Monster at position " << m_pos << " died!" << std::endl;
		}
		else
		{
			std::cout << "Monster at position " << m_pos << " survived!" << std::endl;
		}
	}
private:
	float m_pos;
};

int main()
{
	Monster mstr0(0.0f);
	Monster mstr1(5.0f);
	Monster mstr2(15.0f);

	ExplosionEvent explosionEvent(0.0f);
	std::cout << "Explosion at 0.0!" << std::endl;
	TE::TheEventManager.NewEvent(explosionEvent);
	ABombEvent aBombEvent(0.0f);
	TE::TheEventManager.NewEvent(aBombEvent);

	
	TE::Math::Vector3D<float> test3d = TE::Math::Vector3Df::VECTOR3D_AXIS_X;
	TE::Math::Vector2Df test2d = TE::Math::Vector2Df::VECTOR2D_AXIS_X;
	TE::Math::Base<float>::InverseSqrt(1.0);
	TE::Math::Matrix3D<float> testMat(test3d, test3d, test3d);
	TE::Math::Matrix4D<float> testMat4(test3d, test3d, test3d);
	TE::Math::Quaternion<float> testQuat(0,0,0,1);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			testMat(i,j) = static_cast<float>(i);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << testMat(i,-1);
		}
	}

	system("PAUSE");

	/*char hostType = ' ';
	std::cout << "Server(s) or Client(c):";
	while(hostType != 's' && hostType != 'c')
	{
		std::cin >> hostType;
	}

	std::string ip;
	std::cout << "Enter ip address:" << std::endl;
	std::cin >> ip;
		
	TE::Network::Host host;

	std::string testStr;
	if (hostType == 's')
	{
		host.start(true, 4, ip, 1234);
		std::cout << "Server started!" << std::endl;
	}
	else
	{
		host.start(false,1, ip, 1234);
		std::cout << "Client started!" << std::endl;

		std::cout << "Pleas enter test message: ";
		
		std::cin >> testStr;
	}

	ChatMsg testMsg(testStr);

	while (true)
	{
		host.update();
		if (hostType == 'c')
		{
			
			TE::Network::Packet testPack;
			testMsg.pack(testPack);
			
			host.sendPacket(testPack);
		}
		else
		{

			TE::Network::Packet dummy;
			host.sendPacket(dummy, "server");
		}
		
		Sleep(10);
	}*/

	return 0;
}
