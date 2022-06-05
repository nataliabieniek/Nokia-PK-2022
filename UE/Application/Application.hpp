#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"
#include "Sms/SmsDb.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer,
                SmsDb& smsDB);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleReceiveSms(common::PhoneNumber from, std::string& message) override;
    void handleSendSms(common::PhoneNumber to, const std::string& message) override;

    void handleUnknownRecipient(common::PhoneNumber from) override;

    void handleCallRequest(common::PhoneNumber from) override;
    void handleSendCallRequest(common::PhoneNumber to) override;
    void handleCallAccept(common::PhoneNumber from) override;
    void handleSendCallAccept(common::PhoneNumber from) override;
    void handleSendCallDrop(common::PhoneNumber to) override;
    void handleCallDrop(common::PhoneNumber from) override;
    void handleCallReceiveText(common::PhoneNumber from, std::string &text) override;
    void handleCallSendText(common::PhoneNumber to, const std::string& text) override;

private:
    Context context;
    common::PrefixedLogger logger;

};

}
