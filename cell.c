#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include "npl.h"


//-----------------------------
void initcell(void){
    int addr,x;

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
    makeatom("-->",OPE);  //addredd = 46

    
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
    int res;
    char *str;

    
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



int makestream(FILE *port, int i_o, int type, int action, int fname){
    int addr;

    addr = freshcell();
    SET_TAG(addr,STREAM);
    SET_PORT(addr,port);
    SET_CDR(addr,fname);
    SET_OPT(addr,i_o); //input/output/inout
    SET_VAR(addr,type); //text/binary
    SET_AUX(addr,action); //for eof_action
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


//------for JUMP compiler-----
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
