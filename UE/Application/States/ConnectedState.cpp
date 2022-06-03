#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "ViewingSms.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
    context.timer.stopTimer();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}
void ConnectedState::handleReceiveSms(common::PhoneNumber from, std::string& message)
{
    Sms newSms{from, context.phoneNumber, message};
    context.smsDB.addSmsToDB(newSms);
    context.user.showNewSms();
}

void ConnectedState::handleSendSms(common::PhoneNumber to, const std::string& message)
{
    Sms newSms{context.phoneNumber, to, message};
    newSms.setSmsIsViewed();
    context.smsDB.addSmsToDB(newSms);
    context.bts.sendSms(to, message);
}

void ConnectedState::handleUnknownRecipient(common::PhoneNumber from)
{
    //context.smsDB.setUnknownRecipient();
    context.user.showUnknownRecipient(from);
}

void ConnectedState::handleCallRequest(common::PhoneNumber from)
{
    using namespace std::chrono_literals;
    context.timer.startTimer(30000ms);
    context.user.showCallRequest(from);
}

void ConnectedState::handleSendCallRequest(common::PhoneNumber to) {
    using namespace std::chrono_literals;
    context.timer.startTimer(60s);
    context.bts.sendCallRequest(to);
}

void ConnectedState::handleCallAccept(common::PhoneNumber from)
{
    context.timer.stopTimer();
    context.user.showConversationMode(from);
}

void ConnectedState::handleSendCallAccept(common::PhoneNumber from)
{
    context.timer.stopTimer();
    logger.logInfo(from);
    context.bts.sendCallAccept(from);
}

void ConnectedState::handleSendCallDrop(common::PhoneNumber to)
{
    context.user.showConnected();
    context.timer.stopTimer();
    context.bts.sendCallDrop(to);
}

void ConnectedState::handleCallDrop(common::PhoneNumber from)
{
    context.timer.stopTimer();
    context.user.showConnected();
}



}
