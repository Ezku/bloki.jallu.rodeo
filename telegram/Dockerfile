# http://pm2.keymetrics.io/docs/usage/docker-pm2-nodejs
FROM keymetrics/pm2:8

ADD ./build /app
WORKDIR /app

CMD ["pm2-docker", "app.js"]