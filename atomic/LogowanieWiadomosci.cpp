#include "LogowanieWiadomosci.h"

LogowanieWiadomosci & LogowanieWiadomosci::instancja_klasy()
{
	static LogowanieWiadomosci lg;
	return lg;
}

void LogowanieWiadomosci::loguj(std::string message)
{
	while (zamek.test_and_set(std::memory_order_acquire));
	std::cout << "log: " << message << std::endl;
	zamek.clear(std::memory_order_release);
}
