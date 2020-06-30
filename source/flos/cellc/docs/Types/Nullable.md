## Nullable type

Syntax:

```
<nullable type> ::= '?' |       ; <OPERATOR>
                    'nullable>  ; <IDENTIFIER>
                    <type>
```

Examples:

```
var nullableBool ?bool // by default null

var n1 ?bool = false
var n2 ?bool = null

func hasValue(b ?bool) bool {
    return b // null is false
}
```
