#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

#include "CMemory.h"
#include "CProcess.h"
#include "CBhop.h"

// checking if csgo is still running, what happens if writing using handle to process not running?

// fajnie by było jakby się nie wyperdalało jak tylko cs nie jest odpalony
// nie wypierdala się nie wiem dlaczego, wydawało mi się że robi to na assercie

// exception handling z prawdziwego zdarzenia
// coś jest, okazuje się że exception specifiersy to zły pomysł

// multithreading
// ustawienia
// glowesp
// trigger
// sigscanning / updatowanie offsetów

CProcess process;

int main(int argc, char* argv[])
{
    while (true)
    {
        std::cout << "setting up csgo.exe process." << std::endl;
        if (process.init(L"csgo.exe", { L"client.dll", L"engine.dll" })) { break; }

        std::cout << "csgo.exe process did not set up correctly, retrying in 2 seconds." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "csgo process set up correctly." << std::endl;

	bhop();

	return EXIT_SUCCESS;
}