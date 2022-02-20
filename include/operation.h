#ifndef OPERATION_H_SENTRY
#define OPERATION_H_SENTRY

#include <string>

namespace blockchain {
enum OperationType {
  INSERT = 0,
  DELETE,
  REPLACE,
};

struct Operation {
  OperationType type;
  std::string str;
  std::string path;

  Operation(OperationType type, const std::string &str,
            const std::string &path);

  /*
  ** Return formated like in documentation string:
  ** 'method;str;path'
  **
  ** if @path doesn't start with '/', add '/'
  ** to begining of @path.
  ** For example:
  ** '0;"Hello";/hello.txt'
  */
  std::string ToString();
};
} // namespace blockchain

#endif // OPERATION_H_SENTRY
