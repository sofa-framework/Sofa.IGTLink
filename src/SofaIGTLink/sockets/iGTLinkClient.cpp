#define SOFASLICER_IGTCLIENT_CPP

#include <sofa/core/ObjectFactory.h>
#include <SofaIGTLink/sockets/iGTLinkClient.inl>

namespace SofaSlicer::openigtlink
{

static int iGTLinkClientClass = sofa::core::RegisterObject("iGTLink client wrapper")
.add< iGTLinkClient >(true)
;
}
