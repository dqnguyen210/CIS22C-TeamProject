/*
Team Class
*/

#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED

#include <string>

using namespace std;

class Team
{
private:
    string TeamName;
    string City;
    string HomeCourt;
    int Players;
    string Coach;
    string Owner;
    int Championships;


public:
    Team(){TeamName = ""; City ="";Players = 0; HomeCourt = ""; Coach = ""; Owner = ""; Championships = 0;};
    Team(string n, string city,int play,string court,string c,string o,int num) {TeamName = n; City =city;Players = play; HomeCourt = court; Coach = c; Owner = o; Championships = num;};
    ~Team() {}
    void setTeamName(string s){TeamName = s;}
    void setCity(string s) {City = s;}
    void setPlayers(int num) {Players = num;}
    void setHomeCourt(string court) {HomeCourt = court;}
    void setCoach(string s) {Coach = s;}
    void setOwner(string s){Owner = s;}
    void setChampionships(int c) {Championships=c;}

	string getTeamName() const {return TeamName;}
	string getCity() const {return City;}
	int getPlayers() const {return Players;}
	string getHomeCourt() const {return HomeCourt;}
	string getCoach() const {return Coach;}
	string getOwner() const {return Owner;}
	int getChampionships() const {return Championships;}

	void compareChampionship(const Team &a) 
	{
		if (this->Championships < a.Championships)
			cout << this->TeamName << " has won fewer championships than " << a.TeamName << endl;
		if (this->Championships = a.Championships)
			cout << this->TeamName << " has won equal championships with " << a.TeamName << endl;
		if (this->Championships > a.Championships)
			cout << this->TeamName << " has won more championships than " << a.TeamName << endl;
	}

	bool operator >(const Team &a) {return (TeamName > a.TeamName);}
    bool operator >=(const Team &a) {return (City > a.City);}
    bool operator <(const Team &a) {return (TeamName < a.TeamName);}
    bool operator <=(const Team &a) {return (City < a.City);}
    bool operator ==(const Team &a) {return (TeamName == a.TeamName);}
    bool operator !=(const Team &a) {return (City == a.City);}
    Team& operator =(const Team &a)
    {
        TeamName = a.TeamName;
        City = a.City;
        HomeCourt = a.HomeCourt;
        Players = a.Players;
        Coach = a.Coach;
        Owner = a.Owner;
        Championships = a.Championships;
        return *this;
    }
    bool operator % (Team& a)
	{
		if (a.getCity().find(this->getCity()) != string::npos)
			return true;
		else
			return false;
	}
};
#endif // TEAM_H_INCLUDED
