#pragma once

#include "BaseState.hpp"

namespace ue
{

class NotConnectedState : public BaseState
{
public:
    explicit NotConnectedState(Context& context);
    void handleSib(common::BtsId btsId) override;

    void handleTimeout() final;
};

}
