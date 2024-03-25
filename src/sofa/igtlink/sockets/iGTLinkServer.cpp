#define SOFASLICER_IGTServer_CPP

#include <sofa/core/ObjectFactory.h>
#include <sofa/igtlink/sockets/iGTLinkServer.inl>

namespace sofa::openigtlink
{

    static int iGTLinkServerClass = sofa::core::RegisterObject("iGTLink Server wrapper")
            .add< iGTLinkServer >(true)
    ;
}
