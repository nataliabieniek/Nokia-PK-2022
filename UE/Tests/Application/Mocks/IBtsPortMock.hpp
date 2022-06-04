#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleDisconnected, (), (final));
    MOCK_METHOD(void, handleReceiveSms, (common::PhoneNumber from, std::string& message), (final));

    MOCK_METHOD(void, handleUnknownRecipient, (common::PhoneNumber from), (final));
    MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber from), (final));
    MOCK_METHOD(void, handleCallAccept, (common::PhoneNumber from), (final));
    MOCK_METHOD(void, handleCallDrop, (common::PhoneNumber to), (final));
    MOCK_METHOD(void, handleCallReceiveText, (common::PhoneNumber from, std::string &text), (final));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendSms, (common::PhoneNumber to, const std::string &message), (final));
    MOCK_METHOD(void, sendCallRequest, (common::PhoneNumber to), (final));
    MOCK_METHOD(void, sendCallAccept, (common::PhoneNumber from), (final));
    MOCK_METHOD(void, sendCallDrop, (common::PhoneNumber to), (final));
    MOCK_METHOD(void, sendCallTalk, (common::PhoneNumber partnerPhoneNumber, const std::string &text), (final));

};

}
