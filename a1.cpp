#include <iostream>
#include <fstream>
#include <string>
#define NUMOFCHARS 27

using namespace std;

class dictNode {
    public:
        bool isWord;
        dictNode *next[NUMOFCHARS];

        dictNode () {
            isWord = false;
        }
};

class dictTree {
    public:
        dictTree () {
            startingNode = new dictNode();
        }
        dictTree (fstream &dictFile) {
            startingNode = new dictNode();
            dictNode *currNode;
            string word;

            while (dictFile >> word) {
                currNode = startingNode;

                for (int i = 0; i < word.length(); ++i) {
                    const int charVal = int(tolower(word[i]));
                    const int nodeIndex = getCorrectVal(charVal);

                    if (nodeIndex == -1) {
                        cout << "There appears to be an error with the following word: " << word;
                        cout << " The program might be reading an different ASCII val than a-z" << endl;
                        return;
                    }
                    else {
                        if (currNode->next[nodeIndex] == NULL) {
                            currNode->next[nodeIndex] = new dictNode();
                        }
                        currNode = currNode->next[nodeIndex];
                    }
                }
                currNode->isWord = true;
            }
            delete currNode;
        }

        void findCount(fstream &testFile) {
            dictNode *currNode;
            string word;
            bool hasWord; //flagged true if we are able to reach the end

            while (testFile >> word) {
                currNode = startingNode;
                hasWord = true;
                int count = 0;

                for (int i = 0; i < word.length(); ++i) {
                    const int charVal = int(tolower(word[i]));
                    const int nodeIndex = getCorrectVal(charVal);

                    if (nodeIndex != -1) {
                        if (currNode->next[nodeIndex] == NULL) {
                            hasWord = false;
                            break;
                        }
                        else {
                            currNode = currNode->next[nodeIndex];
                        }
                    }
                }

                if (hasWord) {
                    findRemainingWords(currNode, count);
                }
                cout << word << " " << count << endl;

            }
            delete currNode;

        }
    private:
        dictNode *startingNode;

        int getCorrectVal(const int &charVal) {
            const int apDec = 39; //Decimal values for ', a, and z
            const int aDec = 97;
            const int zDec = 122;

            if (charVal == apDec) {
                return 26;
            }
            else if (charVal >= aDec && charVal <= zDec) {
                return charVal - aDec;
            }
            return -1;
        }

        void findRemainingWords(dictNode *currNode, int &count) {
            if (currNode->isWord) {
                ++count;
            }
            
            const int len = sizeof(currNode->next)/sizeof(currNode->next[0]);
            for (int i = 0; i < len; ++i) {
                if (currNode->next[i] != NULL) {
                    findRemainingWords(currNode->next[i], count);
                }
            }
        }
};

int main (int argc, char **argv) {
    if (argc != 3) {
        cout << "Help: ./a1 dictionarysource.txt testfile.txt" << endl;
    }
    else {
        fstream dictFile;
        
        dictFile.open(argv[1]);
        if(dictFile.is_open()) {
            dictTree *tree = new dictTree(dictFile);

            fstream testFile;

            testFile.open(argv[2]);
            if(dictFile.is_open()) {
                tree->findCount(testFile);
            }
            else {
                cout << "ERRROR: file " << argv[2] << " was not found " << endl;
            }
            delete tree;
            testFile.close();
        }
        else {
            cout << "ERROR: file " << argv[1] << " was not found" << endl;
        }
        dictFile.close();
    }

    return 0;
}