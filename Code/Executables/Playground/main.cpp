#include "AssetImporterTest.h"
#include "NetworkTest.h"
#include "RandomTesting.h"
#include <main.h>

#include "TEThreadPool.h"
#include <iostream>

#include <future>
#include <thread>

#include <assert.h>
#include <iostream>
#include <vector>

#include "TEPacket.h"
#include "TETimer.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

unsigned dummy = 0;

class A {
  public:
    A(const std::string &id) : m_id(id) {}

    const std::string &id() { return m_id; }
    void func() {
        // making sure its not optimized away
        dummy++;
    }

  private:
    std::string m_id;
};

class B {
  public:
    void func() {
        // making sure its not optimized away
        dummy++;
    }
};

int main() {
    std::vector<A> v;
    std::unordered_map<std::string, B> u;
    std::map<std::string, B> m;

    unsigned elementCount = 1;

    struct Times {
        unsigned long long v;
        unsigned long long u;
        unsigned long long m;
    };
    std::map<unsigned, Times> timesMap;

    while (elementCount != 10000000) {
        elementCount *= 10;
        for (unsigned i = 0; i < elementCount; ++i) {
            std::stringstream ss;
            ss << i;
            v.emplace_back(A(ss.str()));
            u.insert(std::make_pair(ss.str(), B()));
            m.insert(std::make_pair(ss.str(), B()));
        }

        std::chrono::time_point<std::chrono::steady_clock> start =
            std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < elementCount; ++i) {
            std::stringstream ss;
            ss << i;
            auto findItr =
                std::find_if(std::begin(v), std::end(v), [&i](A &a) { return a.id() == i; });

            findItr->func();
        }
        auto tp0 = std::chrono::high_resolution_clock::now() - start;
        unsigned long long vTime =
            std::chrono::duration_cast<std::chrono::nanoseconds>(tp0).count();

        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < elementCount; ++i) {
            std::stringstream ss;
            ss << i;
            u[ss.str()].func();
        }
        auto tp1 = std::chrono::high_resolution_clock::now() - start;
        unsigned long long uTime =
            std::chrono::duration_cast<std::chrono::nanoseconds>(tp1).count();

        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < elementCount; ++i) {
            std::stringstream ss;
            ss << i;
            m[ss.str()].func();
        }
        auto tp2 = std::chrono::high_resolution_clock::now() - start;
        unsigned long long mTime =
            std::chrono::duration_cast<std::chrono::nanoseconds>(tp2).count();

        timesMap.insert(std::make_pair(elementCount, Times{vTime, uTime, mTime}));
    }

    for (auto &itr : timesMap) {
        std::cout << "Element count: " << itr.first << std::endl;
        std::cout << "std::vector time:        " << itr.second.v << std::endl;
        std::cout << "std::unordered_map time: " << itr.second.u << std::endl;
        std::cout << "std::map time:           " << itr.second.m << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    std::cout << dummy;
}
/*
I32 main()
{
    A a;
    B b;

    a.Submit(std::bind(&B::func, &b));

    return 0;

        //return AssetImporterTest();
    //return NetworkTestMain();
    //return RandomTesting();
}
*/
