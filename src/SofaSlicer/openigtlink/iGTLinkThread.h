#pragma once

#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include <SofaSlicer/openigtlink/iGTLinkBase.h>

namespace SofaSlicer::openigtlink
{
    class iGTLinkBaseThread
    {
    public:
        iGTLinkBaseThread(iGTLinkBase* _link) : m_link(_link), m_thread(nullptr) {}

        void mainLoop()
        {
            m_running.store(true);
            while(m_running.load(std::memory_order_relaxed))
            {
                if(!m_link->isConnected())
                    m_link->tryConnect();
                else
                    doLoop();
            }
        }

        virtual void doLoop() = 0;

        void launchThread()
        {
            m_thread.reset(new std::thread(std::bind(&iGTLinkBaseThread::mainLoop,this)));
        }

        void stopThread()
        {
            if(m_thread)
            {
                m_running.store(false);
                if (m_thread->joinable())
                    m_thread->join();
            }
            m_thread = NULL;
        }

    private:
        std::atomic<bool> m_running;
        std::shared_ptr<std::thread> m_thread;
        iGTLinkBase * m_link;
    };

}