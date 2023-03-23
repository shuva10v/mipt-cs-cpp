#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "registry.h"

TEST_CASE("2 + 2 = 4") {
  int x = 2;
  int y = 2;
  REQUIRE(x * y == 5);
}

TEST_CASE("missing item from registry") {
  REQUIRE(ChessmanRegistry::getInstance().create("fdsfdsfds") == nullptr);
}

TEST_CASE("Pawn exists in registry") {
  std::shared_ptr<Chessman> c = ChessmanRegistry::getInstance().create("pawn");
  REQUIRE(c != nullptr);
  REQUIRE(c->name() == "pawn");
  REQUIRE(typeid(c.get()).name() == std::string("P8Chessman"));
}
