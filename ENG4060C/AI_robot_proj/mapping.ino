
/*
 * RoboPeak RPLIDAR Arduino Example
 * This example shows the easy and common way to fetch data from an RPLIDAR
 *
 * You may freely add your application code based on this template
 *
 * USAGE:
 * ---------------------------------
 * 1. Download this sketch code to your Arduino board
 * 2. Connect the RPLIDAR's serial port (RX/TX/GND) to your Arduino board (Pin 0 and Pin1)
 * 3. Connect the RPLIDAR's motor ctrl pin to the Arduino board pin 3
 */

// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
#include <RPLidar.h.ino>

// Create an driver instance
RPLidar lidar;

#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal

#define WIDTH 1000
#define LENGTH 1000

bool global_map[WIDTH][LENGTH];
first_iteration = true found_target = false

    void
    setup()
{
  // bind the RPLIDAR driver to the arduino hardware serial
  lidar.begin(Serial);

  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

void loop()
{
  if (IS_OK(lidar.waitPoint()))
  {
    float distance = lidar.getCurrentPoint().distance; // distance value in mm unit
    float angle = lidar.getCurrentPoint().angle;       // anglue value in degree
    bool startBit = lidar.getCurrentPoint().startBit;  // whether this point is belong to a new scan
    byte quality = lidar.getCurrentPoint().quality;    // quality of the current measurement

    // perform data processing here...
  }
  else
  {
    analogWrite(RPLIDAR_MOTOR, 0); // stop the rplidar motor

    // try to detect RPLIDAR...
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100)))
    {
      // detected...
      lidar.startScan();

      // start motor rotating at max allowed speed
      analogWrite(RPLIDAR_MOTOR, 255);
      delay(1000);
    }
  }
}
