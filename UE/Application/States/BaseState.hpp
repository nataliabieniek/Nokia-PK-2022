#pragma once
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleReceiveSms(common::PhoneNumber from, std::string& message) override;
    void handleSendSms(common::PhoneNumber to, const std::string& message) override;

    void handleUnknownRecipient(common::PhoneNumber from) override;

    void handleCallRequest(common::PhoneNumber from) override;
    void handleSendCallRequest(common::PhoneNumber to) override;
    void handleCallAccept(common::PhoneNumber from) override;
    void handleSendCallAccept(common::PhoneNumber from) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
