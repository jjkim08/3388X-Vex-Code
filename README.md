# 3388X VEX Code

Code for VEX V5 Team 3388X.

This repo is where we keep the code for our robot, including driver control, autonomous routines, and other stuff used throughout the season.

## Setup

This project uses:

* VEX V5
* C++
* VS Code
* VEX VS Code Extension

Clone the repo and open it in VS Code:

```bash
git clone https://github.com/jjkim08/3388X-Vex-Code.git
```

From there, connect the V5 Brain and download the program using the VEX extension.

## Structure

```text
3388X-Vex-Code/
├── src/        # Robot code
├── include/    # Header files
├── vex/        # VEX project files
├── .vscode/    # VS Code settings
└── makefile    # Build configuration
```

## Code

Most of the code is in `src/`.

This includes things like:

* Driver control
* Autonomous routines
* Drivetrain code
* Motors and sensors
* Robot configuration
* Utility functions

The code will change throughout the season as we test new things and make improvements to the robot.

## Development

When making changes, test them on the actual robot before pushing them.

For bigger changes, use a separate branch so we can test things without messing with the main code.

```bash
git checkout -b new-feature
```

Once everything works:

```bash
git add .
git commit -m "describe your changes"
git push
```

## Team

**3388X**

VEX V5 Robotics
