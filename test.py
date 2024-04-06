import ctypes
import unittest
import random

class TestBlock(unittest.TestCase):
    """
    Tests AES-128 block operations implemented in C.
    """
    def setUp(self):
        # Load the AES library written in C
        self.aes_lib = ctypes.CDLL("/Users/jiangling/Desktop/secure 40% 11 April/SecureSystemsAssignment2/rijndael starter code/rijndael.so")
        
        # Define the argument and return types for the AES functions
        self.aes_lib.aes_encrypt_block.argtypes = [ctypes.POINTER(ctypes.c_ubyte), ctypes.POINTER(ctypes.c_ubyte)]
        self.aes_lib.aes_encrypt_block.restype = None
        self.aes_lib.aes_decrypt_block.argtypes = [ctypes.POINTER(ctypes.c_ubyte), ctypes.POINTER(ctypes.c_ubyte)]
        self.aes_lib.aes_decrypt_block.restype = None

        # define unit test arguments and return types
        self.aes_lib.sub_bytes.argtypes = [ctypes.POINTER(ctypes.c_ubyte)]
        self.aes_lib.sub_bytes.restype = None


        self.aes_lib.expand_key.argtypes = [ctypes.POINTER(ctypes.c_ubyte), ctypes.POINTER(ctypes.c_ubyte)]
        self.aes_lib.expand_key.restype = None


    # =============================sub_byte test=====================================
    def test_sub_bytes(self):
        """ Test the sub_bytes function in C. """
        for _ in range(3):  # Generate 3 random inputs
            # Generate a random block
            block = [random.randint(0, 255) for _ in range(16)]
            
            # Convert the block to a ctypes array
            block_ctypes = (ctypes.c_ubyte * 16)(*block)
            
            # Call the C function to apply sub_bytes
            self.aes_lib.sub_bytes(block_ctypes)
            
            # Convert the ctypes array back to a list
            block_list = list(block_ctypes)
            
            # Apply sub_bytes in Python
            python_result = self.apply_sub_bytes_py(block)
            
            # Assert that the outputs from C and Python match
            self.assertEqual(block_list, python_result)
            print(block_list, python_result, "sub_bytes test successful")

    def apply_sub_bytes_py(self, block):
        """ Apply sub_bytes in Python. """
        s_box = [
           0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
           0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
           0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
           0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
           0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
           0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
           0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
           0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
           0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
           0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
           0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
           0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
           0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
           0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
           0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
           0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
        ]
        
        # Apply sub_bytes
        return [s_box[val] for val in block]
    
#         # Define a block to apply sub_bytes
#         block = [0x19,0xA0,0x9A,0xE9,0x3D,0xF4,0xC6,0xF8,0xE3,0xE2,0x8D,0x48,0xBE, 0x2B,0x2A,0x08]        
#         # Convert the block to a ctypes array
#         block_ctypes = (ctypes.c_ubyte * 16)(*block)
        
#         # Call the C function to apply sub_bytes
#         self.aes_lib.sub_bytes(block_ctypes)
    
#     # Define the expected result after sub_bytes
#         expected_result = [
#     0xD4, 0xE0, 0xB8, 0x1E, 0x27, 0xBF, 0xB4, 0x41, 0x11, 0x98, 0x5D, 0x52, 0xAE, 0xF1, 0xE5, 0x30
# ]    
#     # Convert the expected result to a ctypes array
#         expected_result_ctypes = (ctypes.c_ubyte * 16)(*expected_result)
    
#     # Convert the ctypes arrays back to lists
#         block_list = list(block_ctypes)
#         expected_result_list = list(expected_result_ctypes)
    
#     # Assert that the block after sub_bytes matches the expected result
#         self.assertEqual(block_list, expected_result_list)
#         print("sub_bytes test successful")

    # =============================shiftrow test=====================================
    def test_shift_rows(self):
        """ Test the shift_rows function in C. """
        # Define a block to apply shift_rows
        block = [0xD4, 0xE0, 0xB8, 0x1E, 0x27, 0xBF, 0xB4, 0x41, 0x11, 0x98, 0x5D, 0x52, 0xAE, 0xF1, 0xE5, 0x30]
        # Convert the block to a ctypes array
        block_ctypes = (ctypes.c_ubyte * 16)(*block)
        
        # Call the C function to apply shift_rows
        self.aes_lib.shift_rows(block_ctypes)
    
        # Define the expected result after shift_rows
        expected_result = [
            0xD4, 0xE0, 0xB8, 0x1E, 0xBF, 0xB4, 0x41, 0x27, 0x5D, 0x52, 0x11, 0x98, 0x30, 0xAE, 0xF1, 0xE5
        ]    
        
        # Convert the expected result to a ctypes array
        expected_result_ctypes = (ctypes.c_ubyte * 16)(*expected_result)
    
        # Convert the ctypes arrays back to lists
        block_list = list(block_ctypes)
        expected_result_list = list(expected_result_ctypes)
    
        # Assert that the block after shift_rows matches the expected result
        self.assertEqual(block_list, expected_result_list)
        print("shift_rows test successful")

  
    # =============================mix columns test=====================================

    def test_mix_columns(self):
        """ Test the mix_columns function in C. """
        # Define a block to apply mix_columns
        block = [
            0xd4, 0xE0, 0xB8, 0x1E,
            0xBF, 0xB4, 0x41, 0x27,
            0x5D, 0x52, 0x11, 0x98,
            0x30, 0xAE, 0xF1, 0xE5
        ]
        # Convert the block to a ctypes array
        block_ctypes = (ctypes.c_ubyte * 16)(*block)
        
        # Call the C function to apply mix_columns
        self.aes_lib.mix_columns(block_ctypes)
    
        # Define the expected result after mix_columns
        expected_result = [
            0x04, 0xE0, 0x48, 0x28,
            0x66, 0xCB, 0xF8, 0x06,
            0x81, 0x19, 0xD3, 0x26,
            0xE5, 0x9A, 0x7A, 0x4C
        ]    
        
        # Convert the expected result to a ctypes array
        expected_result_ctypes = (ctypes.c_ubyte * 16)(*expected_result)
    
        # Convert the ctypes arrays back to lists
        block_list = list(block_ctypes)
        expected_result_list = list(expected_result_ctypes)
    
        # Assert that the block after mix_columns matches the expected result
        self.assertEqual(block_list, expected_result_list)
        print("mix_columns test successful")

    # =============================add round key test=====================================
    # ==============================test expand key =====================================
    def test_expand_key(self):

    # Given 128-bit key
      given_key = b'\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C'
      given_key = bytes.fromhex(given_key)

    # Expected 176-byte expanded key
      expected_expanded_key_hex = """
    2b7e151628aed2a6abf7158809cf4f3c
    a0fafe1788542cb123a339392a6c7605
    f2c295f27a96b9435935807a7359f67f
    3d80477d4716fe3e1e237e446d7a883b
    ef44a541a8525b7fb671253bdb0bad00
    d4d1c6f87c839d87caf2b8bc11f915bc
    6d88a37a110b3efddbf98641ca0093fd
    4e54f70e5f5fc9f384a64fb24ea6dc4f
    ead27321b58dbad2312bf5607f8d292f
    ac7766f319fadc2128d12941575c006e
    d014f9a8c9ee2589e13f0cc8b6630ca6
    """.replace('\n', '').replace(' ', '')
      expected_expanded_key = bytes.fromhex(expected_expanded_key_hex)

    # Define argument and return types for expand_key
      self.aes_lib.expand_key.argtypes = [ctypes.POINTER(ctypes.c_ubyte), ctypes.POINTER(ctypes.c_ubyte)]
      self.aes_lib.expand_key.restype = None

    # Prepare input key as ctypes array
      input_key_ctypes = (ctypes.c_ubyte * 16)(*given_key)
    # Prepare output buffer for expanded key
      output_expanded_key_ctypes = (ctypes.c_ubyte * 176)()

    # Call the expand_key function
      self.aes_lib.expand_key(input_key_ctypes, output_expanded_key_ctypes)

    # Convert the output buffer back to bytes
      output_expanded_key = bytes(output_expanded_key_ctypes)

    # Assert that the expanded key matches the expected value
      self.assertEqual(output_expanded_key, expected_expanded_key, "expand_key test failed")
      print("expand_key test successful")

if __name__ == "__main__":
    unittest.main()




    # def test_success(self):
    #     """ Should be able to encrypt and decrypt block messages. """
    #     # Define a message to encrypt
    #     message = b'\x01' * 16
        
    #     # Convert the message to a ctypes array
    #     message_ctypes = (ctypes.c_ubyte * 16)(*message)
        
    #     # Create a buffer to store the encrypted message
    #     ciphertext = (ctypes.c_ubyte * 16)()
        
    #     # Call the C function to encrypt the message
    #     self.aes_lib.aes_encrypt_block(message_ctypes, ciphertext)
        
    #     # Create a buffer to store the decrypted message
    #     decrypted_message = (ctypes.c_ubyte * 16)()
        
    #     # Call the C function to decrypt the ciphertext
    #     self.aes_lib.aes_decrypt_block(ciphertext, decrypted_message)
        
    #     # Convert the decrypted message back to bytes
    #     decrypted_message_bytes = bytes(decrypted_message)
        
    #     # Assert that the decrypted message matches the original message
    #     self.assertEqual(decrypted_message_bytes, message)

    # def test_expected_value(self):
    #     """
    #     Tests taken from the NIST document, Appendix B:
    #     http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
    #     """
    #     # Define the message and key from the NIST test case
    #     message = b'\x32\x43\xF6\xA8\x88\x5A\x30\x8D\x31\x31\x98\xA2\xE0\x37\x07\x34'
    #     key = b'\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C'
        
    #     # Convert the message and key to ctypes arrays
    #     message_ctypes = (ctypes.c_ubyte * 16)(*message)
    #     key_ctypes = (ctypes.c_ubyte * 16)(*key)
        
    #     # Create a buffer to store the ciphertext
    #     ciphertext = (ctypes.c_ubyte * 16)()
        
    #     # Call the C function to encrypt the message using the provided key
    #     self.aes_lib.aes_encrypt_block(message_ctypes, key_ctypes, ciphertext)
        
    #     # Define the expected ciphertext from the NIST test case
    #     expected_ciphertext = b'\x39\x25\x84\x1D\x02\xDC\x09\xFB\xDC\x11\x85\x97\x19\x6A\x0B\x32'
        
    #     # Convert the expected ciphertext to a ctypes array
    #     expected_ciphertext_ctypes = (ctypes.c_ubyte * 16)(*expected_ciphertext)
        
    #     # Assert that the produced ciphertext matches the expected ciphertext
    #     self.assertEqual(ciphertext, expected_ciphertext_ctypes)

    

if __name__ == "__main__":
    unittest.main()
