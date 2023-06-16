#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int* set;
    unsigned int n;
} MNOZINA;


MNOZINA* constructor(){
    MNOZINA* arr = (MNOZINA*)malloc(sizeof(MNOZINA));
    arr->set = 0;
    return(arr);
}

void intersection(int** intersec, int* set1, int* set2, int n, int* k1) {
    (*k1) = 0;
    *intersec = (int*)malloc(n * sizeof(int));
    int i, j;  //Cyklus pre najdenia intersection, + podmienky, cisla boli jedinecne
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
    (*k2) = 0;
    *unio = (int*)malloc(2 * n * sizeof(int));
    int i, j;
    //Cyklus pre najdenia union zo prvou mnozinou, + podmienky, abi cisla boli jedinecne
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

    //Cyklus pre najdenia union zo druhou mnozinou, + podmienky, abi cisla boli jedinecne
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

void add_elem(int** set1, int** set2, int** copy1, int** copy2, int* n){
    int n1, n2, i; //priradenie noveho prvku
    *copy1 = (int*)malloc((*n) * sizeof(int));
    *copy2 = (int*)malloc((*n) * sizeof(int));
    for (i = 0; i < (*n); i++) {
        (*copy1)[i] = (*set1)[i];
        (*copy2)[i] = (*set2)[i];
    }
    printf("\nEnter a new element for first and for second array in row: ");
    scanf("%i %i", &n1, &n2);
    (*n)++;
    *set1 = (int*)malloc((*n) * sizeof(int));
    *set2 = (int*)malloc((*n) * sizeof(int));
    for (i = 0; i < (*n); i++) {
        if(i == (*n)-1) {
            (*set1)[i] = n1;
            (*set2)[i] = n2;
            break;
        }
        (*set1)[i] = (*copy1)[i];
        (*set2)[i] = (*copy2)[i];
    }
}

void dec_array(int** set1, int** set2, int** copy1, int** copy2, int* n){
    int dec, i;
    printf("How much you want to reduce the arrays? -> ");
    scanf("%i", &dec);
    if((*n) < dec){printf("Your arrays have size %i, you cant decrease for this value!\n", (*n));
                   return 0;}
    (*n) = (*n) - dec;
    *copy1 = (int*)malloc((*n) * sizeof(int));
    *copy2 = (int*)malloc((*n) * sizeof(int));
    for (i = 0; i < (*n); i++) {
        (*copy1)[i] = (*set1)[i];
        (*copy2)[i] = (*set2)[i];
    }
    *set1 = (int*)malloc((*n) * sizeof(int));
    *set2 = (int*)malloc((*n) * sizeof(int));
    for (i = 0; i < (*n); i++) {
        (*set1)[i] = (*copy1)[i];
        (*set2)[i] = (*copy2)[i];
    }
}

void nastav(int** set1, int** set2, int n) { //nastavenie mnozin
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
}

void print_arr(int** set1, int** set2, int n){
    int i;
    printf("First array: ");
    for (i = 0; i < n; i++) {
        printf("%i ", (*set1)[i]);
    }
    printf("\n");

    printf("Second array: ");
    for (i = 0; i < n; i++) {
        printf("%i ", (*set2)[i]);
    }
    printf("\n");
}

int main() {
    srand(time(0));
    int* copy1;
    int* copy2;
    int* set1;
    int* set2;
    int* intersec;
    int* unio;
    int n, i, j, k1 = 0, k2 = 0;;
    MNOZINA* arr1;
    constructor();
    printf("Enter the size of 2 arrays -> ");
    scanf("%i", &n);

    //Deklaracia dynamickych poli, aby ste si sami mohli nastavit velkost mnozin

    nastav(&set1, &set2, n);

    print_arr(&set1, &set2, n);

    intersection(&intersec, set1, set2, n, &k1);

    unions(&unio, set1, set2, n, &k2);

    print(intersec, unio, k1, k2, n);

    add_elem(&set1, &set2, &copy1, &copy2, &n);

    printf("Arrays have size %i now\n", n);

    print_arr(&set1, &set2, n);

    intersection(&intersec, set1, set2, n, &k1);

    unions(&unio, set1, set2, n, &k2);

    print(intersec, unio, k1, k2, n);

    dec_array(&set1, &set2, &copy1, &copy2, &n);

    printf("Arrays have size %i now\n", n);

    print_arr(&set1, &set2, n);

    intersection(&intersec, set1, set2, n, &k1);

    unions(&unio, set1, set2, n, &k2);

    print(intersec, unio, k1, k2, n);

    free(set1);
    free(set2);
    free(intersec);
    free(unio);
    free(copy1);
    free(copy2);

    int ag;
    printf("Again? 1 - yes, 0 - no: ");
    scanf("%i", &ag);
    if(ag == 1) return main();
    return 0;
}
