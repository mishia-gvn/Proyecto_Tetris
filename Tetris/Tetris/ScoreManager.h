#pragma once
#include "Constants.h"
#include "Sorting.h"

class ScoreManager {
private:
    PlayersScore scores[MAX_SCORES];
    int count;
    long lastComparaciones;
    long lastMovimientos;

public:
    ScoreManager() {
        count = 0;
        lastComparaciones = 0;
        lastMovimientos = 0;

        load();
        
        sortScores(true);
    }

    void load() {
        count = 0;

        ifstream file(SCORE_FILE);

        if (!file.is_open()) {
            return;
        }

        string name;
        int score;

        while (count < MAX_SCORES &&
            file >> ws &&
            getline(file, name, '|')) {

            if (file >> score) {
                scores[count].name = name;
                scores[count].score = score;
                count++;
            }

            file.ignore(1000, '\n');
        }

        file.close();
    }

    void save() const {
        ofstream file(SCORE_FILE);

        if (!file.is_open()) {
            return;
        }

        for (int i = 0; i < count; i++) {
            file << scores[i].name << "|" << scores[i].score << "\n";
        }

        file.close();
    }

    void addScore(const string& name, int score) {

        if (count < MAX_SCORES) {

            scores[count].name = name;
            scores[count].score = score;

            count++;
        }
        else {

            int lowestIndex = 0;

            for (int i = 1; i < count; i++) {

                if (scores[i].score < scores[lowestIndex].score) {
                    lowestIndex = i;
                }
            }

            if (score <= scores[lowestIndex].score) {
                return;
            }

            scores[lowestIndex].name = name;
            scores[lowestIndex].score = score;
        }
    }

    void sortScores(bool useQuickSort) {
        lastComparaciones = 0;
        lastMovimientos = 0;

        if (useQuickSort)
            quickSort(scores, 0, count - 1, lastComparaciones, lastMovimientos);
        else
            insertionSort(scores, count, lastComparaciones, lastMovimientos);
    }

    int getCount() const {
        return count;
    }

    long getLastComparaciones() const { 
        return lastComparaciones; 
    }
    
    long getLastMovimientos() const {
        return lastMovimientos;
    }

    PlayersScore getScore(int index) const {
        return scores[index];
    }
};