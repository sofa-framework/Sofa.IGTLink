#define SOFASLICER_IGTCLIENT_CPP

#include <sofa/core/ObjectFactory.h>
#include <sofa/igtlink/sockets/iGTLinkClient.inl>

namespace sofa::openigtlink
{

void registeriGTLinkClient(sofa::core::ObjectFactory* factory)
{
    factory->registerObjects(sofa::core::ObjectRegistrationData("iGTLink client wrapper")
            .add< iGTLinkClient >(true));
}

}
