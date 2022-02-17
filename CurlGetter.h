#pragma once

#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <iostream>

class CurlGetter
{
private:
	CURL* m_CurlHandler;
	CURLcode m_ResponceCode;

public:
	CurlGetter();
	~CurlGetter();
	std::string getJSONstring(const std::string& URL);
};