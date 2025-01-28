#include <sofa/igtlink/utils/EngineToMState.inl>
#include <sofa/core/ObjectFactory.h>

namespace sofa::openigtlink {

SOFA_DECL_CLASS(EngineToMState)

void registerEngineToMState(sofa::core::ObjectFactory* factory)
{
    factory->registerObjects(sofa::core::ObjectRegistrationData("Engine to store data in mstate while dealing with correct resizing")
        .add<EngineToMState<defaulttype::Vec3Types> >(true)
        .add<EngineToMState<defaulttype::Rigid3dTypes> >());
}

}


