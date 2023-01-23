#include "main.hpp"
using namespace std;

// models contents of files
class DataStorageManager {
    private:
        vector<string> word_list{};
    
    public:
        // convert to lowercase and remove punctuation then store in word_list vector
        DataStorageManager(string text) {
            text.erase (::remove_if(text.begin (), text.end (), ::ispunct), text.end ());
            /**regex regex("[^a-zA-Z]+");
            vector<string> read_text(
                sregex_token_iterator(text.begin(), text.end(), regex, -1), 
                sregex_token_iterator()
            ); **/
            ::transform(text.begin(), text.end(), text.begin(), [](unsigned char c){ return ::tolower(c); });

            string buf;
            stringstream ss(text);

            while(getline(ss, buf, ' '))
                word_list.push_back(buf);
        }

        // returns list of words in storage
        vector<string> getWordList() { return word_list; }

};

// models stop word filter
class StopWordManager {
    private:
        vector<string> stop_words{};
    public:
        // reads stop words from file and stores into stop_words vector
        StopWordManager() {
            ifstream file("stop_words.txt");
            stringstream buffer;
            buffer << file.rdbuf();
            string read_words = buffer.str();

            string buf;
            stringstream ss(read_words);

            while(getline(ss, buf, ','))
                stop_words.push_back(buf);
        }

        bool is_stop_word(string word) {
            for (string stop_word : stop_words) {
                if (word.compare(stop_word) == 0) {
                    return true;
                }
            }
            return false;
        }
};

// keeps word frequency data
class WordFrequencyManager {
    private:
        map<string, int> word_freq;
    
    public:
        // increment freq count if word is in dictionary, otherwise add with value 1
        void increment_count(string word) {
            bool found = false;

            for (auto const& [key_word, freq] : word_freq) {
                if (key_word.compare(word) == 0) {
                    word_freq[key_word]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                word_freq[word] = 1;
            }
        }

        map<string, int> getWordFreq() { return word_freq; };

        void sorted() {

        }
};

// instantiates manager classes and runs their methods
class WordFrequencyController {
    public:
        // if word in storage != stopword, then increment
        // print results at the end
        void run(string input) {
            DataStorageManager dsmanager = DataStorageManager(input);
            StopWordManager swmanager;
            WordFrequencyManager wfmanager;

            for (string word : dsmanager.getWordList()) {
                if (!swmanager.is_stop_word(word)) {
                    wfmanager.increment_count(word);
                }
            }

            // todo: sort
            // correct freq count and display
            for (auto const& [key_word, freq] : wfmanager.getWordFreq()) {
                cout << key_word << " - " << freq << '\n';
            }
        }
};

int main(int argc, char** argv)
{
    std::ifstream inFile( argv[1] );

    // copies file content into string
    stringstream buffer;
    buffer << inFile.rdbuf();
    string strInput = buffer.str();

    WordFrequencyController wfcontroller;
    wfcontroller.run(strInput);

    inFile.close();
    
    return 0;
}