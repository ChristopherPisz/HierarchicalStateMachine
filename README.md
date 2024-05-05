# Overview
This library aims to provide the classes necessary to implement a user defined Hierarchical State Machine.
The rules and mechanics of a Hierarchical State Machine were largely taken from the [Wikipedia Article](https://en.wikipedia.org/wiki/UML_state_machine) on the same topic. 
However, some gaps were left there and decisions had to be made on how to handle particular scenarios. 

In searching for exisiting C++ libraries that provided an HSM, I found very few, and those that I did find either did things in such a way that the goals below were not fulfilled, 
or they were part of a larger framework. One such framework was [https://www.state-machine.com/qpc/](Quantum Leaps Real-Time Embedded Framework) whom has a book on the topic.

# Goals
A state machine is desired where

1.States should encapsulate code to be executed, within the state class itself. 

Too many systems simply represent state as an enum or string, having complicated conditionals with the code being executed scattered throughout the codebase.
When looking for what a program does in a particular state, a developer should be able to look at a state class and find the top of the call stack right away.

2. States should take dependencies to execute that code via Dependency Injection
3. States should contain custom data

The state classes should contain or have references to everything they need to perform what they need to do. Large monolithic "manager" classes that 
act on state should be replaced by individual classes that encapsulate functionality specific to each particular state.

4. States and their transitions should be open to extension

Often in a finate state machine, large swaths of code needs to be changed when a new transition, new state, or new actions need to be introduced. When states encapsulate
the data and actions taken on that data, and the state machine handles registration of states and transitions at startup, minimal amounts of code should need to be changed.
If new functionality needs to be added to a particular state, the state class itself should allow for inheritance (whether static polymorphism or dynamic polymorphism).

5. Events should encapsulate data associated with the event

An event often has associated data with it. In a finite state machine, some conditional is looked at, a block of code executes, and any data associated with an event is
retrieved from elsewhere, often in multiple places. Any data associated with the event should be within the event itself and made available to state class methods acting
on that event.

7. Program flow should be more flexible than being in a single state at a time

In a finite state machine, often a sequence of actions needs to be repeated for some occurance, from every state. Consider a sequence of actions that need to be taken
when handling an error event. It is undesirable to create a new event for the same error condition from each other event. In a hierarchical state machine, one parent
state can handle a particular event for all its children. 

In a finate state machine, only one state can be the current state. Conversely, in a hierarchical state machine multiple orthoganal states can be active along with parent and
child states collectively making up a current state configuration. This allows for AND as well as OR combinations. The system can be in state `A` and state `B` at the same time.
The system can also be in state `C` OR `D`. More details on what this means will be provided later in this document.




