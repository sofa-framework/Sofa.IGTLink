#include <sofa/igtlink/utils/EngineToMState.inl>
#include <sofa/core/ObjectFactory.h>

namespace sofa::openigtlink {

SOFA_DECL_CLASS(EngineToMState)

int EngineToMStateClass = core::RegisterObject("")
.add<EngineToMState<defaulttype::Vec3Types> >(true)
.add<EngineToMState<defaulttype::Rigid3dTypes> >();

}


