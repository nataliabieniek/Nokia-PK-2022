#include "BaseState.hpp"

namespace ue
{

BaseState::BaseState(Context &context, const std::string &name)
    : context(context),
      logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::handleTimeout()
{
    logger.logError("Uexpected: handleTimeout");
}

void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Uexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept()
{
    logger.logError("Uexpected: handleAttachAccept");
}

void BaseState::handleAttachReject()
{
    logger.logError("Uexpected: handleAttachReject");
}

void BaseState::handleDisconnected()
{
    logger.logError("Uexpected: handleDisconnected");
}

void BaseState::handleCallRequest(common::PhoneNumber from) {
    logger.logError("Uexpected: handleCallRequest");
}

void BaseState::handleSendCallRequest(common::PhoneNumber to) {
    logger.logError("Uexpected: handleSendCallRequest");
}

void BaseState::handleCallAccept(common::PhoneNumber) {
    logger.logError("Uexpected: handleCallAccept");
}

void BaseState::handleSendCallAccept(common::PhoneNumber from) {
    logger.logError("Uexpected: handleSendCallAccept");
}

void BaseState::handleCallDrop(common::PhoneNumber) {
    logger.logError("Uexpected: handleCallDrop");
}

void BaseState::handleReceiveCallRequest(common::PhoneNumber from) {
    logger.logError("Uexpected: handleReceiveCallRequest");
}

}
