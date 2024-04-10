import sys
from os.path import abspath, join, dirname

submodule_path = abspath(join(dirname(__file__), 'python-aes'))
sys.path.insert(0, submodule_path)



import ctypes
from aes import AES
import unittest
import random

rijndael = ctypes.CDLL('/Users/jiangling/Desktop/secure 40% 11 April/SecureSystemsAssignment2/rijndael starter code/rijndael.so')

class FinalUnitTest(unittest.TestCase):
#     """
#     Tests raw AES-128 block operations.
#     """
    # def generate_random_16_byte_stringl():
  
    def setUp(self):
        self.aes = AES(b'\x00' * 16)


    # def test_encryption(self):
    #     for _ in range(2): 

    #      # Python test
    #       message = [random.randint(0, 255) for _ in range(16)]
    #       print(f"Message in byte: {message}")
    #       key = [random.randint(0, 255) for _ in range(16)]
    #       print(f"Key in byte: {key}")
    #       ciphertext_python= AES(bytes(key)).encrypt_block(bytes(message))
    #       hex_ciphertext_python = ciphertext_python.hex()
    #       print(f"Ciphertext in hexadecimal in python: {hex_ciphertext_python}")

    #      # C test
    #       byte_message = bytes(message)
    #       byte_key= bytes(key)

    #       message_buffer = ctypes.create_string_buffer(byte_message)
    #       key_buffer = ctypes.create_string_buffer(byte_key)

    #     # Define the return type of the AES encryption function
    #       rijndael.aes_encrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)
        
    #     # Call the AES encryption function and get the result
    #       ciphertext_c =ctypes.string_at(rijndael.aes_encrypt_block(message_buffer, key_buffer), 16)

    #    # Convert to a hexadecimal string
    #       hex_ciphertext_c = ciphertext_c.hex()
          

    #     # Compare the ciphertext(in hexadecimal) in C and python
    #       self.assertEqual(hex_ciphertext_python, hex_ciphertext_c)
    #       print(f"Ciphertext(hexadecimal)\nIn Python: {hex_ciphertext_python}\nIn C: {hex_ciphertext_c} \nTHEY MATCH YAY !!")


    def test_decryption(self):
        for _ in range(2): 

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
          print(f"Plaintext in hexadecimal in Python: {hex_plaintext_python}")
          print(" Plaintext in C: {hex_plaintext_c} \nTHEY MATCH YAY !!")
          
          plaintext_c = list(bytes.fromhex(hex_plaintext_c))
          plaintext_python = list(bytes.fromhex(hex_plaintext_python))
          print(f"Plaintext in C: {plaintext_c}")
          print(f"Plaintext in Python: {plaintext_python}")




          








if __name__ == '__main__':
    unittest.main()









        # self.assertEqual(hex_ciphertext_c, hex_expected_output)
        # print(f"The ciphertext in C {hex_ciphertext_c} and ciphertext in C {hex_expected_output} match")

        # test_input = "66814286504060421741230023322616923956"
        # test_key   = "57811460909138771071931939740208549692"
        # # convert string to decimal:
        # decimal_message = int(test_input)
        # message= decimal_message.to_bytes(16, byteorder='big')
        # print(message)
        # decimal_key = int(test_key)
        # key= decimal_key.to_bytes(16, byteorder='big')
        # print(key)
        # message = b'\x32\x43\xF6\xA8\x88\x5A\x30\x8D\x31\x31\x98\xA2\xE0\x37\x07\x34'
        # key     = b'\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C'
        # expected_output =b'\x39\x25\x84\x1D\x02\xDC\x09\xFB\xDC\x11\x85\x97\x19\x6A\x0B\x32'

        # convert expacted_output in hexadecimal
        # hex_expected_output = expected_output.hex()

        # ciphertext_python= AES(bytes(message)).encrypt_block(bytes(key))
        
        # hex_ciphertext_python = ciphertext_python.hex()
        # print(f"Ciphertext in byte: {hex_ciphertext_python}")
 

  

        







# # Load the shared library
# rijndael = ctypes.CDLL('/Users/jiangling/Desktop/secure 40% 11 April/SecureSystemsAssignment2/rijndael starter code/rijndael.so')

# # Define the plaintext and key as lists of decimal values
# plaintext = [50, 67, 246, 168, 136, 90, 48, 141, 49, 49, 152, 162, 224, 55, 7, 52]
# key = [43, 126, 21, 22, 40, 174, 210, 166, 171, 247, 21, 136, 9, 207, 79, 60]

# # Convert plaintext and key to bytes
# plaintext_bytes = bytes(plaintext)
# key_bytes = bytes(key)

# # Ensure the plaintext and key lengths are correct (16 bytes for AES)
# assert len(plaintext_bytes) == 16, "Plaintext length must be 16 bytes"
# assert len(key_bytes) == 16, "Key length must be 16 bytes"

# # Create ctypes string buffers from the byte sequences
# plaintext_buffer = ctypes.create_string_buffer(plaintext_bytes)
# key_buffer = ctypes.create_string_buffer(key_bytes)

# # Define the return type of the AES encryption function
# rijndael.aes_encrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)

# # Call the AES encryption function and get the result
# result = rijndael.aes_encrypt_block(plaintext_buffer, key_buffer)

# # Convert the result to hexadecimal format
# result_hex = binascii.hexlify(bytes(result.contents)).decode('utf-8')

# # Print the result
# print(f"this is the output in hexadecimal: {result_hex}")





  # def test_encrypt_python_and_c(self):
    #     """
    #     Tests taken from the NIST document, Appendix B:
    #     http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
    #     """
    #      # Python test
    #     message = b'\x32\x43\xF6\xA8\x88\x5A\x30\x8D\x31\x31\x98\xA2\xE0\x37\x07\x34'
    #     key     = b'\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C'
    #     expected_output =b'\x39\x25\x84\x1D\x02\xDC\x09\xFB\xDC\x11\x85\x97\x19\x6A\x0B\x32'

    #     # convert expacted_output in hexadecimal
    #     hex_expected_output = expected_output.hex()

    #     ciphertext_python= AES(bytes(key)).encrypt_block(bytes(message))
    #     hex_ciphertext_python = ciphertext_python.hex()
 

    #     # C test
    #     message_buffer = ctypes.create_string_buffer(message)
    #     key_buffer = ctypes.create_string_buffer(key)

    #     # Define the return type of the AES encryption function
    #     rijndael.aes_encrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)
        
    #     # Call the AES encryption function and get the result
    #     ciphertext_c =ctypes.string_at(rijndael.aes_encrypt_block(message_buffer, key_buffer), 16)
    #     print(f"Ciphertex_c in byte: {ciphertext_c}") # b'9%\x84\x1d\x02\xdc\t\xfb\xdc\x11\x85\x97\x19j\x0b2'

    #    # Convert to a hexadecimal string
    #     hex_ciphertext_c = ciphertext_c.hex()

    #    # Compare the ciphertext(in hexadecimal) in C and python
    #     self.assertEqual(hex_ciphertext_python, hex_ciphertext_c)
    #     print(f"The ciphertext in python {hex_ciphertext_python} and the ciphertext in C {hex_ciphertext_c} MATCH")
    #     self.assertEqual(hex_ciphertext_c, hex_expected_output)
    #     print(f"The ciphertext in C {hex_ciphertext_c} and ciphertext in C {hex_expected_output} MATCH")
