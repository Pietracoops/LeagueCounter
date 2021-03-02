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
	std::vector<int> m_position_array;
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

	std::vector<Champion> AllChampionObjects;

	ChampionList(std::string filename);
	~ChampionList();

	std::vector<std::string> GetChampionList();
	std::vector<std::string> Find_All_Files(std::string Path);

	void ChampionListPositions(std::string filename);
	bool Check_In_Database(std::string champInput);

};





