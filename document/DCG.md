# DCG
To use DCG call module.
use_module(dcg).

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

