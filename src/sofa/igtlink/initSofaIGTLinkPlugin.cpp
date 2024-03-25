#include <sofa/core/ObjectFactory.h>

#include <string>

namespace sofa
{
namespace component
{
extern "C"
{
    void initExternalModule()
    {
        static bool first = true;
        if (first)
        {
            first = false;
        }
    }

    const char* getModuleName() { return "SofaIGTLink"; }

    const char* getModuleVersion() { return "0.0"; }

    const char* getModuleLicense() { return "Private"; }

    const char* getModuleDescription() { return "Bridge from SOFA to IGTLink"; }

    const char* getModuleComponentList()
    {
        static std::string classes = sofa::core::ObjectFactory::getInstance()->listClassesFromTarget(sofa_tostring(SOFA_TARGET));
        return classes.c_str();
    }

}  // extern "C"

}  // namespace component
}  // namespace sofa
