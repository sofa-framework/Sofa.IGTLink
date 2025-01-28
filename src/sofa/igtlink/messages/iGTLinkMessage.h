#pragma once

#include "sofa/core/objectmodel/BaseObject.h"
#include "sofa/core/objectmodel/Data.h"
#include "sofa/core/objectmodel/DataLink.h"
#include "sofa/core/objectmodel/Link.h"
#include "sofa/core/objectmodel/DataCallback.h"
#include <igtlMessageBase.h>
#include <sofa/igtlink/sockets/iGTLinkBase.h>
#include <sofa/igtlink/config.h>


using namespace sofa::core::objectmodel;
namespace sofa::openigtlink
{

    class SOFA_IGTLINK_API iGTLinkMessageBase : public BaseObject
    {
    public:
        SOFA_CLASS(iGTLinkMessageBase,BaseObject);

        iGTLinkMessageBase() : m_isDirty(false) {};

        virtual igtl::MessageBase::Pointer getiGTLinkMessage() = 0;
        virtual void updateData(igtl::MessageBase::Pointer) = 0;

        void setDirty(bool _dirty)
        {
            m_isDirty = true;
        }

        const bool getDirty() const
        {
            return m_isDirty;
        }

    private:
        bool m_isDirty;
    };

    class SOFA_IGTLINK_API iGTLinkMessage : public iGTLinkMessageBase
    {
    public:
        SOFA_CLASS(iGTLinkMessage,iGTLinkMessageBase);

        iGTLinkMessage();
        ~iGTLinkMessage();

        SingleLink<iGTLinkMessage, iGTLinkBase, BaseLink::FLAG_STOREPATH | BaseLink::FLAG_STRONGLINK> l_iGTLink;

        void init();

        igtl::MessageBase::Pointer getiGTLinkMessage() = 0;
        void updateData(igtl::MessageBase::Pointer) = 0;


        static std::string templateName(const iGTLinkMessage* = nullptr) { return "Unknown"; }

    private:
        DataCallback c_callBack;
    };

}
