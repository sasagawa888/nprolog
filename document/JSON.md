# JSON
under construction

# usage

```
use_module(json).

?- term_json(foo(1),J).
J = {"predicate":"foo","argument":[1]} .
yes
?- 
```


# Spec 

term_json(Term,Json).


# Caution
To simplify JSON parsing, the handling of strings has been modified. By default, strings are represented enclosed in $. However, when using the JSON module, strings are represented enclosed in ". To revert to the original behavior, use reset_json.
