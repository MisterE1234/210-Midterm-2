//COMSC-210|Midterm-2|Ethan Aylard
//IDE used: Visual Studio Code
//I am going to simulate a coffee house line usding randomly generated names.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        cout << "Printing line: \n";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        cout << "Printing line in reverse: \n";
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    string get_position(int pos) {
    string name;
    if (!head) {
            cout << "List is empty." << endl;
            name = "Error";
            return name;
        }
    
        if (pos == 1) {
            name = head->data;
            return name;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                name = "Error";
                return name;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            name = "Error";
            return name;
        }
    
        name = temp->data;
    
        
        return name;
    }
};
// getRandInt():  creates a random integer value:
//requires: nothing
//returns: int
int getRandInt();

//randIntVar(): Creats a random integer with a variable begining:
//requires : int
//returns: int
int randIntVar(int); 



int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    srand((time(0)));
    const int SIZE = 99;
    const int totalTime = 20;
    int chance;
    int sizeVar;
    int rand_pos;
    string nameTemp;
    ifstream inFile;
    DoublyLinkedList custOrder;

    inFile.open("names.txt");
    if (!inFile){
        cout << "Error opening file." << endl;
        return 1;
    }

    //getting names:
    string names [SIZE];
    for (int i = 0; i < SIZE; i++){
        getline(inFile, nameTemp);
        names[i] = nameTemp;

    }

    inFile.close();

    //Store opens with five names:
    custOrder.push_back(names[getRandInt()]);
    custOrder.push_back(names[getRandInt()]);
    custOrder.push_back(names[getRandInt()]);
    custOrder.push_back(names[getRandInt()]);
    custOrder.push_back(names[getRandInt()]);
    sizeVar = 5;

    cout << "Store opening: \n";
    custOrder.print();

    //Every minute some event happens:
    for (int min = 1; min <= totalTime; min++){
    chance = getRandInt();
    cout << "Time since opened:" << min << endl;
    
    //Customer getting served: 40%
    if (chance < 40) {
        cout <<  custOrder.get_position(1) << " is served.\n";
        custOrder.pop_front();
        sizeVar--;
    }

    // Customer leaves from the back: 20%
    chance = getRandInt();
    if (chance < 20) {
    cout <<  custOrder.get_position(sizeVar) << " (at the rear) left the line.\n";
    custOrder.pop_back();
    sizeVar--;
    }
    //Customer joins the end of line: 60%
    chance = getRandInt();
    if (chance < 60){
        custOrder.push_back(names[getRandInt()]);
        sizeVar++;
        cout <<  custOrder.get_position(sizeVar) << " joins the line.\n";
        
    }

    //Customer leaves line: 10%
    chance = getRandInt();
    if (chance < 10){
        rand_pos = randIntVar(sizeVar);
        cout << custOrder.get_position(rand_pos) << " Leaves the line.\n";
        custOrder.delete_pos(rand_pos);
        sizeVar--;
    }

    //VIP arrives: 10%
    chance = getRandInt();
    if (chance < 10){
        custOrder.push_front(names[getRandInt()]);
        cout << custOrder.get_position(1) << " (VIP) joins the front of the line.\n";
        sizeVar++;
    }


    custOrder.print();
    cout << endl;
    }



    //Delete list:
    custOrder.~DoublyLinkedList();

    return 0;
}


// getRandInt():  creates a random integer value:
//requires: nothing
//returns: int
int getRandInt(){

return rand() % 99;
}

//randIntVar(): Creats a random integer with a variable begining:
//requires : int
//returns: int
int randIntVar(int max){

    
    return (rand() % max) + 1; //returns an int 0-max
}