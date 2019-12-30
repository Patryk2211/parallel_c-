#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <condition_variable>
#include <queue>
#include <cstdio>
#include <ctime>
#include <future>
#include "LogowanieWiadomosci.h"
#include "Biletomat.h"
#include "Klient.h"
#include <windows.h>

std::queue<Klient> bilety(int);
Klient bilet();
void biurko(int i, std::future<std::queue<Klient>>);
void biurkoDlaJednegoKlienta(std::future<Klient>);

int main()
{
	std::clock_t start_zegara;
	double czas_trwania;
	start_zegara = std::clock();

	auto klienci = std::async(std::launch::deferred, bilety, 25);
	//auto klient = std::async(std::launch::deferred, bilet);

	for (int i = 1; i <= 3; i++)
	{
		std::async(std::launch::async, biurko, i, std::move(klienci));
	}
	
	czas_trwania = (std::clock() - start_zegara) / (double)CLOCKS_PER_SEC;
	std::cout << "\n\nprintf: " << czas_trwania << '\n';

	getchar();
	return 0;
}

std::queue<Klient> bilety(int ilosc)
{
	Biletomat tm(100); 
	std::queue<Klient> klienci;

	for (int i = 1; i <= ilosc; ++i)
	{
		Klient c(tm.nastepny_bilet());
		klienci.push(c);

		LogowanieWiadomosci::instancja_klasy().loguj("[+] nowy klient z biletem numer: " +
			std::to_string(c.pobierz_numer()));
		LogowanieWiadomosci::instancja_klasy().loguj("[=] ilosc klientow w kolejce: " +
			std::to_string(klienci.size()));

		Sleep(200);
	}

	return klienci;
}

void biurko(int i, std::future<std::queue<Klient>> klienci)
{
	LogowanieWiadomosci::instancja_klasy().loguj("biurko " + std::to_string(i) + " otwarte");
	auto tmpKlient = klienci.get();

	while (!tmpKlient.empty())
	{
		auto const c = tmpKlient.front();
		tmpKlient.pop();


		LogowanieWiadomosci::instancja_klasy().loguj(
			"[-] biurko " + std::to_string(i) + " obsluguje klienta "
			+ std::to_string(c.pobierz_numer()));

		LogowanieWiadomosci::instancja_klasy().loguj(
			"[=] ilosc klientow w kolejce: " + std::to_string(tmpKlient.size()));

		Sleep(2000);

		LogowanieWiadomosci::instancja_klasy().loguj(
			"[ ] biurko " + std::to_string(i) + " obsluzylo klienta "
			+ std::to_string(c.pobierz_numer()));
	}

	LogowanieWiadomosci::instancja_klasy().loguj("biurko " + std::to_string(i) + " zamkniete");
}

void biurkoDlaJednegoKlienta(std::future<Klient> klient)
{
	LogowanieWiadomosci::instancja_klasy().loguj("biurko " + std::to_string(1) + " otwarte");
	auto tmpKlient = klient.get();

		auto const c = tmpKlient.pobierz_numer();


		LogowanieWiadomosci::instancja_klasy().loguj(
			"[-] biurko " + std::to_string(1) + " obsluguje klienta "
			+ std::to_string(c));

		LogowanieWiadomosci::instancja_klasy().loguj(
			"[=] ilosc klientow w kolejce: " + std::to_string(0));

		//Sleep(2000);

		LogowanieWiadomosci::instancja_klasy().loguj(
			"[ ] biurko " + std::to_string(1) + " obsluzylo klienta "
			+ std::to_string(c));

	LogowanieWiadomosci::instancja_klasy().loguj("biurko " + std::to_string(1) + " zamkniete");
}

Klient bilet()
{
	Biletomat tm(100);
	Klient klient;

		LogowanieWiadomosci::instancja_klasy().loguj("[+] nowy klient z biletem numer: " +
			std::to_string(klient.pobierz_numer()));
		LogowanieWiadomosci::instancja_klasy().loguj("[=] ilosc klientow w kolejce: " +
			std::to_string(1));

		//Sleep(200);

	return klient;
}