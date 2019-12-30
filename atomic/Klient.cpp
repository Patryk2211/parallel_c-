#include "Klient.h"

Klient::Klient(int const no) : number_klienta(no) {}

int Klient::pobierz_numer() const noexcept
{
	return number_klienta;
}

bool operator<(Klient const & l, Klient const & r)
{
	return l.number_klienta > r.number_klienta;
}