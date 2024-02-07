#include <SofaIGTLink/utils/EngineToTopology.inl>
#include <sofa/core/ObjectFactory.h>

namespace sofa {

namespace registrationcst {

SOFA_DECL_CLASS(EngineToTopology)

template <>
std::string EngineToTopology<defaulttype::Vec3Types>::templateName(const EngineToTopology<defaulttype::Vec3Types> *)
{
    return "Vec3d";
}
template class EngineToTopology<defaulttype::Vec3Types>;

template <>
std::string EngineToTopology<defaulttype::Rigid3dTypes>::templateName(const EngineToTopology<defaulttype::Rigid3dTypes> *)
{
    return "Rigid3d";
}
template class EngineToTopology<defaulttype::Rigid3dTypes>;

int EngineToTopologyClass = core::RegisterObject("")
.add<EngineToTopology<defaulttype::Vec3Types> >(true)
.add<EngineToTopology<defaulttype::Rigid3dTypes> >();

}

}

