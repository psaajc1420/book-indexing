#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

void parser();

int main() {


  parser();

//  BookIndexer indexer;

  return 0;
}

void parser() {
  ifstream infile;
  infile.open("../data/test_book.txt");

  int kMaxNumLines = 80;
  int parsedCounter;

  char line[kMaxNumLines];
  char parsedData[2 * kMaxNumLines];

  bool endParse = false;
  bool outerBracketNotFound = false;
  bool innerBracketNotFound = false;

  while (!endParse && infile.good()) {
    infile.getline(line, kMaxNumLines);
    string pageNumber;
    if (line[0] == '<') {
      if (line[1] == '-') {
        endParse = true;
      } else {
        char pageNumberBuffer[80];
        int i = 1;
        while (line[i] != '>') {
          pageNumberBuffer[i - 1] = line[i];
          i++;
        }
        pageNumberBuffer[i - 1] = '\0';
        pageNumber = pageNumberBuffer;
        cout << pageNumber << endl;
      }
    } else {

      for (int i = 0; i < strlen(line); i++) {

        int lineCounter = i;
        if (outerBracketNotFound) {
          while (line[lineCounter] != ']') {
            if (line[lineCounter] == '[') {
              lineCounter++;
              while (line[lineCounter] != ']') {
                parsedData[parsedCounter] = line[lineCounter];
                parsedCounter++;
                lineCounter++;
              }
              lineCounter++;
            }
            if (line[lineCounter] == ']') {
              break;
            }

            parsedData[parsedCounter] = line[lineCounter];
            lineCounter++;
            parsedCounter++;
          }
          parsedData[parsedCounter] = '\0';

          outerBracketNotFound = false;

          cout << parsedData << endl;

        } else {

          parsedCounter = 0;

          if (line[i] == '[') {
            lineCounter++;
            while (line[lineCounter] != ']') {
              if (line[lineCounter] == '[') {
                lineCounter++;
                while (line[lineCounter] != ']') {
                  if (lineCounter >= strlen(line)) {
                    innerBracketNotFound = true;
                    break;
                  }
                  parsedData[parsedCounter] = line[lineCounter];
                  parsedCounter++;
                  lineCounter++;
                }
                lineCounter++;
              }

              if (lineCounter >= strlen(line)) {
                outerBracketNotFound = true;
                break;
              }

              if (innerBracketNotFound || line[lineCounter] == ']') {
                break;
              }

              parsedData[parsedCounter] = line[lineCounter];
              lineCounter++;
              parsedCounter++;
            }
            parsedData[parsedCounter] = '\0';
            if (!outerBracketNotFound || !innerBracketNotFound)
              cout << parsedData << endl;
          }

          if (outerBracketNotFound || innerBracketNotFound) {
            break;
          }
        }
      }
    }
  }
}