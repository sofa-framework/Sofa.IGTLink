#pragma once

#include <map>
#include <sofa/core/objectmodel/BaseObject.h>
#include <igtlClientSocket.h>
#include <sofa/simulation/AnimateBeginEvent.h>


using namespace sofa::core::objectmodel;

namespace SofaSlicer::openigtlink
{
    class iGTLinkMessageBase;
    class iGTLinkReceiverThread;

    class iGTLinkBase : public BaseObject
    {
    public:
        iGTLinkBase();
        ~iGTLinkBase();

        virtual bool isConnected() = 0;
        virtual bool tryConnect() = 0;
        virtual void updateMessages() final;
        virtual void handleEvent(Event* ) final;


        void addMessageObject(iGTLinkMessageBase * _object);

        void removeMessageObject(iGTLinkMessageBase * _object);
        iGTLinkMessageBase* getMessageByName(const std::string& _name);

        Data<int> d_timeout;
        //TODO this is weak, we should find a way to be sender and receiver at the same time
        Data<bool> d_sender;
        std::map<std::string,iGTLinkMessageBase *> m_messageObjects;
        igtl::ClientSocket::Pointer m_socket;
        iGTLinkReceiverThread * m_receiverThread;
    };
}