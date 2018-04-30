import java.util.Scanner;
import java.io.File;
import java.io.IOException;

class UnionFind {
    int N;
    int M;
    int K;

    int[] villages;

    public int find(int i) {
        int ret = this.villages[i];

        while (ret != i) {
            i = ret;
            ret = this.villages[i];
        }

        return ret;
    }

    public boolean union(int i, int j) {
        int rootI = this.find(i);
        int rootJ = this.find(j);

        if (rootI == rootJ) {
            return false;
        }

        this.villages[rootJ] = rootI;
        return true;
    }
}

public class Villages {
    public static void main(String args[]) {
        UnionFind ufd = new UnionFind();
        Scanner scanner = null;

        try {
            scanner = new Scanner(new File(args[0]));
        } catch (IOException e) {
            System.out.println("File not found.");
            System.exit(1);
        }

        ufd.N = scanner.nextInt();
        ufd.M = scanner.nextInt();
        ufd.K = scanner.nextInt();

        int result = ufd.N;

        ufd.villages = new int[ufd.N];
        for (int i = 0; i < ufd.villages.length; i++) {
            ufd.villages[i] = i;
        }

        for (int i = 0; i < ufd.M; i++) {
            if (ufd.union(scanner.nextInt() - 1, scanner.nextInt() - 1))
                result--;
        }

        result -= ufd.K;
        System.out.println(result < 1 ? 1 : result);

        scanner.close();
    }
}
