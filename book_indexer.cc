//
// Created by jacob on 9/25/21.
//

#include "book_indexer.h"

void BookIndexer::Parse() {
  ifstream infile;
  infile.open("../data/test_book.txt");

  bool end_parse = false;
  while (!end_parse && infile.good()) {
    infile.getline(line, kMaxNumLines);
    string page_number;

    if (line[0] == '<') {
      end_parse = ParsePageNumber();
    } else {
      ParseKeyWords();
    }
  }
}

bool BookIndexer::ParsePageNumber() {
  bool end_parse = false;
  if (line[1] == '-') {
    end_parse = true;
  } else {
    int i = 0;
    while (line[i] != '>') {
      page_number_buffer[i - 1] = line[++i];
    }
    page_number_buffer[i - 1] = '\0';
    page_number = atoi(page_number_buffer);
    cout << page_number << endl;
  }
  return end_parse;
}

void BookIndexer::ParseKeyWords() {
  parse_key_next_line = true;
  for (int i = 0; i < strlen(line); i++) {

    line_counter = i;

    if (outer_bracket_not_found && parse_key_next_line) {
      outer_bracket_not_found = false;

      ParseSavedData();

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

      ParseSavedData();

      if (strlen(saved_data) != 0) {
        cout << saved_data << endl;
      }
    } else {

      ParseData();

    }
  }
}

void BookIndexer::ParseSavedData() {
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
}

void BookIndexer::ParseData() {
  parsed_counter = 0;

  if (line[line_counter] == '[') {
    line_counter++;
    while (line[line_counter] != ']') {
      if (line[line_counter] == '[') {
        line_counter++;
        while (line[line_counter] != ']') {
          if (line_counter >= strlen(line)) {
            inner_bracket_not_found = true;
            SaveData();
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
        SaveData();
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
    if (strlen(parsed_data) != 0) {
      cout << parsed_data << endl;
    }

  }
}
void BookIndexer::SaveData() {
  parse_key_next_line = false;
  parsed_data[parsed_counter] = '\0';
  saved_counter = parsed_counter;
  strcpy(saved_data, parsed_data);
  parsed_data[0] = '\0';
}

