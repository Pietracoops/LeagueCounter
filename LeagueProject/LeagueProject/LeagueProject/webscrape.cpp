#include "webscrape.h"


WebScrape::WebScrape()
{
    curl = curl_easy_init();
    m_baseUrl = "https://u.gg/lol/champions/";

    //https://www.utf8-chartable.de/

    utf_chart[' '] = "%20";
    utf_chart['À'] = "%C3%80";
    utf_chart['Á'] = "%C3%81";
    utf_chart['Â'] = "%C3%82";
    utf_chart['Ã'] = "%C3%83";
    utf_chart['Ä'] = "%C3%84";
    utf_chart['Å'] = "%C3%85";
    utf_chart['Æ'] = "%C3%86";
    utf_chart['Ç'] = "%C3%87";
    utf_chart['È'] = "%C3%88";
    utf_chart['É'] = "%C3%89";
    utf_chart['Ê'] = "%C3%8A";
    utf_chart['Ë'] = "%C3%8B";
    utf_chart['Ì'] = "%C3%8C";
    utf_chart['Í'] = "%C3%8D";
    utf_chart['Î'] = "%C3%8E";
    utf_chart['Ï'] = "%C3%8F";
    utf_chart['Ð'] = "%C3%90";
    utf_chart['Ñ'] = "%C3%91";
    utf_chart['Ò'] = "%C3%92";
    utf_chart['Ó'] = "%C3%93";
    utf_chart['Ô'] = "%C3%94";
    utf_chart['Õ'] = "%C3%95";
    utf_chart['Ö'] = "%C3%96";
    utf_chart['×'] = "%C3%97";
    utf_chart['Ø'] = "%C3%98";
    utf_chart['Ù'] = "%C3%99";
    utf_chart['Ú'] = "%C3%9A";
    utf_chart['Û'] = "%C3%9B";
    utf_chart['Ü'] = "%C3%9C";
    utf_chart['Ý'] = "%C3%9D";
    utf_chart['Þ'] = "%C3%9E";
    utf_chart['ß'] = "%C3%9F";
    utf_chart['à'] = "%C3%A0";
    utf_chart['á'] = "%C3%A1";
    utf_chart['â'] = "%C3%A2";
    utf_chart['ã'] = "%C3%A3";
    utf_chart['ä'] = "%C3%A4";
    utf_chart['å'] = "%C3%A5";
    utf_chart['æ'] = "%C3%A6";
    utf_chart['ç'] = "%C3%A7";
    utf_chart['è'] = "%C3%A8";
    utf_chart['é'] = "%C3%A9";
    utf_chart['ê'] = "%C3%AA";
    utf_chart['ë'] = "%C3%AB";
    utf_chart['ì'] = "%C3%AC";
    utf_chart['í'] = "%C3%AD";
    utf_chart['î'] = "%C3%AE";
    utf_chart['ï'] = "%C3%AF";
    utf_chart['ð'] = "%C3%B0";
    utf_chart['ñ'] = "%C3%B1";
    utf_chart['ò'] = "%C3%B2";
    utf_chart['ó'] = "%C3%B3";
    utf_chart['ô'] = "%C3%B4";
    utf_chart['õ'] = "%C3%B5";
    utf_chart['ö'] = "%C3%B6";
    utf_chart['÷'] = "%C3%B7";
    utf_chart['ø'] = "%C3%B8";
    utf_chart['ù'] = "%C3%B9";
    utf_chart['ú'] = "%C3%BA";
    utf_chart['û'] = "%C3%BB";
    utf_chart['ü'] = "%C3%BC";
    utf_chart['ý'] = "%C3%BD";
    utf_chart['þ'] = "%C3%BE";
    utf_chart['ÿ'] = "%C3%BF";

    utf_chart_cont[' ']++;
    utf_chart_cont['À']++;
    utf_chart_cont['Á']++;
    utf_chart_cont['Â']++;
    utf_chart_cont['Ã']++;
    utf_chart_cont['Ä']++;
    utf_chart_cont['Å']++;
    utf_chart_cont['Æ']++;
    utf_chart_cont['Ç']++;
    utf_chart_cont['È']++;
    utf_chart_cont['É']++;
    utf_chart_cont['Ê']++;
    utf_chart_cont['Ë']++;
    utf_chart_cont['Ì']++;
    utf_chart_cont['Í']++;
    utf_chart_cont['Î']++;
    utf_chart_cont['Ï']++;
    utf_chart_cont['Ð']++;
    utf_chart_cont['Ñ']++;
    utf_chart_cont['Ò']++;
    utf_chart_cont['Ó']++;
    utf_chart_cont['Ô']++;
    utf_chart_cont['Õ']++;
    utf_chart_cont['Ö']++;
    utf_chart_cont['×']++;
    utf_chart_cont['Ø']++;
    utf_chart_cont['Ù']++;
    utf_chart_cont['Ú']++;
    utf_chart_cont['Û']++;
    utf_chart_cont['Ü']++;
    utf_chart_cont['Ý']++;
    utf_chart_cont['Þ']++;
    utf_chart_cont['ß']++;
    utf_chart_cont['à']++;
    utf_chart_cont['á']++;
    utf_chart_cont['â']++;
    utf_chart_cont['ã']++;
    utf_chart_cont['ä']++;
    utf_chart_cont['å']++;
    utf_chart_cont['æ']++;
    utf_chart_cont['ç']++;
    utf_chart_cont['è']++;
    utf_chart_cont['é']++;
    utf_chart_cont['ê']++;
    utf_chart_cont['ë']++;
    utf_chart_cont['ì']++;
    utf_chart_cont['í']++;
    utf_chart_cont['î']++;
    utf_chart_cont['ï']++;
    utf_chart_cont['ð']++;
    utf_chart_cont['ñ']++;
    utf_chart_cont['ò']++;
    utf_chart_cont['ó']++;
    utf_chart_cont['ô']++;
    utf_chart_cont['õ']++;
    utf_chart_cont['ö']++;
    utf_chart_cont['÷']++;
    utf_chart_cont['ø']++;
    utf_chart_cont['ù']++;
    utf_chart_cont['ú']++;
    utf_chart_cont['û']++;
    utf_chart_cont['ü']++;
    utf_chart_cont['ý']++;
    utf_chart_cont['þ']++;
    utf_chart_cont['ÿ']++;

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
        
        //std::string str = "https://your.gg/na/profile/Böris the Blade";
        //std::string str3 = "https://your.gg/na/profile/B%C3%B6ris%20the%20Blade";
        //const char* str2 = "https://your.gg/na/profile/Böris the Blade";
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