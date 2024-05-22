#include <variant>
#include <vector>
#include <memory>
#include <iostream>

struct PedCrossingEvent{};
struct ProgramTimeElapsedEvent{};
struct NoProgramEvent{};

struct GreenState
{
	void enter(std::shared_ptr<PedCrossingEvent> predCrossingEvent)
	{}

	void enter(std::shared_ptr<ProgramTimeElapsedEvent> programTimeElapsedEvent)
	{}

	void enter(std::shared_ptr<NoProgramEvent> noProgramEvent)
	{}

	void exit(std::shared_ptr<PedCrossingEvent> pedCrossingEvent)
	{}

	void exit(std::shared_ptr<ProgramTimeElapsedEvent> programTimeElapsedEvent)
	{}

	void exit(std::shared_ptr<NoProgramEvent> noProgramEvent)
	{}
};


// A template to hold parameter pack types
template<typename... >
struct TypeList {};

// Declaration of State Machine template
template<typename StateTypeList, typename EventTypeList>
class StateMachine;

// Specialization of State Machine template
template<typename... StateTypes, typename... EventTypes>
class StateMachine<TypeList<StateTypes...>, TypeList<EventTypes...>>
{
	using EventVariantType = std::variant<EventTypes...>;
	using StateVariantType = std::variant<StateTypes...>;

	StateVariantType m_root;

public:
	StateMachine(StateVariantType root)
	{
		// TODO - Verification of state children conforming to UML Statechart rules
		//        I think we need a base class for state, for children container
		//        We then need to enforce statetypes are that type
	}

	template<typename FromStateType, typename ToStateType, typename EventType>
	void registerTransition()
	{
		// How to make a map of types
	}

	void queueEvent(std::shared_ptr<EventVariantType> event)
	{
		// I want the user to give me instances of the states, because I want the user to be able to DI any dependencies thier handlers have
		//
		// So, while I might take typenames as template params, I still need a way for them to give me the root node containing all the states
		// and then verify all those children are registered.
		//
		// Then, once we have the actual states, we can find the instance, and make the call
	}
};



	int main()
	{
		/*
		// Try out the template. The user will need to supply this to a registration method
		using MyEventTypes = RegisteredEventTypes<std::shared_ptr<PedCrossingEvent>,
												  std::shared_ptr<ProgramTimeElapsedEvent>,
												  std::shared_ptr<NoProgramEvent>>;

		// Test that it works
		std::cout << MyEventTypes::getNumEventTypes() << std::endl;
		std::cout << MyEventTypes::isTypeRegistered<std::shared_ptr<NoProgramEvent>>() << std::endl;

		std::vector<MyEventTypes::EventVariantType> postedEvents = {
			std::make_shared<PedCrossingEvent>(),
			std::make_shared<ProgramTimeElapsedEvent>(),
			std::make_shared<NoProgramEvent>()
		};

		GreenState green;
		std::visit([&green](auto&& arg) { green.enter(arg); }, postedEvents[0]);
		*/
		return 0;
	}
