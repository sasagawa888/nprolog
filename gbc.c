#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include "npl.h"


//---------garbage collection-----------
void gbc(void){
    int addr;

    if(gbc_flag){
        printf("enter GBC free=%d\n", fc);
        fflush(stdout);
    }

    gbcmark();
    gbcsweep();
    fc = 0;
    for(addr=0; addr < HEAPSIZE; addr++)
        if(IS_EMPTY(addr))
            fc++;
    if(gbc_flag){
        printf("exit  GBC free=%d\n", fc);
        fflush(stdout);
    }
}


void markcell(int addr){
    int x;

    if(IS_ALPHA(addr)){
        if(variant[addr - CELLSIZE][0] != UNBIND){
            markcell(variant[addr - CELLSIZE][0]);
            return;
        }
        else
            return;
    }
    if(IS_OUTCELL(addr))
        return;

    if(USED_CELL(addr))
        return;

    if(addr == 0)
        return; //NIL

    MARK_CELL(addr);
    switch(GET_TAG(addr)){
        case EMP:
        case INTN:
        case FLTN:
        case LONGN: return;
        case STREAM:markcell(cdr(addr));
                    return;
        case SINGLE: markcell(car(addr));
                    markcell(cdr(addr));
                    markcell(GET_VAR(addr));
                    markcell(GET_ATTR(addr));
                    markcell(GET_ARITY(addr));
                    return;
        case BIGX:  x=addr;
                    do{
                        MARK_CELL(x);
                        x = next(x);
                    }while(!nullp(x));
                    return;

        case STRUCT:
                    markcell(car(addr));
                    markcell(cdr(addr));
                    markcell(GET_VAR(addr));
                    return;

    }
}

void gbcmark(void){
    int i,j;

    //mark nil and basic symbol
    MARK_CELL(NIL);
    MARK_CELL(YES);
    MARK_CELL(NO);
    MARK_CELL(FEND);
    MARK_CELL(UNDEF);

    //mark variable-list
    markcell(variables);

    //mark listing-list
    markcell(predicates);

    //mark cells chained by symbol hash table
    for(i=0; i<HASHTBSIZE; i++)
        markcell(cell_hash_table[i]);

    //mark stream
    markcell(standard_input);
    markcell(standard_output);
    markcell(standard_error);
    markcell(input_stream);
    markcell(output_stream);
    markcell(error_stream);

    //mark stack
    for(i=0;i<sp;i++){
        if(alpha_variable_p(stack[i])){
            markcell(variant[stack[i]-CELLSIZE][0]);
            markcell(variant[stack[i]-CELLSIZE][1]);
        }
        else
            markcell(stack[i]);
    }

    //mark trail stack
    for(i=0;i<tp;i++){
        for(j=2;j<ARITY;j++){
            markcell(trail[i][j]);
        }
    }
    //mark store stack
    for(i=0;i<TRAILSIZE;i++){
        if(store[i][0] != 0){
            for(j=2;j<ARITY;j++)
                markcell(store[i][j]);
        }
    }
    //mark catch_dt
    for(i=0;i<=catch_pt;i++){
        markcell(catch_dt[i][0]);
        markcell(catch_dt[i][1]);
    }

    //mark cleanup_dt
    markcell(cleanup_dt);
}

void gbcsweep(void){
    int addr;

    addr = 0;
    while(addr < HEAPSIZE){
        if(USED_CELL(addr))
            NOMARK_CELL(addr);
        else{
            clrcell(addr);
            SET_CDR(addr,hp);
            hp = addr;
        }
        addr++;
    }
}

void clrcell(int addr){
    SET_TAG(addr,EMP);
    free(heap[addr].name);
    heap[addr].name = NULL;
    SET_CAR(addr,0);
    SET_CDR(addr,0);
    SET_AUX(addr,0);
    SET_OPT(addr,0);
    SET_TR(addr,0);
}

//when fc is less FREESIZE invoke gbc()
void checkgbc(void){
    if(fc < FREESIZE){
        gbc();
    }
}
