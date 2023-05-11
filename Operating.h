

class Operating
{
public:
    int countBlock = 0, countSuccess = 0;
    double countSpecial = 0, countTotal = 0;

    void RunOperationsMaker(std::vector<std::string> *str)
    {
        countTotal++;
        // main operation logs
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::ofstream outfile;
        std::string tmp = (*str)[0] + ".log";
        const char *name = tmp.c_str();
        outfile.open(name, std::ios_base::app);
        outfile << std::ctime(&now);

        // print a line of the number of times blocking/success operations ran
        if ((*str)[0] == "blocking operation") 
        {
            (countBlock)++;
        }
        if ((*str)[0] == "success operation")
        {
            (countSuccess)++;
        }
        if ((*str)[0] == "special operation")
        {
            countSpecial++;
        }
    }
    // on exit, print a line of the number of times blocking/success operations ran
    void printOnExit()
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::ofstream outfile;
        const char *name = "block.log";
        outfile.open(name, std::ios_base::app);
        outfile << countBlock << " " << std::ctime(&now);

        std::ofstream outfile1;
        const char *name1 = "success.log";
        outfile1.open(name1, std::ios_base::app);
        outfile1 << countSuccess << " " << std::ctime(&now);

        if (countTotal != 0)
        {
            std::ofstream outfile2;
            const char *name2 = "special.log";
            outfile2.open(name2, std::ios_base::app);
            outfile2 << std::fixed << std::setprecision(2);
            outfile2 << (countSpecial / countTotal) << " " << std::ctime(&now);
        }
        countBlock = 0;
        countSuccess = 0;
    }
};