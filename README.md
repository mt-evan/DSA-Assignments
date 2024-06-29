# DSA-Assignments
Data Structures and Algorithms Programming Assignments

# Programming Assignment 1 README
CircularDLL.cpp

Evan Tardiff

2/13/24

Code description:

Class Process: Objects of this class hold the information of the process's name and how much time it has left as well as methods to update its time and display its information.

PUBLIC MEMBER VARIABLES
string processName; - Holds the name of the process.
int totalTime; - Holds the amount of seconds left for a process to be completed.

CONSTRUCTOR
Default constructor that initializes variables processName and totalTime.

PUBLIC MEMBER FUNCTIONS
void updateRunTime()
updateRunTime: Updates the variable totalTime by subtracting it by how many seconds have passed in each cycle. There are no inputs or outputs.
Precondition: Member variable totalTime and global variable quantTime are initialized, and totalTime > 0. An instance of Process has been initialized.
Postcondition: Member variable totalTime has been subtracted by quantTime. If totalTime is <= 0, then the node that holds this Process object gets deleted.

void print()
print: Without any input or output, which just simply prints out the processName and totalTime.
Precondition: The Process object, totalTime, and processName has been initialized.
Postcondition: The processName and totalTime values are printed out followed by " seconds" after totalTime.


Class Node: Objects of this class holds pointers to allow navigation to "adjacent" nodes with a previous and a next node pointer. Each node holds a Process object which includes its time left and process name, and each node has a print method to call its process's print method.

PUBLIC MEMBER VARIABLES
T *data; - A pointer to the Process object that the node stores.
Node<T> *next; - A pointer to the "next" node in the list.
Node<T> *prev; - A pointer to the "previous" node in the list.

CONSTRUCTOR
Default constructor that initializes *data, *next, and *prev.

PUBLIC MEMBER FUNCTIONS
void print()
print: Calls the print method of the Process object to print out its information. There is no input or output.
Precondition: The Node object has been initialized as well as the Process object it has stored in *data as well as any
preconditions required for the print method of Process.
Postcondition: The variables of Process, processName and totalTime, are printed.


Class CircularDLL: Objects of this class is a linked list where each node has a next and a prev node pointer, making it a doubly linked list, and where the head and tail nodes are connected to each other, making it a circular doubly linked list. It holds the nodes that holds the processes.

PUBLIC MEMBER VARIABLES
Node<T> *curr; - Whenever a node needs to be operated on directly, this pointer will point to it.
Node<T> *head; - Points to the head of the linked list to allow a starting/reference point for certain operations.
Node<T> *tail; - Points to the tail of the linked list to allow the program to connect the head and the last node for
inserting a node at the end of the list.
int length; - Holds the number to represent the list's length.

CONSTRUCTORS
Default constructor that initializes *curr, *head, *tail and length.

DESTRUCTORS
Default destructor that deletes each node starting at the head and working its way down to the tail.

PUBLIC MEMBER FUNCTIONS
int getLength()
getLength: Returns the length of the linked list.
Precondition: The linked list has been initialized and is not empty.
Postcondition: The integer held in the variable length is returned.

void printList()
printList: Updates all the processes' totalTime held in the nodes of the list before printing out their information (process names and seconds left). Method takes in no input and outputs nothing besides indirectly printing by calling the print methods of the Node and Process objects. Function works by starting at the head node, updating its runtime, and printing its information if it still has time left. If it does not have time left, then the node gets deleted.
Precondition: Linked list has been initialized, is not empty, and user has selected to not add another process.
Postcondition: All processes time have been updated via updateRunTime() of Process and have been deleted unless they still have time remaining, otherwise the process information gets printed.

void insertProcess(T *data)
insertProcess: Adds a new node to the end of the list. Takes in a Process object as input and creates a new node to store the Process object. There is no output.
Precondition: The linked list has been initialized and has at least one node. The user has decided to add a new process or processes are being prepopulated.
Postcondition: A new node has been ended to the end of the list. Tail pointer points to this node, and the head node's prev pointer points to this node. Length has been incremented by one.

void deleteProcess()
deleteProcess: Deletes a node if its Process object's has finished processing. There is no input or output.
Precondition: The printList() method has been run, and after Process' updateRunTime() executes, the Process object's
totalTime is 0 or less signifying that the process is complete.
Postcondition: If the node being deleted is the head or tail node, the next or previous node is now the head or tail
node respectively, and the node has been deleted. Length has been decremented by one.

# Programming Assignment 2 README
BinaryTree.cpp

Evan Tardiff

3/21/24

The prompt was to come up with a method that would take in any binary tree and output a balanced tree with its contents.

BinarySearchTree remakeTree(BinarySearchTree bst)
Helper method: constructBalancedBST(T array, int start, int end, BinarySearchTree tree)

This method works by initially creating an array filled with the tree’s contents in ascending order. A new tree is created to replace the old one using this array. The value at the index of (array.length - 1) / 2 becomes the root node because it is basically the middle value. The left side of this index and right side become their own arrays, and we repeat this process recursively on them until all the content has been inserted into the tree. We also do left side before right side in the same loop, but doing right first then left should yield the same result.

Pre-conditions:
● The input BST is not null meaning it is not empty
Post-conditions:
● The input BST is deleted whether it’s balanced or not
● A new BST replaces it that is definitely balanced and maintains BST properties
● All elements in the original BST are also in the new one

Pseudocode:
BinarySearchTree remakeTree(BinarySearchTree bst) {
// array is filled with the data in ascending order by traversing tree in-order
T array = createArrayFromBT(bst)
// create new BinarySearchTree
BinarySearchTree newBST = new BinarySearchTree()
// recursively construct the balanced binary search tree from the sorted array
constructBalancedBST(array, 0, array.length - 1, newBST)
deleteOldBST(bst)
return newBST
}
void constructBalancedBST(T array, int start, int end, BinarySearchTree tree) {
// base case when start is greater than end
if (start > end) { return null }
mid = (start+end)/2
node = new Node(array[mid])
tree->insertElement(node)
// recursively make the left subtree with the left part of array
node->setLeftChild(constructBalancedBST(array, start, mid - 1, tree)
// recursively make the right subtree with the right part of array
node->setRightChild(constructBalancedBST(array, mid + 1, end, tree)
}

Proof that it is O(n):
The time complexity for creating the array is O(n) because traversing a tree and visiting each element in an input size of N is O(n). Since each element in the array is processed once, constructing the new tree is O(n). The Big O of the whole algorithm without considering the inserts and deletes is: f(N) = N + N = 2N which is O(n).

# Programming Assignment 3 README
PrimAlgorithm.cpp

Evan Tardiff

5/4/24

Instead of using a list to implement the priority queue (min-heap), a binary tree implementation was a requirement for this assignment. Inserting into the binary tree to make it a min-heap was done with several cases. If the tree is perfect, then insert at the very left of a new depth. If the tree is not perfect, the left subtree is perfect, and the right subtree is not perfect, go right. If the tree is not perfect and the left subtree is not perfect, go left. This is done recursively until the new node is inserted. 
Deleting from this binary tree to make it a min-heap is done with a similar logic but vice versa.
Upheaping and downheaping are implemented so that the min-heap properties are not violated.

The prompt was to define a MST in my own words, define the preconditions of Prim's Algorithm, write the input and output of the algorithm mathematically, and explain a few real world applications of the algorithm.

A Minimum Spanning Tree, in my own words, is a set of edges that connects all the edges of a graph in a way such that there are no cycles, which makes it a tree, and the weights added up of the paths are the minimum possible given the weights of all the edges.

The preconditions to run the Prim’s algorithm of the code I have provided in PA3 is that the 2D array entered in correctly represents the graph it is supposed to represent. Another precondition is that the graph is weighted with any weights being greater than zero, though for a different implementation of Prims algorithm, this may be different. Two more preconditions are that the graph is connected and that it is undirected.

Input:
G = (V,E) where G is a connected, undirected, and weighted graph, where V is the set of all its vertices, and where E is the set of all its edges.
G = (V,E)
Output:
T, a set of edges, which is a minimum spanning tree of G.
T ⊆ E

Some real-world applications of Minimum Spanning Trees include network design to get an overall less expensive path to reach an office or station. For example, a phone line wants to charge you for each wire, so you want an efficient way to connect all computers together and to maximize your savings. Connecting them all in a Minimum Spanning Tree would achieve this. Another real-world application could be a UPS driver needing to deliver a bunch of packages. He wants to be efficient to save time and gas, so following a Minimum Spanning Tree would be ideal since it would provide the best overall route to reach all destinations.
