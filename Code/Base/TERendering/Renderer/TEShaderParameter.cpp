#include <TEShaderParameter.h>
/* #include "Cg/cg.h" */

void TE::Render::ShaderParameterSetter::SetParameter(const std::string &parameterName, /*CGparameter& cgParameter,*/ const Math::Matrix4D<F32> matrix) {
    // cgSetMatrixParameterfc(cgParameter, &matrix(0,0));
}

void TE::Render::ShaderParameterSetter::SetParameter(const std::string &parameterName, /*CGparameter& cgParameter,*/ const Math::Matrix4D<F64> matrix) {
    // cgSetMatrixParameterdc(cgParameter, &matrix(0,0));
}
