#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OUT_OF_MEMORY -1
#define DOESNT_CONTAINS 2
#define CONTAINS 3
#define ERROR_EXISTS 1
#define ERROR_DOESNT_EXISTS 0

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
        return NULL;
    arr->set = NULL;
    arr->n = 0;
    return(arr);
}

int contains(MNOZINA* set, int element) {
    int i;
    for (i = 0; i < set->n; i++) {
        if (set->set[i] == element) 
            return CONTAINS;  // Cislo bolo najdene
        
    }
    return DOESNT_CONTAINS;  // Cislo nebolo najdene
}

int intersection(MNOZINA* intersec, MNOZINA* set1, MNOZINA* set2) {  //algoritmus zlucenia pre prienik
    int k1 = 0;
    int i = 0, j = 0;

    MNOZINA* copy = constructor();
    if (copy == NULL) 
        return OUT_OF_MEMORY;

    copy->set = (int*)malloc(set1->n * sizeof(int));
    if (copy->set == NULL) {
        free_array(copy);
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
            if (k1 == 0 || copy->set[k1 - 1] != set1->set[i]) {
                copy->set[k1] = set1->set[i];
                k1++;
            }
            i++;
            j++;
        }
    }

    for (i = 0; i < k1; i++) intersec->set[i] = copy->set[i];
    intersec->n = k1;
    free_array(copy);
    return 0;
}

int unions(MNOZINA* unio, MNOZINA* set1, MNOZINA* set2) { //algoritmus zlucenia pre zjednotenie
    int k2 = 0;
    int i = 0, j = 0;

    MNOZINA* copy = constructor();
    if (copy == NULL) 
        return OUT_OF_MEMORY;

    copy->set = (int*)malloc((set1->n + set2->n) * sizeof(int));
    if (copy->set == NULL) {
        free_array(copy);
        return OUT_OF_MEMORY;
    }

    while (i < set1->n && j < set2->n) {
        if (set1->set[i] < set2->set[j]) {
            if (k2 == 0 || copy->set[k2 - 1] != set1->set[i]) {
                copy->set[k2] = set1->set[i];
                k2++;
            }
            i++;
        }
        else if (set1->set[i] > set2->set[j]) {
            if (k2 == 0 || copy->set[k2 - 1] != set2->set[j]) {
                copy->set[k2] = set2->set[j];
                k2++;
            }
            j++;
        }
        else {
            if (k2 == 0 || copy->set[k2 - 1] != set1->set[i]) {
                copy->set[k2] = set1->set[i];
                k2++;
            }
            i++;
            j++;
        }
    }
    while (i < set1->n) {
        if (k2 == 0 || copy->set[k2 - 1] != set1->set[i]) {
            copy->set[k2] = set1->set[i];
            k2++;
        }
        i++;
    }
    while (j < set2->n) {
        if (k2 == 0 || copy->set[k2 - 1] != set2->set[j]) {
            copy->set[k2] = set2->set[j];
            k2++;
        }
        j++;
    }
    unio->n = k2;
    for (i = 0; i < k2; i++) unio->set[i] = copy->set[i];
    free_array(copy);
    return 0;
}

int add_elem(MNOZINA* arr, int n) {
    int cont = contains(arr, n);
    if (cont == CONTAINS)
        return CONTAINS;
    arr->n++;
    arr->set = (int*)realloc(arr->set, arr->n * sizeof(int));
    if (arr->set == NULL) {
        free_array(arr);
        return OUT_OF_MEMORY;
    }
    arr->set[arr->n - 1] = n;
    return 0;
}

int del_elem(MNOZINA* arr, int ell) {
    int cont, i, index;
    cont = contains(arr, ell);
    if (cont == DOESNT_CONTAINS)
        return DOESNT_CONTAINS;

    for (i = 0; i < arr->n; i++) {
        if (arr->set[i] == ell) {
            index = i;
            break;
        }
    }
    for (i = index; i < arr->n - 1; i++) {
        arr->set[i] = arr->set[i + 1];
    }
    arr->n--;
    arr->set = (int*)realloc(arr->set, arr->n * sizeof(int));
    if (arr->set == NULL) {
        free_array(arr);
        return OUT_OF_MEMORY;
    }
    return 0;
}

int nastav(MNOZINA* arr) { //nastavenie mnozin
    int i;
    MNOZINA* a = constructor();
    if (a == NULL)
        return OUT_OF_MEMORY;

    a->set = (int*)malloc(arr->n * sizeof(int));
    if (a->set == NULL)
    {
        free_array(a);
        return OUT_OF_MEMORY;
    }
    for (i = 0; i < arr->n; i++) {
        a->set[i] = rand() % 10;
        arr->set[i] = a->set[i];
    }

    free_array(a);
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
        if (arr[j] <= pivot) 
        {
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

void print_arr(MNOZINA* arr) {
    int i;
    for (i = 0; i < arr->n; i++) {
        printf("%i ", arr->set[i]);
    }
}

int err(int a, MNOZINA* set1, MNOZINA* set2, MNOZINA* intersec, MNOZINA* unio)
{
    switch(a)
    {
    case OUT_OF_MEMORY:
        free_array(set1);
        free_array(set2);
        free_array(intersec);
        free_array(unio);
        return ERROR_EXISTS;
    }
    return ERROR_DOESNT_EXISTS;
}

int main() {
    srand(time(0));
    int n, i, k = 1, chyba, new_elem, del;

    MNOZINA* set1 = constructor();
    if (set1 == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    MNOZINA* set2 = constructor();
    if (set2 == NULL)
    {
        free_array(set1);
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    MNOZINA* intersec = constructor();
    if (intersec == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        free_array(set1);
        free_array(set2);
        return -1;
    }
    MNOZINA* unio = constructor();
    if (unio == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        free_array(set1);
        free_array(set2);
        free_array(intersec);
        return -1;
    }

    printf("Enter the size of 2 arrays -> ");
    scanf("%i", &n);
    set1->n = n;
    set2->n = n;

    set1->set = (int*)malloc((set1)->n * sizeof(int));
        if (set1->set == NULL)
        {
            printf("Error: Failed to allocate memory\n");
            free_array(set1);
            free_array(set2);
            free_array(intersec);
            free_array(unio);
            return OUT_OF_MEMORY;
        }
    chyba = nastav(set1);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    set2->set = (int*)malloc((set2)->n * sizeof(int));
    if (set2->set == NULL)
    {
        printf("Error: Failed to allocate memory\n");
        free_array(set1);
        free_array(set2);
        free_array(intersec);
        free_array(unio);
        return OUT_OF_MEMORY;
    }
    chyba = nastav(set2);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    sort(set1, set2);
    printf("First array: ");
    print_arr(set1);
    printf("\n");
    printf("Second array: ");
    print_arr(set2);
    printf("\n");

    intersec->set = (int*)malloc(set1->n * sizeof(int));
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    chyba = intersection(intersec, set1, set2);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    unio->set = (int*)malloc((set1->n + set2->n) * sizeof(int));
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    chyba = unions(unio, set1, set2);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    printf("Intersection: ");
    print_arr(intersec);
    printf("\n");
    printf("Union: ");
    print_arr(unio);
    printf("\n");

    printf("\nEnter a new element for first array: ");
    scanf("%i", &new_elem);
    chyba = add_elem(set1, new_elem);
    if (chyba == CONTAINS)
    {   
        set1->n--;
        set1->set = (int*)realloc(set1->set, set1->n * sizeof(int));
        if (chyba == ERROR_EXISTS) {
            printf("Error: Failed to allocate memory\n");
            return -1;
        }
        printf("\nFirst array already cotains this digit\n");
    }
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    sort(set1, set2);

    intersec->set = (int*)malloc(set1->n * sizeof(int));
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    chyba = intersection(intersec, set1, set2);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    unio->set = (int*)malloc((set1->n + set2->n) * sizeof(int));
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }
    chyba = unions(unio, set1, set2);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    printf("First array: ");
    print_arr(set1);
    printf("\n");
    printf("Second array: ");
    print_arr(set2);
    printf("\n");
    printf("Intersection: ");
    print_arr(intersec);
    printf("\n");
    printf("Union: ");
    print_arr(unio);
    printf("\n");

    printf("\nWhich digit of 2nd array you want to delete? -> ");
    scanf("%i", &del);
    chyba = del_elem(set2, del);
    if (chyba == DOESNT_CONTAINS) printf("\nSecond array doesnt cotains this digit\n");
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    sort(set1, set2);

    intersec->set = (int*)malloc(set1->n * sizeof(int));
    if (intersec->set == NULL)  return OUT_OF_MEMORY;
    chyba = intersection(intersec, set1, set2);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) {
        printf("Error: Failed to allocate memory\n");
        return -1;
    }

    unio->set = (int*)malloc((set1->n + set2->n) * sizeof(int));
    if (unio->set == NULL) return OUT_OF_MEMORY;
    chyba = unions(unio, set1, set2);
    chyba = err(chyba, set1, set2, intersec, unio);
    if (chyba == ERROR_EXISTS) { 
        printf("Error: Failed to allocate memory\n"); 
        return -1;
    }

    printf("First array: ");
    print_arr(set1);
    printf("\n");
    printf("Second array: ");
    print_arr(set2);
    printf("\n");
    printf("Intersection: ");
    print_arr(intersec);
    printf("\n");
    printf("Union: ");
    print_arr(unio);
    printf("\n");

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
