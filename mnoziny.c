#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int* set1;
    int* set2;
    int* intersec;
    int* unio;
    int n;

    printf("Enter the size of 2 arrays -> ");
    scanf("%i", &n);

    //Deklaracia dynamickych poli, aby ste si sami mohli nastavit velkost mnozin
    set1 = (int*)malloc(n * sizeof(int));
    set2 = (int*)malloc(n * sizeof(int));
    intersec = (int*)malloc(n * sizeof(int));
    unio = (int*)malloc(2 * n * sizeof(int));

    int i, j, k1 = 0, k2 = 0;

    for (i = 0; i < n; i++) {
        set1[i] = rand() % 10;
        set2[i] = rand() % 10;
    }

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

    //Cyklus pre najdenia intersection, + podmienky, cisla boli jedinecne
    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) {
            if (set1[i] == set2[j]) {
                int t = 0;
                for (int k = 0; k < k1; k++) {
                    if (intersec[k] == set1[i]) {
                        t = 1;
                        break;
                    }
                }
                if (t==0) {
                    intersec[k1] = set1[i];
                    k1++;
                }
            }
        }
    }
    //Cyklus pre najdenia union zo prvou mnozinou, + podmienky, abi cisla boli jedinecne
    for (i = 0; i < n; i++) { 
        int t = 0;
        for (j = 0; j < n; j++) {
            if (set2[i] == unio[j]) { t = 1;  break; }
        }
        if (t == 0) {
            unio[k2] = set2[i];
            k2++;
        }
        if (k2 > 1 && unio[k2 - 1] == unio[k2 - 2]) {
            k2--;
        }
    }

    //Cyklus pre najdenia union zo druhou mnozinou, + podmienky, abi cisla boli jedinecne
    for (i = 0; i < n; i++) {
        int t = 0;
        for (j = 0; j < n; j++) {
            if (set1[i] == unio[j]) { t = 1;  break; }
        }
        if (t == 0) {
            unio[k2] = set1[i];
            k2++;
        }
        if (k2 > 1 && unio[k2 - 1] == unio[k2 - 2]) {
            k2--;
        }
    }

    printf("Intersection: "); //vystup intersection
    for (i = 0; i < k1; i++) {
        printf("%d ", intersec[i]);
    }
    printf("\n");

    printf("Union: ");  //vystup union
    for (i = 0; i < k2; i++) {
        printf("%d ", unio[i]);
    }
    printf("\n");

    free(set1);
    free(set2);
    free(intersec);
    free(unio);

    return 0;
}

