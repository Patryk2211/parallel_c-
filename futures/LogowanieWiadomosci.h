#pragma once
#include <mutex>
#include <iostream>
#include <string>

class LogowanieWiadomosci
{
protected:
	LogowanieWiadomosci() {}

public:
	static LogowanieWiadomosci& instancja_klasy();

	LogowanieWiadomosci(LogowanieWiadomosci const&) = delete;
	LogowanieWiadomosci& operator= (LogowanieWiadomosci const&) = delete;

	void loguj(std::string wiadomosc);

private:
	std::mutex muteks;
};