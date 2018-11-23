/**
/*File I/O BY Bobby  Nguyen , tested by all members
/* This file has calls a function to main to read a file and input that data into the HashTable and Binary Trees,
/* A function to output data stored in the binary tree to a .txt
*/

#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Hashing.h"
#include "BinarySearchTree.h"
/*
readfile is to be called in main to input data to Hashtable and two binary trees
*/
void readfile(BinarySearchTree<Team*>* BST,BinarySearchTree<Team*>* BST2,Hash* HST)
{
    string name;			//holds variables
	string city;
	int players;
	string court;
	string coach;
	string owner;
	int championships;

    ifstream fin;
    string fname;
    string punct;
    int count =0;
    int size;
	fin.open("input file.txt");

	while (!fin)							// check for file open success or prompt for filename
	{
		cout << "Error opening "<<fname<< "file."<<endl<<"Enter filename: ";
		cin >> fname;
		fname += ".txt";
        fin.open(fname.c_str());
	}
	while (getline(fin, punct,'\n'))
        count++;	//count the number of lines in input file

	size = count * 2 + 1;
    HST->setsize(size); // sets the size of hashtable based on size of lines of data
	fin.clear();								//reset point to beginning of file
	fin.seekg(0, fin.beg);
	getline(fin,name, ';');
    while (!fin.eof())
	{
        if(name != "\n")
		{
			if (name[0] == '\n')
				name.erase(0,1);
			getline(fin, city, ';');
			getline(fin,court,';');
			fin >> players; fin.get();
			getline(fin,coach,';');
			getline(fin,owner,';');
			fin >> championships;
												//calls to insert
			Team* data = new Team(name,city,players,court,coach,owner,championships);
//			Team* returned = new Team();
			HST->insert(data);
			BST->insert(data, 1);
            BST2->insert(data, 2);
            getline(fin,name, ';');
		}
    }
    fin.close();

}

static ofstream saveFile; // declare output file
/*
    print function to be pass into savetofile
*/
void save(Team*& node)
{
    saveFile << node->getTeamName() << ";" << node->getCity() << ";" << node->getPlayers() << ";"<< node->getHomeCourt() << ";" << node->getCoach()<< ";"
			 << node->getOwner()<< ";"<< node->getChampionships()<< ";"<<  endl;
}
/*
open a output.txt file to print data in breadthfirst order into a output file
*/
void savetofile(BinarySearchTree<Team*>* CodeTree)
{
    saveFile.open("output.txt");
	CodeTree->breadthFirst(save);
	saveFile.close();
}
#endif // READFILE_H_INCLUDED
