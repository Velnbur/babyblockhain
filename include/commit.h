#ifndef TRANSACTION_H_SENTRY
#define TRANSACTION_H_SENTRY

#include "operation.h"
#include "sha1.h"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

namespace blockchain {

/*
** Class that represents transaction
** in blockchain as list of operations, desription, nonce,
** local unix time and hash.
**
** P.S.: in documentaion also mentioned as @commit
*/
class Commit {
  std::string ID;
  std::string description;
  std::vector<Operation *> operations;
  int nonce;

  time_t date;
  std::string message;

public:
  /* Operations now belong to Commit object. */
  Commit(const std::vector<Operation *> &operations, int nonce,
         const std::string &description);

  ~Commit();
  const std::string &getDesc() const;
  const std::string &getID() const;
  std::string toString() const;

private:
  /* add hash from SHA1 alg as hexdecimal to end of the string @result*/
  static void hash_to_string(char hash[HASH_SIZE], std::string &result);

  /* convert low 4 bits of byte to hex char */
  static char low_byte_to_char(char c);

  /*  add formated time to the end of string */
  static void format_time(const time_t &date, std::string &result);
};

} // namespace blockchain

#endif // TRANSACTION_H_SENTRY
