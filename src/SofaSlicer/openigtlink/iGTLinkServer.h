#pragma once
#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/objectmodel/Data.h>

#include <string>

#include <igtl/igtlOSUtil.h>
#include <igtl/igtlPointMessage.h>
#include <igtl/igtlServerSocket.h>
#include <SofaSlicer/openigtlink/iGTLinkBase.h>
#include <SofaSlicer/openigtlink/iGTLinkMessage.h>

using namespace sofa::core::objectmodel;

namespace SofaSlicer::openigtlink
{
    class iGTLinkServer : public iGTLinkBase
    {
    public:
        iGTLinkServer();
        ~iGTLinkServer() = default;

        void init();
        void bwdInit();

        virtual bool tryConnect();
        virtual bool isConnected();
        void handleEvent(Event *event);
        void sendMessages();
        void addMessageObject(iGTLinkMessageBase *);
        void removeMessageObject(iGTLinkMessageBase *);


    private:
        igtl::ServerSocket::Pointer m_serverSocket;
        igtl::Socket::Pointer m_socket;
        Data<int> d_port;

    };
}

