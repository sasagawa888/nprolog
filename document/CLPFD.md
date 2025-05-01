# CLPFD
under construction

# Usage

```
?- use_module(clpfd).
```

# Specification

- X #= Y
- X #\= Y
- X #> Y
- X #< Y
- X #>= Y
- X #<= Y


# memo
CLP(FD): Organization of Algorithms and Data Structures

## Data Structures

```
    Variable List
    Example: [var_1, var_2]
    Variables are associated with their respective domains:
    var_1 = [1, 2, 3]
    var_2 = [0, 1, 2]

    Domain List
    Example:
    var_1 : var_2 → [[1,1], [2,2]]
```

## Algorithms

    in Predicate
    Generates the domain for each variable and associates it with the corresponding variable atom.

```
    Equality Constraint #=
    The relation is instantiated and recorded in the domain list.
    At this time, if any variable is not yet determined, a * is inserted in its place.
    If the domain of a variable is not concretely defined, the result is NO.

    Examples:
    X = [1,2], Y = [1,2,3] → X #= Y → domain = [[1,1], [2,2]]

    X = [1,2], Y = [1,2,3], Z = [0,1,2] → X #= Y → domain = []
    Z #<3 → domain[[1,1,3],[2,2,3]]

    Inequality Constraint #\=
    Similar to equality, the relation is instantiated and added to the domain list.
    Insert * for undetermined variables.
    If variable domains are not defined concretely, return NO.

    Examples:
    X = [1,2], Y = [1,2,3] → X #\= Y → domain = [[1,2], [1,3], [2,1], [2,3]]
    
    X = [1,2], Y = [1,2,3], Z = [0,1,2] → X #\= Y → domain = []
    X #= 0 → domain = [[1,2,0], [1,3,0], [2,1,0], [2,3,0]]

    Comparison Constraints #<, #>, #=<, #>=
    These constraints narrow the domain of variables.
    If a variable is narrowed down to a single value, it is considered determined and recorded in the domain list.
    If the domain list already exists, incompatible entries are removed.
    If * is present, it is replaced with a concrete value.

    Example:
    X = [1,2,3] → X #< 2 → X = [1]
    If domains are not concretely defined, represent them abstractly:
    X #> 0 → X = [0,inf]

    label Predicate
    The label predicate searches for a solution that satisfies the constraints processed up to that point and generates it in the domain. If no solution exists, it returns no.


    Example:
    X + Y + Z #= 9, with X in 1..3, Y in 1..3, Z in 1..3.

    Assume X = 1. Then Y + Z = 8.
    However, since the maximum values of Y and Z are both 3, this cannot be satisfied.
    Therefore, all choices with X = 1 fail.

    Assume X = 2. Then Y + Z = 7.
    Again, with the ranges of Y and Z, this is not possible.
    So all choices with X = 2 also fail.

    Assume X = 3. Then Y + Z = 6.

    Assume Y = 1, then Z = 5, which is outside the domain. So Y = 1 fails.

    Assume Y = 2, then Z = 4, which is also outside the domain. So Y = 2 fails.

    Assume Y = 3, then Z = 3, which is within the domain. Success.
   
   Standard form of expressions: To perform inference efficiently, we establish a standard form for expressions where the left-hand side is a variable and the right-hand side is a constant. For example, X #= Y becomes X - Y #= 0. At the stage where we assume X = 1, we transform the expression to Y #= 1.
   For simple expressions, this might seem less efficient, but for more complex expressions, it becomes more efficient. In cases like X + Y + Z #= 9, it is easier to formalize the reasoning process.

   X=1  1+Y+Z=9 -> Y+Z=8 fail
   X=2  2+Y+Z=9 -> Y+Z=7 fail
   x=3  3+Y+Z=9 -> Y+Z=6 succ

   data structure
   int constraint_set;   e.g. [X in 1..3,Y in 1..3,X#=Y]

   local int env is list
   [[var1,list1],[var2,list2]] e.g. [[var_1,[1,2,3]],[var_2,[2,3,4]]] 

   local int index is list
   [1,1] -> var_1=1,var_2=2 when env=[[var_1,[1,2,3]],[var_2,[2,3,4]]] 

   local int domain is list
   e.g. var_1,var_2,var_3...
        [1,2,3]

   bind_variable(expr,env,index)
   { 
     e.g. X+Y#=0 env=[[X,[1,2]],[Y,[2,3]]] index=[1]
     
     SET_CDR(X,nth(find(X,env)))
   }

   satisfiablep(expr,env)
   {
       if(satisfiablep1(expr,env))
             return(YES);
       else
             return(NO);
   }

   satisfiablep1(expr,env)
   {
      e.g. X+Y#=3  X=[0,1] Y=[0,1] -> NO  (because 1+1 < 3)
           X+Y#=3  X=[0,1,2] Y=[0,1] -> YES (because 2+1=3)
           X+Y#<3  X=[0,1] Y=[0,1] -> YES (because 0+0<3)
           X+Y#<3  X=[3,4] Y=[2,3] -> NO  (because 3+2>3)
           X-Y#<3  X=[3,4] Y=[2,3] ->YES (because 3-2<3 or 4-3<3)
   }

   standardization(expr)
   {
      e.g. X #= Y -> X-Y #=0
           X #= Y+1 -> X-Y#=1
           X+Y+Z #= 1 -> X+Y+Z #= 1
   }

   label/1
   res = propagate_all(constraint_set,[],[]);
   if(unify(res,arg1)=YES)
      return(rest,sp[th],th);
   else 
      return(NO);
   

   propagate_all(set,env,domain){
        if(set == NIL)
            return(domain)
        else {
            if(propagete(car(set),env,init_index(env),domain)==YES) 
               //e.g. init_index(env) = [1] 
               propagate_all(cdr(set));
            else
               return(NO);
        }
   }

   propagate(expr,env,index,domain){
        if(expr == NIL)
            return(domain);

        domain = bind_variable(expr,env,index,domain);
        if(saticfiablep(expr,env)=YES)
            index = new_index(index);
            return(propagate(new_expr(expr),env,index,domain));
        else if (next_bind_variable(expr,env,new_index(index))=YES)
            index = new_index(index);
            domain = bind_variable(expr,env,index,domain);
            if(saticfiablep(expr,env)=YES)
                return(propagate(new_expr(expr),new_exv(env),org,domain));
        else
           return(NO);
   }

   
```

