#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "ViewingSms.hpp"

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

void ConnectedState::handleShowSmsList() {
    context.setState<ViewingSms>();
}

}
