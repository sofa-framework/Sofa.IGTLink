#pragma once


#include <SofaSlicer/openigtlink/iGTLinkMessage.h>


using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{
template<class iGTKM, class SOFAT>
iGTLinkMessage<iGTKM,SOFAT>::iGTLinkMessage()
{
    c_callBack.addInput(&d_data);
    c_callBack.addCallback([this](){
        this->setDirty(true);
    });
}

template<class iGTKM, class SOFAT>
void iGTLinkMessage<iGTKM,SOFAT>::setDirty(bool _dirty)
{
    m_isDirty = true;
}

template<class iGTKM, class SOFAT>
const bool iGTLinkMessage<iGTKM,SOFAT>::getDirty() const
{
    return m_isDirty;
}



}