#pragma once

#include "sofa/core/ObjectFactory.h"
#include <SofaIGTLink/messages/iGTLinkPolyDataMessage.h>
#include <igtlPolyDataMessage.h>

using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{
template<class DataType>
iGTLinkPolyDataMessage<DataType>::iGTLinkPolyDataMessage()
:d_points(initData(&d_points,"points","points"))
{

}


template<class DataType>
igtl::MessageBase::Pointer iGTLinkPolyDataMessage<DataType>::getiGTLinkMessage()
{
//    igtl::MessageBase::Pointer polyDataMessage;
//    polyDataMessage = igtl::PolyDataMessage::New();
//
//    igtl::PolyDataMessage * polyPtr = static_cast<igtl::PolyDataMessage*>(polyDataMessage.GetPointer());
//
//    polyPtr->InitPack();
//    polyDataMessage->SetDeviceName(getName());
//
//    igtl::PolyDataPointArray::Pointer pointArray;
//    pointArray = igtl::PolyDataPointArray::New();
//    polyPtr->SetPoints(pointArray);
//    polyPtr->GetPoints()->SetNumberOfPoints(d_data.getValue().size());
//
//    igtlFloat32 igPoint[3];
//    unsigned idx=0;
//    for(auto point : d_data.getValue())
//    {
//        igPoint[0] = (igtlFloat32) point[0];
//        igPoint[1] = (igtlFloat32) point[1];
//        igPoint[2] = (igtlFloat32) point[2];
//        polyPtr->GetPoints()->SetPoint(idx,igPoint);
//        ++idx;
//    }
//
//    polyDataMessage->Pack();
//    return polyDataMessage;
}

template<class DataType>
void iGTLinkPolyDataMessage<DataType>::updateData(igtl::MessageBase::Pointer message)
{

}

static int iGTLinkPolyDataMessageInt = sofa::core::RegisterObject("iGTLink messages")
        .add< iGTLinkPolyDataMessage<sofa::defaulttype::Vec3Types> >();

}
