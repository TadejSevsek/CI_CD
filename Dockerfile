FROM ubuntu:22.04
RUN apt-get update && apt-get install -y g++ make
COPY src/main.cpp /app/main.cpp
RUN g++ -std=c++17 -o /app/program /app/main.cpp
WORKDIR /app
CMD ["./program"]