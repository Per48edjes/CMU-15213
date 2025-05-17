IMAGE_NAME = lx70716/cmu-15213

.PHONY: build run

build:
	colima start
	docker pull $(IMAGE_NAME) 

run:
	docker run --rm --platform linux/amd64 -v "`pwd`"/labs:/usr/src/app/ -it $(IMAGE_NAME)
