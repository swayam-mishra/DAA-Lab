#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the person struct
struct person {
    int id;
    char* name;
    int age;
    int height;
    int weight; // stored in pounds
};

// Global variables
struct person* people = NULL; // Dynamically allocated array of persons
int n = 0; // Number of people

// --- Utility Functions ---
void swap(struct person* a, struct person* b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void free_memory() {
    if (people != NULL) {
        for (int i = 0; i < n; i++) {
            free(people[i].name);
        }
        free(people);
        people = NULL;
        n = 0;
    }
}

// --- Min-Heap Functions (based on Age) ---
void min_heapify(int i, int size) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && people[left].age < people[smallest].age)
        smallest = left;
    if (right < size && people[right].age < people[smallest].age)
        smallest = right;

    if (smallest != i) {
        swap(&people[i], &people[smallest]);
        min_heapify(smallest, size);
    }
}

void build_min_heap() {
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heapify(i, n);
    }
}

// --- Max-Heap Functions (based on Weight) ---
void max_heapify(int i, int size) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && people[left].weight > people[largest].weight)
        largest = left;
    if (right < size && people[right].weight > people[largest].weight)
        largest = right;

    if (largest != i) {
        swap(&people[i], &people[largest]);
        max_heapify(largest, size);
    }
}

void build_max_heap() {
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(i, n);
    }
}

// --- Menu Option Functions ---

// 1. Read data from file
void read_data() {
    if (people != NULL) {
        free_memory();
    }

    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open data.txt\n");
        return;
    }

    char buffer[256];
    n = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        n++;
    }

    if (n == 0) {
        printf("File is empty.\n");
        fclose(file);
        return;
    }

    people = (struct person*)malloc(n * sizeof(struct person));
    if (people == NULL) {
        printf("Memory allocation failed!\n");
        fclose(file);
        n = 0;
        return;
    }

    rewind(file);
    char name_buffer[100];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d,%99[^,],%d,%d,%d",
               &people[i].id,
               name_buffer,
               &people[i].age,
               &people[i].height,
               &people[i].weight);

        people[i].name = (char*)malloc(strlen(name_buffer) + 1);
        strcpy(people[i].name, name_buffer);
    }
    fclose(file);

    // Print formatted table
    printf("%d records read successfully from data.txt.\n", n);
    printf("Id   Name                Age  Height  Weight(pound)\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d %-18s %-4d %-6d %-5d\n",
               people[i].id,
               people[i].name,
               people[i].age,
               people[i].height,
               people[i].weight);
    }
}

// 4. Display weight of youngest person
void display_youngest_weight() {
    if (n == 0) {
        printf("No data available. Please read data first.\n");
        return;
    }
    build_min_heap();
    double weight_kg = people[0].weight * 0.453592; // convert pounds → kg
    printf("Weight of youngest student: %.2f kg\n", weight_kg);
}

// 5. Insert new person into min-heap
void insert_new_person() {
    struct person new_person;
    char name_buffer[100];

    printf("Enter new person's details (ID,Name,Age,Height,Weight): ");
    scanf("%d,%99[^,],%d,%d,%d", &new_person.id, name_buffer, &new_person.age, &new_person.height, &new_person.weight);

    new_person.name = (char*)malloc(strlen(name_buffer) + 1);
    strcpy(new_person.name, name_buffer);

    n++;
    people = (struct person*)realloc(people, n * sizeof(struct person));
    people[n - 1] = new_person;

    int i = n - 1;
    while (i != 0 && people[(i - 1) / 2].age > people[i].age) {
        swap(&people[i], &people[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    printf("New person inserted successfully into the min-heap.\n");
}

// 6. Delete oldest person
void delete_oldest_person() {
    if (n == 0) {
        printf("Heap is empty. Nothing to delete.\n");
        return;
    }

    int oldest_index = 0;
    for (int i = 1; i < n; i++) {
        if (people[i].age > people[oldest_index].age) {
            oldest_index = i;
        }
    }

    printf("Deleting oldest person: %s (Age: %d)\n", people[oldest_index].name, people[oldest_index].age);
    free(people[oldest_index].name);

    people[oldest_index] = people[n - 1];
    n--;
    people = (struct person*)realloc(people, n * sizeof(struct person));

    if (n > 0) {
        build_min_heap();
        printf("Updated list after deletion:\n");
        printf("Id   Name                Age  Height  Weight(pound)\n");
        for (int i = 0; i < n; i++) {
            printf("%-4d %-18s %-4d %-6d %-5d\n",
                   people[i].id,
                   people[i].name,
                   people[i].age,
                   people[i].height,
                   people[i].weight);
        }
    } else {
        printf("Heap is now empty.\n");
    }
}

// --- Main Function ---
int main() {
    int option;

    do {
        printf("\n--- MAIN MENU (HEAP) ---\n");
        printf("1. Read Data\n");
        printf("2. Create Min Heap (based on Age)\n");
        printf("3. Create Max Heap (based on Weight)\n");
        printf("4. Display Weight of the Youngest Person\n");
        printf("5. Insert a New Person into the Min-Heap\n");
        printf("6. Delete the Oldest Person\n");
        printf("7. Exit\n");
        printf("------------------------\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: read_data(); break;
            case 2: build_min_heap(); printf("Min-heap based on age created.\n"); break;
            case 3: build_max_heap(); printf("Max-heap based on weight created.\n"); break;
            case 4: display_youngest_weight(); break;
            case 5: insert_new_person(); break;
            case 6: delete_oldest_person(); break;
            case 7: printf("Exiting program...\n"); break;
            default: printf("Invalid option. Please try again.\n");
        }
    } while (option != 7);

    free_memory();
    return 0;
}
