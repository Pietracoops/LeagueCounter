#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "webscrape.h"
#include "championlist.h"

#include <libxml\tree.h>
#include <libxml\parser.h>
#include <libxml\HTMLparser.h>




int main(void)
{
    std::vector<std::string> Clist;
    std::string htmlBuffer;
    ChampionList champions("LeagueChampions.csv");
    Champion tmpChamp;
    WebScrape webscraper;
    std::ofstream fout;
    std::string databasePath = "E:\\dev\\LeagueProject\\LeagueProject\\LeagueProject\\database\\";

    htmlDocPtr htmlDoc;
    xmlDocPtr doc;
    xmlNode *root_element;

    Clist = champions.GetChampionList();
    champions.Find_All_Files(databasePath);
    

    for (unsigned int i = 0; i < Clist.size(); i++)
    {
        if (champions.Check_In_Database(Clist[i]))
        {
            continue;
        }
        //std::cout << Clist[i] << std::endl;
        std::cout << i + 1 << " of " << Clist.size() << " Champions processed." << std::endl;
        

        webscraper.BuildWebAddress(Clist[i]); //build the request address
        webscraper.ScrapeHTML(htmlBuffer);
        //fout.open("output.html");
        //fout << htmlBuffer;
        //fout.close();
        
        tmpChamp.ChampionName = Clist[i];
        tmpChamp.ProcessChampionHTML(htmlBuffer);
        champions.AllChampionObjects.push_back(tmpChamp);
        

        //Export
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

    std::cout << "Complete" << std::endl;

    return 0;
}