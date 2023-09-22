Obstacle Management
====
To create a bot that can navigate a track with obstacles using an ultrasonic sensor and gyroscope, you'll need to implement a control algorithm that allows the bot to detect obstacles, stop when necessary, and navigate around them. Below is a high-level strategy along with some pseudo code to help you get started.
## **Strategy:**

1. Initialize the bot with the necessary sensors and gyroscope.
2. Start the bot and begin the first lap.
3. Continuously monitor the ultrasonic sensor to detect obstacles in the path.
4. Use the gyroscope to maintain the bot's direction and orientation.
5. When an obstacle is detected:
   - Determine the direction of the obstacle (left or right).
   - Turn the bot in the opposite direction to avoid the obstacle.
   - Resume forward movement once the obstacle is clear.
6. Continue navigating the track and detecting obstacles until completing three laps.

Additionally, we need to fine-tune the values and thresholds for obstacle detection and the turning angles based on your bot's characteristics and the track layout. Testing and iterating on the code and parameters will be crucial to ensure your bot successfully completes the laps while avoiding obstacles.
