//#include "hsmapp/red_state.hpp"
//#include "hsmapp/ped_crossing_event.hpp"

#include <iostream>
#include <memory>
#include <queue>


class State;

/*!
* @brief Event type that uses Type Erasure
* @details Type Erasure pattern was learned from the CppCon 2021 video by Klaus Iglberger "Breaking Dependencies: Type Erasure - A Design Analysis"
*/
class Event
{
	struct EventConcept
	{
		virtual ~EventConcept() {}
		virtual std::unique_ptr<EventConcept> clone() const = 0;
	};

	template<typename T>
	struct EventModel : EventConcept
	{
		EventModel(const T& value)
			: m_object{ value }
		{}

		std::unique_ptr<EventConcept> clone() const override
		{
			return std::make_unique<EventModel>(*this);
		}

		T m_object;
	};

	std::unique_ptr<EventConcept> m_pimpl;

public:
	template<typename T>
	Event(T&& x)
		: m_pimpl{ std::make_unique<EventModel<T>>(std::forward<T>(x)) }
	{}

	Event(Event const& rhs) { m_pimpl = rhs.m_pimpl->clone(); };
	Event(Event&& rhs) = default;
	Event& operator=(Event const& rhs) { m_pimpl = rhs.m_pimpl->clone(); };
	Event& operator=(Event&& rhs) = default;
};

void typeErasure()
{
	struct B
	{
		int foo = 10;
	};

	struct C
	{
		float bar = 20;
	};

	using Events = std::queue<Event>;
	Events events;
	events.push(B());
	events.push(C());

	while (!events.empty())
	{
		auto& baseItem = events.back();


		/* Now how to get the concrete data? Is it possible without a dynamic cast?
		if (baseItem->getType() == Type::TYPE_B)
		{
			auto concreteItem = std::dynamic_pointer_cast<B>(baseItem);
			std::cout << "Your B event contained data: " << concreteItem->foo;
		}

		if (baseItem->getType() == Type::TYPE_C)
		{
			auto concreteItem = std::dynamic_pointer_cast<C>(baseItem);
			std::cout << "Your C event contained data: " << concreteItem->bar;
		}
		*/

		events.pop();
	}
}

void dynamicCast()
{
	// Example of the problem using the classic dynamic cast
	enum Type
	{
		TYPE_B = 0,
		TYPE_C
	};

	struct A
	{
		virtual Type getType() = 0;
	};

	struct B : public A
	{
		int foo = 10;

		virtual Type getType() { return TYPE_B; }
	};

	struct C : public A
	{
		float bar = 20;

		virtual Type getType() { return TYPE_C; }
	};

	std::queue<std::shared_ptr<A>> queue;
	queue.push(std::make_shared<B>());
	queue.push(std::make_shared<C>());

	while (!queue.empty())
	{
		std::shared_ptr<A> baseItem = queue.back();

		if (baseItem->getType() == Type::TYPE_B)
		{
			auto concreteItem = std::dynamic_pointer_cast<B>(baseItem);
			std::cout << "Your B event contained data: " << concreteItem->foo;
		}

		if (baseItem->getType() == Type::TYPE_C)
		{
			auto concreteItem = std::dynamic_pointer_cast<C>(baseItem);
			std::cout << "Your C event contained data: " << concreteItem->bar;
		}

		queue.pop();
	}
}

int main()
{
	typeErasure();

	return 0;
}
