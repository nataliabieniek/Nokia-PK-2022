#pragma once
#include <string>
#include <ctime>
#include <chrono>
#include "Messages/PhoneNumber.hpp"

namespace ue
{
    class Sms{
        public:
            Sms(common::PhoneNumber from, common::PhoneNumber to, std::string smsMessage);

            void setSmsIsViewed();

            common::PhoneNumber getFrom();
            common::PhoneNumber getTo();

            std::string getsmsMessageTest();

            bool isViewed();

            bool isUnknownRecipient();
            void setUnknownRecipient();

        private:
            common::PhoneNumber from{};
            common::PhoneNumber to{};
            bool flgIsViewed;
            std::string smsMessage;
            bool unknownRecipient;
    };
}