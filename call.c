int call(int pred, int arglist, int th)
{
    proof[th]++;
    arglist = deref(arglist, th);

	if (predicatep(pred)) 
	return (prove(wcons(pred,arglist,th), sp[th], NIL, th));
     else 
	return ((GET_SUBR(pred)) (arglist, NIL, th) == YES);
	
    return (NO);
}
