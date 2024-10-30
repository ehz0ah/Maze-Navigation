# mBot Maze Navigation Project

## Project Documentation
[Detailed Documentation](https://github.com/ehz0ah/Maze-Navigation/blob/main/Project%20Documentation.pdf)

## Overview

This GitHub repository contains the source code and documentation for a maze navigation project using the mBot educational robot. The project utilizes an ultrasonic sensor, an infrared sensor, and a color sensor to guide the mBot through a maze. The color sensor is specifically designed to detect the color of the paper beneath the mBot at specific checkpoints.

![238075df-0e0e-455e-b4ac-4b7e33f19a00](https://github.com/user-attachments/assets/475f4616-2cab-4efc-8a08-219e5c5e8089)


## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Usage](#usage)

## Introduction

The mBot Maze Navigation project aims to demonstrate the capabilities of the mBot robot in navigating through a maze environment. The project makes use of various sensors to enable the mBot to make informed decisions about its movement.

## Features

- **Ultrasonic Sensor**: Enables the mBot to measure the distance from the left wall and nudges right accordingly.
- **Infrared Sensor**: Used for detecting how close the mbot is to the right wall and nudges left accordingly.
- **Color Sensor**: Designed to detect specific colors on the paper beneath the mBot at different checkpoints.
- **Maze Navigation Algorithm**: Implements an intelligent algorithm to guide the mBot through the maze, making decisions based on sensor inputs.
- **Checkpoints and Color Detection**: The mBot stops at the checkpoints and uses the color sensor to identify the color of the paper before completing an action according to the colour detected.

## Hardware Requirements

To replicate this project, you will need the following hardware:

- Makeblock mBot robot
- Ultrasonic sensor
- Infrared sensor (Self-Built)
- Color sensor (Self-Built)

![f2155010-9552-4c4f-912e-8a3ae9d91aaa](https://github.com/user-attachments/assets/32fa8f81-29ae-421a-b981-1098d318bb92)

- Maze environment with distinct colors at checkpoints


## Usage

1. Assemble the mBot and attach the ultrasonic sensor, infrared sensor and color sensor.
2. Place the mBot in the maze environment.
3. Power on the mBot and run the uploaded code using arduino.
