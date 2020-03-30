# Slice

Syntax:
```
<slice_type> ::= '[]' <type>
```

Underlying structure in C:
```c
typedef struct {
    cell_byte* buf;
    cell_size cap;
    cell_size len;
} cell_slice;
```

Descriptor:
```c
typedef struct {
    cell_type of_type;
} cell_slice_type;
```

Examples:
```cell
var s []int = new [4]int


```

Interface:
```cell
var s []int

func (s []T) append(obj T) (error, []T)
```
