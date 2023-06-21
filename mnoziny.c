#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int* set;
    unsigned int n;
} MNOZINA;


MNOZINA* constructor() {
    MNOZINA* arr = (MNOZINA*)malloc(sizeof(MNOZINA));
    arr->set = NULL;
    arr->n = 0;
    return(arr);
}

void free_array(MNOZINA* arr)
{
    free(arr->set);
    free(arr);
}

//int same_n_add(MNOZINA* intersec, MNOZINA* unio, int n) {    //F-cia pozarania na prvky, ak dame n do prvej a druhej mnoziny
//    //printf("im here ;(\n");
//    int i = 0, t = 0;
//    for (i = 0; i < intersec->n; i++) {
//        if (intersec->set[i] == n) { t = 1; break; }
//    }
//    if (t == 0) { intersec->set[intersec->n] = n; intersec->n++; }
//    t = 0;
//    for (i = 0; i < unio->n; i++) {
//        if (unio->set[i] == n) { t = 1; break; }
//    }
//    if (t == 0) { unio->set[unio->n] = n; unio->n++; }
//    return t;
//}

MNOZINA* copy_arr(MNOZINA* arr)
{
    int i;
    MNOZINA* copySet = constructor();
    if (copySet == NULL) {
        return 0;
    }
    copySet->set = (int*)malloc(arr->n * sizeof(int));
    copySet->n = arr->n;
    for (i = 0; i < arr->n; i++)
    {
        copySet->set[i] = arr->set[i];
    }
    return(copySet);
}

MNOZINA* intersection(MNOZINA* set1, MNOZINA* set2) {
    MNOZINA* intersec = constructor();
    if (intersec == NULL) {
        return NULL;
    }
    intersec->set = (int*)malloc(set1->n * sizeof(int));
    if (intersec->set == NULL) {
        free_array(intersec);
        return NULL;
    }
    int k1 = 0;
    for (int i = 0; i < set1->n; i++) {
        int t = 0;
        for (int j = 0; j < set2->n; j++) {
            if (set1->set[i] == set2->set[j]) {
                int duplicate = 0;
                for (int k = 0; k < k1; k++) {
                    if (intersec->set[k] == set1->set[i]) {
                        duplicate = 1;
                        break;
                    }
                }
                if (duplicate == 0) {
                    intersec->set[k1] = set1->set[i];
                    k1++;
                }
                t = 1;
                break;
            }
        }
    }
    intersec->n = k1;
    return intersec;
}

MNOZINA* unions(MNOZINA* set1, MNOZINA* set2) {
    MNOZINA* unio = constructor();
    if (unio == NULL) {
        return NULL;
    }
    unio->set = (int*)malloc((set1->n + set2->n) * sizeof(int));
    if (unio->set == NULL) {
        free_array(unio);
        return NULL;
    }
    int k2 = 0;
    for (int i = 0; i < set1->n; i++) {
        int duplicate = 0;
        for (int j = 0; j < k2; j++) {
            if (set1->set[i] == unio->set[j]) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate == 0) {
            unio->set[k2] = set1->set[i];
            k2++;
        }
    }
    for (int i = 0; i < set2->n; i++) {
        int duplicate = 0;
        for (int j = 0; j < k2; j++) {
            if (set2->set[i] == unio->set[j]) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate == 0) {
            unio->set[k2] = set2->set[i];
            k2++;
        }
    }
    unio->n = k2;
    return unio;
}

void add_elem(MNOZINA* set1, MNOZINA* set2/*, MNOZINA** intersec, MNOZINA** unio*/) {
    int n1, n2, i, t=1; //priradenie noveho prvku
    MNOZINA* copySet1 = copy_arr(set1);
    if (copySet1 == NULL)
        return 0;
    MNOZINA* copySet2 = copy_arr(set2);
    if (copySet2 == NULL)
        return 0;
    printf("\nEnter a new element for first and for second array in row: ");
    scanf("%i %i", &n1, &n2);
    set1->n++;
    set2->n++;
    free(set1->set);
    free(set2->set);
    set1->set = (int*)malloc(set1->n * sizeof(int));
    set2->set = (int*)malloc(set1->n * sizeof(int));
    for (i = 0; i < set1->n; i++) {
        if (i == set1->n - 1) {
            set1->set[i] = n1;
            set2->set[i] = n2;
            break;
        }
        set1->set[i] = copySet1->set[i];
        set2->set[i] = copySet2->set[i];
    }
    free_array(copySet1);
    free_array(copySet2);
    printf("Arrays have size %i now\n", set1->n);
   // *intersec = intersection(set1, set2);
   // *unio = unions(set1, set2);
}

void dec_array(MNOZINA* set1, MNOZINA* set2) {
    int dec, i;
    printf("How much you want to reduce the arrays? -> ");
    scanf("%i", &dec);
    if (set1->n < dec) {
        printf("Your arrays have size %i, you cant decrease for this value!\n", set1->n);
        return 0;
    }
    set1->n = set1->n - dec;
    set2->n = set2->n - dec;
    MNOZINA* copy1 = copy_arr(set1);
    MNOZINA* copy2 = copy_arr(set2);
    free(set1->set);
    free(set2->set);
    set1->set = (int*)malloc(set1->n * sizeof(int));
    set2->set = (int*)malloc(set2->n * sizeof(int));
    for (i = 0; i < set1->n; i++) {
        set1->set[i] = copy1->set[i];
        set2->set[i] = copy2->set[i];
    }
    printf("Arrays have size %i now\n", set1->n);
    free_array(copy1);
    free_array(copy2);
}

void nastav(MNOZINA* a) { //nastavenie mnozin
    int i;
    a->set = (int*)malloc(a->n * sizeof(int));
    for (i = 0; i < a->n; i++) {
        a->set[i] = rand() % 10;
    }
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

    for (int j = low; j <= high - 1; j++) {
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

int main() {
    srand(time(0));
    int n, i, k = 1;
    MNOZINA* set1 = constructor();
    if (set1 == NULL)
        return -1;
    MNOZINA* set2 = constructor();
    if (set2 == NULL)
        return -1;
    constructor();
    printf("Enter the size of 2 arrays -> ");
    scanf("%i", &n);
    set1->n = n;
    set2->n = n;

    nastav(set1);
    nastav(set2);

    sort(set1, set2);
    print_arr(set1, set2);

    MNOZINA* intersec = intersection(set1, set2);
    MNOZINA* unio = unions(set1, set2);

    print(intersec, unio);

    add_elem(set1, set2);

    intersec = intersection(set1, set2);
    unio = unions(set1, set2);

    print_arr(set1, set2);

    print(intersec, unio);

    dec_array(set1, set2);

    intersec = intersection(set1, set2);
    unio = unions(set1, set2);

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
