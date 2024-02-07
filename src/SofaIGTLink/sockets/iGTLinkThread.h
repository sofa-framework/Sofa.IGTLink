#pragma once

#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include <mutex>
#include <SofaIGTLink/messages/iGTLinkMessage.h>
#include <sofa/core/objectmodel/Data.h>

class iGTLinkBase;
using namespace sofa::core::objectmodel;

namespace SofaSlicer::openigtlink
{
    class iGTLinkBaseThread
    {
    public:
        iGTLinkBaseThread(iGTLinkBase* _link) : m_link(_link), m_thread(nullptr), m_running(false){}

        void mainLoop();

        virtual void doLoop() = 0;

        bool threadRunning();
        void launchThread();
        void stopThread();

    protected:
        std::atomic<bool> m_running;
        std::shared_ptr<std::thread> m_thread;
        iGTLinkBase * m_link;
    };

    class iGTLinkReceiverThread : public iGTLinkBaseThread
    {
    public:
        iGTLinkReceiverThread(iGTLinkBase* _link);

        virtual void doLoop();

        bool isDataAvailable();
        std::map<std::string,igtl::MessageBase::Pointer>& getAvailableData();

    private:
        void swapData();

        std::atomic<unsigned> m_currentData;
        std::atomic<bool> m_dataAvailable;
        std::map<std::string,igtl::MessageBase::Pointer> m_dataStructures[2];
        std::mutex m_mutex[2];


    };

}
