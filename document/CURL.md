# CURL HTTPS
under construction

# Specification
- create_client_curl(Curl, URL) 
Creates a Curl for the specified URL. If successful, unify it in Curl.

- send_curl(Curl, Post) 
Sends the body (as a string) using POST/PUT.

- recv_curl(Curl, Response) 
Receives the response. Stores it as a string in Response.

- close_curl(Curl) 
Releases the CURL*. Frees internal state and memory.

- set_curl_option(Curl, Option) 
Option can be structures like header("..."), method(post), timeout(5), etc.

- add_curl_header(Curl, Header) 
Adds multiple headers if needed. For example, "Authorization: Bearer ...".

