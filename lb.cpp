#include<iostream>
#include<fstream>
#include<string>

/**
// models contents of file 
class DataStorageManager()
{

}

// models stop word filter
class StopWordManager()
{

}

// keeps word frequency data
class WordFrequencyManager()
{

}
**/
class WordFrequencyController
{
    public:
        void dispatch(const std::string& input, const std::string& text)
        {
            if (input.compare("init") == 0)
            {
                std::cout << "nice\n";
            }
        }
};

int main(int argc, char** argv)
{
    WordFrequencyController wfcontroller;

    std::ifstream inFile( argv[1] );
    std::string strInput;

    // reads content from file into strInput
    while (inFile)
    {    
        std::getline(inFile, strInput);
    }

    wfcontroller.dispatch("init", strInput);
    //wfcontroller.dispatch(['run']);

    inFile.close();
    
    return 0;
}