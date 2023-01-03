#ifndef TYPE_DIKD_H
#define TYPE_DIKD_H
#include<iostream>
using namespace std;

class LinkedList;

struct Node{
    Node(int x, double y):name(x),distance(y){};
    int name;
    double distance;
};

struct Arc{
    Arc():head(0),cost(0),next(0){};
    Arc(int x, double y):head(x),cost(y),next(0){};
    int head;
    double cost;
    Arc* next;
    friend struct LinkedList;
};

struct LinkedList{
    LinkedList():first(0){};
    Arc* first;
    void PrintList();
    void Push_back(int x, double y,Arc***);
};

void LinkedList::Push_back(int x, double y,Arc*** last){
    Arc *newArc = new Arc(x,y);
    if (first == 0) {
        first = newArc;
        return;
    }
    Arc *current = first;
    while (current->next != 0) {
        current = current->next;
    }
    current->next = newArc;
}


void LinkedList::PrintList(){
    if (first == 0) {
        cout << "List is empty.\n";
        return;
    }
    Arc *current = first;
    while (current != 0) {
        cout << "h:"<<current->head << " c:"<<current->cost<<"  ";
        current = current->next;
    }
    cout << endl;
}


#endif

