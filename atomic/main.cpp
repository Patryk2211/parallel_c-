#include <iostream>
#include <cstdio>
#include <ctime>
#include <thread>
#include <queue>
#include "Klient.h"
#include "LogowanieWiadomosci.h"
#include "Biletomat.h"


int main()
{

	std::clock_t start_zegara;
	double czas_trwania;
	start_zegara = std::clock();

	std::queue<Klient> klienci;
	bool biuro_otwarte = true;
	std::atomic<bool> atomowy_bool(false);
	//std::atomic_flag flaga_atomowa;

	std::vector<std::thread> biurka;
	for (int i = 1; i <= 3; ++i)
	{
		biurka.emplace_back([i, &atomowy_bool, /*&flaga_atomowa,*/ &biuro_otwarte, &klienci]() {

			LogowanieWiadomosci::instancja_klasy().loguj("desk " + std::to_string(i) + " open");

			while (biuro_otwarte || !klienci.empty())
			{
				while (!atomowy_bool)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
				}

				if (!klienci.empty()) 
				{
					//while (flaga_atomowa.test_and_set(std::memory_order_release));
					std::atomic<int> tmp;
					tmp.store(klienci.front().pobierz_numer(), std::memory_order_seq_cst);
					klienci.pop();

					std::atomic<int> tmp_size;
					tmp_size.store(klienci.size(), std::memory_order_seq_cst);

					LogowanieWiadomosci::instancja_klasy().loguj(
						"[-] desk " + std::to_string(i) + " handling customer "
						+ std::to_string(tmp.load()));

					LogowanieWiadomosci::instancja_klasy().loguj(
						"[=] queue size: " + std::to_string(tmp_size.load()));

					//flaga_atomowa.clear(std::memory_order_release);
					atomowy_bool = (!klienci.empty()) ? true : false;

					std::this_thread::sleep_for(
						std::chrono::seconds(2));

					LogowanieWiadomosci::instancja_klasy().loguj(
						"[ ] desk " + std::to_string(i) + " done with customer "
						+ std::to_string(tmp.load()));
				}
			}

			LogowanieWiadomosci::instancja_klasy().loguj("desk " + std::to_string(i) + " closed");
		});
	}

	std::thread bilety([&atomowy_bool, /*&flaga_atomowa,*/ &biuro_otwarte, &klienci]() {
		Biletomat tm(100);

		for (int i = 1; i <= 25; ++i)
		{
			Klient c(tm.nastepny_bilet());
			klienci.push(c);

			LogowanieWiadomosci::instancja_klasy().loguj("[+] new customer with ticket " +
				std::to_string(c.pobierz_numer()));
			LogowanieWiadomosci::instancja_klasy().loguj("[=] queue size: " +
				std::to_string(klienci.size()));

			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			atomowy_bool = true;
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