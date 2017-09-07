.PHONY: install build docker-build docker-run

install:
	(cd telegram && yarn)

build:
	(cd telegram && yarn build)

up: build
	docker-compose up
