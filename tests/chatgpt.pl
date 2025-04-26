:- use_module(chatgpt).

test_chat :-
    YourPrompt = "What is the capital of France?",
    YourAPIKey = "sk-...",  % real API key
    chatgpt_query(YourPrompt, YourAPIKey, Response),
    write("ChatGPT says:"),nl,
    write(Response),nl.