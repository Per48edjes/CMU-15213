IMAGE_NAME = cspp

.PHONY: run

run:
	docker run --rm --platform linux/amd64 -v "`pwd`"/labs:/usr/src/app/ -it cspp 
