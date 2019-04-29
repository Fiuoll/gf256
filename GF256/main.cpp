#include <iostream>
#include <string.h>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

constexpr inline unsigned char mult (unsigned char a, unsigned char b)
{
  unsigned char c = 0;
  for (int i = 0; i < 8; i++)
    {
      if (a & 1)
        {
          c ^=  (b << i)
              ^ (b >> (8 - i)) ^ ((b >> (8 - i)) << 1) ^ ((b >> (8 - i)) << 3) ^ ((b >> (8 - i)) << 4)
              ^ ((b >> (8 - i)) >> 5) ^ ((b >> (8 - i)) >> 5 << 1) ^ ((b >> (8 - i)) >> 5 << 3) ^ ((b >> (8 - i)) >> 5 << 4)
              ^ ((b >> (8 - i)) >> 4) ^ ((b >> (8 - i)) >> 4 << 1) ^ ((b >> (8 - i)) >> 4 << 3) ^ ((b >> (8 - i)) >> 4 << 4);
        }
      a >>= 1;
    }
  return c;
}


constexpr array<int, 256> compute_degrees (const unsigned char a)
{
  unsigned char b = 1;
  array<int,256> deg = {};
    for (int i = 1; i < 256; i++)
      {
        deg[b] = i;
        b = mult (a, b);
      }
    return deg;
}

const::std::array<int, 256> degg = compute_degrees (0x11111111);


inline void print (const unsigned char a)
{
  for (int i = 0; i < 8; i++)
    {
      if (a & (1 << (7 - i)))
        printf ("1");
      else
        printf ("0");
    }
  printf ("\n");
}


int main()
{
  unsigned char a = 0, b = 0, c = 0;
  char str1[8], str2, str3[8];


  do
    {
      printf ("Input xxxxxxxx s xxxxxxxx\n");
      scanf ("%s", str1);
      printf ("str1[%d] = %s\n", strlen (str1), str1);
      scanf ("%s", &str2);
      printf ("str2 = %c\n", str2);
      scanf ("%s", str3);
      printf ("str3[%d] = %s\n", strlen (str3), str3);

//      if (strlen (str1) != 8 || strlen (str3) != 8)
//        {
//          printf ("OU\n");
//          break;
//        }

      for (int i = 0; i < 8; i++)
        {
          if (str1[7 - i] == '1')
            a |= 1 << i;
          if (str3[7 - i] == '1')
            b |= 1 << i;
        }

      if (str2 == '+' || str2 == '-')
        {
            c = a ^ b;
            print (c);
        }
      else if (str2 == '*')
        {
          c = mult (a, b);
          print (c);
        }
      else if (str2 == 'x')
        {
          int d = (degg[a] + degg[b]) % 256;
          printf ("deg = %d\n", d);
          for (int i = 0; i < 256; i++)
            {
              if (d == degg[i])
                {
                  c = i;
                }
            }
          print (c);
        }
    }
  while (1);

  return 0;
}
