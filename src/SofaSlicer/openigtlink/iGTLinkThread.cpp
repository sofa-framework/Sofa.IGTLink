#include <SofaSlicer/openigtlink/iGTLinkBase.h>
#include <SofaSlicer/openigtlink/iGTLinkThread.h>
#include <igtlPointMessage.h>
#include <igtlPolyDataMessage.h>

namespace SofaSlicer::openigtlink
{


    void iGTLinkBaseThread::mainLoop()
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


    void iGTLinkBaseThread::launchThread()
    {
        m_thread.reset(new std::thread(std::bind(&iGTLinkBaseThread::mainLoop,this)));
    }

    void iGTLinkBaseThread::stopThread()
    {
        if(m_thread)
        {
            m_running.store(false);
            if (m_thread->joinable())
                m_thread->join();
        }
        m_thread = NULL;
    }

    iGTLinkRecieverThread::iGTLinkRecieverThread(iGTLinkBase* _link) : iGTLinkBaseThread(_link)
    {
        m_currentData.store(0);
    }

    void iGTLinkRecieverThread::swapData()
    {
        unsigned swapped = (m_currentData.load(std::memory_order_relaxed) +1) % 2;
        m_currentData.store(swapped);
    }

    void iGTLinkRecieverThread::doLoop()
    {
        std::lock_guard<std::mutex> lock(m_mutex[m_currentData.load(std::memory_order_relaxed)]);

        igtl::MessageHeader::Pointer headerMsg;
        headerMsg = igtl::MessageHeader::New();

        // Initialize receive buffer
        headerMsg->InitPack();

        // Receive generic header from the socket
        bool timeout(false);
        igtlUint64 r = m_link->m_socket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize(), timeout);
        if (r == 0)
        {
            m_link->m_socket->CloseSocket();
        }
        if (r != headerMsg->GetPackSize())
        {
            return;
        }
        headerMsg->Unpack();

        //TODO This whole if could be remplaced with a factory, or templated layer.
        igtl::MessageBase::Pointer dataMessage;
        if (strcmp(headerMsg->GetDeviceType(), "POINT") == 0)
        {
            dataMessage = igtl::PointMessage::New();
        }
        else if (strcmp(headerMsg->GetDeviceType(), "POLYDATA") == 0)
        {
            dataMessage = igtl::PolyDataMessage::New();
        }
        else
        {
            msg_warning(m_link) << "Message  of type " << headerMsg->GetDeviceType() << " received, but not implemented yet";
            return;
        }


        dataMessage->SetMessageHeader(headerMsg);
        dataMessage->AllocatePack();
        m_link->m_socket->Receive(dataMessage->GetPackBodyPointer(), dataMessage->GetPackBodySize(), timeout);
        m_dataStructures[m_currentData.load(std::memory_order_relaxed)][dataMessage->GetDeviceName()] = dataMessage;
    }

    std::map<std::string,igtl::MessageBase::Pointer>& iGTLinkRecieverThread::getAvailableData()
    {
        swapData();
        m_mutex[(m_currentData.load(std::memory_order_relaxed) +1) % 2].lock();

        return m_dataStructures[(m_currentData.load(std::memory_order_relaxed) +1) % 2];

    }


}