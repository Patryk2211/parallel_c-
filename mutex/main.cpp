#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <condition_variable>
#include <queue>
#include <cstdio>
#include <ctime>
#include "LogowanieWiadomosci.h"
#include "Biletomat.h"
#include "Klient.h"


int main()
{
	std::clock_t start_zegara;
	double czas_trwania;

	start_zegara = std::clock();

	std::queue<Klient> klienci;
	bool biuro_otwarte = true;
	std::mutex muteks;
	std::condition_variable zmienna_warunkowa;

	std::vector<std::thread> biurka;
	for (int i = 1; i <= 3; ++i)
	{
		biurka.emplace_back([i, &biuro_otwarte, &muteks, &zmienna_warunkowa, &klienci]() {

			LogowanieWiadomosci::instancja_klasy().loguj("biurko " + std::to_string(i) + " otwarte");

			while (biuro_otwarte || !klienci.empty())
			{
				std::unique_lock<std::mutex> locker(muteks);

				zmienna_warunkowa.wait_for(locker, std::chrono::seconds(1),
					    [&klienci]() { return !klienci.empty(); }
				);

				if (!klienci.empty())
				{
					auto const c = klienci.front();
					klienci.pop();

					LogowanieWiadomosci::instancja_klasy().loguj(
						"[-] biurko " + std::to_string(i) + " obsluguje klienta "
						+ std::to_string(c.pobierz_numer()));

					LogowanieWiadomosci::instancja_klasy().loguj(
						"[=] ilosc klientow w kolejce: " + std::to_string(klienci.size()));

					locker.unlock();
					zmienna_warunkowa.notify_one();

					std::this_thread::sleep_for(
						std::chrono::seconds(2));

					LogowanieWiadomosci::instancja_klasy().loguj(
						"[ ] biurko " + std::to_string(i) + " obsluzylo klienta "
						+ std::to_string(c.pobierz_numer()));
				}
			}

			LogowanieWiadomosci::instancja_klasy().loguj("biurko " + std::to_string(i) + " zamkniete");
		});
	}

	std::thread bilety([&biuro_otwarte, &klienci,
		                &muteks, &zmienna_warunkowa]() {
		Biletomat tm(100);

		for (int i = 1; i <= 25; ++i)
		{
			Klient c(tm.nastepny_bilet());
			klienci.push(c);

			LogowanieWiadomosci::instancja_klasy().loguj("[+] nowy klient z biletem numer: " +
				std::to_string(c.pobierz_numer()));
			LogowanieWiadomosci::instancja_klasy().loguj("[=] ilosc klientow w kolejce: " +
				std::to_string(klienci.size()));

			zmienna_warunkowa.notify_one();

			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		biuro_otwarte = false;
	});

	bilety.join();
	for (auto & desk : biurka) desk.join();

	czas_trwania = (std::clock() - start_zegara) / (double)CLOCKS_PER_SEC;
	std::cout << "\n\nprintf: " << czas_trwania << '\n';

	getchar();
	return 0;
}