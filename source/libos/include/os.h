#pragma once

#include <cell/builtin.h>

#ifdef NAMESPACE
#undef NAMESPACE
#endif
#define NAMESPACE os
#include <cell/namespace.h>

// module os

typedef struct {
    
} file;

// public func open(name string) (*file, error)

struct open_ret {
    file* _1;
    error _2;
};
