#define SOFASLICER_IGTServer_CPP

#include <sofa/core/ObjectFactory.h>
#include <SofaSlicer/openigtlink/iGTLinkServer.inl>

namespace SofaSlicer::openigtlink
{

    static int iGTLinkServerClass = sofa::core::RegisterObject("iGTLink Server wrapper")
            .add< iGTLinkServer >(true)
    ;
}