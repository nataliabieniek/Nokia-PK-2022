#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleCallRequest(common::PhoneNumber from) {
    logger.logInfo("Received call request from ", from);
}

void ConnectedState::handleSendCallRequest(common::PhoneNumber to) {
    using namespace std::chrono_literals;
    context.timer.startTimer(60000ms);
    context.bts.sendCallRequest(to);
}

}
