#pragma once

#include <SofaSlicer/openigtlink/messages/iGTLinkMessage.h>

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

        Data<std::vector<Vec3>> d_points;
        Data<std::vector<double>> d_radius;
        Data<std::vector<std::string>> d_labels;
        Data<std::vector<std::string>> d_groups;
        Data<std::vector<std::string>> d_owner;
    };
}