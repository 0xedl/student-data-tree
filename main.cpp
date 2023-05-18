// A LOT OF CODE/PSEUDOCODE WAS REFERENCED BY CLASS POWERPOINT SLIDES ON TREES AND BALANCED TREES.
// SOME CODE SNIPPETS WERE PULLED FROM PAST STEPIK QUESTIONS (MY OWN SOLUTIONS).
// CODE IS ALSO REFERENCED FROM (TA) ANDREW'S PROJECT 1 VIDEO AND SLIDES.
//

#include <iostream>
#include "AVL.h"

int main() {
    AVLTree t;

    int input;
    cin >> input;
    string line, name, ufid;
    bool found = true;

    for (int i = 0; i <= input; i++) {
        getline(cin, line);
        // get command line
        int index = line.find_first_of(' ');
        string command = line.substr(0, index);
        // parse out command line from string
        line = line.substr(index + 1);
        // find what command is typed
        if (command == "insert") {
            size_t pos = line.find('\"');
            size_t endPos = line.find('\"', pos + 1);
            found = true;
            if (pos == line.length() - 1 || endPos == -1) {
                name = "";
                ufid = "";
            } else {
                name = line.substr(pos + 1, endPos - pos - 1);
                index = line.find_last_of(' ');
                ufid = line.substr(index + 1);
            }
            if (t.ValidInfo(name, ufid))
                t.InsertNAMEID(name, ufid);
        } else if (command == "remove") {
            t.RemoveID(line);
            found = true;
        } else if (command == "search") {
            found = true;
            // search name
            if (line[0] == '"') {
                name = line.substr(1, line.size() - 2);
                t.SearchName(name);
            }
                // search ID
            else {
                t.SearchID(line);
            }
        } else if (command == "printInorder") {
            found = true;
            t.PrintInorder();
        } else if (command == "printPreorder") {
            found = true;
            t.PrintPreorder();
            cout << endl;
        } else if (command == "printPostorder") {
            found = true;
            t.PrintPostorder();
        } else if (command == "printLevelCount") {
            found = true;
            t.PrintLevelCount();
        } else if (command == "removeInorder") {
            found = true;
            try {
                t.RemoveInorderN(stoi(line));
            }
            catch (std::exception) {
                cout << "unsuccessful\n";
            }
        }
        if (!found)
            cout << "unsuccessful\n";

        found = false;
    }
    return 0;
}