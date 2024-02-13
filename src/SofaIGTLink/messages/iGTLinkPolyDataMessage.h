#pragma once

#include <SofaIGTLink/messages/iGTLinkMessage.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <igtlPolyDataMessage.h>

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

        Data<sofa::type::vector<Vec3>>                              d_points;
        Data<sofa::core::topology::Topology::SetIndices>            d_indices;
        Data<sofa::core::topology::BaseMeshTopology::SeqEdges>      d_edges;
        Data<sofa::core::topology::BaseMeshTopology::SeqTriangles>  d_triangles;
        Data<sofa::core::topology::BaseMeshTopology::SeqTetrahedra> d_tetra;
        Data<sofa::core::topology::BaseMeshTopology::SeqHexahedra>  d_hexa;
        Data<bool> d_enableIndices;
        Data<bool> d_enableEdges;
        Data<bool> d_enableTriangles;
        Data<bool> d_enableTetra;
        Data<bool> d_enableHexa;
    };
}
