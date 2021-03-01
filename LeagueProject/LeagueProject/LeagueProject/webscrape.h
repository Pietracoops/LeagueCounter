#pragma once
	//WebScrape Class
	//Description:  This class is used to scrape the HTML files from u.gg
	//				For champion counter matchups
#define CURL_STATICLIB
#include<string>
#include <curl\curl.h>



class WebScrape {

	CURL* curl;
	CURLcode res;
	std::string readBuffer;
	std::string m_baseUrl;
	std::string m_currentChampionURL;


	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

public:

	WebScrape();
	~WebScrape();

	int ScrapeHTML(std::string & buffer);
	int BuildWebAddress(std::string m_championName);


};


