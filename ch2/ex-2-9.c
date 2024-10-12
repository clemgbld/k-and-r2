int bitcount(unsigned x) {
  int b;
  for (b = 0; x != 0; x &= (x - 1))
    b++;
  return b;
}

/*
explaining what is happening with the substitution model
let's take 22 for x

first iteration
b = 0;
x &= (x - 1)
22 in binary = 10110
22 - 1 = 21 in binary = 10101
10110 & 10101 = 10100 = 20 in decimal

second iteration
b = 1;
x &= (x - 1)
20 in binary = 10100
20 - 1 = 19 in binary = 10011
10100 & 10011 = 10000 = 16 in decimal

third iteration
b = 2;
x &= (x - 1)
16 in binary = 10000
16 - 1 = 15 in binary = 01111
10000 & 01111 = 0 = 0 in decimal

x is 0 so the iteration stop
and b = 3 so the number of 1 bits in 22 is 3

*/
