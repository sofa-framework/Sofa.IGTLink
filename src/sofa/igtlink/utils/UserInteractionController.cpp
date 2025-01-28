#include <sofa/igtlink/utils/UserInteractionController.inl>
#include <sofa/core/ObjectFactory.h>

namespace sofa::openigtlink {

    void registerUserInteractionController(sofa::core::ObjectFactory* factory)
    {
        factory->registerObjects(sofa::core::ObjectRegistrationData("A controller setting an output stiffness to enable following data from outside position")
            .add<UserInteractionController>());
    }

}

