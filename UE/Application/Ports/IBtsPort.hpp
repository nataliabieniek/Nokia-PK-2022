#pragma once

#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleDisconnected() = 0;

    virtual void handleCallRequest(common::PhoneNumber) = 0;
    virtual void handleCallAccept(common::PhoneNumber from) =0;

    virtual void handleReceiveCallRequest(common::PhoneNumber from) = 0;
    virtual void handleCallDrop(common::PhoneNumber) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendCallRequest(common::PhoneNumber to) = 0;
    virtual void sendCallAccept(common::PhoneNumber from) = 0;
};

}
