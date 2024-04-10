
# This is a file that tests the encryption and decryption of AES in python and C and compares the results see if they match

import sys
sys.path.append('./submodule-aes')
from aes import AES

import ctypes
import unittest
import random

rijndael = ctypes.CDLL('./rijndael.so')

class FinalUnitTest(unittest.TestCase):

   def setUp(self):
        self.aes = AES(b'\x00' * 16)
        self.original_key = [random.randint(0, 255) for _ in range(16)]
        self.original_message = [random.randint(0, 255) for _ in range(16)]
        print(f"Original Key: {self.original_key}")
        print(f"Original Message: {self.original_message}")

        self.key = bytes(self.original_key)
        self.message = bytes(self.original_message)


   def test_aes(self):    
       ciphertext_python= AES(bytes(self.key)).encrypt_block(bytes(self.message))
       self.ciphertext_python = ciphertext_python
       self.hex_ciphertext_python = self.ciphertext_python.hex()
      

       byte_message = bytes(self.message)
       byte_key= bytes(self.key)

       message_buffer = ctypes.create_string_buffer(byte_message)
       key_buffer = ctypes.create_string_buffer(byte_key)

        # Define the return type of the AES encryption function
       rijndael.aes_encrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)
        
        # Call the AES encryption function and get the result
       self.ciphertext_c =ctypes.string_at(rijndael.aes_encrypt_block(message_buffer, key_buffer), 16)

       # Convert to a hexadecimal string
       self.hex_ciphertext_c = self.ciphertext_c.hex()
  
       self.assertEqual(self.hex_ciphertext_python, self.hex_ciphertext_c)
       print(f"Ciphertext(hexadecimal)after Encryption:\nIn Python: {self.hex_ciphertext_python}\nIn C: {self.hex_ciphertext_c} \nTHEY MATCH. ENCRYPTION SUCCESS YAY")


       plaintext_python= AES(bytes(self.key)).decrypt_block(bytes(self.ciphertext_python))
       self.hex_plaintext_python = plaintext_python.hex()

       byte_message = bytes(self.ciphertext_c)
       byte_key= bytes(self.key)
       message_buffer = ctypes.create_string_buffer(byte_message)
       key_buffer = ctypes.create_string_buffer(byte_key)

        # Define the return type of the AES decryption function
       rijndael.aes_decrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)
        
        # Call the AES decryption function and get the result
       plaintext_c =ctypes.string_at(rijndael.aes_decrypt_block(message_buffer, key_buffer), 16)

       # Convert to a hexadecimal string
       self.hex_plaintext_c = plaintext_c.hex()


       self.assertEqual(self.hex_plaintext_python, self.hex_plaintext_c)
       print(f"Plaintext(hexadecimal)after Decryption:\nIn Python: {self.hex_plaintext_python}")
       print(f"In C: {self.hex_plaintext_c}")
          
       plaintext_c = list(bytes.fromhex(self.hex_plaintext_c))
       plaintext_python = list(bytes.fromhex(self.hex_plaintext_python))
       print(f"Plaintext after Decryption in C: {plaintext_c}")
       print(f"Plaintext after Decryption in Python: {plaintext_python} \nTHEY MATCH, DECRYPTION SUCCESS YAY")

       self.assertEqual(plaintext_c, self.original_message)
       print(f"Original Message: {self.original_message} and Plaintext after Decryption in C: {plaintext_c} \nTHEY MATCH, SUCCESS")



if __name__ == '__main__':
    
    for _ in range(3):
        unittest.main(argv=[''], exit=False)










        
   