# simple-object-tracking-ardrone
Combines ardrone-autonomy, an object tracking node, and an autopilot node to track and follow an object using the Parrot ARDrone 2.0.

## Installation

## Quick start

## Nodes
### tracker

#### Subscribed topics
- /ardrone/image_raw

#### Published topics
- /bounding_box

#### Services

#### Parameters

#### Required tf transforms


### autopilot

#### Subscribed topics
- /ardrone/navdata
- /simple_object_tracking_ardrone/bounding_box

#### Published topics
- /cmd_vel

#### Services

#### Parameters

#### Required tf transforms
