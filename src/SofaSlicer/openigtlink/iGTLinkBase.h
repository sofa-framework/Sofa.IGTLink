#pragma once

#include <mutex>

namespace SofaSlicer::openigtlink
{
    class iGTLinkBase
    {
    public:
        iGTLinkBase() = default;
        ~iGTLinkBase() = default;

        virtual bool isConnected() = 0;
        virtual bool tryConnect() = 0;

        std::mutex m_mutex;
    };
}