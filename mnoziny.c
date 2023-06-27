#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OUT_OF_MEMORY 'a'
#define TOO_BIG_DECREASE 'b' 

typedef struct {
    int* set;
    unsigned int n;
} MNOZINA;

void free_array(MNOZINA* arr)
{
    free(arr->set);
    free(arr);
}

MNOZINA* constructor() {
    MNOZINA* arr = (MNOZINA*)malloc(sizeof(MNOZINA));
    if (arr == NULL)
    {
        free_array(arr);
        return NULL;
    }
    arr->set = NULL;
    arr->n = 0;
    return(arr);
}

int contains(MNOZINA* set, int element) {
    int i;
    for (i = 0; i < set->n; i++) {
        if (set->set[i] == element) {
            return 1;  // Cislo nebolo najdene
        }
    }
    return 0;  // Cislo nebolo najdene
}

int intersection(MNOZINA* intersec,MNOZINA* set1, MNOZINA* set2) {  //algoritmus zlucenia pre prienik
    int k1 = 0;
    int i = 0, j = 0;

    intersec->set = (int*)malloc(set1->n * sizeof(int));
    if (intersec->set == NULL) {
        free_array(set1);
        free_array(set2);
        free_array(intersec);
        return OUT_OF_MEMORY;
    }
    while (i < set1->n && j < set2->n) {
        if (set1->set[i] < set2->set[j]) {
            i++;
        }
        else if (set1->set[i] > set2->set[j]) {
            j++;
        }
        else {
            if (k1 == 0 || intersec->set[k1 - 1] != set1->set[i]) {
                intersec->set[k1] = set1->set[i];
                k1++;
            }
            i++;
            j++;
        }
    }
    intersec->n = k1;
    return 0;
}

int unions(MNOZINA* unio, MNOZINA* set1, MNOZINA* set2) { //algoritmus zlucenia pre zjednotenie
    int k2 = 0;
    int i = 0, j = 0;

    unio->set = (int*)malloc((set1->n + set2->n) * sizeof(int));
    if (unio->set == NULL) {
        free_array(unio);
        free_array(set1);
        free_array(set2);
        return OUT_OF_MEMORY;
    }
    while (i < set1->n && j < set2->n) {
        if (set1->set[i] < set2->set[j]) {
            if (k2 == 0 || unio->set[k2 - 1] != set1->set[i]) {
                unio->set[k2] = set1->set[i];
                k2++;
            }
            i++;
        }
        else if (set1->set[i] > set2->set[j]) {
            if (k2 == 0 || unio->set[k2 - 1] != set2->set[j]) {
                unio->set[k2] = set2->set[j];
                k2++;
            }
            j++;
        }
        else {
            if (k2 == 0 || unio->set[k2 - 1] != set1->set[i]) {
                unio->set[k2] = set1->set[i];
                k2++;
            }
            i++;
            j++;
        }
    }
    while (i < set1->n) {
        if (k2 == 0 || unio->set[k2 - 1] != set1->set[i]) {
            unio->set[k2] = set1->set[i];
            k2++;
        }
        i++;
    }
    while (j < set2->n) {
        if (k2 == 0 || unio->set[k2 - 1] != set2->set[j]) {
            unio->set[k2] = set2->set[j];
            k2++;
        }
        j++;
    }
    unio->n = k2;
    return 0;
}

int add_elem(MNOZINA* set1, MNOZINA* set2) {
    int n1, n2;
    printf("\nEnter a new element for first and for second array in row: ");
    scanf("%i %i", &n1, &n2);

    set1->n++;
    set2->n++;
    set1->set = (int*)realloc(set1->set, set1->n * sizeof(int));
    if(set1->set == NULL)
    {
        free_array(set1);
        free_array(set2);
        return OUT_OF_MEMORY;
    }
    set2->set = (int*)realloc(set2->set, set2->n * sizeof(int));
    if (set2->set == NULL)
    {
        free_array(set1);
        free_array(set2);
        return OUT_OF_MEMORY;
    }

    set1->set[set1->n - 1] = n1;
    set2->set[set2->n - 1] = n2;
    return 0;
}

int dec_array(MNOZINA* set1, MNOZINA* set2) {
    int dec;
    printf("How much do you want to reduce the arrays? -> ");
    scanf("%i", &dec);

    if (set1->n < dec) {
        free_array(set1);
        free_array(set2);
        return TOO_BIG_DECREASE;
    }

    set1->n -= dec;
    set2->n -= dec;

    set1->set = (int*)realloc(set1->set, set1->n * sizeof(int));
    if (set1->set == NULL)
    {
        free_array(set1);
        free_array(set2);
        return OUT_OF_MEMORY;
    }
    set2->set = (int*)realloc(set2->set, set2->n * sizeof(int));
    if (set2->set == NULL)
    {
        free_array(set1);
        free_array(set2);
        return OUT_OF_MEMORY;
    }
    return 0;
}

int nastav(MNOZINA* a) { //nastavenie mnozin
    int i;
    a->set = (int*)malloc(a->n * sizeof(int));
    if (a->set == NULL)
    {
        free_array(a);
        return OUT_OF_MEMORY;
    }
    for (i = 0; i < a->n; i++) {
        a->set[i] = rand() % 10;
    }
    return 0;
}

void quicksort(int* arr, int low, int high); //quick sort funkcia
int partition(int* arr, int low, int high);
void swap(int* a, int* b);

void sort(MNOZINA* set1, MNOZINA* set2) {
    quicksort(set1->set, 0, set1->n - 1);
    quicksort(set2->set, 0, set2->n - 1);
}

void quicksort(int* arr, int low, int high) {
    int sort_iterations = 0;
    if (low < high) {
        int pivot = partition(arr, low, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j;

    for (j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print(MNOZINA* intersec, MNOZINA* unio) {
    int i, j;
    printf("Intersection: "); //vystup intersection
    for (i = 0; i < intersec->n; i++) {
        printf("%d ", intersec->set[i]);
    }
    printf("\n");
    printf("Union: ");  //vystup union
    for (i = 0; i < unio->n; i++) {
        printf("%d ", unio->set[i]);
    }
    printf("\n");

}

void print_arr(MNOZINA* set1, MNOZINA* set2) {
    int i;
    printf("First array: ");
    for (i = 0; i < set1->n; i++) {
        printf("%i ", set1->set[i]);
    }
    printf("\n");
    printf("Second array: ");
    for (i = 0; i < set2->n; i++) {
        printf("%i ", set2->set[i]);
    }
    printf("\n");
}

int err(int a)
{
    switch(a)
    {
    case OUT_OF_MEMORY:
        printf("Error: Failed to allocate memory\n");
        return 0;
    case TOO_BIG_DECREASE:
        printf("Error: It is not possible to reduce the array to such a number\n");
        return 0;
    }
    return 1;
}

int main() {
    srand(time(0));
    int n, i, k = 1, chyba, error;
    MNOZINA* set1 = constructor();
    if (set1 == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    MNOZINA* set2 = constructor();
    if (set2 == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    MNOZINA* intersec = constructor();
    if (intersec == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    MNOZINA* unio = constructor();
    if (unio == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    printf("Enter the size of 2 arrays -> ");
    scanf("%i", &n);
    set1->n = n;
    set2->n = n;

    chyba = nastav(set1);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    chyba = nastav(set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    sort(set1, set2);
    print_arr(set1, set2);

    intersection(intersec, set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    unions(unio, set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    print(intersec, unio);

    chyba = add_elem(set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    printf("Arrays have size %i now\n", set1->n);
    sort(set1, set2);
    intersection(intersec, set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    unions(unio, set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    print_arr(set1, set2);
    print(intersec, unio);

    chyba = dec_array(set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    printf("Arrays have size %i now\n", set1->n);
    sort(set1, set2);
    chyba = intersection(intersec, set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    chyba = unions(unio, set1, set2);
    chyba = err(chyba);
    if (chyba == 0) return -1;

    print_arr(set1, set2);
    print(intersec, unio);

    free_array(set1);
    free_array(set2);
    free_array(intersec);
    free_array(unio);

    int ag;
    printf("Again? 1 - yes, 0 - no: ");
    scanf("%i", &ag);
    if (ag == 1) return main();
    return 0;
}
