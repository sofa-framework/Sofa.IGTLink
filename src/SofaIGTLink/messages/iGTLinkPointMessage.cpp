#pragma once

#include "sofa/core/ObjectFactory.h"
#include <SofaIGTLink/messages/iGTLinkPointMessage.h>
#include <igtlPointMessage.h>

using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{
template<class DataType>
iGTLinkPointMessage<DataType>::iGTLinkPointMessage()
: d_points(initData(&d_points,"points","points"))
, d_radius(initData(&d_radius,"radius","radius"))
, d_labels(initData(&d_labels,"labels","labels"))
, d_groups(initData(&d_groups,"groups","groups"))
, d_owners(initData(&d_owners,"owners","owner"))
, d_enableRadius(initData(&d_enableRadius,true,"enableRadius","If false, the radius will not be either packed or unpacked"))
, d_enableLabels(initData(&d_enableLabels,true,"enableLabels","If false, the labels will not be either packed or unpacked"))
, d_enableGroups(initData(&d_enableGroups,true,"enableGroups","If false, the groups will not be either packed or unpacked"))
, d_enableOwners(initData(&d_enableOwners,true,"enableOwners","If false, the owners will not be either packed or unpacked"))
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

        // Careful size is not checked to save time
        if(d_enableLabels.getValue())
            igtlPoint->SetName(d_labels.getValue()[i].c_str());
        if(d_enableGroups.getValue())
            igtlPoint->SetGroupName(d_groups.getValue()[i].c_str());
        if(d_enableRadius.getValue())
            igtlPoint->SetRadius(d_radius.getValue()[i]);
        if(d_enableOwners.getValue())
            igtlPoint->SetOwner(d_owners.getValue()[i].c_str());

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

    sofa::helper::WriteAccessor dataPoints(d_points);
    sofa::helper::WriteAccessor dataRadius(d_radius);
    sofa::helper::WriteAccessor dataLabels(d_labels);
    sofa::helper::WriteAccessor dataGroups(d_groups);
    sofa::helper::WriteAccessor dataOwners(d_owners);


    d_points.beginEdit();
    if(d_enableLabels.getValue())
    {
        d_labels.beginEdit();
        dataLabels.resize(pointPtr->GetNumberOfPointElement());
    }
    if(d_enableGroups.getValue())
    {
        d_groups.beginEdit();
        dataGroups.resize(pointPtr->GetNumberOfPointElement());
    }
    if(d_enableRadius.getValue())
    {
        d_radius.beginEdit();
        dataRadius.resize(pointPtr->GetNumberOfPointElement());
    }
    if(d_enableOwners.getValue())
    {
        d_owners.beginEdit();
        dataOwners.resize(pointPtr->GetNumberOfPointElement());
    }


    dataPoints.resize(pointPtr->GetNumberOfPointElement());
    igtlFloat32 x,y,z;

    for(unsigned i=0; i<pointPtr->GetNumberOfPointElement(); ++i)
    {
        igtl::PointElement::Pointer pointElem;
        pointPtr->GetPointElement(i,pointElem);
        pointElem->GetPosition(x,y,z);

        dataPoints[i][0] = x;
        dataPoints[i][1] = y;
        dataPoints[i][2] = z;

        if(d_enableLabels.getValue())
            dataLabels[i] = pointElem->GetName();
        if(d_enableGroups.getValue())
            dataGroups[i] = pointElem->GetGroupName();
        if(d_enableRadius.getValue())
            dataRadius[i] = pointElem->GetRadius();
        if(d_enableOwners.getValue())
            dataOwners[i] = pointElem->GetOwner();

    }

    d_points.endEdit();
    if(d_enableLabels.getValue())
        d_labels.endEdit();
    if(d_enableGroups.getValue())
        d_groups.endEdit();
    if(d_enableRadius.getValue())
        d_radius.endEdit();
    if(d_enableOwners.getValue())
        d_owners.endEdit();
}

static int iGTLinkPointMessageInt = sofa::core::RegisterObject("iGTLink messages")
        .add< iGTLinkPointMessage<sofa::defaulttype::Vec3Types> >();

}
