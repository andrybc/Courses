#include "motor_encoder.ino"
#include "my_lidar.ino"

// The dimensions of the local map (same as `my_lidar.ino`)
#define SIZE 100
#define CELL_SIZE 10 // Each cell represents 10 cm in the real world

// Variables for the starting point and goal position
int startX = 50, startY = 50; // Starting position in `local_map` indices
int robotTargetX, robotTargetY;

// Queue for Breadth-First Search (BFS)
struct Node
{
    int x, y;
    int cost;
};
Node queue[SIZE * SIZE];
int front = 0, rear = 0;

// Movement directions for BFS: Up, Down, Left, Right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// Map to track visited nodes during BFS
bool visited[SIZE][SIZE];

// Backtracking array to store the path
Node parent[SIZE][SIZE];

// Path array for the robot
Node path[SIZE * SIZE];
int pathLength = 0;

// Initialize the robot's position
void setup()
{
    setupMotors();
    lidar.begin(Serial);
    pinMode(RPLIDAR_MOTOR, OUTPUT);
    analogWrite(RPLIDAR_MOTOR, 255);
    Serial.begin(9600);

    // Initialize the robot's starting position
    robotTargetX = startX;
    robotTargetY = startY;
}

// Main loop
void loop()
{
    if (Serial.available())
    {
        char command = Serial.read();

        if (command == 'r')
        { // Command to return to the starting point
            if (findPath(robotTargetX, robotTargetY, startX, startY))
            {
                followPath();
            }
            else
            {
                Serial.println("No path found to the starting point!");
            }
        }
    }

    updateLidarAndMap();
}

// Function to calculate the shortest path using BFS
bool findPath(int startX, int startY, int goalX, int goalY)
{
    // Reset BFS structures
    front = rear = 0;
    memset(visited, false, sizeof(visited));
    memset(parent, -1, sizeof(parent));

    // Initialize the queue with the starting position
    queue[rear++] = {startX, startY, 0};
    visited[startX][startY] = true;

    // Perform BFS
    while (front < rear)
    {
        Node current = queue[front++];
        if (current.x == goalX && current.y == goalY)
        {
            reconstructPath(current);
            return true;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValidCell(nx, ny) && !visited[nx][ny] && local_map[nx][ny] != 1)
            {
                visited[nx][ny] = true;
                queue[rear++] = {nx, ny, current.cost + 1};
                parent[nx][ny] = current;
            }
        }
    }
    return false;
}

// Function to validate if a cell is within bounds and walkable
bool isValidCell(int x, int y)
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// Function to reconstruct the path from goal to start
void reconstructPath(Node current)
{
    pathLength = 0;
    while (parent[current.x][current.y].x != -1)
    {
        path[pathLength++] = current;
        current = parent[current.x][current.y];
    }
}

// Function to follow the calculated path back to the starting point
void followPath()
{
    for (int i = pathLength - 1; i >= 0; i--)
    {
        int targetX = path[i].x;
        int targetY = path[i].y;

        moveToCell(targetX, targetY);
    }
    stopMotors();
    Serial.println("Reached the starting point!");
}

// Function to move the robot to a specific cell
void moveToCell(int targetX, int targetY)
{
    float deltaX = (targetX - robotTargetX) * CELL_SIZE;
    float deltaY = (targetY - robotTargetY) * CELL_SIZE;

    float targetTheta = atan2(deltaY, deltaX);
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    turnAngle(targetTheta - robotTheta, SPEED);
    moveDistance(distance, SPEED);

    robotTargetX = targetX;
    robotTargetY = targetY;
}
