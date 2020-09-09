#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include "npl.h"


//-----------------------------
void initcell(void){
    int addr,x,version;

    for(addr=0; addr < HEAPSIZE; addr++){
        heap[addr].flag = FRE;
        SET_CDR(addr,addr+1);
        SET_CAR(addr,NIL);
        SET_AUX(addr,NIL);
    }
    hp = 0;
    fc = HEAPSIZE;

    for(x=0; x<HASHTBSIZE; x++)
        cell_hash_table[x] = NIL;


    //initialize symbol
    //address of each symbol is defined C macro at opl.h
    makeatom("nil",SIMP);  //address = 0
    makeatom("yes",SIMP);  //address = 2
    makeatom("no",SIMP);   //address = 4
    makeatom("end_of_file",SIMP); //address = 6
    makeatom("<undef>",SIMP);    //address = 8
    makeatom("!",SYS);    //address = 10
    makeatom(",",OPE);    //address = 12
    makeatom(";",OPE);    //address = 14
    makeatom("<leftparen>",SIMP);   //address = 16 '('
    makeatom("<rightparen>",SIMP);  //address = 18 ')'
    makeatom("call",COMP);  //address = 20
    makeatom("?-",OPE);    //address = 22
    makeatom("_",ANOY);     //address = 24
    makeatom(":-",OPE);    //address = 26
    makeatom("@",SYS);     //address = 28
    makeatom(":",SYS);     //address = 30
    makeatom("true",SYS);  //address = 32
    makeatom("false",SIMP); //address = 34
    makeatom("{}",PRED);  //address = 36
    makeatom("->",SYS);  //address = 38
    makeatom("$VAR",PRED); //address = 40
    makeatom("_",SIMP); //address = 42
    makeatom(".",OPE);  //addredd = 44

    version = list5(makeconst("opl"),makeint(1),makeint(7),makeint(0),NIL);
    SET_AUX(version,PRED);
    #if _WIN32
    flag_list = list10(cons(makeconst("bounded"),OPLFALSE),
                      cons(makeconst("integer_rounding_function"),makeconst("toward_zero")),
                      cons(makeatom("char_conversion",SYS),makeconst("on")),
                      cons(makeatom("debug",SYS),makeconst("off")),
                      cons(makeconst("max_arity"),makeint(ARITY-2)),
                      cons(makeconst("unknown"),makeconst("error")),
                      cons(makeconst("double_quotes"),makeconst("chars")),
                      cons(makeatom("char_set",SYS),makeconst("sjis")),
                      cons(makeconst("colon_sets_calling_context"),OPLTRUE),
                      cons(makeconst("version_data"),version));
    #elif __linux
    flag_list = list10(cons(makeconst("bounded"),OPLFALSE),
                      cons(makeconst("integer_rounding_function"),makeconst("toward_zero")),
                      cons(makeatom("char_conversion",SYS),makeconst("on")),
                      cons(makeatom("debug",SYS),makeconst("off")),
                      cons(makeconst("max_arity"),makeint(ARITY-2)),
                      cons(makeconst("unknown"),makeconst("error")),
                      cons(makeconst("double_quotes"),makeconst("chars")),
                      cons(makeatom("char_set",SYS),makeconst("unicode")),
                      cons(makeconst("colon_sets_calling_context"),OPLTRUE),
                      cons(makeconst("version_data"),version));
    #endif
}

int freshcell(void){
    int res;

    res = hp;
    hp = GET_CDR(hp);
    SET_CDR(res,0);
    fc--;
    return(res);
}

void initstream(void){
    standard_input = makestream(stdin,OPL_INPUT,OPL_TEXT,NIL,makeatom("user_input",SIMP));
    standard_output = makestream(stdout,OPL_OUTPUT,OPL_TEXT,NIL,makeatom("user_output",SIMP));
    standard_error = makestream(stderr,OPL_OUTPUT,OPL_TEXT,NIL,makeatom("error",SIMP));
    makealias("user_input",standard_input,STDIO);
    makealias("user_output",standard_output,STDIO);
    makealias("error",standard_error,STDIO);
}

void bindsym(int x, int val){

    if(alpha_variable_p(x))
        variant[x-CELLSIZE][0] = val;
    else if(atom_variable_p(x))
        SET_CAR(x,val);
    else
        error(ILLEGAL_ARGS, "nbindsym", x);

    push_stack(x);
}



int findvar(int x){

    if(alpha_variable_p(x))
        return(variant[x - CELLSIZE][0]);
    else if(atom_variable_p(x))
        return(GET_CAR(x));
    else
        error(ILLEGAL_ARGS, "findvar", x);
    return(NIL);
}


//existance check atom with property
//if not exist return 0.
int findatom(int x, int property){
    return(getatom(GET_NAME(x),property,hash(GET_NAME(x))));
}

//search atom with property
int getatom(char *name, int property, int index){
    int addr;

    addr = cell_hash_table[index];

    while(addr != NIL){
        if(strcmp(name,GET_NAME(car(addr))) == 0 &&
           GET_AUX(car(addr)) == property)
            return(car(addr));
        else
            addr = cdr(addr);
    }
    return(0);
}


int addatom(char *name, int property, int index){
    int addr,res;

    addr = cell_hash_table[index];
    addr = cons(res=makeatom1(name,property),addr);
    cell_hash_table[index] = addr;
    return(res);
}


int makeatom(char *name, int property){
    int index,res;

    index = hash(name);
    if((res=getatom(name,property,index)) != 0)
        return(res);
    else
        return(addatom(name,property,index));
}


int makeatom1(char *pname, int property){
    int addr;
    char *str;

    addr = freshcell();
    SET_TAG(addr,SINGLE);
    str = (char *)malloc(strlen(pname)+1);
    //if(str == NULL)
    //    error(MALLOC_OVERF,"makeatom",NIL);
    heap[addr].name = str;
    strcpy(heap[addr].name,pname);
    SET_CAR(addr,NIL);
    SET_CDR(addr,NIL);
    SET_AUX(addr,property);
    return(addr);
}

int makevariant(void){
    int addr;

    addr = ac;
    ac++;
    return(addr);
}


int hash(char *name){
    int res;

    res = 0;
    while(*name != NUL){
        res = res + (int)(unsigned char)*name;
        name++;
    }
    return(res % HASHTBSIZE);
}

//----------------------------------------

int makeint(int num){
    if(num >= 0)
        return(INT_FLAG | num);
    else
        return(num);
}

int makelong(long long int lngnum){
    int addr;

    addr = freshcell();
    SET_TAG(addr,LONGN);
    SET_LONG(addr,lngnum);
    return(addr);
}

int makeflt(double floatn){
    int addr;

    addr = freshcell();
    SET_TAG(addr,FLTN);
    SET_FLT(addr,floatn);
    return(addr);
}


// e.g x = Y -> make 'Y'
int makecopy(int x){
    int res;

    res = freshcell();
    SET_TAG(res,SINGLE);
    heap[res].name = GET_NAME(x);
    SET_AUX(res,SIMP);
    return(res);
}

int makestr(char *name){
    int pos,code,res;
    char str1[STRSIZE],str2[10],*str;

    if(double_flag == 2){ //string mode
        res = freshcell();
        SET_TAG(res,STR);
        str = (char *)malloc(strlen(name)+1);
        if(str == NULL)
            error(MALLOC_OVERF,"makestr",NIL);
        heap[res].name = str;
        strcpy(heap[res].name,name);
        SET_CAR(res,NIL);
        SET_CDR(res,NIL);
        SET_AUX(res,NIL);
        return(res);
    }

    //codes mode or chars mode
    res = NIL;
    strcpy(str1,name);
    pos = 0;
    code = NIL;
    while(str1[pos] != NUL){
        if(mode_flag == 0 && iskanji(str1[pos])){ //SJIS
            str2[0] = str1[pos++];
            str2[1] = str1[pos++];
            str2[2] = NUL;
        }
        else if(mode_flag == 1 && isUni2(str1[pos])){
            str2[0] = str1[pos++];
            str2[1] = str1[pos++];
            str2[2] = NUL;
        }
        else if(mode_flag == 1 && isUni3(str1[pos])){
            str2[0] = str1[pos++];
            str2[1] = str1[pos++];
            str2[2] = str1[pos++];
            str2[3] = NUL;
        }
        else if(mode_flag == 1 && isUni4(str1[pos])){
            str2[0] = str1[pos++];
            str2[1] = str1[pos++];
            str2[2] = str1[pos++];
            str2[3] = str1[pos++];
            str2[4] = NUL;
        }
        else if(mode_flag == 1 && isUni5(str1[pos])){
            str2[0] = str1[pos++];
            str2[1] = str1[pos++];
            str2[2] = str1[pos++];
            str2[3] = str1[pos++];
            str2[4] = str1[pos++];
            str2[5] = NUL;
        }
        else if(mode_flag == 1 && isUni6(str1[pos])){
            str2[0] = str1[pos++];
            str2[1] = str1[pos++];
            str2[2] = str1[pos++];
            str2[3] = str1[pos++];
            str2[4] = str1[pos++];
            str2[5] = str1[pos++];
            str2[6] = NUL;
        }
        else{//ascii code
            str2[0] = str1[pos++];
            str2[1] = NUL;
        }
        if(double_flag == 0 && mode_flag == 0) //SJIS
            code = makeint(sjis_to_code(str2));
        else if(double_flag == 0 && mode_flag == 1) //unicode
            code = makeint(utf8_to_ucs4(str2));
        else if(double_flag == 1) // chars
            code = makeconst(str2);

        res = cons(code,res);
        }
    return(listreverse(res));
}



int makestream(FILE *port, int i_o, int type, int action, int fname){
    int addr;

    addr = freshcell();
    SET_TAG(addr,STREAM);
    SET_PORT(addr,port);
    SET_CDR(addr,fname);
    SET_OPT(addr,i_o); //input/output/inout
    SET_VAR(addr,type); //text/binary
    SET_AUX(addr,action); //for eof_action
    SET_TR(addr,0); // for at_end_of_stream 1=end
    return(addr);
}

int makealias(char *name, int stream, int type){
    int res;

    res = makeatom(name,SIMP);
    SET_CAR(res,stream);
    SET_CDR(res,type);   // 0=normal  1=user_input,user_output,error
    return(res);
}

int makespec(int spec){
    int res;

    res = NIL;
    if(spec == XFX)
        res = makeconst("xfx");
    else if(spec == XFY)
        res = makeconst("xfy");
    else if(spec == YFX)
        res = makeconst("yfx");
    else if(spec == FX)
        res = makeconst("fx");
    else if(spec == FY)
        res = makeconst("fy");
    else if(spec == XF)
        res = makeconst("xf");
    else if(spec == YF)
        res = makeconst("yf");
    return(res);
}
/*
make exculsicve spec atom
*/
int makeexspec(int old_spec, int spec){
    if(old_spec == FX_XFX){
        if(spec == FY)
            return(makeconst("fx"));
        else if(spec == XFY || spec == YFX)
            return(makeconst("xfx"));
    }
    else if(old_spec == FY_XFX){
        if(spec == FX)
            return(makeconst("fy"));
        else if(spec == XFY || spec == YFX)
            return(makeconst("xfx"));
    }
    else if(old_spec == FY_XFY){
        if(spec == FX)
            return(makeconst("fY"));
        else if(spec == XFX || spec == YFX)
            return(makeconst("xfy"));
    }
    else if(old_spec == FY_YFX){
        if(spec == FX)
            return(makeconst("fy"));
        else if(spec == XFX || spec == XFY)
            return(makeconst("xfx"));
    }
    else if(old_spec == FY_YFX){
        if(spec == FX)
            return(makeconst("fY"));
        else if(spec == XFX || spec == XFY)
            return(makeconst("xfx"));
    }
    else if(old_spec == FY_XF){
        if(spec == FX)
            return(makeconst("fy"));
        else if(spec == YF)
            return(makeconst("xf"));
    }
    else if(old_spec == FX_YF){
        if(spec == FY)
            return(makeconst("fx"));
        else if(spec == XF  || spec == XFX || spec == YFX || spec == XFY)
            return(makeconst("yf"));
    }
    else if(old_spec == FY_XF){
        if(spec == FX)
            return(makeconst("fy"));
        else if(spec == YF || spec == XFX || spec == YFX || spec == XFY)
            return(makeconst("xf"));
    }
    else if(old_spec == FY_YF){
        if(spec == FX)
            return(makeconst("fy"));
        else if(spec == XF || spec == XFX || spec == YFX || spec == XFY)
            return(makeconst("yf"));
    }
    else
        return(NIL);

    return(NIL);
}

//stack
void push_stack(int x){
    stack[sp++] = x;
    if(sp >= STACKSIZE)
        error(STACK_OVERF,NIL,NIL);
}
int pop_stack(void){
    return(stack[--sp]);
}


//trail stack
//push predicate data to trail stack
void push_trail(int x){
    int i;

    if(variablep(x)){
        trail[tp][0] = 2;
        trail[tp][1] = CALL;
        trail[tp][2] = walpha_conversion(x);
        tp++;
        if(tp > TRAILSIZE)
            error(TRAIL_OVERF,"",NIL);
        return;
    }
    if(atomp(x)){
        trail[tp][0] = 1;
        trail[tp][1] = x;
        tp++;
        if(tp > TRAILSIZE)
            error(TRAIL_OVERF,"",NIL);
        return;
    }

    i = 0;
    trail[tp][i] = GET_LENGTH(x);
    if(trail[tp][i] > ARITY)
    	error(OUT_OF_RANGE, "arity is too much", x);
    i++;
    while(!nullp(x)){
    	trail[tp][i] = walpha_conversion(car(x));
        x = cdr(x);
        i++;
    }
    tp++;
    if(tp > TRAILSIZE)
        error(TRAIL_OVERF,"",NIL);
}

//without alpha conversion
void push_trail1(int x){
    int i;

    if(variablep(x)){
        trail[tp][0] = 2;
        trail[tp][1] = CALL;
        trail[tp][2] = x;
        tp++;
        if(tp > TRAILSIZE)
            error(TRAIL_OVERF,"",NIL);
        return;
    }
    if(atomp(x)){
        trail[tp][0] = 1;
        trail[tp][1] = x;
        tp++;
        if(tp > TRAILSIZE)
            error(TRAIL_OVERF,"",NIL);
        return;
    }

    i = 0;
    trail[tp][i] = length(x);
    if(trail[tp][i] > ARITY)
    	error(OUT_OF_RANGE, "arity is too much", x);
    i++;
    while(!nullp(x)){
        trail[tp][i] = car(x);
        x = cdr(x);
        i++;
    }
    tp++;
    if(tp > TRAILSIZE)
        error(TRAIL_OVERF,"",NIL);
}

void push_trail_body(int x){

    if(conjunctionp(x)){
        if(!operationp(cadr(x)) && !operationp(caddr(x))){
            push_trail(caddr(x));
            push_trail(cadr(x));
            return;
        }
        else if(operationp(cadr(x)) && !operationp(caddr(x))){
            push_trail(caddr(x));
            push_trail_body(cadr(x));
            return;
        }
        else if(!operationp(cadr(x)) && operationp(caddr(x))){
            push_trail_body(caddr(x));
            push_trail(cadr(x));
            return;
        }
        else{
            push_trail_body(caddr(x));
            push_trail_body(cadr(x));
            return;
        }
    }
    // if ';' disjuntion, it will be expanded to trail stack on run time.
    else if(disjunctionp(x)){
        x = walpha_conversion(x);
        push_trail1(x);
        return;
    }
    else if(colonp(x)){
        // (: atom pred(t1)) -> atom_pred(t1)
        if(atomp(caddr(x)))
            x = cons(concat_atom(cadr(x),caddr(x)),cdr(caddr(x)));
        else
            x = cons(concat_atom(cadr(x),car(caddr(x))),cdr(caddr(x)));
        push_trail(x);
    }
    else if(nullp(x)){
        return;
    }
    else{
        push_trail(x);
        return;
    }
}

void push_trail_body_with_ask(int x){

    variables = listreverse(unique(varslist(x)));
    x = anoymous_conversion(x); // e.g. f(_,_,_) -> f(v_1,v_2,v_3)
    trail[tp][0] = 1;
    trail[tp][1] = makeatom("%ask",SYS);
    tp++;
    if(tp > TRAILSIZE)
        error(TRAIL_OVERF,"",NIL);
    push_trail_body1(x);
}

void push_trail_body_with_findall_help(int pred, int var){

    variables = listreverse(unique(varslist(pred)));
    trail[tp][0] = 2;
    trail[tp][1] = makeatom("%findall_help",SYS);
    trail[tp][2] = var;
    tp++;
    if(tp > TRAILSIZE)
        error(TRAIL_OVERF,"",NIL);
    push_trail_body1(pred);
}

void push_trail_body_with_bagof_help(int pred, int var, int free){

    variables = listreverse(unique(varslist(pred)));
    trail[tp][0] = 3;
    trail[tp][1] = makeatom("%bagof_help",SYS);
    trail[tp][2] = var;
    trail[tp][3] = free;
    tp++;
    if(tp > TRAILSIZE)
        error(TRAIL_OVERF,"",NIL);
    push_trail_body1(pred);
}



void push_trail_body1(int x){

    if(conjunctionp(x)){
        if(!operationp(cadr(x)) && !operationp(caddr(x))){
            push_trail1(caddr(x));
            push_trail1(cadr(x));
            return;
        }
        else if(operationp(cadr(x)) && !operationp(caddr(x))){
            push_trail1(caddr(x));
            push_trail_body1(cadr(x));
            return;
        }
        else if(!operationp(cadr(x)) && operationp(caddr(x))){
            push_trail_body1(caddr(x));
            push_trail1(cadr(x));
            return;
        }
        else{
            push_trail_body1(caddr(x));
            push_trail_body1(cadr(x));
            return;
        }
    }
    //
    else if(disjunctionp(x)){
        push_trail1(x);
        return;
    }
    else if(colonp(x)){
        // (: atom pred(t1)) -> atom_pred(t1)
        if(atomp(caddr(x)))
            x = cons(concat_atom(cadr(x),caddr(x)),cdr(caddr(x)));
        else
            x = cons(concat_atom(cadr(x),car(caddr(x))),cdr(caddr(x)));
        push_trail1(x);
    }
    else if(nullp(x)){
        return;
    }
    else{
        push_trail1(x);
        return;
    }
}



void store_goal(int nest){
    int i,n;

    tp--;
    n = trail[tp][0];
    for(i=0;i<=n;i++){
        goal[i] = trail[tp][i];
        store[nest][i] = trail[tp][i];
    }
    if(GET_AUX(goal[1]) == PRED ||
       GET_AUX(goal[1]) == COMP)
        context = GET_VAR(goal[1]); //for calling_context
}

void retract_goal(int nest){
    int i,n;

    n = store[nest][0];
    for(i=0;i<=n;i++){
        trail[tp][i] = store[nest][i];
        goal[i]      = store[nest][i];
    }

}

/*
void set_head(int x){
    int i,n;

    if(atomp(x)){
        head[0] = 1;
        head[1] = walpha_conversion(x);
        return;
    }
    n = length(x);
    head[0] = n;
    for(i=1;i<=n;i++){
        head[i] = walpha_conversion(car(x));
        x = cdr(x);
    }
}
*/

//------for JUMP compiler-----

int get_tp(void){
	return(tp);
}

int set_tp(int x){
	tp = x;
    return(0);
}

int get_sp(void){
	return(sp);
}

int callsubr(int x, int nest, int n){
    return((GET_SUBR(x)(nest,n)));
}

int set_sp(int x){
	sp = x;
    return(0);
}

int get_wp(void){
    return(wp);
}

int set_wp(int x){
    wp = x;
    return(0);
}

int get_goal(int n){
	return(goal[n]);
}

int set_goal(int n, int x){
    goal[n] = x;
    return(x);
}

int listcons(int x, int y){
	int res;

    res = cons(x,y);
    SET_AUX(res,LIST);
    return(res);
}

int wlistcons(int x, int y){
    int res;

    res = wcons(x,y);
    SET_AUX(res,LIST);
    return(res);
}

int get_trail_end(void){
	return(trail_end);
}

int set_trail_end(int x){
    trail_end = x;
    return(x);
}

int set_car(int x, int y){
	SET_CAR(x,y);
    return(x);
}

int set_cdr(int x, int y){
	SET_CDR(x,y);
    return(x);
}

int set_aux(int x, int y){
    SET_AUX(x,y);
    return(x);
}

int set_var(int x, int y){
    SET_VAR(x,y);
    return(x);
}

int makepred(char *name){
    return(makeatom(name,PRED));
}

int makeconst(char *name){
    return(makeatom(name,SIMP));
}

int makecomp(char *name){
    return(makeatom(name,COMP));
}

int makesys(char *name){
    return(makeatom(name,SYS));
}

int makeope(char *name){
    return(makeatom(name,OPE));
}

int makeuser(char * name){
    return(makeatom(name,USER));
}

int makevar(char *name){
	int y;

    y = makeatom(name,VAR);
    SET_CAR(y,UNBIND);  //value
    SET_CDR(y,UNBIND);  //alpha variable
    SET_VAR(y,NIL);
    return(y);
}

int makestrflt(char *str){
    return(makeflt(atof(str)));
}

int makestrlong(char *str){
    return(makelong(atoi(str)));
}

void debug(void){
	DEBUG
}


/*
when cont == NIL -> execute body and return
when cont <= HEAPSIZE and not NIL -> invoke interpreter
when cont > HEAPSIZE execut body+cont and return
*/
int proceed(int body, int cont){
    int f,l,save1,save2,save3,i,args;

    if(cont > HEAPSIZE)
        return(proceed(op_connect(body,cont),NIL));
    else if(cont <= HEAPSIZE && !nullp(cont))
        return(proceed(op_connect(body,cont),NIL));
    else if(!nullp(body) && body <= HEAPSIZE){
        save1 = tp;
        save2 = sp;
        save3 = trail_end;
        if(prove_all(save3,save2,body) == YES)
            return(YES);
        else{
            tp = save1;
            unbind(save2);
            retract_goal(body);
            trail_end = save3;
            return(NO);
        }
    }
    else if(nullp(body))
        return(YES);
    else if(builtinp(body)){
        if(singlep(body)){
            f = body;
            args = NIL;
            l = 0;
        }
        else{
            f = car(body);
            args = cdr(body);
            l = length(args);
        }
        for(i=0;i<l;i++){
            set_goal(i+2,car(args));
            args = cdr(args);
        }
        if(callsubr(f,0,l) == YES)
            return(proceed(cont,NIL));
        else
            return(NO);
    }
    else if(user_operation_p(body)){
        if(getatom(GET_NAME(body),COMP,hash(GET_NAME(body))) != 0)
            goto single_compiled;
        else
            goto single_predicate;
    }
    else if(compiledp(body)){
        single_compiled:
        if(singlep(body)){
            f = body;
            args = NIL;
            l = 0;
        }
        else{
            f = car(body);
            args = cdr(body);
            l = length(cdr(body));
        }
        for(i=0;i<l;i++){
            set_goal(i+2,car(args));
            args = cdr(args);
        }
        if(callsubr(f,cont,l) == YES)
            return(YES);
        else
            return(NO);
    }
    else if(predicatep(body)){
        single_predicate:
        save1 = tp;
        save2 = sp;
        save3 = trail_end;
        set_length(body);
        push_trail1(body);
        if(prove_all(trail_end,sp,1) == YES)
            return(proceed(cont,NIL));
        else{
            unbind(save2);
            trail_end = save3;
            return(NO);
        }
    }
    else if(operationp(body) && car(body) == AND){
        if(builtinp(cadr(body))){
            if(singlep(cadr(body))){
                f = cadr(body);
                args = NIL;
                l = 0;
            }
            else{
                f = car(cadr(body));
                args = cdr(cadr(body));
                l = length(cdr(cadr(body)));
            }
            for(i=0;i<l;i++){
                set_goal(i+2,car(args));
                args = cdr(args);
            }
            if(callsubr(f,0,l) == YES)
                return(proceed(caddr(body),cont));
            else
                return(NO);
        }
        else if(user_operation_p(cadr(body))){
            if(getatom(GET_NAME(cadr(body)),COMP,hash(GET_NAME(cadr(body)))) != 0)
                goto and_compiled;
            else
                goto and_predicate;
        }
        else if(compiledp(cadr(body))){
            and_compiled:
            if(singlep(cadr(body))){
                f = cadr(body);
                args = NIL;
                l = 0;
            }
            else{
                f = car(cadr(body));
                args = cdr(cadr(body));
                l = length(cdr(cadr(body)));
            }
            for(i=0;i<l;i++){
                set_goal(i+2,car(args));
                args = cdr(args);
            }
            return(callsubr(f,op_connect(caddr(body),cont),l));
        }
        else if(predicatep(cadr(body))){
            and_predicate:
            save1 = tp;
            save2 = sp;
            save3 = trail_end;
            set_length(cadr(body));
            push_trail1(cadr(body));
            if(prove_all(trail_end,sp,1) == YES)
                return(proceed(op_connect(caddr(body),cont),NIL));
            else{
                unbind(save2);
                trail_end = save3;
                return(NO);
            }
        }
        if(operationp(cadr(body)) && car(cadr(body)) == OR){
            if(proceed(cadr(body),NIL) == YES)
                return(proceed(caddr(body),cont));
            else
                return(NO);
        }
    }
    else if(operationp(body) && car(body) == OR){
        if(ifthenp(cadr(body))){
            if(proceed(cadr(body),NIL) == YES)
                return(proceed(NIL,cont));
            else
                return(proceed(caddr(body),cont));
        }
        else if(!has_cut_p(cadr(body))){
            if(proceed(cadr(body),cont) == YES)
                return(proceed(NIL,cont));
            else
                return(proceed(caddr(body),cont));
        }
        else if(has_cut_p(cadr(body))){
            if(proceed(before_cut(cadr(body)),NIL) == YES){
                if(proceed(after_cut(cadr(body)),NIL) == YES)
                    return(proceed(NIL,cont));
                else
                    return(NO);
            }
            else
                return(proceed(caddr(body),cont));
        }
        else
            return(proceed(caddr(body),cont));
    }
    else
        return(NO);

    return(NO);
}


int op_connect(int x, int y){
    if(nullp(x))
        return(y);
    else if(nullp(y))
        return(x);
    else if(!operationp(x))
        return(wlist3(AND,x,y));
    else
        return(wlist3(car(x),cadr(x),op_connect(caddr(x),y)));
}
