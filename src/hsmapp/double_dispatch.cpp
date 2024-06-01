
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct State;

struct Event {
    virtual ~Event() = default;
    virtual void enter(State &) = 0;
    virtual void exit(State &) = 0;
};


struct PedCrossingEvent;
struct ProgramTimeElapsedEvent;
struct NoProgramEvent;

struct StateBase
{
    virtual ~StateBase() = default;
    virtual void enter(Event& e) { throw "event not implemented"; };
    virtual void exit(Event& e) { throw "event not implemented"; };
};

struct State : StateBase
{
    using StateBase::enter;
    using StateBase::exit;

    virtual void enter(PedCrossingEvent& e) = 0;
    virtual void enter(ProgramTimeElapsedEvent& e) = 0;
    virtual void enter(NoProgramEvent& e) = 0;
    virtual void exit(PedCrossingEvent& e) = 0;
    virtual void exit(ProgramTimeElapsedEvent& e) = 0;
    virtual void exit(NoProgramEvent& e) = 0;
};

struct PedCrossingEvent : Event {
    int m_myCustomUseData = 42;
    void enter(State& s) override { s.enter(*this); }
    void exit(State& s) override { s.exit(*this); }
};

struct ProgramTimeElapsedEvent : Event {
    double m_myOtherUserCustomData = 3.1415;
    void enter(State& s) override { s.enter(*this); }
    void exit(State& s) override { s.exit(*this); }
};

struct NoProgramEvent : Event {
    std::string m_otherDataStill = "Hi there";
    void enter(State& s) override { s.enter(*this); }
    void exit(State& s) override { s.exit(*this); }
};

class Elephant;

struct GreenState : State
{
    GreenState() {}
    Elephant* m_customStateData = nullptr;

    void enter(PedCrossingEvent& predCrossingEvent) override
    {
        if (predCrossingEvent.m_myCustomUseData > 10)
        {
        }
    }

    void enter(ProgramTimeElapsedEvent& programTimeElapsedEvent) override
    {
        if (programTimeElapsedEvent.m_myOtherUserCustomData < 100.0)
        {
        }
    }

    void enter(NoProgramEvent& noProgramEvent) override
    {
        if (noProgramEvent.m_otherDataStill < "100.0")
        {
        }
    }

    void exit(PedCrossingEvent& pedCrossingEvent) override
    {}

    void exit(ProgramTimeElapsedEvent& programTimeElapsedEvent) override
    {}

    void exit(NoProgramEvent& noProgramEvent) override
    {}
};

class Horse;

struct RedState : State
{
    RedState() {}
    Horse* m_customStateData = nullptr;

    void enter(PedCrossingEvent& predCrossingEvent) override
    {}

    void enter(ProgramTimeElapsedEvent& programTimeElapsedEvent) override
    {}

    void enter(NoProgramEvent& noProgramEvent) override
    {}

    void exit(PedCrossingEvent& pedCrossingEvent) override
    {
        std::cout << pedCrossingEvent.m_myCustomUseData << "\n";
    }

    void exit(ProgramTimeElapsedEvent& programTimeElapsedEvent) override
    {
        std::cout << programTimeElapsedEvent.m_myOtherUserCustomData << "\n";
    }

    void exit(NoProgramEvent& noProgramEvent) override
    {
        std::cout << noProgramEvent.m_otherDataStill << "\n";
    }
};


struct Machine
{
    template <typename UserState>
    void RegisterStates(std::vector<std::unique_ptr<UserState>>& in_states) {
        static_assert(std::is_base_of_v<StateBase, UserState>, "Oops");
        do_enter = [](StateBase& s, Event& e) {
            e.enter(static_cast<UserState&>(s));
            };
        do_exit = [](StateBase& s, Event& e) {
            e.exit(static_cast<UserState&>(s));
            };
        for (auto& s : in_states) {
            states.push_back(std::move(s));
        }
    }

    void Run(const std::vector<std::unique_ptr<Event>>& events)
    {
        for (const auto& s : states)
        {
            for (const auto& e : events)
            {
                do_enter(*s, *e);
                do_exit(*s, *e);
            }
        }
    }

private:
    void (*do_enter)(StateBase& s, Event& e) = nullptr;
    void (*do_exit)(StateBase& s, Event& e) = nullptr;
    std::vector<std::unique_ptr<StateBase>> states;

};


int main()
{
    Machine m;

    std::vector<std::unique_ptr<State>> states;
    states.push_back(std::make_unique<GreenState>());
    states.push_back(std::make_unique<RedState>());

    m.RegisterStates(states);

    std::vector<std::unique_ptr<Event>> events;
    events.push_back(std::make_unique<PedCrossingEvent>());
    events.push_back(std::make_unique<ProgramTimeElapsedEvent>());
    events.push_back(std::make_unique<NoProgramEvent>());

    m.Run(events);

}