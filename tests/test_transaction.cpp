#include "../libs/sha1.c"
#include "../src/transaction.cpp"
#include "ctest.h"
#include <iostream>
#include <string>
#include <vector>

CTEST_DATA(transaction)
{
  blockchain::Transaction *trans;
};

CTEST_SETUP(transaction)
{
  std::vector<blockchain::Operation *> vec;
  std::string str("Insert string");
  vec.push_back(new blockchain::Operation(blockchain::OperationType::INSERT, 2,
                                          "hello.txt", &str));
  str = "Replace string";
  vec.push_back(new blockchain::Operation(blockchain::OperationType::REPLACE, 4,
                                          "/Document/hello.txt", &str));

  vec.push_back(new blockchain::Operation(blockchain::OperationType::DELETE, 1,
                                          "/Document/hello.txt"));
  data->trans = new blockchain::Transaction(vec, -1);
}
