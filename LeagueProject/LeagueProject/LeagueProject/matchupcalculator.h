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

	int minElementIndex;

public:
	Team InputTeam;
	Team OutputTeam;

	MatchupCalculator(std::vector<Champion> InputAllChampionObjects);
	~MatchupCalculator();

	void ComputeOutputTeam();

};