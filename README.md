# An OpenGL project to simulate STACK
The project uses Opengl and glut library function to implement 3D graphics and simulates stack data structure. The project is entitled pushpopGO

## Requirements to run the projects
* Microsoft Visual Studio C Compiler(MSVC) 
* glut library 
link to download glut library for MSVC
(https://www.transmissionzero.co.uk/software/freeglut-devel/) 

## pushpopGO
The start animations
![Screenshot (18)](https://github.com/RanjanRaj07/pushpopGO/assets/119508085/e5fee193-cc5d-4417-aa6e-affa4f28e704)
![Screenshot (19)](https://github.com/RanjanRaj07/pushpopGO/assets/119508085/8de59e39-f6b7-4fb7-a940-a257436b46c8)
![Screenshot (20)](https://github.com/RanjanRaj07/pushpopGO/assets/119508085/99fb7ba4-7e97-4870-97cf-ffae591138f0)
![Screenshot (21)](https://github.com/RanjanRaj07/pushpopGO/assets/119508085/a7ab4e09-506e-4139-be40-1dcbcb8ff7dd)

## Rules to follow
<img width="960" alt="Screenshot 2023-08-13 125842" src="https://github.com/RanjanRaj07/pushpopGO/assets/119508085/2313d7e7-89df-4f21-9e6c-802237462b0c">

## The simulation scene
![gamescene](https://github.com/RanjanRaj07/pushpopGO/assets/119508085/ce1ce184-90ea-42b7-8f78-bf64974a2b4c)

the simulation starts with a state where there is a car on the road which has a pothole, 
so the car has to fill the pothole in order to cross the road user needed to press p to push a rock into the hole.

## Push operation
<img width="960" alt="Screenshot 2023-08-13 132713" src="https://github.com/RanjanRaj07/pushpopGO/assets/119508085/f29bcdfc-f85b-4a2c-bbeb-cf1b4971c9ac">
user has to push only till exactly filling the pothole so that he can cross the car across the pothole. if overflow user can a popup message.

<img width="960" alt="Screenshot 2023-08-13 132724" src="https://github.com/RanjanRaj07/pushpopGO/assets/119508085/9c9b5fc2-d48b-4ba5-8970-2331b777cb3d">

## Pop operation
<img width="960" alt="Screenshot 2023-08-13 131736" src="https://github.com/RanjanRaj07/pushpopGO/assets/119508085/5ccb5728-143d-404f-85f9-ec711f4027ae">
on pressing o user can pop the rock(rock from the pothole rises up and moves away from the user's vision. If the user faces underflow he can see a popup message.
<img width="960" alt="Screenshot 2023-08-13 132126" src="https://github.com/RanjanRaj07/pushpopGO/assets/119508085/f442b726-0233-4400-93c8-12da58505c88">

## Reach Finish Line
<img width="960" alt="Screenshot 2023-08-13 132739" src="https://github.com/RanjanRaj07/pushpopGO/assets/119508085/f885f2a3-5c29-41b8-8811-835af0f34290">

there is a flag at the finish line which animates only after the car reaches the finish line. user has to press g to GO.

## Background operation
<img width="960" alt="Screenshot 2023-08-13 133407" src="https://github.com/RanjanRaj07/pushpopGO/assets/119508085/c630b4ec-bc09-4ce7-a1f9-2cf9b54716af">

in the background, stack operation and status will be displayed in the console as and when the user does a push or pop operation.

