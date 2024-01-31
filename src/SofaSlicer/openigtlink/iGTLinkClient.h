#pragma once
#include <sofa/core/objectmodel/Data.h>

#include <string>

#include <igtl/igtlOSUtil.h>
#include <igtl/igtlPointMessage.h>
#include <SofaSlicer/openigtlink/iGTLinkBase.h>

using namespace sofa::core::objectmodel;

namespace SofaSlicer::openigtlink
{
    class iGTLinkClient : public iGTLinkBase
    {
    public:
        iGTLinkClient();
        ~iGTLinkClient() = default;

        void init();

        virtual bool tryConnect();
        virtual bool isConnected();

    private:
        Data<std::string> d_hostname;
        Data<int> d_port;

    };
}

