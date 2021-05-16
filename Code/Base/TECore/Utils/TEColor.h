#ifndef TECOLOR_H
#define TECOLOR_H

#include <TEDataTypes.h>

namespace TE {
    class ColorRGBA {
      public:
        ColorRGBA() {}
        ColorRGBA(Real newr, Real newg, Real newb, Real newa)
            : r(newr),
              g(newg),
              b(newb),
              a(newa) {}

        Real r, g, b, a;
    };
}

#endif