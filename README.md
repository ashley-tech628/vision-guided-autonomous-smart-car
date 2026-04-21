# Vision-Guided Autonomous Smart Car on TC264

## Overview
This project is a first-prize autonomous smart car system developed for intelligent vehicle competition scenarios. It is built on the Infineon TC264 platform and integrates embedded vision, real-time control, and event-aware track handling into a complete autonomous driving pipeline.

The system uses an MT9V03X grayscale camera for real-time track perception, extracts lane boundaries and centerline information, and drives the vehicle through closed-loop steering and speed control. In addition to standard lane following, the software includes dedicated logic for handling special track elements such as roundabouts, intersections, start-line detection, and parking behavior.

This repository represents a full embedded autonomy project rather than a standalone algorithm demo. It combines perception, planning-oriented target generation, control, parameter tuning, and runtime debugging into a deployable on-vehicle software stack.

---

## Award
**First Prize** in an intelligent vehicle competition project.

> Replace this line with the exact competition name and year if you want to make it even stronger.

---

## Key Highlights
- Built on **Infineon TC264D**
- Real-time grayscale vision using **MT9V03X**
- Dual-core task partition for control and image processing
- Robust lane-boundary extraction and centerline generation
- Weighted target-point computation for steering guidance
- Closed-loop steering and speed control
- Support for complex track elements:
  - roundabouts
  - intersections
  - start / finish line detection
  - parking / garage-entry behavior
- Runtime parameter tuning through LCD and keyboard interface
- Wireless debugging / image transmission support

---

## System Architecture
The software follows a perception-to-control pipeline:

1. **Image Acquisition**  
   The camera captures grayscale road images in real time.

2. **Image Processing**  
   The system performs thresholding, binarization, boundary extraction, centerline repair, and target-point calculation.

3. **Track-Element Understanding**  
   Special scenarios such as roundabouts, intersections, starting lines, and parking zones are detected and handled through dedicated logic.

4. **Motion Control**  
   Steering and motor commands are generated using closed-loop control based on image-derived path error and encoder feedback.

5. **Runtime Interaction and Debugging**  
   Parameters can be tuned on-board, while image and debugging data can be transmitted for visualization and analysis.

---

## Core Features

### 1. Real-Time Vision-Based Lane Detection
The project uses camera-based perception to detect road boundaries and estimate the centerline for navigation. The image-processing pipeline includes:
- adaptive thresholding
- region-based Otsu thresholding
- left / right boundary extraction
- centerline reconstruction and repair
- weighted target-point computation for steering

### 2. Embedded Closed-Loop Control
The vehicle uses feedback control for both steering and speed:
- steering PWM control for servo actuation
- motor speed regulation using encoder feedback
- incremental PID control
- adaptive / fuzzy control-related tuning logic

### 3. Special Track Handling
Beyond basic lane following, the codebase includes dedicated logic for competition-style road elements such as:
- roundabout detection and handling
- cross / intersection handling
- start-line recognition
- parking / garage-entry behavior

### 4. Real-Time Embedded Interaction
The system supports field debugging and parameter tuning through:
- LCD display
- keyboard-based menu interaction
- wireless data / image transmission
- flash-based parameter storage

---

## Software Architecture

### CPU0 Responsibilities
CPU0 primarily handles:
- peripheral initialization
- PWM and motor output
- encoder setup
- ADC and timer setup
- keyboard and LCD interaction
- control execution
- parameter persistence

### CPU1 Responsibilities
CPU1 primarily handles:
- waiting for camera frame completion
- running the image-processing pipeline
- updating perception results for control use

This task split improves responsiveness by separating lower-level control and hardware interaction from image-processing workloads.

---

## Technical Stack

### Hardware
- **MCU:** Infineon TC264D
- **Camera:** MT9V03X grayscale camera

### Software / Development
- Embedded C
- AURIX / TC264 embedded development environment
- PWM / encoder / timer / interrupt-based control
- On-board LCD and keyboard interaction
- Wireless debugging utilities

---

## Perception Pipeline
The perception stack includes:
- grayscale image acquisition
- threshold computation
- binary image generation
- lane-boundary extraction
- centerline generation
- weighted path-target calculation

This pipeline enables the vehicle to follow the track robustly while also providing the basis for higher-level logic such as special-element detection.

---

## Control Pipeline
The control stack includes:
- steering servo PWM output
- motor actuation
- encoder pulse acquisition
- speed closed-loop control
- direction correction from image-derived path error

Together, these modules enable stable motion control under competition-style real-time constraints.

---

## Project Structure
```text
.
├── CODE/
│   ├── control.c / control.h
│   ├── image_deal.c / image_deal.h
│   ├── PID.c / PID.h
│   ├── traffic_cricle.c / traffic_cricle.h
│   ├── keyboard.c / keyboard.h
│   ├── swj.c / swj.h
│   └── ZW_Tools.c / ZW_Tools.h
│
├── USER/
│   ├── Cpu0_Main.c
│   ├── Cpu1_Main.c
│   ├── isr.c / isr.h
│   └── TC264_config.h
│
└── Debug/
```

---

## What This Project Demonstrates
This project demonstrates practical ability across multiple engineering domains:
- embedded systems programming
- real-time control
- vision-based perception on resource-constrained hardware
- competition robotics
- system integration under timing and hardware constraints

It is not just a software simulation or algorithm prototype. It is a full embedded autonomy pipeline designed to run on an actual intelligent vehicle platform.

---

## My Contributions
My work in this project focused on building and integrating the full embedded autonomous driving stack, including:
- real-time camera-based lane perception
- lane-boundary and centerline extraction
- target-point generation for path following
- steering and speed control logic
- special-track-element handling
- runtime parameter tuning and debugging support
- end-to-end system integration across control, image processing, and interrupts

---

## Build and Run Notes
This repository contains the embedded source code for the smart car software stack.

To build and run the project, you need:
- the corresponding **TC264 hardware platform**
- the **camera and motor driver setup**
- the vendor / competition board support environment
- the associated embedded toolchain and libraries

Because this is a hardware-dependent project, it is not intended to be executed directly on a general-purpose computer.

---

## Repository Notes
For portfolio purposes, it is recommended to keep:
- `CODE/`
- `USER/`
- essential configuration files

and remove generated or unnecessary content such as:
- `Debug/`
- IDE temporary files
- automatically generated build artifacts

---

## Future Improvements
Potential future improvements include:
- more robust adaptive thresholding under changing lighting conditions
- improved curve-speed planning
- cleaner state-machine design for special track elements
- better telemetry and debugging visualization
- more modular architecture for reuse and maintenance

---


## Author
Ashley Liu
