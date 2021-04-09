#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "webscrape.h"
#include "championlist.h"
#include "matchupcalculator.h"
#include "playerstats.h"

#include "applicationmanip.h"

#include <cpprest/http_listener.h>


//RIOT GAMES API KEY: RGAPI-9660c08a-60a6-4d64-acc5-d0976e02a8ae



int main(void)
{
    //std::cout << "Begin Initialization" << std::endl;
    //
    //ChampionList champions("LeagueChampions.csv");
    //champions.Initialization();
    //champions.ChampionListPositions("LeagueChampions_Positions.csv");
    //
    //std::cout << "Initialization Complete" << std::endl;
    //
    //MatchupCalculator Calculator(champions.AllChampionObjects);

    Application client("cefsimple.exe");
    client.Launch();

    Sleep(5000);

    client.Kill();

    return 0;
}