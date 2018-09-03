//
//  xorshift.cpp
//  ddouble
//
//  Created by Juan Lucas Rey on 15/05/2016.
//  Copyright © 2016 Juan Lucas Rey. All rights reserved.
//

#include "xorshift.h"

uint32_t UnXorShl32(uint32_t x, uint32_t shift)
{
    for (uint32_t i = shift; i < 32; i <<= 1)
        x ^= x << i;
    
    return x;
}

uint32_t UnXorShr32(uint32_t x, uint32_t shift)
{
    for (uint32_t i = shift; i < 32; i <<= 1)
        x ^= x >> i;
    
    return x;
}

uint64_t UnXorShl64(uint64_t x, uint32_t shift)
{
    for (uint32_t i = shift; i < 64; i <<= 1)
        x ^= x << i;
    
    return x;
}

uint64_t UnXorShr64(uint64_t x, uint32_t shift)
{
    for (uint32_t i = shift; i < 64; i <<= 1)
        x ^= x >> i;
    
    return x;
}

uint32_t xorshift128::draw()
{
    uint32_t t = mX ^ (mX << 11);
    t ^= t >> 8;
    mX = mY; mY = mZ; mZ = mW;
    mW ^= mW >> 19;
    mW ^= t;
    
    return mW;
}

uint32_t xorshift128::prev()
{
    uint32_t t = mW ^ mZ ^ (mZ >> 19);
    
    //function
    //t = UnXorShr32 (t, 8);
    //t = UnXorShl32 (t, 11);

    //manual
    //t ^= t >> 8;
    //t ^= t >> 16;
    //t ^= t << 11;
    //t ^= t << 22;
    
    //template
    t = UnXorSh< 8, uint32_t >::Right(t);
    t = UnXorSh< 11, uint32_t>::Left(t);
    
    mW = mZ;
    mZ = mY;
    mY = mX;
    mX = t;
    
    return mW;
}

uint64_t xorshift64star::draw()
{
    mX ^= mX >> 12;
    mX ^= mX << 25;
    mX ^= mX >> 27;
    return mX * UINT64_C(2685821657736338717);
}

uint64_t xorshift64star::curr()
{
    return mX * UINT64_C(2685821657736338717);
}

uint64_t xorshift64star::prev()
{
    //function
    //mX = UnXorShr64 (mX, 27);
    //mX = UnXorShl64 (mX, 25);
    //mX = UnXorShr64 (mX, 12);
    
    //manual
    //mX ^= mX >> 27;
    //mX ^= mX >> 54;
    //mX ^= mX << 25;
    //mX ^= mX << 50;
    //mX ^= mX >> 12;
    //mX ^= mX >> 24;
    //mX ^= mX >> 48;
    
    //template
    mX = UnXorSh< 27, uint64_t >::Right(mX);
    mX = UnXorSh< 25, uint64_t>::Left(mX);
    mX = UnXorSh< 12, uint64_t >::Right(mX);

    return mX * UINT64_C(2685821657736338717);
}

uint64_t xorshift1024star::draw()
{
    const uint64_t s0 = mS[mP];
    uint64_t s1 = mS[mP = (mP + 1) & 15];
    s1 ^= s1 << 31; // a
    mS[mP] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b, c
    return mS[mP] * UINT64_C(1181783497276652981);
}

uint64_t xorshift1024star::curr()
{
    return mS[mP] * UINT64_C(1181783497276652981);
}

uint64_t xorshift1024star::prev()
{
    uint64_t s1 = mS[mP];
    const uint64_t s0 = mS[mP = (mP - 1) & 15];

    s1 ^= (s0 >> 30) ^ s0;
    
    //function
    //s1 = UnXorShr64 (s1, 11);
    //s1 = UnXorShl64 (s1, 31);
    
    //manual
    //s1 ^= s1 >> 11;
    //s1 ^= s1 >> 22;
    //s1 ^= s1 >> 44;
    //s1 ^= s1 << 31;
    //s1 ^= s1 << 62;
    
    //template
    s1 = UnXorSh< 11, uint64_t >::Right(s1);
    s1 = UnXorSh< 31, uint64_t>::Left(s1);
    
    mS[(mP + 1) & 15] = s1;
    
    return mS[mP] * UINT64_C(1181783497276652981);
}

uint64_t xorshift128plus::draw()
{
    uint64_t x = mS[0];
    uint64_t const y = mS[1];
    mS[0] = y;
    x ^= x << 23; // a
    mS[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return mS[1] + y;
}

uint64_t xorshift128plus::curr()
{
    return mS[1] + mS[0];
}

uint64_t xorshift128plus::prev()
{
    uint64_t const y = mS[0];
    uint64_t x = mS[1] ^ y ^ (y >> 26);
    
    //function
    //x = UnXorShr64 (x, 17);
    //x = UnXorShl64 (x, 23);
    
    //manual
    //x ^= x >> 17;
    //x ^= x >> 34;
    //x ^= x << 23;
    //x ^= x << 46;
    
    //template
    x = UnXorSh< 17, uint64_t >::Right(x);
    x = UnXorSh< 23, uint64_t>::Left(x);
    
    mS[0] = x;
    mS[1] = y;
    return y + mS[0];
}