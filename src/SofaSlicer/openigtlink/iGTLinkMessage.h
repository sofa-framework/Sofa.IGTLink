#pragma once

#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/objectmodel/Data.h>
#include <sofa/core/objectmodel/DataCallback.h>
#include <igtlMessageBase.h>


using namespace sofa::core::objectmodel;
namespace SofaSlicer::openigtlink
{

    class iGTLinkMessageBase : public BaseObject
    {
    public:
        virtual igtl::MessageBase::Pointer getiGTLinkMessage() = 0;
        virtual void updateData(igtl::MessageBase::Pointer) = 0;
    };

    template<class iGTKM, class SOFAT>
    class iGTLinkMessage : public iGTLinkMessageBase
    {
        typedef SOFAT::Coord Coord;

    public:

        iGTLinkMessage();
        ~iGTLinkMessage() = default;

        virtual igtl::MessageBase::Pointer getiGTLinkMessage();
        virtual void updateData(igtl::MessageBase::Pointer);

        void setDirty(bool);
        const bool getDirty() const;

        static std::string templateName(const iGTLinkMessage<iGTKM, SOFAT>* = nullptr) { return "Unknown"; }

    private:
        DataCallback c_callBack;
        Data<Coord> d_data;
        bool m_isDirty;
    };

}