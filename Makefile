.PHONY: install build watch up down

install:
	(cd telegram && yarn)

build:
	(cd telegram && yarn build)

watch:
	(cd telegram && yarn watch)

up:
	docker-compose up -d --build

down:
	docker-compose down
