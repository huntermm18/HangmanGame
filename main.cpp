#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

const int TOTAL_NUM_WORDS = 10;
const string words [TOTAL_NUM_WORDS] = {
        "inflate",
        "confusion",
        "assignment",
        "education",
        "roar",
        "orbit",
        "conservation",
        "average",
        "canvas",
        "aquarium"
        };

string getRandomWord();
bool makeGuess(string word, string& progress, char letter);
bool checkVictory(string progress);
void printGallows(int numGuesses);
void printGuessedLetters(set<char> letters);

int main() {

   string word = getRandomWord();
   set<char> guessedLetters;
   int correctGuessesMade = 0;
   int incorrectGuessesMade = 0;
   string progress;
   for (char c : word) {
      progress += "_";
   }

   cout << "Welcome to Hangman!" << endl;
   cout << "The word contains " << word.length() << " letters. Good luck." << endl;

   while(!checkVictory(progress)) {
      char guess;
      cout << endl << "Enter a letter to make a guess: ";
      cin >> guess;
      if (guessedLetters.find(guess) != guessedLetters.end()) {
         cout << "That letter has already been guessed" << endl;
         continue;
      }
      guessedLetters.insert(guess);

      bool successfulGuess = makeGuess(word, progress, guess);
      if (successfulGuess) {
         cout << "Good guess" << endl;
         correctGuessesMade++;
      }
      else {
         cout << "Sorry there are no " << guess << "'s" << endl;
         incorrectGuessesMade++;
      }

      if(checkVictory(progress)) {
         cout << "\n\nCongratulations you guessed it! The word was " << word << endl;
         cout << "It took you " << incorrectGuessesMade + correctGuessesMade << " guesses" << endl;
         break;
      }

      printGallows(incorrectGuessesMade);
      cout << "Current word progress: " << progress << endl;
      cout << "Correct Guesses: " << correctGuessesMade << endl;
      cout << "Incorrect Guesses: " << incorrectGuessesMade << endl;
      cout << "Guessed letters: ";
      printGuessedLetters(guessedLetters);
   }

   cout << "\nEnter the word 'play' to play again. Enter anything else to quit." << endl;
   string playAgain;
   cin >> playAgain;
   if (playAgain == "play") {
      main();
   }
   cout << "Thanks for playing" << endl;

   return 0;
}

string getRandomWord() {
   srand((int)time(nullptr));
   int randomInt = (rand() % TOTAL_NUM_WORDS);
   return words[randomInt];
}

bool makeGuess(string word, string& progress, char letter) {
   bool found = false;
   for (int i = 0; i < word.length(); ++i) {
      if (word[i] == letter) {
         progress[i] = letter;
         found = true;
      }
   }
   return found;
}

bool checkVictory(string progress) {
   for (char c : progress) {
      if (c == '_') {
         return false;
      }
   }
   return true;
}

void printGuessedLetters(set<char> letters) {
   for (char c : letters) {
      cout << c << " ";
   }
}

void printGallows(int numGuesses) {
   cout << "     ======";
   cout << "\n   //     |";
   cout << "\n  ||";
   if (numGuesses>0) cout << "      0";
   cout << "\n  ||";
   if (numGuesses>1) cout << "     \\";
   if (numGuesses>2) cout << "|";
   if (numGuesses>3) cout << "/";
   cout << "\n  ||";
   if (numGuesses>4) cout << "      |";
   cout << "\n  ||";
   if (numGuesses>5) cout << "     /";
   if (numGuesses>6) cout << " \\";
   cout << "\n  ||";
   cout << "\n=======   ";
   for (int i = 0; i < numGuesses - 7; ++i) {
      cout << ".";
   }

   cout << endl;
}