#pragma once

#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/objectmodel/Data.h>
#include <sofa/core/objectmodel/DataLink.h>
#include <sofa/core/objectmodel/Link.h>
#include <sofa/core/objectmodel/DataCallback.h>
#include <igtlMessageBase.h>
#include <SofaSlicer/openigtlink/iGTLinkBase.h>


using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{

    class iGTLinkMessageBase : public BaseObject
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

    template<class iGTKM, class SOFAT>
    class iGTLinkMessage : public iGTLinkMessageBase
    {
        typedef typename SOFAT::VecCoord VecCoord;

    public:
        SOFA_CLASS(SOFA_TEMPLATE2(iGTLinkMessage,iGTKM,SOFAT),iGTLinkMessageBase);

        iGTLinkMessage();
        ~iGTLinkMessage();

        SingleLink<iGTLinkMessage<iGTKM, SOFAT>, iGTLinkBase, BaseLink::FLAG_STOREPATH | BaseLink::FLAG_STRONGLINK> l_iGTLink;

        void init();

        igtl::MessageBase::Pointer getiGTLinkMessage();
        void updateData(igtl::MessageBase::Pointer);


        static std::string templateName(const iGTLinkMessage<iGTKM, SOFAT>* = nullptr) { return "Unknown"; }

    private:
        DataCallback c_callBack;
        Data<VecCoord> d_data;
    };

}