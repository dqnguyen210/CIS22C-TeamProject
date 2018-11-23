// Hashing header file: use for hash table data structure
// Hash is used in this project to search and delete by primary key
// Written by Quynh Nguyen


# ifndef HASHING_H
# define HASHING_H

# include <string>
# include <iostream>
# include "team.h"
using namespace std;

enum Status {EMPTY, DELETED, TAKEN};
struct Node
{
    Status status;
    Team *object;
};
class Hash
{
private:
    Node* Hashtable; //points to an array of Nodes, where each Node
    //contains status and a pointer to a Team object
    int SIZE = 65;
    int loadfactor;
    int collision;

public:
    Hash();
    unsigned int hashing(string);
    unsigned int badHashing(string);
    void insert(Team *);
    Team* search(string, int &);
    void setsize(int s){SIZE = s;}
    int getSize() { return SIZE; }
    double getLoadFactor() { return (double)loadfactor / SIZE * 100;}
    int getCollision() { return collision;}
    bool Delete(string);
    void reHash();
    ~Hash();
};


// constructor
Hash::Hash()
{
    loadfactor = 0;
    collision = 0;

    // Dynamically allocated an array of Node for hash table
    Hashtable = new Node[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        Hashtable[i].status = EMPTY;
        Hashtable[i].object = nullptr;
    }
}

// hash function convert every string into
// a unique number and return that number for
// other purpose
//**********************************************
unsigned int Hash::hashing(string str)
{
    int primes[] = { 233, 389, 521, 163, 379, 167, 503, 83, 37, 13 };  // size is 10, large enough
    unsigned int sum = 0;
    int strLength = str.length();

    for (int i = 0; i < strLength; i++)
    {
        sum += primes[((int)str.at(i)) % 10] * primes[i % 10] * primes[i % 10];
    }

    sum = sum % SIZE;
    return sum;
}

unsigned int Hash::badHashing(string str)
{
    unsigned int sum = 0;
    int strLength = str.length();

    for (int i = 0; i < strLength; i++)
    {
        sum += (int)str.at(i);
    }

    sum = sum % SIZE;
    return sum;
}

// insert functions add new item to Hashtable
// reHash is called if loadfactor > 75%
//**********************************************
void Hash::insert(Team *team)
{
    int addr = hashing(team->getTeamName());
    int newAddr = 0;
    int count = 1;
    bool found = false;

    if (Hashtable[addr].status != TAKEN)    //if the node is not taken
    {
        Hashtable[addr].object = team;     //insert object in that node
        Hashtable[addr].status = TAKEN;
        loadfactor++;
    }
    else
    {
        while (!found && count < SIZE)
        {
            collision++;
            if (addr >= count)
            {
                if (count % 2 == 1)
                {
                    addr += count;
                }
                else
                    addr -= count;
            }
            else
                addr += count;
            count++;
            newAddr = addr % SIZE;
            if (Hashtable[newAddr].status != TAKEN)
            {
                found = true;
                Hashtable[newAddr].object = team;
                Hashtable[newAddr].status = TAKEN;
                loadfactor++;
            }
        }
    }
    if (getLoadFactor() >= 75)
        reHash();
}

// search function searches for a target and
// return the pointer to that target's object
//**********************************************
Team* Hash::search(string search_key, int &index)
{
    int addr = hashing(search_key);
    int count = 0;
    int newAddr = 0;
    bool found = false;

    if (Hashtable[addr].status != EMPTY)
    {
        while (!found && count < SIZE)
        {
            if (addr >= count)
            {
                if (count % 2 == 1)
                {
                    addr += count;
                }
                else
                    addr -= count;
            }
            else
                addr += count;
            count++;
            newAddr = addr % SIZE;
            if (Hashtable[newAddr].status == TAKEN && Hashtable[newAddr].object->getTeamName() == search_key)
            {
                found = true;
                index = newAddr;
                return Hashtable[newAddr].object;
            }
        }
    }
    return nullptr;
}

// Delete calls search function to search for target
// If found, remove the target
//**********************************************
bool Hash::Delete(string search_key)
{
    bool success = false;
    int index = -1;

    Team *target = search(search_key, index);
    if (target!= nullptr)
    {
        success = true;
        Hashtable[index].status = DELETED;
        Hashtable[index].object = nullptr;
    }
    return success;
}

// reHash function traverse the hash table and hash each
// item into the new table using the same hash function &
// collision resolution method, then delete the old hashtable
//***********************************************************
void Hash::reHash()
{
    Node* temp = Hashtable; //save save hashtable to a temp pointer
    Hashtable = new Node[SIZE * 2]; // Dynamically allocated an array for new hash table

    // Move data from old table to new table
    for (int i = 0; i < SIZE * 2; i++)
    {
        insert(temp[i].object);
    }
    delete [] temp; // Free the old Hash table
    temp = 0;
    SIZE *= 2;
}

//Destructor
Hash::~Hash()
{
    delete [] Hashtable;
}

# endif
