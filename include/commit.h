#ifndef TRANSACTION_H_SENTRY
#define TRANSACTION_H_SENTRY

#include "operation.h"
#include "sha1.h"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

namespace blockchain {

const unsigned int KEY_SIZE = 1024; // in bits
const unsigned int SIGN_SIZE = 80;
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
  std::string user_id; // public key

  std::string sign;

public:
  /* Operations now belong to Commit object. */
  Commit(const std::vector<Operation *> &operations, int nonce,
         const std::string &description, const std::string &pub_key);

  ~Commit();
  const std::string &getDesc() const;
  const std::string &getID() const;
  const std::string &getUserID() const;
  const std::string &getSign() const;
  std::string toString() const;
  void doSign(const std::string &priv_key);

  static bool verify(const std::string &sign, const std::string &pub_key,
                     const std::string &message);

private:
  /* add hash from SHA1 alg as hexdecimal to end of the string @result*/
  static void hash_to_string(char *hash, size_t len, std::string &result);

  /* convert low 4 bits of byte to hex char */
  static char low_byte_to_char(char c);

  /*  add formated time to the end of string */
  static void format_time(const time_t &date, std::string &result);
};

} // namespace blockchain

#endif // TRANSACTION_H_SENTRY
