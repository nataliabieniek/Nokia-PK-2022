#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    void handleDisconnected() final;

    void handleCallRequest(common::PhoneNumber from);
};

}
