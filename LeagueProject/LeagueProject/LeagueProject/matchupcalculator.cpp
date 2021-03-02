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
		for (unsigned int j = 0; j < m_championArchive.size(); j++)
		{
			if (m_championArchive[j].ChampionName.compare(InputTeam.Mid.m_countersArray[i].m_counterName) == 0)
			{
				tmpChamp = m_championArchive[j];
			}
		}


		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the top lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Top.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Jungle lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Jungler.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the ADC lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.ADC.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Support lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Support.ChampionName) == 0)
			{
				score++;
			}
		}

		//Assign points based on position
		if (tmpChamp.m_position_array[0] == 1)
		{
			score = score + 0;
		}
		else if (tmpChamp.m_position_array[0] == 2)
		{
			score = score + 1;
		}
		else if (tmpChamp.m_position_array[0] == 3)
		{
			score = score + 4;
		}
		else if (tmpChamp.m_position_array[0] == 4)
		{
			score = score + 2;
		}
		else if (tmpChamp.m_position_array[0] == 5)
		{
			score = score + 4;
		}

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
		for (unsigned int j = 0; j < m_championArchive.size(); j++)
		{
			if (m_championArchive[j].ChampionName.compare(InputTeam.Top.m_countersArray[i].m_counterName) == 0)
			{
				tmpChamp = m_championArchive[j];
			}
		}


		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Mid lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Mid.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Jungle lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Jungler.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the ADC lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.ADC.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Support lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Support.ChampionName) == 0)
			{
				score++;
			}
		}

		//Assign points based on position
		if (tmpChamp.m_position_array[0] == 1)
		{
			score = score + 1;
		}
		else if (tmpChamp.m_position_array[0] == 2)
		{
			score = score + 0;
		}
		else if (tmpChamp.m_position_array[0] == 3)
		{
			score = score + 4;
		}
		else if (tmpChamp.m_position_array[0] == 4)
		{
			score = score + 2;
		}
		else if (tmpChamp.m_position_array[0] == 5)
		{
			score = score + 4;
		}

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
		for (unsigned int j = 0; j < m_championArchive.size(); j++)
		{
			if (m_championArchive[j].ChampionName.compare(InputTeam.Jungler.m_countersArray[i].m_counterName) == 0)
			{
				tmpChamp = m_championArchive[j];
			}
		}


		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Mid lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Mid.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Top lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Top.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the ADC lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.ADC.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Support lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Support.ChampionName) == 0)
			{
				score++;
			}
		}

		//Assign points based on position
		if (tmpChamp.m_position_array[0] == 1)
		{
			score = score + 3;
		}
		else if (tmpChamp.m_position_array[0] == 2)
		{
			score = score + 1;
		}
		else if (tmpChamp.m_position_array[0] == 3)
		{
			score = score + 0;
		}
		else if (tmpChamp.m_position_array[0] == 4)
		{
			score = score + 3;
		}
		else if (tmpChamp.m_position_array[0] == 5)
		{
			score = score + 4;
		}

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
		for (unsigned int j = 0; j < m_championArchive.size(); j++)
		{
			if (m_championArchive[j].ChampionName.compare(InputTeam.ADC.m_countersArray[i].m_counterName) == 0)
			{
				tmpChamp = m_championArchive[j];
			}
		}


		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Mid lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Mid.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Top lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Top.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Jungler lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Jungler.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Support lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Support.ChampionName) == 0)
			{
				score++;
			}
		}

		//Assign points based on position
		if (tmpChamp.m_position_array[0] == 1)
		{
			score = score + 1;
		}
		else if (tmpChamp.m_position_array[0] == 2)
		{
			score = score + 3;
		}
		else if (tmpChamp.m_position_array[0] == 3)
		{
			score = score + 4;
		}
		else if (tmpChamp.m_position_array[0] == 4)
		{
			score = score + 0;
		}
		else if (tmpChamp.m_position_array[0] == 5)
		{
			score = score + 2;
		}

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
		for (unsigned int j = 0; j < m_championArchive.size(); j++)
		{
			if (m_championArchive[j].ChampionName.compare(InputTeam.Support.m_countersArray[i].m_counterName) == 0)
			{
				tmpChamp = m_championArchive[j];
			}
		}


		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Mid lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Mid.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Top lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Top.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Jungler lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.Jungler.ChampionName) == 0)
			{
				score++;
			}
		}

		for (unsigned int j = 0; j < tmpChamp.m_countersArray.size(); j++) //Make sure that the counter pick is not in the Support lane
		{
			if (tmpChamp.m_countersArray[j].m_counterName.compare(InputTeam.ADC.ChampionName) == 0)
			{
				score++;
			}
		}

		//Assign points based on position
		if (tmpChamp.m_position_array[0] == 1)
		{
			score = score + 2;
		}
		else if (tmpChamp.m_position_array[0] == 2)
		{
			score = score + 3;
		}
		else if (tmpChamp.m_position_array[0] == 3)
		{
			score = score + 4;
		}
		else if (tmpChamp.m_position_array[0] == 4)
		{
			score = score + 3;
		}
		else if (tmpChamp.m_position_array[0] == 5)
		{
			score = score + 0;
		}

		CounterChampsSupport.push_back(tmpChamp);
		CounterScores.push_back(score);
		score = 0;
	}


	//Select optimal Support Laner
	minElementIndex = std::min_element(CounterScores.begin(), CounterScores.end()) - CounterScores.begin();
	OutputTeam.Support = CounterChampsSupport[minElementIndex];
	CounterScores.clear();


}

