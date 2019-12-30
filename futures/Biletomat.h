#pragma once

class Biletomat
{
public:
	Biletomat(int const wartosc_poczatkowa);

	int nastepny_bilet();
private:
	int bilet;
};