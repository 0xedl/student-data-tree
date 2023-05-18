//
// Created by Ed Lang on 2/19/23.
//

#pragma once

#include <iostream>
#include<stack>
#include<vector>
#include <regex>

using namespace std;

// STUDENT OBJECT
struct Node {

    string name;
    string ufid;
    int height;
    Node *left;
    Node *right;

    Node(string n, string id) : name(n), ufid(id), height(1), left(nullptr), right(nullptr) {} // constructor
};

class AVLTree {

    bool flag = false; // for search name success && remove success

    //Insert and Deletion
    Node *InsertHelper(Node *node, const string &name, const string &ufid); // Insert
    Node *RemoveHelper(Node *node, const string &ufid); // Remove node based on ufid
    Node *RemoveInOrderNHelper(Node *node, int n); // Remove Nth Node In order traversal
    Node *FindSuccessor(Node *node); // To assist with removing node w/ 2 children - finds successor

    // Rotation, Balance, Heights
    Node *RotateLeft(Node *node); // Left Rotate - Right Right Case
    Node *RotateRight(Node *node); // Right Rotate - Left Left Case
    int GetHeight(Node *node); // Get Height
    void SetHeight(Node *node); // Set Height
    int GetBalanceFactor(Node *node); // Get Balance Factor

    // Searches
    void SearchIDHelper(Node *node, const string &ufid); // Search ID
    void SearchNameHelper(Node *node, const string &name); // Search ID

    //Traversal Helpers to print using vectors
    void FindInOrder(Node *node, vector<Node *> &tree); // Inorder traversal, add to a vector
    void FindPreOrder(Node *node, vector<Node *> &tree);

    void FindPostOrder(Node *node, vector<Node *> &tree);

    // Traversal and Prints
    void PrintInOrderHelper(Node *node); // In order
    void PrintPreOrderHelper(Node *node); // Pre order
    void PrintPostOrderHelper(Node *node); // Post order
    int PrintLevelCountHelper(Node *node); // Level Count

    // TODO: SOMETHING WRONG WITH THESE FUNCTIONS, RETURN TYPE ISSUE MAYBE - TAKE A LOOK IF THERE'S TIME LEFT.
    // Node* RotateLeftRight(Node* node); // Left-Right Rotate - Left Right Case
    // Node* RotateRightLeft(Node* node); // Right-Left Rotate - Right Left Case

public:

    Node *root;

    void InsertNAMEID(const string &name, const string &ufid) { this->root = InsertHelper(this->root, name, ufid); }

    void RemoveID(const string &ufid) {
        this->root = RemoveHelper(this->root, ufid);
        if (flag)
            cout << "successful\n";
        flag = false;
    }

    void RemoveInorderN(int n) {this->root = RemoveInOrderNHelper(this->root, n); }

    void SearchID(const string &ufid) { SearchIDHelper(this->root, ufid); }

    void SearchName(const string &name) { // Search Name and Set flag back to false after complete.
        SearchNameHelper(this->root, name);
        if (!flag) cout << "unsuccessful\n";
        flag = false;
    }

    void PrintInorder() { PrintInOrderHelper(this->root); }

    void PrintPreorder() { PrintPreOrderHelper(this->root); }

    void PrintPostorder() { PrintPostOrderHelper(this->root); }

    void PrintLevelCount() { cout << PrintLevelCountHelper(this->root) << endl; }

    // Name & UFID Check
    bool ValidInfo(const string &name, const string &ufid); // Validate Name && UFID

    AVLTree() : root() {};
};
