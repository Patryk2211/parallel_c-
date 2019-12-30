#pragma once

class Klient
{
public:
	Klient();
	Klient(int const no);
	int pobierz_numer() const noexcept;

private:
	int numer_klienta;
	friend bool operator<(Klient const & l, Klient const & r);
};