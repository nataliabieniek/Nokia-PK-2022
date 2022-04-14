#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "ViewingSms.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleShowSmsList() {
    context.setState<ViewingSms>();
}

}
