#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <assert.h>
#include <thread>
#include <cstdio>
#include <atomic>
#include <csignal>
#include "Printing.h"
#include "Executing.h"

std::vector<std::string> str = {
    "cancelling operation",
    "waiting operation",
    "blocking operation",
    "undefined operation",
    "success operation",
    "special operation"};
Timer clock1;
Printing p;
Operating o;
Executing e;

void signalHandler(int signal)
{
    p.stopShufflePrintThread();
    o.printOnExit();
    e.runMessage();
    p.setFirsTime();
    p.startShufflePrintThread(&str, &clock1);
    std::signal(SIGINT, signalHandler);
}

int main()
{
    e.runMessage();
    e.setStartingLogs(&str);
    std::signal(SIGINT, signalHandler); // handling ^C
    p.startShufflePrintThread(&str, &clock1);
    e.runMainLoop(&str, &clock1, &p, &o);
    return 1;
}






