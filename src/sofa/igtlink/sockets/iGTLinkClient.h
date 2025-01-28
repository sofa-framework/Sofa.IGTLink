#pragma once
#include <sofa/core/objectmodel/Data.h>
#include <sofa/igtlink/config.h>

#include <string>

#include <igtlOSUtil.h>
#include <igtlPointMessage.h>
#include <sofa/igtlink/sockets/iGTLinkBase.h>

using namespace sofa::core::objectmodel;

namespace sofa::openigtlink
{
    class SOFA_IGTLINK_API iGTLinkClient : public iGTLinkBase
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

