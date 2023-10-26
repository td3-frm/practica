import os
import scipy.io

# Get the current script's directory (scripts folder)
script_dir = os.path.dirname(os.path.abspath(__file__))

os.chdir(script_dir)

data = scipy.io.loadmat('Tchaikovsky.mat')

print (f"signal shape: {data['signal'].shape}")
print (f"Fs value: {data['Fs'][0]}")

dumb = 0