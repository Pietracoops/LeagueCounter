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

    std::size_t found;
    for (unsigned int i = 0; i < m_databaseVector.size(); i++)
    {
        found = m_databaseVector[i].find(champInput);
        if (found != std::string::npos)
        {
            return true;
        }
    }
    return false;
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

    //&#x27; is = to "-"

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