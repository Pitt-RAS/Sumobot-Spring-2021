# Sumobot-Spring-2021
## Code base for Sumo Bot project, spring term of 2021.

This is the University of Pittsburgh's Spring 2021 Sumobot repository. Traditionally, Sumobot is a competition in which teams build and program a miniature sumobot to battle other teams' bots. 

2021 was different, however - COVID-19 ravagaed campuses, and the Sumobot competition was cancelled. We used this opportunity to learn some cool robotics topics while designing, creating, and improving upon new sumobot code. 

We began with basic bot programming - and continued into line following, PID control, state machines, localization, motion planning, and external hardware additions. 

This was completed on Pololu's Zumo32U4 sumobot. 

## Detailed below is a broad overview of the tasks we took on and achieved this semester. 

### 2/2021:

*Wooo! This is where your awesome SumoBot code goes!*

In the month of February, we introduced Git, Github, and Trello for Agile-style sprint planning. We also introduced Pololu's Zumo32U4 library, and began to implement instances of some of the bot's hardware components. 

We then began to utilize encoders to improve the control loop of the bot, as well as experiment with the bot's cpability to follow a line on the ground. 

We got it self-correcting its trajectory fairly well! 


### 3/2021:

In the month of March, we implemented PID control on both the straight line driving and line following code. We also implemented object avoidance using the bot's infared sensor. 

The trajectory correction of PID was very notable. However, we had issues with the side sensors and making contact with walls. 

Eventually, we got them to work!

<img src="https://github.com/Pitt-RAS/Sumobot-Spring-2021/blob/main/media/Line_Follower_Photo.png" width="300">

### 4/2021

In the Month of April, we really improved on our previous work. We implemented a state machine to organize the code, used the Gyroscope to measure the orientation of the bot, and attached a servo motor and Ultrasonic sensor to allow the bot to seek the optimal path for driving forward. 

We had some inital trouble with the Gyroscope, but we wrapped it all up in our awesome SODAR code: 

<img src="https://github.com/Pitt-RAS/Sumobot-Spring-2021/blob/main/media/US_Sensors.png" width="300">

<img src="https://github.com/Pitt-RAS/Sumobot-Spring-2021/blob/main/media/SODAR_Photo.png" width="300">

It was a fantastic semester, and though we were heavily restricted due to covid, we designed some innovative bot code capabilities that may not have been possible in a normal year. 

**Check out videos of the bot working in the "media" folder.**

Enjoy the repository!

  -Sumobot 2021 team
