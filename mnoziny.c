#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void intersection(int** intersec, int* set1, int* set2, int n, int* k1) {
    *intersec = (int*)malloc(n * sizeof(int));
    int i, j;  //Cyklus pre najdenia intersection, + podmienky, čísla boli jedinečné
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (set1[i] == set2[j]) {
                int t = 0;
                for (int k = 0; k < (*k1); k++) {
                    if ((*intersec)[k] == set1[i]) {
                        t = 1;
                        break;
                    }
                }
                if (t == 0) {
                    (*intersec)[(*k1)] = set1[i];
                    (*k1)++;
                }
            }
        }
    }

}


void unions(int** unio, int* set1, int* set2, int n, int* k2) {
    *unio = (int*)malloc(2 * n * sizeof(int));
    int i, j;
    //Cyklus pre najdenia union zo prvou množinou, + podmienky, abi čísla boli jedinečné
    for (i = 0; i < n; i++) {
        int t = 0;
        for (j = 0; j < n; j++) {
            if (set2[i] == (*unio)[j]) { t = 1;  break; }
        }
        if (t == 0) {
            (*unio)[(*k2)] = set2[i];
            (*k2)++;
        }
        if ((*k2) > 1 && (*unio)[(*k2) - 1] == (*unio)[(*k2) - 2]) {
            (*k2)--;
        }
    }

    //Cyklus pre najdenia union zo druhou množinou, + podmienky, abi čísla boli jedinečné
    for (i = 0; i < n; i++) {
        int t = 0;
        for (j = 0; j < n; j++) {
            if (set1[i] == (*unio)[j]) { t = 1;  break; }
        }
        if (t == 0) {
            (*unio)[(*k2)] = set1[i];
            (*k2)++;
        }
        if ((*k2) > 1 && (*unio)[(*k2) - 1] == (*unio)[(*k2) - 2]) {
            (*k2)--;
        }
    }
}

void nastav(int** set1, int** set2, int n) {
    *set1 = (int*)malloc(n * sizeof(int));
    *set2 = (int*)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        (*set1)[i] = rand() % 10;
        (*set2)[i] = rand() % 10;
    }
}

void print(int* intersec, int* unio, int k1, int k2, int n) {
    int i, j;
    printf("Intersection: "); //výstup intersection
    for (i = 0; i < k1; i++) {
        printf("%d ", intersec[i]);
    }
    printf("\n");

    printf("Union: ");  //výstup union
    for (i = 0; i < k2; i++) {
        printf("%d ", unio[i]);
    }
    printf("\n");
}

int main() {
    srand(time(0));
    int* set1;
    int* set2;
    int* intersec;
    int* unio;
    int n;

    printf("Enter the size of 2 arrays -> ");
    scanf("%i", &n);

    //Deklarácia dynamických polí, aby ste si sami mohli nastaviť veľkosť množín

    nastav(&set1, &set2, n);

    int i, j, k1 = 0, k2 = 0;
    printf("First array: ");
    for (i = 0; i < n; i++) {
        printf("%i ", set1[i]);
    }
    printf("\n");

    printf("Second array: ");
    for (i = 0; i < n; i++) {
        printf("%i ", set2[i]);
    }
    printf("\n");

    intersection(&intersec, set1, set2, n, &k1);

    unions(&unio, set1, set2, n, &k2);

    print(intersec, unio, k1, k2, n);

    free(set1);
    free(set2);
    free(intersec);
    free(unio);

    return 0;
}
