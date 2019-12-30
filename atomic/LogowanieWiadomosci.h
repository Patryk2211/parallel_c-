#pragma once
#include <string>
#include <iostream>
#include <atomic>

class LogowanieWiadomosci
{
protected:
	LogowanieWiadomosci() {}

public:
	static LogowanieWiadomosci& instancja_klasy();

	LogowanieWiadomosci(LogowanieWiadomosci const&) = delete;
	LogowanieWiadomosci& operator= (LogowanieWiadomosci const&) = delete;

	void loguj(std::string message);

private:
	std::atomic_flag zamek = ATOMIC_FLAG_INIT;
};