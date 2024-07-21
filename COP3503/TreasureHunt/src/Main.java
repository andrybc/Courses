/* COP 3503C Assignment 5
This program is written by: Andry Canel*/
import java.util.*;


class Edge {
    int source, dest, weight;
    public Edge(int source, int dest, int weight) {
        this.source = source;
        this.dest = dest;
        this.weight = weight;
    }
}

class Node {
    int vertex, weight;
    public Node(int vertex, int weight) {
        this.vertex = vertex;
        this.weight = weight;
    }
}

class Graph {
    List<List<Edge>> adjList = null;

    Graph(int n) {
        adjList = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adjList.add(new ArrayList<>());
        }
    }

    void addEdge(int source, int dest, int weight) {
        adjList.get(source).add(new Edge(source, dest, weight));
        adjList.get(dest).add(new Edge(dest, source, weight)); // since the graph is bidirectional
    }
}

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Parse the first line of input
        int C = scanner.nextInt(); 
        int R = scanner.nextInt(); 
        int S = scanner.nextInt() - 1; 
        
        // Initialize the graph
        Graph graph = new Graph(C);
        
        // Parse the roads
        for (int i = 0; i < R; i++) {
            int v = scanner.nextInt() - 1; 
            int u = scanner.nextInt() - 1; 
            int w = scanner.nextInt(); 
            graph.addEdge(v, u, w);
        }
        
        // Parse the distance L
        int L = scanner.nextInt();
        
      
        int[] dist = new int[C];
        boolean[] done = new boolean[C];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[S] = 0;

        // Run Dijkstra's Algorithm
        dijkstra(graph, S, C, dist, done);

        // Count treasures in cities and on roads
        int treasuresInCities = countTreasuresInCities(dist, L);
        int treasuresOnRoads = countTreasuresOnRoads(graph, dist, L, S);

        // Output the results
        System.out.println("In city: " + treasuresInCities);
        System.out.println("On the road: " + treasuresOnRoads);

        scanner.close();
    }

    public static void dijkstra(Graph graph, int source, int n, int[] dist, boolean[] done) {
        PriorityQueue<Node> minHeap = new PriorityQueue<>(Comparator.comparingInt(node -> node.weight));
        minHeap.add(new Node(source, 0));

        while (!minHeap.isEmpty()) {
            Node node = minHeap.poll();
            int u = node.vertex;

            if (done[u]) continue;
            done[u] = true;

            for (Edge edge : graph.adjList.get(u)) {
                int v = edge.dest;
                int weight = edge.weight;

                if (!done[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    minHeap.add(new Node(v, dist[v]));
                }
            }
        }
    }

    public static int countTreasuresInCities(int[] dist, int L) {
        int count = 0;
        for (int i = 0; i < dist.length; i++) {
            if (dist[i] == L) {
                System.out.println("1 treasure is in the city "+ (i+1));

                count++;
            }
        }
        return count;
    }

    public static int countTreasuresOnRoads(Graph graph, int[] dist, int L, int capital) {
        int count = 0;
        Set<String> countedEdges = new HashSet<>(); // To keep track of counted edges
        Set<String> countedTreasureLocations = new HashSet<>(); // To keep track of counted treasure locations

        for (List<Edge> edges : graph.adjList) {
            for (Edge edge : edges) {
                int u = edge.source;
                int v = edge.dest;
                int weight = edge.weight;

                // Ensure the edge is not counted twice
                String edgeKey = u < v ? u + "-" + v : v + "-" + u;
                if (countedEdges.contains(edgeKey)) continue;
                countedEdges.add(edgeKey);

                // Check if there is a point on the road from u to v that is exactly L distance from the capital
                if (dist[u] < L && L < dist[u] + weight && v != capital) {
                    int potentialTreasureDist = L - dist[u];
                    String treasureLocationKey = edgeKey + "-" + potentialTreasureDist;
                    int result = isShortestPath(dist, u, v, potentialTreasureDist, L, weight);
                    if (result == 1) {
                        System.out.println("1 treasure is on the road (" + (u + 1) + ", " + (v + 1) + ") at distance " + potentialTreasureDist + " from city " + (u + 1));
                        count++;
                    } else if (result == 2) {
                        System.out.println("1 treasure is on the road (" + (u + 1) + ", " + (v + 1) + ") at distance " + potentialTreasureDist + " from city " + (u + 1));
                        count++;
                        countedEdges.add(edgeKey); // Mark the edge to avoid double counting
                        continue;
                    }
                    countedTreasureLocations.add(treasureLocationKey);
                }
              //  if (countedEdges.contains(edgeKey)) continue;
                // Check if there is a point on the road from v to u that is exactly L distance from the capital
                if (dist[v] < L && L < dist[v] + weight&& u != capital) {
                    int potentialTreasureDist = L - dist[v];
                    String treasureLocationKey = edgeKey + "-" + (weight - potentialTreasureDist);
                    int result = isShortestPath(dist, v, u, potentialTreasureDist, L, weight);
                    if (result == 1) {
                        System.out.println("1 treasure is on the road (" + (v + 1) + ", " + (u + 1) + ") at distance " + potentialTreasureDist + " from city " + (v + 1));
                        count++;
                    } else if (result == 2) {
                        System.out.println("1 treasure is on the road (" + (v + 1) + ", " + (u + 1) + ") at distance " + potentialTreasureDist + " from city " + (v + 1));
                        count++;
                        countedEdges.add(edgeKey); // Mark the edge to avoid double counting
                    }
                    countedTreasureLocations.add(treasureLocationKey);
                }
            }
        }
        return count;
    }

    public static int isShortestPath(int[] dist, int u, int v, int potentialTreasureDist, int L, int weight) {
    	boolean isSameLocationFromBothEnds = (potentialTreasureDist == weight - (L - dist[v]));
        if ((dist[u] + potentialTreasureDist == L) && (dist[v] + weight - potentialTreasureDist >= L)) {
            if (isSameLocationFromBothEnds) {
            	System.out.println("treasure at same location!!");
                return 2; // Both ways, same location
            }
            return 1; // Shortest path
        }
        return 0; // Not the shortest path
    }
}
