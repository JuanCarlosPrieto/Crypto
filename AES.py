import base64
import pyaes
import numpy as np
import tkinter as tk
import matplotlib.pyplot as plt
from PIL import Image
from tkinter import filedialog


# Convertir imagen a bytes
def image_to_bits(image_path):
    image = Image.open(image_path).convert('RGB')
    image_array = np.array(image)
    byte_array = image_array.tobytes()
    return byte_array, image_array.shape


# Cifrar datos de imagen con AES
def encrypt_aes(byte_array, key, iv):
    aes_cipher = pyaes.AESModeOfOperationCBC(key, iv=iv)
    
    # Agregar padding para hacer que los datos sean múltiplos del tamaño del bloque (16 bytes)
    pad_length = 16 - (len(byte_array) % 16)
    padded_data = byte_array + bytes([pad_length] * pad_length)
    
    # Cifrar los datos en bloques de 16 bytes
    encrypted_data = b""
    for i in range(0, len(padded_data), 16):
        block = padded_data[i:i + 16]
        encrypted_data += aes_cipher.encrypt(block)
    return encrypted_data


# Decodificar Base64 a bytes
def b64_bits(data):
    return base64.b64decode(data)


# Decifrar datos cifrados con AES
def decrypt_aes(byte_array, key, iv):
    aes_cipher = pyaes.AESModeOfOperationCBC(key, iv=iv)
    
    # Decifrar los datos en bloques de 16 bytes
    decrypted_data = b""
    for i in range(0, len(byte_array), 16):
        block = byte_array[i:i + 16]
        decrypted_data += aes_cipher.decrypt(block)
    
    # Eliminar padding
    pad_length = decrypted_data[-1]
    unpadded_data = decrypted_data[:-pad_length]
    return unpadded_data


# Reconstruir imagen desde los datos descifrados
def recreate_image(data, shape):
    image_array = np.frombuffer(data, dtype=np.uint8)
    image_array = image_array.reshape(shape)
    decrypted_image = Image.fromarray(image_array)
    plt.imshow(decrypted_image)
    plt.axis("off")  # Ocultar ejes
    plt.show()


# Pedir al usuario que elija el tamaño de la clave
def get_aes_key():
    print("Selecciona el tamaño de la clave AES:")
    print("1: 128 bits (16 bytes)")
    print("2: 192 bits (24 bytes)")
    print("3: 256 bits (32 bytes)")

    while True:
        choice = input("Introduce tu elección (1, 2 o 3): ")
        if choice in ['1', '2', '3']:
            break
        print("Opción no válida. Intenta de nuevo.")
    
    key_sizes = {'1': 16, '2': 24, '3': 32}
    key_size = key_sizes[choice]
    key = input(f"Introduce una clave (mínimo {key_size} caracteres): ").encode()
    
    # Ajustar la clave al tamaño adecuado (truncar o rellenar con ceros)
    if len(key) < key_size:
        key = key.ljust(key_size, b'\0')
    elif len(key) > key_size:
        key = key[:key_size]
    
    return key


# Código principal para seleccionar la imagen y realizar cifrado/descifrado
root = tk.Tk()
root.withdraw()
image_path = filedialog.askopenfilename(
    title="Selecciona una imagen",
    filetypes=[("Archivos de imagen", "*.jpg;*.png;*.bmp;*.webp;*.avif")]
)

if image_path:
    key = get_aes_key()  # Obtener la clave del usuario
    iv = b"1234567812345678"  # IV fijo de 16 bytes (puedes mejorarlo si lo haces dinámico)

    # Convertir la imagen a un arreglo de bytes
    byte_array, shape = image_to_bits(image_path)

    # Cifrar la imagen usando AES
    encrypted_data = encrypt_aes(byte_array, key, iv)

    # Codificar los datos cifrados en Base64
    encrypted_b64 = base64.b64encode(encrypted_data)

    # Mostrar el texto cifrado en Base64
    print("Imagen cifrada en Base64:")
    print(encrypted_b64.decode())

    # Decodificar de Base64 y descifrar
    encrypted_bytes = b64_bits(encrypted_b64)
    decrypted_data = decrypt_aes(encrypted_bytes, key, iv)

    # Reconstruir y mostrar la imagen original
    recreate_image(decrypted_data, shape)

else:
    print("No se ha seleccionado ninguna imagen.")

root.destroy()
