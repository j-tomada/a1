#include <iostream>
#include <fstream>
#include <string>
#define NUMOFCHARS 27

using namespace std;

class dictNode {
    public:
        dictNode () {
            isWord = false;
        }
        void setIsWord (const bool &boolVal) {
            isWord = boolVal;
        }
        bool getBool (){
            return isWord;
        }
    private:
        bool isWord;
        dictNode *next[NUMOFCHARS];
};

class dictTree {
    public:
        dictTree () {
            startingNode = new dictNode();
        }
    private:
        dictNode *startingNode;

        void createTree () {

        }
}

int main () {
    dictNode *testNode = new dictNode();
    delete testNode;

    return 0;
}