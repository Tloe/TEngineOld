#ifndef TESHADER_H
#define TESHADER_H
#include <string>

namespace TE
{
	namespace Render
	{
		class Shader
		{
		public:
			Shader(const std::string &filename)
				:
				m_fileName(filename)
			{}

			const std::string& GetFileName() const
			{
				return m_fileName;
			}
		private:
			std::string m_fileName;
		};
	}
}

#endif