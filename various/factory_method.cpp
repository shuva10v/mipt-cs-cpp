#include <cassert>
#include <iostream>
#include <memory>

#include "chessman.h"

std::shared_ptr<Chessman> Chessman::create(ChessmanCode code) {
  switch (code) {
    case PAWN:
      return std::shared_ptr<Chessman>(new Pawn());
    case BISHOP:
      return std::shared_ptr<Chessman>(new Bishop());
    default:
      assert(false);
  }
}

Chessman* Chessman::create_raw(ChessmanCode code) {
  switch (code) {
    case PAWN:
      return new Pawn();
    case BISHOP:
      return new Bishop();
    default:
      assert(false);
  }
}

int main() {
  std::cout << "Running factory method example with raw pointer\n";
  Chessman* pawn_raw = Chessman::create_raw(PAWN);
  std::cout << "I am pawn: " << pawn_raw->name() << "\n";
  delete pawn_raw;

  std::cout << "Running factory method example with shared_ptr\n";
  std::shared_ptr<Chessman> pawn = Chessman::create(PAWN);
  std::shared_ptr<Chessman> bishop = Chessman::create(BISHOP);
  std::cout << "I am pawn: " << pawn->name() << "\n";
  std::cout << "I am bishop: " << bishop->name() << "\n";
  return 0;
}