#include <commit.h>
#include <iostream>
#include <openssl/bn.h>
#include <openssl/dsa.h>
#include <string>
#include <vector>

void create_keys(std::string &pub, std::string &priv)
{
  DSA *dsa = DSA_new();
  DSA_generate_parameters_ex(dsa, blockchain::KEY_SIZE, NULL, 0, NULL, NULL,
                             NULL);
  DSA_generate_key(dsa);
  BIGNUM *pub_key = BN_new();
  BIGNUM *priv_key = BN_new();
  BIGNUM *priv_copy = NULL, *pub_copy = NULL;
  DSA_get0_key(dsa, (const BIGNUM **)&pub_copy, (const BIGNUM **)&priv_copy);
  BN_copy(pub_key, pub_copy);
  BN_copy(priv_key, priv_copy);

  char *hex = BN_bn2hex(pub_key);
  pub = hex;
  delete[] hex;
  hex = BN_bn2hex(priv_key);
  priv = hex;
  delete[] hex;
  BN_free(pub_key);
  BN_free(priv_key);
  DSA_free(dsa);
}

int main()
{
  std::string priv, pub;

  create_keys(pub, priv);

  std::vector<blockchain::Operation *> vec;
  std::string str("Insert string");
  vec.push_back(new blockchain::Operation(blockchain::OperationType::INSERT, 2,
                                          "hello.txt", &str));
  str = "Replace string";
  vec.push_back(new blockchain::Operation(blockchain::OperationType::REPLACE, 4,
                                          "/Document/hello.txt", &str));

  vec.push_back(new blockchain::Operation(blockchain::OperationType::DELETE, 1,
                                          "/Document/hello.txt"));

  blockchain::Commit comm(vec, -1, "Hello world", pub);
  comm.doSign(priv);

  std::cout << "Basic example of commit in text:" << std::endl;
  std::cout << comm.toString() << std::endl;

  std::cout << "Verify this commit by public key: " << std::boolalpha
            << comm.verify(comm.getSign(), comm.getUserID(), comm.getMessage())
            << std::endl;
}
