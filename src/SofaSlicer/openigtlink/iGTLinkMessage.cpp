#include <sofa/core/ObjectFactory.h>
#include <SofaSlicer/openigtlink/iGTLinkMessage.inl>
#include <sofa/defaulttype/VecTypes.h>
#include <sofa/type/vector.h>
#include <igtlPointMessage.h>

using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{

template <>
std::string iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>::templateName (const iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>* object)
{
    return "Vec3Types";
}

template <>
igtl::MessageBase::Pointer iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>::getiGTLinkMessage()
{

    // Create a point message
    igtl::MessageBase::Pointer pointMsg;
    pointMsg = igtl::PointMessage::New();
    pointMsg->SetDeviceName(getName());

    igtl::PointMessage * pointPtr = static_cast<igtl::PointMessage*>(pointMsg.GetPointer());

    for(auto point: d_data.getValue())
    {
        auto igtlPoint = igtl::PointElement::New();
        igtlPoint->SetPosition(point[0],point[1],point[3]);
//        igtlPoint->SetName("POINT_0");
//        igtlPoint->SetGroupName("GROUP_0");
//        igtlPoint->SetRGBA(0xFF, 0x00, 0x00, 0xFF);
//        igtlPoint->SetRadius(15.0);
//        igtlPoint->SetOwner("IMAGE_0");
        pointPtr->AddPointElement(igtlPoint);
    }
    return pointMsg;
}

template <>
void iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>::updateData(igtl::MessageBase::Pointer)
{

}

static int iGTLinkMessageClass = sofa::core::RegisterObject("iGTLink messages")
        .add< iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types> >()
;

}