#include "playerstats.h"

Player::Player()
{


}

Player::~Player()
{

}

void Player::ConcatChars(const char* str1, const char* str2)
{
    //Clean ResultInside First
    for (unsigned int i = 0; i < 150; i++)
    {
        ConcatenatedString[i] = ' ';
    }


    strcpy_s(ConcatenatedString, str1); // copy string one into the result.
    strcat_s(ConcatenatedString, str2); // append string two to the result.
    //return Result;
}


void Player::ProcessPlayerStats(const char* PlayerNameInput)
{
    PlayerName = PlayerNameInput;
    WebScrape PlayerWebScraper;
    //Scrape OP.GG for champions played

    ConcatChars(opggRootAddress, PlayerNameInput);
    std::string opggRaw = PlayerWebScraper.ScrapeHTML(ConcatenatedString);
    ProcessOPGGRaw(opggRaw);

    //Scrape YOUR.GG for Match History
    ConcatChars(yourggRootAddress, PlayerNameInput);
    std::string yourggRaw = PlayerWebScraper.ScrapeHTML(ConcatenatedString);
    ProcessYOURGGRaw(yourggRaw);

}

void Player::ProcessOPGGRaw(std::string rawHTMLInput)
{

    Champion tmpChamp;
    std::size_t found;
    //remove tabs and spaces first
    rawHTMLInput.erase(std::remove(rawHTMLInput.begin(), rawHTMLInput.end(), '\n'), rawHTMLInput.end());
    rawHTMLInput.erase(std::remove(rawHTMLInput.begin(), rawHTMLInput.end(), '\t'), rawHTMLInput.end());
    rawHTMLInput.erase(std::remove(rawHTMLInput.begin(), rawHTMLInput.end(), ','), rawHTMLInput.end());

    //This finds the current champ we're looking for
    while (true)
    {
        found = rawHTMLInput.find("Rank Cell");
        if (found != std::string::npos)
        {
            //remove all beginning crap before this
            rawHTMLInput.erase(0, found);

            //Get Champion Name
            found = rawHTMLInput.find("Image __sprite");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found);
            }
            found = rawHTMLInput.find(">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 1);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.ChampionName = rawHTMLInput.substr(0, found);
            }
            found = tmpChamp.ChampionName.find("&#039;"); //replace "'"
            if (found != std::string::npos)
            {
                tmpChamp.ChampionName.erase(found, 6);
                tmpChamp.ChampionName.insert(found, "'");
            }
            found = tmpChamp.ChampionName.find("&amp;"); //replace "'"
            if (found != std::string::npos)
            {
                tmpChamp.ChampionName.erase(found, 6);
                tmpChamp.ChampionName.insert(found, "& ");
            }
            //=================================

            //Get Wins
            found = rawHTMLInput.find("Text Left\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 11);
            }
            found = rawHTMLInput.find("W<");
            if (found != std::string::npos)
            {
                tmpChamp.Wins = stoi(rawHTMLInput.substr(0, found));
            }

            //Get Losses
            found = rawHTMLInput.find("Text Right\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("L<");
            if (found != std::string::npos)
            {
                tmpChamp.Losses = stoi(rawHTMLInput.substr(0, found));
            }

            tmpChamp.GamesPlayed = tmpChamp.Wins + tmpChamp.Losses;
            tmpChamp.WinRatio = (float(tmpChamp.Wins) / float(tmpChamp.GamesPlayed)) * 100;

            //Get Kills
            found = rawHTMLInput.find("Kill\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 6);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.Kills = stof(rawHTMLInput.substr(0, found));
            }

            //Get Deaths
            found = rawHTMLInput.find("Death\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 7);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.Deaths = stof(rawHTMLInput.substr(0, found));
            }

            //Get Assists
            found = rawHTMLInput.find("Assist\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 8);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.Assists = stof(rawHTMLInput.substr(0, found));
            }
            
            //Gold
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                //remove comma
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.Gold = stoi(rawHTMLInput.substr(0, found));
            }

            //CS
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.CS = stof(rawHTMLInput.substr(0, found));
            }

            //Max Kills
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.MaxKills = stoi(rawHTMLInput.substr(0, found));
            }

            //Max Deaths
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.MaxDeaths = stoi(rawHTMLInput.substr(0, found));
            }

            //Average Damage Dealt
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.AverageDamageDealt = stoi(rawHTMLInput.substr(0, found));
            }

            //Average Damage Taken
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpChamp.AverageDamageTaken = stoi(rawHTMLInput.substr(0, found));
            }

            //Double Kill
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                if (rawHTMLInput.substr(0, found).compare("") == 0)
                {
                    tmpChamp.DoubleKills = 0;
                }
                else
                {
                    tmpChamp.DoubleKills = stoi(rawHTMLInput.substr(0, found));
                }
            }

            //Triple Kill
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                if (rawHTMLInput.substr(0, found).compare("") == 0)
                {
                    tmpChamp.DoubleKills = 0;
                }
                else
                {
                    tmpChamp.TripleKills = stoi(rawHTMLInput.substr(0, found));
                }                
            }

            //Quadra Kill
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                if (rawHTMLInput.substr(0, found).compare("") == 0)
                {
                    tmpChamp.DoubleKills = 0;
                }
                else
                {
                    tmpChamp.QuadraKills = stoi(rawHTMLInput.substr(0, found));
                }
            }

            //Penta Kill
            found = rawHTMLInput.find("Value Cell\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 12);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                if (rawHTMLInput.substr(0, found).compare("") == 0)
                {
                    tmpChamp.DoubleKills = 0;
                }
                else
                {
                    tmpChamp.PentaKills = stoi(rawHTMLInput.substr(0, found));
                }
            }

            PlayedChampions.push_back(tmpChamp);
        }
        else
        {
            break; //no more champs in list
        }
    }

}

void Player::ProcessYOURGGRaw(std::string rawHTMLInput)
{
    Champion tmpChamp;
    Game tmpGame;
    std::size_t found;
    std::string tmpStr;
    PlayerMinimal tmpPlayerMin;

    std::ofstream fout;
    fout.open("output.html");
    fout << rawHTMLInput;
    fout.close();
    //remove tabs and spaces first
    rawHTMLInput.erase(std::remove(rawHTMLInput.begin(), rawHTMLInput.end(), '\n'), rawHTMLInput.end());
    rawHTMLInput.erase(std::remove(rawHTMLInput.begin(), rawHTMLInput.end(), '\t'), rawHTMLInput.end());
    rawHTMLInput.erase(std::remove(rawHTMLInput.begin(), rawHTMLInput.end(), ','), rawHTMLInput.end());


    //  data-href="/na/profile/DomingoDuck/match/3814748228" >

    //Find SoloQ Rank
    found = rawHTMLInput.find("<span class=\"gg-sub-title\">");
    if (found != std::string::npos)
    {
        rawHTMLInput.erase(0, found + 27);
    }
    found = rawHTMLInput.find("mt-1\">");
    if (found != std::string::npos)
    {
        rawHTMLInput.erase(0, found + 6);
    }
    found = rawHTMLInput.find("<");
    if (found != std::string::npos)
    {
        SoloQRank = rawHTMLInput.substr(0, found);
        SoloQRank.erase(std::remove(SoloQRank.begin(), SoloQRank.end(), ' '), SoloQRank.end());
    }

    //Find Flex Rank
    found = rawHTMLInput.find("<span class=\"gg-sub-title\">");
    if (found != std::string::npos)
    {
        rawHTMLInput.erase(0, found + 27);
    }
    found = rawHTMLInput.find("mt-1\">");
    if (found != std::string::npos)
    {
        rawHTMLInput.erase(0, found + 6);
    }
    found = rawHTMLInput.find("<");
    if (found != std::string::npos)
    {
        FlexRank = rawHTMLInput.substr(0, found);
        FlexRank.erase(std::remove(FlexRank.begin(), FlexRank.end(), ' '), FlexRank.end());
    }

    ComputeRankValue();

    //Initial Cleanup
    found = rawHTMLInput.find("div id=\"profileGraphAllPc\"");
    if (found != std::string::npos)
    {
        rawHTMLInput.erase(0, found + 39);
    }

    found = rawHTMLInput.find("<div class = \"d-none d-lg-block\" style = \"padding: 1px\">");
    if (found != std::string::npos)
    {
        //int value = rawHTMLInput.end();
        rawHTMLInput.erase(found, rawHTMLInput.size() - 1);
    }


    //This finds the current champ we're looking for
    while (true)
    {

        found = rawHTMLInput.find("/match/");
        if (found != std::string::npos)
        {
            //remove all beginning crap before this
            rawHTMLInput.erase(0, found);

            //Get Game type
            found = rawHTMLInput.find("<div class=\"d-flex flex-column justify-content-between align-items-center\" style=\"min-width: 55px\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 99);
            }
            found = rawHTMLInput.find("<div>");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 5);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpStr = rawHTMLInput.substr(0, found);
                tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
                tmpGame.GameType = tmpStr;

                if (tmpGame.GameType.compare("") == 0) break;
            }

            //Get Victory Status
            found = rawHTMLInput.find("<div class=\"text-f mt-1\">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 25);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpStr = rawHTMLInput.substr(0, found);
                tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
                if (tmpStr.compare("Loss") == 0)
                {
                    tmpGame.VictoryStatus = false;
                }
                else
                {
                    tmpGame.VictoryStatus = true;
                }
            }

            //Get Champion Name
            found = rawHTMLInput.find("/champion/");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 10);
            }
            found = rawHTMLInput.find(".png");
            if (found != std::string::npos)
            {
                tmpGame.ChampionPlayed = rawHTMLInput.substr(0, found);
            }

            //Get Rating
            found = rawHTMLInput.find("data-event=\"move_to_match matchlist_contribution\"");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found);
            }
            found = rawHTMLInput.find(">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 1);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpGame.Rating = stof(rawHTMLInput.substr(0, found));
            }

            //Get Laning Phase
            found = rawHTMLInput.find("data-event=\"move_to_match matchlist_laningphase\"");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found);
            }
            found = rawHTMLInput.find(">");
            if (found != std::string::npos)
            {
                rawHTMLInput.erase(0, found + 1);
            }
            found = rawHTMLInput.find("<");
            if (found != std::string::npos)
            {
                tmpStr = rawHTMLInput.substr(0, found);
                tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
                tmpGame.LaningPhaseRatio = tmpStr;
            }

            //Get Team Participants
            for (unsigned int i = 0; i < 10; i++) //10 players
            {
                //Player Champ
                //Get Champion Name
                found = rawHTMLInput.find("/champion/");
                if (found != std::string::npos)
                {
                    rawHTMLInput.erase(0, found + 10);
                }
                found = rawHTMLInput.find(".png");
                if (found != std::string::npos)
                {
                    tmpPlayerMin.Champion = rawHTMLInput.substr(0, found);
                }


                //Player Name
                found = rawHTMLInput.find("data-event=\"move_to_profile matchlist_summoner\"");
                if (found != std::string::npos)
                {
                    rawHTMLInput.erase(0, found);
                }
                found = rawHTMLInput.find(">");
                if (found != std::string::npos)
                {
                    rawHTMLInput.erase(0, found + 1);
                }
                found = rawHTMLInput.find("<");
                if (found != std::string::npos)
                {
                    tmpStr = rawHTMLInput.substr(0, found);
                    tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
                    tmpPlayerMin.PlayerNameStr = tmpStr;

                    //tmpGame.LaningPhaseRatio = tmpStr;
                }

                if (tmpPlayerMin.PlayerNameStr.compare(PlayerName) == 0)
                {
                    if (i == 0)
                    {
                        tmpGame.Position = 2;
                    }
                    else if (i == 1)
                    {
                        tmpGame.Position = 3;
                    }
                    else if (i == 2)
                    {
                        tmpGame.Position = 1;
                    }
                    else if (i == 3)
                    {
                        tmpGame.Position = 4;
                    }
                    else if (i == 4)
                    {
                        tmpGame.Position = 5;
                    }
                }

                if (i < 5)
                {
                    tmpGame.FriendlyTeam.push_back(tmpPlayerMin);
                }
                else
                {
                    tmpGame.EnemyTeam.push_back(tmpPlayerMin);
                }

            }


            MatchHistory.push_back(tmpGame);
            tmpGame.EmptyObject();
          
        }
        else
        {
            break; //no more champs in list
        }
    }
}


void Player::ComputeRankValue()
{
    //Ranks go according to the following:
    //Iron
    //Bronze
    //Silver
    //Gold
    //Platinum
    //Diamond
    //Master
    //Grandmaster
    //Challenger

    std::size_t found;

    //SoloQ
    for (unsigned int i = 0; i < Ranks.size(); i++)
    {
        found = SoloQRank.find(Ranks[i]);
        if (found != std::string::npos)
        {
            SoloQRank.erase(0, found + Ranks[i].size());
            SoloQRankValue = RankConversion[i+1] - stoi(SoloQRank);
            break;
        }
    }

    //Flex
    for (unsigned int i = 0; i < Ranks.size(); i++)
    {
        found = FlexRank.find(Ranks[i]);
        if (found != std::string::npos)
        {
            FlexRank.erase(0, found + Ranks[i].size());
            FlexQRankValue = RankConversion[i+1] - stoi(FlexRank);
            break;
        }
    }

}

void Player::EmptyObject()
{
    PlayerName.clear();
    PlayedChampions.clear();	//Use OP.GG
    SoloQRank = "";
    FlexRank = "";
    MatchHistory.clear();

}


Game::Game()
{

}

Game::~Game()
{

}

void Game::EmptyObject()
{
    FriendlyTeam.clear();
    EnemyTeam.clear();
    ChampionPlayed = "";
    VictoryStatus = false;
    GameType = "";
    Rating = 0.0;
    LaningPhaseRatio = "";
    Position = 0;
}