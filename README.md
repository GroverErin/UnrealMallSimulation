# UnrealMallSimulation
Final Project for GAP 321 and 285 classes: A shopping mall simulation using utility theory for agent decision-making.

Here are some instructions/details for my project:

Left click will select whatever you had your cursor over
, whether that is an agent, or a 'building', or an empty tile.

Right click will de-select all.

WASD will move the camera around.
Mouse scroll wheel to zoom in and out.

The motives are now in a C++ layer.
	The start values are set inside of a blueprint instance of this class. (Somewhat tuned random on spawn)
	You can set the tick amount here for faster or slower motive updating. (for tuning)

Population is updated by the mall spawner actor in the world.
	It currently only effects the amount of agents capable of being in the mall at one time.

The agent now has a C++ layer, which handles the FindBestAction function.
	This gets the actors that are maintained by the player class for quick access.
	There is a frustration to population mutliplier which tunes how quickly an agent gets frustrated when the population is closer to max. (in the blueprint)
	There is an inertia multiplier which forces an agent to stay in an action a bit longer. Default is 1.2, set it higher to minimize oscillation.

Shops, vendors, and benches contain tunable values for the "boost" they give to the motive decay rates.
