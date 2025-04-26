# TCP/IP 
 I have implemented the TCP/IP predicates. see ./tests/socket.pl

# Specification
- create_server_socket(Soket,port) 
 Creates and returns a socket as a server based on the port number. Provide the port number to port. It ranges from 0 to 65536.

- create_client-socket(Soket,port,ip-address)
 Provide the port number to port. It ranges from 0 to 65536. ip-address is given as an atom. Example: '127.1.1.1' Returns yes is success.

- send_socket(Socket,Atom) 
 Sends an atom to the socket. Returns yes.

- recv_socket(Socket,Atom) 
 Receives from the socket and returns yes.

- close_socket(Socket) 
 Closes the socket. Returns yes.

 ```
 start_server :-
    create_server_socket(ServerSocket, 5000),
    write('Server started on port 5000'),nl,
    recv_socket(ServerSocket, Message),
    write('Server received: '),
    write(Message),nl,
    send_socket(ServerSocket, Message),
    close_socket(ServerSocket).

start_client :-
    create_client_socket(ClientSocket, 5000, '127.1.1.1'),
    send_socket(ClientSocket, hello),
    write('Client sent: hello'),nl,
    recv_socket(ClientSocket, Message),
    write('Client recv: '),
    write(Message),nl,
    close_socket(ClientSocket).

 ```

