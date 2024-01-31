#include <SofaSlicer/openigtlink/iGTLinkBase.h>
#include <SofaSlicer/openigtlink/iGTLinkMessage.h>


namespace SofaSlicer::openigtlink
{
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

    void iGTLinkBase::updateMessages()
    {
        //TODO unpack data comming from thread


        for(auto it : m_messageObjects)
        {
            if(it.second->getDirty())
            {
                auto message = it.second->getiGTLinkMessage();
                int success = m_socket->Send(message->GetPackPointer(), message->GetPackSize());
                it.second->setDirty(false);
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