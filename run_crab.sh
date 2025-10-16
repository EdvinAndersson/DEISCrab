#!/bin/bash

# Name of your executable
TARGET="./crab.out"

# Kill any existing pigpiod instances
sudo killall pigpiod

# Remove stale PID file if it exists
sudo rm -f /var/run/pigpio.pid

# Start pigpio daemon
sudo pigpiod

# Give the daemon a moment to start
sleep 1

# Run your C++ program with sudo
sudo $TARGET