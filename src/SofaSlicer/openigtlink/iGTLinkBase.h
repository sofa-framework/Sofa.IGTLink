#pragma once

#include <mutex>
#include <map>
#include <sofa/core/objectmodel/BaseObject.h>


using namespace sofa::core::objectmodel;

namespace SofaSlicer::openigtlink
{
    class iGTLinkMessageBase;

    class iGTLinkBase : public BaseObject
    {
    public:
        iGTLinkBase() = default;
        ~iGTLinkBase() = default;

        virtual bool isConnected() = 0;
        virtual bool tryConnect() = 0;


        void addMessageObject(iGTLinkMessageBase * _object);

        void removeMessageObject(iGTLinkMessageBase * _object);

        std::map<std::string,iGTLinkMessageBase *> m_messageObjects;
        std::mutex m_mutex;
    };
}