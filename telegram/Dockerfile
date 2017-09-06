FROM alpine:3.6

# node, yarn
RUN apk add --no-cache \
 nodejs-current \
 yarn

# bs-platform
RUN apk add --no-cache \
  python \
  g++ \
  make

ADD . /app
WORKDIR /app

RUN yarn --verbose

CMD yarn start
