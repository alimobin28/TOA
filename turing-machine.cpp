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
        k = 1;
    }

    bool AnagramChecker()
    {
        k = 1;
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

    long long CountCharacters()
    {
        k = 1;
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
