#pragma once
#include <sofa/igtlink/messages/iGTLinkMessage.h>


using namespace sofa::core::objectmodel;
namespace sofa::openigtlink
{

    iGTLinkMessage::iGTLinkMessage()
            : l_iGTLink(initLink("iGTLink","iGTLink to Client or Server"))
    {

    }

    iGTLinkMessage::~iGTLinkMessage()
    {
        if(l_iGTLink->isConnected())
            l_iGTLink->removeMessageObject(this);
    }

    void iGTLinkMessage::init()
    {
        auto dataVec = this->getDataFields();
        for(auto data : dataVec)
            c_callBack.addInput(data);

        c_callBack.addCallback([this]()
                               {
                                   this->setDirty(true);
                               });
        if(!l_iGTLink.empty())
        {
            l_iGTLink->addMessageObject(this);
        }
    }
}
