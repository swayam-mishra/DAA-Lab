## **Goal of the Program**

To:

1. Read integers from a file.
2. Sort them using **Merge Sort**.
3. Count number of comparisons made during sorting.
4. Measure and display **execution time in nanoseconds**.
5. Write the sorted result to another file.

---
## Why `#define MAX 1000`?

This sets the **maximum number of elements** the array can hold.  
Your instruction said:

> _"Number of elements in each input file should vary from 300 to 500 entries."_

So we choose `MAX = 1000` to be safely above that (a buffer), while still being memory-efficient for a C program.

---
## Breakdown of the Code

### 1. **Header Files**

``` C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
```

- `stdio.h`: For input/output operations.
- `stdlib.h`: For `malloc`, `free`, and `exit`.
- `time.h`: To measure time using `clock()`.

---
### 2. **Global Comparison Counter**

``` C
int comparison_count = 0;
```

This variable counts **how many times elements are compared** during sorting.  
It helps analyze algorithm performance beyond just time.

---
### 3. **Merge Function**

``` C
void merge(int arr[], int l, int m, int r)
```
This is the **core of merge sort**. It:

- Splits the array into two halves (from `l` to `m`, and `m+1` to `r`)
- Merges them into a sorted segment
- Counts comparisons between elements from both halves

Use of `malloc` creates temporary arrays `L` and `R` to hold the left and right segments of the array.

---
### 4. **Recursive Merge Sort**

``` C
void mergeSort(int arr[], int l, int r)
```

Classic divide-and-conquer:

- Divide the array until each piece has 1 element.
- Merge back using the `merge()` function.
- Sorting happens during merging, not splitting.

---
### 5. **Reading from File**

``` C
int readFromFile(const char *filename, int arr[])
```
- Opens file in read mode
- Reads integers one by one using `fscanf`
- Stores them in the array `arr`
- Returns how many elements were read

This keeps the program flexible: you can change the input file and the code will adapt.

---
### 6. **Writing to File**

``` C
void writeToFile(const char *filename, int arr[], int n)
```
- Writes sorted array to output file using `fprintf`.

---
### 7. **Printing Array**
``` C
void printArray(int arr[], int n)
```

Prints the array content on screen before and after sorting.

---
### 8. **Main Menu Loop**

c

CopyEdit

`while (1) {     printf("\nMAIN MENU (MERGE SORT)\n");     ...     scanf("%d", &choice);`

- Provides a **menu-driven interface**.
    
- Lets the user choose between ascending, descending, or random input files.
    
- Based on input, sets the input and output file names accordingly.
    
- Calls sorting logic and displays results.
    

---

### 9. **Measuring Execution Time**

c

CopyEdit

`start = clock(); // Sorting operation end = clock();`

- `clock()` gives processor time in **clock ticks**.
    
- Convert it to **nanoseconds**:
    

c

CopyEdit

`double elapsed_time = ((double)(end - start) * 1000000000.0) / CLOCKS_PER_SEC;`

This assumes only this program is using the CPU — as per your assignment note.

---

## 🧠 Why is this design effective?

| Feature              | Why it's used                                     |
| -------------------- | ------------------------------------------------- |
| `MAX 1000`           | Safe buffer for 500-entry files. Avoids overflow. |
| `mergeSort`          | Efficient (O(n log n)) comparison-based sorting   |
| `comparison_count`   | Useful for algorithm performance analysis         |
| `clock()`            | Portable and simple timing method                 |
| `fscanf` / `fprintf` | Clean way to handle structured file input/output  |
| Menu Loop            | Makes program user-friendly and reusable          |