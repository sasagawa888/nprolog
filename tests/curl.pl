
% curl test

foo :- 
    create_curl_client(C, "https://httpbin.org/post"),
    set_curl_option(C, method(post)),
    send_curl(C, "hello=world"),
    recv_curl(C, R),
    write(R),nl,
    close_curl(C).