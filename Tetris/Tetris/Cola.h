#pragma once
#include "Piece.h"
#include "Constants.h"
#include <cstdlib>

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

    void enqueue(Piece* piece) {
        Node* newNode = new Node(piece);

        if (backNode == nullptr) {
            frontNode = newNode;
            backNode = newNode;
        }
        else {
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
        while (!isEmpty()) {
            Piece* piece = dequeue();
            delete piece;
        }
    }

    void fillBag() {
        int bag[PIECE_TYPES] = {
            PIECE_I,
            PIECE_O,
            PIECE_T,
            PIECE_J,
            PIECE_L,
            PIECE_S,
            PIECE_Z
        };

		for (int i = PIECE_TYPES - 1; i > 0; i--) {
            int j = rand() % (i + 1);
			
			int temp = bag[i];
			bag[i] = bag[j];
			bag[j] = temp;
		}

		for (int i = 0; i < PIECE_TYPES; i++) {
			enqueue(new Piece(bag[i]));
		}
    }
};
