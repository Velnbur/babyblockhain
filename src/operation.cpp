#include "operation.h"
#include <string>

namespace bc = blockchain;

bc::Operation::Operation(OperationType type, const std::string &str,
                         const std::string &path)
    : type(type), str(str)
{
  if (path[0] != '/')
    this->path = '/' + path;
  else
    this->path = path;
}

std::string bc::Operation::ToString()
{
  std::string result;
  result += std::to_string(static_cast<int>(type));
  result += ';' + str + ';' + path;
  return result;
}
