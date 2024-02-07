#pragma once

#include <SofaIGTLink/messages/iGTLinkMessage.h>

using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{
    template<class DataType>
    class iGTLinkPointMessage : public iGTLinkMessage
    {
        typedef typename DataType::Coord Vec3;
    public:
        iGTLinkPointMessage();

        virtual igtl::MessageBase::Pointer getiGTLinkMessage() ;
        virtual void updateData(igtl::MessageBase::Pointer) ;

        Data<sofa::type::vector<Vec3>> d_points;
        Data<sofa::type::vector<double>> d_radius;
        Data<sofa::type::vector<std::string>> d_labels;
        Data<sofa::type::vector<std::string>> d_groups;
        Data<sofa::type::vector<std::string>> d_owner;
    };
}
