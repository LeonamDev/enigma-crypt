### Simple enigma encripter/decripter

#### License
- MIT License
   - **See LICENSE file**

This was an exercise I did for a subject some time ago, I found this file in my old backups and decided to refactor it and publish here.

Simple implementation with fixed rotors.

The idea is simple, you have 3 concentric rotors containing the caracters you wish to encode.
Then, for encryption of a character ch:

1. Find ch on the inner rotor (inner[x])
2. Find the character aligned with it on the outer rotor (outer[x])
  - The rotors are concentric, so the index is the same, so if ch == inner[5], we'll get outer[5]
3. Find outer[x] in the middle rotor (middle[y])
4. The encrypted character will be outer[y]
5. Rotate inner rotor by 1 position
  - if the inner rotor completed a full turn, rotate middle rotor by 1 position

#### TODOs
- [ ] Remove some duplicated code, especially in file_encode/decode
- [X] Have an option to pipe in encoded/plain data
- [ ] Translate spaces back on decoding
- [ ] Enlarge rotors' character set
- [ ] Allow setting of user-defined characters for rotors
  - *At least to allow programmers to reuse this code*
