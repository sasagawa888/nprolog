idea memo
continuation passing style

foo(X) :- p1(X),p2(X),p3(X).
if(cps(p1(X),[p2(X),p3(X)])==YES)
    return(YES);
else
    return(NO);

bar(X) :- p1(X),p2(X);p3(X),p4(X).
if(cps(p1(X),[p2(X)]))==YES)
    return(YES);
else if(cps(p3(X),[p4(X)])==YES)
    return(YES);
else
    return(NO);

boo(X) :- p1(X),p2(X),!,p3(X),p4(X).
if(cps(p1(X),[p2(X)])==YES){
    if(cps(p3(X),[p4(X)])==YES)
        return(YES);
    else
        return(NO);
}else return(NO);

cps(int p,int rest){
    if(call(p)==YES)
        return(cps(car(rest),cdr(rest)));
    else
        return(NO);
}

int conjunction(int x){
    if(nullp(x))
        return(YES);
    else{
        call(car(x));
        conjunction(cdr(x));
    }       
}





