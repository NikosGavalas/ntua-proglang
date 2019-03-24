#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    ifstream infile;
    infile.open(argv[1]);

    int N, K, B;
    infile >> N;
    infile >> K;
    infile >> B;

    long long steps[N + 1];
    memset(steps, 0, sizeof(steps));

    int i, j, in;
    int hoplengths[K];
    for (i = 0; i < K; i++) {
        infile >> in;
        hoplengths[i] = in;
    }

    for (i = 0; i < B; i++) {
        infile >> in;
        steps[in] = -1;
    }

    infile.close();

    int next_step;
    steps[1] = 1;
    for (i = 2; i < N + 1; i++) {
        if (steps[i] < 0)
            continue;
        for (j = 0; j < K; j++) {
            next_step = i - hoplengths[j];
            if (next_step < 1 || steps[next_step] < 0)  // if off bounds, or broken,
                continue;
            steps[i] += steps[i - hoplengths[j]];
            steps[i] %= 1000000009;
        }
    }

    cout << steps[N] << endl;

    return 0;
}
