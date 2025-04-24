start_server(Port) :-
    create_server_socket(S, Port),
    loop(S).

loop(ServerSocket) :-
    % クライアント接続を受け入れる
    accept_connection(ServerSocket, ClientSocket),
    recv_socket(ClientSocket, RequestAtom),
    % HTTPレスポンスを構築
    atom_concat('HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, world!', '', Response),
    send_socket(ClientSocket, Response),
    close_socket(ClientSocket),
    loop(ServerSocket).

accept_connection(ServerSocket, ClientSocket) :-
    % ServerSocketでrecv_socketを試してClientSocketにバインドするような処理が必要
    recv_socket(ServerSocket, ClientSocket).  % この動作はN-Prologの実装次第