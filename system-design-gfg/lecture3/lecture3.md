# Load balancing

## Hashing

## Load Balancing Consistent Hashing


# Proxies
![alt text](image.png)
## Forward proxy

## Reverse Proxy


# CAD THEOREM

# Design Google Drive
![alt text](image-3.png)
## Requirements
### Functional Requirements
- Users should be able to upload files, create folders, copy and move files & folder just like a filesystem.
- Users should be able to access their files from any device, as long as they're logged in to their accounts.

### No functional requirements
- Resumable upload.

### Schema
- File
- Folders
- FileMetadata

### API
![alt text](image-1.png)

### HLD

#### Upload File
Blobs as S3, and Azure Blob can create events and execute lambda or azure functions.
![alt text](image-2.png)

#### Share File
use a join tbale.

#### Download File

##### CDNS and its problem

#### Sync The Multiple Clients.
![alt text](image-4.png)

##### Server Sent Events SSE.

##### Push & Pull

### How to upload the file of size 100GB
- Dynamic Chunking
- Static Chunking

#### How to update the file

### File Compression

### How to encrypt the files.

# Content-Encoding Response Header, BR & GZIP

# Homework
Create a Podcast System, suscribers, notifications of podcast uploaded. take in consideration there are celebrities.

