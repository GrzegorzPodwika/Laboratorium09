#include "libExceptions.h"
#include <iostream>
using namespace std;

void seeExceptions(EXCEPTION_CODE error)
{
	switch (error) {
	case EXCEPTION_CODE::openError:
		cerr << "Blad otwarcia pliku odczytu";
		break;
	case EXCEPTION_CODE::readError:
		cerr << "Blad otwarcia pliku zapisu";
		break;
	case EXCEPTION_CODE::lackOfMemory:
		cerr << "Problem z alokacja miejsca";
		break;
	case EXCEPTION_CODE::notNaturalNumber:
		cerr << "Wystapienie liczby innej niz naturalna, ktora byla konieczna";
		break;
	default:
		cerr << "Nieznany blad";
		break;
	}
}
