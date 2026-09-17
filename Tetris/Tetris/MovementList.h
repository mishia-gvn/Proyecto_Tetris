#pragma once

enum MovementType {
    LEFT,
    RIGHT,
    DOWN,
    ROTATE,
    HARD_DROP
};

struct Node {
    MovementType movement;
    Node* previous;
    Node* next;

    Node(MovementType movement) {
        this->movement = movement;
        previous = nullptr;
        next = nullptr;
    }
};

class MovementList{
private:

    Node* head;
    Node* tail;
    Node* current;

public:

    MovementList(){
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~MovementList(){
        clear();
    }

    void add(MovementType movement){
        Node* newNode = new Node(movement);

        if (head == nullptr){
            head = newNode;
            tail = newNode;
            current = newNode;
            return;
        }

        if (current != tail){
            Node* temp = current->next;

            while (temp != nullptr){
                Node* next = temp->next;
                delete temp;
                temp = next;
            }

            current->next = nullptr;
            tail = current;
        }

        newNode->previous = current;
        current->next = newNode;

        tail = newNode;
        current = newNode;
    }

    bool undo(){
        if (current == nullptr){
            return false;
        }

        if (current->previous == nullptr){
            return false;
        }

        current = current->previous;
        return true;
    }

    bool redo(){
        if (current == nullptr){
            return false;
        }

        if (current->next == nullptr){
            return false;
        }

        current = current->next;
        return true;
    }

    void clear(){
        Node* currentNode = head;

        while (currentNode != nullptr){
            Node* next = currentNode->next;
            delete currentNode;
            currentNode = next;
        }

        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
};

