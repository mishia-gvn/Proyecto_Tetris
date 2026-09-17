#pragma once
#include "Event.h"

class ColaEvent{
private:

    struct Node{
        Event event;
        Node* next;

        Node(Event event) : event(event), next(nullptr){
        }
    };

    Node* frontNode;
    int size;

public:

    ColaEvent(){
        frontNode = nullptr;
        size = 0;
    }

    ~ColaEvent(){
        clear();
    }

    void enqueue(Event event){
        Node* newNode = new Node(event);

        if (frontNode == nullptr || event.triggerTime < frontNode->event.triggerTime){
            newNode->next = frontNode;
            frontNode = newNode;
            size++;
            return;
        }

        Node* current = frontNode;

        while (current->next != nullptr &&
            current->next->event.triggerTime <= event.triggerTime){
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;

        size++;
    }

    Event* front(){
        if (frontNode == nullptr){
            return nullptr;
        }

        return &frontNode->event;
    }

    Event dequeue(){
        if (frontNode == nullptr)
        {
            return Event(Event::SPAWN, 0.0f);
        }

        Node* temp = frontNode;
        Event event = temp->event;

        frontNode = frontNode->next;

        delete temp;
        size--;

        return event;
    }

    bool isEmpty() const{
        return frontNode == nullptr;
    }

    int getSize() const{
        return size;
    }

    void clear(){
        while (frontNode != nullptr){
            Node* temp = frontNode;
            frontNode = frontNode->next;

            delete temp;
        }

        size = 0;
    }
};