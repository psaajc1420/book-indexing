//
// Created by jacob on 9/25/21.
//

#ifndef BOOK_INDEXING_BOOK_INDEXER_H
#define BOOK_INDEXING_BOOK_INDEXER_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

class BookIndexer {
public:
  void Parse();

private:

  bool ParsePageNumber();
  void ParseSavedData();
  void ParseData();
  void ParseKeyWords();
  void SaveData();

  static constexpr int kMaxNumLines = 80;
  int parsed_counter;
  int saved_counter;
  int line_counter;
  int page_number;
  char line[kMaxNumLines];
  char page_number_buffer[kMaxNumLines];
  char parsed_data[2 * kMaxNumLines];
  char saved_data[2 * kMaxNumLines];

  bool outer_bracket_not_found = false;
  bool inner_bracket_not_found = false;
  bool parse_key_next_line;



};

#endif //BOOK_INDEXING_BOOK_INDEXER_H
