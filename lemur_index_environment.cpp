#include "lemur_index_environment.h"

using namespace std; 

lemur_index_environment::~lemur_index_environment() {
  index->close();
};

void lemur_index_environment::create(string location) {
  index->create(location.c_str());
};
