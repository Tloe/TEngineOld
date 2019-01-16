#include "TEStateExecutor.h"

TE::InputMapping::StateExecutor::StateExecutor( const std::string & stateName )
	: m_nameHash(HashGenerator()(stateName))
{

}

TE::InputMapping::StateExecutor::~StateExecutor()
{

};
