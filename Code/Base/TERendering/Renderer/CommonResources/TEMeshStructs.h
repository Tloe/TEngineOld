#ifndef TEMESHSTRUCTS_H
#define TEMESHSTRUCTS_H

#include "TEDataTypes.h"
#include <vector>

namespace TE::Render {
  namespace PrimitiveType {
    enum { POINTS, LINES, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, COUNT };
  }

  namespace Usage {
    enum { STATIC, DYNAMIC };
  }

  namespace Semantics {
    enum {
      POSITION,
      BLENDWEIGHT,
      NORMAL,
      DIFFUSECOLOR,
      SPECULARCOLOR,
      TESSFACTOR,
      POINTSIZE,
      BLENDINDICES,
      TEXTURE0,
      TEXTURE1,
      TEXTURE2,
      TEXTURE3,
      TEXTURE4,
      TEXTURE5,
      TEXTURE6,
      TEXTURE7,
      TANGENT,
      BINORMAL,
      COUNT
    };
  }

  namespace LayoutElementValueType {
    enum { F32 = 0, U16 = 4, COUNT };
  }

  struct VertexBufferInfo {
    struct LayoutElement {
      I32 layoutSemantic;
      I32 valueType;
      I32 valueCount;
      I32 byteOffset;
    };

    typedef std::vector<LayoutElement> LayoutElementVec;

    U32 primitiveType;
    U32 usage;
    U32 dataElementCount;
    U32 dataElementSize;
    U32 dataSize;

    LayoutElementVec layoutElements;
  };

  struct IndexBufferInfo {
    U32 usage;
    U32 dataElementCount;
    U32 dataElementSize;
    U32 dataSize;
  };
}

#endif
