#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"

#include <future>


namespace ue
{

    class TimerPort : public ITimerPort
    {
    public:
        TimerPort(common::ILogger& logger);

        void start(ITimerEventsHandler& handler);
        void stop();

        // ITimerPort interface
        void startTimer(Duration duration) final;
        void stopTimer() final;

    private:
        common::PrefixedLogger logger;
        ITimerEventsHandler* handler = nullptr;
        bool isRunning = false;
        std::future<void> future;
    };

}