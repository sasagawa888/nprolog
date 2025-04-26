# CURL HTTPS
under construction

# Specification
- create_curl_client(Curl, URL)	指定URLでCURL *を生成。成功すればCurlに格納。
- send_curl(Curl, Atom)	POST/PUTなどでボディを送信（文字列形式）。
- recv_curl(Curl, Response)	レスポンスの受信。文字列としてResponseに格納。
- close_curl(Curl)	CURL *を開放。内部状態・メモリ解放。
- set_curl_option(Curl, Option)	Optionは header("..."), method(post), timeout(5) などの構造に。
- add_curl_header(Curl, Header)	複数ヘッダーの追加が必要なとき。"Authorization: Bearer ..." など。