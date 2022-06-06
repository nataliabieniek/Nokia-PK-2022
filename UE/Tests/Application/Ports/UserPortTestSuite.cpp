#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/UserPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IUeGuiMock.hpp"
#include "Mocks/ISmsDb.hpp"

namespace ue
{
    using namespace ::testing;

    class UserPortTestSuite : public Test
    {
    protected:
        const common::PhoneNumber PHONE_NUMBER{112};
        const common::PhoneNumber PHONE_NUMBER_RECIPIENT{122};
        NiceMock<common::ILoggerMock> loggerMock;
        StrictMock<IUserEventsHandlerMock> handlerMock;
        StrictMock<IUeGuiMock> guiMock;
        StrictMock<IListViewModeMock> listViewModeMock;
        StrictMock<ISmsDbMock> smsDbMock;

        StrictMock<IDialModeMock> dialModeMock;
        StrictMock<ISmsComposeModeMock> smsComposeModeMock;
        StrictMock<ICallModeMock> callModeMock;
        StrictMock<ITextModeMock> alertModeMock; //setAlertMode
        StrictMock<ITextModeMock> viewTextModeMock; //setViewTextMode

        UserPort objectUnderTest{loggerMock, guiMock, PHONE_NUMBER, smsDbMock};

        UserPortTestSuite()
        {
            EXPECT_CALL(guiMock, setTitle(HasSubstr(to_string(PHONE_NUMBER))));
            objectUnderTest.start(handlerMock);
        }
        ~UserPortTestSuite()
        {
            objectUnderTest.stop();
        }
    };

    TEST_F(UserPortTestSuite, shallStartStop)
{
}

TEST_F(UserPortTestSuite, shallShowNotConnected)
{
EXPECT_CALL(guiMock, showNotConnected());
objectUnderTest.showNotConnected();
}

TEST_F(UserPortTestSuite, shallShowConnecting)
{
EXPECT_CALL(guiMock, showConnecting());
objectUnderTest.showConnecting();
}

TEST_F(UserPortTestSuite, shallShowMenuOnConnected)
{
std::function<void()> callback;
EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
EXPECT_CALL(listViewModeMock, clearSelectionList());
EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
objectUnderTest.showConnected();
}

TEST_F(UserPortTestSuite, shallshowDial)
{
std::function<void()> callback;
EXPECT_CALL(guiMock, setDialMode()).WillOnce(ReturnRef(dialModeMock));
EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
objectUnderTest.showDial();
}

TEST_F(UserPortTestSuite, shallShowCallRequest)
{
std::function<void()> callback;
EXPECT_CALL(guiMock, setAlertMode()).WillOnce(ReturnRef(alertModeMock));
EXPECT_CALL(alertModeMock, setText(to_string(PHONE_NUMBER_RECIPIENT)+ " is calling..."));
EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
objectUnderTest.showCallRequest(PHONE_NUMBER_RECIPIENT);
}


TEST_F(UserPortTestSuite, shallSetSmsEditView)
{
std::function<void()> callback;
EXPECT_CALL(guiMock, setSmsComposeMode()).WillOnce(ReturnRef(smsComposeModeMock));
EXPECT_CALL(smsComposeModeMock, clearSmsText());
EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
objectUnderTest.setSmsEditView();
}

TEST_F(UserPortTestSuite, shallShowConversationMode)
{
std::function<void()> callback;
EXPECT_CALL(guiMock, setCallMode()).WillOnce(ReturnRef(callModeMock));
EXPECT_CALL(callModeMock, clearOutgoingText());
EXPECT_CALL(callModeMock, clearIncomingText());
EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
objectUnderTest.showConversationMode(PHONE_NUMBER_RECIPIENT);
}

}

