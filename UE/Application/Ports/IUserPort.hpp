#pragma once


namespace ue
{

class IUserEventsHandler
{
public:
//    virtual void handleShowSmsList() = 0;
    virtual ~IUserEventsHandler() = default;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
};

}
