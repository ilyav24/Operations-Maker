#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include "Operating.h"

class Executing
{
public:
    void runMessage()
    {
        char input;
        while (input != 'Y' && input != 'N')
        {
            std::cout << std::endl << "Type Y / N." << std::endl;
            std::cout << "When running, use ^C to return to this message." << std::endl;
            std::cin >> input;
        }
        if (input == 'N')
        {
            exit(0);
        }
    }
    // set all .logs with starting times
    void setStartingLogs(std::vector<std::string> *str)
    {
        auto end = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        for (auto s : (*str))
        {
            std::ofstream outfile;
            std::string tmp = s + ".log";
            const char *name = tmp.c_str();
            outfile.open(name, std::ios_base::app);
            outfile << std::ctime(&end) << std::endl;
        }
    }
    void runMainLoop(std::vector<std::string> *str,Timer<std::chrono::duration<int64_t, std::micro>, std::chrono::_V2::steady_clock> *clock1, Printing *p, Operating *o)
    {
        while (1)
        {
            // wait for the next operation
            while (!((*p).medone))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            // measure time
            // run operation
            // block until next operation is chosen
            (*clock1).tick();
            (*o).RunOperationsMaker(&(*str));
            (*clock1).tock();
            (*p).setMedoneFalse();
        }
    }
};