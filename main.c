#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Legge file e conta righe ---
int leng(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Cannot open file");
        exit(1);
    }
    int count = 0;
    char line[100];
    while (fgets(line, sizeof(line), f)) {
        count++;
    }
    fclose(f);
    return count;
}

// --- Legge numeri dal file ---
int* number(const char *filename, int length) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Cannot open file");
        exit(1);
    }
    int *numbers = malloc(length * sizeof(int));
    if (!numbers) {
        perror("Malloc failed");
        exit(1);
    }
    for (int i = 0; i < length; i++) {
        if (fscanf(f, "%d", &numbers[i]) != 1) {
            fprintf(stderr, "Error reading number at line %d\n", i+1);
            exit(1);
        }
    }
    fclose(f);
    return numbers;
}

// --- Insertion sort con array dinamico (simile al Python) ---
int* sort(int *numbers, int length) {
    int *numbersort = malloc(length * sizeof(int));
    int sorted_len = 0;

    for (int i = 0; i < length; i++) {
        int n = numbers[i];
        int inserted = 0;

        for (int j = 0; j < sorted_len; j++) {
            if (n < numbersort[j]) {
                // sposta tutto a destra
                for (int k = sorted_len; k > j; k--) {
                    numbersort[k] = numbersort[k-1];
                }
                numbersort[j] = n;
                inserted = 1;
                break;
            }
        }

        if (!inserted) {
            numbersort[sorted_len] = n;
        }

        sorted_len++;
    }

    return numbersort;
}

// --- Scrive array su file ---
void filegen(const char *filename, int *array, int length) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Cannot open result.txt");
        exit(1);
    }
    for (int i = 0; i < length; i++) {
        fprintf(f, "%d\n", array[i]);
    }
    fclose(f);
}

// --- Main ---
int main() {
    char filename[256];
    printf("File name: ");
    scanf("%s", filename);

    int length = leng(filename);
    int *numbers = number(filename, length);

    clock_t start = clock();
    int *sorted = sort(numbers, length);
    clock_t end = clock();

    filegen("result.txt", sorted, length);

    printf("File sorted successfully.\n");
    printf("Sorting lasted %.5f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(numbers);
    free(sorted);
    return 0;
}