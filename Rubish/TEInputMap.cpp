#include <TEInputMap.h>

int TE::Context::InputMap::GetTEInputFromVirtualKey( int vkey )
{
	std::map<int, TEInput>::iterator itr = m_VKTEMap.find(vkey);
	if (itr != m_VKTEMap.end())
		return itr->second;

	return -1;
}

int TE::Context::InputMap::GetVirtualKeyFromTEInput( TEInput teinput )
{
	std::map<TEInput, int>::iterator itr = m_TEVKMap.find(teinput);
	if (itr != m_TEVKMap.end())
		return itr->second;

	return -1;
}
