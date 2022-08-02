#pragma once

#include <lex/token_type.hpp>

#include <fmt/core.h>

#include <filesystem>
#include <iostream>
#include <istream>

namespace lex {

//////////////////////////////////////////////////////////////////////

struct Location {
  size_t lineno = 0;
  size_t columnno = 0;

  std::string Format() const {
    return fmt::format("Line = {}, column = {}",  //
                       lineno, columnno);
  }
};

//////////////////////////////////////////////////////////////////////

struct SpanLines {
  Location start;
  size_t span_number;
};

//////////////////////////////////////////////////////////////////////

class Scanner {
 public:
  Scanner(std::istream& source) : source_{source} {
    FetchNextSymbol();
  }

  void MoveRight() {
    switch (CurrentSymbol()) {
      case '\n':
        location_.columnno = 0;
        location_.lineno += 1;
        break;

      case EOF:
        // FMT_ASSERT(false, "\nReached EOF\n");
        break;

      default:
        location_.columnno += 1;
    }

    FetchNextSymbol();
  }

  void MoveNextLine() {
    while (CurrentSymbol() != '\n') {
      MoveRight();
    }

    // Finally, move to the next line
    MoveRight();
  }

  char CurrentSymbol() {
    return symbol_;
  }

  char PeekNextSymbol() {
    return source_.peek();
  }

  Location GetLocation() const {
    return location_;
  }

 private:
  void FetchNextSymbol() {
    symbol_ = source_.get();
  }

 private:
  std::istream& source_;

  Location location_;

  char symbol_;
};

//////////////////////////////////////////////////////////////////////

}  // namespace lex
