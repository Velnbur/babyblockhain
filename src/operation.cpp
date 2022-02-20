#include "operation.h"
#include <string>

namespace bc = blockchain;

bc::Operation::Operation(OperationType type, unsigned int line_number,
                         const std::string &path, const std::string *str)
    : type(type), n(line_number)
{
  if (path[0] != '/')
    this->path = '/' + path;
  else
    this->path = path;

  if (type == bc::OperationType::DELETE)
    this->str = nullptr;
  else
    this->str = new std::string(*str);
}

std::string bc::Operation::ToString() const
{
  std::string result;
  result += std::to_string(static_cast<int>(type)) + ';' + std::to_string(n) +
            ';' + path;
  if (type != bc::OperationType::DELETE)
    result += ";\"" + (*str) + '"';
  return result;
}

bc::Operation::~Operation()
{
  delete str;
}
