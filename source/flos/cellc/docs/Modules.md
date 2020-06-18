# Module declaration

Modules are representation of unit of source.

Syntax:

```
<module statement> ::= 'module' <module path> [ ';' | <NEWLINE> ]

<module path> ::= <IDENTIFIER> [ '.' <IDENTIFIER> ]*
```

Examples:

```
module std

module std.utf

```

# Import declaration

Import declaration specifies other modules to import. By default compiler will look for modules in `/lib` directory. If *module location* is specified, then compiler will use library pointed by string literal. 

Imported modules can be named by *module alias*.

Syntax:

```
<import statement> ::= 'import' <module path> [ '=' <module alias> ]? [ 'from' <module location> ]? [ ';' | <NEWLINE> ]

<module alias> ::= <IDENTIFIER>
<module location> ::= <STRING>
```

Examples:

```
import std.file
import aaa.file = FILE
import xyz from "/lib/libabc_xyz.so"
import bar.xyz = BAR from "~/lib/bar/xyz.so"
```

