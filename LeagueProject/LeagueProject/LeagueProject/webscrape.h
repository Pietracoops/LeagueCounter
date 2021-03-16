#pragma once
	//WebScrape Class
	//Description:  This class is used to scrape the HTML files from u.gg
	//				For champion counter matchups
#define CURL_STATICLIB
#include<string>
#include <curl\curl.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

class WebScrape {

	CURL* curl;
	CURLcode res;
	std::string readBuffer;
	std::string m_baseUrl;
	std::string m_currentChampionURL;

	std::map<char, std::string>utf_chart;
	std::map<char, int>utf_chart_cont;

	const char* m_championTierListURL = "https://u.gg/lol/top-lane-tier-list";
	//std::string m_summonerStatsURL = "https://na.op.gg/summoner/champions/userName=DomingoDuck";
	//std::string m_summonerStatsURL = "https://your.gg/na/profile/domingoduck";
	const char* m_summonerStatsURL = "https://your.gg/na/profile/DomingoDuck/match/3814748228";

	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

	void cleanStr(std::string& inputStr);
	

public:

	WebScrape();
	~WebScrape();

	
	std::string ScrapeHTML(std::string Scrapebuffer);
	std::string ProcessForYOURGG(std::string buffer);
	int ScrapeHTMLChampion(std::string & buffer);
	int BuildWebAddress(std::string m_championName);
	int BuildChampionTierList();
	int GetSummonerStats();


};


