#include "TimerPort.hpp"
#include <thread>

namespace ue
{

    TimerPort::TimerPort(common::ILogger &logger)
            : logger(logger, "[TIMER PORT]")
    {}

    void TimerPort::start(ITimerEventsHandler &handler)
    {
        logger.logDebug("Timer started");
        this->handler = &handler;
    }

    void TimerPort::stop()
    {
        logger.logDebug("Timer stopped");
        handler = nullptr;
    }

    void TimerPort::startTimer(Duration duration)
    {
        using namespace std::chrono_literals;
        logger.logInfo("Start timer: ", duration.count(), "ms");

        constexpr auto interval = 100ms;
        isRunning = true;

        future = std::async([this, interval, numCycles = duration / interval] {
            for (auto i = decltype(numCycles){0}; i < numCycles; ++i)
            {
                std::this_thread::sleep_for(interval);
                if (!isRunning)
                {
                    return;
                }
            }
            handler->handleTimeout();
            isRunning = false;
        });
    }

    void TimerPort::stopTimer()
    {
        logger.logInfo("Stop timer");
        isRunning = false;
    }

}