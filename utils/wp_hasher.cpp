#include <QString>
#include "wp_hasher.hpp"


namespace utils
{

qint8 q[] = {0, 15, 17, 3, 19, 6, 6, 11, 18, 13, 25, 24, 26, 13, 20, 18, 10, 15, 14, 9, 19, 5, 9, 22, 11, 24, 12, 19, 16, 13, 29, 16};
qint8 r[] = {0, 1, 1, 8, 1, -3, -3, 8, -6, 1, 1, -6, -9, 0, -13, -7, 6, 2, 1, 8, 11, 0, -4, 6, 6, -5, 1, -9, -1, -11, -5, -1};


string_type
hasher(const string_type &magic, const string_type &salt)
{
    string_type hashed;
    hashed.reserve(32);
    int a,b;
    bool foo;
    for (int i = 0; i < 32; i++) 
    {
        b = magic.mid(i,1).toInt(&foo, 16);
        a = salt.mid(i&7,1).toInt(&foo, 16);

        (b > 57)? b -= 87 : b -=48;
        (a > 57)? a -= 87 : a -=48;


        b = (((b ^ q[i] ^ a ) + r[i]) & 0xf);

        (b > 9)? b += 87 : b += 48;

        hashed.append(char_type(b));
    }
    qint64 ctime = time_type::currentDateTime().currentMSecsSinceEpoch();
    time_list tl;
    tl.append(ctime & 0xf);
    ctime >>= 4;
    tl.append(ctime & 0xf);
    ctime >>= 4;
    tl.append(ctime & 0xf);

    tl.append( (-tl[0] - tl[1] - tl[2])  &0xf   );

    for (int i = 0; i < 4; i++) 
    {
        qint8& x = tl[i];
        (x > 8)? x += 87 : x += 48;
        hashed.append(char_type(x));
    }


    return hashed;

}


}
