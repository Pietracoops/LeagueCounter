#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "webscrape.h"
#include "championlist.h"
#include "matchupcalculator.h"

#include <libxml\tree.h>
#include <libxml\parser.h>
#include <libxml\HTMLparser.h>


void Initialization(ChampionList &championsInput)
{

    std::vector<std::string> Clist;
    std::string htmlBuffer;
    //ChampionList champions("LeagueChampions.csv");
    Champion tmpChamp;
    WebScrape webscraper;
    std::ofstream fout;
    std::string databasePath = "E:\\dev\\LeagueCounter\\LeagueProject\\LeagueProject\\LeagueProject\\database\\";

    htmlDocPtr htmlDoc;
    xmlDocPtr doc;
    xmlNode* root_element;

    Clist = championsInput.GetChampionList();
    championsInput.Find_All_Files(databasePath);


    for (unsigned int i = 0; i < Clist.size(); i++)
    {
        //std::cout << i + 1 << " of " << Clist.size() << " Champions processed." << std::endl;
        if (championsInput.Check_In_Database(Clist[i])) // If already in database then proceed to next champ
        {
            continue;
        }

        webscraper.BuildWebAddress(Clist[i]);                   //build the request address
        webscraper.ScrapeHTML(htmlBuffer);                      //Retrieve html as string

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
    //ChampionList champions("LeagueChampions_Positions.csv");

    std::cout << "Begin Initialization" << std::endl;
    Initialization(champions);
    champions.ChampionListPositions("LeagueChampions_Positions.csv");
    std::cout << "Initialization Complete" << std::endl;

    MatchupCalculator Calculator(champions.AllChampionObjects);

    //Give input team
    Calculator.InputTeam.TeamPicksStr.push_back("Aatrox");
    Calculator.InputTeam.TeamPicksStr.push_back("Fizz");
    Calculator.InputTeam.TeamPicksStr.push_back("Ivern");
    Calculator.InputTeam.TeamPicksStr.push_back("Draven");
    Calculator.InputTeam.TeamPicksStr.push_back("Alistar");

    Calculator.ComputeOutputTeam();

    //Spit out recommended team
    std::cout << "Top Laner: "      << Calculator.OutputTeam.Top.ChampionName << std::endl;
    std::cout << "Mid Laner: "      << Calculator.OutputTeam.Mid.ChampionName << std::endl;
    std::cout << "Jungler Laner: "  << Calculator.OutputTeam.Jungler.ChampionName << std::endl;
    std::cout << "ADC Laner: "      << Calculator.OutputTeam.ADC.ChampionName << std::endl;
    std::cout << "Support Laner: "  << Calculator.OutputTeam.Support.ChampionName << std::endl;



    return 0;
}