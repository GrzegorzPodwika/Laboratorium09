#pragma once

enum EXCEPTION_CODE
{
	openError,
	readError,
	lackOfMemory,
	notNaturalNumber
};


/*Wyœwietla zaistnia³e wyj¹tki*/
void seeExceptions(EXCEPTION_CODE error);
