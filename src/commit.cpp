#include "commit.h"
#include "sha1.h"
#include <ctime>
#include <random>
#include <string>

namespace bc = blockchain;

bc::Commit::Commit(const std::vector<Operation *> &opers, int nonce,
                   const std::string &desc)
    : description(desc), operations(opers), nonce(nonce), date(time(0))
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

  hash_to_string(hash, ID);
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

std::string bc::Commit::toString() const
{
  return message;
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
void bc::Commit::hash_to_string(char hash[HASH_SIZE], std::string &result)
{
  char buff[HASH_SIZE * 2]; // size twice as big because you need two chars to
                            // represent one byte as hexdecimal
  for (int i = 0; i < HASH_SIZE; ++i) {
    char left_c = (hash[i] >> 4);
    char right_c = hash[i] - (left_c << 4);
    buff[i * 2] = low_byte_to_char(left_c);
    buff[i * 2 + 1] = low_byte_to_char(right_c);
  }

  // this stuff is faster than returning new object as result
  result.append(buff);
}
