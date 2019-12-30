#include "Biletomat.h"

Biletomat::Biletomat(int const ilosc) : bilet(ilosc) {}

int Biletomat::nastepny_bilet()
{
	return bilet++;
}