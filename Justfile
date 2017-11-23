default:
	just -l

install:
	(cd telegram && yarn)

build:
	(cd telegram && yarn build:dist)

watch:
	(cd telegram && yarn watch:dist)

up:
	docker-compose up -d --build

down:
	docker-compose down
