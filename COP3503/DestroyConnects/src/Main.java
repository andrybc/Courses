/* COP 3503C Assignment 3
This program is written by: Andry Bruel Canel */



import java.util.*;
import java.math.BigInteger;

public class Main {
    static int[] parent, rank;
    static BigInteger[] size;//integer did not work on larger test cases
    static List<List<Integer>> graph;
    static List<int[]> edges;
    static List<Integer> toDestroy;
    static int n, m;
    static List<BigInteger> results;

    static void initializeDisjointSet() {
        parent = new int[n + 1];
        rank = new int[n + 1];
        size = new BigInteger[n + 1];

        for (int i = 1; i <= n; i++) {
            parent[i] = i; // each node is its own parent initially
            rank[i] = 0;   // initial rank is 0
            size[i] = BigInteger.ONE;   // each node is its own component initially
        }
    }

    static int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // path compression part
        }
        return parent[x];
    }

    static void union(int x, int y) {//union function to connect nodes
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
                size[rootX] = size[rootX].add(size[rootY]);
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
                size[rootY] = size[rootY].add(size[rootX]);
            } else {
                parent[rootY] = rootX;
                size[rootX] = size[rootX].add(size[rootY]);
                rank[rootX]++;
            }
        }
    }

    static BigInteger calculateConnectivity() {//calculates how many nodes are connected and sums the squares
        BigInteger connectivity = BigInteger.ZERO;
        boolean[] counted = new boolean[n + 1];
        for (int i = 1; i <= n; i++) {
            int root = find(i);
            if (!counted[root]) {
                connectivity = connectivity.add(size[root].multiply(size[root]));
                counted[root] = true;
            }
        }
        return connectivity;
    }

    static void generateResults() {//main function that calls function to remove
        results = new ArrayList<>();
        boolean[] isDestroyed = new boolean[m];

        // mark destroyed edges
        for (int edgeIndex : toDestroy) {
            isDestroyed[edgeIndex] = true;
        }

        // initialize disjoint set and build the graph from scratch
        initializeDisjointSet();
        for (int i = 0; i < m; i++) {
            if (!isDestroyed[i]) {
                int[] edge = edges.get(i);
                union(edge[0], edge[1]);
            }
        }

        // calculate connectivity of the starting state
        results.add(calculateConnectivity());

        // Reprocess edges in reverse order of their removal
        for (int i = toDestroy.size() - 1; i >= 0; i--) {
            int edgeIndex = toDestroy.get(i);
            int[] edge = edges.get(edgeIndex);
            union(edge[0], edge[1]);

            // Calculate connectivity after adding back each edge
            results.add(calculateConnectivity());

            // Print current state of the graph and disjoint set after each edge addition
          //  System.out.println("\nRe-adding edge: " + Arrays.toString(edges.get(edgeIndex)));
           // printGraph();
           // printDisjointSet();
        }
    }

    static void printResults() {//prints output
        for (int i = results.size() - 1; i >= 0; i--) {
            System.out.println(results.get(i));
        }
    }

    static void printGraph() {//helper function that prints out graph
        System.out.println("Graph Representation:");
        for (int i = 1; i <= n; i++) {
            System.out.print(i + ": ");
            for (int neighbor : graph.get(i)) {
                System.out.print(neighbor + " ");
            }
            System.out.println();
        }
    }

    static void printDisjointSet() {//shows whats inside disjoint set to see if the size category is changing 
        if (parent == null) {
            System.out.println("Disjoint set is not initialized.");
            return;
        }
        System.out.println("Disjoint Set Representation:");
        System.out.println("Node\tParent\tRank\tSize");
        for (int i = 1; i <= n; i++) {
            System.out.println(i + "\t" + parent[i] + "\t" + rank[i] + "\t" + size[i]);
        }
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

      
        n = scan.nextInt();
        m = scan.nextInt();
        int d = scan.nextInt();
        scan.nextLine(); 

        // initialize global lists
        graph = new ArrayList<>(n + 1);
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        edges = new ArrayList<>(m);
        toDestroy = new ArrayList<>(d);

        // initialize disjoint set before using it
        initializeDisjointSet();

        // Read in all the edges
        for (int i = 0; i < m; i++) {
            int u = scan.nextInt();
            int v = scan.nextInt();
            scan.nextLine(); // Move to the next line
            graph.get(u).add(v);
            graph.get(v).add(u);
            edges.add(new int[]{u, v});
        }

        // Read in all the edges to destroy
        for (int i = 0; i < d; i++) {
            toDestroy.add(scan.nextInt() - 1); // 1-based to 0-based index
        }

        // Print initial state for debugging
        //printGraph();
        //printDisjointSet();

        // Generate results and print them
        generateResults();
        printResults();

        scan.close();
    }
}
