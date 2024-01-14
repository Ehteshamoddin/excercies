/* #include <bits/stdc++.h>
using namespace std;

int main()
{
    string sentence;
    cout << "Enter a long sentence (up to 300 characters): ";
    getline(cin, sentence);

    map<char, int> frequencyMap;

    // Counting occurrence frequency
    for (char ch : sentence)
    {
        if (isalnum(ch))
        {
            frequencyMap[ch]++;
        }
    }

    for (char ch = 'a'; ch <= 'z'; ++ch)
    {
        if (frequencyMap.find(ch) != frequencyMap.end())
        {
            cout << ch << ": ";
            for (int i = 0; i < frequencyMap[ch]; ++i)
            {
                cout << '|';
            }
            cout << '\n';
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ++ch)
    {
        if (frequencyMap.find(ch) != frequencyMap.end())
        {
            cout << ch << ": ";
            for (int i = 0; i < frequencyMap[ch]; ++i)
            {
                cout << '|';
            }
            cout << '\n';
        }
    }

    for (char ch = '0'; ch <= '9'; ++ch)
    {
        if (frequencyMap.find(ch) != frequencyMap.end())
        {
            cout << ch << ": ";
            for (int i = 0; i < frequencyMap[ch]; ++i)
            {
                cout << '|';
            }
            cout << '\n';
        }
    }

    // vector<pair<char, int>> sortedFrequency(frequencyMap.begin(), frequencyMap.end());
    // // Sort the vector based on character
    // sort(sortedFrequency.begin(), sortedFrequency.end(), [](auto &a, auto &b) {
    //     return a.first < b.first;
    // });

    // cout << "\nSorted Frequencies:\n";
    // for (const auto &entry : sortedFrequency)
    // {
    //     cout << entry.first << ": ";
    //     for (int i = 0; i < entry.second; ++i)
    //     {
    //         cout << '|';
    //     }
    //     cout << '\n';
    // }

    return 0;
} */

// working 1
#include <bits/stdc++.h>

#include <iomanip>
#ifdef TIOCGWINSZ
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

int main()
{
    string sentence;
    cout << "Enter a sentence (up to 300 characters): ";
    getline(cin, sentence);

    unordered_map<char, int> frequencies;
    for (char c : sentence)
    {
        if (isalnum(c))
        {
            frequencies[tolower(c)]++;
        }
    }

    // Get terminal width
    int term_width = 100; // Default if detection fails
#ifdef TIOCGWINSZ
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (w.ws_col > 0)
    {
        term_width = w.ws_col;
    }
#endif

    // Sort characters alphabetically
    vector<pair<char, int>> sorted_freq(frequencies.begin(), frequencies.end());
    sort(sorted_freq.begin(), sorted_freq.end());

    for (const auto &entry : sorted_freq)
    {
        int count = entry.second;

        // Print only if count > 0
        if (count > 0)
        {
            cout << entry.first << " - ";

            // Print bars, compacting excess with an asterisk
            int bars_to_print = min(count, term_width);
            cout << setw(bars_to_print) << setfill('|') << "" << setfill(' '); // Print bars using setw()
            if (count > term_width)
            {
                cout << " + " << (count - term_width);
            }

            cout << endl;
        }
    }

    return 0;
}
