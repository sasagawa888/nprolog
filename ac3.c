/*
*  AC-3 
*/

// each element [var1,var2,expr]
void fd_enqueue(int x){
	fd_queue[fd_enque_idx] = x;
	fd_enque_idx++;
}

int fd_dequeue()
{	
	int res;

	res = fd_queue[fd_deque_idx];
	fd_deque_idx++;
	return(res);
}


void fd_enqueue_affected_arcs(int idx)
{
	int i,arc;

	for(i=0;i<fd_deque_idx;i++){
		arc = fd_queue[i];
		if(GET_ARITY(car(arc)) == idx)
			fd_enqueue(arc);
	}
}

void fd_remove(int idx, int x)
{
	int i;

	// if already removed return
	for(i=0;i<fd_rem_idx[idx];i++)
	{
		if(fd_removed[idx][i] == x)
			return;
	}

    fd_removed[idx][fd_rem_idx[idx]] = x;
    fd_rem_idx[idx]++;

	// for retest consistency for removed variable, enqueue arcs 
	fd_enqueue_affected_arcs(idx);
}

int fd_find_variables(int expr)
{
	if(compiler_variable_p(expr))
		return(wlist1(expr,0));
	else if (structurep(expr))
		return(append(fd_find_variables(cadr(expr)),
	                 (fd_find_variables(caddr(expr)))));
	else 
		return(NIL);
}

int pair_with(int x, int lst)
{
	if(nullp(lst))
		return(NIL);
	else 
		return(wcons(wlist2(x,car(lst),0),
	           pair_with(x,cdr(lst)),0));
}

int comb_two1(int head, int tail)
{
	if(nullp(head))
		return(NIL);
	else 
		return(append(pair_with(car(head),tail),
		       comb_two1(cdr(head),cdr(tail))));
}


// combination of 2 elements. [a,b,c] -> [[a,b],[a,c],[b.c]]
int comb_two(int lst)
{
	return(comb_two1(lst,cdr(lst)));
}

void fd_enqueue_arc(int expr)
{
	int vars,pairs,pair,arc;

	vars = fd_find_variables(expr);
	pairs = comb_two(vars);

	while(!nullp(pairs)){
		pair = car(pairs);
		arc = wlist3(car(pair),cadr(pair),expr,0);
		fd_enqueue(arc);
		arc = wlist3(cadr(pair),car(pair),expr,0);
		fd_enqueue(arc);
		pairs = cdr(pairs);
	}

}

void fd_consistent1(int expr, int idx)
{
    int left, right;

    left = fd_analyze(cadr(expr));
    right = fd_analyze(caddr(expr));

    if (fd_eq(expr)) {		//#=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) == car(right))	// value left ==value right
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		printf("remove val=%d\n", fd_min[idx] + fd_domain[idx]);
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (free_variablep(cadr(expr))) {
		fd_domain[GET_ARITY(cadr(expr))] = car(right);
		fd_min[GET_ARITY(cadr(expr))] = 0;
		fd_len[GET_ARITY(cadr(expr))] = 1;
		return;
	    } else if (in_interval(right, left))	// value right is in_interval range left
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		printf("remove val=%d\n", fd_min[idx] + fd_domain[idx]);
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (in_interval(left, right))	// value left is in_interval range right
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		printf("remove val=%d\n", fd_min[idx] + fd_domain[idx]);
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
		return;

	}
    } else if (fd_neq(expr)) {	//#\=
	if (length(left) == 1 && length(right) == 1) {
	    if (!(car(left) == car(right)))	// value left != value right
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (!in_interval(right, left))	// value right is not in_interval left range
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (!in_interval(left, right))	// value left is not in_interval right range
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
		return;
	}
    } else if (fd_smaller(expr)) {	//#<
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) < car(right))	// value left < value right
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (cadr(left) < car(right))	//max of range < value
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) < car(right))	//min of range  < value
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
			return;
	}
    } else if (fd_eqsmaller(expr)) {	//#<=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) <= car(right))	//value left < value right
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (cadr(left) <= car(right))	//max of range <= value
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) <= car(right))	//min of range  <= value
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
		return;
	}
    } else if (fd_greater(expr)) {	//#>
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) > car(right))	// value left > value right
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (car(left) > car(right))	//min of range > value
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) > cadr(right))	//value of max of range
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
		return;
	}
    } else if (fd_eqgreater(expr)) {	//#>=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) >= car(right))
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (car(left) >= car(right))	//min of range > value
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) >= cadr(right))	//value of max of range
		return;
	    else {
		fd_remove(idx, fd_min[idx] + fd_domain[idx]);
		fd_rem_sw = 1;
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
		return;
	}
    }
    return;

}

void fd_consistent(int c)
{
    int var, expr, idx, len, i;

	print(c);
    var = car(c);
    expr = caddr(c);
    idx = GET_ARITY(var);
    len = fd_len[idx];
    for (i = 0; i < len; i++) {
	fd_domain[idx] = i;
	fd_rem_sw = 0;
	fd_consistent1(expr, i);
    }
	fd_domain[idx] = UNBOUND;
}

int fd_empty()
{
	if(fd_deque_idx == fd_enque_idx)
		return(1);
	else 
		return(0);
}


void fd_propagate()
{	
	int arc;
    while (!fd_empty()) {
	arc = fd_dequeue();
	fd_consistent(arc);
    }
}


int b_label(int arglist, int rest, int th)
{
    int n, ind, arg1, save1, save2, save3, res;

    n = length(arglist);
    ind = makeind("label", n, th);
    save1 = wp[th];
    save2 = sp[th];
    save3 = ac[th];
    if (n == 1) {
	arg1 = car(arglist);

	fd_sets = reverse(fd_sets);
	fd_var_idx = 0;
	res = fd_solve();

	if (res == NO || res == COMPLETE)
	    return (NO);

      loop:
	unify(arg1, domain_to_value(revderef(arg1, th), th), th);
	if (prove_all(rest, sp[th], th) == YES)
	    return (YES);

	wp[th] = save1;
	unbind(save2, th);
	ac[th] = save3;
	res = next_domain();
	if (res == NO)
	    return (NO);
	if (res == COMPLETE)
	    return (YES);

	res = fd_solve();

	if (res == COMPLETE)
	    return (YES);
	else if (res == YES)
	    goto loop;
	else if (res == NO)
	    return (NO);
    }

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_ac3(int arglist, int rest, int th)
{
    int n, ind, sets;

    n = length(arglist);
    ind = makeind("ac3", n, th);
    if (n == 0) {
	sets = reverse(fd_sets);
	while(!nullp(sets)){
		fd_enqueue_arc(car(sets));
		sets = cdr(sets);
	}
	while(!fd_empty()){
		int arc;
		arc = fd_dequeue();
		print(arc);
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}