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
    using namespace std::chrono_literals;
    context.timer.startTimer(30000ms);
    context.user.showCallRequest(from);
}

void ConnectedState::handleSendCallRequest(common::PhoneNumber to) {
    using namespace std::chrono_literals;
    context.timer.startTimer(60000ms);
    context.bts.sendCallRequest(to);
}

void ConnectedState::handleCallAccept(common::PhoneNumber from) {
    context.timer.stopTimer();
    context.user.setConversationMode(from);
}

void ConnectedState::handleSendCallAccept(common::PhoneNumber from) {
    context.timer.stopTimer();
    context.bts.sendCallAccept(from);
}

}
