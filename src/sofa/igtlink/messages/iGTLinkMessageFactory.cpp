//
// Created by paul on 27/01/25.
//

#include <sofa/igtlink/messages/iGTLinkMessageFactory.h>
namespace sofa::openigtlink
{
    iGTLinkMessageFactory* iGTLinkMessageFactory::getFactory()
    {
        static iGTLinkMessageFactory * factory = nullptr;
        if (factory == nullptr)
        {
            factory = new iGTLinkMessageFactory;
        }
        return factory;
    }

}