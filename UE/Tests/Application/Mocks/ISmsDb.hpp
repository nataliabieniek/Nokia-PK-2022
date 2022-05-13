#pragma once

#include <gmock/gmock.h>
#include "Sms/Sms.hpp"
#include "Sms/SmsDb.hpp"

namespace ue
{
    class ISmsDbMock : public SmsDb
    {
    public:
        ISmsDbMock();
        ~ISmsDbMock();

        MOCK_METHOD(void, addSmsToDB, (Sms newSms));
        MOCK_METHOD(Sms, getSmsFromDB, (int smsIndex));
        MOCK_METHOD(std::vector<Sms>&, getSmsList, ());
    };

}