# Basic data types


## Boolean type

Syntax:

```
<boolean type> ::= 'int1' | 'bool'  ; <IDENTIFIER>

<boolean values> ::= 'true' | 'false' | ; <IDENTIFIER>
                        '0' | '1'       ; <NUMBER>
```

## Integer types

Syntax:

```
<integer types> ::= [us]int[8|16|32|64|128] ; <IDENTIFIER>

<integer values> ::= 0[bB][_01]+ |          ; <NUMBER>
                        0[cC][_0-7]+ |      ; <NUMBER>
                        [0-9]+ |            ; <NUMBER>
                        0[xX][0-9a-fA-F]+   ; <NUMBER>
```

Aliases:

```cell
alias byte = sint8
alias short = sint16
alias int = sint32
alias long = sint32
alias cent = sint128

alias char = uint32 ; Unicode code point
```

# Floating point type

```
<floating point type> ::= float[16|32|64|128]

```

Aliases:

```
alias float = float32
alias double = float64
```
