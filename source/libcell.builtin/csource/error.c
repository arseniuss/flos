#include <cell/error.h>

string __default_error_str(void);

error_s __default_error_s = {
  .str = __default_error_str
};

error __default_error = &__default_error_s;

string __default_error_str(void) {
  return string_c ("error");
}
