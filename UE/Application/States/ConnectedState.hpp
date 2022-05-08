#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    void handleDisconnected() final;

    void handleCallRequest(common::PhoneNumber from) final;
    void handleCallAccept(common::PhoneNumber from) final;

    void handleSendCallRequest(common::PhoneNumber to) final;
    void handleSendCallAccept(common::PhoneNumber from) final;
};

}
