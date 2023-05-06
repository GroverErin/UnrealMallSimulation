# Unreal Mall Simulation

**Final Project for GAP 321 and 285 classes:** A shopping mall simulation using utility theory for agent decision-making in Unreal Engine. This is representative of a game similar to the Sims.

<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/UnrealMallSimulation.png?raw=true" alt="Unreal Mall Simulation"/>
</p>

## Overview

This project features a simulated shopping mall environment, where agents (shoppers) navigate through the mall making decisions based on utility theory. The agents interact with various objects such as shops, vendors, and benches, each of which influences the agents' motive decay rates.

Utility theory is used to model the decision-making process of agents (shoppers) as they navigate and interact with the shopping mall environment. Agents evaluate the utility of different actions (e.g., visiting a shop, sitting on a bench) based on their current motives and the environmental factors, and then choose the action that maximizes their overall utility

## Timeline
This project took roughly 2 weeks, including the documentation found in Technical_Doc and Design_Doc.

## Bugs
You may experience bugs and crashes, as this was a school assignment and many edge cases may not be caught.

## Controls

- **Left click**: Selects an object (agent, building, or empty tile) the cursor is hovering over.
	- You can place/sell new buildings on empty tiles by selecting them and selecting the UI button at the bottom of the screen.
- **Right click**: Deselects all objects.
- **WASD**: Moves the camera around.
- **Mouse scroll wheel**: Zooms in and out.

## Technical Details

### Motives

Motives are implemented in a C++ layer. The starting values are set within a blueprint instance of this class. You can set the tick rate to be faster or slower for each motive tick for tuning purposes.

### Population

The population is updated by the 'mall spawner' actor in the world. It currently only affects the number of agents that can be present in the mall at any given time.

### Agent

The agent has a C++ layer, which handles the `FindBestAction` function. This function retrieves the actors that are maintained by the player class for quick access. The blueprint contains a 'frustration to population' multiplier that tunes how quickly an agent gets frustrated when the population is closer to max. There is also an inertia multiplier which forces an agent to stay in an action a bit longer. The default value is 1.2, set it higher to minimize action oscillation.

### Shops, Vendors, and Benches

Shops, vendors, and benches contain tunable values for the "boost" they provide to the motive decay rates. Adjust these values to fine-tune the impact each object has on agent behavior.

## Technical Documentation

Here is the contents of the Technical_Doc.docx file, please note that although this document references a 'team', the team is imaginary, as this document was supposed to represent creating a technical document for a team's proposal:

### Overview
The fundamental details needed in order to gain a better understanding of the information detailed in this technical document answer the following questions: What engine will the team be using to accomplish this task? And, How will the Utility scoring system work?

To answer the former, the team will be using the Unreal Engine 4. The reason for this is due to the familiarity that the engineers have with the engine as apposed to most other options. This will result in the lowest possible development time by removing the need for the engineers to become familiar with any new development environments. Due to the bonus development time, the project will result in a higher quality end product.

To answer the remaining question, the Utility scoring system will work by, first, separating each trait that the agent has a desire to fulfill into a category that can be weighed separately among other categories. The score will be based solely off of a utility score graph (detailed below). From the agent’s perspective, this “bucketing” system [Graham] will answer the question of “Which desire do I wish to fulfill most?”.

Second, each trait that needs to be fulfilled will contain a list of all actions that potentially fulfill that trait. The actions will then be scored individually. This will allow a single action to receive a utility score separate to the categories score, and the usefulness of this step will be given in an example later in this proposal.

The remainder of this proposal will go into detail on the Utility scoring system, including the specific implementations of the designers requested functionality.

### Trait Utility Scores
#### Population
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/PopulationCurve.png?raw=true" alt="Population Curve"/>
</p>
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/PopulationFormula.png?raw=true" alt="Population Formula"/>
</p>
The team proposes that the overall crowdedness of the mall, or an area of, will be modeled with a quadratic curve, shown in Figure 1. The default population curve has been modeled here to be nearly linear, but a quadratic curve was chosen so that when tuned, the curve can represent an agent that might be more averse to crowded areas, or having a higher utility score at lower values.

Equation 1 depicts the equation used in Figure 1, the Utility Score, U, is the ratio of the current population to max population, with the tunable value, s, being able to change the sharpness of the curve. Any value of s lower than 1 and greater than 0 will result in a rotated quadratic, higher than 1 will result in a regular quadratic, and 1 will be linear. A rotated quadratic more easily represents an agent that gets frustrated in crowded areas, where a linear might be a default agent value, and a quadratic might represent an agent that isn’t bothered by crowds. The value of s should remain between 0 and 2.

#### Energy
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/EnergyCurve.png?raw=true" alt="Energy Curve"/>
</p>
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/EnergyFormula.png?raw=true" alt="Energy Formula"/>
</p>
The energy level of an agent will be modeled with a piecewise combination of a reversed quadratic curve and a linear curve, shown in Figure 2. This was chosen in order to model the way that some team members personally felt while shopping at a mall: First they were excited to shop and walk around, then suddenly after a time had passed, they realized how tired they were. After that “crash”, they began to get tired at a more noticeable rate.

Equation 2 is the most complex of the equations within this technical document and is the only equation that does not tune very easily from a designer’s perspective. The first section of the piecewise is a simple linear curve, a ratio between the agent’s current energy to its maximum energy, however, the second section of the piecewise details an inversed quadratic curve, which does not tune well. A series of linear curves may be better used and tuned by a designer instead, so that an agent that tires more or less quickly may be modeled.

#### Shop Desire
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/ShopCurve.png?raw=true" alt="Shop Curve"/>
</p>
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/ShopFormula.png?raw=true" alt="Shop Formula"/>
</p>
An agent’s desire to shop will be modeled from a simple linear curve, as the desire to shop increases, the likely-hood of an agent choosing to do so also increases, this is shown with both Figure 3 and Equation 3.

#### Hunger
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/HungerCurve.png?raw=true" alt="Hunger Curve"/>
</p>
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/HungerFormula.png?raw=true" alt="Hunger Formula"/>
</p>
An agent’s hunger will be modeled by a logistics curve, so that an agent would remain satiated for a while, gain hunger very rapidly, then remain hungry at a moderate level, until slowly declining to a very hungry state. This is shown in Figure 4. In Equation 4, there are two values that are used to tune this model, h and k. The sharpness of the curve is tuned with k, and is a difficult value to tune properly, and must remain between 0 and 1.65 in order to maintain this curve’s relative shape, so it is best left as a constant. However, h is much more easily tuned by a designer. It represents the point at which the utility score for hunger will be at a value of 0.5, so a more gluttonous agent might have a lower h value than an agent that eats less often.

#### Frustration
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/FrustrationCurve.png?raw=true" alt="Frustration Curve"/>
</p>
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/FrustrationFormula.png?raw=true" alt="Frustration Formula"/>
</p>
The team has decided that frustration should be a separate trait from Population. This is because there are multiple reasons that a typical mall that would frustrate a shopper, from dirty bathrooms, or waiting in line, to rude employees. Making this a separate trait will greatly increase the scalability of this system for the designers.

As shown in Figure 5, Frustration will be modeled with a logistics curve, similarly to hunger, but reversed. This will allow an agent to remain in a non-frustrated state, before rapidly shifting to a more frustrated state. In Equation 5, the values of h and k will behave similarly to those of Equation 4, where k is a constant and h will tune the point where the utility score for frustration will be at a value of 0.5.

### Action Utility Scores
<p align="center">
  <img src="https://github.com/GroverErin/UnrealMallSimulation/blob/main/Images/ActionChoiceExample.jpg?raw=true" alt="Action Choice Example"/>
</p>
Due to the designer’s request being that of a simple simulation, how an action can be scored will be made simple and designer friendly: A score will be given to an action based on how well it will fulfill the trait it belongs to.

For example, if a bench can rest an agent by 5, and a massage chair can rest an agent my 25, the agent will likely choose the massage chair. However, in order to prevent the massage chair from always getting chosen, we will compare the potential energy gain, to the energy the agent needs. Therefore, if the agent only needs 5 energy, then the massage chair would also only have a score of 5, making the two options equally comparable.

Additionally, an action will be chosen by random from among the top designer tunable amount of the highest scoring actions. To prevent an agent from oscillating between choices, an agent will not be allowed to make another choice until its current action is completed. In Figure 6, it is shown using the values taken from the equations in this document what choice would be made by the agent. If the randomization is ruled out, it is likely that the agent will choose to shop at Macy’s.

Lastly, additional factors can be added to the final score for each action. For example, resting at a massage chair can have a cost of 5 dollars, where a bench may be free. If an agent’s current wallet contains $5, they may not be willing to choose that option over a free one. This would necessitate an additional utility scoring model for an agent’s money.

### Performance
The agents will have to iterate through each trait on every AI frame. The number of agents, a, have a number of traits, n, which also act as a container for actions, m. However, only one trait will have to check each of its actions, unless they cannot be completed, in which case, the agent should choose from the next highest scored trait.

So, worst-case would be O(a*n*m) if all traits had an equal number of actions. This would be fine for smaller values of a, n, or m, but it does not scale well. A solution would be to not continue to iterate through the traits and actions, but instead to increase an agent’s frustration, and wait until the next AI frame to re-attempt the action selection. This would instead result in every agent scoring every trait, but only scoring actions from one trait.

### Memory
The memory usage of this system would be negligible.

## Design Documentation

Here is the contents of the Design_Doc.docx file, please note that although this document references a 'team', the team is imaginary, as this document was supposed to represent creating a design document for a team's proposal:

### Overview
The team is proposing the design of a Shopping Mall Simulation, where the player can place and remove features from a mall that the shoppers can indulge themselves in. The simulation will be based on an AI in the simulation, that will react dynamically to the player changing features in the mall. Players will fill the role of the mall manager, and be able to place and remove food vendors, rest areas, social areas, and various shops around the mall space. The goal of the player will be to design the mall in such a way that it will attract and maintain more customers and bring in a larger profit.

### Gameplay
The mall will begin as an empty sandbox-like space, where the player will have an initial budget to build some features in the space. Features are locations that an AI customer can go to effect one of their many motives (See Mall AI Customers). These features will have an associated cost to them, with the player having to spend some of their initial budget. Better features will have a higher associated cost to them.  In addition to the cost of the feature, some features might have an income associated with them for whenever an AI customer interacts with them. Some example features might be:

| Motive | Feature         | Cost   | Commodity     | Income/Customer |
|--------|-----------------|--------|--------------|-----------------|
| Rest   | Bench           | $ 50   | 10 Energy     | $ 0             |
| Rest   | Massage Chair   | $ 150  | 25 Energy     | $ 3             |
| Rest   | Massage Table   | $ 250  | 40 Energy     | $ 8             |
| Food   | Hot Dog Stand   | $ 100  | 10 Hunger     | $ 3             |
| Food   | Taco Bar        | $ 300  | 25 Hunger     | $ 9             |
| Shop   | Clothing Outlet | $ 1,750 | 15 Shop Desire | $ 59           |
| Shop   | Fancy Pant-sy   | $ 2,825 | 30 Shop Desire | $ 180          |
| Decor  | Fountain        | $ 500  | 15 Social      | $ 1             |


Of course, these are examples and all values will be tunable by the designer. Some of these features may also provide dual utility – fulfilling two types or agent motives, like a massage parlor might provide rest and shop desire.

The mall will have a popularity level that will be related to the number of features the mall has, and how luxurious those features are. A higher popularity rate will increase the agent spawn rate per minute of the mall. The mall will have a designer tunable maximum population. The current population will have an effect on the customers within the mall, likely increasing their frustration as the mall becomes crowded.

The player themselves will be able to select any agent within the mall and “watch” their motives, traits, and current state of the agent. They will also be able to cycle through a list of placeable features and place them within the mall space, if they can afford the cost of the feature.

### Mall AI Customers
The mall AI will use a combination of utility AI and a form of state machine. The agent will enter/spawn into the mall with a series of (tunable) randomized motive values, such as, hunger, energy, or frustration. These motives will provide a utility score for the desired action the agent wishes to take. The agent will then take an action based on the score of its motive and the weight of its traits, as each agent will desire certain motives over others. This utility system will be based heavily on the utility system defined in the contents of the EGrover_321_Technical_Doc that is attached.

When an agent reaches its destination, it will enter into a state relating to that destination. An example: When an agent enters a shop, it would enter a shopping state with a state-enter condition of b-lining to a random part of the shop, a state-update condition of wandering throughout the shop, and a state-exit condition of paying at the register.

Agents will have a series of Motives and Traits that will define an agent’s behaviors. Motives are the ‘stats’ of an agent/shopper, and a trait is something unique to the shopper that affects these motives. These might include:
 - Energy – Amount of rest needed by the agent.
 	- Insomniac’s may not care about their energy trait as much.
 - Hunger – Amount of food needed by the agent.
	- Gluttons may care about their hunger much more than other things.
 - Frustration – How much the agent wants to leave the mall.
 	- Irritable may get frustrated more quickly.
 - Money – How much currency the agent has left to spend.
 	- Penny-pincher might be less willing to spend money.
 - Shop Desire – How badly the agent wants to shop.
 	- Shopaholic might desire varieties of shops.
 - Social – How much the agent wants to socialize.
 	- Introvert may avoid social situations.

Agents will leave the mall when they have run out of money to spend in the mall, if they do not desire a free service such as socializing or resting. Every time an agents desired action is not possible, a small amount of frustration will be added to the agent, until the agent decides to leave. Agents will maintain a list of the places they have been, and that will restrict the agent from visiting that location again, possibly within a tunable timeframe. The AI be able to navigate around the mall, dynamically, to avoid obstacles, navigate to newly placed shops and handle the removal of shops.

### AI Debug Feature
There will be a tool that will allow a developer to spawn an agent into the mall at a selected location with custom traits and motive values. The tool will also allow the developer to select an agent and tune its current motives, money, and traits, or event de-spawn the agent entirely.

### Stretch Goals
 - Allow the mall to be expanded for a fee, increasing the build space and the population cap.
 - Create a “billing” cycle, where after a set time, the mall must pay bills based on the number of features within the mall, creating a “lose” condition if the player goes into a negative balance.
