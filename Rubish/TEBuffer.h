#ifndef TEBUFFER_H
#define TEBUFFER_H

#include <boost/shared_array.hpp>

namespace TE
{
	namespace Render
	{
		class Buffer
		{
		public:
			Buffer(char* data, int elementCount, int elementSize)
				:
				m_data(data),
				m_elementCount(elementCount),
				m_elementSize(elementSize)
			{}

			void SetData(char* data, int elementCount, int elementSize)
			{
				m_elementCount = elementCount;
				m_elementSize = elementSize;
				m_data.reset(data);
			}

			const boost::shared_array<char> GetData() const
			{
				return m_data;
			}

			int GetElementCount() const
			{
				return m_elementCount;
			}

			int GetElementSize() const
			{
				return m_elementSize;
			}

			int GetDataSize() const
			{
				return m_elementCount*m_elementSize;
			}
		private:
			int							m_elementCount;
			int							m_elementSize;
			boost::shared_array<char>	m_data;
		};
	}
}

#endif
