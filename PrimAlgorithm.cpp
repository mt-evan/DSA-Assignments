#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
using namespace std;

const int VERTEXCOUNT = 5;

class Data {
private:
    int sourceVertex;
    int destinationVertex;
    int edgeCost;
public:
    Data(int sourceVertex, int destinationVertex, int edgeCost) {
        this->sourceVertex = sourceVertex;
        this->destinationVertex = destinationVertex;
        this->edgeCost = edgeCost;
    }
    void print() const {
        cout << sourceVertex << " - " << destinationVertex << " -> " << edgeCost << endl;
    }
    // returns true if this data's edge cost is smaller than the other
    bool compareValue(int otherEdgeCost) {
        return edgeCost < otherEdgeCost;
    }
    void setSourceVertex(int x) {
        sourceVertex = x;
    }
    int getSourceVertex() {
        return sourceVertex;
    }
    void setDestinationVertex(int x) {
        destinationVertex = x;
    }
    int getDestinationVertex() {
        return destinationVertex;
    }
    void setEdgeCost(int x) {
        edgeCost = x;
    }
    // getValue returns edgeCost
    int getValue() {
        return edgeCost;
    }
};

template <typename T> class Node {
private:
    T* data;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;
public:
    explicit Node (T* data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    }
    void print () {
        data->print ();
    }
    // compare method to compare Data values.
    // returns true if this data's edge cost is smaller than the other
    bool compareData(T* otherData) {
        return data->compareValue(otherData->getValue());
    }
    void setData(T* x) {
        data = x;
    }
    T* getData() {
        return data;
    }
    void setLeftChild(Node<T>* node) {
        leftChild = node;
    }
    Node<T>* getLeftChild() {
        return leftChild;
    }
    void setRightChild(Node<T>* node) {
        rightChild = node;
    }
    Node<T>* getRightChild() {
        return rightChild;
    }
    void setParent(Node<T>* node) {
        parent = node;
    }
    Node<T>* getParent() {
        return parent;
    }
};

template <typename T> class BinaryHeap {
private:
    Node<T>* root;
    int numberOfElements;
    int height;
    // helper method for destructor
    void deleteHeap(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        deleteHeap(node->getLeftChild());
        deleteHeap(node->getRightChild());
        delete node;
    }
    int countHeight(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int leftSubtreeHeight = countHeight(node->getLeftChild());
            int rightSubtreeHeight = countHeight(node->getRightChild());

            if (leftSubtreeHeight >= rightSubtreeHeight) {
                return leftSubtreeHeight + 1;
            } else {
                return rightSubtreeHeight + 1;
            }
        }
    }
    // return true if subtree is full
    bool isSubTreeFull(Node<T>* subRoot) {
        int subNumberOfElements = countNodes(subRoot);
        int subHeight = countHeight(subRoot);
        return pow(2, subHeight) - 1 == subNumberOfElements;
    }
    // counts the number of elements in a subtree
    int countNodes(Node<T>* subRoot) {
        if (subRoot == nullptr) {
            return 0;
        } else {
            return 1 + countNodes(subRoot->getLeftChild()) + countNodes(subRoot->getRightChild());
        }
    }

public:
    BinaryHeap() {
        root = nullptr;
        numberOfElements = 0;
        height = 0;
    }
    ~BinaryHeap() {
        deleteHeap(root);
    }
    void setRoot (Node<T>* node) {
        root = node;
    }
    Node<T>* getRoot() {
        return root;
    }
    void setNumberOfElements(int x) {
        numberOfElements = x;
    }
    int getNumberOfElements() {
        return numberOfElements;
    }
    void setHeight(int x) {
        height = x;
    }
    int getHeight() {
        return height;
    }

    //inserts the data into the heap and
    //heapify. This method return nothing
    void insertElement(T* data) {
        auto* newNode = new Node<T>(data);
        if (root == nullptr) {
            root = newNode;
            numberOfElements = 1;
            height = 1;
            return;
        }
        Node<T>* temp = root;
        // if tree is full, meaning 2^h - 1 == numberOfElements, next insert on far left of a new level
        if (numberOfElements == pow(2, height) -1) {
            while (temp->getLeftChild() != nullptr) {
                temp = temp->getLeftChild();
            }
            temp->setLeftChild(newNode);
            newNode->setParent(temp);
        }
            // if left subtree is full, go right, else go left. repeat
            // a subtree is full if its subNumberOfElements == 2^subheight - 1
        else {
            while (true) {
                // does temp have a left child? If not insert there
                if (temp->getLeftChild() == nullptr) {
                    temp->setLeftChild(newNode);
                    newNode->setParent(temp);
                    break;
                }
                // is left subtree full?
                if (isSubTreeFull(temp->getLeftChild())) {
                    if (temp->getRightChild() == nullptr) {
                        temp->setRightChild(newNode);
                        newNode->setParent(temp);
                        break;
                    } else {
                        temp = temp->getRightChild();
                    }
                } else {
                    temp = temp->getLeftChild();
                }
            }
        }
        numberOfElements++;
        height = countHeight(root);
        // upheap. only change data and not pointers of nodes
        while (newNode != root && newNode->compareData(newNode->getParent()->getData())) {
            T* tempData = newNode->getData();
            newNode->setData(newNode->getParent()->getData());
            newNode->getParent()->setData(tempData);
            newNode = newNode->getParent();
        }
    }

    //finds the smallest element in the tree and
    //returns it to the calling method and heapify. It returns the data object
    T* deleteMin() {
        Node<T>* temp = root;
        T* dataToReturn = root->getData();
        if (root == nullptr) {
            return nullptr;
        }
        if (root->getLeftChild() == nullptr) {
            root = nullptr;
            numberOfElements = 0;
            height = 0;
            return dataToReturn;
        }
        // algorithm to find successor node:
        // if no left child, take current node
        // if only left child, take left child
        // if tree is full, go right
        // if right subtree not full, go right, else go left
        while (true) {
            if (temp->getLeftChild() == nullptr) { // if no left child, take current node
                root->setData(temp->getData());
                if (temp == temp->getParent()->getLeftChild()) {
                    temp->getParent()->setLeftChild(nullptr);
                } else {
                    temp->getParent()->setRightChild(nullptr);
                }
                delete temp;
                break;
            }
            else if (temp->getLeftChild() != nullptr && temp->getRightChild() == nullptr) { // if only left child, take left child
                temp = temp->getLeftChild();
                root->setData(temp->getData());
                temp->getParent()->setLeftChild(nullptr);
                delete temp;
                break;
            }
            else if (isSubTreeFull(temp)) { // if tree is full, go right
                temp = temp->getRightChild();
            } else if (isSubTreeFull(temp->getRightChild())) {  // if right subtree full, go left, else go right
                temp = temp->getLeftChild();
            } else {
                temp = temp->getRightChild();
            }
        }
        // down heap
        temp = root;
        while (true) {
            // if temp has no children, we are done
            if (temp->getLeftChild() == nullptr) {
                break;
            }
            // if temp only has a left child, do one last comparison
            if (temp->getLeftChild() != nullptr && temp->getRightChild() == nullptr) {
                if (!temp->compareData(temp->getLeftChild()->getData())) {
                    T* tempData = temp->getData();
                    temp->setData(temp->getLeftChild()->getData());
                    temp->getLeftChild()->setData(tempData);
                }
                break;
            }
            // if temp has both a left and right child, compare which child is lesser and compare that with temp
            if (temp->getLeftChild() != nullptr && temp->getRightChild() != nullptr) {
                // which child is lesser?
                Node<T>* lesserChild;
                // if left child is smaller
                if (temp->getLeftChild()->compareData(temp->getRightChild()->getData())) {
                    lesserChild = temp->getLeftChild();
                }
                    // if right child is smaller or they are equal
                else {
                    lesserChild = temp->getRightChild();
                }
                // compare lesser child with temp
                if (lesserChild->compareData(temp->getData())) {
                    T* tempData = temp->getData();
                    temp->setData(lesserChild->getData());
                    lesserChild->setData(tempData);
                    temp = lesserChild;
                }
                    // if lesser child is larger than temp, we are done
                else {
                    break;
                }
            }
        }
        numberOfElements--;
        height = countHeight(root);
        return dataToReturn;
    }
};

// runs the prims algorithm on the graph and prints the output
void runPrims (int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap) {
    cout << "Prim's MST is Edge -> Cost" << endl;
    list<int> unvisited;
    list<int> visited;

    // initialize all vertices as unvisited
    for (int i = 0; i < VERTEXCOUNT; i++) {
        unvisited.push_back(i);
    }

    // select 0 as the starting vertex
    int currVertex = unvisited.front();
    auto x = find(unvisited.begin(), unvisited.end(), currVertex);
    unvisited.erase(x);
    // add the current vertex to visited
    visited.push_back(currVertex);
    // initialize the first batch of edges to consider
    // add edges connected to the current vertex to the binary heap
    for (int i = 0; i < VERTEXCOUNT; i++) {
        // check if the edge is not zero and the adjacent vertex is not visited
        if (G[currVertex][i] != 0) {
            Data* edge = new Data(currVertex, i, G[currVertex][i]);
            binHeap->insertElement(edge);
        }
    }

    while (visited.size() != VERTEXCOUNT) {
        // find the minimum edge in the priority queue
        // delete the minimum edge from the binary heap
      //  Node<Data>* minEdgeNode = binHeap->deleteMin();
        Data* minEdge = binHeap->deleteMin();
        int destinationVertex = minEdge->getDestinationVertex();
        // loop until we find an edge that brings us to an unvisited vertex
        // find(visited.begin(), visited.end(), i) != visited.end() returns true if i is in list
        while (find(visited.begin(), visited.end(), destinationVertex) != visited.end()) {
            minEdge = binHeap->deleteMin();
            destinationVertex = minEdge->getDestinationVertex();
        }
        minEdge->print();
        // add the vertex to the visited list
        currVertex = minEdge->getDestinationVertex(); // maybe change to source
        x = find(unvisited.begin(), unvisited.end(), currVertex);
        unvisited.erase(x);
        visited.push_back(currVertex);
        // add edges connected to the current vertex to the binary heap
        for (int i = 0; i < VERTEXCOUNT; i++) {
            // check if the edge is not zero and the adjacent vertex is not visited
            // find(visited.begin(), visited.end(), i) == visited.end() returns false if i is in list
            if (G[currVertex][i] != 0 && find(visited.begin(), visited.end(), i) == visited.end()) {
                Data* edge = new Data(currVertex, i, G[currVertex][i]);
                binHeap->insertElement(edge);
            }
        }
    }
}

int main() {
    int G[VERTEXCOUNT][VERTEXCOUNT] ={
            {0, 3, 65, 0, 0},
            {3, 0, 85, 20, 45},
            {65, 85, 0, 41, 77},
            {0, 20, 41, 0, 51},
            {0, 45, 77, 51, 0}
    };
    auto* binHeap = new BinaryHeap<Data>;
    runPrims(G, binHeap);
    delete binHeap;
    return 0;
}
