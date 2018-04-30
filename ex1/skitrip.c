#include <stdio.h>
#include <stdlib.h>

int In[2000001];

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("%s\n", "Usage: ./skitrip <infile>");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		printf("%s\n", "File not found.");
		exit(1);
	}

	int n;
	fscanf(fp, "%d", &n); // for n >= 2

	int i, Max[n], Min[n];
	for (i = 0; i < n; i++) {
		fscanf(fp, "%d", &In[i]);
	}

	fclose(fp);

	Min[0] = In[0];
	for (i = 1; i < n; i++) {
		Min[i] = (In[i] < Min[i - 1] ? In[i] : Min[i - 1]);
	}

	Max[n - 1] = In[n - 1];
	for (i = n - 2; i >= 0; i--) {
		Max[i] = (In[i] > Max[i + 1] ? In[i] : Max[i + 1]);
	}

	int j = 0, ret = 0;
	i = 0;
	while (i < n && j < n) {
		if (Max[i] >= Min[j])
			i++;
		else
			j++;
		if (ret < i - j)
			ret = i - j;
	}

	printf("%d\n", (ret == 0 ? ret : ret - 1));
	return 0;
}
