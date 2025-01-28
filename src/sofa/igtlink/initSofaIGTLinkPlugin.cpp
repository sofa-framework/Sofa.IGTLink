#include <sofa/core/ObjectFactory.h>

#include <string>
#include <sofa/igtlink/config.h>

namespace sofa
{
namespace component
{
extern "C"
{
    SOFA_IGTLINK_API void initExternalModule()
    {
        static bool first = true;
        if (first)
        {
            first = false;
        }
    }

    SOFA_IGTLINK_API const char* getModuleName() { return "SofaIGTLink"; }

    SOFA_IGTLINK_API const char* getModuleVersion() { return "0.0"; }

    SOFA_IGTLINK_API const char* getModuleLicense() { return "Private"; }

    SOFA_IGTLINK_API const char* getModuleDescription() { return "Bridge from SOFA to IGTLink"; }

    SOFA_IGTLINK_API const char* getModuleComponentList()
    {
        static std::string classes = sofa::core::ObjectFactory::getInstance()->listClassesFromTarget(sofa_tostring(SOFA_TARGET));
        return classes.c_str();
    }

}  // extern "C"

}  // namespace component
}  // namespace sofa
