#include <iomanip>
#include "Timer.h"

class Printing
{
public:
    void setMedoneFalse()
    {
        medone = false;
    }
    void setFirsTime()
    {
        firstTime = true;
    }
    void startShufflePrintThread(std::vector<std::string> *str,Timer<std::chrono::duration<int64_t, std::micro>, std::chrono::_V2::steady_clock> *clock1)
    {
        PrintingFuncFlag = true;
        std::thread(&Printing::RunPrintingFunc, this, &(*str), &(*clock1)).detach();
    }
    void stopShufflePrintThread()
    {
        PrintingFuncFlag = false;
    }

    void RunPrintingFunc(std::vector<std::string> *str,Timer<std::chrono::duration<int64_t, std::micro>, std::chrono::_V2::steady_clock> *clock1)
    {
        while (PrintingFuncFlag)
        {
            std::string leadingZerosMicrosString,leadingZerosMillisString;
            // randomly shuffle words
            std::random_device device;
            std::default_random_engine engine(device());
            std::shuffle(begin(*str), end(*str), engine);
            if (!firstTime)
            {
                auto time_elapsed = (*clock1).duration();
                auto h = std::chrono::duration_cast<std::chrono::hours>(time_elapsed);
                time_elapsed -= h;
                auto m = std::chrono::duration_cast<std::chrono::minutes>(time_elapsed);
                time_elapsed -= m;
                auto s = std::chrono::duration_cast<std::chrono::seconds>(time_elapsed);
                time_elapsed -= s;
                auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(time_elapsed);
                time_elapsed -= millis;
                auto micros = std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed);
                // next part is to display leading zeros in milli and micro seconds i.e "000022", not "022"
                auto leadingZerosMicros = micros.count();
                auto leadingZerosMillis = millis.count();
                if(leadingZerosMicros < 10)
                    leadingZerosMicrosString = "00" + std::to_string(leadingZerosMicros);
                else if(leadingZerosMicros < 100)
                    leadingZerosMicrosString = "0" + std::to_string(leadingZerosMicros);
                else
                    leadingZerosMicrosString = std::to_string(leadingZerosMicros);
                if(leadingZerosMillis < 10)
                    leadingZerosMillisString = "00" + std::to_string(leadingZerosMillis);
                else if(leadingZerosMillis < 100)
                    leadingZerosMillisString = "0" + std::to_string(leadingZerosMillis);
                else
                    leadingZerosMillisString = std::to_string(leadingZerosMillis);
                

                std::cout << "Last operation took: " << h.count() << ":" 
                << m.count() << ":" 
                << s.count() << "." 
                << leadingZerosMillisString 
                << leadingZerosMicrosString << 
                std::endl;
            }
            firstTime = false;
            std::cout << "Next operation is: " << (*str)[0] << std::endl;
            medone = true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    bool PrintingFuncFlag = true;
    std::atomic<int> medone = false;
    bool firstTime = true;
};