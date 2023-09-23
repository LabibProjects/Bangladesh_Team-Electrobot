**Power and Sense Management**
====
In the realm of robotics, effective power and sense management is the linchpin of our robot's performance. Our cutting-edge system ensures optimal resource allocation, revolutionizing how robots interact with their surroundings.

## 1. Power Management: 
<img align="center" width="565" alt="Power" src="https://github.com/LabibProjects/Bangladesh_Team-Electrobot/assets/133244520/1dc2b2e0-065b-4f39-ad3b-c7338fe91b3e">

   At first from lipo battery we are fetching 11.1v and being 12v by XL4015. then MP1184 are cosuming power to 5v for the sensor e.g. Huskylens, URM09 ultrasonic sensor and gyroscope. Laterby we are suplying 7v to servo 12v to BTS7960 and motor being powered to.
## 2. Sensors: 
<img width="571" alt="Sensor" src="https://github.com/LabibProjects/Bangladesh_Team-Electrobot/assets/133244520/43bbd256-99ae-4685-831e-1c7c8020c8ad">

- #### **Ultrasonic Sensor:**
   <img width="150" alt="" src="https://github.com/LabibProjects/Bangladesh_Team-Electrobot/assets/133244520/c9ecbc5d-8167-4a29-850e-549671265471">

  
   The URM09 is an ultrasonic distance sensor used for measuring distances. We're powering it with a stable 5V supply obtained from an MP1584 voltage regulator connected to an 11.1V LiPo battery. This setup ensures reliable distance measurements and efficient power management for our robot.


- #### **Huskylens:**
  <img width="150" alt="" src="https://github.com/LabibProjects/Bangladesh_Team-Electrobot/assets/133244520/3ae58273-62b2-4618-b277-88c366db123c">

The HuskyLens is a smart vision sensor used for various applications, including object detection, tracking, and recognition. In our configuration, we mentioned that the HuskyLens is powered by 5V, which is sourced from a JRC Board by i2c ports. This JRC Board is connected to an MP1584 voltage regulator, which, in turn, is connected to an XT4015 module. All of these components are powered by an 11.1V LiPo battery.
- #### **Gyroscope:**
  <img width="150" alt="MPU" src="https://github.com/LabibProjects/Bangladesh_Team-Electrobot/assets/133244520/91c8ec6c-5d88-4726-917d-88b6b141fade">


The MPU6050 is a popular gyroscope and accelerometer sensor used for motion sensing and orientation tracking in various applications, including robotics and motion-controlled devices. In our setup, the MPU6050 is powered by a 5V supply sourced from a JRC Board, which itself receives power from an MP1584 voltage regulator. This MP1584 regulator is connected to an XT4015 module, and the entire system is powered by an 11.1V LiPo battery.
