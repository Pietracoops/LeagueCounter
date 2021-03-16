#pragma once
#include "championlist.h"
#include "webscrape.h"
#include <algorithm>

struct PlayerMinimal {
	const char* PlayerName;
	std::string PlayerNameStr;
	std::string Champion;
	int Position;
};

class Game {




public:
	
	std::vector<PlayerMinimal> FriendlyTeam;
	std::vector<PlayerMinimal> EnemyTeam;



	std::string ChampionPlayed;
	bool VictoryStatus;
	std::string GameType;
	float Rating;
	std::string LaningPhaseRatio;
	int Position;

	void EmptyObject();
	Game();
	~Game();


};

class Player {

	const char* opggRootAddress = "https://na.op.gg/summoner/champions/userName=";
	const char* yourggRootAddress = "https://your.gg/na/profile/";
	char opggRootAddressResult[150];   // array to hold the result.
	char yourggRootAddressResult[150];   // array to hold the result.
	
	
	char ConcatenatedString[150];
	void ComputeRankValue();
	void ConcatChars(const char* str1, const char* str2);

	std::vector<std::string> Ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Diamond", "Master", "Grandmaster", "Challenger" };
	std::vector<int> RankConversion = { 1,5,9,13,17,21,25,29,33,37 };


public:
	std::string PlayerName;
	std::vector<Champion> PlayedChampions;
	std::string SoloQRank;
	std::string FlexRank;
	std::vector<Game> MatchHistory;

	int PredictedPosition;
	int Position;

	int SoloQRankValue; //Use these to compare rank
	int FlexQRankValue;

	void ProcessPlayerStats(const char* PlayerNameInput);
	void ProcessOPGGRaw(std::string rawHTMLInput);
	void ProcessYOURGGRaw(std::string rawHTMLInput);
	void EmptyObject();
	Player();
	~Player();


};