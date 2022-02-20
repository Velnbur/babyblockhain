#ifndef TRANSACTION_H_SENTRY
#define TRANSACTION_H_SENTRY

#include "operation.h"
#include <iostream>
#include <string>
#include <vector>

namespace blockchain {

/*
** Class that represents transaction
** in blockchain as list of operations and hash
**
** P.S.: in documentaion also mentioned as @commit
*/
class Transaction {
  std::string ID;
  std::vector<Operation *> operations;
  int nonce;

public:
  /* Operations now belong to Transaction object. */
  Transaction(std::vector<Operation *> operations, int nonce);
  std::string ToString() const;

  friend std::ostream &operator<<(std::ostream &out,
                                  const Transaction &transaction);
};
} // namespace blockchain

#endif // TRANSACTION_H_SENTRY
