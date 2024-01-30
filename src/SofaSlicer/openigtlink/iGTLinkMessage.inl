#pragma once


#include <SofaSlicer/openigtlink/iGTLinkMessage.h>


using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{

template<class iGTKM, class SOFAT>
iGTLinkMessage<iGTKM,SOFAT>::iGTLinkMessage()
: l_iGTLink(initLink("iGTLink","iGTLink to Client or Server"))
, d_data(initData(&d_data,"data","Data vector"))
{
    c_callBack.addInput(&d_data);
    c_callBack.addCallback([this](){
        this->setDirty(true);
    });
}

template<class iGTKM, class SOFAT>
iGTLinkMessage<iGTKM,SOFAT>::~iGTLinkMessage()
{
    if(l_iGTLink->isConnected())
        l_iGTLink->removeMessageObject(this);
}

template<class iGTKM, class SOFAT>
void iGTLinkMessage<iGTKM,SOFAT>::init()
{
    if(l_iGTLink->isConnected())
        l_iGTLink->addMessageObject(this);
}





}