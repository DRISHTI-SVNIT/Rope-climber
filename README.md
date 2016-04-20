# Rope-climber
A robot that can travel through the terrains where wheeled mobility is hard. It uses motors to trace through a rope between destinations.

## How to use
1. The robot has a main power switch (big electrical switch). Switch it on.
2. If the connections were correct, motor driver and Arduino LEDS will light up. Make sure the XBee is connected and lit.
3. Plug XBee in your PC and open XCTU software for Serial communication.
4. Wait for the yellow light on XBee to be lit then you are ready to go. Look in #Troubleshooting section if the light is not yellow.
5. Once connected, send "m" for manual mode and "x" for autonomous mode.
6. Pressing "s" stops the robot irrespective of the mode and sets the robot in manual mode.

### Manual mode - 
* Controls - 

a - Direction 1

d - Direction 2

## Troubleshooting
### XBee
* Yellow light is not lit - 
1. Get XBee closer to the robot. (Range problem)
2. Check RX TX connections.
3. Restart the robot.
4. Plug in the XBee again in the PC.
