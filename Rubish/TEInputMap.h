/**
 *	\file		TEInputMap.h
 *  \author		Terje Loe
 *  \brief		Defenitions for InputMap class. Used to map from OS virtual key to TEngine input type
 *				might not be needed. need to use it more to find out
 */

#ifndef TEINPUTMAP_H
#define TEINPUTMAP_H

#include <TEInput.h>
#include <map>

namespace TE
{
	namespace Context
	{
		class InputMap
		{
		public:
			InputMap();
			int GetTEInputFromVirtualKey(int vkey);
			int GetVirtualKeyFromTEInput(TEInput teinput);
		private:
			std::map<int, TEInput> m_VKTEMap;
			std::map<TEInput, int> m_TEVKMap;
		};
	}
}

#endif
