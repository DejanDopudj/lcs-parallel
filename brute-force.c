#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs(char text1[], char text2[], int i, int j) {
    if (text1[i] == '\0' || text2[j] == '\0')
        return 0;

    if (text1[i] == text2[j])
        return 1 + lcs(text1, text2, i + 1, j + 1);
    else
        return max(
            lcs(text1, text2, i + 1, j),
            lcs(text1, text2, i, j + 1)
        );
}

int main() {
    char text1[] = "TFGEHST";
    char text2[] = "TESJHT";
    int result = lcs(text1, text2, 0, 0);
    printf("Length of Longest Common Subsequence: %d\n", result);
    return 0;
}
