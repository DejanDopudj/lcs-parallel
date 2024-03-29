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
    char key[15];
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
        int r = rand();
        if(i == 1 && j == 1){
            printf("%d\t", r);
        }
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

    FILE *in = fopen("t3.txt", "r");
    int m = 1000;
    int n = 1000;
    char *text1 = (char *)malloc(m * sizeof(char));
    char *text2 = (char *)malloc(n * sizeof(char));
    fscanf(in, "%s %s", text1, text2);
    fclose(in);    
    HashMap* ht = createHashMap(pow(2,23));
    clock_t start = clock();
    #pragma omp parallel num_threads(4)
    {  
        srand((time(NULL)) ^ omp_get_thread_num());
        //moguce je dodati da se nakon jednog izvrsavanja svi ostali threadovi zaustave
        //ali kako je do tada hes tabela vec skoro skroz popunjena, ne bi mnogo optimizovalo 
        int res = lcs_top_down(text1, text2, 0, 0, ht);  
        // clock_t end = clock();
        // double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        // printf("Time taken: %f seconds\n", cpu_time_used);

    }
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);


    return 0;
}


