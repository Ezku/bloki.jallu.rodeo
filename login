#!/bin/sh
# Log in to AWS ECR in docker and hyper
echo docker: logging in to AWS ECR
eval $(aws ecr get-login --no-include-email --region eu-central-1)
echo
echo hyper: logging in to AWS ECR
eval $(aws ecr get-login --no-include-email --region eu-central-1 | sed 's/docker/hyper/')
