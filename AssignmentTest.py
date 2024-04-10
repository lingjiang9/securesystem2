
import sys
sys.path.append('./submodule-aes')
from aes import AES

import ctypes
import unittest
import random



rijndael = ctypes.CDLL('./rijndael.so')

class FinalUnitTest(unittest.TestCase):
#     """
#     Tests raw AES-128 block operations.
#     """
    # def generate_random_16_byte_stringl():
  
    def setUp(self):
        self.aes = AES(b'\x00' * 16)


    def test_encryption(self):
        for _ in range(3): 

         # Python test
          message = [random.randint(0, 255) for _ in range(16)]
          print(f"Message in byte: {message}")
          key = [random.randint(0, 255) for _ in range(16)]
          print(f"Key in byte: {key}")
          ciphertext_python= AES(bytes(key)).encrypt_block(bytes(message))
          hex_ciphertext_python = ciphertext_python.hex()
          print(f"Ciphertext in hexadecimal in python: {hex_ciphertext_python}")

         # C test
          byte_message = bytes(message)
          byte_key= bytes(key)

          message_buffer = ctypes.create_string_buffer(byte_message)
          key_buffer = ctypes.create_string_buffer(byte_key)

        # Define the return type of the AES encryption function
          rijndael.aes_encrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)
        
        # Call the AES encryption function and get the result
          ciphertext_c =ctypes.string_at(rijndael.aes_encrypt_block(message_buffer, key_buffer), 16)

       # Convert to a hexadecimal string
          hex_ciphertext_c = ciphertext_c.hex()
          

        # Compare the ciphertext(in hexadecimal) in C and python
          self.assertEqual(hex_ciphertext_python, hex_ciphertext_c)
          print(f"Ciphertext(hexadecimal)\nIn Python: {hex_ciphertext_python}\nIn C: {hex_ciphertext_c} \nTHEY MATCH ENCRYPTION SUCCESS YAY !!")


    def test_decryption(self):
        for _ in range(3): 

         # Python test
          message = [random.randint(0, 255) for _ in range(16)]
          key = [random.randint(0, 255) for _ in range(16)]

          plaintext_python= AES(bytes(key)).decrypt_block(bytes(message))
          hex_plaintext_python = plaintext_python.hex()

         # C test
          byte_message = bytes(message)
          byte_key= bytes(key)
          message_buffer = ctypes.create_string_buffer(byte_message)
          key_buffer = ctypes.create_string_buffer(byte_key)

        # Define the return type of the AES decryption function
          rijndael.aes_decrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)
        
        # Call the AES decryption function and get the result
          plaintext_c =ctypes.string_at(rijndael.aes_decrypt_block(message_buffer, key_buffer), 16)

       # Convert to a hexadecimal string
          hex_plaintext_c = plaintext_c.hex()
    

        # Compare the plaintext(in hexadecimal) in C and python
          self.assertEqual(hex_plaintext_python, hex_plaintext_c)
          print(f"Plaintext(hexadecimal) in Python: {hex_plaintext_python}")
          print(f"Plaintext(hexadecimal) in C: {hex_plaintext_c} \nTHEY MATCH")
          
          plaintext_c = list(bytes.fromhex(hex_plaintext_c))
          plaintext_python = list(bytes.fromhex(hex_plaintext_python))
          print(f"Plaintext in C: {plaintext_c}")
          print(f"Plaintext in Python: {plaintext_python} \nThey MATCH, ENCRYPTION SUCCESS YAY !!")
    



       




if __name__ == '__main__':
    unittest.main()









        
   