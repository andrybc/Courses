import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import java.util.TreeSet;
import java.util.Collections;

public class Main {
    final public static int NEG_INF = Integer.MIN_VALUE;
    final public static int POS_INF = Integer.MAX_VALUE;
    public static Random rndObj = new Random();
    private ArrayList<node> levels;
    private int size;

    public Main() {
        levels = new ArrayList<node>();
        levels.add(buildLevel(0));
        size = 1;
    }

    public node buildLevel(int id) {
        node first = new node(NEG_INF, id);
        node last = new node(POS_INF, id);
        first.next = last;
        last.prev = first;
        return first;
    }

    public ArrayList<node> search(int value) {
        ArrayList<node> res = new ArrayList<node>();
        node cur = levels.get(size - 1);
        for (int i = size - 1; i >= 0; i--) {
            while (cur.next != null && cur.next.data < value) {
                cur = cur.next;
            }
            res.add(cur);
            if (i > 0 && cur.down != null) {
                cur = cur.down;
            }
        }
        Collections.reverse(res);
        return res;
    }

    public boolean insert(int value) {
        ArrayList<node> beforeList = search(value);
        if (beforeList.get(0).next.data == value) {
            return false;
        }

        node curn = null;
        int i = 0;
        while (i <= size) {
            int val = i == 0 ? 1 : rndObj.nextInt(2);
            if (val == 0) {
                break;
            }

            node newn = new node(value, i);
            if (i > 0) {
                curn.up = newn;
                newn.down = curn;
            }

            if (i == size) {
                node nextL = buildLevel(size);
                levels.add(nextL);
                connectLastLevel();
                beforeList.add(nextL);
            }

            node tmpLow = beforeList.get(i);
            node tmpNext = tmpLow.next;
            newn.prev = tmpLow;
            newn.next = tmpNext;
            tmpLow.next = newn;
            tmpNext.prev = newn;

            if (i == size) {
                size++;
                break;
            }
            i++;
            curn = newn;
        }
        return true;
    }

    public boolean delete(int value) {
        ArrayList<node> beforeList = search(value);
        node toDelete = beforeList.get(0).next;
        if (toDelete == null || toDelete.data != value) {
            return false;
        }

        for (int i = 0; i < beforeList.size(); i++) {
            node prev = beforeList.get(i);
            node current = prev.next;
            if (current == null || current.data != value) {
                break;
            }

            if (current.next != null) {
                current.next.prev = prev;
            }
            prev.next = current.next;
        }

        while (size > 1 && levels.get(size - 1).next.data == POS_INF) {
            levels.remove(size - 1);
            size--;
        }
        return true;
    }

    private int topLevelSize() {
        node cur = levels.get(size - 1);
        int sz = 0;
        while (cur != null) {
            cur = cur.next;
            sz++;
        }
        return sz;
    }

    public void connectLastLevel() {
        node top = levels.get(levels.size() - 1);
        node below = levels.get(levels.size() - 2);
        top.down = below;
        below.up = top;
        top = top.next;
        while (below.data != POS_INF) {
            below = below.next;
        }
        top.down = below;
        below.up = top;
    }

    public void printAllLevels() {
        System.out.println(levels.size() + " and " + size);
        for (int i = 0; i < size; i++) {
            System.out.print("Level " + i + ": ");
            printLevel(i);
        }
        System.out.println("---------------------------");
    }

    public void printLevel(int id) {
        node cur = levels.get(id);
        while (cur != null) {
            System.out.print(cur.data + " ");
            cur = cur.next;
        }
        System.out.println();
    }

    public static void basicInsertTest() {
        Main mine = new Main();
        for (int i = 0; i < 10; i++) {
            int item = rndObj.nextInt(1000);
            System.out.println("Gen " + item);
            boolean flag = mine.insert(item);
            if (flag) {
                System.out.println("Inserted " + item);
            } else {
                System.out.println("Rejected " + item);
            }
            mine.printAllLevels();
        }

        Scanner sc = new Scanner(System.in);
        int item = 0;
        while (item != -1) {
            System.out.println("Enter an item to delete: ");
            item = sc.nextInt();
            boolean flag = mine.delete(item);
            if (flag) {
                System.out.println("Deleted " + item);
                mine.printAllLevels();
            } else {
                System.out.println(item + " cannot be deleted.");
            }
        }
    }

    public ArrayList<Integer> getList() {
        node bottom = levels.get(0);
        ArrayList<Integer> res = new ArrayList<Integer>();
        bottom = bottom.next;
        while (bottom.data != POS_INF) {
            res.add(bottom.data);
            bottom = bottom.next;
        }
        return res;
    }

    public static void largeTestRandom(int testSize) {
        Main skipList = new Main();
        TreeSet<Integer> treeSet = new TreeSet<>();

        int[] insertValues = new int[testSize];
        int[] deleteValues = new int[testSize];

        for (int i = 0; i < testSize; i++) {
            insertValues[i] = rndObj.nextInt(2000001);
            deleteValues[i] = rndObj.nextInt(2000001);
        }

        // measure time for skip list
        long startTime = System.currentTimeMillis();

        for (int val : insertValues) {
            skipList.insert(val);
        }

        long skipListInsertTime = System.currentTimeMillis() - startTime;

        startTime = System.currentTimeMillis();

        for (int val : deleteValues) {
            skipList.delete(val);
        }

        long skipListDeleteTime = System.currentTimeMillis() - startTime;

        long skipListTotalTime = skipListInsertTime + skipListDeleteTime;

        // measure time for tree set
        startTime = System.currentTimeMillis();

        for (int val : insertValues) {
            treeSet.add(val);
        }

        long treeSetInsertTime = System.currentTimeMillis() - startTime;

        startTime = System.currentTimeMillis();

        for (int val : deleteValues) {
            treeSet.remove(val);
        }

        long treeSetDeleteTime = System.currentTimeMillis() - startTime;

        long treeSetTotalTime = treeSetInsertTime + treeSetDeleteTime;

        System.out.println("Test size: " + testSize);
        System.out.println("===========");
        System.out.println();
        System.out.println("Skip list insertion to " + skipListInsertTime + " ms");
        System.out.println("Skip list deletion to " + skipListDeleteTime + " ms");
        System.out.println("Skip list actions to " + skipListTotalTime + " ms");
        System.out.println("Tree set insertion to " + treeSetInsertTime + " ms");
        System.out.println("Tree set deletion to " + treeSetDeleteTime + " ms");
        System.out.println("Tree set actions to " + treeSetTotalTime + " ms");
        System.out.println();
    }

    public static void main(String[] args) {
        int[] testSizes = {50000, 100000, 150000, 200000, 250000, 300000, 350000,400000,450000, 500000};

        for (int size : testSizes) {
            largeTestRandom(size);
        }
    }
}

class node {
    public int data;
    public node next;
    public node prev;
    public node up;
    public node down;
    public int level;

    public node(int myval, int mylev) {
        data = myval;
        level = mylev;
        next = null;
        prev = null;
        up = null;
        down = null;
    }
}
