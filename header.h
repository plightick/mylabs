#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int p_1(char *input) {
    if (input[0] == '-') {
        for (int i = 1; input[i] != '\n' && input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                return 0;
            }
        }
    } else {
        for (int i = 0; input[i] != '\n' && input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                return 0;
            }
        }
    }
    return 1;
}

int p_2(char* input, int* integer) {
    int temp;
    if (p_1(input) && sscanf(input, "%d", &temp) == 1) {
        *integer = temp;
        return 1;
    } else {
        return 0;
    }
}

int p() {
    char in[20];
    int Int = 0;
    while (1) {
        fgets(in, sizeof(in), stdin);
        if (p_2(in, &Int) == 1) {
            break;
        } else if (in[0] == '\n') {
            return INT_MIN;
        } else {
            printf("Invalid input. Please enter an integer: ");
        }
    }
    return Int;
}

int check(int a, int b) {
    int c;
    while (1) {
        c = p();
        if (c == INT_MIN) {
            return INT_MIN;
        }
        if (c >= a && c <= b) {
            break;
        } else {
            printf("Input out of range. Please enter a number between %d and %d: ", a, b);
        }
    }
    return c;
}

int checker(int value) {
    int valid = 0;
    while (!valid) {
        printf("Enter a number (1 or 2): ");
        if (scanf("%d", &value) == 1) {
            if (value == 1 || value == 2) {
                valid = 1;
            } else {
                printf("Invalid input. Please enter 1 or 2.\n");
            }
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n');
        }
    }
    return value;
}

void foundAmountOfMax(const char *filename, int maxValue) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int num;
    int amount = 0;
    while (fread(&num, sizeof(int), 1, file)) {
        if (num == maxValue) {
            amount++;
        }
    }

    printf("Amount of max value = %d \n", amount);

    fclose(file);
}

void readingFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int num;
    while (fread(&num, sizeof(int), 1, file) == 1) {
        printf("%d\n", num);
    }

    fclose(file);
}

void fillingOutTheFile(const char *filename) {
    FILE *file = fopen(filename, "w+b");
    if (!file) {
        perror("Error");
        return;
    }

    printf("Press Enter on an empty line to finish:\n");

    int maxValue = INT_MIN;
    int minValue = INT_MAX;

    while (1) {
        int number = check(INT_MIN, INT_MAX);

        if (number == INT_MIN) {
            break;
        }

        if (maxValue <= number) {
            maxValue = number;
        }

        if (minValue >= number) {
            minValue = number;
        }

        fwrite(&number, sizeof(int), 1, file);
    }



    fclose(file);

    printf("First file: \n");
    readingFile(filename);

    foundAmountOfMax(filename, maxValue);

}

void maxValueToMin(const char *filename) {
    FILE *file = fopen(filename, "r+b"); 
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int num;
    int maxValue = INT_MIN;
    int minValue = INT_MAX;

    while (fread(&num, sizeof(int), 1, file)) {
        if (num < minValue) {
            minValue = num;
        }
        if (num > maxValue) {
            maxValue = num;
        }
    }

    fseek(file, 0, SEEK_SET);


    while (fread(&num, sizeof(int), 1, file)) {
        if (num == maxValue) {
            fseek(file, -sizeof(int), SEEK_CUR);

            fwrite(&minValue, sizeof(int), 1, file);
  
            fseek(file, 0, SEEK_CUR);
        }
    }


    fseek(file, 0, SEEK_SET);

    printf("New file: \n");


    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d\n", num);
    }

    fclose(file);
}

void bubble(const char *filename){
    FILE *file = fopen(filename, "r+b"); 
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int first;
    int second;
    int num;
    int count = 0;

    while (fread(&first, sizeof(int), 1, file)){
        count++;
    }

    for(int i = 0; i < count - 1; i++){

        fseek(file, 0, SEEK_SET);

        for(int j = 0; j < count - 1 - i; j++){
            fread(&first, sizeof(int), 1, file);
            fread(&second, sizeof(int), 1, file); 

            if (first < second){
                fseek(file, -2*sizeof(int), SEEK_CUR);

                fwrite(&second, sizeof(int), 1, file);
                fwrite(&first, sizeof(int), 1, file);

                fseek(file, -sizeof(int), SEEK_CUR);
            } else{
                fseek(file, -sizeof(int), SEEK_CUR);
            }

        }
    }

    printf("Sort file: \n");

    fseek(file, 0, SEEK_SET);

    while (fread(&num, sizeof(int), 1, file) == 1) {
        printf("%d\n", num);
    }

    fclose(file);
}