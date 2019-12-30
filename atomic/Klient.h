#pragma once
#include <atomic>

class Klient
{
public:
	Klient(int const no);
	int pobierz_numer() const noexcept;

private:
	int number_klienta;
	friend bool operator<(Klient const & l, Klient const & r);
};