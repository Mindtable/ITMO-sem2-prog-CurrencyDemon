#include <iostream>
#include "CurlGetter.h"
#include "Statistics.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <Windows.h>


int main()
{
	bool exitNeeded = false;
	using json = nlohmann::json;

	Statistics dollar("USD");
	Statistics euro("EUR");
	CurlGetter curl;

	std::thread thr([&exitNeeded]()
		{
			std::string input;
			while (std::cin >> input && input != "#");
			exitNeeded = true;
		});

	while(!exitNeeded)
	{
		std::string result;
		result = curl.getJSONstring("https://www.cbr-xml-daily.ru/daily_json.js");
		//result = curl.getJSONstring("http://api.currencylayer.com/live?access_key=dee259d7d6573750110a00338bc5dc07&currencies=RUB,EUR");

		json ValuteJSON = json::parse(result);

		//double eur = ValuteJSON["quotes"]["USDEUR"];
		//eur = ValuteJSON["quotes"]["USDRUB"] * (1 / eur);
		std::cout << "EURO: " << ValuteJSON["Valute"]["EUR"]["Value"] << std::endl;
		std::cout << "AMERICAN DOLLAR: " << ValuteJSON["Valute"]["USD"]["Value"] << std::endl;
		
		euro.insert(ValuteJSON["Valute"]["EUR"]["Value"]);
		dollar.insert(ValuteJSON["Valute"]["USD"]["Value"]);

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		system("cls");
	}
	thr.join();
	return 0;
}