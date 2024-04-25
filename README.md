# Control System for Elevator Using PLC and Arduino

## Project Overview

This project involves the design and implementation of a control system for an elevator using Programmable Logic Controllers (PLC) and Arduino microcontrollers. The system facilitates movement between four floors using a series of inputs from buttons and sensors, managing the elevator's motor operations based on state transitions and sensor readings.

**The project covers the 0,1,2 floors, and the** **initial state is 1st floor.**

## Features

- **PLC and Arduino Integration**: Utilizes both PLC and Arduino to achieve precise control over elevator mechanics.
- **State Machine Logic**: Implements a detailed state machine for handling elevator position and movement commands.
- **Input Handling**: Processes inputs from floor request buttons and floor presence sensors to direct elevator movement.
- **Motor Control**: Manages elevator motor operations with forward/reverse and stop/start functionalities.

## System Requirements

- PLC system capable of handling multiple inputs and outputs.
- Arduino microcontroller for additional processing and control.
- Buttons for floor requests and sensors for detecting the elevator's current floor.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Floressek/Lift_siemens.git
   ```
2. **Set up the hardware connections** as per the schematics provided in the schematics directory.
3. **Upload the Arduino sketch** found in the `src` directory to your Arduino.

## Usage

After setting up the system:
- Press the designated button to request the elevator to move to a desired floor.
- The system reads the input and checks the current elevator state to decide the direction and motion of the elevator.

## Diagrams and State Transitions

- Detailed wiring diagrams and state transition diagrams are available in the `docs` folder.

## Contributing

Contributions to this project are welcome. Please ensure to follow the guidelines in the `CONTRIBUTING.md` file.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## Authors

- **Szymon Florek** - Initial work and implementation.

---
