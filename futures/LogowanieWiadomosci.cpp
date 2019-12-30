#include "LogowanieWiadomosci.h"

LogowanieWiadomosci &LogowanieWiadomosci::instancja_klasy()
{
	static LogowanieWiadomosci logowanie;
	return logowanie;
}

void LogowanieWiadomosci::loguj(std::string wiadomosc)
{
	std::lock_guard<std::mutex> lock(muteks);
	std::cout << "log: " << wiadomosc << std::endl;
}