#ifndef HSMLIB_EVENT_HXX
#define HSMLIB_EVENT_HXX


struct Event
{
    virtual unsigned getTypeId() = 0;
};

#endif
