# Video Streaming
There are various ways to send a video to a client, the simplest one is for the video to live in a server, and the client to ask for it, wait for all the bytes of the video to be downloaded in the client application and then play. Of course, this a terrible choice for streaming services, as it makes the user experience and internet experience way worse.

Before explaining the protocols, let's explain a video, a video is a file which consists of multiple images, these images contains an array of bits which encode a color at each image pixel, when these images are played at a rate the ilussion of a motion is displayed. The amount of bits needed to play a second of the video will depend on:

1 - The image quality, higher definition image contain more bits.
2 - frames per second, more images per second means more bits per second.

Video files can't simply be transmitted over the internet just as they are, because they're usually heavy, specially high quality videos, that's why we need to compressed them using an encoding algorithm or CODEC, the most popular is H.264. This codec algorithm is used by an encoder, it reads the bytes from the application and decode its back to the original video (in the client side), the rate at which the encoder decode the chunks is called `bitrate`.

## DASH (Dynamic Advanced Streaming over Http)
DASH runs on top of http on top of UDP, and basically it consists on sending a stream of chunks of bytes corresponding to the video. The client can adapt the bitrate of the video chunks being requested, this allows it to adapt to the current bandwith.

You may have seen this on sites like youtube, where the video quality make change mid-video due to the network conditions, that's Dash in action. If the throughput is less than the decoding rate / bitrate, then loading spinners appear on the screen, because the video is being played at a faster rate than the byte video buffer is getting filled at.

