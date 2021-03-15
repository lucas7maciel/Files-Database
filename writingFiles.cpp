#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

class Central {
    public:
        string addString, fileName,line, listName, reW;
        int alter, countLine;

    string getFileName () {
        //This method receives the name of the file to be edited, if you type 'create', a new file will be created
        cin >> fileName;

        if (fileName == "create") {
            cout << "Type the name of the new file:";
            cin.ignore(); cin >> fileName;
            ofstream oFile;
            oFile.open(fileName + ".txt");

            //Now the new file will be added to 'fileList.txt'
            ofstream oLister (listName, ios_base :: app | ios_base :: out);
            oLister << ", " + fileName << " ";

        } else if (fileName == "close") { return "close"; }

        fileName += ".txt";

        ifstream iFile(fileName);

        if (iFile.is_open()){ return "C:/GOG Games/" + fileName; }
        else { cout << "\nThis file does not exist\n"; pressToCon();}

        return "";
    }

    void fileList() {
        //This method will checks if 'fileList.txt' exists
        listName = "fileList.txt";
        fstream Lister(listName);
        if (!Lister.good()) {
            ofstream oLister (listName, ios_base :: app | ios_base :: out);
            oLister << "Files:";
        }

        //And then print it
        ifstream iLister(listName);
        getline(iLister, line);
        if (line.find(",", 0) == 6) { line.erase (6,2); }
        cout << line << "\n";
    }

    void pressToCon() {
        cout << "\nPress any key to continue\n";
        getch();
        system("cls");
    }

    void printFile() {
        ifstream iFile(fileName);

        cout << fileName + "\n\n";
        while ( getline (iFile, line)) { cout << line << "\n"; }
    }

    void add() {
        //The method instantiates the output object and adds a line to the current file
        ofstream file (fileName, ios_base :: app | ios_base :: out);
        printFile();

        cout << "\nType the line you want to add:";
        cin.ignore(); getline(cin, addString);
        file << addString + "\n";
        system("cls");
    }

    void alterLine() {
        //First, we print the lines from the file with their numbers on the side
        while (0 != 1) {
            ifstream iFile(fileName);
            countLine = 1;

            cout << fileName << "\n\n";
            while ( getline (iFile, line)){
                cout << countLine << "  " << line << "\n";
                countLine++;
            }
                cout << "\nType the number of the line you want to alter:";
                cin >> alter;
                if (alter < countLine && alter >= 1) {
                    break;
                } else { system("cls"); }
            }

        //The file will be read again with each line being stored in 'reW', and the alter line will be repositioned
        ifstream iiFile(fileName);
        countLine = 1;
        reW = "";

        while ( getline (iiFile, line)){
            if (countLine == alter) {
                cout << "Type the new line:";
                cin.ignore(); getline(cin, line);
                system("cls");
            }
            countLine++;
            reW += line + "\n";
        }

        //Then, we create an output with the trunc parameter, which will restart the file content, and add 'reW'
        ofstream oFile;
        oFile.open(fileName, ofstream::out | ofstream::trunc);

        oFile << reW;
        cout << fileName << "\n\n" << reW;
        pressToCon();
    }

    void deleteFile() {
        if (fileName == "fileList.txt") {
            cout << "You cannot delete 'fileList'";
            pressToCon();
        }   else {
            char nf[fileName.size()];

            for (int x = 0; x < fileName.size(); x++) {
                    nf[x] = fileName.at(x);
            } //Loop used to copy fileName into a char

            remove(nf);

            //These lines remove the name of the file from 'fileList'
            ifstream iLister(listName);
            getline(iLister, line);

            fileName = fileName.substr(0, fileName.size()-4);
            fileName = ", " + fileName + " ";
            int pos = line.find(fileName);
            int len = fileName.length();
            line.replace(pos, len, "");

            ofstream oLister;
            oLister.open(listName, ofstream::out | ofstream::trunc);
            oLister << line;

            cout << "File deleted";

            pressToCon();
            }
    }
};

int main() {
    string name, order;
    Central c;

    while (0 != 1) {
        c.fileList();
        cout << "Type the name of the file, 'create' or 'close':";
        name = c.getFileName();

        if (name == "close") {
            return 0;
        }

        //Loop used to edit the file, if name = "", the user entered a nonexistent folder
        while (name != "") {
            system("cls");
            cout << c.fileName << "\n\n" << "'read', 'add', 'alter', 'delete' or 'other':";
            cin >> order;
            system("cls");

            if (order == "read") { c.printFile(); c.pressToCon(); }

            else if (order == "add") { c.add(); c.printFile(); c.pressToCon();}

            else if (order == "alter") {c.alterLine();}

            else if (order == "other") { break; }

            else if (order == "delete") {
                c.deleteFile();
                break;
            }
        }
    }
}
