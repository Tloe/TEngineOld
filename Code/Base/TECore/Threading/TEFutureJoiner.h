#ifndef TEFUTUREJOINER_H
#define TEFUTUREJOINER_H

#include <future>
#include <vector>

namespace TE::Threading {
    template <typename R> class FutureJoiner {
      public:
        explicit FutureJoiner(std::vector<std::future<R>> &futures) : m_futures(futures) {}

        ~FutureJoiner() {
            for (auto &future : m_futures) {
                future.wait();
            }
        }

      private:
        std::vector<std::future<R>> &m_futures;
    };
}

#endif
