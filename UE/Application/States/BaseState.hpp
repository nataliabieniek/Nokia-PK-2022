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

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
