import os

# Create a named pipe (FIFO)
fifo_name = 'myfifo'
if not os.path.exists(fifo_name):
    os.mkfifo(fifo_name)

# Fork the process
pid = os.fork()

if pid == 0:
    # This is the child process
    # Open the FIFO for writing
    fifo = open(fifo_name, 'w')
    # Write a message to the FIFO
    fifo.write('Hello from the child process!\n')
    # Close the FIFO
    fifo.close()
else:
    # This is the parent process
    # Open the FIFO for reading
    fifo = open(fifo_name, 'r')
    # Read the message from the FIFO
    message = fifo.read()
    # Close the FIFO
    fifo.close()
    # Print the message
    print('Received message from child process:', message)
