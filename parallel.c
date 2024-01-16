#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "hashmap.c"
int test;


int my_max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs_top_down(char text1[], char text2[], int i, int j, HashMap* ht) {
    if (text1[i] == '\0' || text2[j] == '\0')
        return 0;
    char key[10000];
    sprintf(key, "%dS%d", i, j);
    int val = get(ht,key);
    if (val != -1){
        return val;
        }

    if (text1[i] == text2[j]) {
        int value = 1 + lcs_top_down(text1, text2, i + 1, j + 1, ht);
        insert(ht, key,value);
        return value;
    } else {
        srand(time(NULL));  
        int r = rand();
        int value = -1;
        if (r%2 == 0){      
            value = my_max(
                lcs_top_down(text1, text2, i + 1, j, ht),
                lcs_top_down(text1, text2, i, j + 1, ht)
            );
        }
        else{      
            value = my_max(
                lcs_top_down(text1, text2, i, j + 1, ht),
                lcs_top_down(text1, text2, i + 1, j, ht)
            );
        }
        insert(ht, key,value);
        return value;
    }
}

int main() {
    clock_t begin = clock();

    char text1[] = "asdfasdfgsqweadgdfgdsgsdfgsdfa";
    char text2[] = "asdfzxcbasddsafgsdfgsdgsdfgf";
    int len1 = sizeof(text1) - 1; 
    int len2 = sizeof(text2) - 1; 
    
    HashMap* ht = createHashMap(pow(2,16));
    #pragma omp parallel num_threads(4)
    {
        int result = lcs_top_down(text1, text2, 0, 0, ht);
        printf("Length of Longest Common Subsequence: %d\n", result);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%d %d",(end), begin);
    char endkey[10000];
    sprintf(endkey, "%dS%d",6, 6);
    

    // printf(hashFunction("6S6", ht->size));

    return 0;
}


