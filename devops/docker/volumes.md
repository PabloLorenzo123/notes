# Docker Volumes
Volumes per se, means an external storage source, such as flash drive or any external drive. In Linux distros, external drives are referred as volumes, linux namespace also have the same concept of volumes.\

In Docker volumes simply refer to, persistent external storage sources one or more containers can use. At its nature, a container is stateless everytime we spin up a new server it starts with its memory layer completely clear, and each time we shut down a container all its file in its filesystem are lost. Volumes is the solution docker provides for this.

The term volume originally comes from operating systems. Historically, a volume is a storage unit containing a filesystem, such as a hard drive partition, SSD, USB drive, network drive, or any filesystem the OS can mount. Linux often refers to mounted filesystems as volumes.

Docker borrows this term, but with a slightly different meaning.

A Docker volume is a persistent storage location managed by Docker that exists outside of a container's writable filesystem. One or more containers can mount the same volume and access its files.

Containers are designed to be ephemeral (temporary). Every time we create a new container, it starts with a fresh writable filesystem. Any files created inside the container disappear when the container is removed.

There are three type of volumes.

## BIND-MOUNTS
Bind a local file or folder to an internal container file or folder, this is preferribily only used in development. Remind you that whenever we want to change a file inside the container such as source code, we need to rebuild the image and spin up a new container, bind mounts solve this.

to mention a few of use cases we have:
1 - We want to reflect our source code chances in our host system into the source code running inside the container.
2 - The container is producing files we want to keep or see in our local filesystem, such as /logs.

We use this like this:

```
docker run --name CONTAINER_NAME -v ABSOLUTE_LOCAL_PATH:PATH_INSIDE_CONTAINER IMAGE_NAME
```

With docker compose:
```
services:
    api:
        build:
            dockerfile: PATH_TO_DOCKER_FILE
            context:    CONTEXT_THE_IMAGE_SHOULD_HAVE
        volumes:
            - ABSOLUTE_LOCAL_PATH:PATH_INSIDE_CONTAINER
```

## ANONYMOUS VOLUMES
These volumes persist files or folder of a container, but it is only meant to be used by a single container. Its lifecycle is attached to the container, its use cases are:
1 - You want a certain file or folder to persist in a container, and not be lost when it's stopped.
2 - If you have a bind-mount in the container, you may use an anonymous container to override a file found in the local host with the file found in the anonymous volume, for instance
```
docker run --name simple-container \
-v ./app/node_modules \ # anonymous volume.
-v "C:/Users/pablo/Documents/Software Engineering/docker-k8s-complete/simple-ass-container:/app" \ # bind mount.
-d -p 80:80 simple-node
```

Here it doesnt matter what i do with my local node_modules folder, the container will only use the node_modules found in its anonymous volume.


example of usage of case 1:

```
docker run --name simple-container -v ./app/node_modules -d simple-node
```

Note, when using the flag --rm with docker run, not only will be the container removed when it's stopped but also its anonymous volumes.

Example with docker-compose:
```
services:
    api:
        image: my-repo/my-api
        volumes:
            - internal_container_path
```

## NAMED VOLUMES
These are reusable volumes, they're not attached to a single container and they have own their independent life cycle.
example:

With docker run:
```
docker run --name CONTAINER_NAME -v VOLUME_NAME:INTERNAL_CONTAINER_ABSOLUTE_PATH IMAGE_NAME
```

With docker compose:
```
services:
    api:
        image: my-repo/my-api
        volumes:
            - VOLUME_NAME:INTERNAL_CONTAINER_ABSOLUTE_PATH

volumes:
    - VOLUME_NAME
```

If the named volume is not created, docker will create it on the fly with these commands. Anyway you can create the volume separately with
```
docker volume create VOLUME_NAME
```

## A PROBLEM I FACED.
I spin my head around this bug for a while, worth documenting it here. So i had a basic express API which was connecting to a Mongo Atlas DB through the moongose library, it seemed that the repo i cloned had an outdated version of mongoose not compatible with the recent version of ATLAS, so i had to update the package.json dependency to include a more recent version of mongoose.

But, the container was failing, didn't know why. it worked locally, but it was not working on the container. After looking around it, i found (with help of claude) that the /node_modules folder in the container was not updating.

the dockerfile looked like this:
```
FROM NODE:21-alpine

WORKDIR APP

COPY package.json .

RUN npm install

CMD npm start

```

The docker-compose like this:
```
services:
    api:
        image: my-repo/api
        volumes:
            - MY_LOCAL_API:/ # bind mount.
            - /app/node_modules
```

The culprit was, that even if were rebuilding the image, the ultimate node_modules anonymous volume was not picking up the changes (the new dependency). To solve it i used.

```
docker-compose down -v
```
This -v flags remove named volumes declare in the "volumes" section, and anonymous volumes attached to the containers.

I spinned up the container again, and problem solved.