#include <sofa/igtlink/utils/PickingInteractor.inl>
#include <sofa/core/ObjectFactory.h>

namespace sofa::openigtlink {

SOFA_DECL_CLASS(PickingInteractor)

void registerPickingInteractor(sofa::core::ObjectFactory* factory)
{
    factory->registerObjects(sofa::core::ObjectRegistrationData("PickingInteractor used to enable random point picking given an input position")
                              .add<PickingInteractor<defaulttype::Vec3Types>>(true));
}

}