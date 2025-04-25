# ChatGPT
under construction
This is a library for communicating via the ChatGPT API."

# Usage
```
?- use_module(chatgpt).
```

# Caution
Due to its use of JSON, the ChatGPT library processes strings in double-quoted mode.
If you want to revert to the original $-style strings, please execute the reset_json predicate.

# Test

```
:- use_module(chatgpt).

test_chat :-
    YourPrompt = "What is the capital of France?",
    YourAPIKey = "sk-...",  % API key
    chatgpt_query(YourPrompt, YourAPIKey, Response),
    write("ChatGPT says:"),nl,
    write(Response),nl.
```