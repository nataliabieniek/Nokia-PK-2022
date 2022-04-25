#pragma once
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"
#include "Messages/PhoneNumber.hpp"

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

    void handleCallAccept(common::PhoneNumber from) override;
    void handleCallDrop(common::PhoneNumber from) override;
    void handleSendCallRequest(common::PhoneNumber from, common::PhoneNumber to) override;
    void handleReceiveCallRequest(common::PhoneNumber from) override;
protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
