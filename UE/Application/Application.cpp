#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer)
    : context{iLogger, bts, user, timer},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
    logger.logError("Timeout");
}

void Application::handleSib(common::BtsId btsId)
{
    logger.logInfo("Handling Sib");
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
    logger.logInfo("Attached");
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
    logger.logError("Cannot attach");
}

void Application::handleDisconnected()
{
    logger.logInfo("Disconnecting");
    context.state->handleDisconnected();
}

void Application::handleCallRequest(common::PhoneNumber from) {
    logger.logInfo("Handling call request");
    context.state->handleCallRequest(from);
}

void Application::handleSendCallRequest(common::PhoneNumber from, common::PhoneNumber to) {
    context.state->handleSendCallRequest(from, to);
}

void Application::handleReceiveCallRequest(common::PhoneNumber from) {
    context.state->handleReceiveCallRequest(from);
}

void Application::handleCallDrop(common::PhoneNumber from) {
    logger.logInfo("Handling call drop");
    context.state->handleCallDrop(from);
}

void Application::handleCallAccept(common::PhoneNumber from) {
    logger.logInfo("Handling call accept");
    context.state->handleCallAccept(from);
}

}
