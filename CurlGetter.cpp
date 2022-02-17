#include "CurlGetter.h"

static size_t
WriteMemoryCallback(void* contents, size_t size, size_t nmemb, std::string &userp)
{
	userp.append(static_cast<char*>(contents), size * nmemb);
	return size * nmemb;
}

CurlGetter::CurlGetter() 
{
	curl_global_init(CURL_GLOBAL_ALL);
}

CurlGetter::~CurlGetter()
{
	curl_global_cleanup();
}

std::string CurlGetter::getJSONstring(const std::string& URL)
{
	std::string result;

	/* Init curl session */
	m_CurlHandler = curl_easy_init();

	/* Set URL */
	curl_easy_setopt(m_CurlHandler, CURLOPT_URL, URL.c_str());

	/* Data writing callback */
	curl_easy_setopt(m_CurlHandler, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* Passing pointer to write destination */
	curl_easy_setopt(m_CurlHandler, CURLOPT_WRITEDATA, &result);

	/* Provide user agent field */
	curl_easy_setopt(m_CurlHandler, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	/* Get actual data */
	m_ResponceCode = curl_easy_perform(m_CurlHandler);

	curl_easy_cleanup(m_CurlHandler);

	if (m_ResponceCode != CURLE_OK) {
		std::cerr << "Error getting request" << std::endl;
		return "";
	}

	return result;
}

