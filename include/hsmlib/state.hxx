#ifndef HSMLIB_STATE_HXX
#define HSMLIB_STATE_HXX

#include "hsmlib/event.hpp"

#include <memory>


/*!
* @detail Employs Curious Reoccuring Template Pattern, for static polymorphism. All types should be known at compile time.
*/
template <class Derived>
class State
{
public:
    void enter(std::shared_ptr<Event> event)
    {
        static_cast<Derived *>(this)->enter(event);
    };

    void exit(std::shared_ptr<Event> event)
    {
        static_cast<Derived*>(this)->exit(event);
    }
};

#endif
