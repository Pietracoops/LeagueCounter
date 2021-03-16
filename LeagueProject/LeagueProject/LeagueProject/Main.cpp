#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "webscrape.h"
#include "championlist.h"
#include "matchupcalculator.h"
#include "playerstats.h"

#include <libxml\tree.h>
#include <libxml\parser.h>
#include <libxml\HTMLparser.h>


//RIOT GAMES API KEY: RGAPI-9660c08a-60a6-4d64-acc5-d0976e02a8ae

void Initialization(ChampionList &championsInput)
{

    std::vector<std::string> Clist;
    std::string htmlBuffer;
    //ChampionList champions("LeagueChampions.csv");
    Champion tmpChamp;
    WebScrape webscraper;
    std::ofstream fout;
    std::string databasePath = "E:\\dev\\LeagueCounter\\LeagueProject\\LeagueProject\\LeagueProject\\database\\";

    Clist = championsInput.GetChampionList();
    championsInput.Find_All_Files(databasePath);


    //webscraper.BuildChampionTierList();  //this needs work because of react web page
    webscraper.GetSummonerStats();


    for (unsigned int i = 0; i < Clist.size(); i++)
    {
        //std::cout << i + 1 << " of " << Clist.size() << " Champions processed." << std::endl;
        if (championsInput.Check_In_Database(Clist[i])) // If already in database then proceed to next champ
        {
            continue;
        }

        webscraper.BuildWebAddress(Clist[i]);                   //build the request address
        webscraper.ScrapeHTMLChampion(htmlBuffer);              //Retrieve html as string

        tmpChamp.ChampionName = Clist[i];                       //Fill champion name
        tmpChamp.ProcessChampionHTML(htmlBuffer);               //Fetch champion counters from html
        championsInput.AllChampionObjects.push_back(tmpChamp);  //Insert champion object into full champion list

        //Export into database
        fout.open(databasePath + Clist[i] + ".txt");
        for (unsigned int i = 0; i < tmpChamp.m_countersArray.size(); i++)
        {
            fout << tmpChamp.m_countersArray[i].m_counterName << " " << tmpChamp.m_countersArray[i].percent << std::endl;
            std::cout << tmpChamp.m_countersArray[i].m_counterName << " " << tmpChamp.m_countersArray[i].percent << std::endl;
        }
        fout.close();

        //Clear
        tmpChamp.Reset();
        htmlBuffer = "";

    }



}



int main(void)
{
    ChampionList champions("LeagueChampions.csv");

    std::cout << "Begin Initialization" << std::endl;
    Initialization(champions);
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



    const char* str;
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


    str = "DomingoDuck";
    team2.push_back(str);
    str = "oOImfezoOo";
    team2.push_back(str);
    str = "MastrixX";
    team2.push_back(str);
    str = "Best Shot";
    team2.push_back(str);
    str = "ysl prodigy";
    team2.push_back(str);

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