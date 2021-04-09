#pragma once

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#pragma comment(lib, "cpprest_2_10")

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

#define TRACE(msg)            wcout << msg
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"

map<utility::string_t, utility::string_t> dictionary;


class RESTServer {

	void display_json(json::value const& jvalue, utility::string_t const& prefix);
	void handle_get(http_request request);
	void handle_request(http_request request, function<void(json::value const&, json::value&)> action);
	void handle_post(http_request request);
	void handle_put(http_request request);
	void handle_del(http_request request);

public:
	RESTServer();
	~RESTServer();

	void Launch();
};