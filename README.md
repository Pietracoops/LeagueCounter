**LeagueCounter is still under development.**

## Welcome to LeagueCounter!

This project aims to help C++ developers connect to and interact with League of Legends databases through scraping and API usage.  

## Getting Started

![Vcpkg package](https://repology.org/badge/version-for-repo/vcpkg/cpprestsdk.svg)

## How to Use

Initialize using the champion database and call the initialization function. Then we feed the database with the preferred positions of each champion.
```
    ChampionList champions("LeagueChampions.csv");
    champions.Initialization();
    champions.ChampionListPositions("LeagueChampions_Positions.csv");
	
```

Then we will initialize a MatchupCalculator object with our champion database.
```
MatchupCalculator Calculator(champions.AllChampionObjects);

```

We can then use the MatchupCalculator object to determine a counter team for a specific matchup, with the calculated Win percentage.
```
    Calculator.InputTeam.TeamPicksStr.push_back("Caitlyn");
    Calculator.InputTeam.TeamPicksStr.push_back("Ashe");
    Calculator.InputTeam.TeamPicksStr.push_back("Kalista");
    Calculator.InputTeam.TeamPicksStr.push_back("Tristana");
    Calculator.InputTeam.TeamPicksStr.push_back("Lucian");
    
    Calculator.ComputeOutputTeam();
    
    std::cout << "===================== TEAM 1: INPUT TEAM ===============================" << std::endl;
    std::cout << "Top Laner:        "      << Calculator.InputTeam.Top.ChampionName << std::endl;
    std::cout << "Mid Laner:        "      << Calculator.InputTeam.Mid.ChampionName << std::endl;
    std::cout << "Jungler Laner:    "      << Calculator.InputTeam.Jungler.ChampionName << std::endl;
    std::cout << "ADC Laner:        "      << Calculator.InputTeam.ADC.ChampionName << std::endl;
    std::cout << "Support Laner:    "      << Calculator.InputTeam.Support.ChampionName << std::endl;
    
    std::cout << "===================== TEAM 2: OUTPUT TEAM ==============================" << std::endl;
    
    std::cout << "Top Laner:        "      << Calculator.OutputTeam.Top.ChampionName << std::endl;
    std::cout << "Mid Laner:        "      << Calculator.OutputTeam.Mid.ChampionName << std::endl;
    std::cout << "Jungler Laner:    "      << Calculator.OutputTeam.Jungler.ChampionName << std::endl;
    std::cout << "ADC Laner:        "      << Calculator.OutputTeam.ADC.ChampionName << std::endl;
    std::cout << "Support Laner:    "      << Calculator.OutputTeam.Support.ChampionName << std::endl;
    std::cout << "WIN PERCENTAGE CALCULATED: "    << Calculator.WinPercent << std::endl;
```

The ClashPredictor function of the calculator can predict the positions of each player on enemy team and recommend bans for that position in order of priority. The following code
is used to enter two teams into the ClashPredictor function.
```
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
```
The output can be retrieved by doing the following:
```
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
```