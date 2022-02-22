#include "ctest.h"
#include "sha1.h"
#include <commit.h>
#include <iostream>
#include <string>
#include <vector>

CTEST_DATA(commit)
{
  blockchain::Commit *trans;
};

CTEST_SETUP(commit)
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
  data->trans = new blockchain::Commit(vec, -1, "Hello world");
}

CTEST2(commit, test)
{

  std::cout << std::hex << data->trans->toString() << std::endl;
}
