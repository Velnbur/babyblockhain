#include "commit.h"
#include "sha1.h"
#include <cstddef>
#include <ctime>
#include <openssl/bn.h>
#include <openssl/dsa.h>
#include <openssl/ossl_typ.h>
#include <random>
#include <string>

namespace bc = blockchain;

bc::Commit::Commit(const std::vector<Operation *> &opers, int nonce,
                   const std::string &desc, const std::string &pub_key)
    : description(desc), operations(opers), nonce(nonce), date(time(0)),
      user_id(pub_key)
{
  format_time(date, message);
  message.push_back('\n');
  message.append('"' + description +
                 "\"\n"); // bound description with '"' symbols and add new line
  message.push_back('\n');

  for (auto oper : opers)
    message.append(oper->toString() + '\n');

  char *hash =
      SHA1((message + std::to_string(this->nonce)).c_str(), message.size());

  hash_to_string(hash, HASH_SIZE, ID);
  message = ID + '\n' + message;
  delete[] hash;
}

bc::Commit::~Commit()
{
  for (auto oper : operations)
    delete oper;
}

const std::string &bc::Commit::getDesc() const
{
  return description;
}
const std::string &bc::Commit::getID() const
{
  return ID;
}

const std::string &bc::Commit::getUserID() const
{
  return user_id;
}

const std::string &bc::Commit::getSign() const
{
  return sign;
}

const std::string &bc::Commit::getMessage() const
{
  return message;
}

std::string bc::Commit::toString() const
{
  return sign + '\n' + user_id + '\n' + message;
}

void bc::Commit::doSign(const std::string &priv_key)
{
  DSA *dsa = DSA_new();
  DSA_generate_parameters_ex(dsa, KEY_SIZE, NULL, 0, NULL, NULL, NULL);
  BIGNUM *priv = BN_new();
  BIGNUM *pub = BN_new();
  BN_hex2bn(&priv, priv_key.c_str());
  BN_hex2bn(&pub, user_id.c_str());
  DSA_set0_key(dsa, pub, priv);

  DSA_SIG *sig =
      DSA_do_sign((unsigned char *)message.c_str(), message.size(), dsa);

  BIGNUM *R = BN_new(), *S = BN_new();
  DSA_SIG_get0(sig, (const BIGNUM **)&R, (const BIGNUM **)&S);
  char *r_hex = BN_bn2hex(R);
  char *s_hex = BN_bn2hex(S);
  sign.clear();
  sign.append(r_hex);
  sign.append(s_hex);

  delete[] r_hex;
  delete[] s_hex;
  DSA_free(dsa);
  DSA_SIG_free(sig);
}

bool bc::Commit::verify(const std::string &sign, const std::string &pub_key,
                        const std::string &message)
{
  bool result = false;
  DSA *dsa = DSA_new();

  DSA_SIG *sig = DSA_SIG_new();
  BIGNUM *R = BN_new();
  BIGNUM *S = BN_new();
  BIGNUM *pub = BN_new();

  BN_hex2bn(&pub, pub_key.c_str());
  BN_hex2bn(&R, sign.substr(0, SIGN_SIZE / 2 - 1).c_str());
  BN_hex2bn(&S, sign.substr(SIGN_SIZE / 2, SIGN_SIZE - 1).c_str());

  DSA_SIG_set0(sig, R, S);

  DSA_set0_key(dsa, pub, NULL);

  result = DSA_do_verify((unsigned char *)message.c_str(), (int)message.size(),
                         sig, dsa);
  DSA_SIG_free(sig);
  DSA_free(dsa);
  return result;
}

#define TIME_BUFF_SIZE 21

void bc::Commit::format_time(const time_t &date, std::string &result)
{
  char time_buff[TIME_BUFF_SIZE];
  auto timeinfo = localtime(&date);
  strftime(time_buff, TIME_BUFF_SIZE, "%d/%m/%Y %H:%M:%S", timeinfo);
  result.append(time_buff);
}

/*
** Get low foru bits of byte and convert it to one char
** in hexdecimal representaion.
*/
char bc::Commit::low_byte_to_char(char ch)
{
  ch &= 0x0f; // get low byte of ch;

  if (ch < 10)
    return ch + '0';
  return ch - 10 + 'a';
}

/*
**  convert array of bytes to array of chars where every byte
**  is a two hex numbers, for example:
**
**  [255, 10, 11, 0] -> ['f', 'f', '0', 'a', '0', 'b', '0', '0'];
**                       |  255  |    10   |    11   |    0    |
*/
void bc::Commit::hash_to_string(char *hash, size_t len, std::string &result)
{
  for (size_t i = 0; i < len; ++i) {
    char left_c = (hash[i] >> 4);
    char right_c = hash[i] - (left_c << 4);
    result.push_back(low_byte_to_char(left_c));
    result.push_back(low_byte_to_char(right_c));
  }
}
