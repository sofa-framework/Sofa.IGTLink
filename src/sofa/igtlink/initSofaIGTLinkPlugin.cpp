#include <sofa/core/ObjectFactory.h>
#include <sofa/helper/system/PluginManager.h>
#include <string>
#include <sofa/igtlink/config.h>

namespace sofa
{
namespace openigtlink
{
extern void registeriGTLinkPointMessage(sofa::core::ObjectFactory* factory);
extern void registeriGTLinkPolyDataMessage(sofa::core::ObjectFactory* factory);
extern void registeriGTLinkClient(sofa::core::ObjectFactory* factory);
extern void registeriGTLinkServer(sofa::core::ObjectFactory* factory);
extern void registerEngineToMState(sofa::core::ObjectFactory* factory);
extern void registerPickingInteractor(sofa::core::ObjectFactory* factory);
extern void registerUserInteractionController(sofa::core::ObjectFactory* factory);

extern "C"
{

    SOFA_IGTLINK_API void initExternalModule()
    {
        static bool first = true;
        if (first)
        {
            sofa::helper::system::PluginManager::getInstance().registerPlugin(MODULE_NAME);
            first = false;
        }
    }

    SOFA_IGTLINK_API const char* getModuleName() { return MODULE_NAME; }

    SOFA_IGTLINK_API const char* getModuleVersion() { return "0.0"; }

    SOFA_IGTLINK_API const char* getModuleLicense() { return "Private"; }

    SOFA_IGTLINK_API const char* getModuleDescription() { return "Bridge from SOFA to IGTLink"; }

    SOFA_IGTLINK_API const char* getModuleComponentList()
    {
        static std::string classes = sofa::core::ObjectFactory::getInstance()->listClassesFromTarget(sofa_tostring(SOFA_TARGET));
        return classes.c_str();
    }

    SOFA_IGTLINK_API void registerObjects(sofa::core::ObjectFactory* factory)
    {
        registeriGTLinkPointMessage(factory);
        registeriGTLinkPolyDataMessage(factory);
        registeriGTLinkClient(factory);
        registeriGTLinkServer(factory);
        registerEngineToMState(factory);
        registerPickingInteractor(factory);
        registerUserInteractionController(factory);
    }

}  // extern "C"

}  // namespace openigtlink
}  // namespace sofa
