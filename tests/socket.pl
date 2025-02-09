% test socket


start_server :-
    create_server_socket(ServerSocket, 5000),
    write('Server started on port 5000'),nl,
    recv_socket(ServerSocket, Message),
    write('Server received: '),
    write(Message),nl,
    send_socket(ServerSocket, Message),
    close_socket(ServerSocket).

start_client :-
    create_client_socket(ClientSocket, 5000, '102.168.1.1'),
    send_socket(ClientSocket, hello),
    write('Client sent: hello'),nl,
    recv_socket(ClientSocket, Message),
    write('Client recv: '),
    write(Message),nl,
    close_socket(ClientSocket).


