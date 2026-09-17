#pragma once
#include "Piece.h"

class Pila{
private:

    Piece* piece;
    const int capacity = 1;

public:

    Pila(){
        piece = nullptr;
    }

    ~Pila(){
        clear();
    }

    void push(Piece* newPiece){
        if (isFull()){
            return;
        }

        piece = newPiece;
    }

    Piece* pop(){
        if (isEmpty()){
            return nullptr;
        }

        Piece* temp = piece;
        piece = nullptr;

        return temp;
    }

    Piece* top() const{
        return piece;
    }

    bool isEmpty() const{
        return piece == nullptr;
    }

    bool isFull() const{
        return piece != nullptr;
    }

    void clear(){
        if (piece != nullptr){
            delete piece;
            piece = nullptr;
        }
    }
};