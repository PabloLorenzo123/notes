FROM dhi.io/dotnet:10-sdk

# Set working directory inside the namespace, now all commands will work here.
WORKDIR /app
# Copy the source code to the /app folder inside the container file system.
COPY . /app

# This is just documenting, that the process will have a 5001 port with a process listening to it.
EXPOSE 5001

RUN dotnet restore
RUN dotnet build --no-restore
RUN dotnet dev-certs https

CMD ["dotnet", "run", "MinimalApi", "-lp", "https"]
