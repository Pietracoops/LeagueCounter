#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "webscrape.h"
#include "championlist.h"
#include "matchupcalculator.h"
#include "playerstats.h"

#include <cpprest/http_listener.h>


//RIOT GAMES API KEY: RGAPI-9660c08a-60a6-4d64-acc5-d0976e02a8ae



int main(void)
{
    std::cout << "Begin Initialization" << std::endl;

    ChampionList champions("LeagueChampions.csv");
    champions.Initialization();
    champions.ChampionListPositions("LeagueChampions_Positions.csv");

    std::cout << "Initialization Complete" << std::endl;

    MatchupCalculator Calculator(champions.AllChampionObjects);

    //Calculator.InputTeam.TeamPicksStr.push_back("Caitlyn");
    //Calculator.InputTeam.TeamPicksStr.push_back("Ashe");
    //Calculator.InputTeam.TeamPicksStr.push_back("Kalista");
    //Calculator.InputTeam.TeamPicksStr.push_back("Tristana");
    //Calculator.InputTeam.TeamPicksStr.push_back("Lucian");
    //
    //Calculator.ComputeOutputTeam();
    //
    //std::cout << "===================== TEAM 1: INPUT TEAM ===============================" << std::endl;
    //std::cout << "Top Laner:        "      << Calculator.InputTeam.Top.ChampionName << std::endl;
    //std::cout << "Mid Laner:        "      << Calculator.InputTeam.Mid.ChampionName << std::endl;
    //std::cout << "Jungler Laner:    "      << Calculator.InputTeam.Jungler.ChampionName << std::endl;
    //std::cout << "ADC Laner:        "      << Calculator.InputTeam.ADC.ChampionName << std::endl;
    //std::cout << "Support Laner:    "      << Calculator.InputTeam.Support.ChampionName << std::endl;
    //
    //std::cout << "===================== TEAM 2: OUTPUT TEAM ==============================" << std::endl;
    //
    //std::cout << "Top Laner:        "      << Calculator.OutputTeam.Top.ChampionName << std::endl;
    //std::cout << "Mid Laner:        "      << Calculator.OutputTeam.Mid.ChampionName << std::endl;
    //std::cout << "Jungler Laner:    "      << Calculator.OutputTeam.Jungler.ChampionName << std::endl;
    //std::cout << "ADC Laner:        "      << Calculator.OutputTeam.ADC.ChampionName << std::endl;
    //std::cout << "Support Laner:    "      << Calculator.OutputTeam.Support.ChampionName << std::endl;
    //std::cout << "WIN PERCENTAGE CALCULATED: "    << Calculator.WinPercent << std::endl;


    PlayerMinimal PlayerObject;
    std::vector<PlayerMinimal> team1;
    std::vector<const char*> team2;
    PlayerObject.PlayerName = "DomingoDuck";
    PlayerObject.Position = 2;
    team1.push_back(PlayerObject);
    PlayerObject.PlayerName = "oOImfezoOo";
    PlayerObject.Position = 3;
    team1.push_back(PlayerObject);
    PlayerObject.PlayerName = "MastrixX";
    PlayerObject.Position = 4;
    team1.push_back(PlayerObject);
    PlayerObject.PlayerName = "Best Shot";
    PlayerObject.Position = 5;
    team1.push_back(PlayerObject);
    PlayerObject.PlayerName = "ysl prodigy";
    PlayerObject.Position = 1;
    team1.push_back(PlayerObject);


    team2.push_back("ATownSwinger");
    team2.push_back("cyhe66");
    team2.push_back("CTYPanda");
    team2.push_back("JaNaCl");
    team2.push_back("Solarienn");

    Calculator.ClashPredictor(team1, team2);

    std::cout << "================================ RESULTS ==============================" << std::endl;
    std::cout << "PREDICTED POSITIONS:" << std::endl;
    std::cout << "Top Laner:     "  << Calculator.ClashEnemyTeam.TeamPlayers[1].PlayerName << std::endl;
    std::cout << "Jungle Laner:  "  << Calculator.ClashEnemyTeam.TeamPlayers[2].PlayerName << std::endl;
    std::cout << "Mid Laner:     "  << Calculator.ClashEnemyTeam.TeamPlayers[0].PlayerName << std::endl;
    std::cout << "ADC Laner:     "  << Calculator.ClashEnemyTeam.TeamPlayers[3].PlayerName << std::endl;
    std::cout << "Support Laner: "  << Calculator.ClashEnemyTeam.TeamPlayers[4].PlayerName << std::endl;


    std::cout << "RECOMMENDED MID BANS IN ORDER OF PRIORITY:" << std::endl;
    for (unsigned int i = 0; i < Calculator.ClashEnemyTeam.MidBans.size(); i++)
    {
        std::cout << Calculator.ClashEnemyTeam.MidBans[i].ChampionName << std::endl;
        if (i > 5)
        {
            break;
        }
    }

    std::cout << "RECOMMENDED TOP BANS IN ORDER OF PRIORITY:" << std::endl;
    for (unsigned int i = 0; i < Calculator.ClashEnemyTeam.TopBans.size(); i++)
    {
        std::cout << Calculator.ClashEnemyTeam.TopBans[i].ChampionName << std::endl;
        if (i > 5)
        {
            break;
        }
    }

    std::cout << "RECOMMENDED JUNGLE BANS IN ORDER OF PRIORITY:" << std::endl;
    for (unsigned int i = 0; i < Calculator.ClashEnemyTeam.JunglerBans.size(); i++)
    {
        std::cout << Calculator.ClashEnemyTeam.JunglerBans[i].ChampionName << std::endl;
        if (i > 5)
        {
            break;
        }
    }

    std::cout << "RECOMMENDED ADC BANS IN ORDER OF PRIORITY:" << std::endl;
    for (unsigned int i = 0; i < Calculator.ClashEnemyTeam.ADCBans.size(); i++)
    {
        std::cout << Calculator.ClashEnemyTeam.ADCBans[i].ChampionName << std::endl;
        if (i > 5)
        {
            break;
        }
    }

    std::cout << "RECOMMENDED SUPPORT BANS IN ORDER OF PRIORITY:" << std::endl;
    for (unsigned int i = 0; i < Calculator.ClashEnemyTeam.SupportBans.size(); i++)
    {
        std::cout << Calculator.ClashEnemyTeam.SupportBans[i].ChampionName << std::endl;
        if (i > 5)
        {
            break;
        }
    }

    return 0;
}