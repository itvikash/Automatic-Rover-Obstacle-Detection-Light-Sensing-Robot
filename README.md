# Automatic Rover — Obstacle Detection & Light-Sensing Robot

A four-wheel drive rover built with an Arduino Uno, combining automatic obstacle avoidance and ambient light sensing, with support for manual RC control.


## Description

This project is a four-wheeled automatic rover powered by an Arduino Uno. It uses an ultrasonic sensor to detect and avoid obstacles in its path, and an LDR (Light Dependent Resistor) sensor to sense ambient light conditions. Movement is handled by four heavy-duty DC motors, giving the rover reliable drive power. In addition to autonomous operation, the rover supports manual control via an RC remote, allowing it to switch between automatic and manual driving modes.

## Features

- Four-wheel drive with heavy-duty motors for reliable movement
- Ultrasonic sensor for real-time obstacle detection and avoidance
- LDR sensor for ambient light sensing
- RC remote control support with auto/manual mode switching
- Built on Arduino Uno

## Hardware Components

| Component | Description |
|---|---|
| Arduino Uno | Main microcontroller |
| Ultrasonic Sensor (HC-SR04) | Obstacle detection |
| LDR Sensor | Light sensing |
| Heavy-Duty DC Motors (x4) | Drive motors |
| Motor Driver (2-channel) | Controls the 4 drive motors |
| Chassis | Four-wheel/tracked base |
| RC Transmitter & Receiver (FlySky) | Manual control |

## Remote Control

The rover can be driven manually using this RC transmitter/receiver setup, or left to run autonomously in obstacle-avoidance mode.

## How It Works

The Arduino Uno continuously reads input from the ultrasonic sensor to detect obstacles ahead and from the LDR sensor to monitor ambient light. In automatic mode, if an obstacle is detected within range, the rover stops, reverses briefly, and turns to find a clear path before continuing forward. A mode switch on the RC transmitter lets the operator override this and drive the rover manually. Motor direction and speed are controlled through a 2-channel motor driver connected to the four drive motors.

## Code

The Arduino sketch (`rover_code.ino`) is included in this repository and handles:
- Ultrasonic-based obstacle avoidance
- LDR light-level monitoring
- RC signal reading for manual control
- Auto/Manual mode switching
- Motor control functions (forward, backward, turn left, turn right, stop)

> **Note:** Pin assignments and threshold values in the code are set based on common wiring conventions for these components. Verify and update them to match your actual circuit before uploading.

```cpp
// See rover_code.ino for the full sketch
```

## Getting Started

1. Wire the components as per the pin definitions at the top of `rover_code.ino` (update to match your build).
2. Open `rover_code.ino` in the Arduino IDE.
3. Select **Arduino Uno** as the board and the correct COM port.
4. Upload the sketch.
5. Power the rover and test in both auto and manual modes.

## Author

Vikash Kumar — B.Tech, Electrical and Electronics Engineering (3rd Year)

---

