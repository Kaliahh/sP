#include <iostream>
#include <functional>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

std::vector<std::string> read_wordle_js(std::istream&& is)
{
    std::vector<std::string> words;
    auto word = std::string{};
    while (is) { // check for EOF and potential I/O errors
        if (is.peek() == '"') { // look for an opening quote
            is >> std::quoted(word); // read the word in quotes and remove quotes
            if (word.length() == 5 && // must be 5-letter word
                std::all_of(std::cbegin(word), std::cend(word), // all lower-case letters
                            [](char c) { return std::isalpha(c) && std::islower(c); }))
                words.push_back(word);
        } else
            is.get(); // skip one character
    }
    std::sort(std::begin(words), std::end(words));
    words.erase(std::unique(std::begin(words), std::end(words)), words.end());
    for (auto& item : words) {
        transform(item.begin(), item.end(), item.begin(), ::toupper);
    }
    return words;
}


bool decideOn(const char& c, const vector<string>& pattern, int index) {



//    if (pattern[0] == '-' && pattern[1] == c) {
//        return false;
//    }
//    else if (pattern[0] == '+' && pattern[1] == c) {
//        return true;
//    }
//    else {
//        return true;
//    }
}

vector<string> convertPattern(const string& pattern) {
    vector<string> result;

    for (int i = 0; i < pattern.size(); i++) {
        if (ispunct(pattern[i])) {
            string temp;
            temp.push_back(pattern[i]);
            temp.push_back(pattern[i + 1]);
            i++;
            result.push_back(temp);
        }
        else {
            result.emplace_back(1, pattern[i]);
        }
    }

    return result;
}

std::vector<std::string> filter(std::vector<std::string>&& words, const std::string& pattern) {

    int i = 0;
    int pos = 0;

    while (i < pattern.size()){
        // The letter is in the correct place
        if (isalpha(pattern[i])) {
            auto it = remove_if(
                                words.begin(),
                                words.end(),
                                [pos, c=pattern[i]](const string& s) -> bool { return s[pos] != c; }
                                );

            words.erase(it, words.end());
            i++;
            pos++;
        }
        // The letter is in the word, but not in the correct place
        else if (pattern[i] == '+' && i + 1 < pattern.length() && isalpha(pattern[i + 1])) {
            i++;
            auto it = remove_if(
                    words.begin(),
                    words.end(),
                    [pos, c=pattern[i]](const string& s) -> bool {
                        return s[pos] == c // We don't want it in this place
                        || find(s.begin(), s.end(), c) == s.end(); // But we want it somewhere in the string
                        // If it is in place or not in the string, we remove the string.
                    }
                    );

            words.erase(it, words.end());
            i++;
            pos++;
        }
        // The letter is not in the word
        else if (pattern[i] == '-' && i + 1 < pattern.length() && isalpha(pattern[i + 1])) {
            i++;
            auto it = remove_if(
                    words.begin(),
                    words.end(),
                    [c = pattern[i]](const string& s) -> bool {
                        return find(s.begin(), s.end(), c) != s.end();
                    }
                    );
            words.erase(it, words.end());
            i++;
            pos++;
        }
    }

    return std::move(words);
}

bool sanitize(const string& guess) {

//    return all_of(guess.begin(), guess.end(), [](char c) -> bool {
//        return (isalpha(c) && isupper(c)) || c == '+' || c == '-';
//    } );
    return regex_match(guess, std::regex{"[+-]?[A-Z][+-]?[A-Z][+-]?[A-Z][+-]?[A-Z][+-]?[A-Z]"});
}

int main()
{
    auto fileStream = ifstream{"/home/ane/Documents/GitHub/sP/Session-3/database"};
    const auto database = read_wordle_js(std::move(fileStream));/* read the database from the javascript file */
    auto words = database; // make a copy of the database

    auto guess = std::string{}; // allocate memory to store guess patterns
    while (words.size() > 1) {
        std::cout << words.size() << " words remaining\n";
        bool good = true;
        do {
            std::cout << "Enter a guess pattern: ";
            std::cin >> guess;
//            guess = "-C+RA-N-E";
            good = sanitize(guess);
            /* sanitize: set good to false if input fails to follow the pattern */
        } while (!good);
        /* apply the filter on the words */
        /* pick and announce one of the words for the user to try */

        words = filter(std::move(words), guess);

        cout << "Try " << words[0] << endl;
    }
    if (words.size() == 1) {
        std::cout << "Congratulations: " << words.front() << "\n";
    } else {
        std::cerr << "Something got messed up :-(\n";
    }
}

/**

class Test {
public:
    int myInt;

    int operator+(const Test& other) {
        return myInt + other.myInt;
    }

    explicit Test(int a) {
        myInt = a;
        cout << "The constructor has been run" << endl;
    }
    void Something() {
        cout << "Test" << endl;
    }
};

void classTestReference(Test& test) {
    test.Something();
    test.myInt += 1;
    cout << test.myInt << endl;
}

void classTestValue(Test test) {
    test.Something();
    test.myInt += 1;
    cout << test.myInt << endl;
}

void classTest() {
    auto test = Test{5};

    test.myInt += 1;

    cout << test.myInt << endl;

    classTestReference(test);

    cout << test.myInt << endl;

    classTestValue(test);

    cout << test.myInt << endl;

    auto test2 = Test{300};

    cout << test + test2 << endl;
}

void lambdaPassTest(const std::function<int (int)>& f) {
    cout << f(5) << endl;
}

void lambdaTest() {
    int a{3};

    auto f1 = [=](int x) mutable {a = 0; return x + a;};

    lambdaPassTest(f1);

    cout << a << endl;

//    cout << f1(1) << endl;
}


void consume(vector<int>&& test) {
    for (auto& item : test) {
        item += 1;
        cout << item << ", ";
    }
    cout << endl;
}

void moveTest() {
    vector<int> list{1, 2, 3, 4};

    consume(move(list));

//    consume(list);

    for (auto item : list) {
        cout << item << ", ";
    }
    cout << endl;
}


int main() {
//    lambdaTest();
//    moveTest();
//    classTest();
    return 0;
}

 */

