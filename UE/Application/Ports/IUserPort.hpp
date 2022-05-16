#pragma once
#include "Messages/PhoneNumber.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
//    virtual void handleShowSmsList() = 0;
    virtual ~IUserEventsHandler() = default;
    virtual void handleSendSms(common::PhoneNumber to, const std::string& message) = 0;
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
};

}
