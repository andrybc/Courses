
/* COP 3503C Assignment 4
This program is written by: Andry Canel*/



import java.util.*;


public class Main {

    private static char[][] grid;
    private static int rows;
    private static int cols;
    private static int[] start = new int[2];
    private static int[] end = new int[2];
    private static Map<Character, List<int[]>> teleports = new HashMap<>();
    
    private static int bfs() {
        Queue<int[]> queue = new LinkedList<>();
        boolean[][] visited = new boolean[rows][cols];
        Map<Character, Boolean> teleportVisited = new HashMap<>();

        queue.add(new int[]{start[0], start[1], 0});
        visited[start[0]][start[1]] = true;

        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int x = current[0];
            int y = current[1];
            int moves = current[2];

            // check if we have reached the end
            if (x == end[0] && y == end[1]) {
                return moves;
            }

            // move in all four directions
            for (int[] dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                if (isValidMove(newX, newY, visited)) {
                    visited[newX][newY] = true;
                    queue.add(new int[]{newX, newY, moves + 1});
                }
            }

            //teleport if on a teleportation square
            if (grid[x][y] >= 'A' && grid[x][y] <= 'Z') { // directly checking for uppercase letters
                char teleportChar = grid[x][y];
                if (!teleportVisited.getOrDefault(teleportChar, false)) {
                    teleportVisited.put(teleportChar, true);
                    for (int[] pos : teleports.get(teleportChar)) {
                        int newX = pos[0];
                        int newY = pos[1];
                        if (!visited[newX][newY]) {
                            visited[newX][newY] = true;
                            queue.add(new int[]{newX, newY, moves + 1});
                        }
                    }
                }
            }
        }

        return -1; // if no path is found
    }

    private static boolean isValidMove(int x, int y, boolean[][] visited) {
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] != '!' && !visited[x][y];
    }
    
    private static void printTeleports() {
        System.out.println("Teleports:");
        for (Map.Entry<Character, List<int[]>> entry : teleports.entrySet()) {
            char teleportChar = entry.getKey();
            List<int[]> positions = entry.getValue();
            System.out.print(teleportChar + ": ");
            for (int[] pos : positions) {
                System.out.print(Arrays.toString(pos) + " ");
            }
            System.out.println();
        }
    }
	public static void main(String[] args) {
		// TODO Auto-generated method stub
        Scanner scanner = new Scanner(System.in);

     
        rows = scanner.nextInt();
        cols = scanner.nextInt();
        scanner.nextLine(); 

        // initializing the grid
        grid = new char[rows][cols];

        // Reading the grid
        for (int i = 0; i < rows; i++) {
            String line = scanner.nextLine();
            for (int j = 0; j < cols; j++) {
                char ch = line.charAt(j);
                grid[i][j] = ch;
                
                // Identifying start, end, and teleportation squares
                if (ch == '*') {
                    start[0] = i;
                    start[1] = j;
                } else if (ch == '$') {
                    end[0] = i;
                    end[1] = j;
                } else if (Character.isUpperCase(ch)) {
                    teleports.putIfAbsent(ch, new ArrayList<>());
                    teleports.get(ch).add(new int[]{i, j});
                }
            }
        }

      /*  // code to see if the input parsing is corect
        System.out.println("Grid:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(grid[i][j]);
            }
            System.out.println();
        }
        System.out.println("Start: " + Arrays.toString(start));
        System.out.println("End: " + Arrays.toString(end));
       // System.out.println("Teleports: " + teleports);
        printTeleports();
        */
        // Execute BFS to find the shortest path
        int result = bfs();
        if (result == -1) {
            System.out.println("Stuck, we need help!");
        } else {
            System.out.println(result);
        }
	}

}
