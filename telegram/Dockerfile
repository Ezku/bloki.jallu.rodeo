FROM node:10.14.2-alpine

SHELL ["/bin/ash", "-c"]

COPY ./dist /app
WORKDIR /app

CMD ["node", "./index.js"]
