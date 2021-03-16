#include "webscrape.h"


WebScrape::WebScrape()
{
    curl = curl_easy_init();
    m_baseUrl = "https://u.gg/lol/champions/";

    //https://www.utf8-chartable.de/

    utf_chart[' '] = "%20";
    utf_chart['�'] = "%C3%80";
    utf_chart['�'] = "%C3%81";
    utf_chart['�'] = "%C3%82";
    utf_chart['�'] = "%C3%83";
    utf_chart['�'] = "%C3%84";
    utf_chart['�'] = "%C3%85";
    utf_chart['�'] = "%C3%86";
    utf_chart['�'] = "%C3%87";
    utf_chart['�'] = "%C3%88";
    utf_chart['�'] = "%C3%89";
    utf_chart['�'] = "%C3%8A";
    utf_chart['�'] = "%C3%8B";
    utf_chart['�'] = "%C3%8C";
    utf_chart['�'] = "%C3%8D";
    utf_chart['�'] = "%C3%8E";
    utf_chart['�'] = "%C3%8F";
    utf_chart['�'] = "%C3%90";
    utf_chart['�'] = "%C3%91";
    utf_chart['�'] = "%C3%92";
    utf_chart['�'] = "%C3%93";
    utf_chart['�'] = "%C3%94";
    utf_chart['�'] = "%C3%95";
    utf_chart['�'] = "%C3%96";
    utf_chart['�'] = "%C3%97";
    utf_chart['�'] = "%C3%98";
    utf_chart['�'] = "%C3%99";
    utf_chart['�'] = "%C3%9A";
    utf_chart['�'] = "%C3%9B";
    utf_chart['�'] = "%C3%9C";
    utf_chart['�'] = "%C3%9D";
    utf_chart['�'] = "%C3%9E";
    utf_chart['�'] = "%C3%9F";
    utf_chart['�'] = "%C3%A0";
    utf_chart['�'] = "%C3%A1";
    utf_chart['�'] = "%C3%A2";
    utf_chart['�'] = "%C3%A3";
    utf_chart['�'] = "%C3%A4";
    utf_chart['�'] = "%C3%A5";
    utf_chart['�'] = "%C3%A6";
    utf_chart['�'] = "%C3%A7";
    utf_chart['�'] = "%C3%A8";
    utf_chart['�'] = "%C3%A9";
    utf_chart['�'] = "%C3%AA";
    utf_chart['�'] = "%C3%AB";
    utf_chart['�'] = "%C3%AC";
    utf_chart['�'] = "%C3%AD";
    utf_chart['�'] = "%C3%AE";
    utf_chart['�'] = "%C3%AF";
    utf_chart['�'] = "%C3%B0";
    utf_chart['�'] = "%C3%B1";
    utf_chart['�'] = "%C3%B2";
    utf_chart['�'] = "%C3%B3";
    utf_chart['�'] = "%C3%B4";
    utf_chart['�'] = "%C3%B5";
    utf_chart['�'] = "%C3%B6";
    utf_chart['�'] = "%C3%B7";
    utf_chart['�'] = "%C3%B8";
    utf_chart['�'] = "%C3%B9";
    utf_chart['�'] = "%C3%BA";
    utf_chart['�'] = "%C3%BB";
    utf_chart['�'] = "%C3%BC";
    utf_chart['�'] = "%C3%BD";
    utf_chart['�'] = "%C3%BE";
    utf_chart['�'] = "%C3%BF";

    utf_chart_cont[' ']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;
    utf_chart_cont['�']++;

}

WebScrape::~WebScrape()
{
    curl_easy_cleanup(curl);
}

size_t WebScrape::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int WebScrape::ScrapeHTMLChampion(std::string & buffer)
{

    //curl = curl_easy_init();
   
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, m_currentChampionURL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        
        buffer = readBuffer;
        readBuffer = "";
   
        return 0;
    }

    return 1;
}

int WebScrape::BuildWebAddress(std::string m_championName)
{
    //Remove spaces in champion name
    m_championName.erase(std::remove_if(m_championName.begin(), m_championName.end(), isspace), m_championName.end());

    if (m_championName.compare("Nunu&Willump") == 0)
    {
        m_currentChampionURL = m_baseUrl + "nunu" + "/counter";
    }
    else
    {
        m_currentChampionURL = m_baseUrl + m_championName + "/counter";
    }

    return 0;
}


int WebScrape::GetSummonerStats()
{
    std::string outputhtml;

    outputhtml = ScrapeHTML(m_summonerStatsURL);

    std::ofstream fout;

    fout.open("slist.html");
    fout << outputhtml;
    fout.close();

    return 0;
}

int WebScrape::BuildChampionTierList()
{
    std::string outputhtml;

    outputhtml = ScrapeHTML(m_championTierListURL);

    std::ofstream fout;

    fout.open("clist.html");
    fout << outputhtml;
    fout.close();

    return 0;
}

std::string WebScrape::ProcessForYOURGG(std::string buffer)
{
    size_t found;
    while (true)
    {
        found = buffer.find(" ");
        if (found != std::string::npos)
        {
            buffer.erase(found, 1);
            buffer.insert(found, "%20");
        }
        else
        {
            break;
        }
    }

    return buffer;
}


void WebScrape::cleanStr(std::string& inputStr)
{
    char tmpChar;
    for (unsigned int i = 0; i < inputStr.size(); i++)
    {
        if (utf_chart_cont[inputStr[i]] == 1)
        {
            tmpChar = inputStr[i];
            inputStr.erase(i, 1);
            inputStr.insert(i, utf_chart[tmpChar]);
        }
    }
}


std::string WebScrape::ScrapeHTML(std::string Scrapebuffer)
{
    //size_t found;
    //std::cout << "test" << std::endl;
    //Need to learn how to scrape dynamic websites
    readBuffer = "";
    if (curl) {
        //while (true)
        //{
        //    found = buffer.find(" ");
        //    if (found != std::string::npos)
        //    {
        //        buffer.erase(found, 1);
        //        buffer.insert(found, "+");
        //    }
        //    else
        //    {
        //        break;
        //    }
        //}
        
        //std::string str = "https://your.gg/na/profile/B�ris the Blade";
        //std::string str3 = "https://your.gg/na/profile/B%C3%B6ris%20the%20Blade";
        //const char* str2 = "https://your.gg/na/profile/B�ris the Blade";
        //const char* str4 = "https://your.gg/na/profile/B%C3%B6ris%20the%20Blade";
        //https://your.gg/na/profile/B%C3%B6ris%20the%20Blade

        cleanStr(Scrapebuffer);

        curl_easy_setopt(curl, CURLOPT_URL, Scrapebuffer.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        return readBuffer;
    }
    else
    {
        std::cout << "Error initializing Curl" << std::endl;
        return "";
    }

}