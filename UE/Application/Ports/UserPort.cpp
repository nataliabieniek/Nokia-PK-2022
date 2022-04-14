#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"

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

    gui.setAcceptCallback([this]{
        auto indx = gui.setListViewMode().getCurrentItemIndex();
        logger.logInfo(indx.second);
        if(indx.second == 0) {
            logger.logInfo("Item on index 0 selected");
        } else if(indx.second) {
            showSmsList();
        }
    });
    gui.setRejectCallback([]{});

}

void UserPort::showSmsList() {
    auto &smsList = gui.setListViewMode();
    smsList.clearSelectionList();

    gui.setRejectCallback([this]{showConnected();});
}

}
