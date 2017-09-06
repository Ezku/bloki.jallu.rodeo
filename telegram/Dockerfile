FROM alpine:3.6

RUN apk add --no-cache \
 nodejs-current

ADD ./build /app
WORKDIR /app

CMD node app.js
