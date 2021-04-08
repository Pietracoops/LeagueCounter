#include "matchupcalculator.h"

Team::Team()
{

}

Team::~Team()
{

}

MatchupCalculator::MatchupCalculator(std::vector<Champion> InputAllChampionObjects)
{
	m_championArchive = InputAllChampionObjects;
}

MatchupCalculator::~MatchupCalculator()
{

}



bool MatchupCalculator::FindChampionObject(std::string InputChampionName, Champion &OutputChampion)
{

	//Search the total champs array for the counter champ
	for (unsigned int j = 0; j < m_championArchive.size(); j++)
	{
		if (m_championArchive[j].ChampionName.compare(InputChampionName) == 0)
		{
			OutputChampion = m_championArchive[j];
			return true;
		}
	}

	return false; //no match
}


int MatchupCalculator::FindCounter(Champion& InputChampionName, Champion& CompareChampion)
{
	int score = 0;
	for (unsigned int j = 0; j < InputChampionName.m_countersArray.size(); j++) //Make sure that the counter pick is not in the top lane
	{
		if (InputChampionName.m_countersArray[j].m_counterName.compare(CompareChampion.ChampionName) == 0)
		{
			score++;
		}
	}

	return score;
}


int MatchupCalculator::PositionWeights(Champion& InputChampion, std::vector<int> weights)
{
	int score = 0;
	if (InputChampion.m_position_array[0] == 1)
	{
		score = score + weights[0]; //0
	}
	else if (InputChampion.m_position_array[0] == 2)
	{
		score = score + weights[1]; //1
	}
	else if (InputChampion.m_position_array[0] == 3)
	{
		score = score + weights[2]; //4
	}
	else if (InputChampion.m_position_array[0] == 4)
	{
		score = score + weights[3]; //2
	}
	else if (InputChampion.m_position_array[0] == 5)
	{
		score = score + weights[4]; //4
	}

	return score;
}


void MatchupCalculator::ComputeWinPercent()
{
	//reset winpercent first
	WinPercent = 0;

	if (OutputTeam.Mid.ChampionName.compare("") != 0)
	{
		for (unsigned int i = 0; i < InputTeam.Mid.m_countersArray.size(); i++)
		{
			if (InputTeam.Mid.m_countersArray[i].m_counterName.compare(OutputTeam.Mid.ChampionName) == 0)
			{
				Percentages.push_back(InputTeam.Mid.m_countersArray[i].percent);
				break;
			}
		}
	}

	if (OutputTeam.Top.ChampionName.compare("") != 0)
	{
		for (unsigned int i = 0; i < InputTeam.Top.m_countersArray.size(); i++)
		{
			if (InputTeam.Top.m_countersArray[i].m_counterName.compare(OutputTeam.Top.ChampionName) == 0)
			{
				Percentages.push_back(InputTeam.Top.m_countersArray[i].percent);
				break;
			}
		}
	}

	if (OutputTeam.Jungler.ChampionName.compare("") != 0)
	{
		for (unsigned int i = 0; i < InputTeam.Jungler.m_countersArray.size(); i++)
		{
			if (InputTeam.Jungler.m_countersArray[i].m_counterName.compare(OutputTeam.Jungler.ChampionName) == 0)
			{
				Percentages.push_back(InputTeam.Jungler.m_countersArray[i].percent);
				break;
			}
		}
	}

	if (OutputTeam.ADC.ChampionName.compare("") != 0)
	{
		for (unsigned int i = 0; i < InputTeam.ADC.m_countersArray.size(); i++)
		{
			if (InputTeam.ADC.m_countersArray[i].m_counterName.compare(OutputTeam.ADC.ChampionName) == 0)
			{
				Percentages.push_back(InputTeam.ADC.m_countersArray[i].percent);
				break;
			}
		}
	}

	if (OutputTeam.Support.ChampionName.compare("") != 0)
	{
		for (unsigned int i = 0; i < InputTeam.Support.m_countersArray.size(); i++)
		{
			if (InputTeam.Support.m_countersArray[i].m_counterName.compare(OutputTeam.Support.ChampionName) == 0)
			{
				Percentages.push_back(InputTeam.Support.m_countersArray[i].percent);
				break;
			}
		}
	}

	for (unsigned int i = 0; i < Percentages.size(); i++)
	{
		WinPercent += Percentages[i];
	}

	WinPercent = WinPercent / Percentages.size();
}


void MatchupCalculator::ComputeOutputTeam()
{
	//Check input team first
	for (unsigned int i = 0; i < InputTeam.TeamPicksStr.size(); i++)
	{
		//Search for champ in array
		for (unsigned int j = 0; j < m_championArchive.size(); j++)
		{
			if (m_championArchive[j].ChampionName.compare(InputTeam.TeamPicksStr[i]) == 0)
			{
				InputTeam.TeamPicks.push_back(m_championArchive[j]);
				break;
			}

		}
	}

	//We now have the Champion Objects and we will make assumptions of their possible positions
	//we want to have a value of 1 for each available position
	PredictInputChampionPositions();


	//Now lets cycle through each position and select the best counter picks
	//We'll start with mid lane
	//We will assign each counter a score, the lower the score the better the counter
	if (FindMidCounter())
	{
		std::cout << "Failed to compute Mid Counter" << std::endl;
	}

	//We'll proceed with Top lane
	//We will assign each counter a score, the lower the score the better the counter
	if (FindTopCounter())
	{
		std::cout << "Failed to compute Top Counter" << std::endl;
	}

	//We'll proceed with Jungle lane
	//We will assign each counter a score, the lower the score the better the counter
	if (FindJunglerCounter())
	{
		std::cout << "Failed to compute Jungle Counter" << std::endl;
	}

	//We'll proceed with Jungle lane
	//We will assign each counter a score, the lower the score the better the counter
	if (FindADCCounter())
	{
		std::cout << "Failed to compute ADC Counter" << std::endl;
	}

	//We'll proceed with Jungle lane
	//We will assign each counter a score, the lower the score the better the counter

	if (FindSupportCounter())
	{
		std::cout << "Failed to compute Support Counter" << std::endl;
	}


	ComputeWinPercent();
}


bool MatchupCalculator::PredictInputChampionPositions()
{
	//Assign Points First
	std::vector<int> tmpVector = { 0,0,0,0,0 };
	for (unsigned int i = 0; i < 5; i++) //positions
	{
		InputChampPositionScores.push_back(tmpVector);
		for (unsigned int j = 0; j < InputTeam.TeamPicks.size(); j++)
		{
			for (unsigned int k = 0; k < InputTeam.TeamPicks[j].m_position_array.size(); k++)
			{
				if (InputTeam.TeamPicks[j].m_position_array[k] == i + 1)
				{
					InputChampPositionScores[i][j] = 5 - k;
				}
			}
		}
	}

	//Pick a Mid Laner
	InputTeam.Mid = InputTeam.TeamPicks[0];
	for (unsigned int i = 1; i < InputChampPositionScores[0].size(); i++)
	{
		if (InputChampPositionScores[0][i] > InputChampPositionScores[0][i - 1] && ValidateInputDuplicates(InputTeam.TeamPicks[i]))
		{
			InputTeam.Mid = InputTeam.TeamPicks[i];
		}
	}

	//Pick a Top Laner
	for (unsigned int i = 0; i < InputTeam.TeamPicks.size(); i++)
	{
		if (ValidateInputDuplicates(InputTeam.TeamPicks[i])) InputTeam.Top = InputTeam.TeamPicks[i];
	}
	for (unsigned int i = 1; i < InputChampPositionScores[1].size(); i++)
	{
		if (InputChampPositionScores[1][i] > InputChampPositionScores[1][i - 1] && ValidateInputDuplicates(InputTeam.TeamPicks[i]))
		{
			InputTeam.Top = InputTeam.TeamPicks[i];
		}
	}

	//Pick a Jungler Laner
	for (unsigned int i = 0; i < InputTeam.TeamPicks.size(); i++)
	{
		if (ValidateInputDuplicates(InputTeam.TeamPicks[i])) InputTeam.Jungler = InputTeam.TeamPicks[i];
	}
	for (unsigned int i = 1; i < InputChampPositionScores[2].size(); i++)
	{
		if (InputChampPositionScores[2][i] > InputChampPositionScores[2][i - 1] && ValidateInputDuplicates(InputTeam.TeamPicks[i]))
		{
			InputTeam.Jungler = InputTeam.TeamPicks[i];
		}
	}

	//Pick a ADC Laner
	for (unsigned int i = 0; i < InputTeam.TeamPicks.size(); i++)
	{
		if (ValidateInputDuplicates(InputTeam.TeamPicks[i])) InputTeam.ADC = InputTeam.TeamPicks[i];
	}
	for (unsigned int i = 1; i < InputChampPositionScores[0].size(); i++)
	{
		if (InputChampPositionScores[3][i] > InputChampPositionScores[3][i - 1] && ValidateInputDuplicates(InputTeam.TeamPicks[i]))
		{
			InputTeam.ADC = InputTeam.TeamPicks[i];
		}
	}

	//Pick a Support Laner
	for (unsigned int i = 0; i < InputTeam.TeamPicks.size(); i++)
	{
		if (ValidateInputDuplicates(InputTeam.TeamPicks[i])) InputTeam.Support = InputTeam.TeamPicks[i];
	}
	for (unsigned int i = 1; i < InputChampPositionScores[4].size(); i++)
	{
		if (InputChampPositionScores[4][i] > InputChampPositionScores[4][i - 1] && ValidateInputDuplicates(InputTeam.TeamPicks[i]))
		{
			InputTeam.Support = InputTeam.TeamPicks[i];
		}
	}

	return true;
}


bool MatchupCalculator::ValidateInputDuplicates(Champion ChampionNameInput)
{
	if (ChampionNameInput.ChampionName.compare(InputTeam.Mid.ChampionName) == 0)
	{
		return false;
	}
	if (ChampionNameInput.ChampionName.compare(InputTeam.Top.ChampionName) == 0)
	{
		return false;
	}
	if (ChampionNameInput.ChampionName.compare(InputTeam.Jungler.ChampionName) == 0)
	{
		return false;
	}
	if (ChampionNameInput.ChampionName.compare(InputTeam.ADC.ChampionName) == 0)
	{
		return false;
	}
	if (ChampionNameInput.ChampionName.compare(InputTeam.Support.ChampionName) == 0)
	{
		return false;
	}
	return true;
}

Champion MatchupCalculator::CheckDuplicates(std::vector<Champion> InputVectorArray, int InputPositionValidator)
{
	std::sort(CounterScores.begin(), CounterScores.end()); //sort it first
	bool PositionValid = false;

	for (unsigned int i = 0; i < CounterScores.size(); i++)
	{
		tmpChamp = InputVectorArray[CounterScores[i][1]];

		// Check if Position is applicable
		for (unsigned int j = 0; j < tmpChamp.m_position_array.size(); j++)
		{
			if (tmpChamp.m_position_array[j] == InputPositionValidator)
			{
				PositionValid = true;
			}
		}
		if (PositionValid == false) continue;

		//Check if any of the other positions have same champ
		if (tmpChamp.ChampionName.compare(OutputTeam.Mid.ChampionName) == 0)	continue;
		else if (tmpChamp.ChampionName.compare(OutputTeam.Top.ChampionName) == 0)	continue;
		else if (tmpChamp.ChampionName.compare(OutputTeam.Jungler.ChampionName) == 0)	continue;
		else if (tmpChamp.ChampionName.compare(OutputTeam.ADC.ChampionName) == 0)	continue;
		else if (tmpChamp.ChampionName.compare(OutputTeam.Support.ChampionName) == 0)   continue;
		else if (tmpChamp.ChampionName.compare(InputTeam.Mid.ChampionName) == 0)   continue;
		else if (tmpChamp.ChampionName.compare(InputTeam.Top.ChampionName) == 0)   continue;
		else if (tmpChamp.ChampionName.compare(InputTeam.Jungler.ChampionName) == 0)   continue;
		else if (tmpChamp.ChampionName.compare(InputTeam.ADC.ChampionName) == 0)   continue;
		else if (tmpChamp.ChampionName.compare(InputTeam.Support.ChampionName) == 0)   continue;

		//Break and keep tmpChamp as is
		break;
	}

	return tmpChamp;
}

bool MatchupCalculator::FindMidCounter()
{
	if (InputTeam.Mid.ChampionName.compare("") == 0)
	{
		std::cout << "No Mid Champion Selected" << std::endl;
		return false;
	}

	for (unsigned int i = 0; i < InputTeam.Mid.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Mid.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found MID" << std::endl;
			return false; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.ADC);
		score += FindCounter(tmpChamp, InputTeam.Support);

		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsMidLane);

		CounterChampsMid.push_back(tmpChamp);
		CounterScoresCouple.push_back(score);
		CounterScoresCouple.push_back(i);
		CounterScores.push_back(CounterScoresCouple);
		score = 0;
		CounterScoresCouple.clear();
	}

	//Select optimal Mid Laner
	OutputTeam.Mid = CheckDuplicates(CounterChampsMid, 1);
	CounterScores.clear();
	return true;
}


bool MatchupCalculator::FindTopCounter()
{
	if (InputTeam.Top.ChampionName.compare("") == 0)
	{
		std::cout << "No Top Champion Selected" << std::endl;
		return false;
	}

	for (unsigned int i = 0; i < InputTeam.Top.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Top.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return false; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.ADC);
		score += FindCounter(tmpChamp, InputTeam.Support);


		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsTopLane);

		CounterChampsTop.push_back(tmpChamp);
		CounterScoresCouple.push_back(score);
		CounterScoresCouple.push_back(i);
		CounterScores.push_back(CounterScoresCouple);
		score = 0;
		CounterScoresCouple.clear();
	}

	//Select optimal Top Laner
	OutputTeam.Top = CheckDuplicates(CounterChampsTop, 2);
	CounterScores.clear();
	return true;
}

bool MatchupCalculator::FindJunglerCounter()
{
	if (InputTeam.Jungler.ChampionName.compare("") == 0)
	{
		std::cout << "No Jungler Champion Selected" << std::endl;
		return false;
	}

	for (unsigned int i = 0; i < InputTeam.Jungler.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Jungler.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return false; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.ADC);
		score += FindCounter(tmpChamp, InputTeam.Support);

		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsJunglerLane);

		CounterChampsJungler.push_back(tmpChamp);
		CounterScoresCouple.push_back(score);
		CounterScoresCouple.push_back(i);
		CounterScores.push_back(CounterScoresCouple);
		score = 0;
		CounterScoresCouple.clear();
	}

	//Select optimal Jungle Laner
	OutputTeam.Jungler = CheckDuplicates(CounterChampsJungler, 3);
	CounterScores.clear();
	return true;
}

bool MatchupCalculator::FindADCCounter()
{
	if (InputTeam.ADC.ChampionName.compare("") == 0)
	{
		std::cout << "No ADC Champion Selected" << std::endl;
		return false;
	}

	for (unsigned int i = 0; i < InputTeam.ADC.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.ADC.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return false; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.Support);


		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsADCLane);

		CounterChampsADC.push_back(tmpChamp);
		CounterScoresCouple.push_back(score);
		CounterScoresCouple.push_back(i);
		CounterScores.push_back(CounterScoresCouple);
		score = 0;
		CounterScoresCouple.clear();
	}

	//Select optimal ADC Laner
	OutputTeam.ADC = CheckDuplicates(CounterChampsADC, 4);
	CounterScores.clear();

	return true;
}

bool MatchupCalculator::FindSupportCounter()
{
	if (InputTeam.Support.ChampionName.compare("") == 0)
	{
		std::cout << "No Support Champion Selected" << std::endl;
		return false;
	}

	//We'll proceed with Jungle lane
	//We will assign each counter a score, the lower the score the better the counter
	for (unsigned int i = 0; i < InputTeam.Support.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Support.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return false; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.ADC);

		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsSupportLane);

		CounterChampsSupport.push_back(tmpChamp);
		CounterScoresCouple.push_back(score);
		CounterScoresCouple.push_back(i);
		CounterScores.push_back(CounterScoresCouple);
		score = 0;
		CounterScoresCouple.clear();
	}

	//Select optimal Support Laner
	OutputTeam.Support = CheckDuplicates(CounterChampsSupport, 5);
	CounterScores.clear();

	return true;

}

std::vector<int> MatchupCalculator::ClashPredictorGetChampionPosition(std::string ChampionNameInput)
{

	//find champion in champion archive
	Champion tmpChamp;
	std::vector<int> tmpVec = { 0 };
	for (unsigned int i = 0; i < m_championArchive.size(); i++)
	{
		if (ChampionNameInput.compare(m_championArchive[i].ChampionName) == 0)
		{
			return m_championArchive[i].m_position_array;
		}
	}

	return tmpVec;
}


void MatchupCalculator::Combinations(std::vector<std::vector<int>> &inputArray)
{
	std::vector<int> combination;
	int myints[] = { 0,1,2,3,4 };
	std::sort(myints, myints + 5);

	do {
		combination.push_back(myints[0]);
		combination.push_back(myints[1]);
		combination.push_back(myints[2]);
		combination.push_back(myints[3]);
		combination.push_back(myints[4]);
		inputArray.push_back(combination);
		combination.clear();
	} while (std::next_permutation(myints, myints + 5));

}

std::vector<int> MatchupCalculator::GetOptimalPositions(std::vector<std::vector<int>> combinationsMatrix, std::vector<std::vector<float>> positionWeights)
{
	float sum = 0;
	std::vector<float> couple;
	std::vector<std::vector<float>> sums;
	for (unsigned int i = 0; i < combinationsMatrix.size(); i++)
	{

		sum += positionWeights[combinationsMatrix[i][0]][0];
		sum += positionWeights[combinationsMatrix[i][1]][1];
		sum += positionWeights[combinationsMatrix[i][2]][2];
		sum += positionWeights[combinationsMatrix[i][3]][3];
		sum += positionWeights[combinationsMatrix[i][4]][4];
		couple.push_back(sum);
		couple.push_back((float)i);
		sums.push_back(couple);
		couple.clear();
		sum = 0;


	}

	std::sort(sums.begin(), sums.end(), std::greater<std::vector<float>>()); //ranks

	std::vector<int> output;
	output.push_back(combinationsMatrix[(u_int)sums[0][1]][0]);
	output.push_back(combinationsMatrix[(u_int)sums[0][1]][1]);
	output.push_back(combinationsMatrix[(u_int)sums[0][1]][2]);
	output.push_back(combinationsMatrix[(u_int)sums[0][1]][3]);
	output.push_back(combinationsMatrix[(u_int)sums[0][1]][4]);

	return output;
}

std::vector<int> MatchupCalculator::ClashPredictorOptimizationMatrix(std::vector<std::vector<int>> PositionsMatrixInput, std::vector<std::vector<int>> RankMatrixInput)
{

	std::vector<float> Couple;
	std::vector<std::vector<float>> RankMatrixInputNormalized;

	//Normalize the Rank
	for (unsigned int i = 0; i < RankMatrixInput.size(); i++)
	{
		Couple.push_back((float)(RankMatrixInput[i][0] / 100.0));
		Couple.push_back((float)RankMatrixInput[i][1]);
		RankMatrixInputNormalized.push_back(Couple);
		Couple.clear();
	}

	std::vector<float> PlayerSet;
	std::vector<std::vector<float>> PositionsMatrixInputNormalizedWRank;
	//Multiply the PositionsMatrix with the RankMatrix
	for (unsigned int i = 0; i < PositionsMatrixInput.size(); i++)
	{
		for (unsigned int j = 0; j < PositionsMatrixInput[i].size(); j++)
		{
			PlayerSet.push_back(PositionsMatrixInput[i][j] * RankMatrixInputNormalized[i][0]);
		}

		PositionsMatrixInputNormalizedWRank.push_back(PlayerSet);
		PlayerSet.clear();
	}

	std::vector<std::vector<int>> combinationsInput;
	Combinations(combinationsInput);

	return GetOptimalPositions(combinationsInput, PositionsMatrixInputNormalizedWRank);
}

std::vector<Champion> MatchupCalculator::ClashPredictorGetPositionChamps(Player InputPlayer)
{
	std::vector<Champion> Bans;
	std::vector<std::vector<float>> ChampionRanks;
	std::vector<float> subset;
	float score = 0;
	bool ChampMatchesPlayerPosition;

	for (unsigned int i = 0; i < InputPlayer.PlayedChampions.size(); i++)
	{
		ChampMatchesPlayerPosition = false;

		score += (float)(InputPlayer.PlayedChampions[i].GamesPlayed * 0.80);
		score += (float)(InputPlayer.PlayedChampions[i].WinRatio * 0.10);
		score += (float)(((InputPlayer.PlayedChampions[i].Kills + InputPlayer.PlayedChampions[i].Assists) / InputPlayer.PlayedChampions[i].Deaths) * 0.075);
		score += (float)(InputPlayer.PlayedChampions[i].CS * 0.05);
		score += (float)((InputPlayer.PlayedChampions[i].Gold / 1000) * 0.075);

		for (unsigned int j = 0; j < m_championArchive.size(); j++)
		{
			if (m_championArchive[j].ChampionName.compare(InputPlayer.PlayedChampions[i].ChampionName) == 0)
			{

				for (unsigned int k = 0; k < m_championArchive[j].m_position_array.size(); k++)
				{
					if (m_championArchive[j].m_position_array[k] == InputPlayer.PredictedPosition)
					{
						ChampMatchesPlayerPosition = true;
						break;
					}
				}
				break;

			}
		}

		if (ChampMatchesPlayerPosition == true)
		{
			score *= 1.5;
		}
		
		subset.push_back(score);
		subset.push_back((float)i);
		ChampionRanks.push_back(subset);
		subset.clear();
		score = 0;

	}
	
	std::sort(ChampionRanks.begin(), ChampionRanks.end(), std::greater<std::vector<float>>()); //ranks
	Champion tmpChamp;
	for (unsigned int i = 0; i < ChampionRanks.size(); i++)
	{
		tmpChamp = InputPlayer.PlayedChampions[(u_int)ChampionRanks[i][1]];
		Bans.push_back(tmpChamp);
	}

	return Bans;
}


void MatchupCalculator::ClashPredictorEnemyTeamPicks()
{
	ClashTeam EnemyTeam;
	std::vector<std::vector<int>> EnemyTeamRanks;
	std::vector<int> rankCouple;

	//for finding position
	std::vector<std::vector<int>> tmpPositionsArray;
	std::vector<int> tmpPositions;
	std::vector<int> PositionsTally = { 0,0,0,0,0 };

	std::vector<int> tmpPredictedPositions;


	//Find Highest Ranked Players
	for (unsigned int i = 0; i < EnemyTeamPlayers.size(); i++)
	{
		//GET RANKS
		rankCouple.clear();
		if (EnemyTeamPlayers[i].FlexQRankValue > EnemyTeamPlayers[i].SoloQRankValue)
		{
			rankCouple.push_back(EnemyTeamPlayers[i].FlexQRankValue);
			rankCouple.push_back(i);
			EnemyTeamRanks.push_back(rankCouple);
		}
		else
		{
			rankCouple.push_back(EnemyTeamPlayers[i].SoloQRankValue);
			rankCouple.push_back(i);
			EnemyTeamRanks.push_back(rankCouple);
		}

		
		//Find Positions
		PositionsTally = { 0,0,0,0,0 };
		for (unsigned int j = 0; j < EnemyTeamPlayers[i].PlayedChampions.size(); j++)
		{
			tmpPositions = ClashPredictorGetChampionPosition(EnemyTeamPlayers[i].PlayedChampions[j].ChampionName);
			for (unsigned int k = 0; k < tmpPositions.size(); k++)
			{
				PositionsTally[tmpPositions[k] - 1] += EnemyTeamPlayers[i].PlayedChampions[j].GamesPlayed;
			}
		}

		tmpPositionsArray.push_back(PositionsTally);
		PositionsTally.clear();

	}

	std::vector<int> OptimizedPositions;
	OptimizedPositions = ClashPredictorOptimizationMatrix(tmpPositionsArray, EnemyTeamRanks);

	//std::sort(EnemyTeamRanks.begin(), EnemyTeamRanks.end(), std::greater<std::vector<int>>()); //ranks

	EnemyTeam.TeamPlayers.push_back(EnemyTeamPlayers[OptimizedPositions[0]]);
	EnemyTeam.TeamPlayers.push_back(EnemyTeamPlayers[OptimizedPositions[1]]);
	EnemyTeam.TeamPlayers.push_back(EnemyTeamPlayers[OptimizedPositions[2]]);
	EnemyTeam.TeamPlayers.push_back(EnemyTeamPlayers[OptimizedPositions[3]]);
	EnemyTeam.TeamPlayers.push_back(EnemyTeamPlayers[OptimizedPositions[4]]);

	for (unsigned int i = 0; i < EnemyTeam.TeamPlayers.size(); i++)
	{
		EnemyTeam.TeamPlayers[i].PredictedPosition = i + 1;
	}



	//Find Champs for each role
	EnemyTeam.MidBans	  = ClashPredictorGetPositionChamps(EnemyTeam.TeamPlayers[0]);
	EnemyTeam.TopBans	  = ClashPredictorGetPositionChamps(EnemyTeam.TeamPlayers[1]);
	EnemyTeam.JunglerBans = ClashPredictorGetPositionChamps(EnemyTeam.TeamPlayers[2]);
	EnemyTeam.ADCBans	  = ClashPredictorGetPositionChamps(EnemyTeam.TeamPlayers[3]);
	EnemyTeam.SupportBans = ClashPredictorGetPositionChamps(EnemyTeam.TeamPlayers[4]);


	ClashEnemyTeam = EnemyTeam;

}

void MatchupCalculator::ClashPredictor(std::vector<PlayerMinimal> FriendlyTeamInputs, std::vector<const char*> EnemyTeamInputs)
{
	//Research all Players
	Player tmpPlayer;
	
	std::cout << "===================== TEAM 1: INPUT TEAM ===============================" << std::endl;
	//Get Friendly Team
	for (unsigned int i = 0; i < FriendlyTeamInputs.size(); i++)
	{
		std::cout << FriendlyTeamInputs[i].PlayerName << std::endl;
		tmpPlayer.ProcessPlayerStats(FriendlyTeamInputs[i].PlayerName);
		FriendlyTeamPlayers.push_back(tmpPlayer); //Add to Team array
		tmpPlayer.EmptyObject(); //Clear temp object
	}


	std::cout << "===================== TEAM 2: OUTPUT TEAM ==============================" << std::endl;
	//Get Enemy Team
	for (unsigned int i = 0; i < EnemyTeamInputs.size(); i++)
	{
		std::cout << EnemyTeamInputs[i] << std::endl;
		tmpPlayer.ProcessPlayerStats(EnemyTeamInputs[i]);
		EnemyTeamPlayers.push_back(tmpPlayer); //Add to Team array
		tmpPlayer.EmptyObject(); //Clear temp object
	}


	//Compute Enemy team best picks
	ClashPredictorEnemyTeamPicks();



	std::cout << "complete" << std::endl;

}