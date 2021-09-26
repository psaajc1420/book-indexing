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
  int parsed_counter;

  char line[kMaxNumLines];
  char parsed_data[2 * kMaxNumLines];

  bool end_parse = false;
  bool outer_bracket_not_found = false;
  bool inner_bracket_not_found = false;

  while (!end_parse && infile.good()) {
    infile.getline(line, kMaxNumLines);
    string page_number;
    if (line[0] == '<') {
      if (line[1] == '-') {
        end_parse = true;
      } else {
        char page_number_buffer[80];
        int i = 1;
        while (line[i] != '>') {
          page_number_buffer[i - 1] = line[i];
          i++;
        }
        page_number_buffer[i - 1] = '\0';
        page_number = page_number_buffer;
        cout << page_number << endl;
      }
    } else {

      for (int i = 0; i < strlen(line); i++) {

        int line_counter = i;
        if (outer_bracket_not_found) {
          while (line[line_counter] != ']') {
            if (line[line_counter] == '[') {
              line_counter++;
              while (line[line_counter] != ']') {
                parsed_data[parsed_counter] = line[line_counter];
                parsed_counter++;
                line_counter++;
              }
              line_counter++;
            }
            if (line[line_counter] == ']') {
              break;
            }

            parsed_data[parsed_counter] = line[line_counter];
            line_counter++;
            parsed_counter++;
          }
          parsed_data[parsed_counter] = '\0';

          outer_bracket_not_found = false;

          cout << parsed_data << endl;

        } else {

          parsed_counter = 0;

          if (line[i] == '[') {
            line_counter++;
            while (line[line_counter] != ']') {
              if (line[line_counter] == '[') {
                line_counter++;
                while (line[line_counter] != ']') {
                  if (line_counter >= strlen(line)) {
                    inner_bracket_not_found = true;
                    break;
                  }
                  parsed_data[parsed_counter] = line[line_counter];
                  parsed_counter++;
                  line_counter++;
                }
                line_counter++;
              }

              if (line_counter >= strlen(line)) {
                outer_bracket_not_found = true;
                break;
              }

              if (inner_bracket_not_found || line[line_counter] == ']') {
                break;
              }

              parsed_data[parsed_counter] = line[line_counter];
              line_counter++;
              parsed_counter++;
            }
            parsed_data[parsed_counter] = '\0';
            if (!outer_bracket_not_found || !inner_bracket_not_found)
              cout << parsed_data << endl;
          }

          if (outer_bracket_not_found || inner_bracket_not_found) {
            break;
          }
        }
      }
    }
  }
}