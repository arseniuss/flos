# Array

Syntax:
```
<array_type> ::= '[' <capacity> ']' <type>

<capacity>  ::= <number> | '?'
```

Underlying structure in C:
```c
typedef struct {
    cell_byte* buf;
    cell_size len;
} cell_array;
```

Descriptor:
```c
typedef struct {
    cell_type of_type;
    cell_size len;
} cell_array_type;
```

Examples:
```cell
var a [5]int
var b [6]int = { 1, 2, 3 }
var c [8]int = { 12, [6] = 3, [3] = 1 }

var test = new [5]int // type is actually *[5]int aka pointer to array of 5 to ints
```

Interface:
```cell

var a [5]int // in c: CELL_ARRAY_MAKE(a, 5, int);

@safe
func (a [?]interface) len() size {
    return a.len
}

func (a [?](t type)) sizeof() size {
    return a.len * t.size
}

```



