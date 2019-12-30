#pragma once
#include <atomic>

class Biletomat
{
public:
	Biletomat(int const);

	int nastepny_bilet();
private:
	int bilet;
};