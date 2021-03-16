#pragma once
#include "championlist.h"
#include "playerstats.h"
#include <algorithm>




class ClashTeam {




public:
	std::vector<Champion> TopBans;
	std::vector<Champion> JunglerBans;
	std::vector<Champion> MidBans;
	std::vector<Champion> ADCBans;
	std::vector<Champion> SupportBans;
	std::vector<Player> TeamPlayers;

};



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

	std::vector<std::vector<int>> CounterScores;
	std::vector<int> CounterScoresCouple;	//score | index
	int score = 0;

	std::vector<std::vector<int>> InputChampPositionScores;

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

	bool FindMidCounter();
	bool FindTopCounter();
	bool FindJunglerCounter();
	bool FindADCCounter();
	bool FindSupportCounter();

	Champion CheckDuplicates(std::vector<Champion> InputVectorArray, int InputPositionValidator);
	bool PredictInputChampionPositions();
	bool ValidateInputDuplicates(Champion ChampionNameInput);


	
	void ClashPredictorEnemyTeamPicks();
	std::vector<int> ClashPredictorOptimizationMatrix(std::vector<std::vector<int>> PositionsMatrixInput, std::vector<std::vector<int>> RankMatrixInput);
	std::vector<int> ClashPredictorGetChampionPosition(std::string ChampionNameInput);
	std::vector<int> GetOptimalPositions(std::vector<std::vector<int>> combinationsMatrix, std::vector<std::vector<float>> positionWeights);
	std::vector<Champion> ClashPredictorGetPositionChamps(Player InputPlayer);

	void Combinations(std::vector<std::vector<int>> &inputArray);

public:
	Team InputTeam;
	Team OutputTeam;
	float WinPercent = 0;

	std::vector<Player> FriendlyTeamPlayers;
	std::vector<Player> EnemyTeamPlayers;

	MatchupCalculator(std::vector<Champion> InputAllChampionObjects);
	~MatchupCalculator();

	void ComputeOutputTeam();
	void ComputeWinPercent();

	ClashTeam ClashEnemyTeam;
	void ClashPredictor(std::vector<PlayerMinimal> FriendlyTeamInputs, std::vector<const char*> EnemyTeamInputs);


};