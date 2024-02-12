#pragma once

#include <SofaIGTLink/messages/iGTLinkMessage.h>

using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{
    template<class DataType>
    class iGTLinkPolyDataMessage : public iGTLinkMessage
    {
        typedef typename DataType::Coord Vec3;
    public:
        iGTLinkPolyDataMessage();

        virtual igtl::MessageBase::Pointer getiGTLinkMessage() ;
        virtual void updateData(igtl::MessageBase::Pointer) ;

        Data<sofa::type::vector<Vec3>> d_points;

    };
}
