The Caesar Cipher was improved in the sixteenth century by Blaise de Vigenere.
Here we consider every character as an integral residue modulo the size of the alphaet.
This way, the Caesar Cipher can be consideed as adding 3 to every characters. The
Vigenere Cipher consists of using a word as a secret key K, splitting the messages into
blocks of the same length of the key, and adding characterwise the key onto every
block.

As an example we encrypt "this is a dummy message withe the key ABC.
Here we need t compute

    thi sis adu mmy mes sag e
+   ABC ABC ABC ABC ABC ABC A
-----------------------------
=   TIK SJU AEW MNA MFU SBI E

and we obtain TIKSJUAEWMNAMFUSBIE. Note that adding A, B and C corresponds
to a translation by 0, 1 and 2 positions respectively in the alphabet. Translations are
cyclic, e.g. y + C = A.
