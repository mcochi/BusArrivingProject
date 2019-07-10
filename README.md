# BusArrivingProject

## General Description
Everyone hates losing the bus and installing useless apps on the mobile that you're going to use once in life. 
For solving this problem, I've developed a new system that will ask an API Rest Service when the next bus will arrive. Once API Rest service has responded, time left to the next bus will be displayed in an LCD Screen. An ESP8266 will be the board responsible for asking the API REST Service and the LCD screen will be controlled by an Arduino Uno.
I've personalized this project for Zaragoza API. This API provides information about the time to arrive on the next bus or geographical coordinates of bus stops, for instance. 
In my case, I have 2 bus lines that I'm interested in, 39 and CI2. So, I've prepared the system for selecting the bus line I'm interested in each moment, and time is displayed on the LCD screen. If I want not to arrive late for the buses, I've to go out from home 5 minutes before the bus arrive. Due to this situation, a buzzer will sound every time there are 5 minutes left to the next bus. 

## Fritzing Schema
Schema is shown below:
![BusArrivingProject Schema](https://github.com/mcochi/BusArrivingProject/blob/master/BusArrivingProject.fzz)
