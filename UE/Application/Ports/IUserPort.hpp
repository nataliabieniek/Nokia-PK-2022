#pragma once

#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void handleSendCallRequest(common::PhoneNumber to) = 0;
    virtual void handleSendCallAccept(common::PhoneNumber from) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;

    virtual void showDial() = 0;
    virtual void showCallRequest(common::PhoneNumber from) = 0;
    virtual void setConversationMode(common::PhoneNumber from) = 0;
};

}
