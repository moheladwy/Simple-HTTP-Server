# Use a minimal base image with GCC installed
FROM alpine:3.18

# Install necessary build tools
ARG GCC_VERSION=13.2.0-r3
ARG MUSL_VERSION=1.2.4-r0
RUN apk add --no-cache \
    gcc=${GCC_VERSION} \
    musl-dev=${MUSL_VERSION} \
    make

# Set working directory
WORKDIR /server

# Copy source files
COPY . .

# Build the project
RUN make build

# Expose the port the server listens on
EXPOSE 8080

# Set environment variables if needed
ENV PORT=8080

# Run the server when the container starts
CMD ["./server.bin"]

# Use a non-root user for better security
RUN adduser -D appuser
USER appuser
