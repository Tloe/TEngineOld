#ifndef TETHREADJOINER_H
#define TETHREADJOINER_H

#include <vector>
#include <thread>

namespace TE
{
    namespace Threading
    {
        class ThreadJoiner
        {
        public:
            ThreadJoiner(std::vector<std::thread> & threads)
                : m_threads(threads)
            {}

            ~ThreadJoiner()
            {
                for(auto & thread : m_threads)
                {
                    if(thread.joinable())
                        thread.join();
                }
            }
        private:
            std::vector<std::thread> & m_threads;

        };
    }
}

#endif
