#include <sofa/igtlink/utils/iGTLinkMouseInteractor.inl>
#include <sofa/core/ObjectFactory.h>

namespace sofa::openigtlink {

SOFA_DECL_CLASS(iGTLinkMouseInteractor)

int iGTLinkMouseInteractorClass = core::RegisterObject("")
                              .add<iGTLinkMouseInteractor<defaulttype::Vec3Types>>(true);

}