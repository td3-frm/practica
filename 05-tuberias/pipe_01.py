import os

# Create a pipe
read_pipe, write_pipe = os.pipe()

# Create a child process
child_pid = os.fork()

if child_pid == 0:
    # This is the child process
    os.close(write_pipe)
    message = os.read(read_pipe, 1024)
    print(f'Received message in child process: {message.decode()}')
    os.close(read_pipe)
    exit(0)
else:
    # This is the parent process
    os.close(read_pipe)
    message = b'Hello from parent process!'
    os.write(write_pipe, message)
    os.close(write_pipe)
    pid, status = os.waitpid(child_pid, 0)
    print(f'Child process {child_pid} finished with status {status}')
