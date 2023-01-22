#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<cctype>

// models contents of file 
class DataStorageManager
{
    private:
        std::vector<std::string> message;
        std::string data = "";

        // convert to lowercase and remove punctuation + store in data
        void init(std::string message)
        {
            message.erase (std::remove_if(message.begin (), message.end (), ispunct), message.end ());
            std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c){ return std::tolower(c); });
            this->data = message;
        }

        void words() 
        {
            
        }

    public:
        void dispatch(std::vector<std::string> message)
        {
            if (message[0].compare("init") == 0)
                return this->init(message[1]);

            else if (message[0].compare("words") == 0)
                return this->words();

            else
                std::cout << "Message not understood: " << message[0] << "." << "\n";
        }
};

// models stop word filter
class StopWordManager
{
    private:
        std::vector<std::string> message;
        std::vector<std::string> stop_words{};

        // reads stop words from file and stores into stop_words vector
        void init()
        {
            std::ifstream file( "stop_words.txt" );
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string read_words = buffer.str();

            std::string buf;
            std::stringstream ss(read_words);

            while (getline(ss, buf, ','))
                stop_words.push_back(buf);
        }

        void is_stop_word(std::string message){}

    public:
        void dispatch(std::vector<std::string> message)
        {
            if (message[0].compare("init") == 0)
                return this->init();

            else if (message[0].compare("is_stop_word") == 0)
                return this->is_stop_word(message[1]);

            else
                std::cout << "Message not understood: " << message[0] << "." << "\n";
        }
};

// keeps word frequency data
class WordFrequencyManager
{
    private:
        std::vector<std::string> message;

        void increment_count(std::string message){}
        void sorted(){}

    public:
        void dispatch(std::vector<std::string> message)
        {
            if (message[0].compare("increment_count") == 0)
                return this->increment_count(message[1]);

            else if (message[0].compare("sorted") == 0)
                return this->sorted();

            else
                std::cout << "Message not understood: " << message[0] << "." << "\n";
        }
};

class WordFrequencyController
{
    private:
        std::vector<std::string> input;

        DataStorageManager dsmanager;
        StopWordManager swmanager;
        WordFrequencyManager wfmanager;

        void init(std::string file)
        {
            dsmanager.dispatch({"init", file});
            swmanager.dispatch({"init"});
        }

        void run()
        {
            for(auto const& i : dsmanager.dispatch({"words"}))
                std::cout << i << "\n";
        }

    public:
        void dispatch(std::vector<std::string> input)
        {
            if (input[0].compare("init") == 0)
                return this->init(input[1]);

            else if (input[0].compare("run") == 0)
                return this->run();

            else
                std::cout << "Message not understood: " << input[0] << "." << "\n";
        }
};

int main(int argc, char** argv)
{
    WordFrequencyController wfcontroller;

    std::ifstream inFile( argv[1] );

    // copies file content into string
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string strInput = buffer.str();

    wfcontroller.dispatch({"init", strInput});
    wfcontroller.dispatch({"run"});

    inFile.close();
    
    return 0;
}
