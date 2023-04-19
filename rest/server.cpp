#include <json/json.h>
#include <spdlog/spdlog.h>

#include <atomic>
#include <iostream>
#include <restbed>

std::atomic<long> counter{0};

void increment(const std::shared_ptr<restbed::Session> session) {
  const auto& request = session->get_request();
  auto count = request->get_path_parameter("count");
  spdlog::info("Incrementing counter: {}", count);
  counter.fetch_add(std::atol(count.data()));
  spdlog::info("Value after increment: {}", counter);
  const std::string response = "OK";
  session->close(restbed::OK, response,
                 {{"Content-Length", fmt::to_string(response.size())}});
}

void print(const std::shared_ptr<restbed::Session> session) {
  spdlog::info("Printing counter");
  const std::string response = fmt::to_string(counter.load());
  session->close(restbed::OK, response,
                 {{"Content-Length", fmt::to_string(response.size())}});
}

void print_json(const std::shared_ptr<restbed::Session> session) {
  spdlog::info("Printing counter");
  Json::Value response;
  response["value"] = static_cast<Json::UInt64>(counter.load());
  response["status"] = "OK";

  Json::FastWriter writer;
  const std::string response_str = writer.write(response);
  session->close(restbed::OK, response_str,
                 {{"Content-Length", fmt::to_string(response_str.size())},
                  {"Content-type", "application/json"}});
}

int main(int, char**) {
  spdlog::info("REST API demo!");
  auto resource1 = std::make_shared<restbed::Resource>();
  resource1->set_path("/increment/{count:.*}");
  resource1->set_method_handler("POST", increment);

  auto resource2 = std::make_shared<restbed::Resource>();
  resource2->set_path("/counter");
  resource2->set_method_handler("GET", print_json);

  auto settings = std::make_shared<restbed::Settings>();
  settings->set_port(8080);
  settings->set_default_header("Connection", "close");

  restbed::Service service;
  service.publish(resource1);
  service.publish(resource2);
  service.start(settings);

  return EXIT_SUCCESS;
}
