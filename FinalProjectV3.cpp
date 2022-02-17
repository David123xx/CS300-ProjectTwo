//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : David Robey
// Version     : 2.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : CS300 final project final version
//============================================================================

/*
* I want to state that I realized my previous uploads were not working properly
* upon exiting the program. I feel like that was copping out. instead I decided 
* make cleaner and more functional code re-using the recourses we have already 
* created in this class. that is why I labeled it Version 2.0.
* I feel like this should've been the go-to route.
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Course {
    string courseId; // unique identifier
    string courseName;
    vector<string> prerequisites;

    Course() {
        courseId = "";
        courseName = "";
        prerequisites;
    }
};

// Internal structure for tree node
struct Node {
    //changed internal structure. rest looked more like it was from hash class
    Course course;
    Node* right;
    Node* left;

    Node() {
        right = left = nullptr;
    }

    Node(Course course) : Node() {
        this->course = course;
    }
    
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    //added
    void PostOrder();
    //added
    void postOrder(Node* node);
    //addded
    void preOrder(Node* node);
    //added
    void PreOrder();
    Node* getRoot();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root
    this->preOrder(root);
}
/**
 * Remove node prive method
 */

Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    //if node is nullptr return node
    if (node == nullptr) {
        return node;
    }
    //checks left based on string value
    if (courseId.compare(node->course.courseId) < 0) {
        //recursive check removeNode()
        node->left = removeNode(node->left, courseId);
    }
    //else checks right based on string value
    else if (courseId.compare(node->course.courseId) > 0) {
        //recursive check removeNode()
        node->right = removeNode(node->right, courseId);
    }
    else {
        // if there is no children simply delete the node - remove leaf
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // If there is a left children remove node
        else if (node->left != nullptr && node->right == nullptr) {
            Node* tempNode = node;
            node = node->left;
            delete tempNode;
            // If there is a right children remove node
        }
        else if (node->left == nullptr && node->right != nullptr) {
            Node* tempNode = node;
            node = node->right;
            delete tempNode;
        }
        else {
            // Find successor (leftmost child of right subtree)
            Node* temp = node->right;
            while (temp->left == nullptr) {
                temp = temp->left;
            }
            node->course = temp->course;
            node->right = removeNode(node->right, temp->course.courseId);
        }
    }
    return node;
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    //if root equal nullptr
    if (this->root == nullptr) {
        //root is equal to new node bid
        this->root = new Node(course);
    }
    else {
        // other wise add it to the root
        this->addNode(root, course);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string courseId) {
    // FIXME (6) Implement removing a bid from the tree
    // remove node root bidID
    this->removeNode(root, courseId);
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {
    Node* current = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr) {
        // if match found, return current bid
        if (current->course.courseId.compare(courseId) == 0) {
            cout << current->course.courseId << ", " << current->course.courseName << endl;
            cout << "Prerequisites: ";
            if (current->course.prerequisites.size() == 0) {
                cout << "None" << endl;
            }
            else {
                for (int i = 0; i < current->course.prerequisites.size(); ++i) {
                    if (i != (current->course.prerequisites.size() - 1)) {
                        cout << current->course.prerequisites.at(i) << ", ";
                    }
                    else {
                        cout << current->course.prerequisites.at(i) << endl;
                    }
                }
            }

            return current->course;
        }
        // if bid is smaller than current node then traverse left
        if (courseId.compare(current->course.courseId) < 0) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            // set current node equal to root
            current = current->right;
        }
    }

    Course course;
    return course;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        else {
            // recurse down the left node
            this->addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {

    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << node->course.courseId << ", " << node->course.courseName << endl;
        //InOder right
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    // FixMe (10): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output bidID, title, amount, fund
        cout << node->course.courseId << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    // FixMe (11): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        cout << node->course.courseId << endl;
        //postOrder left
        postOrder(node->left);
        //postOrder right  
        postOrder(node->right);
    }
}
ifstream& operator>> (ifstream& is, Course& course)
{
    is >> course.courseId >> course.courseName;
    return is;
}



void loadfile(BinarySearchTree* targetTree, string targetFile) {
    ifstream dataFile;
    streampos fileStart;
    string line;
    string compareString;
    stringstream lineBuffer;
    int lineCount = 0;
    bool validLine = true;
    bool courseExists;
    string courseNum;
    string courseName;
    Course* newCourse = nullptr;
    vector<string> courses;
    const char DELIMITER = ',';


    //opens file
    dataFile.open(targetFile);

    fileStart = dataFile.rdbuf()->pubseekoff(0, dataFile.beg, dataFile.in);

    getline(dataFile, line);

    dataFile.rdbuf()->pubseekpos(3, dataFile.in);
    dataFile.rdbuf()->pubseekpos(0, dataFile.in);

    fileStart = dataFile.tellg();

    // Get all course numbers
    while (!dataFile.eof()) {
        getline(dataFile, line, DELIMITER);
        courses.push_back(line);
        getline(dataFile, line);
    }

    dataFile.seekg(fileStart);

    while (validLine && dataFile.good()) {
        ++lineCount;

        lineBuffer.clear();
        lineBuffer.sync();
        line.clear();

        getline(dataFile, line);
        lineBuffer.str(line);

        getline(lineBuffer, courseNum, DELIMITER);

        if (lineBuffer.good()) {
            getline(lineBuffer, courseName, DELIMITER);
            newCourse = new Course();
            newCourse->courseId = courseNum;
            newCourse->courseName = courseName;
        }
        else {
            validLine = false;
        }

        while (validLine && !lineBuffer.eof()) {
            getline(lineBuffer, courseNum, DELIMITER);

            courseExists = false;
            for (auto it = courses.begin(); !(it == courses.end() || courseExists); ++it) {
                if (courseNum.compare(*it) == 0) {
                    newCourse->prerequisites.push_back(courseNum);
                    courseExists = true;
                }
            }
            validLine = courseExists;
        }

        if (validLine) {
            targetTree->Insert(*newCourse);
        }
    }
    cout << "file loaded" << endl;

    dataFile.close();
}
void loadMenu() {
    cout << "Welcome to the course planner" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl;
}
int main()
{
    int command;
    
    string userInput;
    string userInput_B;
    string defaultFile = "ABCU_Advising_Program_Input.txt";
    BinarySearchTree* tree = nullptr;
    Course course;
    loadMenu();
    while (true) {
        getline(cin, userInput);
        command = stoi(userInput);
        switch (command) {
        case 1:
            tree = new BinarySearchTree();
            loadfile(tree, defaultFile);
            loadMenu();
            break;
        case 2:
            cout << "Here is a sample Schedule" << endl;
            tree->InOrder();
            loadMenu();
            break;
        case 3:
            
            cout << "What course do you want to know about?" << endl;
            getline(cin, userInput_B);

            tree->Search(userInput_B);

            loadMenu();
            break;
        case 9:
            return 0;
        default:
            cout <<userInput <<  " is not a valid option." << endl;
            loadMenu();
            break;
        }
    }
    
    cout << "ending" << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
