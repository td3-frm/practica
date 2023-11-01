import numpy as np
import matplotlib.pyplot as plt

def zplane(b, a):
    """
    Plot the complex z-plane given a transfer function.
    """
    
    # Calculate zeros and poles
    zeros = np.roots(b)
    poles = np.roots(a)

    # Plot the unit circle
    unit_circle = plt.Circle((0, 0), 1, color='blue', fill=False, linestyle='dashed')
    
    # Create figure and axis
    fig, ax = plt.subplots()
    ax.add_artist(unit_circle)

    # Plot zeros and poles
    plt.scatter(np.real(zeros), np.imag(zeros), marker='o', color='red', label='Zeros')
    plt.scatter(np.real(poles), np.imag(poles), marker='x', color='green', label='Poles')

    # Set labels and title
    plt.title('Pole-Zero Plot')
    plt.xlabel('Real')
    plt.ylabel('Imaginary')

    # Set equal aspect ratio
    plt.axis('equal')

    # Set grid
    plt.grid(which='both', color='grey', linestyle=':', linewidth=0.5)

    # Add legend
    plt.legend()

    # Show plot
    plt.show()

# Ejemplo de uso de la función
b = np.array([1, -2.5, 1]) # Coeficientes del numerador (zeros)
a = np.array([1, -0.5])    # Coeficientes del denominador (poles)
zplane(b, a)
