/*
main.cpp
contains menu features
programmed and modified by: So Yeon Wang and Xiaoran Mei
tested by: all members
*/

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <cmath>


//#include "team.h"
#include "Hashing.h"
#include "readFile.h"
#include "Stack.h"

void welcome();
void mainMenu();
void insertManager(BinarySearchTree<Team*>*, BinarySearchTree<Team*>*, Hash*);
void searchMenu(Hash*, BinarySearchTree<Team*>*, BinarySearchTree<Team*>*);
//void searchPrimary(Hash*);
void searchPrimary(Hash* teamHash);
void searchSecondary(BinarySearchTree<Team*>*);
void deleteMenu(BinarySearchTree<Team*>*, BinarySearchTree<Team*>*, Hash*);
void deleteManager(BinarySearchTree<Team*>*, BinarySearchTree<Team*>*, Hash*, Stack<Team*>*);
void undoDelete(BinarySearchTree<Team*>*, BinarySearchTree<Team*>*, Hash*, Stack<Team*>*);
bool saveFileManager(BinarySearchTree<Team*>*, Stack<Team*>*);
void printMenu(BinarySearchTree<Team*>*, BinarySearchTree<Team*>*);
void printList(BinarySearchTree<Team*>*, char);
void hashStatistics(Hash*);

/**
void saveToFile(Team*& team, ofstream& outputFile)
{
        outputFile << team->getTeamName() << ";" << team->getCity() << ";" << team->getHomeCourt() << ";" <<
        team->getPlayers() << ";" << team->getCoach() << ";" << team->getOwner() << ";" << team->getChampionships() << endl;
}*/

void displayIndented(Team*& team, int& level)
{
    int index = level / 4;
	cout<< right << setw(5 * level) << "#" << index <<" Name: " << team->getTeamName() << endl; // << "(" << node->getCode() << ")\n";
	cout<< right << setw(5 * level) << "-" << "> City: " << team->getCity() << endl;
	cout<< right << setw(5 * level) << "-" << "> Home Court: " << team->getHomeCourt() << "\n";
	cout<< right << setw(5 * level) << "-" << "> Players on Roster: " << team->getPlayers() << "\n";
	cout<< right << setw(5 * level) << "-" << "> Coach: " << team->getCoach() << "\n";
	cout<< right << setw(5 * level) << "-" << "> Owner: " << team->getOwner() << "\n";
    cout<< right << setw(5 * level) << "-" << "> Championships won: " << team->getChampionships() << endl;
}

void displayOne(Team*& team)
{
    cout << "<< " << team->getTeamName() << " >>\n"
         << "City: " << team->getCity()
         << "\nHome Court: " << team->getHomeCourt()
         << "\nPlayers on Roster: " << team->getPlayers()
         << "\nCoach: " << team->getCoach()
         << "\nOwner: " << team->getOwner()
         << "\nChampionships won: " << team->getChampionships() << endl << endl;
}

void displayInList(Team*& team)
{
    cout << "|" << left << setw(25) << team->getTeamName() << "|" << setw(19) << team->getCity() << "|" << setw(27) << team->getHomeCourt()
         << "|" << right << setw(7) << team->getPlayers() << "|" << left << setw(16) << team->getCoach()
         << "|" << setw(33) << team->getOwner() << "|" << right << setw(12) << team->getChampionships() << "|" << endl;
}

int main()
{
    welcome();
    BinarySearchTree<Team*>* nameTree = new BinarySearchTree<Team*>;
	BinarySearchTree<Team*>* cityTree = new BinarySearchTree<Team*>;
	Hash* teamHash = new Hash();
    char menu;
	readfile(nameTree, cityTree, teamHash);
    do
    {
        mainMenu();
        cout << "Select the menu: ";
        cin >> menu;
        menu = toupper(menu);
        switch (menu)
        {
            case 'A': insertManager(nameTree, cityTree, teamHash);
                break;
            case 'S': searchMenu(teamHash, cityTree, nameTree);
                break;
            case 'D': deleteMenu(nameTree, cityTree, teamHash);
                break;
            case 'P': printMenu(nameTree, cityTree);
                break;
            case 'T': hashStatistics(teamHash);
                break;
            case 'Q': cout << "Quit the Program.\n\n";
                break;
        }
    }while (menu != 'Q');

	savetofile(nameTree);
	cout << "Saved to file." << endl;

    delete teamHash;
}

void welcome()
{
    cout << "<<    CIS-22C Team Project    >>\n"
         << "Team Title: Basketball Team Database.\n"
         << "\nTeam members:\n"
         << "\tXiaoran Mei\n"
         << "\tKeano Zamora\n"
         << "\tDiep Quynh Nguyen\n"
         << "\tSoyeon Wang\n"
         << "\tBobby Nguyen" << endl << endl;

}
void mainMenu()
{
    cout << " _______________________________\n"
         << "|           Main Menu           |\n"
         << "|-------------------------------|\n"
         << "| A - Add Team                  |\n"
         << "| S - Search Team               |\n"
         << "| D - Delete Team               |\n"
         << "| P - Print Team                |\n"
         << "| T - Show Statistics of Hash   |\n"
         << "| Q - Quit                      |\n"
         << "|_______________________________|\n";


}

void insertManager(BinarySearchTree<Team*>* nameTree, BinarySearchTree<Team*>* cityTree, Hash* teamHash)
{
    Team* newTeam = new Team();
	string input, check;
    int index = -1;

    // Check and Insert Team Name
	bool valid = false;
	while (!valid)
	{
		cout << "Enter the Team Name: ";
		cin.ignore();
		getline(cin, input);
		if (!teamHash->search(input, index)) // check duplicate
        {
            valid = true;
            newTeam->setTeamName(input);
        }

		else
		{
			cout << " Error: Team with that name already exists!\n";
			
		}

		
	}

	//Insert City and Home Court
	cout << "Enter City: ";
	getline(cin, input);
	newTeam->setCity(input);
	cout << "Enter Home Court: ";
	getline(cin, input);
	newTeam->setHomeCourt(input);

	//Check and Insert the Number of Players
	valid = false;
	cout << "Enter the Number of Players: ";
    int a;
    cin >> a;
    newTeam->setPlayers(a);
/**	while (!valid)
    {
		getline(cin, input);
		try {
			newTeam->setPlayers(stoi(input)); //check if input is a number
			valid = true;
		}
		catch (invalid_argument e) {
			cout << "That is not a number. Please try again:";
		}
	}
*/
    //Insert Coach and Owner
	cout << "Enter Coach: ";
	cin.ignore();
	getline(cin, input);
	newTeam->setCoach(input);
    cout << "Enter Owner: ";
//    cin.ignore();
	getline(cin, input);
	newTeam->setOwner(input);

	//Check and Insert the Number of Championships
	valid = false;
	cout << "Enter the Number of Championships: ";
    cin >> a;
    newTeam->setChampionships(a);

/**	while (!valid)
    {
		getline(cin, input);
		try {
			newTeam->setChampionships(stoi(input)); //check if input is a number
			valid = true;
		}
		catch (invalid_argument e) {
			cout << "That is not a number. Please try again:";
		}
	}*/


	// Input data to tree and hash table
	nameTree->insert(newTeam, 1); // insert to BST Name
	cityTree->insert(newTeam, 2); // insert to BST Code
	teamHash->insert(newTeam); // insert to Hash Table

	cout << "Successfully Added!" << endl;
}

void searchMenu(Hash* teamHash, BinarySearchTree<Team*>* cityTree, BinarySearchTree<Team*>* nameTree)
{
    char menu;
    do
    {
        cout << " _______________________________\n"
             << "|          Search Menu          |\n"
             << "|-------------------------------|\n"
             << "| P - By Team Name              |\n"
             << "| S - By City                   |\n"
             << "| R - Return to Main Menu       |\n"
             << "|_______________________________|\n";

        cout << "Select the menu: ";
        cin >> menu;
        menu = toupper(menu);
        switch (menu)
        {
            case 'P': //searchPrimary(teamHash);
                        searchPrimary(teamHash);
                break;
            case 'S': searchSecondary(cityTree);
                break;
            case 'R': cout << "Return to the Main Menu.\n\n";
                break;
        }
    }while (menu != 'R');
}

// search primary by hash
void searchPrimary(Hash* teamHash)
{
    string searchName;
	Team* searchedTeam = nullptr;
    int index = -1;
	cout << "Enter the Team Name to be Searched: ";
	cin.ignore();
	getline(cin, searchName);

	searchedTeam = teamHash->search(searchName,index);//Search Code Hash
	if (searchedTeam != NULL)
		displayOne(searchedTeam);
	else
        cout << "ERROR: Team with the Name - " << searchName << " - Not Found..." << endl;
}


// search primary using BST
//void searchPrimary(BinarySearchTree<Team*>* nameTree)
//{
//    string searchName;
//	Team* searchedTeam = nullptr;
//	cout << "Enter the Name of Team to be Searched: ";
//	cin.ignore();
//	getline(cin, searchName);
//	Team* searching = new Team;
//	searching->setTeamName(searchName); // Search Name BST
//	if (nameTree->getEntry(searching, *&searchedTeam, 1, displayOne))
//        displayOne(searchedTeam);
//    else
// 		cout << "\nERROR: Team with Name - " << searchName << " - Not Found..." << endl;
//}

void searchSecondary(BinarySearchTree<Team*>* cityTree)
{
    string searchCity;
	Team* searchedTeam = nullptr;
	cout << "Enter the City of Team to be Searched: ";
	cin.ignore();
	getline(cin, searchCity);
	Team* searching = new Team;
	searching->setCity(searchCity); // Search Name BST
	if (!cityTree->getEntry(searching, *&searchedTeam, 2, displayOne))
 		cout << "\nERROR: Team with City - " << searchCity << " - Not Found..." << endl;
}


void deleteMenu(BinarySearchTree<Team*>* nameTree, BinarySearchTree<Team*>* cityTree, Hash* teamHash)
{
    char menu;
    Stack<Team*> undoStack;
    do
    {
    cout << " _______________________________\n"
         << "|          Delete Menu          |\n"
         << "|-------------------------------|\n"
         << "| D - Delete Team               |\n"
         << "| U - Undo Delete               |\n"
         << "| S - Save to file              |\n"
         << "| R - Return to Main Menu       |\n"
         << "|_______________________________|\n";

        cout << "Select the menu: ";
        cin >> menu;
        menu = toupper(menu);
        switch (menu)
        {
            case 'D': deleteManager(nameTree, cityTree, teamHash, &undoStack);
                break;
            case 'U': undoDelete(nameTree, cityTree, teamHash, &undoStack);
                break;
            case 'S': savetofile(nameTree);//if(saveFileManager(nameTree, &undoStack))
                      cout << "Save to File Successful!\n\n";
                break;
            case 'R': cout << "Return to the Main Menu.\n\n";
                break;
        }
    }while (menu != 'R');
}


void deleteManager(BinarySearchTree<Team*>* nameTree, BinarySearchTree<Team*>* cityTree, Hash* teamHash, Stack<Team*>* undoStack)
{
    string enteredName;
    Team* temp = new Team;
    Team* teamRemove;
//    int index;
	cout << "Enter Team Name to be Removed: ";
	cin.ignore();
	getline(cin, enteredName);
	temp->setTeamName(enteredName);
	nameTree->getEntry(temp, teamRemove, 1, displayOne);
	if (teamRemove != nullptr && nameTree->remove(teamRemove, 1) && cityTree->remove(teamRemove, 2) && teamHash->Delete(enteredName))
        cout << " \nDelete Successful!\n";
	else
		cout << " \nUnavailable data. Cannot Delete!\n";

    undoStack->push(teamRemove);


/**	Team* nameRemove = teamHash->search(enteredName, index);
	Team* cityRemove = nullptr;
	nameRemove->setTeamName(enteredName);
	nameTree->getEntry(nameRemove, cityRemove, 1, test);
	if (nameRemove != NULL&& cityRemove != NULL && cityTree->remove(cityRemove, 2) && nameTree->remove(nameRemove, 1) && teamHash->Delete(enteredName)) // Remove data from BST and Hash Table
		cout << " \nDetele Successful!\n";
	else
		cout << " \nUnavailable data. Cannot Delete!\n";*/

}

void undoDelete(BinarySearchTree<Team*>* nameTree, BinarySearchTree<Team*>* cityTree, Hash* teamHash, Stack<Team*>* undoStack)
{
    if(undoStack->isEmpty())
        cout << "No Team Left. Cannot Undo Delete!" << endl;
    else
    {
        Team* returnTeam = new Team;
        undoStack->pop(returnTeam);
        cout << "Undo Delete - " << returnTeam->getTeamName() << endl;
        nameTree->insert(returnTeam, 1); // insert to BST Name
        cityTree->insert(returnTeam, 2); // insert to BST Code
        teamHash->insert(returnTeam);
    }
}
/**
bool saveFileManager(BinarySearchTree<Team*>* nameTree, Stack<Team*>* undoStack)
{
    delete undoStack;
    ofstream outputFile("output file.txt");
    nameTree->printFile(saveToFile, outputFile);
    outputFile.close();
}
*/
void printMenu(BinarySearchTree<Team*>* nameTree, BinarySearchTree<Team*>* cityTree)
{
    char menu;
    do
    {
    cout << " _________________________________\n"
         << "|            Print Menu           |\n"
         << "|---------------------------------|\n"
         << "| U - Unsorted Data               |\n"
         << "| I - Indented Tree(Primary)      |\n"
         << "| N - Indented Tree(Secondary)    |\n"
         << "| P - Sorted by Team Name(Primary)|\n"
         << "| S - Sorted by City(Secondary)   |\n"
         << "| R - Return to Main Menu         |\n"
         << "|_________________________________|\n";

        cout << "Select the menu: ";
        cin >> menu;
        menu = toupper(menu);
        switch (menu)
        {
            case 'U': printList(nameTree, menu);
                break;
            case 'I': nameTree->indentList(displayIndented);
                break;
            case 'N': cityTree->indentList(displayIndented);
                break;
            case 'P': printList(nameTree, menu);
                break;
            case 'S': printList(cityTree, menu);
                break;
            case 'R': cout << "Return to the Main Menu.\n\n";
                break;
        }
    }while (menu != 'R');
}

void printList(BinarySearchTree<Team*>* treePtr, char menu)
{
    cout << " _________________________________________________________________________________________________________________________________________________\n"
         << "|                                                                 Basketball Team                                                                 |\n"
         << "|=================================================================================================================================================|\n"
         << "|" << left << setw(25) << "Name" << setw(20) << "|City" << setw(28) << "|Home court" << setw(8) << "|Players"
         << setw(17) << "|Coach" << setw(34) << "|Owner" << setw(15) << "|Championship|\n"
         << "|-------------------------------------------------------------------------------------------------------------------------------------------------|\n";
    if(menu == 'U')
        treePtr->breadthFirst(displayInList);
    else if (menu == 'P')
        treePtr->inOrder(displayInList);
    else if (menu == 'S')
        treePtr->inOrder(displayInList);
    cout << "|_________________________|___________________|___________________________|_______|________________|_________________________________|____________|\n";
}

void hashStatistics(Hash* hash)
{
	cout << "~*~*    Statistics    *~*~" << endl
		<< "Collisions: " << hash->getCollision() << endl
		<< "Default Bucket Size: " << hash->getSize() << endl
		<< "Load Factor: " << hash->getLoadFactor() << endl;
}
