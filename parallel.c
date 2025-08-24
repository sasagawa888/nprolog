#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "npl.h"


/* distributed parallel */
int pred_to_str(int x)
{
    int res;

    memset(output_buffer, '\0', sizeof(output_buffer));
    dialog_flag = 1;
    print(x);
    printstr(".\n");
    dialog_flag = 0;
    res = makestr((char *) output_buffer);
    return (res);
}

int str_to_pred(int x)
{
    int res;

    dialog_flag = 1;
    memset(input_buffer, '\0', sizeof(input_buffer));
    strcpy(input_buffer, GET_NAME(x));
    read_string_term(0);
    res = variable_to_call(readparse(0));
    memset(input_buffer, 0, sizeof(input_buffer));
    dialog_flag = 0;
    return (res);
}

// under construction V_1 -> v_1
int convert_to_variant(int x, int th)
{
    char *substr, *var;
    int i;

    if (nullp(x))
	return (NIL);
    else if (narrow_variable_p(x)) {
	var = GET_NAME(x);
	substr = &var[2];
	i = atoi(substr);
	i = i + CELLSIZE;
	return (i);
    }
    if (listp(x)) {
	return (x);
    } else if (!structurep(x)) {
	return (x);
    }
    return (wcons
	    (convert_to_variant(car(x), th),
	     convert_to_variant(cdr(x), th), th));
}

// under construction v_1 -> V_1
int convert_to_variable(int x, int th)
{
    char str[256];

    if (nullp(x))
	return (NIL);
    else if (IS_ALPHA(x)) {
	sprintf(str, "V_%d", x - CELLSIZE);
	return (makevar(str));
    } else if (listp(x)) {
	return (x);
    } else if (!structurep(x)) {
	return (x);
    } else
	return (wcons(convert_to_variable(car(x), th),
		      convert_to_variable(cdr(x), th), th));
}

void init_parent(void)
{

    // create socket
    parent_sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (parent_sockfd[0] < 0) {
	exception(SYSTEM_ERR, makestr("init parent"), NIL, 0);
    }
    // initialize parent_addr
    memset((char *) &parent_addr, 0, sizeof(parent_addr));
    parent_addr.sin_family = AF_INET;
    parent_addr.sin_addr.s_addr = INADDR_ANY;
    parent_addr.sin_port = htons(PORT);

    // bind socket
    if (bind
	(parent_sockfd[0], (struct sockaddr *) &parent_addr,
	 sizeof(parent_addr)) < 0) {
	exception(SYSTEM_ERR, makestr("init parent"), NIL, 0);
    }

}

void init_child(int n, int x)
{

    // create socket
    child_sockfd[n] = socket(AF_INET, SOCK_STREAM, 0);
    if (child_sockfd[n] < 0) {
	exception(SYSTEM_ERR, makestr("dp_create"), makeint(n), 0);
    }
    // initialize child_addr
    memset((char *) &child_addr[n], 0, sizeof(child_addr[n]));
    child_addr[n].sin_family = AF_INET;
    child_addr[n].sin_port = htons(PORT);

    if (inet_pton(AF_INET, GET_NAME(x), &child_addr[n].sin_addr) < 0)
	exception(SYSTEM_ERR, makestr("dp_create"), x, 0);


    if (connect
	(child_sockfd[n], (struct sockaddr *) &child_addr[n],
	 sizeof(child_addr[n])) < 0) {
	exception(SYSTEM_ERR, makestr("dp_create"), makeint(n), 0);
    }

}


int receive_from_parent(void)
{
	child_buffer_pos = 0;
	child_buffer_end = 0;
    return (makestr(child_buffer));
}

void send_to_parent(int x)
{
    int n,i;

    // send message to parent
    memset(output_buffer, 0, sizeof(output_buffer));
    strcpy(output_buffer, GET_NAME(x));
	i = strlen(output_buffer);
	output_buffer[i] = 0x16;
	output_buffer[i+1] = 0;
    n = write(parent_sockfd[1], output_buffer, i+1);
    memset(output_buffer, 0, sizeof(output_buffer));
    if (n < 0) {
	exception(SYSTEM_ERR, makestr("send to parent"), x, 0);
    }

}

void send_to_parent_buffer(void)
{
    int n,i;

	i = strlen(output_buffer);
	output_buffer[i] = 0x16;
	output_buffer[i+1] = 0;
    n = write(parent_sockfd[1], output_buffer, i+1);
    if (n < 0) {
	exception(SYSTEM_ERR, makestr("send to parent buffer"), NIL, 0);
    }
}

void send_to_parent_control(int code)
{
    int n;

	memset(output_buffer,0,sizeof(output_buffer));
	output_buffer[0] = code;
	output_buffer[1] = 0x16;
	output_buffer[2] = 0;
    n = write(parent_sockfd[1], output_buffer, 2);
    if (n < 0) {
	exception(SYSTEM_ERR, makestr("send to parent code"), NIL, 0);
    }
}


void send_to_child(int n, int x)
{
    int m,i;

    memset(output_buffer, 0, sizeof(output_buffer));
    strcpy(output_buffer, GET_NAME(x));
	i = strlen(output_buffer);
	output_buffer[i] = 0x16;
    m = write(child_sockfd[n], output_buffer, strlen(output_buffer));
    memset(output_buffer, 0, sizeof(output_buffer));
    if (m < 0) {
	exception(SYSTEM_ERR, makestr("send to child"), NIL, 0);
    }
}

// send one control code
void send_to_child_control(int n, int code)
{
    int m;

	memset(output_buffer,0,sizeof(output_buffer));
	output_buffer[0] = code;
	output_buffer[1] = 0x16;
    m = write(child_sockfd[n], output_buffer, 2);
    if (m < 0) {
	exception(SYSTEM_ERR, makestr("send to child buffer"), NIL, 0);
    }
}



int receive_from_child(int n)
{
	return (makestr(parent_buffer[n]));
}


int b_dp_create(int arglist, int rest, int th)
{
    int n, ind, arg1, i, pred;

    n = length(arglist);
    ind = makeind("dp_create", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!listp(arg1))
	    exception(NOT_LIST, ind, arg1, th);
	if (length(arg1) > PARASIZE)
	    exception(RESOURCE_ERR, ind, arg1, th);

	parent_flag = 1;
	child_num = 0;
	while (!nullp(arg1)) {
	    if (!atomp(car(arg1)))
		exception(NOT_ATOM, ind, arg1, th);

	    init_child(child_num, car(arg1));
	    arg1 = cdr(arg1);
	    child_num++;
	}
	init_preceiver(child_num);

	for(i=0;i<child_num;i++){
		pred = list2(makeatom("dp_setid",SYS),makeint(i));
		send_to_child(i, pred_to_str(pred));
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_setid(int arglist, int rest, int th)
{
	int n, arg1, ind;

    n = length(arglist);
    ind = makeind("dp_setid", n, th);
    if (n == 1) {
		arg1 = car(arglist);
		child_id = GET_INT(arg1);
		return (prove_all(rest, sp[th], th));
	}
	exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_senderr(int arglist, int rest, int th)
{
	int n, arg1, ind;

    n = length(arglist);
    ind = makeind("dp_senderr", n, th); 
    if (n == 1) {
		arg1 = car(arglist);
		
		printf("occured an error in child %d\n",GET_INT(arg1));
		fflush(stdout);
		return (NO);
	}
	exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


// close all distributed child 
int b_dp_close(int arglist, int rest, int th)
{
    int n, ind, i, exp;

    n = length(arglist);
    ind = makeind("dp_close", n, th);
    if (n == 0) {

	if (parent_flag) {
	    exp = makeatom("dp_close",SYS);
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, pred_to_str(exp));
	    }
	}



	if (child_flag) {
	    printf("N-Prolog exit network mode.\n");
	    longjmp(buf, 2);
	}

	child_num = 0;
	parent_flag = 0;
	receiver_exit_flag = 1;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, 0);
    return (NO);

}

// close all distributed child and shutdown 
int b_dp_halt(int arglist, int rest, int th)
{
    int n, ind, i, exp;

    n = length(arglist);
    ind = makeind("dp_halt", n, th);
    if (n == 0) {

	if (parent_flag) {
	    exp = makeatom("dp_halt",SYS);
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, pred_to_str(exp));
	    }
	}

	
	if (child_flag) {
	    printf("N-Prolog exit network mode.\n");
	    receiver_exit_flag = 1;
	    shutdown_flag = 1;
	    longjmp(buf, 2);
	}

	child_num = 0;
	parent_flag = 0;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, 0);
    return (NO);

}



int b_dp_prove(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res ,i;

    n = length(arglist);
    ind = makeind("dp_prove", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (GET_INT(arg1) >= child_num || GET_INT(arg1) < 0)
	    exception(RESOURCE_ERR, ind, arg1, th);
	if (!callablep(arg2))
	    exception(NOT_CALLABLE, ind, arg2, th);

	i = GET_INT(arg1);
	memset(parent_buffer[i],0,sizeof(parent_buffer[i]));
	send_to_child(GET_INT(arg1), pred_to_str(arg2));
	while(parent_buffer[i][0] == 0){
	usleep(1000);
	if(ctrl_c_flag == 1){
		send_to_child_control(GET_INT(arg1),0x11);
		printf("ctrl+C\n");
	    longjmp(buf, 1);
	}
	}
	res =
	    convert_to_variant(str_to_pred(receive_from_child(i)), th);
	
	if (prove_all(res, sp[th], th) == YES)
		return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

// parent Prolog
int b_dp_transfer(int arglist, int rest, int th)
{
    int n, ind, arg1, i, m;
    FILE *file;

    n = length(arglist);
    ind = makeind("dp_transfer", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	file = fopen(GET_NAME(arg1), "r");
	if (!file) {
	    exception(CANT_OPEN, ind, arg1, th);
	}


	for (i = 0; i < child_num; i++) {
	    send_to_child_control(i, 0x15);
		send_to_child(i, arg1);

	    int bytes_read;
	    while ((bytes_read =
		    fread(transfer, sizeof(char), sizeof(transfer),
			  file)) > 0) {
		m = write(child_sockfd[i], transfer, bytes_read);
		if (m < 0) {
		    exception(SYSTEM_ERR, makestr("dp_transfer"), NIL, th);
		}
	    }
	    send_to_child_control(i, 0x16);
	    m = write(child_sockfd[i], transfer, 1);
	    if (m < 0) {
		exception(SYSTEM_ERR, makestr("dp_transfer"), NIL, th);
	    }
	    receive_from_child(i);
	    fseek(file, 0, SEEK_SET);
	}
	fclose(file);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_consult(int arglist, int rest, int th)
{
    int n, ind, arg1, pred1, pred2, i;

    n = length(arglist);
    ind = makeind("dp_consult", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	pred1 = list2(makeatom("consult", SYS), arg1);
	prove_all(pred1, sp[th], th);

	if (parent_flag) {
	    pred2 = list2(makeatom("dp_consult", SYS), arg1);
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, pred_to_str(pred2));
		receive_from_child(i);
	    }
	}
	return (YES);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_dp_reconsult(int arglist, int rest, int th)
{
    int n, ind, arg1, pred1, pred2, i;

    n = length(arglist);
    ind = makeind("dp_reconsult", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	pred1 = list2(makeatom("reconsult", SYS), arg1);
	prove_all(pred1, sp[th], th);

	if (parent_flag) {
	    pred2 = list2(makeatom("dp_reconsult", SYS), arg1);
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, pred_to_str(pred2));
		receive_from_child(i);
	    }
	}
	return (YES);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_dp_compile(int arglist, int rest, int th)
{
    int n, ind, arg1, pred1, pred2, i;

    n = length(arglist);
    ind = makeind("dp_compile", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	pred1 = list2(makeatom("compile_file", PRED), arg1);
	prove_all(pred1, sp[th], th);

	if (parent_flag) {
	    pred2 = list3(AND ,list2(makeatom("use_module",SYS),makeconst("compiler")),
		                   list2(makeatom("compile_file", PRED), arg1));
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, pred_to_str(pred2));
		receive_from_child(i);
	    }
	}
	return (YES);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int all_received(int *result, int size) {
    for (int i = 0; i < size; i++) {
        if (result[i] == 0)  
            return 0;   
    }
    return 1;             
}

int b_dp_and(int arglist, int rest, int th)
{
    int n, ind, arg1, m, i, j, pred, res , result[PARASIZE];

    n = length(arglist);
    ind = makeind("dp_and", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	m = length(arg1);
	if (m > child_num)
	    exception(RESOURCE_ERR, ind, makestr("child_num"), th);

	i = 0;
	while (!nullp(arg1)) {
	    pred = deref(car(arg1), th);
	    send_to_child(i, pred_to_str(pred));
	    arg1 = cdr(arg1);
	    i++;
	}

	for(i=0;i<m;i++){
		result[i] = 0;
		memset(parent_buffer[i],0,sizeof(parent_buffer[i]));
	}
	
	while(!all_received(result,m)){
		if(ctrl_c_flag == 1){
			for(i=0;i<m;i++){
				if(result[i] == 0)
				send_to_child_control(i,0x11);
			}
			printf("ctrl+C\n");
			ctrl_c_flag = 0;
	    	longjmp(buf, 1);
		}
		for (i = 0; i < m; i++) {
			if(parent_buffer[i][0] != 0 && result[i] == 0){
				result[i] = 1;
				res = convert_to_variant(str_to_pred(receive_from_child(i)), th);
				if (prove_all(res, sp[th], th) == NO){
					for(j=0;j<m;j++){
						if(result[j] == 0){
							send_to_child_control(j,0x11); // stop signal
						}
					}
					return(NO);
	            }
		   }
	    }
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_or(int arglist, int rest, int th)
{
    int n, ind, arg1, m, i, j, pred, res, result[PARASIZE];

    n = length(arglist);
    ind = makeind("dp_or", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	m = length(arg1);
	if (m > child_num)
	    exception(RESOURCE_ERR, ind, makestr("child_num"), th);

	i = 0;
	while (!nullp(arg1)) {
	    pred = deref(car(arg1), th);
	    send_to_child(i, pred_to_str(pred));
	    arg1 = cdr(arg1);
	    i++;
	}

	for(i=0;i<m;i++){
		result[i] = 0;
		memset(parent_buffer[i],0,sizeof(parent_buffer[i]));
	}
	
	while(!all_received(result,m)){
		if(ctrl_c_flag == 1){
			for(i=0;i<m;i++){
				if(result[i] == 0)
				send_to_child_control(i,0x11);
			}
			printf("ctrl+C\n");
			ctrl_c_flag = 0;
	    	longjmp(buf, 1);
		}
		for (i = 0; i < m; i++) {
			if(parent_buffer[i][0] != 0 && result[i] == 0){
				result[i] = 1;
				res = convert_to_variant(str_to_pred(receive_from_child(i)), th);
				if(prove_all(res, sp[th], th) == YES){
					for(j=0;j<m;j++){
						if(result[j] == 0){
							send_to_child_control(j,0x11); // stop signal
						}
					}
					return (prove_all(rest, sp[th], th));
				} 
			}
		}
	}
	return(NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_countup(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("dp_countup", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	proof[th] = proof[th] + GET_INT(arg1);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


// multi thread parallel functions 
void mt_enqueue(int n)
{
    pthread_mutex_lock(&mutex);
    mt_queue[mt_queue_pt] = n;
    mt_queue_pt++;
    pthread_cond_signal(&mt_cond_queue);
    pthread_mutex_unlock(&mutex);
}

int mt_dequeue(int arg)
{
    int num, i;

    if (mt_queue_pt == 0) {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_queue, &mutex);
	pthread_mutex_unlock(&mutex);
    }

    num = mt_queue[0];
    mt_queue_pt--;
    for (i = 0; i < mt_queue_pt; i++) {
	mt_queue[i] = mt_queue[i + 1];
    }
    pthread_mutex_lock(&mutex);
    para_input[num] = copy_work(convert_to_variable(arg, num), num);
    para_output[num] = NIL;
    pthread_cond_signal(&mt_cond_para[num]);
    pthread_mutex_unlock(&mutex);

    return (num);
}

int eval_para(int arg)
{
    int num;

    num = mt_dequeue(arg);
    return (num);
}

int query_thread(int x, int th)
{
    variables[th] = listreverse(unique(varslist(x)));
    return (prove_all(addask(x, th), sp[th], th));
}

void *parallel(void *arg)
{
    int num = *(int *) arg;

    while (1) {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_para[num], &mutex);
	pthread_mutex_unlock(&mutex);
	if (parallel_exit_flag)
	    goto exit;

	int ret = setjmp(buf3);
	if (ret == 0) {
	    para_output[num] = query_thread(para_input[num], num);
	} else if (ret == 1) {
	    para_output[num] = -1;	// error
	    ret = 0;
	}
	mt_enqueue(num);
	pthread_mutex_lock(&mutex);
	active_thread--;
	pthread_mutex_unlock(&mutex);
	if (active_thread == 0) {
	    pthread_mutex_lock(&mutex);
	    pthread_cond_signal(&mt_cond_main);
	    pthread_mutex_unlock(&mutex);
	}
    }
  exit:
    pthread_exit(NULL);
}

void init_para(void)
{
    int i;

    // mt_queue[1,2,3,4,...] worker thread number 
    // mt_para_thread[1] has worker-number 1
    // mt_para_thread[2] has worker-number 2 ... 
    //
    for (i = 0; i < mt_queue_num; i++) {
	mt_queue[i] = i + 1;
    }

    for (i = 0; i < mt_queue_num; i++) {
	pthread_create(&mt_para_thread[i + 1], NULL, parallel,
		       &mt_queue[i]);
    }

    mt_queue_pt = mt_queue_num;
}


void exit_para(void)
{
    int i;

    parallel_exit_flag = 1;
    for (i = 1; i <= mt_queue_num; i++) {
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&mt_cond_para[i]);
	pthread_mutex_unlock(&mutex);
    }

}


int b_mt_create(int arglist, int rest, int th)
{
    int n, ind, arg1, i, m;

    n = length(arglist);
    ind = makeind("mt_create", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (GET_INT(arg1) > THREADSIZE)
	    exception(RESOURCE_ERR, ind, makestr("thread_size"), th);

	if (thread_flag)
	    return (YES);

	mt_queue_num = GET_INT(arg1);
	thread_num = mt_queue_num;
	thread_flag = 1;
	init_para();
	m = thread_num + 1;
	for (i = 0; i < m; i++) {
	    wp_min[i] = HEAPSIZE + 1 + (CELLSIZE - HEAPSIZE) / m * i;
	    wp_max[i] = wp_min[i] + (CELLSIZE - HEAPSIZE) / m;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_mt_close(int arglist, int rest, int th)
{
    int n, ind;
    n = length(arglist);
    ind = makeind("mt_close", n, th);
    if (n == 0) {

	exit_para();
	thread_flag = 0;
	mt_queue_num = 0;
	thread_num = 1;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_mt_and(int arglist, int rest, int th)
{
    int n, ind, arg1, i, j, pred;

    n = length(arglist);
    ind = makeind("mt_and", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (length(arg1) > mt_queue_num)
	    exception(RESOURCE_ERR, ind, makestr("mt_queue_num"), th);


	i = 0;
	while (!nullp(arg1)) {
	    pred = convert_to_variable(car(arg1), th);
	    eval_para(pred);
	    arg1 = cdr(arg1);
	    i++;
	}

	active_thread = i;
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_main, &mutex);
	pthread_mutex_unlock(&mutex);


	// receive result from each thread
	for (j = 1; j <= i; j++) {
	    if (para_output[j] == NO)
		return (NO);
	    else if (para_output[j] == -1)
		longjmp(buf, 1);

	}

	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_mt_or(int arglist, int rest, int th)
{
    int n, ind, arg1, i, j;

    n = length(arglist);
    ind = makeind("mt_or", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (length(arg1) > mt_queue_num)
	    exception(RESOURCE_ERR, ind, makestr("mt_queue_num"), th);


	i = 0;
	while (!nullp(arg1)) {
	    eval_para(car(arg1));
	    arg1 = cdr(arg1);
	    i++;
	}
	active_thread = i;
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_main, &mutex);
	pthread_mutex_unlock(&mutex);

	// receive result from each thread
	for (j = 1; j <= i; j++) {
	    if (para_output[j] == YES)
		goto succ;
	    else if (para_output[j] == -1)
		longjmp(buf, 1);

	}
	return (NO);

      succ:
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_mt_prove(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("mt_prove", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	return (prove_all(arg2, sp[GET_INT(arg1)], GET_INT(arg1)));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

void print_ascii(char *str) {
	int i;
    for (i = 0; i < strlen(str); i++) {
        printf("0x%02X ", (unsigned char)str[i]);
    }
    printf("\n");
}


// Thread for parent receiver
void *preceiver(void *arg)
{
	int n, m, i;
	char buffer[BUFSIZE],sub_buffer[BUFSIZE];

	n = *(int *) arg;

    while (1) {

	if (receiver_exit_flag)
	    break;

	// read message from parent
	memset(buffer, 0, sizeof(buffer));
	reread:
	memset(sub_buffer, 0, sizeof(sub_buffer));
    m = read(child_sockfd[n], sub_buffer, sizeof(sub_buffer));
    if (m < 0) {
	exception(SYSTEM_ERR, makestr("receive from child"), makeint(n),
		  0);
    }

	//print_ascii(sub_buffer);printf("m=%d",m);fflush(stdout);
	strcat(buffer,sub_buffer);

	// normal message  0x16 is at m-1
	if(sub_buffer[m-1] != 0x16)
		goto reread;

	//print_ascii(buffer); 
	
	i = strlen(buffer);
	buffer[i] = 0;
	strcpy(parent_buffer[n],buffer); 
    }

    pthread_exit(NULL);
}

// Thread for child receiver
void *creceiver(void *arg)
{
    int n, m, i, j;
	char buffer[BUFSIZE],sub_buffer[BUFSIZE];
	FILE *file;

	if (!connect_flag) {
	//wait conneting
	listen(parent_sockfd[0], 5);
	parent_len = sizeof(parent_addr);
	connect_flag = 1;

	// connection from parent
	parent_sockfd[1] =
	    accept(parent_sockfd[0], (struct sockaddr *) &parent_addr,
		   &parent_len);
	if (parent_sockfd[1] < 0) {
	    exception(SYSTEM_ERR, makestr("*creceiver"), NIL, 0);
	}
    }

    
    while (1) {

	if (receiver_exit_flag)
	    break;

	
	// read message from parent
	retry:
	memset(buffer, 0, sizeof(buffer));
	reread:
	memset(sub_buffer, 0, sizeof(sub_buffer));
	n = read(parent_sockfd[1], sub_buffer, sizeof(sub_buffer));
	if (n < 0) {
	    exception(SYSTEM_ERR, makestr("*creceiver"), NIL, 0);
	}

	strcat(buffer,sub_buffer);
	if(sub_buffer[n-1] != 0x16)
		goto reread;

	if (buffer[0] == 0x15) {	// dp-treansfer
	    i = 2;
	    j = 0;
	    while (buffer[i] != 0x16) { // get file name
		sub_buffer[j] = buffer[i];
		i++;
		j++;
	    }
	    sub_buffer[j - 1] = 0;	// \n -> '0'
		/*
	    file = fopen(sub_buffer, "w");
	    if (!file) {
		exception(CANT_OPEN, makestr("dp_transfer"), NIL, 0);
	    }

	    i++;
	    j = 0;
	    while (buffer[i] != 0x16) { // get file data
		sub_buffer[j] = buffer[i];
		i++;
		j++;
	    }
	    sub_buffer[j] = 0;
	    i = strlen(sub_buffer);
	    fwrite(sub_buffer, sizeof(char), i, file);
	    fclose(file);
		*/
	    printf("dp_transfer");
	    fflush(stdout);
		memset(buffer, 0, sizeof(buffer));
	    strcpy(buffer,"true.\n");
		memset(child_buffer, 0, sizeof(child_buffer));
	}

	pthread_mutex_lock(&mutex2);
	j = 0;	
	m = strlen(buffer);

	for (i = 0; i < m-1; i++) {
		if(buffer[i] == 0x11){
			memset(child_buffer,0,sizeof(child_buffer));
			strcpy(child_buffer,"fail.");
			child_buffer_pos = 0;
			child_buffer_end = 5;
			ctrl_c_flag = 1;
			goto exit;
		}
	    else { 
			child_buffer[j] = buffer[i];
	    	j++;
		}
	}

	child_buffer_pos = 0;
	child_buffer_end = j;

	exit:
	printf("receive from parent %s\n",child_buffer);

	child_buffer_ready = 1;
	pthread_cond_signal(&md_cond);
	pthread_mutex_unlock(&mutex2);

	
    }

    pthread_exit(NULL);
}


void init_preceiver(int n)
{	
	int i;
    // create parent receiver thread 
	for(i=0;i<n;i++){
		int *arg = malloc(sizeof(int));
        *arg = i;
    	pthread_create(&preceiver_thread[i], NULL, preceiver, arg);
	}

}

void init_creceiver(void)
{
    // create child receiver thread 
    pthread_create(&creceiver_thread, NULL, creceiver, NULL);

}
