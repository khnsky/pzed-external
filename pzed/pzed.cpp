#include "stdafx.h"

#include <cstdlib>
#include <iostream>

#include "CMemory.h"
#include "CProcess.h"
#include "CBhop.h"

// fajnie by było jakby się nie wyperdalało jak tylko cs nie jest odpalony
// exception handling z prawdziwego zdarzenia
// multithreading
// ustawienia
// glowesp
// trigger
// sigscanning / updatowanie offsetów

CProcess csgo;

int main(int argc, char* argv[])
{
	csgo.init(L"csgo.exe");
	bhop();

	return EXIT_SUCCESS;
}