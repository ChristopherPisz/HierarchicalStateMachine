#include "hsmapp/red_state.hpp"
#include "hsmapp/ped_crossing_event.hpp"

#include <memory>


int main()
{
	RedState redState;

	std::shared_ptr<Event> pedCrossingEvent = std::make_shared<PedCrossingEvent>();
	
	redState.enter(pedCrossingEvent);

	return 0;
}
