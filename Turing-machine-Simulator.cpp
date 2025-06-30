// Turing Machine For String Manipulation

/*
Group Members :
Ali Mobin (23K-0622)
Taaha Khan (23K-0583)
Usman Ahmed (23K-0820)
*/

#include <bits/stdc++.h>
// 1)  String Concatenation
// 2)  Palindrome Checker
// 3)  Anagram Checker
// 4)  String Reversal
// 5)  Count Characters
// 6)  Trim Spaces
// we will be implementing Turing Machine
using namespace std;
vector<char> Tape;
int k = 1;
class TuringMachine
{
    string str, str1;
    string state;
    char alpha1, alpha2;
    int k;

public:
    TuringMachine()
    {
        state = "";
        str = "";
        k=1;
    }

    void Concatenate()
    {
        k=1;
        cout << "Enter language of two alphabet : "; // 2 symbol based charcter set input
        cin >> alpha1 >> alpha2;

        while (alpha1 == alpha2) // Check for redunandt alphabets
        {
            cout << "Enter language of two alphabet : ";
            cin >> alpha1 >> alpha2;
        }
        cout << "Enter string 1 : "; // string 1 input
        cin >> str;

        for (int i = 0; i < str.length(); i++)
        { // Verification of grammar of string 1
            if (str[i] != alpha1 && str[i] != alpha2)
            {
                cout << "Incorrect string grammar: " << endl;
                return;
            }
        }

        cout << "Enter String 2 : "; // string 2 input
        cin >> str1;

        for (int i = 0; i < str1.length(); i++)
        { // Verification of grammar of string 2
            if (str1[i] != alpha1 && str1[i] != alpha2)
            {
                cout << "Incorrect string grammar: " << endl;
                return;
            }
        }

        Tape.clear(); // Clearing the tape for handling new function

        Tape.push_back('B'); // B for balnk cell at the start
        for (char c : str)   // string 1 being written on tape
        {
            Tape.push_back(c);
        }
        Tape.push_back('#'); // String seperator symbol
        for (char c : str1)  // string 2 being written on tape
        {
            Tape.push_back(c);
        }
        Tape.push_back('B'); // B for balnk cell at the end

        int head = 1; // read-write head set to the begining charcter of string 1
        display_tape(head);

        while (Tape[head] != '#') // Traverse the tape until seperator symbol is encountered
        {
            head++; // Move read-write head right
            display_tape(head);
        }

        char temp; // For storing something read from the tape which
        //  is to be written back on the tape

        while (Tape[head] != 'B') // Continue left shift cell by cell until B
        //  (The blank cell marking the end of tape) is encounterd
        {
            head++;            // move the read-write head right
            temp = Tape[head]; // store the read symbol
            display_tape(head);
            head--;            // move read-write head left
            Tape[head] = temp; // replace the symbol by writng the previously read symbol
            display_tape(head);
            head++; // move read-write head right again
            display_tape(head);
        }

        return;
    }

    void PalindromeChecker()
    {
        k=1;
        cout << "Enter language of two alphabet : "; // 2 symbol based charcter set input
        cin >> alpha1 >> alpha2;

        while (alpha1 == alpha2) // Check for redundtant alphabets
        {
            cout << "Enter language of two alphabet : ";
            cin >> alpha1 >> alpha2;
        }
        cout << "Enter string to check for palindrome: ";
        cin >> str;

        for (int i = 0; i < str.length(); i++)
        { // Verifcation of string grammar
            if (str[i] != alpha1 && str[i] != alpha2)
            {
                cout << "Incorrect string grammar: " << endl;
                return;
            }
        }

        Tape.clear(); // Clearing the tape for perfoming the new functionality
        int head = 1; // Set read-write head to the start of the input string

        Tape.push_back('B'); // First cell of tape is initialized as blank B
        for (char c : str)   // read-write head writes each charcter of user input string and moves rightward
        {
            Tape.push_back(c);
        }
        Tape.push_back('B'); // Last cell of tape is initialized as blank B

        if (Tape.size() % 2 != 0) // If the string if of odd length we mark the center character with 'Z'
        // This prevents the midle of the string from being altered during palindrome comparisons
        {
            head = (Tape.size() + 1) / 2 - 1;
            Tape[head] = 'Z';
            head = 1;
        }

        string state = "q0"; // Setting up the start state
        char temp;           // For holding the tape charcter that we are to use for palindrome comparisions

        while (true)
        {

            if (state == "q0") // Frontward symbol reader and replacer state
            {
                if (Tape[head] == alpha1) // If it is the first user inputted alphabet we replace it by  X
                {
                    Tape[head] = 'X'; // Write X denoting the cell has been read and will not be further considered
                    temp = alpha1;    // Store the read symbol which will be used later for palindrom comparision
                    state = "q1";     // State transiton to q1
                }
                else if (Tape[head] == alpha2) // If it is the second user inputted alphabet we replace it by Y
                {
                    Tape[head] = 'Y'; // Write Y denoting the cell has been read and will not be further considered
                    temp = alpha2;    // Store the read symbol which will be used later for palindrom comparision
                    state = "q1";     // State transiton to q1
                }
                else
                {
                    state = "q_accept"; // If it is not one of the user inputted characters then we have successfully
                    // compared all charcters and hence it is a palindrom. We transiton to the accept state.
                }
                head++;
                display_tape(head);
            }

            else if (state == "q1") // Rightward moving state for reaching the backward comparision character
            {
                while (Tape[head] != 'B' && Tape[head] != 'X' && Tape[head] != 'Y')
                // Continue on moving rightward. This is dine for reaching the last readable symbol
                {
                    head++; // Move read-write head right
                    display_tape(head);
                }
                head--; // Move read-write head left to the desired readable symbol
                display_tape(head);
                state = "q2"; // State transiton to q2
            }

            else if (state == "q2") // state for checking whethe rthe strinh has been entirely checked dor not
            {
                while (Tape[head] == 'X' || Tape[head] == 'Y') // For checking if there remains any readable cell or not
                {
                    head--; // Move read-write head left
                    display_tape(head);
                }

                if (Tape[head] == 'B') // if the read-write head is pointing to blank cell we have performed all comparisions
                    state = "q_accept";
                else
                    state = "q3"; // Transiton to q3
            }

            else if (state == "q3") // Palindrome comparision state
            {
                if (Tape[head] != temp && Tape[head] != 'Z') // vif comaprision was unsuccessful we transiton to q_reject
                    state = "q_reject";

                else if (Tape[head] == 'Z') // else if the read-write head is pointing to the middle we transiton to q_accept as all comparisons have been performed
                    state = "q_accept";

                else // else we have more compariosn to perform and the current comparion was successful.
                {
                    if (Tape[head] == alpha1)
                        Tape[head] = 'X';
                    else if (Tape[head] == alpha2)
                        Tape[head] = 'Y';

                    state = "q4"; // Transition to q4
                    head--;       // Move read-write head left
                }

                display_tape(head);
            }

            else if (state == "q4") // Leftward moving state for reaching the next forward charcter to compare
            {
                while (Tape[head] != 'X' && Tape[head] != 'Y')
                {
                    head--; // Move read-write head left
                    display_tape(head);
                }

                head++; // Move read-write head right
                display_tape(head);

                if (Tape[head] == 'Z')
                    state = "q_accept"; // Transiton to state q_accept as no more compariosn are needed to be performed
                else
                    state = "q0"; // Transiton back to start state q0 as more compariosn are needed to be performed
            }

            else if (state == "q_reject") // Rejecting state
            {
                cout << "* OUTPUT *" << endl;
                cout << "Not a palindrome" << endl;
                break;
            }

            else if (state == "q_accept") // Accepting state
            {
                cout << "* OUTPUT *" << endl;
                cout << "It is a palindrome" << endl;
                break;
            }
        }
        return;
    }

    bool AnagramChecker()
    {
k=1;
        cout << "Enter language of two alphabet : "; // taking input
        cin >> alpha1 >> alpha2;

        while (alpha1 == alpha2) // Keep asking until two different alphabets are entered
        {
            cout << "Enter language of two alphabet : ";
            cin >> alpha1 >> alpha2;
        }

        // input
        cout << "Enter stirng 1 : ";
        cin >> str;
        cout << "Enter String 2  :";
        cin >> str1;

        Tape.clear();
        for (char c : str)
        {
            Tape.push_back(c); // Add first string characters to the tape
        }

        // Put '#' between the two strings on the tape
        Tape.push_back('#');

        for (char c : str1)
        {
            Tape.push_back(c); // Add second string characters to the tape
        }

        Tape.push_back('B'); // Add 'B' to mark end of tape

        int head = 0;                            // Head starts from beginning
        pair<string, char> state = {"q0", '\0'}; // Start state q0 and empty char

        while (true)
        {
            display_tape(head); // Show tape

            if (state.first == "q0")
            {
                // If character is not special symbol
                if (Tape[head] != '#' && Tape[head] != '*' && Tape[head] != 'B')
                {
                    state.second = Tape[head]; // Save current letter
                    Tape[head] = '*';          // Mark it as used
                    display_tape(head);
                    state.first = "q1"; // Go to next state

                    // Move to second part of tape after #
                    while (Tape[head] != '#')
                    {
                        head++;
                    }
                    head++; // Move after '#'
                    while (Tape[head] == '*')
                    {
                        head++; // Skip already matched symbols
                    }
                }
                else if (Tape[head] == '#')
                {
                    head++;
                    state.first = "q2"; // Move to final checking state
                }
                else
                {
                    head++;
                }
            }
            else if (state.first == "q1")
            {
                // Try to find matching letter in second part
                if (Tape[head] == state.second)
                {
                    Tape[head] = '*'; // Mark matched letter
                    display_tape(head);
                    state = {"q0", '\0'}; // Go back to q0
                    head = 0;             // Start again from beginning
                }
                else if (Tape[head] == 'B')
                {
                    return false; // Reached end without match
                }
                else
                {
                    head++;
                }
            }
            else if (state.first == "q2")
            {
                if (Tape[head] == '*') // Skip all matched symbols
                {
                    head++;
                }
                else if (Tape[head] == 'B')
                {
                    return true; // All letters matched — it's an anagram
                }
                else
                {
                    return false; // Found unmatched letter
                }
            }
        }
    }

    void StringReversal()
    {
        k=1;
        // Input of language
        cout << "Enter language of two alphabets: ";
        cin >> alpha1 >> alpha2;
        while (alpha1 == alpha2)
        {
            cout << "Both alphabets must be different. Enter again: "; // Exclusivity checker
            cin >> alpha1 >> alpha2;
        }

        // Taking string input
        cout << "Enter string: ";
        cin >> str;

        Tape.clear();
        Tape.push_back('#'); // Starting delimiter
        // Write string to tape
        for (char c : str)
        {
            Tape.push_back(c);
        }
        Tape.push_back('#'); // Ending delimiter
        int head = 1;        // Start after first '#'
        char temp;
        string state = "q0";

        while (state != "B") // Final halting state
        {
            if (state == "q0")
            {

                while (Tape[head] != '#') // Move head to the end (before last '#')
                {
                    head++;
                }
                head--;
                display_tape(head);
                state = "q1";
            }

            else if (state == "q1")
            {
                while (Tape[head] == 'X') // Find next unprocessed character from end
                {
                    head--;
                }
                if (Tape[head] == '#') // All characters processed
                {
                    head++;
                    state = "qf"; // Final state
                }
                else if (Tape[head] == alpha1 || Tape[head] == alpha2)
                {
                    temp = Tape[head]; // Save character
                    Tape[head] = 'X';  // Mark as processed
                    state = "q2";      // Go to insertion state
                }
                display_tape(head);
            }

            else if (state == "q2")
            {

                while (Tape[head] != '#') // Move head to the right end of tape
                {
                    head++;
                }
                Tape.insert(Tape.begin() + head, temp); // Insert saved character before '#'
                display_tape(head);
                state = "q3";
            }

            else if (state == "q3")
            {

                head--;
                while (Tape[head] != 'X')
                {
                    head--; // Go back to find next unprocessed char from original string
                }
                head--; // Move left of that 'X'
                display_tape(head);
                state = "q1"; // Loop back
            }

            else if (state == "qf") // Final state
            {
                display_tape(head);
                state = "B"; // Halt(blank)
            }
        }
    }

    long long CountCharacters()
    {
        k=1;
        // input of language
        cout << "Enter language of two alphabet : ";
        cin >> alpha1 >> alpha2;

        while (alpha1 == alpha2)
        {
            cout << "Enter language of two alphabet : ";
            cin >> alpha1 >> alpha2;
        }

        cout << "Enter stirng  : "; // input
        cin >> str;

        Tape.clear();

        for (char c : str)
        {
            Tape.push_back(c); // adding each char of string
        }

        Tape.push_back('#'); // add '#'

        int head = 0;        // Starting position of the tape head
        string state = "q0"; // Starting state
        int count = 0;       // To count how many characters we read

        // Run until we reach final state qf
        while (state != "qf")
        {
            char symbol = Tape[head]; // Read symbol under tape head

            if (state == "q0")
            {
                if (symbol == '#')
                {
                    state = "qf"; // If end symbol found, go to final state
                }
                else
                {
                    Tape[head] = 'X';   // Mark character as counted
                    display_tape(head); // Show tape status
                    count++;            // Increase count
                    head++;             // Move to next character
                }
            }
        }

        return count; // returning count
    }
    void TrimSpaces()
    {
        // Input of language
        cout << "Enter language of two alphabet : ";
        cin >> alpha1 >> alpha2;
        while (alpha1 == alpha2) // Ensuring both alphabets are different
        {
            cout << "Enter language of two alphabet : ";
            cin >> alpha1 >> alpha2;
        }
        // Taking input string
        cout << "Enter string: ";
        cin.ignore();
        getline(cin, str);

        Tape.clear(); // Clearing tape for new input
        for (char c : str)
        {
            Tape.push_back(c); // Writing input string to tape
        }
        Tape.push_back('B'); // End of tape

        int head = 0;
        string state = "q0";

        // Move to the first non-space character
        while (true)
        {
            display_tape(head);

            if (state == "q0")
            {
                char symbol = Tape[head];

                if (symbol == ' ') // Leading space
                {
                    for (int i = head; i < Tape.size() - 1; i++)
                    {
                        Tape[i] = Tape[i + 1]; // shifting
                    }
                    Tape.pop_back(); // Remove space
                }
                else if (symbol == 'B') // Empty input or only spaces
                {
                    state = "qf"; // Finish
                }
                else
                {
                    head++;
                }
            }
            else if (state == "qf") // All trimming done
            {
                cout << "* OUTPUT *" << endl;
                display_tape(head);
                break; // Stop printing after blank
            }
        }
    }
    /*
    this function is for tape display , displaying state of tape at each transition
    when i equals tracker it means the state is at that character  we are showing "^^^"
    to that
    */
    void display_tape(int tracker)
    {
        cout << "TAPE AT " << k << " ITERATION : " << endl;
        k++;
        for (int i = 0; i < Tape.size(); i++)
        {
            cout << "----";
        }
        cout << endl;
        for (int i = 0; i < Tape.size(); i++)
        {
            cout << "| " << Tape[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < Tape.size(); i++)
        {
            if (i == tracker)
            {
                cout << "^^^^^";
            }
            else
            {
                cout << "----";
            }
        }
        cout << endl
             << endl;
    }
};
int main()
{
    int choice;
    TuringMachine Tm; // object of Turing Machine class
    while (true)
    {
        // menu options for selecting String Manipulation function
        cout << "Turing Machine for String Manipulation" << endl;
        cout << "--------------------------------" << endl;
        cout << "1. String Concatenation" << endl;
        cout << "2. Palindrome Checker" << endl;
        cout << "3. Anagram Checker" << endl;
        cout << "4. String Reversal" << endl;
        cout << "5. Count Characters" << endl;
        cout << "6. Trim Spaces" << endl;
        cout << "0. Exit(Press 0)" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 0: // for exit
        {
            cout << "THANK YOU FOR USING TURING MACHINE SIMULATOR FOR STRING MANIPULATION" << endl;
            exit(0);
        }
        case 1: // for concatenation of Two Strings
        {
            Tm.Concatenate();
            break;
        }
        case 2: // for Checking if a string is a palindrome
        {
            Tm.PalindromeChecker();
            break;
        }
        case 3: // checking if two strings are Anagram
        {
            if (Tm.AnagramChecker())
            {
                cout << "Its a ANAGRAM" << endl;
            }
            else
            {
                cout << "Its not a ANAGRAM" << endl;
            }
            break;
        }
        case 4: // reversing the string
        {
            Tm.StringReversal();
            break;
        }
        case 5: // Counting Character in string entered by user
        {
            long long count = Tm.CountCharacters();
            cout << "Characters in String are  : " << count << endl;
            break;
        }
        case 6: // For trimming leading and trailing spaces from a string
        {
            Tm.TrimSpaces();
            break;
        }
        default:
            cout << "Please enter a Valid Input" << endl;
            break;
        }
    }
}