#include "indri/IndexEnvironment.hpp"

using namespace std; 

class lemur_index_environment {
private:
  indri::api::IndexEnvironment *index;
public:
  lemur_index_environment() : index() {};
  virtual ~pymer_index_environment();
  void create(string location);
};
