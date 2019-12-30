#include "Biletomat.h"

Biletomat::Biletomat(int const wartosc_poczatkowa) :
	bilet(wartosc_poczatkowa)
{}

int Biletomat::nastepny_bilet()
{
	return bilet++;
}