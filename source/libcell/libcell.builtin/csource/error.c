#include <cell/error.h>

cell_string __default_error_str(void);

cell_error __default_error_s = {
    .string = __default_error_str
};

cell_string __default_error_str(void) {
    return cell_string_c("error");
}
