#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"

#include <UeGui/ICallMode.hpp>
#include "UeGui/IDialMode.hpp"
#include "UeGui/ITextMode.hpp"


namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
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

    gui.setAcceptCallback([this](){
        auto indx = gui.setListViewMode().getCurrentItemIndex();
        //logger.logInfo(indx.second);
        //if(indx.second == 0) {
        //    logger.logInfo("Item on index 0 selected");
        //} else if(indx.second) {
        //    logger.logInfo("SOmething else.");
        //}

        switch (indx.second) {
            case 0:
                logger.logInfo("Compose SMS");
                break;
            case 1:
                logger.logInfo("View SMS");
                break;
            case 2:
                logger.logInfo("Dial mode");
                showDial();
                break;
        }
        
        
    });
    gui.setRejectCallback([]{});

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
    });
    gui.setRejectCallback([this] {
        showConnected();
    });
}

void UserPort::showCallRequest(common::PhoneNumber from)
{
    IUeGui::ITextMode& calling = gui.setAlertMode();
    logger.logInfo("Someone is calling");
    calling.setText(common::to_string(from) + " is calling...");

    gui.setAcceptCallback([this, from] {
       handler->handleSendCallAccept(from);
        setConversationMode(from);
    });

    gui.setRejectCallback([this, from] {

    });
}

void UserPort::setConversationMode(const common::PhoneNumber from) {
    IUeGui::ICallMode& call = gui.setCallMode();
}

}

