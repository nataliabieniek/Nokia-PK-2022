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
    virtual void handleReceiveSms(common::PhoneNumber from, std::string& message) = 0;

    virtual void handleUnknownRecipient(common::PhoneNumber from) = 0;

    virtual void handleCallRequest(common::PhoneNumber from) = 0;
    virtual void handleCallAccept(common::PhoneNumber from) = 0;
    virtual void handleCallDrop(common::PhoneNumber to) = 0;

    virtual void handleCallReceiveText(common::PhoneNumber from, std::string &text) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendSms(common::PhoneNumber to, const std::string &message) = 0;
    virtual void sendCallRequest(common::PhoneNumber to) = 0;
    virtual void sendCallAccept(common::PhoneNumber from) = 0;
    virtual void sendCallDrop(common::PhoneNumber to) = 0;

    virtual void sendCallTalk(common::PhoneNumber partnerPhoneNumber, const std::string &text) = 0;
};

}
