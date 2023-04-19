#include <json/json.h>
#include <restclient-cpp/connection.h>
#include <restclient-cpp/restclient.h>
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
  spdlog::info("REST API client demo!");
  int increment = std::atoi(argv[1]);
  spdlog::info("Going to increment with {}", increment);
  auto conn = std::make_shared<RestClient::Connection>(
      "http://localhost:8080/increment/");
  RestClient::Response r = conn->post(fmt::to_string(increment), "{}");

  conn =
      std::make_shared<RestClient::Connection>("http://localhost:8080/counter");

  r = conn->get("");
  Json::Reader reader;
  Json::Value response;
  reader.parse(r.body, response);
  spdlog::info("Counter value: {}", response["value"].asInt64());

  return EXIT_SUCCESS;
}
