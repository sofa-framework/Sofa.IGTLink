#pragma once

#include "sofa/core/ObjectFactory.h"
#include <SofaIGTLink/messages/iGTLinkPointMessage.h>
#include <SofaIGTLink/messages/iGTLinkMessage.inl>
#include <igtlPointMessage.h>

using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{
template<class DataType>
iGTLinkPointMessage<DataType>::iGTLinkPointMessage()
:d_points(initData(&d_points,"points","points"))
,d_radius(initData(&d_radius,"radius","radius"))
,d_labels(initData(&d_labels,"labels","labels"))
,d_groups(initData(&d_groups,"groups","groups"))
{

}


template<class DataType>
igtl::MessageBase::Pointer iGTLinkPointMessage<DataType>::getiGTLinkMessage()
{
    // Create a point message
    igtl::MessageBase::Pointer pointMsg;
    pointMsg = igtl::PointMessage::New();

    igtl::PointMessage * pointPtr = static_cast<igtl::PointMessage*>(pointMsg.GetPointer());
    pointPtr->InitPack();
    pointMsg->SetDeviceName(getName());

    for(unsigned i=0; i<d_points.getValue().size(); ++i)
    {
        auto& point = d_points.getValue()[i];
        auto igtlPoint = igtl::PointElement::New();
        if(d_labels.getValue().size())
        {
            igtlPoint->SetName(d_labels.getValue()[i].c_str());
        }
        if(d_groups.getValue().size())
        {
            igtlPoint->SetGroupName(d_groups.getValue()[i].c_str());
        }
        if(d_radius.getValue().size())
        {
            igtlPoint->SetRadius(d_radius.getValue()[i]);
        }
        if(d_owner.getValue().size())
        {
            igtlPoint->SetOwner(d_owner.getValue()[i].c_str());
        }
        pointPtr->AddPointElement(igtlPoint);
        igtlPoint->SetPosition(point[0],point[1],point[2]);
    }
    pointPtr->Pack();
    return pointMsg;
}

template<class DataType>
void iGTLinkPointMessage<DataType>::updateData(igtl::MessageBase::Pointer message)
{
    igtl::PointMessage * pointPtr = static_cast<igtl::PointMessage*>(message.GetPointer());
    pointPtr->Unpack();

//    pointPtr->GetBufferBodyPointer()
    d_points.beginEdit();

    sofa::helper::WriteAccessor data(d_points);
    data.resize(pointPtr->GetNumberOfPointElement());
    igtlFloat32 x,y,z;

    for(unsigned i=0; i<pointPtr->GetNumberOfPointElement(); ++i)
    {
        igtl::PointElement::Pointer pointElem;
        pointPtr->GetPointElement(i,pointElem);
        pointElem->GetPosition(x,y,z);
        data[i][0] = x;
        data[i][1] = y;
        data[i][2] = z;
    }
    d_points.endEdit();
}

static int iGTLinkPointMessageInt = sofa::core::RegisterObject("iGTLink messages")
        .add< iGTLinkPointMessage<sofa::defaulttype::Vec3Types> >();

}
