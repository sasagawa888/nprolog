# Superset
 N-Prolog is compatible with ARITY/PROLOG. This is an old language specification from the 1980s. Some predicates have been added to run more modern code, primarily based on ISO-Prolog. However, please note that these may not necessarily conform to the ISO-Prolog specification.

 # Spec
The following extension functions respect ISO-Prolog as much as possible, but they are provided primarily for the purpose of being a backward-compatible extension in N-Prolog. Please refrain from pointing out differences with ISO.

 ```
\+ (not)
atom_concat/3
append/3
member/2
between/3
select/3
succ/2
maplist/2
compound/1
ground/1
once/1
atom_codes/2
atom_chars/2
char_code/2
number_codes/2
number_chars/2
predicate_property/2
reverse/2 
bagof/3
setof/3
findall/3
existerrors/2
write_canonical/1 /2
atom_length/2
get_char/1 2
get_byte/1 2
put_char/1 
flush_output/0
catch/3
throw/1
unify_with_occurs_check/2
current_input/1
current_output/1
set_input/1
set_output/1
use_module/1
module/1
```

# String
In ARITY/PROLOG, strings were enclosed in $ symbols. In N-Prolog, this convention is maintained, but strings enclosed in double quotes (") are also recognized as strings. However, similar to ISO-Prolog, these are treated as lists.

```
N-Prolog Ver 3.80
?- X = "abc".
X = [97,98,99] .
yes
?- 

```

# Function
In ARITY/PROLOG, the ^ symbol is used for exponentiation. However, since ** is used for exponentiation in ISO-Prolog, we allow this as well.

```
N-Prolog Ver 3.80
?- X is 2**3.
X = 8 .
yes
?- 
```