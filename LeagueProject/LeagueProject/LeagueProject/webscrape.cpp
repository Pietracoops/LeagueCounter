#include "webscrape.h"


WebScrape::WebScrape()
{
    curl = curl_easy_init();
    m_baseUrl = "https://u.gg/lol/champions/";
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

int WebScrape::ScrapeHTML(std::string & buffer)
{

    curl = curl_easy_init();
   
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

    m_currentChampionURL = m_baseUrl + m_championName + "/counter";

    return 0;
}