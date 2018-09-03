#ifndef finance_RNG_h
#define finance_RNG_h

class RNG
{
public:
    RNG();
    void init_genrand64(unsigned long long seed);
    void init_by_array64(unsigned long long init_key[],
                         unsigned long long key_length);
    unsigned long long genrand64_int64(void);
    unsigned long long genrand64_int64_back(void);
    unsigned long long genrand64_int64_curr(void);
    long long genrand64_int63(void);
    double genrand64_real1(void);
    double genrand64_real2(void);
    double genrand64_real3(void);
    double genrand64_real1_back(void);
    double genrand64_real1_curr(void);
    double curr(void);
    double draw(void);
    double prev(void);
private:
    /* The array for the state vector */
    unsigned long long mt[312]; 
    /* mti==NN+1 means mt[NN] is not initialized */
    int mti; 
};


#endif
