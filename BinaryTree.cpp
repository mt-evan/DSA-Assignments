#include <iostream>
using namespace std;

class Data {
private:
    int value;
public:
    explicit Data(int x) {
        value = x;
    }

    void setValue(int x) {
        value=x;
    }
    int getValue() const {
        return value;
    }

    void print() const {
        cout << value;
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

template <typename T> class BinarySearchTree {
private:
    Node<T> *root;
    int numberOfElements;
    int height;

    // helper method for finding the kth element
    // traverses tree in-order and keeps track of how many nodes we have visited
    // int i has the & so that its value is maintained across the recursions
    void findKthElementHelper(Node<T>* node, int k, int& i) {
        if (node != nullptr) {
            findKthElementHelper(node->getLeftChild(), k, i);
            i++;
            if (k == i) {
                node->print();
                cout << endl;
                return;
            }
            findKthElementHelper(node->getRightChild(), k, i);
        }
    }

    // helper method for printing pre-order that is recursive
    void printPreorder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        node->print();
        cout << " ";
        printPreorder(node->getLeftChild());
        printPreorder(node->getRightChild());
    }

    // helper method for sortAscending() that is recursive
    // traverses tree in-order
    void sortAndPrintAscending(Node<T>* node) {
        if (node != nullptr) {
            sortAndPrintAscending(node->getLeftChild());
            node->print();
            cout << " ";
            sortAndPrintAscending(node->getRightChild());
        }
    }

    // helper method for sortDescending() that is recursive
    // traverses tree in-order but goes right first instead left
    void sortAndPrintDescending(Node<T>* node) {
        if (node != nullptr) {
            sortAndPrintDescending(node->getRightChild());
            node->print();
            cout << " ";
            sortAndPrintDescending(node->getLeftChild());
        }
    }

    // helper method for Destructor that recursively
    // traverses tree in post-order and deletes each node
    void deleteTree(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->getLeftChild());
        deleteTree(node->getRightChild());
        delete node->getData();
        delete node;
    }

    int updateHeight(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int leftSubtreeHeight = updateHeight(node->getLeftChild());
            int rightSubtreeHeight = updateHeight(node->getRightChild());

            if (leftSubtreeHeight >= rightSubtreeHeight) {
                return leftSubtreeHeight + 1;
            } else {
                return rightSubtreeHeight + 1;
            }
        }
    }
public:
    explicit BinarySearchTree(T* data) {
        root = new Node<T>(data);
        numberOfElements = 1;
        height = 1;
    }

    // Destructor
    // Idea: traverse tree with post Order and delete each node
    // post order so that root is deleted last
    ~BinarySearchTree() {
        deleteTree(root);
    }

    void setRoot(Node<T>* node) {
        root = node;
    }
    Node<T>* getRoot() {
        return root;
    }
    void setNumberOfElements(int x) {
        numberOfElements = x;
    }
    int getnumberOfElements() {
        return numberOfElements;
    }
    void setHeight(int h) {
        height = h;
    }
    int getHeight(){
        return height;
    }

    // print tree with Pre Order
    void print() {
        printPreorder(root);
        cout << endl;
    }

    void insertElement(T* data) {
        auto* node = new Node<T>(data);
        Node<T>* temp = root;
        // find where to insert
        while (temp != nullptr) {
            if (node->getData()->getValue() < temp->getData()->getValue()) {
                if (temp->getLeftChild() == nullptr) {
                    temp->setLeftChild(node);
                    node->setParent(temp);
                    break;
                } else {
                    temp = temp->getLeftChild();
                    continue;
                }
            } else if (node->getData()->getValue() > temp->getData()->getValue()) {
                if (temp->getRightChild() == nullptr) {
                    temp->setRightChild(node);
                    node->setParent(temp);
                    break;
                } else {
                    temp = temp->getRightChild();
                    continue;
                }
            }
            else {
                cout << "No dupicate items allowed\n";
                delete node;
                return;
            }
        }

        // find if height needs to be incremented
        height = updateHeight(root);
        numberOfElements++;
    }

    void deleteElement(T* data) {
        Node<T>* temp = root;
        Node<T>* nodeToDelete;
        Node<T>* parentOfNodeToDelete;

        // find the node we delete
        while (temp != nullptr) {
            if (data->getValue() == temp->getData()->getValue()) {
                nodeToDelete = temp;
                break;
            } else if (data->getValue() < temp->getData()->getValue()) {
                temp = temp->getLeftChild();
            } else {
                temp = temp->getRightChild();
            }
        }

        // if no such node exists in tree
        if (nodeToDelete == nullptr || temp == nullptr) {
            cout << "Number does not exist\n";
            return;
        }

        parentOfNodeToDelete = nodeToDelete->getParent(); // easier to keep track of the parent

        // how to rearrange the children and parent pointers
        // CASE 1: if no children
        if (nodeToDelete->getRightChild() == nullptr && nodeToDelete->getLeftChild() == nullptr) {
            // root is only element in tree and gets deleted
            if (nodeToDelete == root) {
                root = nullptr;
            }
                // if node being deleted is a left child
            else if (parentOfNodeToDelete->getLeftChild() == nodeToDelete) {
                parentOfNodeToDelete->setLeftChild(nullptr);
            }
                // if node being deleted is a right child
            else {
                parentOfNodeToDelete->setRightChild(nullptr);
            }
            delete nodeToDelete;
        }

            // at this point we know the node has at least one child
            // CASE 2: if only one child
            // has a right child
        else if (nodeToDelete->getLeftChild() == nullptr) {
            if (nodeToDelete == root) {
                root = nodeToDelete->getRightChild();
            } else if (parentOfNodeToDelete->getLeftChild() == nodeToDelete) {
                parentOfNodeToDelete->setLeftChild(nodeToDelete->getRightChild());
            } else {
                parentOfNodeToDelete->setRightChild(nodeToDelete->getRightChild());
            }
            delete nodeToDelete;
        }
            // has a left child
        else if (nodeToDelete->getRightChild() == nullptr) {
            if (nodeToDelete == root) {
                root = nodeToDelete->getLeftChild();
            } else if (parentOfNodeToDelete->getLeftChild() == nodeToDelete) {
                parentOfNodeToDelete->setLeftChild(nodeToDelete->getLeftChild());
            } else {
                parentOfNodeToDelete->setRightChild(nodeToDelete->getLeftChild());
            }
            delete nodeToDelete;
        }

            // CASE 3: if two children, must find a succeeding node
            // make a sucNodeParent pointer to make it easier
        else {
            Node<T>* sucNode = nodeToDelete->getLeftChild();
            Node<T>* sucNodeParent = nodeToDelete;
            // find right most child of left subtree to succeed
            while (sucNode->getRightChild() != nullptr) {
                sucNodeParent = sucNode;
                sucNode = sucNode->getRightChild();
            }

            // put the data of sucNode in nodeToDelete
            // we delete sucNode later since we copied its data
            nodeToDelete->setData(sucNode->getData());

            // adjust sucNode's original parent's pointer to its child that ended up succeeding
            if (sucNodeParent->getLeftChild() == sucNode) {
                sucNodeParent->setLeftChild(sucNode->getRightChild());
            } else {
                sucNodeParent->setRightChild(sucNode->getRightChild());
            }
            // delete sucNode in this case instead of nodeToDelete because we did a "swap"
            delete sucNode;
        }

        // find if height needs to be decremented
        height = updateHeight(root);
        numberOfElements--;
    }

    // finds the element in the kth in
    // ascending order of elements in the tree and prints it
    void findKthElement(int k) {
        // if element is not in tree
        if (k < 1 || k > numberOfElements) {
            cout << "Number does not exist\n";
            return;
        }

        int i = 0;
        // traverse tree in-order and keep track of how many nodes we have visited
        // when i = k, we have found the kth element in ascending order
        findKthElementHelper(root, k, i);
    }

    // finds the smallest element in the
    // tree and prints it.
    void findSmallest() {
        Node<T>* temp = root;
        while (temp->getLeftChild() != nullptr) {
            temp = temp->getLeftChild();
        }
        cout << temp->getData()->getValue() << endl;
    }
    // finds the biggest element in the tree
    // and prints it
    void findBiggest() {
        Node<T>* temp = root;
        while (temp->getRightChild() != nullptr) {
            temp = temp->getRightChild();
        }
        cout << temp->getData()->getValue() << endl;
    }
    // prints all the elements stored in the BST
    // in ascending order
    // must be written recursively
    void sortAscending() {
        sortAndPrintAscending(root);
        cout << endl;
    }
    // prints all the elements stored in the BST
    // in descending order
    // must be written recursively
    void sortDescending() {
        sortAndPrintDescending(root);
        cout << endl;
    }
};

int main() {
    int a[] = {10,45,23,67,89,34,12,99};
    Data* newData = new Data(a[0]);
    BinarySearchTree<Data>* newBST = new BinarySearchTree<Data>(newData);
    for(int i=1;i< (sizeof(a)/sizeof(int));i++)
    {
        newData = new Data(a[i]);
        newBST->insertElement(newData);
    }
    newBST->print();
    newBST->findSmallest();
    newBST->findBiggest();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete root
    newBST->print();
    newData = new Data(45);
    newBST->deleteElement(newData); //delete with two children
    newBST->print();
    newData = new Data(12);
    newBST->deleteElement(newData); //delete with one child
    newBST->print();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete a number that doesnt exist. What will you print?
    newBST->print();
    newBST->findKthElement(1); //first element
    newBST->findKthElement(newBST->getnumberOfElements()); //last element
    newBST->findKthElement(3); // some element in between
    newBST->findKthElement(7); // Edge case where item does not exist. What will you print?
    newBST->findSmallest();
    newBST->findBiggest();
    newBST->sortAscending();
    newBST->sortDescending();
    return 0;
}
