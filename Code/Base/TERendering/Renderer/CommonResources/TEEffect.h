#ifndef TEEFFECT_H
#define TEEFFECT_H

#include <string>
#include <unordered_map>
/* #include "Cg/cg.h" */
#include "TEShaderParameter.h"
#include <TEResource.h>

namespace TE {
namespace Render {
    class Effect : public Resources::Resource {
      public:
        Effect(const std::string &filePath);
        ~Effect();

        void Initialize(/*CGcontext& cgContext*/);
        void Cleanup();
        bool SetupNextPass();
        /* CGpass GetFirstPass() const; */
        /* CGparameter& GetCGParamaeter(const std::string& name); */

      private:
        /* CGeffect m_cgEffect; */
        bool m_isInitialized;
        /* CGtechnique m_cgTechnique; */
        /* CGpass m_cgPass; */
        /* std::unordered_map<std::string, CGparameter> m_cgParameters; */
    };
}
}

#endif
