#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE* open_file(char* filename, char* mode)
{
    FILE* fptr;
    if ((fptr = fopen(filename, mode)) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    return fptr;
}

int* load_file(char* filename, int n)
{
    int i = 0;
    char* token;
    char* str = (char*) malloc(1024 * sizeof(char));
    int* out  = (int*) malloc(n * sizeof(int));

    FILE *fptr = open_file(filename, "r");
    
    while(!feof(fptr)){
        fgets(str,1024,fptr);

        token = strtok(str, "\n");
        
        while( token != NULL ) {
            out[i] = atoi(token);
            token = strtok(NULL, "\n");
            i++;
        }
    }
    fclose(fptr);

    return out;
}

int* generate_random_number(int n)
{
    srand(time(NULL));
    int* out = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        out[i] = rand();  
    }
    return out;
}

void write_in_file(char* filename, int* numbers, int size)
{   
    FILE *fptr = open_file(filename, "w");

    for (int i = 0; i < size - 1; i++)
    {
        fprintf(fptr,"%d\n", numbers[i]);
    }
    fprintf(fptr,"%d", numbers[size - 1]);

    fclose(fptr);
}

int* reverse_elements(int* numbers, int size)
{
    int* tmp = (int*) malloc(size * sizeof(int));
    int var = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        tmp[var] = numbers[i];
        var++;
    }
    return tmp;
}

// Function to swap the the position of two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int* arr, int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heap_sort(int* arr, int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        // Heapify root element to get highest element at root again
        heapify(arr, i, 0);
    }
}

// Print an array
void print_array(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void generate_test_files(int n){
    int* random_numbers = generate_random_number(n);
    write_in_file("files/medio.txt", random_numbers, n);

    int* r = load_file("files/medio.txt", n);
    
    heap_sort(r, n);

    write_in_file("files/melhor.txt", r, n);

    r = reverse_elements(r, n);

    write_in_file("files/pior.txt", r, n);
}


int main()
{
    int n = 40000;
    
    //generate_test_files(n);
    
    int* r = load_file("files/pior.txt", n);

    heap_sort(r, n);

    return 0;
}