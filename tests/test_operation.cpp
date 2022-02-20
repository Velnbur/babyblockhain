#include "../src/operation.cpp"
#include "ctest.h"
#include <string>

CTEST_DATA(operation)
{
  blockchain::Operation *oper;
  blockchain::Operation *oper_delete;
};

CTEST_SETUP(operation)
{
  auto str = std::string("Insert string");
  data->oper = new blockchain::Operation(blockchain::OperationType::INSERT, 2,
                                         "hello.txt", &str);
  data->oper_delete = new blockchain::Operation(
      blockchain::OperationType::DELETE, 2, "hello.txt");
}

CTEST2(operation, delete_construct)
{
  ASSERT_TRUE(data->oper_delete->str == nullptr);
}

CTEST2(operation, path_add_slash)
{
  ASSERT_STR(data->oper->path.c_str(), "/hello.txt");
}

CTEST2(operation, to_string)
{
  ASSERT_STR("0;2;/hello.txt;\"Insert string\"",
             data->oper->ToString().c_str());
}

CTEST2(operation, to_string_delete)
{
  ASSERT_STR("1;2;/hello.txt", data->oper_delete->ToString().c_str());
}
