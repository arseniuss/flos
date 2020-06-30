## Immutable type

Syntax:

```
<immutable type> ::= '!' |      ; <OPERATOR>
                    'immutable' ; <IDENTIFIER>
                    <type>
```

Examples:

```
var value !bool = false // unchangeable, equal to const value = false

var v2 !bool // once set cannot change

v2 = true
v2 = false // error

@safe
func (value !interface) hasValue() bool {
     return value.fixed
}
```
