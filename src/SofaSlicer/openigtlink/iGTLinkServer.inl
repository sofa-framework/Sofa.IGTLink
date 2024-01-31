#pragma once
#include <SofaSlicer/openigtlink/iGTLinkServer.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <map>


namespace SofaSlicer::openigtlink
{

iGTLinkServer::iGTLinkServer()
: d_port(initData(&d_port,"port","Name of host to connect to"))
, m_serverSocket(nullptr)
{

}

iGTLinkServer::~iGTLinkServer()
{
    m_socket->CloseSocket();
    m_serverSocket->CloseSocket();
}


void iGTLinkServer::init()
{
    tryConnect();
}


bool iGTLinkServer::tryConnect()
{
    d_componentState.setValue(ComponentState::Loading);
    if(!m_serverSocket)
    {
        m_serverSocket = igtl::ServerSocket::New();
        int r = m_serverSocket->CreateServer(d_port.getValue());
        if (r < 0)
        {
            msg_warning(this)<<std::string("Cannot create socket on port : ") + std::to_string(d_port.getValue());
            m_serverSocket = NULL;
            return false;
        }
    }
    m_socket = m_serverSocket->WaitForConnection(10);
    if(!m_socket)
    {
        std::cout << (std::string("No client connected currently on port :") + std::to_string(d_port.getValue())) <<std::endl;
        d_componentState.setValue(ComponentState::Loading);
    }
    else
    {
        std::cout << ("One client is connected")<<std::endl;
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
        d_componentState.setValue(ComponentState::Loading);
    }
    d_componentState.setValue(ComponentState::Valid);
    return connected;
}








}

