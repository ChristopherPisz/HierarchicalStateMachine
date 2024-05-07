#ifndef HSMAPP_PED_CROSSING_EVENT_HPP
#define HSMAPP_PED_CROSSING_EVENT_HPP

#include "hsmlib/event.hpp"
#include "hsmapp/event_types.hpp"

#include <chrono>
#include <iostream>


struct PedCrossingEvent : public Event
{
    std::chrono::time_point<std::chrono::utc_clock> m_buttonPressedTimestamp;

    unsigned getTypeId() override { return static_cast<unsigned>(EventType::PED_CROSSING_EVENT); }
};

#endif
