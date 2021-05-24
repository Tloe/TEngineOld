#include <TEEffect.h>

TE::Render::Effect::Effect(const std::string &filePath)
    : Resource(filePath),
      m_isInitialized(false) {}

TE::Render::Effect::~Effect() {}

bool TE::Render::Effect::SetupNextPass() {
    return true;
    /* static bool firstPass = true; */
    /* if (!firstPass && m_cgPass) */
    /* { */
    /* 	cgResetPassState(m_cgPass); */
    /* 	m_cgPass = cgGetNextPass(m_cgPass); */
    /* } */
    /* else */
    /* { */
    /* 	firstPass = false; */
    /* 	m_cgPass = cgGetFirstPass(m_cgTechnique); */
    /* } */

    /* if (m_cgPass) */
    /* { */
    /* 	cgSetPassState(m_cgPass); */
    /* 	return true; */
    /* } */
    /* else */
    /* { */
    /* 	return false; */
    /* } */
}

/* CGpass TE::Render::Effect::GetFirstPass() const */
/* { */
/* 	return cgGetFirstPass(m_cgTechnique); */
/* } */

/* CGparameter& TE::Render::Effect::GetCGParamaeter( const std::string& name ) */
/* { */
/* 	assert(m_cgParameters.find(name) != m_cgParameters.end()); */
/* 	return m_cgParameters.find(name)->second; */
/* } */

void TE::Render::Effect::Initialize(/*CGcontext& cgContext*/) {
    /* if (m_isInitialized) return; */

    /* const char* data = reinterpret_cast<const char*>(GetDataFront()); */

    /* //std::cout << "START:" << std::endl << data << std::endl << "END"<< std::endl; */

    /* m_cgEffect = cgCreateEffect(cgContext, data, NULL); */
    /* m_cgTechnique = cgGetFirstTechnique(m_cgEffect); */
    /* while (m_cgEffect && cgValidateTechnique(m_cgTechnique) == CG_FALSE) */
    /* { */
    /* //std::cout << "Technique " << cgGetTechniqueName(m_cgTechnique) << " did not validate" <<
     * std::endl; */
    /* 	m_cgTechnique = cgGetNextTechnique(m_cgTechnique); */
    /* } */
    /* if (!m_cgTechnique) */
    /* { */
    /* 	std::clog << "Your GPU does not support any of the techniques available" << std::endl; */
    /* 	exit(1); */
    /* } */

    /* CGparameter nextParam = cgGetFirstEffectParameter(m_cgEffect); */
    /* while(nextParam) */
    /* { */
    /* 	m_cgParameters.insert(std::make_pair(cgGetParameterName(nextParam), nextParam)); */
    /* 	nextParam = cgGetNextParameter(nextParam); */
    /* } */

    /* m_isInitialized = true; */
}

void TE::Render::Effect::Cleanup() {
    if (m_isInitialized) {
        // cgDestroyEffect(m_cgEffect);
        m_isInitialized = false;
    }
}
