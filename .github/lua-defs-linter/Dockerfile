FROM alpine:latest

RUN apk add lua-language-server

ENTRYPOINT ["lua-language-server", "--check=utils/lua-defs"]
