# Engineering materials | Team Electrobots | Bangladesh
----

This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2023.

----
## Team Members:

- Zuniyed Hossain Bhuiyan
- L.M Mahir Labib
- Tanvir Rahman Saad
----

## Contents

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `Mobility Management` contains details of the movement management of the bot, chasis design,power,torque etc.
* `Power and Sense Management` contains discussion about the power supply and sensors used in the vehicle.
* `Obstacle Management` include the strategy for the vehicle to negotiate the obstacle course for all the challenges.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.


The "Electrobot Autonomous Vehicle" project is an innovative endeavor that combines cutting-edge technologies to create a self-guided vehicle capable of intelligent navigation. This repository serves as a central hub for all essential files, documentation, and information related to the project.The project utilizes an ESP32-based development board known as the "JRC Board." This versatile and powerful board forms the foundation of the vehicle's control system.To enable advanced object recognition capabilities, the vehicle is equipped with a DFROBOT Gravity Huskylens, an AI-based camera. This camera plays a crucial role in identifying and interacting with objects in the vehicle's environment.The project incorporates an MPU-6050 gyroscope and accelerometer sensor. This sensor suite provides critical data for lap counting and monitoring angular velocity. The angular velocity measurements are given in millivolts per degree per second (mV/deg/s).

# Electric System design: 

We have choosed the 

## Software Setup Procedure

![ide_dl](https://github.com/LabibProjects/Bangladesh_Team-Electrobot/blob/main/other/ide_dl.png)
- At first, we will have to download and install the most up-to-date version of the Arduino IDE on our computer. We can find the software at arduino.cc/en/Main/Software.

![ide_set_1](https://github.com/LabibProjects/Bangladesh_Team-Electrobot/blob/main/other/ide_set_1.png)   |  ![ide_set_2](https://github.com/LabibProjects/Bangladesh_Team-Electrobot/blob/main/other/ide_set_2.png)
- In our Arduino IDE, we need to go to File > Preferences, and then enter the following into the 'Additional Board Manager URLs' field. Finally, we click OK.
`https://espressif.github.io/arduino-esp32/package_esp32_index.json`

![ide_set_3](https://github.com/LabibProjects/Bangladesh_Team-Electrobot/blob/main/other/ide_set_3.png)
- On the left side of our IDE we will have to open our Board Manager . Press install button for the "ESP32 by Espressif Systems".

![ide_set_4](https://github.com/LabibProjects/Bangladesh_Team-Electrobot/blob/main/other/ide_set_4.png)
- Now we will have to select our board so on the upper left side of IDE we will select our board, "ESP32 DEV MODULE" then we will select our prefered board where we have connected our JRC board.

![ide_set_5](https://github.com/LabibProjects/Bangladesh_Team-Electrobot/blob/main/other/ide_set_5.png)
- Finally our task is to upload the code clicking "→" icon we upload our code. 

- Now we can turn on the toggle switch after placing robot on track and it will start doing the laps.
