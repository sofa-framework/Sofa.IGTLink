//#include <SofaSlicer/openigtlink/iGTLinkBase.h>
//#include <SofaSlicer/openigtlink/iGTLinkThread.h>
//
//namespace SofaSlicer::openigtlink
//{
//
//
//    void iGTLinkBaseThread::mainLoop()
//    {
//        m_running.store(true);
//        while(m_running.load(std::memory_order_relaxed))
//        {
//            if(!m_link->isConnected())
//                m_link->tryConnect();
//            else
//                doLoop();
//        }
//    }
//
//
//    void iGTLinkBaseThread::launchThread()
//    {
//        m_thread.reset(new std::thread(std::bind(&iGTLinkBaseThread::mainLoop,this)));
//    }
//
//    void iGTLinkBaseThread::stopThread()
//    {
//        if(m_thread)
//        {
//            m_running.store(false);
//            if (m_thread->joinable())
//                m_thread->join();
//        }
//        m_thread = NULL;
//    }
//
//    iGTLinkRecieverThread::iGTLinkRecieverThread()
//    : d_timeout(initData(&d_timeout,0,"timeout","Timeout recieving data"))
//    {
//        m_currentData.store(0);
//    }
//
//    void iGTLinkRecieverThread::swapData()
//    {
//        unsigned swapped = (m_currentData.load(std::memory_order_relaxed) +1) % 2;
//        m_currentData.store(swapped);
//    }
//
//    void iGTLinkRecieverThread::doLoop()
//    {
//        std::lock_guard<std::mutex> lock(m_mutex[m_currentData.load(std::memory_order_relaxed)]);
//
//        igtl::MessageHeader::Pointer headerMsg;
//        headerMsg = igtl::MessageHeader::New();
//
//        // Initialize receive buffer
//        headerMsg->InitPack();
//
//        // Receive generic header from the socket
//        bool timeout(false);
//        igtlUint64 r = m_link->m_socket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize(), timeout);
//        if (r == 0)
//        {
//            m_link->m_socket->CloseSocket();
//        }
//        if (r != headerMsg->GetPackSize())
//        {
//            return;
//        }
//
//        //TODO This whole if could be remplaced with a factory, or templated layer.
//        if (strcmp(headerMsg->GetDeviceType(), "POINT") == 0)
//        {
//
////            ReceivePoint(socket, headerMsg);
//        }
//        else if (strcmp(headerMsg->GetDeviceType(), "POLYDATA") == 0)
//        {
////            ReceiveTrajectory(socket, headerMsg);
//        }
//        else
//        {
//            msg_warning(m_link) << "Message  of type " << headerMsg->GetDeviceType() << " received, but not implemented yet";
//        }
//
//        // Deserialize the header
//        headerMsg->Unpack();
//    }
//
//    std::map<std::string,igtl::MessageBase::Pointer>& iGTLinkRecieverThread::getAvailableData()
//    {
//        swapData();
//        m_mutex[(m_currentData.load(std::memory_order_relaxed) +1) % 2].lock();
//
//        return m_dataStructures[(m_currentData.load(std::memory_order_relaxed) +1) % 2];
//
//    }
//
//
//}