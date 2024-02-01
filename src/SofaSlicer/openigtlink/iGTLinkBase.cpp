#include <SofaSlicer/openigtlink/iGTLinkBase.h>
#include <SofaSlicer/openigtlink/iGTLinkMessage.h>
#include <SofaSlicer/openigtlink/iGTLinkThread.h>


namespace SofaSlicer::openigtlink
{
    iGTLinkBase::iGTLinkBase()
    : d_timeout(initData(&d_timeout,-1,"timeout","Timeout in milliseconds"))
    , d_sender(initData(&d_sender,false,"sender","Are you a sender"))
    , m_receiverThread(nullptr)
    {
        if(!d_sender.getValue())
            m_receiverThread = new iGTLinkReceiverThread(this);
        this->f_listening.setValue(true);
    }


    iGTLinkBase::~iGTLinkBase()
    {
        m_receiverThread ->stopThread();
        delete m_receiverThread;
    }

    void iGTLinkBase::addMessageObject(iGTLinkMessageBase *_object)
    {
        if (m_messageObjects.find(_object->getName()) == m_messageObjects.end())
        {
            m_messageObjects[_object->getName()] = _object;
        }
        else
        {
            msg_warning(std::string("Message with name ") + _object->getName() + " already exists.");
        }
    }

    void iGTLinkBase::removeMessageObject(iGTLinkMessageBase *_object)
    {
        m_messageObjects.erase(_object->getName());
    }

    iGTLinkMessageBase* iGTLinkBase::getMessageByName(const std::string& _name)
    {
        auto it = m_messageObjects.find(_name);
        if (it == m_messageObjects.end())
            return nullptr;
        else
            return it->second;
    }


    void iGTLinkBase::updateMessages()
    {
        if(!d_sender.getValue())
        {
            if (!m_receiverThread->threadRunning())
            {
                m_receiverThread->launchThread();
            }
            if (m_receiverThread->isDataAvailable())
            {
                std::map<std::string, igtl::MessageBase::Pointer> &data = m_receiverThread->getAvailableData();
                for (auto &dataMessage: data)
                {
                    auto registeredMessage = getMessageByName(dataMessage.first);
                    if (registeredMessage)
                        registeredMessage->updateData(dataMessage.second);
                }
            }
        }
        else
        {
            for(auto it : m_messageObjects)
            {
                if(it.second->getDirty())
                {
                    auto message = it.second->getiGTLinkMessage();
                    m_socket->Send(message->GetPackPointer(), message->GetPackSize());
                    it.second->setDirty(false);
                }
            }
        }
    }

    void iGTLinkBase::handleEvent(Event *event)
    {
        if(sofa::simulation::AnimateBeginEvent::checkEventType(event))
        {
            if(d_componentState.getValue()!=ComponentState::Valid)
            {
                if(!tryConnect()) return;
            }
            updateMessages();
        }
    }
}