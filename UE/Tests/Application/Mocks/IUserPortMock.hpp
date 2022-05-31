#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;

    MOCK_METHOD(void, handleSendSms, (common::PhoneNumber to, const std::string &message), (final));

    MOCK_METHOD(void, handleSendCallRequest, (common::PhoneNumber to), (final));
    MOCK_METHOD(void, handleSendCallAccept, (common::PhoneNumber from), (final));
    MOCK_METHOD(void, handleSendCallDrop, (common::PhoneNumber from), (final));
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, setSmsEditView, (), (final));
    MOCK_METHOD(void, setSmsListView, (), (final));
    MOCK_METHOD(void, showNewSms, (), (final));
    MOCK_METHOD(void, checkUnread, (), (final));

    MOCK_METHOD(void, showDial, (), (final));
    MOCK_METHOD(void, showCallRequest, (common::PhoneNumber from), (final));
    MOCK_METHOD(void, showConversationMode, (common::PhoneNumber from), (final));
    MOCK_METHOD(void, showUnknownRecipient, (common::PhoneNumber from), (final));
};

}
