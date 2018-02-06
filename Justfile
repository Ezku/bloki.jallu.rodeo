default:
	just -l

install:
	npm install -g yarn
	yarn global add https://github.com/reasonml/reason-cli/archive/3.0.4-bin-darwin.tar.gz
	(cd telegram && yarn)

build:
	(cd telegram && yarn build:dist)

watch:
	(cd telegram && yarn watch:dist)

up:
	docker-compose up -d --build

down:
	docker-compose down

# Launch pm2 monit on telegram container
monit:
	./monit

# Log in to AWS ECR in docker and hyper
login:
	./login
