#include <iostream>
using namespace std;

// quantum time: used to decrement the time left for each process
int quantTime = 0;

class Process {
public:
    string processName;
    int totalTime;
    Process (string processName, int totalTime){
        //Fill constructor here
        this->processName = processName;
        this->totalTime = totalTime;
    }
    void updateRunTime() {
        //write method to update totalTime after each quantum cycle.
        totalTime -= quantTime;
    }
    void print () {
        //write print method to print the name of the process and the time left
        cout << processName << " " << totalTime << " seconds";
    }
};
// Node Class: Node for the DoublyLinkedList
template <typename T> class Node {
public:
    T *data;
    Node<T> *next;
    Node<T> *prev;
    Node (T *data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
    Node () {
        next = nullptr;
        prev = nullptr;
    }
    void print () {
        data->print ();
    }
};
//CircularDoublyLinkedList Class: Container for Nodes
template <typename T> class CircularDLL {
private:
    Node<T> *curr;
    Node<T> *head;
    Node<T> *tail;
    int length;
public:
// Constructor
    CircularDLL(T *data) {
        //Write constructor for the DLL here
        curr = new Node<T>(data);
        head = curr;
        tail = curr;
        length = 1;
    }

    //Destructor
    ~CircularDLL() {
        //Write code for destructor here
        curr = head;
        while (head) {
            head = head->next;
            delete curr;
            curr = head;
        }
    }

    // Accesser for length
    int getLength() {
        return length;
    }

    Node<T> * getHead() {
        return head;
    }

    Node<T> * getNextNode(Node<T> *node) {
        return node->next;
    }

    void printList() {
        //Write code to print the list here.
        curr = head;
        int i = 1;
        for (int j = 0; j < length; j++) {
            cout << "\t" << i << ".   ";
            i++;
            curr->print();
            cout << endl;
            curr = curr->next;
        }
        cout << endl;
    }

    //Insert a process at the end of the list
    void insertProcess(T *data) {
        //write code to insert process here
        curr = new Node<T>(data);

        curr->next = head;
        head->prev = curr;

        tail->next = curr;
        curr->prev = tail;
        tail = curr;
        length++;
    }

    //Delete a Process
    void deleteProcess(Node<T> *node) {
        //write code to delete process here
        curr = node;
        if (curr==head) {
            head = curr->next;
        }
        if (curr==tail) {
            tail = curr->prev;
        }
        length--;
        if (length == 1) {
            curr->next->next = nullptr;
            curr->next->prev = nullptr;
        } else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        delete curr;
    }
};


int main() {
    int numOfSecondsPassed = 0;
    int cycleNum = 1;
    int n;
    char userDecision;
    string tempName;
    int tempTime;
    Process *tempProcess;
    Node<Process> *currNode;
    Node<Process> *tempNode;

    // Start the Main program by asking the user what quantum time the scheduler algorithm will be
    cout << "Enter Quantum Time:";
    cin >> quantTime;

    cout << "\nPrepopulating with processes\n" << endl;

    // prepopulated data
    auto *processA = new Process("Process A", 10);
    auto *processB = new Process("Process B", 12);
    auto *processC = new Process("Process C", 8);
    auto *processD = new Process("Process D", 5);
    auto *processE = new Process("Process E", 10);

    // the linked list
    auto *linkedList = new CircularDLL<Process>(processA);
    linkedList->insertProcess(processB);
    linkedList->insertProcess(processC);
    linkedList->insertProcess(processD);
    linkedList->insertProcess(processE);

    linkedList->printList();

    do {
        cout << "Add new process? (Enter Y/N)" << endl;
        cin >> userDecision;
        if (userDecision == 'Y' || userDecision == 'y'){
            cout << "Enter New Process Name: " << endl;
            cin.ignore();
            getline(cin, tempName);
            cout << "Enter Total Process Time: " << endl;
            cin >> tempTime;
            tempProcess = new Process("Process " + tempName, tempTime);
            linkedList->insertProcess(tempProcess);
            cout << "Process Added." << endl;
            continue;
        } else {
            cout << "Running Cycle " << cycleNum << endl << endl;
            numOfSecondsPassed += quantTime;
            cout << "After cycle " << cycleNum << " - " << numOfSecondsPassed << " second elapses - state of processes is as follows:\n";
            cycleNum++;
            // iterates through all nodes to update the processes totalTime. deletes them if needed.
            n = linkedList->getLength();
            currNode = linkedList->getHead();
            for (int j = 0; j < n; j++) {
                tempNode = linkedList->getNextNode(currNode);
                currNode->data->updateRunTime();
                if (currNode->data->totalTime <= 0) {
                    linkedList->deleteProcess(currNode);
                }
                currNode = tempNode;
            }
            linkedList->printList();
        }
    } while(linkedList->getLength() > 0); // exit loop and program when linked list is empty
    cout << "All processes are completed";
    return 0;
}
