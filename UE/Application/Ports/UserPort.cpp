#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"

#include <UeGui/ICallMode.hpp>
#include "UeGui/IDialMode.hpp"


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

    gui.setAcceptCallback([this]{
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
                logger.logInfo("Call");
                IUeGui::IDialMode& dial = gui.setDialMode();
                gui.setAcceptCallback([this] {
                });
                break;
        }
        
        
    });
    gui.setRejectCallback([]{});

}

}

