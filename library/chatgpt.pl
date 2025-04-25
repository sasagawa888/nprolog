:- module(chatgpt, [chatgpt_query/3]).

:- use_module(json).

% Main predicate
% chatgpt_query(+Prompt, +APIKey, -Response)
chatgpt_query(Prompt, APIKey, Response) :-
    % Step 1: Connect to api.openai.com (e.g., port 443 or 80 if TLSなし)
    create_client_socket(Socket, 80, 'api.openai.com'),

    % Step 2: Build HTTP POST body with Prompt
    format(Body, "{\"model\":~S, \"messages\":[{\"role\":\"user\",\"content\":~S}]}", 
           ["\"gpt-3.5-turbo\"", Prompt]),

    % Step 3: Build HTTP headers with APIKey and content length
    string_length(Body, Len),
    format(Headers, 
           "POST /v1/chat/completions HTTP/1.1\r\nHost: api.openai.com\r\nAuthorization: Bearer ~S\r\nContent-Type: application/json\r\nContent-Length: ~D\r\n\r\n~S",
           [APIKey, Len, Body]),

    % Step 4: Send the request
    atom_string(HeadersAtom, Headers),
    send_socket(Socket, HeadersAtom),

    % Step 5: Receive response (simple line-by-line, assumes one recv is enough)
    recv_socket(Socket, RespAtom),
    atom_string(RespAtom, Response),

    % Step 6: Close socket
    close_socket(Socket).