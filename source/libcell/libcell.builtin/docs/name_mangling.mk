# Name mangling

functions start with prefix __

function: <name> <paramaters> <return type> <module>
	
name: 'N' <length> <name>
	
parameters: 'P' [ <type> ]+
	
type:
	<void> |
	<unsigned integer> |
	<signed integer> |
	<float> |
	<ifloat> |
	<cfloat> |
	<pointer> |
	<array> |
	<slice> |
	<func> |
	<struct> |
	<interface>
	
bits: '8' | '16' | '32' | '64' | '128'
	
attributes: 
	'C' - const
	

void:		    'v'	
bool:		    'b'
char:		    'c'
unsigned integer:   'u' <bits>
signed integer:	    's' <bits>
float:		    'f' <bits>	
ifloat:		    'fi' <bits>	
cfloat:		    'fc' <bits>	
	
pointer:	    'P' <type>
array:		    'A' <type>
slice:		    'S' <type>
func:		    'F' <parameters> <return type>
struct:		    'X' 'N' <struct name> 'M' <module>
interface:	    'I' 'n' <interface name> 'm' <module>
	
return type: 'R' <type>
module: 'M' <name>
	
string => XN6string
	
module my.string; func (s string) len() size_t => __3lenPXN6stringRu64M2my6string

module builtin; func (s string) length() size_t => __6lengthPXNstringRu64

module abc {

type str struct {}
type istr interface{ test(); }

func (s string) test(i istr, u uint16) bool 
} =>
__4test P( X(n6string) I(n4istr m3abc) u16 ) R( b ) M( 3abc )
	 
