#include <iostream>
#include <fstream>
#include <cstdlib> // For atoi
#include <cstring>

using namespace std;

struct word
{
    bool solved;
    char theWord[50];
    string numbercodes[50];
    word()
    {
        solved = false;
        strcpy(theWord, "");
    }
};

class gameClass
{
    private:
        char words[3];
        string hints[50];
        string hintsAns[50];
        char input[50];
        word wordObj[50];
        string answer;
        word ansObj;
    public:
        void readPuzzleData()
        {
            fstream myfile("puzzledata.txt");
            if (myfile.is_open())
            {
                myfile.getline(words, 3); //2
                for (int i=0; i<atoi(words); i++)
                {
                    getline(myfile, hints[i]); //Complete, not divided
                    getline(myfile, hintsAns[i]); //whole
                    for (int j=0; j<hintsAns[i].length(); j++)
                        wordObj[i].theWord[j] = hintsAns[i][j];
                    myfile.getline(input, 50); //6 1 5 3 2
                    char *token = strtok(input, " ");
                    for (int j=0; token != NULL; j++)
                    {
                        wordObj[i].numbercodes[j] = token;
                        token = strtok(NULL, " ");
                    }
                }
                getline(myfile, answer);
                for (int j=0; j<answer.length(); j++)
                    ansObj.theWord[j] = answer[j];
                myfile.getline(input, 50);
                char *token = strtok(input, " ");
                for (int j=0; token != NULL; j++)
                {
                    ansObj.numbercodes[j] = token;
                    token = strtok(NULL, " ");
                }
                myfile.close();
            }
            else
            {
                cout << "Could not find puzzledata.txt" << endl;
                exit(EXIT_FAILURE);
            }
        }
        void printPuzzle()
        {
            cout << "The clues are: " << endl;
            cout << endl;
            for (int i=0; i<atoi(words); i++)
            {
                cout << hints[i] << endl;
                for (int j=0; wordObj[i].numbercodes[j] != ""; j++)
                {
                        cout << "__" << wordObj[i].numbercodes[j] << " ";
                }
                cout << endl << endl;
            }
            cout << endl;
            for (int j=0; ansObj.numbercodes[j] != ""; j++)
                cout << "__" << ansObj.numbercodes[j] << " ";

            cout << endl << endl;
        }
        bool checkWord(string input)
        {
            for (int i=0; i<atoi(words); i++)
            {
                if (hintsAns[i] == input)
                {
                    wordObj[i].solved = true;
                    return true;
                }
            }
            return false;
        }
        void printProgress()
        {
            cout << endl;
            for (int i=0; i<atoi(words); i++)
            {
                if (wordObj[i].solved == false)
                {
                    cout << hints[i] << endl;
                    for (int j=0; wordObj[i].numbercodes[j] != ""; j++)
                        cout << "__" << wordObj[i].numbercodes[j] << " ";
                    cout << endl << endl;
                }
            }
            for (int j=0; j<strlen(ansObj.theWord); j++)
            {
                for (int k=0; k<atoi(words); k++)
                {
                    for (int l=0; l<strlen(wordObj[k].theWord); l++)
                    {
                        if (ansObj.numbercodes[j] == wordObj[k].numbercodes[l])
                        {
                            if (wordObj[k].solved == true)
                                cout << ansObj.theWord[j] << " ";
                            else
                                cout << "__ ";
                        }
                    }
                }
            }
            cout << endl;
        }
        void victoryCheck()
        {
            bool allWon = true;
            for (int i=0; i<atoi(words); i++)
            {
                if (wordObj[i].solved == false)
                    allWon = false;
            }
            if (allWon == true)
            {
                cout << "Congratualations, you've solved the puzzle!" << endl;
                exit(0);
            }
        }
};

int main()
{
	gameClass newgame;
	newgame.readPuzzleData();
	newgame.printPuzzle();
	string input;
	cout << "You have 8 guesses." << endl;
	for (int i=8; i>0; i--)
    {
        cout << "Please enter a guess: ";
        cin >> input;
        if (newgame.checkWord(input) == true)
        {
            cout << "That's correct!" << endl;
            newgame.printProgress();
            newgame.victoryCheck();
        }
        else
            cout << "Sorry that is not an answer." << endl;
        cout << endl;
        cout << "You have " << i-1 << " more guesses." << endl;
    }
    cout << "You could not solve the puzzle!" << endl;
    return 0;
}
