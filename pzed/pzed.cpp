#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

#include "CMemory.h"
#include "CProcess.h"
#include "CBhop.h"
#include "Offsets.h"

// checking if csgo is still running, what happens if writing using handle to process not running?

// csgo as global Process variable is bad idea, only for now,
// later cs will be member of settings class or maybe cheat module base class

// better exception handling, are there any places that could leak handles etc.
// multithreading
// ustawienia
// glowesp
// trigger
// sigscanning / updatowanie offsetów

CProcess process;

int main(int argc, char* argv[])
{
    for (;;)
    {
        std::cout << "setting up csgo.exe process." << std::endl;
        if (process.init("csgo.exe", { "client.dll", "engine.dll" })) { break; }

        // maybe extend wait between each try everytime it fails?
        std::cout << "csgo.exe process did not set up correctly, retrying in 2 seconds." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "csgo process set up correctly." << std::endl;

	bhop();

	return EXIT_SUCCESS;
}