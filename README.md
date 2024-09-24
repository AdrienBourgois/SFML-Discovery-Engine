# SFML-Discovery-Engine

## Introduction
Welcome to the SFML Discovery Engine, a micro game engine designed to help users discover SFML and quickly prototype games. This engine is fully portable and easy to set up, making it an excellent tool for educators, students, and hobbyists interested in exploring the fundamentals of game development.

## Features
- **Fully Portable**: All necessary libraries are included within the project directory. No additional installations are required.
- **Unity-like Architecture**: Implements a familiar scene, GameObjects, and components system inspired by Unity to manage game entities and their behaviors.
- **Integrated Debugging with ImGUI**: Features ImGUI integration for real-time debugging and UI management.
- **Visual Studio Solution**: Includes a Visual Studio solution with two projects: one for the engine and another for game development using the engine.

## Getting Started
### Prerequisites
No external installations are needed as all dependencies are included.

### Installation
Clone this repository:
`git clone https://github.com/AdrienBourgois/SFML-Discovery-Engine.git`

### Compiling and Running
- Open the solution (.sln file) in Visual Studio.
- Build the solution to compile the projects.
- Set the Game project as the startup project and run it to see the engine in action.

## Project Structure
- **Engine**: Contains all the core functionality, including modules for rendering, input handling, and scene management. This project is built as a static library (.lib) used by the **Game** project.
- **Game**: A separate project set up to use the engine for game logic, demonstrating how to implement gameplay features. It builds as the final executable.

## Directory Overview
```
/SFML-Discovery-Engine
  /Engine                   # Engine functionality
  /Game                     # Game project using the engine
  /include                  # All external headers for SFML and ImGUI
  /lib                      # Static libraries needed for SFML and ImGUI
  /Assets                   # Graphics and other assets used by the engine and the game
  .gitignore                # Lists files excluded from version control
  LICENSE                   # MIT License details
  README.md                 # This file
  SFML Discovery Engine.sln # The Visual Studio solution for development
```

## Support
If this project aids your learning or game development, please share your work with me. I'm especially interested in hearing from educators who use this project in their courses!
