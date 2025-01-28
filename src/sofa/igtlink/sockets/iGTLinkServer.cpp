#define SOFASLICER_IGTServer_CPP

#include <sofa/core/ObjectFactory.h>
#include <sofa/igtlink/sockets/iGTLinkServer.inl>

namespace sofa::openigtlink
{

void registeriGTLinkServer(sofa::core::ObjectFactory* factory)
{
    factory->registerObjects(sofa::core::ObjectRegistrationData("iGTLink Server wrapper")
        .add< iGTLinkServer >(true));
}
}
