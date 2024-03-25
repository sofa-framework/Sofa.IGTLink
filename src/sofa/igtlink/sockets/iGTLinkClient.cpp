#define SOFASLICER_IGTCLIENT_CPP

#include <sofa/core/ObjectFactory.h>
#include <sofa/igtlink/sockets/iGTLinkClient.inl>

namespace sofa::openigtlink
{

static int iGTLinkClientClass = sofa::core::RegisterObject("iGTLink client wrapper")
.add< iGTLinkClient >(true)
;
}
