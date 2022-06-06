#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue
{

    BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
            : logger(logger, "[BTS-PORT]"),
              transport(transport),
              phoneNumber(phoneNumber)
    {}

    void BtsPort::start(IBtsEventsHandler &handler)
    {
        transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
        transport.registerDisconnectedCallback([this]() {handleDisconnected();});
        this->handler = &handler;
    }

    void BtsPort::stop()
    {
        transport.registerMessageCallback(nullptr);
        transport.registerDisconnectedCallback(nullptr);
        handler = nullptr;
    }

    void BtsPort::handleMessage(BinaryMessage msg)
    {
        try
        {
            common::IncomingMessage reader{msg};
            auto msgId = reader.readMessageId();
            auto from = reader.readPhoneNumber();
            auto to = reader.readPhoneNumber();


            switch (msgId)
            {
                case common::MessageId::Sib:
                {
                    auto btsId = reader.readBtsId();
                    handler->handleSib(btsId);
                    break;
                }
                case common::MessageId::AttachResponse:
                {
                    bool accept = reader.readNumber<std::uint8_t>() != 0u;
                    if (accept)
                        handler->handleAttachAccept();
                    else
                        handler->handleAttachReject();
                    break;
                }
                case common::MessageId::Sms:
                {
                    std::string message = reader.readRemainingText();
                    handler->handleReceiveSms(from, message);
                    break;
                }
                case common::MessageId::UnknownRecipient:
                {
                    handler->handleUnknownRecipient(from);
                    break;
                }
                case common::MessageId::CallRequest: {
                    handler->handleCallRequest(from);
                    break;
                }
                case common::MessageId::CallAccepted: {
                    handler->handleCallAccept(from);
                    break;
                }
                case common::MessageId::CallDropped: {
                    handler->handleCallDrop(from);
                    break;
                }
                case common::MessageId::CallTalk: {
                    std::string text = reader.readRemainingText();
                    logger.logDebug("Handle call talk: " + common::to_string(from) + " - " + text);
                    handler->handleCallReceiveText(from, text);
                    break;
                }
                default:
                    logger.logError("unknown message: ", msgId, ", from: ", from);

            }
        }
        catch (std::exception const& ex)
        {
            logger.logError("handleMessage error: ", ex.what());
        }
    }


    void BtsPort::sendAttachRequest(common::BtsId btsId)
    {
        logger.logDebug("sendAttachRequest: ", btsId);
        common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                    phoneNumber,
                                    common::PhoneNumber{}};
        msg.writeBtsId(btsId);
        transport.sendMessage(msg.getMessage());


    }

    void BtsPort::handleDisconnected() {
        handler->handleDisconnected();
    }

    void BtsPort::sendSms(common::PhoneNumber to, const std::string &message)
    {
        logger.logDebug("sendSms: ", to);
        common::OutgoingMessage msg{common::MessageId::Sms,
                                    phoneNumber,
                                    to};
        msg.writeText(message);
        transport.sendMessage(msg.getMessage());
    }

    void BtsPort::sendCallRequest(common::PhoneNumber to) {
        common::OutgoingMessage msg{common::MessageId::CallRequest,
                                    phoneNumber,
                                    to};
        transport.sendMessage(msg.getMessage());
    }

    void BtsPort::sendCallAccept(common::PhoneNumber from)
    {
        common::OutgoingMessage msg{common::MessageId::CallAccepted,
                                    phoneNumber,
                                    from};
        transport.sendMessage(msg.getMessage());
    }

    void BtsPort::sendCallDrop(common::PhoneNumber to)
    {
        common::OutgoingMessage msg{common::MessageId::CallDropped,
                                    phoneNumber,
                                    to};
        transport.sendMessage(msg.getMessage());
    }

    void BtsPort::sendCallTalk(common::PhoneNumber partnerPhoneNumber, const std::string &text) {
        logger.logDebug("Sending to BTS");
        common::OutgoingMessage msg{common::MessageId::CallTalk, phoneNumber, partnerPhoneNumber};
        msg.writeText(text);
        transport.sendMessage(msg.getMessage());
    }

}

