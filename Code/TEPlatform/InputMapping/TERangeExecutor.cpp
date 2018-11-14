#include "TERangeExecutor.h"

TE::InputMapping::RangeExecutor::RangeExecutor( const std::string& rangeName )
	: m_nameHash(HashGenerator()(rangeName))
{

}
