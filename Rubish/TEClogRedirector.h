#ifndef TECLOGREDIRECTOR_H
#define TECLOGREDIRECTOR_H
#include <fstream>
#include <iostream>

namespace TE
{
	class ClogRedirector
	{
	public:
		ClogRedirector(const std::string& filePath)
		{
			m_outStream.open(filePath);

			m_rFormer_buff = std::clog.rdbuf(m_outStream.rdbuf());
		}

		~ClogRedirector()
		{
			m_outStream.close();
			std::clog.rdbuf(m_rFormer_buff);
		}
	private:
		std::ofstream m_outStream;
		std::streambuf* m_rFormer_buff;
	};
}

#endif