#pragma once
#include <string>

struct PlayersScore {
    std::string name;
    int score;
};

inline void swap(PlayersScore& a, PlayersScore& b) {
    PlayersScore temp = a;
    a = b;
    b = temp;
}

inline void insertionSort(PlayersScore player[], int n, long& comparaciones, long& movimientos) {

    comparaciones = 0;
    movimientos = 0;

    for (int i = 1; i < n; i++) {

        PlayersScore clave = player[i];

        int j = i - 1;

        while (j >= 0) {

            comparaciones++;

            if (player[j].score < clave.score) {

                movimientos++;

                player[j + 1] = player[j];
                j--;
            }
            else {
                break;
            }
        }

        player[j + 1] = clave;

        movimientos++;
    }
}

inline void quickSort(PlayersScore player[], int left, int right, long& comparaciones, long& intercambios) {

    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;

    int pivot = player[(left + right) / 2].score;

    while (i <= j) {

        while (player[i].score > pivot) {
            comparaciones++;
            i++;
        }

        comparaciones++;

        while (player[j].score < pivot) {
            comparaciones++;
            j--;
        }

        comparaciones++;

        if (i <= j) {

            swap(player[i], player[j]);
            intercambios++;

            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(player, left, j, comparaciones, intercambios);
    }

    if (i < right) {
        quickSort(player, i, right, comparaciones, intercambios);
    }
}