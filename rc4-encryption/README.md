RC4 works as a finite automaton with an internal state. It reads a plaintext as a byte
stream and produces a ciphertext as a byte stream. Its hear is actually a key-stream
generator which is used for the one-time pad algorithm. In an initialization stage, a
secret key is processed without producing keys. The automaton ends up in an internal
state which is thus uniquely derived from the secret key only. Then, every time unit,
the automaton updates its internal state and produces a key byte which is XORed to a
plaintext byte in order to lead to a ciphertext byte.
