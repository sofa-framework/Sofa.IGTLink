#include <sofa/igtlink/utils/PickingInteractor.inl>
#include <sofa/core/ObjectFactory.h>

namespace sofa::openigtlink {

SOFA_DECL_CLASS(PickingInteractor)

int PickingInteractorClass = core::RegisterObject("")
                              .add<PickingInteractor<defaulttype::Vec3Types>>(true);

}