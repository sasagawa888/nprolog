% test socket


start_server :-
    create_server_socket(ServerSocket, 5000),
    writeln('Server started on port 5000'),
    recv_socket(ServerSocket, Message),
    write('Server received: '),
    write(Message),
    nl,
    close_socket(ServerSocket).

start_client :-
    create_client_socket(ClientSocket, 5000, '192.168.1.1'),
    send_socket(ClientSocket, hello),
    writeln('Client sent: hello'),
    close_socket(ClientSocket).


