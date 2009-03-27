#include "indri/IndexEnvironment.hpp"
 
using namespace indri::api;

int main() {
  IndexEnvironment *index = new IndexEnvironment();
  index->create("/tmp/blah");
  return 0;
};
