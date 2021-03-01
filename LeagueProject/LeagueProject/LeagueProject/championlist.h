#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <iostream>

struct counter
{
	std::string m_counterName;
	float percent;
};

class Champion {

	

public:

	std::vector<counter> m_countersArray;
	std::string ChampionName;
	void ProcessChampionHTML(std::string htmlFile);
	Champion();
	~Champion();
	void Reset();

};


class ChampionList {

	std::vector<std::string> m_championVector;
	std::ifstream fin;
	std::vector<std::string> m_databaseVector;


public:

	ChampionList(std::string filename);
	~ChampionList();
	std::vector<std::string> GetChampionList();
	std::vector<Champion> AllChampionObjects;
	std::vector<std::string> Find_All_Files(std::string Path);
	bool Check_In_Database(std::string champInput);

};





