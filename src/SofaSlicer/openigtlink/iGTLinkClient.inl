#pragma once
#include <SofaSlicer/openigtlink/iGTLinkClient.h>


namespace SofaSlicer::openigtlink
{

iGTLinkClient::iGTLinkClient()
: d_hostname(initData(&d_hostname,"hostname","Name of host to connect to"))
, d_port(initData(&d_port,"port","Name of host to connect to"))
{

}


void iGTLinkClient::init()
{
    m_socket = igtl::ClientSocket::New();

    tryConnect();
}

bool iGTLinkClient::tryConnect()
{
    d_componentState.setValue(ComponentState::Loading);

    int r = m_socket->ConnectToServer(d_hostname.getValue().c_str(), d_port.getValue());
    if(r == -1)
    {
        msg_warning(this) << "Socket not connected to hostname : " << d_hostname.getValue() << ":" <<d_port.getValue();
        d_componentState.setValue(ComponentState::Loading);
    }
    else
    {
        msg_info(this) <<  "Client is connected";
        d_componentState.setValue(ComponentState::Valid);
    }
    return r != -1;
}


bool iGTLinkClient::isConnected()
{
    bool connected = m_socket->GetConnected();
    if(!connected)
    {
        msg_warning(this) << "Socket not connected to hostname : " << d_hostname.getValue() << ":" <<d_port.getValue();
        d_componentState.setValue(ComponentState::Loading);
    }
    d_componentState.setValue(ComponentState::Valid);
    return connected;
}

}

