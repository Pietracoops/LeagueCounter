#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <iostream>
#include <exception>
#include "webscrape.h"

struct counter
{
	std::string m_counterName;
	float percent;
};

class Champion {

	

public:
	std::string ChampionName;
	std::vector<int> m_position_array;
	std::vector<counter> m_countersArray;
	
	int Wins;
	int Losses;
	int GamesPlayed;
	float WinRatio;
	//KDA
	float Kills;
	float Deaths;
	float Assists;

	int Gold;
	float CS;
	int MaxKills;
	int MaxDeaths;
	int AverageDamageDealt;
	int AverageDamageTaken;

	int DoubleKills;
	int TripleKills;
	int QuadraKills;
	int PentaKills;


	
	void ProcessChampionHTML(std::string htmlFile);
	Champion();
	~Champion();
	void Reset();

};


class ChampionList {

	std::vector<std::string> m_championVector;
	std::ifstream fin;
	std::vector<std::string> m_databaseVector;

	std::vector<std::string> Clist;

public:

	std::vector<Champion> AllChampionObjects;

	ChampionList(std::string filename);
	~ChampionList();

	std::vector<std::string> GetChampionList();
	std::vector<std::string> Find_All_Files(std::string Path);

	void ChampionListPositions(std::string filename);
	void ChampionTierListImport(std::string filename);
	bool Check_In_Database(std::string champInput);
	void Initialization();

};





