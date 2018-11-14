#include "TEActionExecutor.h"

TE::InputMapping::ActionExecutor::ActionExecutor( const std::string& actionName )
	: m_nameHash(HashGenerator()(actionName))
{

}
