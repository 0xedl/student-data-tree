//
// Created by Ed Lang on 2/19/23.
//

#include "AVL.h"


Node *AVLTree::InsertHelper(Node *node, const string &name, const string &ufid) {

    if (node == nullptr) {
        cout << "successful\n";
        return new Node(name, ufid);
    }
    // Check for Unique and Insertion
    if (ufid < node->ufid)
        node->left = InsertHelper(node->left, name, ufid);
    else if (ufid > node->ufid)
        node->right = InsertHelper(node->right, name, ufid);
    else { // Not Unique UFIDa
        cout << "unsuccessful\n";
        return node;
    }

    // Set height
    SetHeight(node);

    // Check Balance
    int balance = GetBalanceFactor(node);
    // Left Left Case
    if (balance > 1 && ufid < node->left->ufid)
        return RotateRight(node);

    // Right Right Case
    if (balance < -1 && ufid > node->right->ufid)
        return RotateLeft(node);

    // Left Right Case
    if (balance > 1 && ufid > node->left->ufid) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && ufid < node->right->ufid) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    return node;
}

Node *AVLTree::RotateLeft(Node *node) {
    Node *gc = node->right->left;
    Node *np = node->right;
    np->left = node;
    node->right = gc;
    // Update heights
    SetHeight(node);
    SetHeight(np);
    // Return new root
    return np;
}

Node *AVLTree::RotateRight(Node *node) {
    Node *gc = node->left->right;
    Node *np = node->left;
    np->right = node;
    node->left = gc;

    // Update heights
    SetHeight(node);
    SetHeight(np);
    // Return new root
    return np;
}

/*TODO: fix these if there's time
Node *AVLTree::RotateLeftRight(Node *node) { // ONLY WORKS WHEN NOT IN ITS OWN FUNCTION?? THINK IT HAS SOMETHING TO DOW/ RETURN NODE->LEFT
    node->left = RotateLeft(node->left);
    return RotateRight(node);
}

Node *AVLTree::RotateRightLeft(Node *node) { // ONLY WORKS WHEN NOT IN ITS OWN FUNCTION?? THINK IT HAS SOMETHING TO DOW/ RETURN NODE->RIGHT
    node->right = RotateRight(node->right);
    return RotateLeft(node);
}
*/// TODO: end todo

int AVLTree::GetHeight(Node *node) {
    if (node == nullptr) return 0;
    return node->height;
}

void AVLTree::SetHeight(Node *node) {
    if (node == nullptr)
        return;
    node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

int AVLTree::GetBalanceFactor(Node *node) {
    return GetHeight(node->left) - GetHeight(node->right);
}

Node *AVLTree::RemoveHelper(Node *node, const string &ufid) {
    // Base case: tree is empty
    if (node == nullptr) {
        cout << "unsuccessful\n";
        return node;
    }

    // Compare the UFID of the node to be removed with the UFID of the current node
    if (ufid < node->ufid) {
        node->left = RemoveHelper(node->left, ufid);
    } else if (ufid > node->ufid) {
        node->right = RemoveHelper(node->right, ufid);
    } else { // Node Found
        // Case 1: Node has no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
            // Case 2: Node has one child
        else if (node->left == nullptr) {
            Node *temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node *temp = node;
            node = node->left;
            delete temp;
        }

            // Case 3: Node has two children
        else {
            Node *successor = FindSuccessor(node->right);
            node->name = successor->name;
            node->ufid = successor->ufid;
            node->right = RemoveHelper(node->right, successor->ufid);
        }

        flag = true;
        SetHeight(node);
    }
    return node;
}

Node *AVLTree::FindSuccessor(Node *node) { // find successor to replace removed node
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void AVLTree::SearchIDHelper(Node *node, const string &ufid) {
// Base Case: Not Found
    if (node == nullptr) {
        cout << "unsuccessful\n";
        return;
    }
    // Found it!!!
    if (node->ufid == ufid) {
        cout << node->name << endl;
        return;
    }

    if (node->ufid > ufid)
        SearchIDHelper(node->left, ufid);
    if (node->ufid < ufid)
        SearchIDHelper(node->right, ufid);
}

void AVLTree::SearchNameHelper(Node *node, const string &name) {
    if (node == nullptr) {
        return;
    }
    if (node->name == name) {
        cout << node->ufid << endl;
        flag = true; // variable in AVL to mark if found
    }

    SearchNameHelper(node->left, name);
    SearchNameHelper(node->right, name);
}

void AVLTree::PrintInOrderHelper(Node *node) {
    if (node == nullptr) return;
    vector<Node *> tree;
    FindInOrder(node, tree);
    for (int i = 0; i < tree.size(); i++) {
        cout << tree[i]->name;
        if (i < tree.size() - 1)
            cout << ", ";
    }
    cout << endl;

}

void AVLTree::PrintPreOrderHelper(Node *node) {
    if (node == nullptr) return;

    vector<Node *> tree;
    FindPreOrder(node, tree);
    for (int i = 0; i < tree.size(); i++) {
        cout << tree[i]->name;
        if (i < tree.size() - 1)
            cout << ", ";
    }
    cout << endl;
}

void AVLTree::PrintPostOrderHelper(Node *node) {
    if (node == nullptr) return;
    vector<Node *> tree;
    FindPostOrder(node, tree);
    for (int i = 0; i < tree.size(); i++) {
        cout << tree[i]->name;
        if (i < tree.size() - 1)
            cout << ", ";
    }
    cout << endl;
}

int AVLTree::PrintLevelCountHelper(Node *node) {
    if (node == nullptr) return 0;
    int l = PrintLevelCountHelper(node->left);
    int r = PrintLevelCountHelper(node->right);
    return l > r ? l + 1 : r + 1;
}

Node *AVLTree::RemoveInOrderNHelper(Node *node, int n) {
    if (node == nullptr) {
        cout << "unsuccessful\n";
        return node;
    }

    vector<Node *> tree;
    FindInOrder(node, tree);

    if (n < 0 || tree.size() < n){
        cout << "unsuccessful\n";
        return node;
    }

    if (tree[n] != nullptr) {
        cout << "successful\n";
        return RemoveHelper(node, tree[n]->ufid);
    } else cout << "unsuccessful\n";
    return node;
}

void AVLTree::FindInOrder(Node *node, vector<Node *> &tree) {
    if (node == nullptr)
        return;

    FindInOrder(node->left, tree);
    tree.push_back(node);
    FindInOrder(node->right, tree);
}

void AVLTree::FindPreOrder(Node *node, vector<Node *> &tree) {

    if (node == nullptr)return;
    tree.push_back(node);
    FindPreOrder(node->left, tree);
    FindPreOrder(node->right, tree);
}

void AVLTree::FindPostOrder(Node *node, vector<Node *> &tree) {
    if (node == nullptr) return;
    FindPostOrder(node->left, tree);
    FindPostOrder(node->right, tree);
    tree.push_back(node);
}

bool AVLTree::ValidInfo(const string &name, const string &ufid) {

    std::regex id_comp = regex("[0-9]{8}?"); // ufid
    std::regex n_comp("^(?=.*[a-zA-Z])[a-zA-Z ]+$");

    if (regex_match(ufid, id_comp) && regex_match(name, n_comp)) // compare both
        return true;

    cout << "unsuccessful\n";
    return false;
}