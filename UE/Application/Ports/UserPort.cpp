#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/ICallMode.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Sms/SmsDb.hpp"
#include <algorithm>

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber, SmsDb& smsDB)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber),
      smsDB(smsDB)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Call","");

    gui.setAcceptCallback([&](){
        auto index = gui.setListViewMode().getCurrentItemIndex();

        switch (index.second) {
            case 0:
                logger.logInfo("Compose SMS");
                setSmsEditView();
                break;
            case 1:
                logger.logInfo("View SMS");
                setSmsListView();
                break;
            case 2:
                logger.logInfo("Dial mode");
                showDial();
                break;
        }
    });
    gui.setRejectCallback([]{});
}

void UserPort::setSmsEditView()
{
    IUeGui::ISmsComposeMode& smsView = gui.setSmsComposeMode();
    smsView.clearSmsText();
    gui.setAcceptCallback([&]() {
        handler->handleSendSms(smsView.getPhoneNumber(), smsView.getSmsText());
        logger.logInfo(smsView.getSmsText());
        smsView.clearSmsText();
        showConnected();
    });
    gui.setRejectCallback([&]() {
        smsView.clearSmsText();
        showConnected();
    });
}

void UserPort::setSmsListView()
{
    IUeGui::IListViewMode& smsListView = gui.setListViewMode();

    smsListView.clearSelectionList();
    std::vector<Sms>& smsList = smsDB.getSmsList();

    if(smsList.empty()){
        IUeGui::ITextMode& emptyList = gui.setViewTextMode();
        emptyList.setText("No one like you :'( \n It's empty.");
    } else {
        for(auto sms: smsList) {
            if(sms.isUnknownRecipient()) {
                smsListView.addSelectionListItem("TO: UNKNOWN RECIPIENT", "");
                continue;
            }
            if(sms.isViewed()) {
                if(sms.getFrom() == phoneNumber) {
                    smsListView.addSelectionListItem("TO:"+ to_string(sms.getTo()) + " " + sms.getsmsMessageTest().substr(0,3) + "...", "");
                } else {
                    smsListView.addSelectionListItem("FROM:"+ to_string(sms.getFrom()) + " " + sms.getsmsMessageTest().substr(0,3) + "...", "");
                }
            }
            if(!sms.isViewed()) {
                if(sms.getFrom() == phoneNumber) {
                    smsListView.addSelectionListItem("TO:"+ to_string(sms.getTo()) + " " + sms.getsmsMessageTest().substr(0,3) + "...", "");
                } else {
                    smsListView.addSelectionListItem("NEW FROM:"+ to_string(sms.getFrom()) + " " +sms.getsmsMessageTest().substr(0,3) + "...", "");
                }
            }
        }
        gui.setAcceptCallback([&]() {
            IUeGui::ITextMode& smsContent = gui.setViewTextMode();
            smsContent.setText(smsList[smsListView.getCurrentItemIndex().second].getsmsMessageTest());
            smsList[smsListView.getCurrentItemIndex().second].setSmsIsViewed();
            checkUnread();
            gui.setRejectCallback([&]() {
                setSmsListView();
            });
        });
    }

    gui.setRejectCallback([&]() {
        showConnected();
    });
}

void UserPort::showNewSms()
{
    gui.showNewSms(true);
}

void UserPort::checkUnread()
{
    std::vector<Sms>& smsList = smsDB.getSmsList();
    for(auto sms: smsList) {
        if(!sms.isViewed()) {
            gui.showNewSms(true);
            break;
        } else {
            gui.showNewSms(false);
        }
    }
}

void UserPort::showDial()
{
    IUeGui::IDialMode& dial = gui.setDialMode();

    gui.setAcceptCallback([&]() {
        common::PhoneNumber to = dial.getPhoneNumber();
        logger.logInfo(to);
        IUeGui::ITextMode& calling = gui.setAlertMode();
        calling.setText("Calling " + to_string(to) + "...");
        handler->handleSendCallRequest(to);

        gui.setRejectCallback([&, to]() {
            handler->handleSendCallDrop(to);
            showConnected();
        });

        gui.setAcceptCallback([] {});
    });
    gui.setRejectCallback([&] {
        showConnected();
    });
}

void UserPort::showCallRequest(common::PhoneNumber from)
{
    IUeGui::ITextMode& calling = gui.setAlertMode();
    logger.logInfo("Someone is calling");
    calling.setText(common::to_string(from) + " is calling...");

    gui.setAcceptCallback([&, from] {

        handler->handleSendCallAccept(from);
        logger.logInfo(common::to_string(from));
        showConversationMode(from);
    });

    gui.setRejectCallback([&, from] {
        handler->handleSendCallDrop(from);
        showConnected();
    });
}

void UserPort::showConversationMode(common::PhoneNumber from)
{
    IUeGui::ICallMode& call = gui.setCallMode();
    call.clearIncomingText();
    call.clearOutgoingText();
    logger.logInfo(common::to_string(from));

    gui.setAcceptCallback([&, from] {
        logger.logInfo("Accept:" + common::to_string(from));
        auto text = call.getOutgoingText();
        updateTalkMessages(phoneNumber, text);
        handler->handleCallSendText(from, text);
        call.clearOutgoingText();
    });
}

void UserPort::showUnknownRecipient(common::PhoneNumber)
{

    IUeGui::ITextMode& alert = gui.setAlertMode();
    alert.setText("Unavailable.");

    gui.setRejectCallback([&] {
        showConnected();
    });
}

void UserPort::showUnavailableRecipient(common::PhoneNumber &from) {
    IUeGui::ITextMode& alert = gui.setAlertMode();
    alert.setText(to_string(from) + " is busy");

    gui.setRejectCallback([&] {
        showConnected();
    });
}

void UserPort::updateTalkMessages(common::PhoneNumber &from, std::string &text) {
    IUeGui::ICallMode& call = gui.setCallMode();
    call.appendIncomingText(common::to_string(from) + ": " + text);
}
}
