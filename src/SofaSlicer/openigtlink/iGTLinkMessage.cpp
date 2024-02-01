#include <sofa/core/ObjectFactory.h>
#include <SofaSlicer/openigtlink/iGTLinkMessage.inl>
#include <sofa/defaulttype/VecTypes.h>
#include <sofa/helper/accessor/WriteAccessor.h>
#include <sofa/type/vector.h>
#include <igtlPointMessage.h>
#include <igtlPolyDataMessage.h>

using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{


//TODO Instead of specialization, inheritence should be used to enable multi input/output messages because the number of existing messages in igtlink is small.
/****** POINT MESSAGES (FIDUCIALS) *****/
template <>
std::string iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>::templateName (const iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>* object)
{
        return "PointVector";
}

template <>
igtl::MessageBase::Pointer iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>::getiGTLinkMessage()
{
    // Create a point message
    igtl::MessageBase::Pointer pointMsg;
    pointMsg = igtl::PointMessage::New();

    igtl::PointMessage * pointPtr = static_cast<igtl::PointMessage*>(pointMsg.GetPointer());
    pointPtr->InitPack();
    pointMsg->SetDeviceName(getName());


    for(auto point: d_data.getValue())
    {
        auto igtlPoint = igtl::PointElement::New();
        igtlPoint->SetGroupName(getName().c_str());
//        igtlPoint->SetName("POINT_0");
//        igtlPoint->SetRGBA(0xFF, 0x00, 0x00, 0xFF);
//        igtlPoint->SetRadius(15.0);
//        igtlPoint->SetOwner("IMAGE_0");
        pointPtr->AddPointElement(igtlPoint);
        igtlPoint->SetPosition(point[0],point[1],point[2]);
    }
    pointPtr->Pack();
    return pointMsg;
}

template <>
void iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>::updateData(igtl::MessageBase::Pointer message)
{
    igtl::PointMessage * pointPtr = static_cast<igtl::PointMessage*>(message.GetPointer());
    pointPtr->Unpack();

//    pointPtr->GetBufferBodyPointer()
    d_data.beginEdit();

    sofa::helper::WriteAccessor data(d_data);
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
    d_data.endEdit();
}

/****** DOUBLE POINT MESSAGES (POLYDATA) *****/
template <>
std::string iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3dTypes>::templateName (const iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3dTypes>* object)
{
    return "PolyDataDouble";
}

template <>
igtl::MessageBase::Pointer iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3dTypes>::getiGTLinkMessage()
{
    // Create a point message
    igtl::MessageBase::Pointer polyDataMessage;
    polyDataMessage = igtl::PolyDataMessage::New();

    igtl::PolyDataMessage * polyPtr = static_cast<igtl::PolyDataMessage*>(polyDataMessage.GetPointer());

    polyPtr->InitPack();
    polyDataMessage->SetDeviceName(getName());

    igtl::PolyDataPointArray::Pointer pointArray;
    pointArray = igtl::PolyDataPointArray::New();
    polyPtr->SetPoints(pointArray);
    polyPtr->GetPoints()->SetNumberOfPoints(d_data.getValue().size());

    igtlFloat32 igPoint[3];
    unsigned idx=0;
    for(auto point : d_data.getValue())
    {
        igPoint[0] = (igtlFloat32) point[0];
        igPoint[1] = (igtlFloat32) point[1];
        igPoint[2] = (igtlFloat32) point[2];
        polyPtr->GetPoints()->SetPoint(idx,igPoint);
        ++idx;
    }

    polyDataMessage->Pack();
    return polyDataMessage;
}

template <>
void iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3dTypes>::updateData(igtl::MessageBase::Pointer message)
{


}

/****** FLOAT POINT MESSAGES (POLYDATA) *****/
template <>
std::string iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3fTypes>::templateName (const iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3fTypes>* object)
{
    return "PolyDataFloat";
}

template <>
igtl::MessageBase::Pointer iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3fTypes>::getiGTLinkMessage()
{

        // Create a point message
    igtl::MessageBase::Pointer polyDataMessage;
    polyDataMessage = igtl::PolyDataMessage::New();
    polyDataMessage->InitPack();
    polyDataMessage->SetDeviceName(getName());



    if(d_data.getValue().size())
    {
        igtl::PolyDataMessage *polyPtr = static_cast<igtl::PolyDataMessage *>(polyDataMessage.GetPointer());

        igtl::PolyDataPointArray::Pointer pointArray;
        pointArray = igtl::PolyDataPointArray::New();
        polyPtr->SetPoints(pointArray);
        pointArray->SetNumberOfPoints(d_data.getValue().size());

        igtlFloat32 *beginPtr;
        pointArray->GetPoint(0, beginPtr);

        sofa::helper::WriteAccessor data(d_data);


        memcpy(beginPtr, data->data(), d_data.getValue().size() * sizeof(float));
    }

    polyDataMessage->Pack();
    return polyDataMessage;
}

template <>
void iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3fTypes>::updateData(igtl::MessageBase::Pointer message)
{


}

static int iGTLinkMessageClass = sofa::core::RegisterObject("iGTLink messages")
        .add< iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types> >()
        .add< iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3fTypes> >()
        .add< iGTLinkMessage<igtl::PolyDataMessage,sofa::defaulttype::Vec3dTypes> >()
;

}