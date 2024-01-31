#pragma once

#include <map>
#include <sofa/core/objectmodel/BaseObject.h>
#include <igtl/igtlClientSocket.h>
#include <sofa/simulation/AnimateBeginEvent.h>


using namespace sofa::core::objectmodel;

namespace SofaSlicer::openigtlink
{
    class iGTLinkMessageBase;

    class iGTLinkBase : public BaseObject
    {
    public:
        iGTLinkBase() { this->f_listening.setValue(true); };
        ~iGTLinkBase() = default;

        virtual bool isConnected() = 0;
        virtual bool tryConnect() = 0;
        virtual void updateMessages() final;
        virtual void handleEvent(Event* ) final;


        void addMessageObject(iGTLinkMessageBase * _object);

        void removeMessageObject(iGTLinkMessageBase * _object);

        std::map<std::string,iGTLinkMessageBase *> m_messageObjects;
        igtl::ClientSocket::Pointer m_socket;
    };
}