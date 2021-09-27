#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

void run();

int main() {

  run();

  return 0;
}

void run() {
  ifstream infile;
  infile.open("../data/test_book.txt");

  const int kMaxNumLines = 80;
  int parsed_counter;
  int saved_counter;
  int line_counter;
  char line[kMaxNumLines];
  char page_number_buffer[kMaxNumLines];
  char parsed_data[2 * kMaxNumLines];
  char saved_data[2 * kMaxNumLines];

  bool end_parse = false;
  bool outer_bracket_not_found = false;
  bool inner_bracket_not_found = false;
  bool parse_key_next_line;

  while (!end_parse && infile.good()) {
    infile.getline(line, kMaxNumLines);
    string page_number;

    if (line[0] == '<') {
      if (line[1] == '-') {
        end_parse = true;
      } else {
        int i = 0;
        while (line[i] != '>') {
          page_number_buffer[i - 1] = line[++i];
        }
        page_number_buffer[i - 1] = '\0';
        page_number = page_number_buffer;
        cout << page_number << endl;
      }
    } else {

      parse_key_next_line = true;
      for (int i = 0; i < strlen(line); i++) {

        line_counter = i;

        if (outer_bracket_not_found && parse_key_next_line) {
          outer_bracket_not_found = false;

          while (line[line_counter] != ']') {
            if (line[line_counter] == '[') {
              line_counter++;
              while (line[line_counter] != ']') {
                saved_data[saved_counter] = line[line_counter];
                saved_counter++;
                line_counter++;
              }
              line_counter++;
            }

            if (line[line_counter] == ']') {
              break;
            }

            saved_data[saved_counter] = line[line_counter];
            line_counter++;
            saved_counter++;
          }
          saved_data[saved_counter] = '\0';
          saved_counter = 0;

          if (strlen(saved_data) != 0) {
            cout << saved_data << endl;
          }

        } else if (inner_bracket_not_found && parse_key_next_line) {
          inner_bracket_not_found = false;

          while (line[line_counter] != ']') {
            saved_data[saved_counter] = line[line_counter];
            saved_counter++;
            line_counter++;
          }
          line_counter++;

          while (line[line_counter] != ']') {
            if (line[line_counter] == '[') {
              line_counter++;
              while (line[line_counter] != ']') {
                saved_data[saved_counter] = line[line_counter];
                saved_counter++;
                line_counter++;
              }
              line_counter++;
            }

            if (line[line_counter] == ']') {
              break;
            }

            saved_data[saved_counter] = line[line_counter];
            line_counter++;
            saved_counter++;
          }
          saved_data[saved_counter] = '\0';
          saved_counter = 0;

          if (strlen(saved_data) != 0) {
            cout << saved_data << endl;
          }
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
                    parse_key_next_line = false;
                    parsed_data[parsed_counter] = '\0';
                    saved_counter = parsed_counter;
                    strcpy(saved_data, parsed_data);
                    parsed_data[0] = '\0';
                    break;
                  }
                  parsed_data[parsed_counter] = line[line_counter];
                  parsed_counter++;
                  line_counter++;
                }
                line_counter++;
              }

              if (inner_bracket_not_found) break;

              if (line_counter >= strlen(line)) {
                outer_bracket_not_found = true;
                parse_key_next_line = false;
                parsed_data[parsed_counter] = '\0';
                saved_counter = parsed_counter;
                strcpy(saved_data, parsed_data);
                parsed_data[0] = '\0';
                break;
              }

              if (line[line_counter] == ']') {
                break;
              }

              parsed_data[parsed_counter] = line[line_counter];
              line_counter++;
              parsed_counter++;
            }
            parsed_data[parsed_counter] = '\0';
            if (!outer_bracket_not_found || !inner_bracket_not_found) {
              if (strlen(parsed_data) != 0) {
                cout << parsed_data << endl;
              }
            }

          }
        }
      }
    }
  }
}
