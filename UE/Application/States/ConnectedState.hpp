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

};

}
