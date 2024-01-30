#pragma once
#include <SofaSlicer/openigtlink/iGTLinkServer.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <map>


namespace SofaSlicer::openigtlink
{

iGTLinkServer::iGTLinkServer()
: d_port(initData(&d_port,"hostname","Name of host to connect to"))
, m_serverSocket(nullptr)
{

}


void iGTLinkServer::init()
{
    tryConnect();
}


bool iGTLinkServer::tryConnect()
{
    if(!m_serverSocket)
    {
        m_serverSocket = igtl::ServerSocket::New();
        int r = m_serverSocket->CreateServer(d_port.getValue());
        if (r < 0)
        {
            msg_warning(std::string("Cannot create socket on port : ") + std::to_string(d_port.getValue()));
            m_serverSocket = NULL;
            return false;
        }
    }
    m_socket = m_serverSocket->WaitForConnection(10);
    if(!m_socket)
    {
        msg_warning(std::string("No client connected currently on port :") + std::to_string(d_port.getValue()));
        d_componentState.setValue(ComponentState::Invalid);
    }
    else
    {
        d_componentState.setValue(ComponentState::Valid);

    }
    return m_socket;
}


bool iGTLinkServer::isConnected()
{
    bool connected = m_socket->GetConnected();
    if(!connected)
    {
        msg_warning(std::string("Socket not connected to port : ") + std::to_string(d_port.getValue()));
        d_componentState.setValue(ComponentState::Invalid);
    }
    return connected;
}

void iGTLinkServer::handleEvent(Event *event)
{

    if(sofa::simulation::AnimateBeginEvent::checkEventType(event))
    {
        if(d_componentState.getValue()!=ComponentState::Valid)
        {
            if(!tryConnect()) return;
        }
        sendMessages();
    }
}

void iGTLinkServer::addMessageObject(iGTLinkMessageBase * _object)
{
    if(m_messageObjects.find(_object->getName()) == m_messageObjects.end())
    {
        m_messageObjects[_object->getName()] = _object;
    }
    else
    {
        msg_warning(std::string("Message with name ") + _object->getName() + " already exists.");
    }
}

void iGTLinkServer::removeMessageObject(iGTLinkMessageBase * _object)
{
    m_messageObjects.erase(_object->getName());
}

void iGTLinkServer::sendMessages()
{

}



}

