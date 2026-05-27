# The Content-Type Header

The Content-Type header indicates the media type of the HTTP message body.

In HTTP requests, it tells the server how the request body should be interpreted.

In HTTP responses, it tells the client or browser how the response body should be interpreted or processed.

Media types (also known as MIME types, from Multiple Internet Mail Extensions) follow the format:

TYPE/SUBTYPE; parameter=value

## Text Type
Indicates that the content is text, its most common substypes are:
- text/plain: have no format.
- text/html: ex. text/html;charset=utf-8.
- text/css.
- text/javascript: use this over application/javascript.

## Application Type
Application data.
- application/json = json.
- application/xml = xml.
- application/x-www-form-urlencoded = commonly used in Html forms, ex name=Pablo&lastName=Lorenzo.. this url is url encoded.

## Image tyoe
- image/jpeg.
- image/png.

## multipart
I have only dealt with
multipart/form-data, it consist on a request with multiple bodies each one having a distinct content-disposition: mime. This is used when we have a form that needs files.

multipart/form-data consists of a single HTTP body divided into multiple parts using MIME boundaries.

ex:
```
POST /upload HTTP1/1.1
host: example.api.com
content-type: multipart/form-data; boundary="abc"

--abc
content-disposition: form-data; name="profile-photo"; filename="profile-photo.jpg"
content-type: image/jpg

<binary content of the photo>

--abc
content-disposition: form-data; name=fullname
content-type: text/plain

Pablo Lorenzo

--abc--

```

Content-Disposition indicates how content should be handled or presented.

- inline: for instance if the server sends back a pdf, it tells the browser to open it in the pdf viewer.
- attachment: tells the browser to download it.
- form-data: used in http request mostly. tells this is the field of a form.
