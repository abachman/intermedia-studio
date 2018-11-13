# Project 3 - Real Time Accessibility on the Network

The first project was about a single input or output across the network.

The second was about remotely controlled devices, starting to move more of your project's control signal and input/output across the network.

For the third project you will be building an interactive, *real-time* object or experience that is *accessible* to the people who are experiencing it, *over the network*.


## What is "Real Time"?

https://en.wikipedia.org/wiki/Real-time_computing#Near_real-time

> A real-time system has been described as one which "controls an environment by receiving data, processing them, and returning the results sufficiently quickly to affect the environment at that time".
> ...
> A signal processing algorithm that cannot keep up with the flow of input data with output falling farther and farther behind the input is not real-time. But if the delay of the output (relative to the input) is bounded regarding a process that operates over an unlimited time, then that signal processing algorithm is real-time, even if the throughput delay may be very long.
> ...
> Real-time bidirectional telecommunications delays of less than 300 ms ("round trip" or twice the unidirectional delay) are considered "acceptable" to avoid undesired "talk-over" in conversation.

Much of the Wikipedia discusses examples of particular systems, but we're not concerned about those use cases--for example, "transmission of voice and video", "software that maintains and updates the flight plans for commercial airliners", or "a car engine control system". Instead, I'd like to focus on the timing and interactivity aspects.

**Your projects should talk to us and be communicative, in real time.**

Real time, networked systems may measure, track, or record streams of data over time, but they should respond to input with output quickly enough as to be immediate.


## Accessibility

Everyone (in our class) who experiences the work should be able to control it or see the output without access to any of your personal accounts or account credentials. For examples of basic network communication without credentials / special accounts, see the [Arduino->web (Glitch) and web->Arduino sketches from session 2](https://github.com/abachman/intermedia-studio/tree/master/examples/002-full-stack) or the [arduino->processing sketches from session 6](https://github.com/abachman/intermedia-studio/tree/master/examples/006-simple-protocols).

To be specific, I want to move away from works that are communicating across the network, using data in interesting ways, but controlled or ultimately visible to only one person.

*// I'm very interested in supporting technical challenges in this area*


## The Network

Interaction is possible at arbitrary distances thanks to network connectivity. It should be possible to place your work at any location in the building and interact (see the result or effect change within the project) with it in some way from any other.

---------------------------------------------------------

## BONUS POINTS

Provide a programmable interface (web API or small code library) that can be used by any other IA creator/maker to interact with your project.


## DOUBLE BONUS POINTS

Use someone else's programmable interface to connect your project to theirs or vice versa.

