// This library stores


// The local map represents a one meter (100 centimeter) square map
// that stores the evironment and the robots location within the 
// local map: 0 = OPEN, 1 = WALL, 2 = ROBOT
#define SIZE 100 
int local_map[SIZE][SIZE];

// The degree map checks whether the data given by the lidar has already
// been received in the robot's current position based on degree
#define MIN_DEGREES 200
bool degree[360];
int degrees_received;

// The robot's dimensions 
#define ROBOT_WIDTH 10
#define ROBOT_LENGTH 10

// The robot's X and Y position in proportion to local map's index along
// with the robot's orientation based on the starting orientation
int robot_X;
int robot_Y;
int robot_orientation;

// updates the local map with objects recorded from lidar
// angle is in degrees and distance is in mm
void update_local_map(float angle, float distance){
  // convert distance in meters to distance in centimeters
  int new_distance = int(distance / 10);

  int object_X = new_distance * cos(angle + robot_orientation) + robot_X;
  int object_Y = new_distance * sin(angle + robot_orientation) + robot_Y;

  local_map[object_X][object_Y] = 1;
}

// updates variables to the robot's new location
void update_position(int X, int Y){
  // clear robot's previous position from local map 
  local_map[robot_X][robot_Y] = 0;

  // update local map and robot's coordinates with new position
  local_map[X][Y] = 2;
  robot_X = X;
  robot_Y = Y;
}
// updates orientation to the robot's new orientation
void update_orientation(int orient){
  robot_orientation = orient;
}

void scan_360(RPLIDAR lidar){
  while(degrees_received == MIN_DEGREES){
    // round angle to nearest whole number
    int new_angle = round_degree(lidar.getCurrentPoint().angle);

    // check if angle has already been received
    if(!degree[new_angle]){
      return;
    }

    // if new angle, update local map
    degree[new_angle] = true;
    degrees_received++;
    update_local_map(angle, lidar.getCurrentPoint().distance);
  }
}

int round_degree(float angle){
  // trancate angle
  int degree = int(angle);

  // returned rounded value
  if(angle >= degree + 0.5)
    return degree + 1;
  return degree;
}

