#ifndef TESHADERPARAMETER_H
#define TESHADERPARAMETER_H

#include "TEMatrix4D.h"
#include <TEDataTypes.h>
#include "Cg/cg.h"
#include <string>

namespace TE
{
	namespace Render
	{
		class ShaderParameterSetter
		{
		public:
			void SetParameter(const std::string& parameterName, CGparameter& cgParameter, const Math::Matrix4D<F32> matrix);
			void SetParameter(const std::string& parameterName, CGparameter& cgParameter, const Math::Matrix4D<F64> matrix);
		};

		class ShaderParameterBase
		{

		};

		template<typename T>
		class ShaderParameter : public ShaderParameterBase
		{
		public:
			ShaderParameter(const std::string& parameterName)
				:
				m_parameterName(parameterName)
			{}

			~ShaderParameter()
			{}

			const std::string& GetName()
			{
				return m_parameterName;
			}

			void Update(CGparameter& cgParameter, const T& parameter);
		private:
			std::string m_parameterName;
			ShaderParameterSetter m_parameterSetter;
		};
		
		template<typename T>
		void TE::Render::ShaderParameter<T>::Update( CGparameter& cgParameter, const T& parameter )
		{
			m_parameterSetter.SetParameter(m_parameterName, cgParameter, parameter);
		}

	}
}

#endif
