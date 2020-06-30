## Pointer type

Syntax:

```
<pointer type> ::= '*' |        ; <OPERATOR>
                    'pointer'   ; <IDENTIFIER>
                    <type>
```

Examples:

```
var ptr *int // pointer to int

type e struct { field int }
var ptr *e = new(e)

e.field
```
