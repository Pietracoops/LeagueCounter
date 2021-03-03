#pragma once
#include "championlist.h"

class Team {




public:
	Champion Mid;
	Champion Top;
	Champion Jungler;
	Champion ADC;
	Champion Support;

	std::vector<std::string> TeamPicksStr;
	std::vector<Champion> TeamPicks;
	Team();
	~Team();

};



class MatchupCalculator {

	std::vector<Champion> m_championArchive;

	std::vector<int> CounterScores;
	int score = 0;

	Champion tmpChamp;
	std::vector<Champion> CounterChampsMid;
	std::vector<Champion> CounterChampsTop;
	std::vector<Champion> CounterChampsJungler;
	std::vector<Champion> CounterChampsADC;
	std::vector<Champion> CounterChampsSupport;

	std::vector<int> weightsMidLane		= { 0,1,4,2,4 };
	std::vector<int> weightsTopLane		= { 1,0,4,2,4 };
	std::vector<int> weightsJunglerLane = { 3,1,0,3,4 };
	std::vector<int> weightsADCLane		= { 1,3,4,0,2 };
	std::vector<int> weightsSupportLane = { 2,3,4,3,0 };

	std::vector<float> Percentages;

	int minElementIndex;

	bool FindChampionObject(std::string InputChampionName, Champion& OutputChampion);
	int FindCounter(Champion& InputChampionName, Champion& CompareChampion);
	int PositionWeights(Champion& InputChampion, std::vector<int> weights);


public:
	Team InputTeam;
	Team OutputTeam;
	float WinPercent = 0;

	MatchupCalculator(std::vector<Champion> InputAllChampionObjects);
	~MatchupCalculator();

	void ComputeOutputTeam();
	void ComputeCounterChamp();
	void ComputeWinPercent();


};