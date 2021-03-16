#include "championlist.h"

ChampionList::ChampionList(std::string filename)
{
	//import the file
	fin.open(filename);

	std::string champion;

	while (std::getline(fin, champion))  // same as: while (getline( myfile, line ).good())
	{
		m_championVector.push_back(champion);
	}

    fin.close();

}

void ChampionList::ChampionListPositions(std::string filename)
{
    //import the file
    fin.open(filename);

    std::string tmpString;
    std::string posPlaceHolder;
    std::size_t found;
    int LastChamp = 0;

    while (std::getline(fin, tmpString))  // same as: while (getline( myfile, line ).good())
    {
        for (unsigned int i = LastChamp; i < m_championVector.size(); i++)
        {
            //std::cout << i + 1 << " of " << m_championVector.size() << " Champions processed." << std::endl;

            found = tmpString.find(AllChampionObjects[i].ChampionName + " ");
            if (found != std::string::npos)
            {
                //remove champion name
                tmpString.erase(0, AllChampionObjects[i].ChampionName.length() + 1); //We're erasing to make the search faster
            }
            else
            {
                continue;
            }

            while (true)
            {
                found = tmpString.find(" ");
                if (found != std::string::npos)
                {
                    posPlaceHolder = tmpString.substr(0, found);

                    //Mid
                    found = posPlaceHolder.find("Mid");
                    if (found != std::string::npos)
                    {
                        AllChampionObjects[i].m_position_array.push_back(1);
                        tmpString.erase(found, 4);
                        continue;

                    }

                    //Top
                    found = posPlaceHolder.find("Top");
                    if (found != std::string::npos)
                    {
                        AllChampionObjects[i].m_position_array.push_back(2);
                        tmpString.erase(found, 4);
                        continue;
                    }

                    //Jungle
                    found = posPlaceHolder.find("Jungle");
                    if (found != std::string::npos)
                    {
                        AllChampionObjects[i].m_position_array.push_back(3);
                        tmpString.erase(found, 7);
                        continue;
                    }

                    //ADC
                    found = posPlaceHolder.find("ADC");
                    if (found != std::string::npos)
                    {
                        AllChampionObjects[i].m_position_array.push_back(4);
                        tmpString.erase(found, 4);
                        continue;
                    }

                    //Support
                    found = posPlaceHolder.find("Support");
                    if (found != std::string::npos)
                    {
                        AllChampionObjects[i].m_position_array.push_back(5);
                        tmpString.erase(found, 8);
                        continue;
                    }

                }
                else
                {
                    break;
                }


            }

           

            LastChamp = i; //save last champ we searched
            break;

        }

    }

    fin.close();

}


std::vector<std::string> ChampionList::Find_All_Files(std::string Path)
{

    std::experimental::filesystem::path Filepath;
    std::vector<std::string> Files;

    for (const auto& entry : std::experimental::filesystem::directory_iterator(Path))
    {
        Filepath = entry.path().c_str();
        //str = entry.path().generic_u8string();
        Files.push_back(entry.path().generic_u8string());
        //std::cout << entry.path() << std::endl;
    }

    m_databaseVector = Files;
    return Files;
}

bool ChampionList::Check_In_Database(std::string champInput)
{
    std::ifstream fin;
    Champion tmpChamp;
    counter tmpCounter;
    std::size_t found;
    std::string tmpStr;
    bool success = false;
    for (unsigned int i = 0; i < m_databaseVector.size(); i++)
    {
        found = m_databaseVector[i].find(champInput);
        if (found != std::string::npos)
        {
            //import data from file
            tmpChamp.ChampionName = champInput;
            //std::cout << champInput << std::endl;
            fin.open(m_databaseVector[i]);
            if (fin.is_open())
            {
                do 
                {
                    fin >> tmpCounter.m_counterName;
                    //Check for random string
                    found = tmpCounter.m_counterName.find("&#x27;");
                    if (found != std::string::npos)
                    {
                        //remove all beginning crap before this
                        tmpCounter.m_counterName.erase(found, 6);
                        tmpCounter.m_counterName.insert(found, "'");
                    }

                    while (true)
                    {
                        found = NULL;
                        fin >> tmpStr;
                        success = true;
                        try
                        {
                            tmpCounter.percent = std::stof(tmpStr, &found);
                        }
                        catch(std::exception e)
                        {
                            if (tmpStr.compare("&amp;") == 0)
                            {
                                tmpCounter.m_counterName += " &";
                            }
                            else
                            {
                                tmpCounter.m_counterName += " " + tmpStr;
                            }

                            success = false;
                        }

                        if (success == true)
                        {
                            break;
                        }
                        
                    }

                    tmpChamp.m_countersArray.push_back(tmpCounter);
                    if (tmpChamp.m_countersArray.size() == 10) break;
                } while (!fin.eof());
            }
            else
            {
                std::cout << "Failed to open file: " << m_databaseVector[i] << std::endl;
            }
            fin.close();
            
            AllChampionObjects.push_back(tmpChamp); //Add champion to list

            return true;
        }
    }
    return false;
}


void ChampionTierListImport(std::string filename)
{


}



ChampionList::~ChampionList()
{

}

std::vector<std::string> ChampionList::GetChampionList()
{
	return m_championVector;
}


Champion::Champion()
{

}

Champion::~Champion()
{

}


void Champion::ProcessChampionHTML(std::string htmlFile)
{
    Champion tmpChamp;
    std::string ChampName;
    std::string WinRate;
    std::string CurrentChamp;

    counter CounterChamp;

    //std::ofstream fout;
    //fout.open("output.html");
    //fout << htmlFile;
    //fout.close();
    //&#x27; is = to "'"

    //This finds the current champ we're looking for
    std::size_t found = htmlFile.find("champion-name");
    if (found != std::string::npos)
    {
        //remove all beginning crap before this
        htmlFile.erase(0, found);
    }

    found = htmlFile.find(">");
    if (found != std::string::npos)
    {
        //remove all beginning crap before this
        htmlFile.erase(0, found);
    }

    found = htmlFile.find("<");
    if (found != std::string::npos)
    {
        CurrentChamp = htmlFile.substr(1, found - 1);
        htmlFile.erase(0, found);
    }

    while (true)
    {
        std::size_t found = htmlFile.find("champion-name");
        if (found != std::string::npos)
        {
            //remove all beginning crap before this
            htmlFile.erase(0, found);
        }
        else
        {
            break;
        }

        found = htmlFile.find(">");
        if (found != std::string::npos)
        {
            //remove all beginning crap before this
            htmlFile.erase(0, found);
        }

        found = htmlFile.find("<");
        if (found != std::string::npos)
        {
            ChampName = htmlFile.substr(1, found - 1);
            htmlFile.erase(0, found);
        }

        found = htmlFile.find("\"win-rate\"");
        if (found != std::string::npos)
        {
            //remove all beginning crap before this
            htmlFile.erase(0, found);
        }

        found = htmlFile.find(">");
        if (found != std::string::npos)
        {
            //remove all beginning crap before this
            htmlFile.erase(0, found);
        }

        found = htmlFile.find("<");
        if (found != std::string::npos)
        {
            WinRate = htmlFile.substr(1, found - 1);
            htmlFile.erase(0, found);
        }

        //clean win rate
        WinRate = WinRate.substr(0, WinRate.length() - 4);

        CounterChamp.m_counterName  = ChampName;
        CounterChamp.percent        = stof(WinRate);

        m_countersArray.push_back(CounterChamp);

        CounterChamp.m_counterName = "";
        CounterChamp.percent = -1;

        if (m_countersArray.size() == 10)
        {
            break;
        }
    }



}

void Champion::Reset()
{
    std::cout << "Resetting array" << std::endl;
    m_countersArray.clear();
    std::cout << "size of array: " << m_countersArray.size() << std::endl;
}