#include "Klient.h"

Klient::Klient(int const no) : numer_klienta(no) {}

int Klient::pobierz_numer() const noexcept
{
	return numer_klienta;
}

bool operator<(Klient const & l, Klient const & r)
{
	return l.numer_klienta > r.numer_klienta;
}