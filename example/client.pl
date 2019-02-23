client :-
    client_connect('192.168.1.12','5000',S),
    repeat,
    read(X),
    socket_send(S,X),
    socket_recieve(S,Y),
    write(Y),nl,
    X == end,
    socket_close(S).

