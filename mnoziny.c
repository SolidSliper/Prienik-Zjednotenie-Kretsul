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

int same_n_add(MNOZINA* intersec, MNOZINA* unio, int n){
    //printf("im here ;(\n");
    int i = 0, t = 0;
    for(i = 0; i < intersec->n; i++){
        if(intersec->set[i] == n){t = 1; break;}
    }
    if(t == 0) {intersec->set[intersec->n] = n; intersec->n++;}
    t = 0;
    for(i = 0; i < unio->n; i++){
        if(unio->set[i] == n){t = 1; break;}
    }
    if(t == 0) {unio->set[unio->n] = n; unio->n++;}
    return t;
}

MNOZINA* intersection(MNOZINA* intersec, MNOZINA* set1, MNOZINA* set2) {
    constructor();
    printf("im not here ;)\n)");
    int k1 = 0;
    intersec->set = (int*)malloc(intersec->n * sizeof(int));
    int i, j;  //Cyklus pre najdenia intersection, + podmienky, ÄÃ­sla boli jedineÄnÃ©
    for (i = 0; i < set1->n; i++) {
        for (j = 0; j < set2->n; j++) {
            if (set1->set[i] == set2->set[j]) {
                int t = 0;
                for (int k = 0; k < k1; k++) {
                    if (intersec->set[k] == set1->set[i]) {
                        t = 1;
                        break;
                    }
                }
                if (t == 0) {
                    intersec->set[k1] = set1->set[i];
                    k1++;
                }
            }
        }
    }
    intersec->n = k1;
    return(intersec);
}


MNOZINA* unions(MNOZINA* unio, MNOZINA* set1, MNOZINA* set2) {
    constructor();
    int k2 = 0;
    unio->set = (int*)malloc(2 * unio->n * sizeof(int));
    int i, j, k = 0;
    //Cyklus pre najdenia union zo prvou mnoÅ¾inou, + podmienky, abi ÄÃ­sla boli jedineÄnÃ©
    for (i = 0; i < set1->n; i++) {
        int t = 0;
        for (j = 0; j < set2->n; j++) {
            k++;
            if (set2->set[i] == unio->set[j]) { t = 1; k++; break; }
        }
        if (t == 0) {
            unio->set[k2] = set2->set[i];
            k2++;
        }
        if ((k2 > 1) && (unio->set[k2 - 1] == unio->set[k2 - 2])) {
            k2--; 
            k++;
        }
    }   

    //Cyklus pre najdenia union zo druhou mnoÅ¾inou, + podmienky, abi ÄÃ­sla boli jedineÄnÃ©
    for (i = 0; i < set1->n; i++) {
        int t = 0;
        for (j = 0; j < set2->n; j++) {
            k++;
            if (set1->set[i] == unio->set[j]) { t = 1; k++; break; }
        }
        if (t == 0) {
            unio->set[k2] = set1->set[i];
            k2++;
        }
        if (k2 > 1 && unio->set[k2 - 1] == unio->set[k2 - 2]) {
            k2--;
            k++;
        }
    }
    printf("k = %i \n", k);
    unio->n = k2;
    return(unio);    
}

MNOZINA* add_elem(MNOZINA* set1, MNOZINA* set2, MNOZINA* copy1, MNOZINA* copy2, MNOZINA* intersec, MNOZINA* unio){
    constructor();
    int n1, n2, i, t; //priradenie noveho prvku
    copy1->set = (int*)malloc(copy1->n * sizeof(int));
    copy2->set = (int*)malloc(copy1->n * sizeof(int));
    for (i = 0; i < set1->n; i++) {
        copy1->set[i] = set1->set[i];
        copy2->set[i] = set2->set[i];
    }
    printf("\nEnter a new element for first and for second array in row: ");
    scanf("%i %i", &n1, &n2);
    set1->n++;
    set2->n++;
    set1->set = (int*)malloc(set1->n * sizeof(int));
    set2->set = (int*)malloc(set1->n * sizeof(int));
    for (i = 0; i < set1->n; i++) {
        if(i == set1->n-1) {
            set1->set[i] = n1;
            set2->set[i] = n2;
            break;
        }
        set1->set[i] = copy1->set[i];
        set2->set[i] = copy2->set[i];
    }
    printf("Arrays have size %i now\n", set1->n);
    if(n1 == n2) t = same_n_add(intersec, unio, n1);
    if(t == 0) return 0;
    intersection(intersec, set1, set2);
    unions(unio, set1, set2);
}

MNOZINA* dec_array(MNOZINA* intersec, MNOZINA* unio, MNOZINA* set1, MNOZINA* set2, MNOZINA* copy1, MNOZINA* copy2){
    constructor();
    int dec, i;
    printf("How much you want to reduce the arrays? -> ");
    scanf("%i", &dec);
    if(set1->n < dec){printf("Your arrays have size %i, you cant decrease for this value!\n", set1->n);
                   return 0;}
    set1->n = set1->n - dec;
    set2->n = set2->n - dec;
    copy1->set = (int*)malloc(set1->n * sizeof(int));
    copy2->set = (int*)malloc(set2->n * sizeof(int));
    for (i = 0; i < set1->n; i++) {
        copy1->set[i] = set1->set[i];
        copy2->set[i] = set2->set[i];
    }
    set1->set = (int*)malloc(set1->n * sizeof(int));
    set2->set = (int*)malloc(set2->n * sizeof(int));
    for (i = 0; i < set1->n; i++) {
        set1->set[i] = copy1->set[i];
        set2->set[i] = copy2->set[i];
    }
    printf("Arrays have size %i now\n", set1->n);
    intersection(intersec, set1, set2);
    unions(unio, set1, set2);
}

MNOZINA* nastav(MNOZINA* a) { //nastavenie mnozin
    constructor();
    a->set = (int*)malloc(a->n * sizeof(int));
    int i;
    for (i = 0; i < a->n; i++) {
        a->set[i] = rand() % 10;
    }
        
   return(a);
}

MNOZINA* sort(MNOZINA* set1, MNOZINA* set2){
    int i, j, t;
    for(i = 0; i<set1->n-1; i++){
        for(j = 0; j<set1->n-i-1; j++){
        if( set1->set[j] > set1->set[j+1]){
             t = set1->set[j];
             set1->set[j] = set1->set[j+1];
             set1->set[j+1] = t; 
            }
        }
    }

    for(i = 0; i<set2->n-1; i++){
        for(j = 0; j<set2->n-i-1; j++){
        if( set2->set[j] > set2->set[j+1]){
             t = set2->set[j];
             set2->set[j] = set2->set[j+1];
             set2->set[j+1] = t; 
            }
        }
    }
}

void print(MNOZINA intersec, MNOZINA unio) {
    constructor();
    int i, j;
    printf("Intersection: "); //vÃ½stup intersection
    for (i = 0; i < intersec.n; i++) {
        printf("%d ", intersec.set[i]);
    }
    printf("\n");

    printf("Union: ");  //vÃ½stup union
    for (i = 0; i < unio.n; i++) {
        printf("%d ", unio.set[i]);
    }
    printf("\n");

}

void print_arr(MNOZINA* set1, MNOZINA* set2){
    constructor();
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
    //int* copy1;
    //int* copy2;
    int n, k = 1;
    MNOZINA set1;
    MNOZINA set2;
    MNOZINA intersec;
    MNOZINA unio;
    MNOZINA copy1;
    MNOZINA copy2;
    constructor();
    printf("Enter the size of 2 arrays -> ");
    scanf("%i", &n);
    set1.n = n;
    set2.n = n;
    unio.n = n;
    intersec.n = 2*n;
    copy1.n = n;
    copy2.n = n;
    //DeklarÃ¡cia dynamickÃ½ch polÃ­, aby ste si sami mohli nastaviÅ¥ veÄ¾kosÅ¥ mnoÅ¾Ã­n

    nastav(&set1);
    nastav(&set2);
    sort(&set1, &set2);
    print_arr(&set1, &set2);

    intersection(&intersec ,&set1, &set2);
    unions(&unio, &set1, &set2);

    print(intersec, unio);

    add_elem( &set1, &set2, &copy1, &copy2, &intersec, &unio);

    print_arr(&set1, &set2);

    print(intersec, unio);

    dec_array(&intersec, &unio, &set1, &set2, &copy1, &copy2);

    print_arr(&set1, &set2);

    print(intersec, unio);

    free(intersec.set);
    free(unio.set);
    free(copy1.set);
    free(copy2.set);

    int ag;
    printf("Again? 1 - yes, 0 - no: ");
    scanf("%i", &ag);
    if(ag == 1) return main();
    return 0;
}
