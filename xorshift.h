//
//  xorshift.h
//  ddouble
//
//  Created by Juan Lucas Rey on 15/05/2016.
//  Copyright © 2016 Juan Lucas Rey. All rights reserved.
//

#ifndef xorshift_h
#define xorshift_h

#include <stdint.h>
#include <vector>
#include <iostream>

using namespace std;

template< int i, typename Type, typename Enable = void >
class UnXorSh{
public:
    static inline Type Right( Type x)
    {
        x ^= x >> i;
        return UnXorSh< (i << 1), Type >::Right(x);
    }
    
    static inline Type Left( Type x)
    {
        x ^= x << i;
        return UnXorSh< (i << 1), Type >::Left(x);
    }
};

template< int i, typename Type >
class UnXorSh< i, Type, typename std::enable_if< (i >= sizeof(Type)*CHAR_BIT) >::type >{
public:
    static inline Type Right( Type x)
    {
        return x;
    }
    
    static inline Type Left( Type x)
    {
        return x;
    }
};


uint32_t UnXorShl32(uint32_t x, uint32_t shift);
uint32_t UnXorShr32(uint32_t x, uint32_t shift);
uint64_t UnXorShl64(uint64_t x, uint32_t shift);
uint64_t UnXorShr64(uint64_t x, uint32_t shift);

class PRNG32
{
public:
    virtual uint32_t curr() = 0;
    virtual uint32_t draw() = 0;
    virtual uint32_t prev() = 0;
};

class PRNG64
{
public:
    virtual uint64_t curr() = 0;
    virtual uint64_t draw() = 0;
    virtual uint64_t prev() = 0;
};

class xorshift128 : public PRNG32
{
public:
    xorshift128(uint32_t x,uint32_t y,uint32_t z,uint32_t w):
    mX(x),mY(y),mZ(z),mW(w){}
    
    uint32_t curr(){return mW;}
    uint32_t draw();
    uint32_t prev();
    
private:
    
    uint32_t mX,mY,mZ,mW;
    
};

class xorshift64star : public PRNG64
{
public:
    xorshift64star(uint32_t x):
    mX(x){}
    
    uint64_t curr();
    uint64_t draw();
    uint64_t prev();
    
private:
    
    uint64_t mX;
    
};

class xorshift1024star : public PRNG64
{
public:

    xorshift1024star(vector<uint64_t> s, int p) : mS(s),mP(p)
    {}
    
    uint64_t curr();
    uint64_t draw();
    uint64_t prev();
    
private:
    
    vector<uint64_t> mS;
    int mP;
    
};

class xorshift128plus : public PRNG64
{
public:
    
    xorshift128plus(uint64_t s1, uint64_t s2)
    {
        mS[0] = s1;
        mS[1] = s2;
    }
    
    uint64_t curr();
    uint64_t draw();
    uint64_t prev();
    
private:
    
    uint64_t mS[2];
    
};

#endif /* xorshift_h */
