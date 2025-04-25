:- use_module(chatgpt).

test_chat :-
    YourPrompt = "What is the capital of France?",
    YourAPIKey = "sk-...",  % 実際のAPIキーをここに
    chatgpt_query(YourPrompt, YourAPIKey, Response),
    writeln("ChatGPT says:"),
    writeln(Response).