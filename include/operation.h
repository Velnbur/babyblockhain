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
  unsigned int n; // number of line in file
  std::string *str;
  std::string path;
  /*
  ** if @type is OperationType::DELETE @str will be @nullptr
  */
  Operation(OperationType type, unsigned int line_number,
            const std::string &path, const std::string *str = nullptr);
  ~Operation();
  /*
  ** Return formated like in documentation string:
  ** 'method;str;path'
  **
  ** if @path doesn't start with '/', add '/'
  ** to begining of @path.
  ** For example:
  ** '0;"Hello";/hello.txt'
  */
  std::string toString() const;
};
} // namespace blockchain

#endif // OPERATION_H_SENTRY
