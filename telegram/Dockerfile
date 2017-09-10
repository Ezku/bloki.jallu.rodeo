# http://pm2.keymetrics.io/docs/usage/docker-pm2-nodejs
FROM keymetrics/pm2:8

ADD ./pm2.docker.yml /app/app.yml
WORKDIR /app

EXPOSE 9615

CMD ["pm2-docker", "app.yml", "--web", "9615"]
