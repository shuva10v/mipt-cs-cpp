#include <spdlog/spdlog.h>
#include <sqlite_modern_cpp.h>

#include <iostream>

int main(int, char**) {
  try {
    spdlog::info("Sqlite demo!");
    sqlite::database db("database.db");
    db << "create table if not exists scores ("
          "   _id integer primary key autoincrement not null,"
          "   name text,"
          "   score int"
          ");";
    std::string player;
    int score;
    std::cout << "Input player name: ";
    std::cin >> player;
    std::cout << "Input score: ";
    std::cin >> score;
    db << "insert into scores (name,score) values (?, ?);" << player << score;

    int max_score;
    db << "select max(score) from scores" >> max_score;
    std::string best_player;
    (db << "select name from scores where score = ? limit 1" << max_score) >>
        best_player;
    std::cout << "Max score is: " << max_score << "\n";
    std::cout << "Best player is: " << best_player << "\n";
  } catch (std::exception& e) {
    spdlog::error("Error: {}", e.what());
  }
}
