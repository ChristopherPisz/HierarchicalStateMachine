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

/*
* I needed a way to define the variant at compile time without knowing the user defined types
*/
template<typename... Types>
class RegisteredEventTypes
{
	// Helper to determine if a type is part of the variant
	template<typename T, typename VARIANT_T>
	struct isVariantMember;

	// Helper to determine if a type is part of the variant
	template<typename T, typename... ALL_T>
	struct isVariantMember<T, std::variant<ALL_T...>> : public std::disjunction<std::is_same<T, ALL_T>...> {};

public:
	using EventVariantType = std::variant<Types...>;

	static constexpr size_t getNumEventTypes()
	{
		return std::variant_size_v<EventVariantType>;
	}

	template<typename T>
	static constexpr bool isTypeRegistered()
	{
		return isVariantMember <T, EventVariantType>::value;
	}
};


int main()
{
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

	return 0;
}
