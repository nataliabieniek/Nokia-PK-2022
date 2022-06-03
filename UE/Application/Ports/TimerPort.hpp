#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"

#include <future>


namespace ue
{
    using namespace std::chrono_literals;
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
        void processingTimeout(std::chrono::duration<double> sleepTime);
        common::PrefixedLogger logger;
        ITimerEventsHandler* handler = nullptr;
        bool isRunning = false;
        std::future<void> future;
        std::thread timerThread;
        const std::chrono::duration<double> interval = 100ms;
    };

}