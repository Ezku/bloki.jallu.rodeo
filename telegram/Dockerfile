FROM node:9.5.0-alpine

SHELL ["/bin/ash", "-c"]

COPY ./build /app
WORKDIR /app

CMD ["node", "./app.js"]
