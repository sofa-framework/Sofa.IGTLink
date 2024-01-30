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

}

template <>
void iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types>::updateData(igtl::MessageBase::Pointer)
{

}

static int iGTLinkMessageClass = sofa::core::RegisterObject("iGTLink messages")
        .add< iGTLinkMessage<igtl::PointMessage,sofa::defaulttype::Vec3Types> >()
;

}