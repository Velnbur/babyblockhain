#include "transaction.h"
#include "sha1.h"
#include <string>

namespace bc = blockchain;

bc::Transaction::Transaction(const std::vector<Operation *> &opers, int nonce)
    : operations(opers), nonce(nonce)
{
  std::string message;
  for (auto oper : opers)
    message += oper->ToString();

  message += std::to_string(nonce);
  char *hash = SHA1(message.c_str(), message.size());
  this->ID = hash;
  delete[] hash;
}

bc::Transaction::~Transaction()
{
  for (auto oper : operations)
    delete oper;
}

std::string bc::Transaction::ToString() const
{
  std::string result;
  result += ID;
  for (auto oper : operations)
    result += oper->ToString() + '\n';
  return result;
}

std::ostream &operator<<(std::ostream &out, const bc::Transaction &trans)
{
  out << trans.ToString();
  return out;
}
