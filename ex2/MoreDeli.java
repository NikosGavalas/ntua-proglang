import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Comparator;
import java.util.HashMap;

public class MoreDeli
{
    static class MyComparator implements Comparator<Coordinates>
    {
		public int compare(Coordinates i, Coordinates j)
        {
			return  i.cost - j.cost;
		}
	}

    static class Coordinates
    {
        int x;
        int y;
        int cost;
        Coordinates parent;

        public Coordinates(int x, int y, int cost, Coordinates parent)
        {
            this.x = x;
            this.y = y;
            this.cost = cost;
            this.parent = parent;
        }

        @Override
        public boolean equals(Object o) {
            Coordinates cmp = (Coordinates) o;

            return this.x == cmp.x && this.y == cmp.y && this.cost == cmp.cost;
        }
    }

    public static ArrayList<Coordinates> getNeighbors(Coordinates current, ArrayList<ArrayList<Character>> map) {
        ArrayList<Coordinates> ret = new ArrayList<Coordinates>(4);


        /* U */
        if ((current.x - 1 >= 0) && (map.get(current.x - 1).get(current.y) != 'X') && (map.get(current.x - 1).get(current.y) != '+'))
            ret.add(new Coordinates(current.x - 1, current.y, current.cost + 3, current));
        /* D */
        if ((current.x + 1 < map.size()) && (map.get(current.x + 1).get(current.y) != 'X') && (map.get(current.x + 1).get(current.y) != '+'))
            ret.add(new Coordinates(current.x + 1, current.y, current.cost + 1, current));
        /* R */
        if ((current.y + 1 < map.get(0).size()) && (map.get(current.x).get(current.y + 1) != 'X') && (map.get(current.x).get(current.y + 1) != '+'))
            ret.add(new Coordinates(current.x, current.y + 1, current.cost + 1, current));
        /* L */
        if ((current.y - 1 >= 0) && (map.get(current.x).get(current.y - 1) != 'X') && (map.get(current.x).get(current.y - 1) != '+'))
            ret.add(new Coordinates(current.x, current.y - 1, current.cost + 2, current));

        return ret;
    }

    public static void printSolution(Coordinates current) {
        if (current.parent == null)
            return;

        printSolution(current.parent);

        if (current.parent.x == current.x - 1 && current.parent.y == current.y)
            System.out.printf("%c", 'D');

        if (current.parent.x == current.x + 1 && current.parent.y == current.y)
            System.out.printf("%c", 'U');

        if (current.parent.x == current.x && current.parent.y == current.y - 1)
            System.out.printf("%c", 'R');

        if (current.parent.x == current.x && current.parent.y == current.y + 1)
            System.out.printf("%c", 'L');

    }

    public static void main(String args[])
    {

        BufferedReader br = null;

        ArrayList<ArrayList<Character>> map = new ArrayList<ArrayList<Character>>();
        ArrayList<Character> temp;
        String line;

        Coordinates start = new Coordinates(0,0,0, null);
        Coordinates end = new Coordinates(0,0,0, null);
        Coordinates current = new Coordinates(0,0,0, null);

        try {
            br = new BufferedReader(new FileReader(args[0]));

            int x = 0;
            int y = 0;

            while ((line = br.readLine()) != null) {

                String[] splitted = line.split("");
                temp = new ArrayList<Character>();
                for (String token : splitted) {
                    if (token.length() > 0) {
                        char c = token.charAt(0);
                        temp.add(c);

                        if (c == 'S') {
                            start.x = x;
                            start.y = y;
                        }
                        if (c == 'E') {
                            end.x = x;
                            end.y = y;
                        }
                        y++;
                    }
                }
                map.add(temp);
                y = 0;
                x++;
            }
            br.close();
        } catch (IOException e) {
            System.out.println("File not found");
            System.exit(1);
        }

        MyComparator comparator = new MyComparator();
        PriorityQueue<Coordinates> pq = new PriorityQueue<Coordinates>(1000000, comparator);
        ArrayList<Coordinates> neighbors = new ArrayList<Coordinates>(4);

        pq.add(start);

        while (!pq.isEmpty()) {
            current = pq.remove();

            map.get(current.x).set(current.y, '+');

            if (current.x == end.x && current.y == end.y)
                break;
            neighbors = getNeighbors(current, map);
            for (Coordinates neighbor : neighbors) {
                if (!pq.contains(neighbor)) {
                    pq.add(neighbor);
                }
            }
        }
        System.out.printf("%d ", current.cost);

        printSolution(current);
        System.out.println();

    }
}
