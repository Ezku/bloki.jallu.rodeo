.PHONY: install build docker-build docker-run

install:
	(cd telegram && yarn)

build:
	(cd telegram && yarn build)

docker-build: build
	(cd telegram && docker build --tag="bloki/telegram" .)

docker-run: docker-build
	docker run bloki/telegram