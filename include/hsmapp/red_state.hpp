#ifndef HSMAPP_STATE_RED_HPP
#define HSMAPP_STATE_RED_HPP

#include "hsmlib/state.hxx"

#include <iostream>
#include <memory>


class RedState : public State<RedState>
{
public:
    void enter(std::shared_ptr<Event> event)
    {
        std::cout << "You have entered the Red State";
    };

    void exit(std::shared_ptr<Event> event)
    {
        std::cout << "You have exited the Red State";
    }
};

#endif
