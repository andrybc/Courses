/*This code was discussed in the lab*/
/*Kruskal's minimum spanning tree that uses disjoint sets for detecting cycle*/
/*This code was adapted from a code avaialable at geeksforgeeks.org*/

import java.util.*;

public class Kruskal_ds {
    class pair {
        private int ID; 
        private int height;
        public pair(int myNum, int myHeight) {
            ID = myNum;
            height = myHeight;
        }
    
        public int getHeight() {
            return height;
        }
    
        public int getID() {
            return ID;
        }
    
        public void incHeight() {
            height++;
        }
    
        public void decHeight() {
            height--;
        }
    
        public void setID(int newID) {
            ID = newID;
        }
    }

    class DisjointSet{
        private pair[] parents;
        // Create the initial state of a disjoint set of n elements, 0 to n-1.
	    public DisjointSet(int n) {
            // All nodes start as leaf nodes.
            parents = new pair[n];
            for (int i=0; i<n; i++)
                parents[i] = new pair(i, 0); //0 is height 0. parent[i]'s parent is i now
	    }

        // Returns the root node of the tree storing id.
    	public int find(int id) {
            // I am the root of the tree)
            if (id == parents[id].getID()) 
                return id;
            // Find my parent's root.
            int res = find(parents[id].getID());
        
            // if res is not mu existing parent, make it parent
            if (res != parents[id].getID())
            {
                // Attach me directly to the root of my tree.
                parents[id].setID(res);
                parents[res].decHeight(); //decrease height as id is leveled up
            }
            return res;
        }
        
        public boolean union(int id1, int id2) {
    
            // Find the parents of both nodes.
            int root1 = find(id1);
            int root2 = find(id2);
    
            // No union needed.
            if (root1 == root2)
                return false;
    
            // Attach tree 2 to tree 1
            if (parents[root1].getHeight() > parents[root2].getHeight()) {
                parents[root2].setID(root1);
            }
    
            // Attach tree 1 to tree 2
            else if (parents[root2].getHeight() > parents[root1].getHeight() ) {
                parents[root1].setID(root2);
            }
    
            // Same height case - just attach tree 2 to tree 1, adjust height.
            else {
                parents[root2].setID(root1);
                parents[root1].incHeight();
            }
            // We successfully did a union.
            return true;
        }
        
        // Just represents this object as a list of each node's parent.
        public String toString() {
            String ans = "";
            for (int i=0; i<parents.length; i++)
            {
                if (i == parents[i].getID()) //print the height if the node is root
                ans = ans + "(" + i + ", " + parents[i].getID() + ":" + parents[i].getHeight()+") ";
                else
                ans = ans + "(" + i + ", " + parents[i].getID() + ") ";
            }   
            return ans;
        }
    }//End of DisjointSet class
    
    // A class to represent a graph edge
	class Edge implements Comparable<Edge>
	{
		int src, dest, weight;

		// Comparator function used for
		// sorting edgesbased on their weight
		public int compareTo(Edge compareEdge)
		{
			return this.weight - compareEdge.weight;
		}
	};

    int V, E; // V-> no. of vertices & E->no.of edges
	Edge edge[]; // collection of all edges

    // Creates a graph with V vertices and E edges
	Kruskal_ds(int v, int e)
	{
		V = v;
		E = e;
		edge = new Edge[E];
		for (int i = 0; i < e; ++i)
			edge[i] = new Edge();
        
	}

    // The main function to construct MST using Kruskal's
	// algorithm
	void KruskalMST()
	{
		// Tnis will store the resultant MST
		ArrayList<Edge> result = new ArrayList<Edge>();
	
		// An index variable, used for sorted edges
		// Step 1: Sort all the edges in non-decreasing
		// order of their weight. If we are not allowed to
		// change the given graph, we can create a copy of
		// array of edges
		Arrays.sort(edge);

		// Create a disjoint set to detect cycles
        DisjointSet ds = new DisjointSet(V);

		int i = 0; // Index used to pick next edge
		while (i < V) // iterate over all the edges
		{
			// Step 2: Pick the smallest edge. And increment
			// the index for next iteration
			Edge next_edge = edge[i];

			int x = ds.find(next_edge.src);
			int y = ds.find(next_edge.dest);

			// If including this edge does't cause cycle,
			// include it in result and increment the index
			// of result for next edge
			if (x != y) {
				result.add(next_edge);
                ds.union(next_edge.src, next_edge.dest);
			}// Else discard the next_edge
            i += 1;
		}

		// print the contents of result[] to display
		// the built MST
		System.out.println("Following are the edges in "
						+ "the constructed MST");
		int minimumCost = 0;
		for (i = 0; i < result.size(); ++i)
		{
			System.out.println(result.get(i).src + " -- "
							+ result.get(i).dest
							+ " == " + result.get(i).weight);
			minimumCost += result.get(i).weight;
		}
		System.out.println("Minimum Cost Spanning Tree "
						+ minimumCost);
	}

	// Driver Code
	public static void main(String[] args)
	{

		/* Let us create following weighted graph
				10
			0--------1
			| \	     |
		   6| 5\     |15
			|	 \   |
			2--------3
				4	 */
		int V = 4; // Number of vertices in graph
		int E = 5; // Number of edges in graph
		Kruskal_ds graph = new Kruskal_ds(V, E);

		// add edge 0-1
		graph.edge[0].src = 0;
		graph.edge[0].dest = 1;
		graph.edge[0].weight = 10;

		// add edge 0-2
		graph.edge[1].src = 0;
		graph.edge[1].dest = 2;
		graph.edge[1].weight = 6;

		// add edge 0-3
		graph.edge[2].src = 0;
		graph.edge[2].dest = 3;
		graph.edge[2].weight = 5;

		// add edge 1-3
		graph.edge[3].src = 1;
		graph.edge[3].dest = 3;
		graph.edge[3].weight = 15;

		// add edge 2-3
		graph.edge[4].src = 2;
		graph.edge[4].dest = 3;
		graph.edge[4].weight = 4;

		// Function call
		graph.KruskalMST();
	}
}
