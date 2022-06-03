#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
    bool isTalking = false;
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

    void handleCallReceiveText(common::PhoneNumber from, std::string &text) final;
    void handleCallSendText(common::PhoneNumber to, const std::string& text) final;

    void handleTimeout() final;

    void handleCallReceiveText(common::PhoneNumber from, std::string &text) final;
    void handleCallSendText(common::PhoneNumber to, const std::string& text) final;

};

}
