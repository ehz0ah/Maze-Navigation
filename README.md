# mBot Maze Navigation Project

## Overview

This GitHub repository contains the source code and documentation for a maze navigation project using the mBot educational robot. The project utilizes an ultrasonic sensor, an infrared sensor, and a color sensor to guide the mBot through a maze. The color sensor is specifically designed to detect the color of the paper beneath the mBot at specific checkpoints.


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
- **Color Sensor**: Designed to detect specific colors on the paper beneath the mBot at different checkpoints 
- **Maze Navigation Algorithm**: Implements an intelligent algorithm to guide the mBot through the maze, making decisions based on sensor inputs.
- **Checkpoints and Color Detection**: The mBot stops at the checkpoints and uses the color sensor to identify the color of the paper before completing an action according to the colour detected.

## Hardware Requirements

To replicate this project, you will need the following hardware:

- Makeblock mBot robot
- Ultrasonic sensor
- Infrared sensor
- Color sensor
- Maze environment with distinct colors at checkpoints


## Usage

1. Assemble the mBot and attach the ultrasonic sensor, infrared sensor (self-built), and color sensor (self-built).
2. Place the mBot in the maze environment.
3. Power on the mBot and run the uploaded code using arduino.
