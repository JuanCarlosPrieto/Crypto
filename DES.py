import base64
import pyDes
import numpy as np
import tkinter as tk
import matplotlib.pyplot as plt
from PIL import Image
from tkinter import filedialog



def image_to_bits(image_path):
    image = Image.open(image_path).convert('RGB')
    image_array = np.array(image)
    byte_array = image_array.tobytes()
    return byte_array, image_array.shape


def encrypt_des(byte_array, key):
    des_key = key[:8]
    des_cipher = pyDes.des(des_key, pyDes.CBC, b"12345678", pad=None, padmode=pyDes.PAD_PKCS5)

    encrypted_data = des_cipher.encrypt(byte_array)
    return encrypted_data


def bits_b64(data):
    return base64.b64encode(data)



def b64_bits(data):
    return base64.b64decode(data)


def descipher_des(byte_array, key):
    des_key = key[:8]
    des_cipher = pyDes.des(des_key, pyDes.CBC, b"12345678", pad=None, padmode=pyDes.PAD_PKCS5)

    decrypted_data = des_cipher.decrypt(byte_array)
    return decrypted_data


def recreate_image(data, shape):
    image_array = np.frombuffer(data, dtype=np.uint8)
    image_array = image_array.reshape(shape)

    decrypted_image = Image.fromarray(image_array)
    plt.imshow(decrypted_image)
    plt.show()




# Recibir como entrada cualquier imagen en cualquier formato
root = tk.Tk()
root.withdraw()
image_path = filedialog.askopenfilename(title="Selecciona una imagen",
                                        filetypes=[("Archivos de imagen", "*.jpg;*.png;*.bmp;*.webp;*.avif")])


if image_path:
    key = b'porelmismoriopasamos'
    
    # Convertir la imagen a una representación de bits, por lo que simplemente convierta el archivo que lee en un arreglo de bits
    byte_array, shape = image_to_bits(image_path)

    # Cifrar la imagen utilizando DES y una clave determinada por usted
    encryption = encrypt_des(byte_array, key)

    # Codificar el mensaje cifrado en Base64 
    mes_b64 = bits_b64(encryption)
    
    # Mostrar en la consola el texto en Base 64
    print(mes_b64)

    # Decodificar de Base64 a la representación en bits
    img_b64 = b64_bits(mes_b64)

    # Decifrar utilizando DES
    decryption = descipher_des(img_b64, key)

    # Generar la imagen original y mostrarla
    recreate_image(decryption, shape)

else:
    print('No se ha seleccionado ninguna imagen')

root.destroy()