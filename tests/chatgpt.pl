:- use_module(json).

% ChatGPT sned massage to API and recieve response
call_chatgpt(Prompt, Response) :-
    create_curl_client(Curl, 'https://api.openai.com/v1/completions'),
    ApiKey = 'your-api-key-here',
    %set_curl_option(Curl, header('Content-Type: application/json')),
    %set_curl_option(Curl, header('Authorization: Bearer ' + ApiKey)),
    json_data(Prompt, JSONData),
    send_curl(Curl, JSONData),
    recv_curl(Curl, Response),
    close_curl(Curl).

% convert prompt to JSON format
json_data(Prompt, JSONData) :-
    format(JSONData, '{"model": "gpt-3.5-turbo", "messages": [{"role": "user", "content": "~w"}]}', [Prompt]).

% ?- call_chatgpt('What is the capital of France?', Response).