#pragma once
#include <SofaSlicer/openigtlink/iGTLinkClient.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <sofa/simulation/AnimateBeginEvent.h>


namespace SofaSlicer::openigtlink
{

iGTLinkClient::iGTLinkClient()
: d_hostname(initData(&d_hostname,"hostname","Name of host to connect to"))
, d_port(initData(&d_hostname,"hostname","Name of host to connect to"))
{

}


void iGTLinkClient::init()
{
    m_socket = igtl::ClientSocket::New();

    tryConnect();
}

bool iGTLinkClient::tryConnect()
{
    int r = m_socket->ConnectToServer(d_hostname.getValue().c_str(), d_port.getValue());
    if(!r)
    {
        msg_warning(std::string("Socket not connected to hostname : ") + d_hostname.getValue() + ":" + std::to_string(d_port.getValue()));
        d_componentState.setValue(ComponentState::Invalid);
    }
    return r;
}


bool iGTLinkClient::isConnected()
{
    bool connected = m_socket->GetConnected();
    if(!connected)
    {
        msg_warning(std::string("Socket not connected to hostname : ") + d_hostname.getValue() + ":" + std::to_string(d_port.getValue()));
        d_componentState.setValue(ComponentState::Invalid);
    }
    else
    {
        d_componentState.setValue(ComponentState::Valid);
    }
    return connected;
}

void iGTLinkClient::handleEvent(Event *event)
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

void iGTLinkClient::updateMessages()
{
//    for(auto slave : getMessagesObjects())
//    {
//
//    }
}



}

