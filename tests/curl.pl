
% curl test
:- use_module(json).

foo(T) :- 
    create_client_curl(C, "https://httpbin.org/post"),
    set_curl_option(C, method(post)),
    send_curl(C, "hello=world"),
    recv_curl(C, R),
    string_term(R,J),
    term_json(T,J),
    write(R),nl,
    close_curl(C).

