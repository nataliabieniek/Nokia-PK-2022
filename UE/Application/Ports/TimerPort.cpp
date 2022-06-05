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
        if(isRunning) {
            isRunning = false;
            std::this_thread::sleep_for(2 * interval);
        }

        logger.logInfo("Start timer: ", duration.count(), "ms");
        isRunning = true;
        timerThread = std::thread(&TimerPort::processingTimeout, this, duration);
        timerThread.detach();
    }

    void TimerPort::stopTimer()
    {
        logger.logInfo("Stop timer");
        isRunning = false;
        std::this_thread::sleep_for(2 * interval);
    }

    void TimerPort::processingTimeout(std::chrono::duration<double> sleepTime) {
        auto start = std::chrono::system_clock::now();
        while(start + sleepTime > std::chrono::system_clock::now()) {
            std::this_thread::sleep_for(interval);
            if(!isRunning) {
                return;
            }
        }
        handler->handleTimeout();
        isRunning = false;
    }

}