#include "RowList.h"

RowList::Row::Row(){
    for (int i = 0; i < BOARD_CELLS; i++){
        cells[i] = 0;
    }

    next = nullptr;
}

RowList::RowList(){
    head = nullptr;
    size = 0;

    for (int i = 0; i < BOARD_ROWS; i++){
        Row* newRow = new Row();

        if (head == nullptr){
            head = newRow;
        }
        else{
            Row* current = head;

            while (current->next != nullptr){
                current = current->next;
            }

            current->next = newRow;
        }

        size++;
    }
}

RowList::~RowList(){
    clear();
}

void RowList::clear(){
    Row* current = head;

    while (current != nullptr){
        Row* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    size = 0;
}

int RowList::getSize() const{
    return size;
}

int RowList::getCell(int row, int column) const{
    if (row < 0 || row >= size || column < 0 || column >= BOARD_CELLS){
        return 0;
    }

    Row* current = head;

    for (int i = 0; i < row; i++){
        current = current->next;
    }

    return current->cells[column];
}

void RowList::setCell(int row, int column, int value){
    if (row < 0 || row >= size || column < 0 || column >= BOARD_CELLS){
        return;
    }

    Row* current = head;

    for (int i = 0; i < row; i++){
        current = current->next;
    }

    current->cells[column] = value;
}

void RowList::copyRow(int source, int destination){
    for (int column = 0; column < BOARD_CELLS; column++) {
        int value = getCell(source, column);
        setCell(destination, column, value);
    }
}
