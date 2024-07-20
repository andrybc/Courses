import java.util.*;
import java.io.*;

public class Main {
   
    public static int n;
    public static int e;
    public static ArrayList[] graph;
   
   
   
   
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
       
        n = in.nextInt();
        e = in.nextInt();
       
        graph = new ArrayList[n];
        for(int i = 0; i < n; i++){
            graph[i] = new ArrayList<Integer>();
        }
       
       
        for(int i = 0; i <  e; i++){
            int v1 = in.nextInt() - 1;
            int v2 = in.nextInt() -1;
            graph[v1].add(v2);
            graph[v2].add(v1);
           
        }
       
        int[] remList = new int[n];
        for(int i = 0; i < n; i++){
            remList[i] = in.nextInt() - 1;
        }
       
       
        boolean[] res = new boolean[n];
        dset dj = new dset(n);
        res[n-1] = true;
        boolean[] inGraph = new boolean[n];
        inGraph[remList[n-1]] = true;
       
        for( int i = n - 2; i >= 0; i--){
           
            int item = remList[i];
            for(int  j = 0; j < graph[item].size(); j++){
                int next = (Integer)(graph[item].get(j));
                if(inGraph[next]){
                    dj.union(item,next);
                }
            }
           
            res[i] = (dj.getNumTrees() == i + 1);
            inGraph[item] = true;
        }
       
        for(int i = 0; i < n ; i++){
            if(res[i]){
                System.out.println("YES");
            }
            else{
                System.out.println("NO");

            }
        }
       
       
    }
}

class dset{
   
    private pair[] parents;
    private int numTrees;
   
    public dset(int n){
       
    	numTrees = n;
        parents = new pair[n];
        
        
        for(int i = 0; i < n ; i++){
            parents[i] = new pair(i, 0);
        }
    }
    
    public int getNumTrees() {
        return numTrees;
    }
   
    public int find(int id){
       
        while( id != parents[id].getID()){
            id = parents[id].getID();
        }
       
        return id;
           
    }
   
    public boolean union(int id1, int id2){
       
        int root1 = find(id1);
        int root2 = find(id2);
       
        if(root1 == root2){
            return false;
        }
       
        if(parents[root1].getHeight() > parents[root2].getHeight()){
            parents[root2].setID(root1);
        }
        else if(parents[root2].getHeight() > parents[root1].getHeight()){
            parents[root1].setID(root2);
        }
        else{
            parents[root2].setID(root1);
            parents[root1].incHeight();
        }
        numTrees--;
        return true;
    }
   
}

class pair{
   
    private int ID;
    private int height;
   
    public pair(int myNum, int myHeight){
        ID = myNum;
        height = myHeight;
    }
   
    public int getHeight(){
        return height;
    }
    public int getID(){
        return ID;
    }
    public void incHeight(){
        height++;
    }
   
    public void setID(int newID){
        ID = newID;
    }
}

