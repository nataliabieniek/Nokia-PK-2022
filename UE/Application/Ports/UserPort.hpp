#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Sms/SmsDb.hpp"

namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber, SmsDb& smsDB);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void setSmsEditView() override;
    void setSmsListView() override;
    void showNewSms() override;
    void checkUnread() override;

    void showDial() override;
    void showCallRequest(common::PhoneNumber from) override;
    void showConversationMode(common::PhoneNumber from) override;

    void showUnknownRecipient(common::PhoneNumber from) override;

    void showUnavailableRecipient(common::PhoneNumber &from) override;
    void updateTalkMessages(common::PhoneNumber &from, std::string &text) override;


private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    SmsDb& smsDB;
    IUserEventsHandler* handler = nullptr;

    void showSmsList();
};

}
