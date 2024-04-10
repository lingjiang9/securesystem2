This is an AES-128 assignment for module Secure Systems Development, implemented in C.Results have been tested against the NIST standard (http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf),Appendix B – Cipher Example page 33-34. 

What is included:

1.rijndael.c is the file that includes all the AES-128 implementation I did.

2.submodule-aes is the file I added as submodule from repo: https://github.com/boppreh/aes.git

3.AssignmentTest.py is the file that tests the entire encryption and decryption in both my C implementation(rijndael.c) and the Python implementation(path:./submodule-aes/aes.py).
It generates 3 random plaintexts and keys, encrypt them with C and Python implementation and compare see if the resulting ciphertexts match.
Then feed the key and ciphertexts into the decryption and ensure that the output matches the
original plaintext. 

4.test.c is the file that tests the single unit functions(sub bytes, shift rows, mix columns, add round key, expand key, main rounds,etc).

5.main.c is the file that provides an 4x4 matrix interface where plaintext and cipher was formatted in 4 x 4 matric.
