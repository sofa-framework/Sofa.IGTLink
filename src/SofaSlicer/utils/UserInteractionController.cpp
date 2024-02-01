#include <SofaSlicer/utils/UserInteractionController.inl>
#include <sofa/core/ObjectFactory.h>

namespace SofaSlicer {

int UserInteractionControllerClass = sofa::core::RegisterObject("")
.add<UserInteractionController>();

}

