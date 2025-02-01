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

    memset(bridge, '\0', sizeof(bridge));
    bridge_flag = 1;
    print(x);
    printstr(".\n");
    bridge_flag = 0;
    res = makestr((char *) bridge);
    return (res);
}

int str_to_pred(int x)
{
    int res;

    bridge_flag = 1;
    memset(bridge, '\0', sizeof(bridge));
    strcpy(bridge, GET_NAME(x));
    read_string_term(0);
    res = variable_to_call(readparse(0));
    memset(bridge, 0, sizeof(bridge));
    bridge_flag = 0;
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
	exception(SYSTEM_ERROR, makestr("init parent"), NIL, 0);
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
	exception(SYSTEM_ERROR, makestr("init parent"), NIL, 0);
    }

}

void init_child(int n, int x)
{

    // create socket
    child_sockfd[n] = socket(AF_INET, SOCK_STREAM, 0);
    if (child_sockfd[n] < 0) {
	exception(SYSTEM_ERROR, makestr("dp_create"), makeint(n), 0);
    }
    // initialize child_addr
    memset((char *) &child_addr[n], 0, sizeof(child_addr[n]));
    child_addr[n].sin_family = AF_INET;
    child_addr[n].sin_port = htons(PORT);

    if (inet_pton(AF_INET, GET_NAME(x), &child_addr[n].sin_addr) < 0)
	exception(SYSTEM_ERROR, makestr("dp_create"), x, 0);


    if (connect
	(child_sockfd[n], (struct sockaddr *) &child_addr[n],
	 sizeof(child_addr[n])) < 0) {
	exception(SYSTEM_ERROR, makestr("dp_create"), makeint(n), 0);
    }

}


int receive_from_parent(void)
{
    int n;

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
	    exception(SYSTEM_ERROR, makestr("receive from parent"), NIL, 0);
	}
    }
    // read message from parent
    memset(bridge, 0, sizeof(bridge));
    n = read(parent_sockfd[1], bridge, sizeof(bridge) - 1);
    if (n < 0) {
	exception(SYSTEM_ERROR, makestr("receive from parent"), NIL, 0);
    }
    return (makestr(bridge));
}

void send_to_parent(int x)
{
    int n;

    // send message to parent
    memset(bridge, 0, sizeof(bridge));
    strcpy(bridge, GET_NAME(x));
    n = write(parent_sockfd[1], bridge, strlen(bridge));
    memset(bridge, 0, sizeof(bridge));
    if (n < 0) {
	exception(SYSTEM_ERROR, makestr("send to parent"), x, 0);
    }
}

void send_to_parent_buffer(void)
{
    int n;

    n = write(parent_sockfd[1], bridge, strlen(bridge));
    if (n < 0) {
	exception(SYSTEM_ERROR, makestr("send to parent buffer"), NIL, 0);
    }
    memset(bridge, 0, sizeof(bridge));
}

void send_to_child(int n, int x)
{
    int m;

    memset(bridge, 0, sizeof(bridge));
    strcpy(bridge, GET_NAME(x));
    m = write(child_sockfd[n], bridge, strlen(bridge));
    memset(bridge, 0, sizeof(bridge));
    if (m < 0) {
	exception(SYSTEM_ERROR, makestr("send to child"), NIL, 0);
    }
}

int receive_from_child(int n)
{
    int m, i, j;
    char sub_buffer[256], sub_buffer1[256 + 2];

    // receive from child
  reread:
    memset(bridge, 0, sizeof(bridge));
    m = read(child_sockfd[n], bridge, sizeof(bridge) - 1);
    if (m < 0) {
	exception(SYSTEM_ERROR, makestr("receive from child"), makeint(n), 0);
    }

  retry:
    if (bridge[0] == '\x02') {
	i = 0;
	while (bridge[i + 1] != '\x03') {
	    sub_buffer[i] = bridge[i + 1];
	    i++;
	}
	if (!(child_flag && parent_flag)) {
	    sub_buffer[i] = 0;
	    printf("%s", sub_buffer);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sprintf(sub_buffer1, "\x02%s\x03", sub_buffer);
	    send_to_parent(makestr(sub_buffer1));
	}
	j = 0;
	i = i + 2;
	while (bridge[j + i] != 0) {
	    bridge[j] = bridge[j + i];
	    j++;
	}
	bridge[j] = 0;
	if (bridge[0] == 0)
	    goto reread;
	else
	    goto retry;
    } else if (bridge[0] == '\x15') {
	if (!(child_flag && parent_flag)) {
	    exception(SYSTEM_ERROR, makestr("in child"), makeint(n), 0);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sub_buffer1[0] = '\x15';
	    send_to_parent(makestr(sub_buffer1));
	}
    } else {
	return (makestr(bridge));
    }

    return (0);
}




int receive_from_child_or(int n)
{
    int i, m, res;

    //initialize -1 (not received)
    for (i = 0; i < n; i++) {
	child_result[i] = -1;
    }
    res = receive_from_child_or1(n);

    // kill not received child
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1) {
	    // send child stop signal
	    memset(bridge, 0, sizeof(bridge));
	    bridge[0] = '\x11';
	    m = write(child_sockfd[i], bridge, strlen(bridge));
	    if (m < 0) {
		exception(SYSTEM_ERROR, makestr("receive from child"), NIL, 0);
	    }
	    // receive result and ignore
	    while ((m =
		    read(child_sockfd[i], bridge,
			 sizeof(bridge) - 1)) == 0) {
	    }
	}
    }

    return (res);
}


int receive_from_child_or1(int n)
{
    int m, i;

    // receive from child
    m = 0;
  retry:
    memset(bridge, 0, sizeof(bridge));
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1) {
	    m = read(child_sockfd[i], bridge, sizeof(bridge));
	}
	if (m < 0) {
	    exception(SYSTEM_ERROR, makestr("receive from child"), makeint(i), 0);
	} else if (m > 0) {
	    child_result[i] = receive_from_child_or2(i);
	}
    }

    //if find true return it.
    for (i = 0; i < n; i++) {
	if (child_result[i] != -1
	    && strcmp(GET_NAME(child_result[i]), "fail.") != 0)
	    return (child_result[i]);
    }


    //if exist not received result, goto retry
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1)
	    goto retry;
    }

    // if not exist YES, return fail.
    return (makeatom("fail", SYS));
}

int receive_from_child_or2(int n)
{
    char sub_buffer[256], sub_buffer1[256 + 2];
    int i, j;

  retry:
    if (bridge[0] == '\x02') {
	i = 0;
	while (bridge[i + 1] != '\x03') {
	    sub_buffer[i] = bridge[i + 1];
	    i++;
	}
	if (!(child_flag && parent_flag)) {
	    sub_buffer[i] = 0;
	    printf("%s", sub_buffer);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sprintf(sub_buffer1, "\x02%s\x03", sub_buffer);
	    send_to_parent(makestr(sub_buffer1));
	}
	j = 0;
	i = i + 2;
	while (bridge[j + i] != 0) {
	    bridge[j] = bridge[j + i];
	    j++;
	}
	bridge[j] = 0;
	if (bridge[0] == 0)
	    return (-1);
	else
	    goto retry;

    } else if (bridge[0] == '\x15') {
	if (!(child_flag && parent_flag)) {
	    exception(SYSTEM_ERROR, makestr("in child"), makeint(n), 0);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sub_buffer1[0] = '\x15';
	    send_to_parent(makestr(sub_buffer1));
	}
    } else {
	return (makestr(bridge));
    }

    return (0);
}



// Thread for child lisp receiver
void *receiver(void *arg)
{
    int i;
    char sub_buffer[256];

    while (1) {
	if (receiver_exit_flag)
	    goto exit;

	if (child_busy_flag) {
	    receive_from_parent();
	  retry:
	    if (bridge[0] == '\x11') {
		// child stop 
		if (!(child_flag && parent_flag)) {
		    memset(sub_buffer, 0, sizeof(sub_buffer));
		    sub_buffer[0] = '\x11';
		    for (i = 0; i < child_num; i++)
			send_to_child(i, makestr(sub_buffer));
		}
		ctrl_c_flag = 1;
	    } else if (bridge[0] == '\x12') {
		// child pause 
		if (!(child_flag && parent_flag)) {
		    memset(sub_buffer, 0, sizeof(sub_buffer));
		    sub_buffer[0] = '\x12';
		    for (i = 0; i < child_num; i++)
			send_to_child(i, makestr(sub_buffer));
		}
		pause_flag = 1;
	    } else if (bridge[0] == '\x13') {
		// child resume 
		if (!(child_flag && parent_flag)) {
		    memset(sub_buffer, 0, sizeof(sub_buffer));
		    sub_buffer[0] = '\x11';
		    for (i = 0; i < child_num; i++)
			send_to_child(i, makestr(sub_buffer));
		}
		pause_flag = 0;
	    }

	    if (bridge[1] != 0) {
		int i;
		i = 0;
		while (bridge[i + 1] != 0) {
		    bridge[i] = bridge[i + 1];
		    i++;
		}
		bridge[i] = 0;
		goto retry;
	    }

	}

    }

  exit:
    pthread_exit(NULL);
}


void init_receiver(void)
{
    // create child receiver thread 
    pthread_create(&receiver_thread, NULL, receiver, NULL);

}


int b_dp_create(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
	ind = makeind("dp_create",n,th);
    if (n == 1) {
	parent_flag = 1;
	child_num = 0;
	arg1 = car(arglist);
	while (!nullp(arg1)) {
	    if (!atomp(car(arg1)))
		exception(NOT_ATOM, ind, arg1, th);

	    init_child(child_num, car(arg1));
	    arg1 = cdr(arg1);
	    child_num++;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

// close all distributed child 
int b_dp_close(int arglist, int rest, int th)
{
    int n, ind, i, exp;

    n = length(arglist);
	ind = makeind("dp_close",n,th);
    if (n == 0) {

	if (parent_flag) {
	    exp = makestr("dp_close.");
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, exp);
	    }
	}

	if (parent_flag) {
	    for (i = 0; i < child_num; i++)
		close(child_sockfd[i]);
	}

	if (child_flag) {
	    printf("N-Prolog exit network mode.\n");
	    close(parent_sockfd[0]);
	    close(parent_sockfd[1]);
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
    int n, ind,arg1, arg2, res;

    n = length(arglist);
	ind = makeind("dp_prove",n,th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (GET_INT(arg1) >= child_num || GET_INT(arg1) < 0)
	    exception(RESOURCE_ERR, makestr("dp_prove"), arg1, th);

	send_to_child(GET_INT(arg1), pred_to_str(arg2));
	res =
	    convert_to_variant(str_to_pred
			       (receive_from_child(GET_INT(arg1))), th);
	if (prove_all(res, sp[th], th) == YES)
	    return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

// parent Prolog
int b_dp_transfer(int arglist, int rest, int th)
{
    int n, ind,arg1, pred1, pred2, i, m;
    FILE *file;

    n = length(arglist);
	ind = makeind("dp_transfer",n,th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	file = fopen(GET_NAME(arg1), "r");
	if (!file) {
	    exception(CANT_OPEN, ind, arg1, th);
	}

	pred1 = list2(makeatom("dp_receive", SYS), arg1);

	for (i = 0; i < child_num; i++) {
	    send_to_child(i, pred_to_str(pred1));

	    int bytes_read;
	    while ((bytes_read =
		    fread(transfer, sizeof(char), sizeof(transfer),
			  file)) > 0) {
		m = write(child_sockfd[i], transfer, bytes_read);
		if (m < 0) {
		    exception(SYSTEM_ERROR, makestr("dp_transfer"), NIL, th);
		}
	    }
	    memset(transfer, 0, sizeof(transfer));
	    transfer[0] = 0x15;
	    m = write(child_sockfd[i], transfer, 1);
	    if (m < 0) {
		exception(SYSTEM_ERROR, makestr("dp_transfer"), NIL, th);
	    }
	    receive_from_child(i);
	    fseek(file, 0, SEEK_SET);
	}
	fclose(file);
	if (parent_flag) {
	    pred2 = list2(makeatom("dp_transfer", SYS), arg1);
	    for (i = 0; i < child_num; i++)
		send_to_child(i, pred_to_str(pred2));
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

// child Prolog
int b_dp_receive(int arglist, int rest, int th)
{
    int n,ind, arg1;
    FILE *file;

    n = length(arglist);
	ind = makeind("dp_recieve",n,th);
    if (n == 1) {
	child_busy_flag = 0;
	arg1 = car(arglist);


	file = fopen(GET_NAME(arg1), "w");
	if (!file) {
	    exception(CANT_OPEN, ind, arg1, th);
	}

	int bytes_received;
	while ((bytes_received =
		read(parent_sockfd[1], transfer, sizeof(transfer))) > 0) {
	    if (transfer[bytes_received - 1] == 0x15) {
		transfer[bytes_received - 1] = 0;
		fwrite(transfer, sizeof(char), bytes_received - 1, file);
		break;
	    }
	    fwrite(transfer, sizeof(char), bytes_received, file);
	}
	child_busy_flag = 1;
	fclose(file);
	return (YES);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_consult(int arglist, int rest, int th)
{
    int n,ind,arg1, pred1, pred2, i;

	n = length(arglist);
	ind = makeind("dp_consult",n,th);
	if(n==1){
    arg1 = car(arglist);
    if (!atomp(arg1))
	exception(NOT_ATOM, ind, arg1, th);

    pred1 = list2(makeatom("reconsult", SYS), arg1);
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

int b_dp_compile(int arglist, int rest, int th)
{
    int n, ind,arg1, pred1, pred2, i;

    n = length(arglist);
	ind = makeind("dp_compile",n,th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	pred1 = list2(makeatom("compile_file", PRED), arg1);
	prove_all(pred1, sp[th], th);

	if (parent_flag) {
	    pred2 = list2(makeatom("dp_compile", SYS), arg1);
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


int b_dp_report(int arglist, int rest, int th)
{
    int n, ind,arg1;
    char sub_buffer[STRSIZE];

    n = length(arglist);
	ind = makeind("dp_report",n,th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!stringp(arg1))
	    exception(NOT_STR, ind, arg1, th);

	memset(sub_buffer, 0, sizeof(sub_buffer));
	sprintf(sub_buffer, "\x02%s\x03", GET_NAME(arg1));
	send_to_parent(makestr(sub_buffer));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_and(int arglist, int rest, int th)
{
    int n, ind, arg1, m, i, j, pred, res;

    n = length(arglist);
	ind = makeind("dp_and",n,th);
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
	for (i = 0; i < m; i++) {
	    res =
		convert_to_variant(str_to_pred(receive_from_child(i)), th);
	    if (prove_all(res, sp[th], th) == NO) {
		for (j = i; j < m; j++) {
		    res =
			convert_to_variant(str_to_pred
					   (receive_from_child(j)), th);
		}
		return (NO);
	    }
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_or(int arglist, int rest, int th)
{
    int n, ind, arg1, m, i, pred, res;

    n = length(arglist);
	ind = makeind("do_or",n,th);
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
	res =
	    convert_to_variant(str_to_pred(receive_from_child_or(m)), th);
	if (prove_all(res, sp[th], th) == YES)
	    return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_countup(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
	ind = makeind("dp_countup",n,th);
    if (n == 1) {
	arg1 = car(arglist);

	proof[th] = proof[th] + GET_INT(arg1);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_parent(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
	ind = makeind("dp_parent",n,th);
    if (n == th) {

	if (parent_flag)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_child(int arglist, int rest, int th)
{
    int n,ind;

    n = length(arglist);
	ind = makeind("dp_child",n,th);
    if (n == th) {

	if (!parent_flag && child_flag)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_wait(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
	ind = makeind("dp_wait",n,th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (GET_INT(arg1) > 60)
	    exception(RESOURCE_ERR, ind, makestr("over 60"), th);

	sleep(GET_INT(arg1));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_pause(int arglist, int rest, int th)
{
    int n, ind, arg1;
    char sub_buffer[256];

    n = length(arglist);
	ind = makeind("dp_pause",n,th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (GET_INT(arg1) >= child_num)
	    exception(RESOURCE_ERR, ind, makestr("child_num"), th);


	memset(sub_buffer, 0, sizeof(sub_buffer));
	sub_buffer[0] = 0x11;
	send_to_child(GET_INT(arg1), makestr(sub_buffer));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dp_resume(int arglist, int rest, int th)
{
    int n, ind, arg1;
    char sub_buffer[256];

    n = length(arglist);
	ind = makeind("dp_resume",n,th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (GET_INT(arg1) >= child_num)
	    exception(RESOURCE_ERR, ind, makestr("child_num"), th);

	memset(sub_buffer, 0, sizeof(sub_buffer));
	sub_buffer[0] = 0x11;
	send_to_child(GET_INT(arg1), makestr(sub_buffer));
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
	ind = makeind("mt_create",n,th);
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
    int n,ind;
    n = length(arglist);
	ind = makeind("mt_close",n,th);
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
	ind = makeind("mt_and",n,th);
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
	ind = makeind("mt_or",n,th);
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
	ind = makeind("mt_prove",n,th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	return (prove_all(arg2, sp[GET_INT(arg1)], GET_INT(arg1)));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
