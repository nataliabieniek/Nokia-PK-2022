#pragma once
#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleSendSms(common::PhoneNumber to, const std::string& message) = 0;

    virtual void handleSendCallRequest(common::PhoneNumber to) = 0;

    virtual void handleSendCallAccept(common::PhoneNumber from) = 0;
    virtual void handleSendCallDrop(common::PhoneNumber from) = 0;

    virtual void handleCallSendText(common::PhoneNumber to, const std::string& text) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void setSmsEditView() = 0;
    virtual void setSmsListView() = 0;
    virtual void showNewSms() = 0;
    virtual void checkUnread() = 0;

    virtual void showDial() = 0;
//    virtual void showDialCalling(IUeGui::IDialMode dial) = 0;
    virtual void showCallRequest(common::PhoneNumber from) = 0;
    virtual void showConversationMode(common::PhoneNumber from) = 0;

    virtual void showUnknownRecipient(common::PhoneNumber from) = 0;

    virtual void showUnavailableRecipient(common::PhoneNumber &from) = 0;

    virtual void updateTalkMessages(common::PhoneNumber &from, std::string &text) = 0;
};

}
