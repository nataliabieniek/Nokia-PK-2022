#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    void handleDisconnected() final;
    void handleReceiveSms(common::PhoneNumber from, std::string& message) final;
    void handleSendSms(common::PhoneNumber to, const std::string& message) final;

    void handleUnknownRecipient(common::PhoneNumber from) final;

    void handleCallRequest(common::PhoneNumber from) final;
    void handleSendCallRequest(common::PhoneNumber to) final;
    void handleCallAccept(common::PhoneNumber from) final;
    void handleSendCallAccept(common::PhoneNumber from) final;
    void handleSendCallDrop(common::PhoneNumber to) final;
    void handleCallDrop(common::PhoneNumber from) final;

    void handleTimeout() final;

};

}
