#pragma once

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void insertionSort(int A[], int n, long& comparaciones, long& movimientos) {

    comparaciones = 0;
    movimientos = 0;

    for (int i = 1; i < n; i++) {

        int clave = A[i];

        int j = i - 1;

        while (j >= 0) {

            comparaciones++;
            if (A[j] > clave) {

                movimientos++;

                A[j + 1] = A[j];
                j = j - 1;
            }
            else {
                break;
            }
        }

        A[j + 1] = clave;

        movimientos++;
    }
}

void quickSort(int A[], int left, int right,
    long& comparaciones, long& intercambios){
    if (left >= right){
        return;
    }

    int i = left;
    int j = right;
    int pivot = A[(left + right) / 2];

    while (i <= j){
        while (A[i] < pivot){
            comparaciones++;
            i++;
        }

        comparaciones++;

        while (A[j] > pivot){
            comparaciones++;
            j--;
        }

        comparaciones++;

        if (i <= j){
            swap(A[i], A[j]);
            intercambios++;

            i++;
            j--;
        }
    }

    if (left < j){
        quickSort(A, left, j, comparaciones, intercambios);
    }

    if (i < right){
        quickSort(A, i, right, comparaciones, intercambios);
    }
}