#ifndef TEINDEXBUFFERDX11_H
#define TEINDEXBUFFERDX11_H

#include "TEDataTypes.h"

#include <memory>

struct ID3D11Buffer;

namespace TE
{
	namespace Context { class APIContext; }
	namespace Render { class Mesh; }

	namespace Render
	{
		class APIIndexBuffer
		{
		public:
			APIIndexBuffer(Context::APIContext& context, const Mesh& mesh);
			~APIIndexBuffer();

			void Enable();
			void Disable();

            U32 IncreaseUsageCount();
            U32 DecreaseUsageCount();

        private:
            U32 m_usageCount;
			const Mesh& m_mesh;
			ID3D11Buffer* m_D3DindexBuffer;
			TE::Context::APIContext& m_apiContext;
		};

		typedef std::unique_ptr<APIIndexBuffer> APIIndexBufferUPtr;
	}
}

#endif
