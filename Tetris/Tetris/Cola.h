#pragma once
#include "Piece.h"

class Cola {
private:

    struct Node {
        Piece* piece;
        Node* next;

        Node(Piece* piece) {
            this->piece = piece;
            next = nullptr;
        }
    };

    Node* frontNode;
    Node* backNode;
    int size;

public:

    Cola(){
        frontNode = nullptr;
        backNode = nullptr;
        size = 0;
    }

    ~Cola(){
        clear();
    }

    void enqueue(Piece* piece){
        Node* newNode = new Node(piece);

        if (backNode == nullptr){
            frontNode = newNode;
            backNode = newNode;
        }
        else{
            backNode->next = newNode;
            backNode = newNode;
        }

        size++;
    }

    Piece* dequeue(){
        if (frontNode == nullptr){
            return nullptr;
        }

        Node* temp = frontNode;
        Piece* piece = temp->piece;

        frontNode = frontNode->next;

        if (frontNode == nullptr){
            backNode = nullptr;
        }

        delete temp;
        size--;

        return piece;
    }

    Piece* front() const{
        if (frontNode == nullptr){
            return nullptr;
        }

        return frontNode->piece;
    }

    bool isEmpty() const{
        return frontNode == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    void clear(){
        while (!isEmpty()){
            dequeue();
        }
    }
};