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
    for (int i = 0;; ++i)
    {
        std::cout << "setting up csgo.exe process." << std::endl;
        if (process.init(L"csgo.exe")) { break; }

        for (int wait = i * 2; 0 <= wait; --wait)
        {
            std::cout << "csgo.exe process did not set up correctly, retrying in "
                << wait << " seconds." << '\r' <<std::flush;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << std::endl;
    }
    std::cout << "csgo process set up correctly." << std::endl;

	bhop();

	return EXIT_SUCCESS;
}