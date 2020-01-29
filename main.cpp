//
// Created by miri on 20.1.2020.
//

#include "Server.h"
#include "empiric test/empiric_test.h"

using namespace server_side;
using namespace test;

int main(int argc, char *argv[]) {
  // if you would like to see the empiric test use this code:test::experiment();
  (void)argc;
  if (argv[1] != nullptr) {
    // case that we have port from user
    boot::Main::main(argv[1]);
  }
  // default port: 5600
  char port[] = "5600";
  boot::Main::main(port);
}
