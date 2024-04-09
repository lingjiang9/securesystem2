import ctypes
import binascii

# Load the shared library
rijndael = ctypes.CDLL('/Users/jiangling/Desktop/secure 40% 11 April/SecureSystemsAssignment2/rijndael starter code/rijndael.so')

# Define the plaintext and key as lists of decimal values
plaintext = [50, 67, 246, 168, 136, 90, 48, 141, 49, 49, 152, 162, 224, 55, 7, 52]
key = [43, 126, 21, 22, 40, 174, 210, 166, 171, 247, 21, 136, 9, 207, 79, 60]

# Convert plaintext and key to bytes
plaintext_bytes = bytes(plaintext)
key_bytes = bytes(key)

# Ensure the plaintext and key lengths are correct (16 bytes for AES)
assert len(plaintext_bytes) == 16, "Plaintext length must be 16 bytes"
assert len(key_bytes) == 16, "Key length must be 16 bytes"

# Create ctypes string buffers from the byte sequences
plaintext_buffer = ctypes.create_string_buffer(plaintext_bytes)
key_buffer = ctypes.create_string_buffer(key_bytes)

# Define the return type of the AES encryption function
rijndael.aes_encrypt_block.restype = ctypes.POINTER(ctypes.c_char * 16)

# Call the AES encryption function and get the result
result = rijndael.aes_encrypt_block(plaintext_buffer, key_buffer)

# Convert the result to hexadecimal format
result_hex = binascii.hexlify(bytes(result.contents)).decode('utf-8')

# Print the result
print(f"this is the output in hexadecimal: {result_hex}")
