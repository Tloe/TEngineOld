#ifndef TEFUNCTIONWRAPPER_H
#define TEFUNCTIONWRAPPER_H

#include <memory>

namespace TE {
namespace Threading {
    class FunctionWrapper {
      public:
        FunctionWrapper();

        template <typename F>
        FunctionWrapper(F &&f)
            : m_function(new FunctionStorage<F>(std::move(f))) {
        }

        FunctionWrapper(FunctionWrapper &&other);

        FunctionWrapper &operator=(FunctionWrapper &&other);

        void operator()();

      private:
        struct FunctionStorageBase {
            virtual ~FunctionStorageBase() {}
            virtual void Call() = 0;
        };
        template <typename F>
        struct FunctionStorage : FunctionStorageBase {
            F function;
            FunctionStorage(F &&function) : function(std::move(function)) {}
            virtual void Call() { function(); }
        };
        typedef std::unique_ptr<FunctionStorageBase> FunctionStorageBaseUPtr;

        FunctionWrapper(const FunctionWrapper &);
        FunctionWrapper &operator=(const FunctionWrapper &);

        FunctionStorageBaseUPtr m_function;
    };
}
}

#endif
