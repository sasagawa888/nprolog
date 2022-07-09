/*
SAM Sasagawa Abstract Machine
idea memo
fact(0,1).
fact(N,Y) :-
  N1 is N-1,
  fact(N1,Z),
  Y is N*Z.
SAS  ASEM
fact:
unify(A0,0),jrf(next),unify(A1,1),jrf(next),ret,
next:
unify(A0,N),retf,unify(A1,Y),retf,is(N1,-(N,1)),bias(2),pushB,ld(A0,N1),ld(A1,Z),call(fact),popB,is(Y,*(N,Z)).
byte code
unify,A0,0,jrf,4,unify,A1,1,jrf,2,ret,
unify,A0,N,retf,unify,A1,Y,retf,is,N1,-,N,1,bias,2,pushB,ld,A0,N1,ld,A1,Z,call,fact,popB,is,Y,*,N,Z.
list data
[1,2,3] -> cons(1,cons(2,3)) => cons,1,cons,2,3.
predicate
foo(a,b,c) -> foo,3,a,b,c.
atom -> heap
var -> variant area 
query ?- foo(X,Y,Z) -> ld,A0,X,ld,A1,Y,ld,A2,Z,call,foo.
*/

//register
int a1,a2,a3,a4,a5,a6; // input register
int b;  // bias register
int pc; //program counter
int flag;  // if unify success 1 else 0

// byte code
int code[1024];

//abstrct machine
void sam(){
  static const void *JUMPTABLE[] = 
    {&&CASE_NOP,  //0
    &&CASE_HALT,  //1
    &&CASE_JP,    //2
    &&CASE_JPNT,  //3
    };
  CASE_NOP:
   pc = pc + 1;
   goto *JUMPTABLE[code[pc]];

  CASE_HALT:
    return;

  CASE_JP:
   pc = code[pc+1];
   goto *JUMPTABLE[code[pc]];

  CASE_JPNT:
   if(flag == 0)
   {
    pc = code[pc+1];
    goto *JUMPTABLE[code[pc]];
   }
   else
   {
    pc = code[pc+1];
    goto *JUMPTABLE[code[pc]];
   }

}

/*
* my old Scheme implementation "Normal". Remembering VM.
//----------VM1----------------------------
int vm1(void){
	int arg,res,clo,m,n,o,i,j,x,y,z,size,clo_code,cont,cont_code,cont_stack,
        save_module,cps_env,cps_lsp,cps_pc;
        
    char str[SYMSIZE],c;
	
	
	static const void *JUMPTABLE[] = 
    {&&CASE_NOP,  //0
    &&CASE_HALT,  //1
    &&CASE_CONST, //2
    &&CASE_LVAR,  //3
    &&CASE_GVAR,  //4
    &&CASE_LSET,  //5
    &&CASE_GSET,  //6
    &&CASE_POP,   //7
    &&CASE_JUMP,  //8
	&&CASE_TJUMP, //9
    &&CASE_FJUMP, //10
    &&CASE_RETURN,//11
    &&CASE_ARGS,  //12
    &&CASE_CALL,  //13
    &&CASE_CALLJ, //14
    &&CASE_FN,    //15
    &&CASE_SAVE,  //16
    &&CASE_PRIM,  //17
    &&CASE_DEF,   //18
    &&CASE_DEFM,  //19
    &&CASE_DEFH,  //20
    &&CASE_NEQP,  //21
    &&CASE_SMLP,  //22
    &&CASE_ESMLP, //23
    &&CASE_GRTP,  //24
    &&CASE_EGRTP, //25
    &&CASE_ZEROP, //26
    &&CASE_ADD1,  //27
    &&CASE_SUB1,  //28
    &&CASE_ADD2,  //29
    &&CASE_SUB2,  //30
    &&CASE_GREF,  //31
    &&CASE_CATCH, //32
    &&CASE_PAUSE, //33
    &&CASE_CAR,   //34
    &&CASE_CDR,   //35
    &&CASE_CONS,  //36
    &&CASE_ADAPT, //37
    &&CASE_DEFLIB,//38
    &&CASE_EXPLIB,//39
    &&CASE_IMPLIB, //40
    &&CASE_CONT,   //41
    &&CASE_APPARG, //42
    &&CASE_PUSHWND,//43
    &&CASE_POPWND, //44
    &&CASE_PUSHEXH,//45
    &&CASE_POPEXH, //46
    &&CASE_EXCEPT, //47
    &&CASE_RETRACT,//48
    &&CASE_R9,     //49
    &&CASE_R10,    //50
    &&CASE_DEREF,  //51
    &&CASE_UNIFY,  //52
    &&CASE_UNIFYC, //53
    &&CASE_UNIFYV, //54
    &&CASE_UNIFYS, //55
    &&CASE_TRY,    //56
    &&CASE_CALLP,  //57
    &&CASE_PROCEED,//58
    &&CASE_FAIL,   //59
    &&CASE_ARGSP,  //60
    &&CASE_CUT,	   //61
    &&CASE_CALLM   //62
    };
	
    n_args = 0;
    for(i=lst; i>=0; i--){
    	clr_ref(i);
        local_stack[i] = NIL;
    }
    lsp = 0; //(Prolog local_stack_pointer)
	lst = lsp;
    tsp = 0; //(Prolog trail_stack_pointer)
	cps_env = NIL;
    cps_lsp = 0;
    cps_pc = 0;
    SET_CDR(NIL,NIL); //prologの変数消去中にnilのcdrが書き換えられているので
    goto *JUMPTABLE[code[pc]];
    
    CASE_NOP:
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_HALT:
    	for(i=0; i< code_pointer_end; i++){
        	SET_AUX(code_pointer[i][0], -1);
        }
        code_pointer_end = 0;
        if(!nullp(local_stack[0]) && TOP_STACK != BOOLF){
        	x = reverse(local_stack[0]);
            while(!nullp(x)){
				y = car(x);
            	print(car(y));
                printf(" = ");
                print(deref1(cdr(y)));
                printf("\n");
                x = cdr(x);
            }
			fflush(output_port);
            HALT_LOOP:
            c = getc(input_port);
            if(c == ';'){
            	pop_s();
                goto CASE_FAIL;
            }
            else if(c == '.')
            	goto HALT_EXIT;
            else
            	goto HALT_LOOP;
        }
        HALT_EXIT:
    	return(TOP_STACK);
        
    CASE_CONST:
    	push_s(ARG1);
        pc = pc + 2;
		goto *JUMPTABLE[code[pc]];
        
    CASE_LVAR:
    	if(ARG1 == 0)
    		push_s(GET_ENV_VEC_ELT(env,ARG2));
    	else
        	push_s(get_lvar(ARG1, ARG2));
    
        pc = pc + 3;
        goto *JUMPTABLE[code[pc]];
        
    CASE_GVAR:
    	arg = ARG1;
    	res = GET_CAR(arg);
        
        if(res == undef)
            	exception("", UNBOUND_VARIABLE, arg);
        
        push_s(res);
        
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];

    CASE_LSET:
		res = POP_S;
        set_lvar(ARG1,ARG2,res);
        push_s(res);
        pc = pc + 3;
        goto *JUMPTABLE[code[pc]];
        
    CASE_GSET:
        x = POP_S;
        arg = ARG1;

		if(GET_CAR(arg) != undef)
        	if(stack_continuationp(x))
                SET_CAR(arg,scont_to_hcont(x));
            else
            	SET_CAR(arg,x);
    	else
        	exception("", UNBOUND_VARIABLE, arg);
       	
        push_s(x);
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];
    
    CASE_POP:
    	pop_s();
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    CASE_JUMP:
        pc = pc + ARG1;
        goto *JUMPTABLE[code[pc]];
	
    
    CASE_TJUMP:
        if(POP_S != BOOLF)
        	pc = pc + ARG1;
        else
        	pc = pc + 2;
        
        goto *JUMPTABLE[code[pc]];
        	
        
    CASE_FJUMP:
        if(POP_S == BOOLF)
        	pc = pc + ARG1;
        else
        	pc = pc + 2;
        
        goto *JUMPTABLE[code[pc]];
        
    CASE_RETURN:
        pc = THIRD_STACK;
        env = SECOND_STACK;
        stack[sp-3] = stack[sp-1];
        sp = sp - 2;
        goto *JUMPTABLE[code[pc]];
    	
    CASE_ARGS:
    	check_ctrl();
    	m = ARG1;
        n = abs(m);
		
        env = make_env(n,env);
   
        //通常の引数の場合。
        if(m >= 0){
			for(j=n-1; j>=0; j--) 
                SET_ENV_VEC_ELT(env, j ,pop_s());        
		}
        //余剰引数の場合。
		else{
        	x = count_stack() - (n-1);//剰余引数の個数
            //余剰引数をリストにまとめる。
			arg = NIL;
            for(i=x; i>0; i--)
            	arg = cons(POP_S,arg);
            SET_ENV_VEC_ELT(env, n-1, arg);
            //余剰以外の引数を環境にセットする。
            for(j=n-2; j>=0; j--) 
                SET_ENV_VEC_ELT(env, j ,pop_s()); 	
        }
        	
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];
    
    
    
    CASE_CALL:
		check_ctrl();
        n = ARG1;
        reg_n = n; //APPARGのために値を保存する。
    	clo = POP_S;
        
		if(closurep(clo)){
        	m = GET_ARGS_CNT(clo);
            if(m != -128){
            	if(((m >=0 ) && m != n) ||
            		( m < 0 && n < abs(m)-1))
				exception(GET_NAME(clo),INCORRECT_ARG_CNT,NIL);
            }
        	//まだ展開されていない命令列の場合
			if((x=GET_AUX(clo)) == -1){
                clo_code = GET_CAR(clo);
                size = GET_CDR(clo_code);
                for(i=0; i<size; i++)
                	code[i+tail] = GET_VEC_ELT(clo_code,i);
                head = tail;
                tail = tail+size;
                SET_AUX(clo,head);
                code_pointer[code_pointer_end][0] = clo;
                code_pointer[code_pointer_end][1] = head;
                code_pointer_end++;
                if(code_pointer_end > CLOSIZE)
                	exception("call", CLOSURE_OVERF,NIL);
            	insert_stack(env,pc+2,n);
                env = GET_CDR(clo);
            	pc = head;
        	}
            //既に展開されている命令列の場合。
        	else{
                i = sp-1;
    			for(j=n; j>0; j--){
    				stack[i+2] = stack[i];
        			i--;
    			}
    			stack[sp-n] = pc+2;
    			stack[sp-n+1] = env;
    			sp = sp + 2; 
				//insert_stack(env,pc+2,n);
                env = GET_CDR(clo);
            	pc = x;
        	}
        	goto *JUMPTABLE[code[pc]];
        }
        if(heap_continuationp(clo)){
			//継続から渡された引数
            if(n == 0)
            	arg = empty_set;
            else if (n == 1)
            	arg = pop_s();
            else{
            	arg = NIL;
            	for(i=0; i<n; i++)
            		arg = cons(pop_s(),arg);
            }
                
            //dynamic-windの処理
            x = caddr(GET_AUX(clo));
            if(!equalp(winders,x)){
            	do_wind(x);
            }	
            //メモリ展開情報のクリア
            for(i=0; i< code_pointer_end; i++){
        		SET_AUX(code_pointer[i][0], -1);
        	}
        	code_pointer_end = 0;

 			
            //継続の保持する命令列を復元
        	cont_code = GET_CAR(clo);
            pc = GET_VEC_ELT(cont_code,0); //pcなどを復元
            code_pointer_end = GET_VEC_ELT(cont_code,1);
            head = GET_VEC_ELT(cont_code,2);
            tail = GET_VEC_ELT(cont_code,3);
            
            
            j = 4;
            for(i=0; i<code_pointer_end; i++){
            	code_pointer[i][0] = GET_VEC_ELT(cont_code,j);    //closure
            	code_pointer[i][1] = GET_VEC_ELT(cont_code,j+1);  //start address
				SET_AUX(code_pointer[i][0],code_pointer[i][1]);
                x = code_pointer[i][0];
                clo_code = GET_CAR(x);
                size = GET_CDR(clo_code);
                y = code_pointer[i][1];
                for(z=0; z<size; z++)
                	code[z+y] = GET_VEC_ELT(clo_code,z);   
                j = j + 2;
			}
            y = code_pointer[0][1];
            for(i=0; i<y; i++){
            	code[i] = GET_VEC_ELT(cont_code,j);
                j++;
            }
            
            //継続の保持するスタックを復元
            cont_stack = GET_CDR(clo);
			m = GET_CDR(cont_stack);
            for(i=0; i<m; i++)
            	stack[i] = GET_VEC_ELT(cont_stack,i);
            sp = m;
            
            //継続に渡された引数をスタックトップへ
            if(n == 0 || n == 1)
            	push_s(arg);
            else
            	push_s(make_multiple_values(arg));

			
            //継続の保持する環境を復元
            env = car(GET_AUX(clo));
            current_module = cadr(GET_AUX(clo));
            goto *JUMPTABLE[code[pc]];	
        }
        if(stack_continuationp(clo)){
        	//継続から渡された引数
            if(n == 0)
            	arg = empty_set;
            else if (n == 1)
            	arg = pop_s();
            else{
            	arg = NIL;
            	for(i=0; i<n; i++)
            		arg = cons(pop_s(),arg);
            }
            
            //dynamic-windの処理
            x = caddr(GET_AUX(clo));
            if(!equalp(winders,x)){
            	do_wind(x);
            }	
            pc = GET_CAR(clo);
            sp = GET_CDR(clo);
            env = car(GET_AUX(clo));
            current_module = cadr(GET_AUX(clo));
            push_s(arg);
    		goto *JUMPTABLE[code[pc]];	
        }
        if(subrp(clo) || t_closurep(clo)){
            contflag = 0; //ret命令で制御を返すようにする
        	push_s(((GET_SUBR(clo))(n)));
            pc = pc + 2;
            goto *JUMPTABLE[code[pc]]; 
        }
        exception("", NOT_PROCEDURE, clo);
        	
        
    CASE_CALLJ:
		check_ctrl();
        n = ARG1;
    	clo = POP_S;
        
        if(closurep(clo)){
            m = GET_ARGS_CNT(clo);
            if(m != -128){//-128のときは引数個数チェックをしない。applyのため
            	if(((m >=0 ) && m != n) ||
               	( m < 0 && n < abs(m)-1))
            		exception(GET_NAME(clo),INCORRECT_ARG_CNT,NIL);
            }
        	if((x=GET_AUX(clo)) == -1){
				clo_code = GET_CAR(clo);
            	size = GET_CDR(clo_code);
            	for(i=0; i<size; i++)
            	code[i+tail] = GET_VEC_ELT(clo_code,i);
            	head = tail;
            	tail = tail+size;
            	SET_AUX(clo,head);
            	code_pointer[code_pointer_end][0] = clo;
            	code_pointer[code_pointer_end][1] = head;
            	code_pointer_end++;
				if(code_pointer_end > CLOSIZE)
            		exception("callj", CLOSURE_OVERF,NIL);
            	env = GET_CDR(clo);
            	pc = head;
        	}
        	else{
        		env = GET_CDR(clo);
            	pc = x;
        	}
        	goto *JUMPTABLE[code[pc]];
        }
         
        if(heap_continuationp(clo)){
			//継続から渡された引数
            if(n == 0)
            	arg = empty_set;
            else if (n == 1)
            	arg = pop_s();
            else{
            	arg = NIL;
            	for(i=0; i<n; i++)
            		arg = cons(pop_s(),arg);
            }
                
            //dynamic-windの処理
            x = caddr(GET_AUX(clo));
            if(!equalp(winders,x)){
            	do_wind(x);
            }	
            //メモリ展開情報のクリア
            for(i=0; i< code_pointer_end; i++){
        		SET_AUX(code_pointer[i][0], -1);
        	}
        	code_pointer_end = 0;

 			
            //継続の保持する命令列を復元
        	cont_code = GET_CAR(clo);
            pc = GET_VEC_ELT(cont_code,0); //pcなどを復元
            code_pointer_end = GET_VEC_ELT(cont_code,1);
            head = GET_VEC_ELT(cont_code,2);
            tail = GET_VEC_ELT(cont_code,3);
            
            
            j = 4;
            for(i=0; i<code_pointer_end; i++){
            	code_pointer[i][0] = GET_VEC_ELT(cont_code,j);    //closure
            	code_pointer[i][1] = GET_VEC_ELT(cont_code,j+1);  //start address
				SET_AUX(code_pointer[i][0],code_pointer[i][1]);
                x = code_pointer[i][0];
                clo_code = GET_CAR(x);
                size = GET_CDR(clo_code);
                y = code_pointer[i][1];
                for(z=0; z<size; z++)
                	code[z+y] = GET_VEC_ELT(clo_code,z);   
                j = j + 2;
			}
            y = code_pointer[0][1];
            for(i=0; i<y; i++){
            	code[i] = GET_VEC_ELT(cont_code,j);
                j++;
            }
            
            //継続の保持するスタックを復元
            cont_stack = GET_CDR(clo);
			m = GET_CDR(cont_stack);
            for(i=0; i<m; i++)
            	stack[i] = GET_VEC_ELT(cont_stack,i);
            sp = m;
            
            //継続に渡された引数をスタックトップへ
            if(n == 0 || n == 1)
            	push_s(arg);
            else
            	push_s(make_multiple_values(arg));

			
            //継続の保持する環境を復元
            env = car(GET_AUX(clo));
            current_module = cadr(GET_AUX(clo));
            goto *JUMPTABLE[code[pc]];	
        }
        if(stack_continuationp(clo)){
        	//継続から渡された引数
            if(n == 0)
            	arg = empty_set;
            else if (n == 1)
            	arg = pop_s();
            else{
            	arg = NIL;
            	for(i=0; i<n; i++)
            		arg = cons(pop_s(),arg);
            }
            //dynamic-windの処理
            x = caddr(GET_AUX(clo));
            if(!equalp(winders,x)){
            	do_wind(x);
            }	
            pc = GET_CAR(clo);
            sp = GET_CDR(clo);
            env = car(GET_AUX(clo));
            current_module = cadr(GET_AUX(clo));
            push_s(arg);
    		goto *JUMPTABLE[code[pc]];	
        }
        if(subrp(clo) || t_closurep(clo)){
        	push_s(((GET_SUBR(clo))(n))); 
            pc = THIRD_STACK;
        	env = SECOND_STACK;
        	stack[sp-3] = stack[sp-1];
        	sp = sp - 2;
        	goto *JUMPTABLE[code[pc]]; 
        }
		exception("", NOT_PROCEDURE, clo);  
    
    CASE_FN:
        n = ARG1;
        arg = ARG2;
        res = make_clo();
        if(listp(arg)){
        	clo_code = list_to_code_obj(arg);
            code[pc + 2] = clo_code;
        }
        else
        	clo_code = arg;
        SET_CAR(res,clo_code);
        SET_CDR(res,env);
        SET_ARGS_CNT(res,n);
        push_s(res);
        pc = pc + 3;
        goto *JUMPTABLE[code[pc]];
        
    CASE_SAVE:
		push_s(ARG1);
    	push_s(env);
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];
    
    CASE_PRIM:
		check_ctrl();
        x = ARG1;
        if(symbolp(x)){
        	clo = car(x);
            if(clo == undef) exception("", UNBOUND_VARIABLE, x);
        }
        else
        	clo = x;
        n = ARG2;
    	pc = pc + 3;
        push_s(((GET_SUBR(clo))(n)));
    	goto *JUMPTABLE[code[pc]];  
	
    CASE_DEF:
        arg = ARG1;
        
        
        if(closurep(TOP_STACK)|| hygienicp(TOP_STACK)){
        	clo = TOP_STACK;
            strcpy(str,GET_NAME(arg));
            SET_NAME(clo,str);
        }
        
		SET_CAR(arg,pop_s());
        
        push_s(arg);
        pc = pc + 2;
		goto *JUMPTABLE[code[pc]];
    	
    CASE_DEFM:
        arg = ARG1;
        clo = make_macro();
        SET_CAR(clo,pop_s());
        SET_CAR(arg,clo);
        strcpy(str,GET_NAME(arg));
        SET_NAME(clo,str);
        push_s(arg);
        pc = pc + 2;
    	goto *JUMPTABLE[code[pc]];
        
    CASE_DEFH:
		clo = make_hygienic();
        SET_CAR(clo,pop_s());
        SET_CDR(clo,env); //vm-env
        push_s(clo);
        pc = pc + 1;
    	goto *JUMPTABLE[code[pc]];
    
    CASE_NEQP:
    	y = pop_s();
        x = pop_s();

    	if(integerp(x) && integerp(y)){
     		if(x == y)
    			push_s(BOOLT);
        	else
        		push_s(BOOLF);
    	}
		else{
        	if(!numberp(x))
            	exception("=", NOT_NUMBER, x);
            if(!numberp(y))
            	exception("=", NOT_NUMBER, y);
                
        	if(numeqp(x,y))
            	push_s(BOOLT);
            else
            	push_s(BOOLF);
        }
        
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_SMLP:
    	y = pop_s();
        x = pop_s();

    	if(integerp(x) && integerp(y)){
     		if(x < y)
    			push_s(BOOLT);
        	else
        		push_s(BOOLF);
    	}
		else{
        	if(!numberp(x))
            	exception("<", NOT_NUMBER, x);
            if(!numberp(y))
            	exception("<", NOT_NUMBER, y);
                
        	if(smallerp(x,y))
            	push_s(BOOLT);
            else
            	push_s(BOOLF);
        }
        
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_ESMLP:
    	y = pop_s();
        x = pop_s();

    	if(integerp(x) && integerp(y)){
     		if(x <= y)
    			push_s(BOOLT);
        	else
        		push_s(BOOLF);
    	}
		else{
        	if(!numberp(x))
            	exception("<=", NOT_NUMBER, x);
            if(!numberp(y))
            	exception("<=", NOT_NUMBER, y);
            
        	if(eqsmallerp(x,y))
            	push_s(BOOLT);
            else
            	push_s(BOOLF);
        }
        
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    
    CASE_GRTP:
    	y = pop_s();
        x = pop_s();

    	if(integerp(x) && integerp(y)){
     		if(x > y)
    			push_s(BOOLT);
        	else
        		push_s(BOOLF);
    	}
		else{
        	if(!numberp(x))
            	exception(">", NOT_NUMBER, x);
            if(!numberp(y))
            	exception(">", NOT_NUMBER, y);
        
        	if(greaterp(x,y))
            	push_s(BOOLT);
            else
            	push_s(BOOLF);
        }
        
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    	
    
    CASE_EGRTP:
    	y = pop_s();
        x = pop_s();

    	if(integerp(x) && integerp(y)){
     		if(x >= y)
    			push_s(BOOLT);
        	else
        		push_s(BOOLF);
    	}
		else{
        	if(!numberp(x))
            	exception(">=", NOT_NUMBER, x);
            if(!numberp(y))
            	exception(">=", NOT_NUMBER, y);
            
        	if(eqgreaterp(x,y))
            	push_s(BOOLT);
            else
            	push_s(BOOLF);
        }
        
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    	
    
    CASE_ZEROP:
        x = pop_s();

    	if(integerp(x)){
     		if(get_int(x) == 0)
    			push_s(BOOLT);
        	else
        		push_s(BOOLF);
    	}
		else{
        	if(!numberp(x))
            	exception("zero?", NOT_NUMBER, x);
        
        	if(zerop(x))
            	push_s(BOOLT);
            else
            	push_s(BOOLF);
        }
        
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    	
        
    CASE_ADD1:
    	arg = pop_s();
    	if(integerp(arg)){
    		x = get_int(arg);
    		x++;
    		push_s(make_int(x));
		}
    	else{
    		if(!numberp(arg))
        		exception("add1",NOT_NUMBER,arg);
    		push_s(plus(arg,make_int(1)));
    	}
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_SUB1:
    	arg = pop_s();
    	if(integerp(arg)){
    		x = get_int(arg);
    		x--;
    		push_s(make_int(x));
		}
    	else{
    		if(!numberp(arg))
        		exception("sub1",NOT_NUMBER,arg);
    		push_s(minus(arg,make_int(1)));
    	}
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_ADD2:
    	arg = pop_s();
    	if(integerp(arg)){
    		x = get_int(arg);
    		x = x+2;
    		push_s(make_int(x));
		}
    	else{
    		if(!numberp(arg))
        		exception("add2",NOT_NUMBER,arg);
    		push_s(plus(arg,make_int(2)));
    	}
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_SUB2:
    	arg = pop_s();
    	if(integerp(arg)){
    		x = get_int(arg);
    		x = x-2;
    		push_s(make_int(x));
		}
    	else{
    		if(!numberp(arg))
        		exception("add2",NOT_NUMBER,arg);
    		push_s(minus(arg,make_int(2)));
    	}
    	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_GREF:
		push_s(ARG1);
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];
    
    CASE_CATCH:
    	cont_code = make_memory();
    	cont_stack = make_stack();
        cont = make_hcont();
        SET_CAR(cont,cont_code);
        SET_CDR(cont,cont_stack);
        SET_AUX(cont,cons(TOP_STACK,cons(current_module,cons(winders,NIL))));
    	push_s(cont);
        pc = pc + 1;
    	goto *JUMPTABLE[code[pc]];
    
    CASE_PAUSE:
    	return(TOP_STACK);
    
    CASE_CAR:
    	x = pop_s();
        if(pairp(x))
    		push_s(GET_CAR(x));
    	else
    		exception("car", NOT_PAIR, x);
      	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_CDR:
        x = pop_s();
        if(pairp(x))
    		push_s(GET_CDR(x));
    	else
    		exception("cdr", NOT_PAIR, x);
      	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_CONS:
        y = pop_s();
        x = pop_s();
        push_s(cons(x,y));
      	pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_ADAPT:
    	arg = pop_s();
    
		if(GET_TAG(arg) == MUL){
    		m = GET_VEC_ELT(arg,0);
    		for(i=1; i<=m; i++){
    			x = GET_VEC_ELT(arg,i);
        	push_s(x);
    		}
    	}
    	else if(arg == empty_set){
    		m = 0;
    	}
    	else{
    		m = 1;
			push_s(arg);
    	}
        
		code[pc + 5] = m;
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    CASE_DEFLIB:
    	export_id = NIL;
        export_rename = NIL;
        save_module = current_module;
        x = ARG1; //name
        y = ARG2; //body
        for(i=0; i<module_table_end; i++)
        	if(equalp(module_table[i][0],x))
            	goto deflib_exit;
        
        module_table[i][0] = x;
        module_table_end++;
        
        deflib_exit:
        current_module = i;
        y = remake(y);
        
        while(!nullp(y)){
        	push_e(y);
        	arg = eval1(car(y),i);
            pop_e(1);
            y = cdr(y);
        }
        while(!nullp(export_rename)){
        	m = car(export_rename);
            n = car(m);
            o = car(cdr(m));
            SET_CAR(o,GET_CAR(n));
            export_id = cons(o,export_id);
            export_rename = cdr(export_rename);
        }
        module_table[i][1] = export_id;
        
		y = module_table[i][1];
        while(!nullp(y)){
        	m = car(y);
        	if(GET_CAR(m) == undef)
            	exception("", UNBOUND_VARIABLE, m);
        	y = cdr(y);
        }
        current_module = 0;
        export_id = NIL;
        export_rename = NIL;
        current_module = save_module;
        pc = pc + 3;
        goto *JUMPTABLE[code[pc]];
        
    
    CASE_EXPLIB:
        x = ARG1; //id-list
        while(!nullp(x)){
        	if(eqp(car(car(x)),make_sym("rename")))
        		export_rename = cons(cdr(car(x)),export_rename);
        	else
        		export_id = cons(car(x),export_id);
            
            x = cdr(x);
        }
        push_s(undef);
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];
    
    CASE_IMPLIB:
    	x = ARG1; //<name idintifier>
        while(!nullp(x)){
        	m = car(x);
            if(eqvp(car(m),make_sym("only"))){
            	o = cddr(m); //only symbols
				m = cadr(m); //module_name
                load_libpath(m);
                for(i=0; i<module_table_end; i++)
        			if(equalp(module_table[i][0],m))
            			goto implib_only_exit;
        
        		exception("", NOT_EXIST_LIB, m);
        
        		implib_only_exit:
                y = module_table[i][1]; //export-list
        
        		while(!nullp(y)){
        			n = car(y);
                    if(memv(n,o) != BOOLF)
                        SET_CAR(remake(n),GET_CAR(n));
            		
                    y = cdr(y);
        		}
            }
            else if(eqvp(car(m),make_sym("except"))){
				o = cddr(m); //only symbols
				m = cadr(m); //module_name
                load_libpath(m);
                for(i=0; i<module_table_end; i++)
        			if(equalp(module_table[i][0],m))
            			goto implib_except_exit;
        
        		exception("", NOT_EXIST_LIB, m);
        
        		implib_except_exit:
                y = module_table[i][1]; //export-list
        
        		while(!nullp(y)){
        			n = car(y);
                    if(memv(n,o) == BOOLF)
                        SET_CAR(remake(n),GET_CAR(n));
            		
                    y = cdr(y);
        		}
            }
            else{
            	load_libpath(m);
        		for(i=0; i<module_table_end; i++)
        			if(equalp(module_table[i][0],m))
            			goto implib_else_exit;
        
        		exception("", NOT_EXIST_LIB, m);
        
        		implib_else_exit:
        		y = module_table[i][1]; //export-list
        
        		while(!nullp(y)){
        			n = car(y);
            		SET_CAR(remake(n),GET_CAR(n));
            		y = cdr(y);
        		}
            }
            x = cdr(x);
        }
        push_s(undef);
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];
		
    CASE_CONT:
        cont = make_scont();
		SET_CAR(cont,SECOND_STACK); //pc
        SET_CDR(cont,sp-2); //sp
        SET_AUX(cont,cons(TOP_STACK,cons(current_module,cons(winders,NIL))));
        //env+moduleNum+winders
    	push_s(cont);
        pc = pc + 1;
    	goto *JUMPTABLE[code[pc]];
        
    CASE_APPARG:
    	arg = pop_s();
    	if(!listp(arg))
    		exception("apply", NOT_LIST, arg);
        n = reg_n;
    	for(i=n-2; i>0; i--)
    		arg = cons(pop_s(),arg);
   
		x = pop_s(); //procedure
        
   		n = 0;
        while(!nullp(arg)){
        	push_s(car(arg));
            arg = cdr(arg);
            n++;
            if(sp > STACKSIZE) 
            	exception("apply", STACK_OVERF, NIL);
        }
        code[pc+2] = n; //続く(call n)命令のnを書き換える。
        push_s(x);
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
    
    
     CASE_PUSHWND:
    	y = pop_s(); //after
        x = pop_s(); //before
        winders = cons(cons(x,y),winders);
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    CASE_POPWND:
        winders = cdr(winders);
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    CASE_PUSHEXH:
    	x = pop_s();
        exception_handler = cons(x,exception_handler);
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    CASE_POPEXH:
        if(nullp(exception_handler)){
        	printf("Exception: invoke raise\n");
    		longjmp(toplevel,1);
        }	
        x = car(exception_handler);
        push_s(x);
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    CASE_EXCEPT:
    	printf("Exception: invoke raise\n");
    	longjmp(toplevel,1);
            
    CASE_RETRACT:
    	sp = sp + 1;
        pc = pc + 1;
        goto *JUMPTABLE[code[pc]];
        
    CASE_R9:
    CASE_R10: goto *JUMPTABLE[code[pc]];
    
    CASE_DEREF:
        x = ARG1;
        y = deref(x);
		push_s(y);
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];  
        
    
    CASE_UNIFY:
        x = get_lvar(ARG1, ARG2 + 3); 
        y = ARG3;
		y = deref(y);
        if(!unify(x,y))
			goto CASE_FAIL;
        
        pc = pc + 4;
        goto *JUMPTABLE[code[pc]];  
        
    CASE_UNIFYC:
        x = get_lvar(ARG1, ARG2 + 3);
        y = ARG3;
        if(refp(x) && !anoymousp(car(x))){
        	z = make_ref(undef);
        	SET_CDR(x,z);
            SET_AUX(z,x);
            SET_CDR(z,y);
            push_l(z);
        }
        else{
        	if(!eqvp(x,y))
			goto CASE_FAIL;
        }
        pc = pc + 4;
        goto *JUMPTABLE[code[pc]];  
        
        
    CASE_UNIFYV:
        x = get_lvar(ARG1, ARG2 + 3);
        y = ARG3;
        y = deref(y);
        if((refp(x) && anoymousp(car(x))) ||
           (refp(y) && anoymousp(car(y)))){
           //non operation
        }
        else if(refp(x) && refp(y)){
        	SET_CDR(x,y);
            SET_AUX(y,x);
        }
        else if(refp(x) && !refp(y)){
        	z = make_ref(undef);
            SET_CDR(x,z);
            SET_AUX(z,x);
            SET_CDR(z,y);
            push_l(z);
        }
        else if(!refp(x) && refp(y)){
        	SET_CDR(y,x);
        }
        else{
        	if(!equalp(x,y))
            	goto CASE_FAIL;
        }
        
        pc = pc + 4;
        goto *JUMPTABLE[code[pc]]; 
    
      	
    CASE_UNIFYS:
        x = pop_s();
        y = ARG1;
        y = deref_shallow(y);
        
        if(refp(y) && !anoymousp(car(y))){
           	 SET_CDR(y,x);
        }
        else{
        	 if(!eqvp(x,y))
        		goto CASE_FAIL;
        }
        	
        push_s(x);
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]]; 
        
        
    CASE_TRY:
        n = ARG1;
		base[lsp] = tsp;
        if(n != BOOLF){
			push_t(env);
        	push_t(lsp);
        	push_t(pc+n); //fail continuation
    	}
        
        pc = pc + 2;
        goto *JUMPTABLE[code[pc]];  
        
    CASE_CALLP:
		check_ctrl();
                
        n = ARG1;
    	clo = POP_S;
        cps_env = env;
        cps_lsp = lsp;
        cps_pc = pc + 2;
        
		m = GET_ARGS_CNT(clo);
        if(((m >=0 ) && m != n) ||
          ( m < 0 && n < abs(m)-1))
        	exception(GET_NAME(clo),INCORRECT_ARG_CNT,NIL);
        
        //まだ展開されていない命令列の場合
		if((x=GET_AUX(clo)) == -1){
        	clo_code = GET_CAR(clo);
            size = GET_CDR(clo_code);
            for(i=0; i<size; i++)
            	code[i+tail] = GET_VEC_ELT(clo_code,i);
            head = tail;
            tail = tail+size;
            SET_AUX(clo,head);
            code_pointer[code_pointer_end][0] = clo;
            code_pointer[code_pointer_end][1] = head;
            code_pointer_end++;
            if(code_pointer_end > CLOSIZE)
            	exception("callp", CLOSURE_OVERF,NIL);
            
            env = GET_CDR(clo);
            pc = head;
        }
        //既に展開されている命令列の場合。
        else{
            env = GET_CDR(clo);
            pc = x;
        }
        
        lst++;
        lsp = lst;
        goto *JUMPTABLE[code[pc]];  
        
    CASE_PROCEED:
        lsp = get_lvar(0,1);
        pc  = get_lvar(0,2);
        env = get_lvar(0,0);
		push_s(BOOLT);
        goto *JUMPTABLE[code[pc]];
        	
    
    CASE_FAIL:
        if(tsp <= 0){
        	push_s(BOOLF);
            goto CASE_HALT;	
		}
        
        x = pop_t(); //pc fail continuation
        y = pop_t(); //lsp
        z = pop_t(); //env
        
        for(i=lst; i>=y; i--){
        	clr_ref(i);
            local_stack[i] = NIL;
        }
        
        pc = x;
        lsp = y;
        lst = lsp;
        env = z;
    	goto *JUMPTABLE[code[pc]];
    
    CASE_ARGSP:
    	check_ctrl();
    	
    	n = ARG1;
        env = make_env(n + 3,env);
		
        //通常の引数の場合。
        for(j=n-1+3; j>=3; j--) 
			SET_ENV_VEC_ELT(env, j ,pop_s());        
		
        SET_ENV_VEC_ELT(env, 0 ,cps_env);
        SET_ENV_VEC_ELT(env, 1 ,cps_lsp);
        SET_ENV_VEC_ELT(env, 2 ,cps_pc); 
		
        pc = pc + 2;
    	goto *JUMPTABLE[code[pc]];
        
    CASE_CUT:
        tsp = base[lsp];
        push_s(BOOLT);
        pc = pc + 1;
    	goto *JUMPTABLE[code[pc]];
    
    CASE_CALLM:
    	check_ctrl();
    	x = ARG1;
        x = deref(x);
        if(!pairp(x))
        	exception("", ILLEGAL_PRED, x);
            
    	cps_env = env;
        cps_lsp = lsp;
        cps_pc = pc + 2;
        
        clo = caar(x);
        y = cdr(x);
        n = 0;
        while(!nullp(y)){
        	push_s(car(y));
            n++;
            y = cdr(y);
        }
        m = GET_ARGS_CNT(clo);
        if(((m >=0 ) && m != n) ||
          ( m < 0 && n < abs(m)-1))
        	exception(GET_NAME(clo),INCORRECT_ARG_CNT,NIL);
        
        //まだ展開されていない命令列の場合
		if((x=GET_AUX(clo)) == -1){
        	clo_code = GET_CAR(clo);
            size = GET_CDR(clo_code);
            for(i=0; i<size; i++)
            	code[i+tail] = GET_VEC_ELT(clo_code,i);
            head = tail;
            tail = tail+size;
            SET_AUX(clo,head);
            code_pointer[code_pointer_end][0] = clo;
            code_pointer[code_pointer_end][1] = head;
            code_pointer_end++;
            if(code_pointer_end > CLOSIZE)
            	exception("callm", CLOSURE_OVERF,NIL);
            
            env = GET_CDR(clo);
            pc = head;
        }
        //既に展開されている命令列の場合。
        else{
            env = GET_CDR(clo);
            pc = x;
        }
        
        lst++;
        lsp = lst;
        goto *JUMPTABLE[code[pc]];
        
}
*/