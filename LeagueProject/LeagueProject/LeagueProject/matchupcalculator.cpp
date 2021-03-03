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

void MatchupCalculator::ComputeCounterChamp()
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
	for (unsigned int i = 0; i < InputTeam.TeamPicks.size(); i++)
	{
		for (unsigned int j = 0; j < InputTeam.TeamPicks[i].m_position_array.size(); j++)
		{
			if (InputTeam.Mid.ChampionName.compare("") == 0 && InputTeam.TeamPicks[i].m_position_array[j] == 1)
			{
				InputTeam.Mid = InputTeam.TeamPicks[i];
			}

			if (InputTeam.Top.ChampionName.compare("") == 0 && InputTeam.TeamPicks[i].m_position_array[j] == 2)
			{
				InputTeam.Top = InputTeam.TeamPicks[i];
			}

			if (InputTeam.Jungler.ChampionName.compare("") == 0 && InputTeam.TeamPicks[i].m_position_array[j] == 3)
			{
				InputTeam.Jungler = InputTeam.TeamPicks[i];
			}

			if (InputTeam.ADC.ChampionName.compare("") == 0 && InputTeam.TeamPicks[i].m_position_array[j] == 4)
			{
				InputTeam.ADC = InputTeam.TeamPicks[i];
			}

			if (InputTeam.Support.ChampionName.compare("") == 0 && InputTeam.TeamPicks[i].m_position_array[j] == 5)
			{
				InputTeam.Support = InputTeam.TeamPicks[i];
			}
		}
	}


	//Now lets cycle through each position and select the best counter picks
	//We'll start with mid lane
	//We will assign each counter a score, the lower the score the better the counter
	for (unsigned int i = 0; i < InputTeam.Mid.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Mid.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.ADC);
		score += FindCounter(tmpChamp, InputTeam.Support);

		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsMidLane);

		CounterChampsMid.push_back(tmpChamp);
		CounterScores.push_back(score);
		score = 0;
	}

	//Select optimal Mid Laner
	minElementIndex = std::min_element(CounterScores.begin(), CounterScores.end()) - CounterScores.begin();
	OutputTeam.Mid = CounterChampsMid[minElementIndex];
	CounterScores.clear();


	//We'll proceed with Top lane
	//We will assign each counter a score, the lower the score the better the counter
	for (unsigned int i = 0; i < InputTeam.Top.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Top.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.ADC);
		score += FindCounter(tmpChamp, InputTeam.Support);


		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsTopLane);

		CounterChampsTop.push_back(tmpChamp);
		CounterScores.push_back(score);
		score = 0;
	}

	//Select optimal Top Laner
	minElementIndex = std::min_element(CounterScores.begin(), CounterScores.end()) - CounterScores.begin();
	OutputTeam.Top = CounterChampsTop[minElementIndex];
	CounterScores.clear();
	

	//We'll proceed with Jungle lane
	//We will assign each counter a score, the lower the score the better the counter
	for (unsigned int i = 0; i < InputTeam.Jungler.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Jungler.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.ADC);
		score += FindCounter(tmpChamp, InputTeam.Support);

		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsJunglerLane);

		CounterChampsJungler.push_back(tmpChamp);
		CounterScores.push_back(score);
		score = 0;
	}

	//Select optimal Jungle Laner
	minElementIndex = std::min_element(CounterScores.begin(), CounterScores.end()) - CounterScores.begin();
	OutputTeam.Jungler = CounterChampsJungler[minElementIndex];
	CounterScores.clear();




	//We'll proceed with Jungle lane
	//We will assign each counter a score, the lower the score the better the counter
	for (unsigned int i = 0; i < InputTeam.ADC.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.ADC.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.Support);


		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsADCLane);

		CounterChampsADC.push_back(tmpChamp);
		CounterScores.push_back(score);
		score = 0;
	}

	//Select optimal ADC Laner
	minElementIndex = std::min_element(CounterScores.begin(), CounterScores.end()) - CounterScores.begin();
	OutputTeam.ADC = CounterChampsADC[minElementIndex];
	CounterScores.clear();


	//We'll proceed with Jungle lane
	//We will assign each counter a score, the lower the score the better the counter
	for (unsigned int i = 0; i < InputTeam.Support.m_countersArray.size(); i++)
	{
		//Search the total champs array for the counter champ
		if (!FindChampionObject(InputTeam.Support.m_countersArray[i].m_counterName, tmpChamp))
		{
			std::cout << "Champion counter not found: Error: MatchupCalculator::ComputeOutputTeam: F1" << std::endl;
			return; //error
		}

		score += FindCounter(tmpChamp, InputTeam.Mid);
		score += FindCounter(tmpChamp, InputTeam.Top);
		score += FindCounter(tmpChamp, InputTeam.Jungler);
		score += FindCounter(tmpChamp, InputTeam.ADC);

		//Assign points based on position
		score += PositionWeights(tmpChamp, weightsSupportLane);

		CounterChampsSupport.push_back(tmpChamp);
		CounterScores.push_back(score);
		score = 0;
	}

	//Select optimal Support Laner
	minElementIndex = std::min_element(CounterScores.begin(), CounterScores.end()) - CounterScores.begin();
	OutputTeam.Support = CounterChampsSupport[minElementIndex];
	CounterScores.clear();

	ComputeWinPercent();
}

