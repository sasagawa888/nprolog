# DCG

## Usage
:- use_module(dcg).

## Spec
□ phrase/2

phrase(DCGBody, List)

Applies a DCG rule (DCGBody) to the input list List.

Internally, DCG rules are translated into predicates that take two arguments (a difference list: input and remaining list).
phrase/2 is syntactic sugar that succeeds only when the entire input list is consumed (i.e., the remaining list becomes []).

Success condition: DCGBody successfully parses (or generates) List and consumes all elements (no remainder).

Example

% Example: parse "ab"
ab --> [a], [b].

?- phrase(ab, [a,b]).
yes
?- phrase(ab, [a,b,c]).
no

Can also be used for generation

?- phrase(ab, X).
X = [a,b].

Notes

DCGBody is typically a non-terminal symbol (e.g., ab) or a DCG body expression.

On failure, it simply fails (no). Exception behavior is implementation-dependent.

□ phrase/3

phrase(DCGBody, List, Rest)

Applies a DCG rule (DCGBody) to the input list List, returning the remaining unconsumed list in Rest.

Success condition: DCGBody consumes a prefix of List, and the remaining suffix unifies with Rest.

Example

ab --> [a], [b].

?- phrase(ab, [a,b,c], Rest).
Rest = [c].

?- phrase(ab, [a], Rest).
no

Can also be used for generation

?- phrase(ab, X, [c]).
X = [a,b,c].

Relationship to phrase/2

phrase(G, L) :- phrase(G, L, []).
□ dcg_expand/2

dcg_expand(DCGRuleOrBody, Expanded)

Expands a DCG rule or body into its corresponding standard Prolog clause(s) using difference lists.

Typical input

A rule: (Head --> Body)

In some implementations, a body expression may also be accepted

Output

The expanded Prolog clause (or term representing it)

Conceptual example

ab --> [a], [b].

is approximately expanded into:

ab(S0, S) :- S0 = [a|S1], S1 = [b|S].

(The actual variable names and structure are implementation-dependent.)

Purpose

To inspect how DCG rules are translated internally

To normalize DCG syntax before compilation or further processing

Notes (implementation-dependent aspects)

Whether both full rules and standalone bodies are supported

The exact format of the returned expanded clause

How embedded goals {Goal} inside DCG rules are expanded


## Example
The following is an example from Professor Hideyuki Nakashima's "Prolog".

A dog bites a postman.

This English sentence has a structure. Its structure follows certain grammatical rules. 


```
Sentence-> noun phrase, verb phrase
Noun phrases-> articles, nouns
Article-> a
Noun-> dog
Noun-> postman
Verb phrase-> verb, noun phrase
Verb-> bits 
```
It's possible to write this directly in Prolog, but there's an easier way.
That is DCG. It is possible to write the above rules almost as they are.

Write the following code to a file and load it with consult in the same way as the Prolog code. 


```
s --> np,vp.
np --> det,n.
det -->[a].
n -->[dog].
n -->[postman].
vp --> v,np.
v -->[bites].
```

The grammar category is abbreviated. 

```
sentence　s
noun　n
noun　phrase　np
verb　v
determiner　det
verb　phrase
```

Let's run this on the N-Prolog processing system.
You can check if the sentence is correct with the predicate phrase. 


```
| ?- phrase(s,[a,dog,bites,a,postman]).
yes
| 
```

In this way, it was confirmed that the sentence given in the list has the given sentence structure. What if you give the wrong sentence? 


```
| ?- phrase(s,[bites,a,dog,a,postman]).
no
|
```

False is returned. It violates the grammar rules.

Interestingly, you can also generate sentences that meet grammatical rules. 

```
| ?- phrase(s,X).
X = [a,dog,bites,a,dog];
X = [a,dog,bites,a,postman];
X = [a,postman,bites,a,dog];
X = [a,postman,bites,a,postman];
no
| 
```

When I typed a semicolon and backtracked, some sentences came out.
The meaning is strange, but it follows the grammatical rules. 
