#pragma once
#include <cstdint>
#include <cmath>
using word=uint32_t;
#define RADIX 4294967296UL
#define HALF_RADIX 2147483648UL
#define INIT_CAP 16
#define MAX(a, b) ((a) > (b) ? (a) : (b))
class UInteger{
public:
    UInteger(){
        cap=INIT_CAP;
        len=0;
        data=new word[INIT_CAP]{};
    }
    UInteger(const UInteger& other){
        cap=other.cap;
        len=other.len;
        data=new word [cap]{};
        for(size_t i=0;i<cap;++i){
            data[i]=other.data[i];
        }
    }
    UInteger(UInteger&& other) noexcept{
        cap=other.cap;
        len=other.len;
        data=other.data;
        other.data= nullptr;
    }
    ~UInteger(){
        cap=0;
        len=0;
        if(data!= nullptr){
            delete[] data;
            data= nullptr;
        }
    }
    static UInteger add(const UInteger& a, const UInteger& b){
        UInteger res;
        word sum , co=0;
        for (size_t i=0;i< MAX(a.len,b.len);++i){
            sum=co;
            if(i<a.len) sum+=a.data[i];
            if(i<b.len) sum+=b.data[i];
            res.push(sum);
            if(i<a.len) {
                co = sum<a.data[i] ? 1 : 0;
            }
            if(i<b.len) {
                co = sum<b.data[i] ? 1 : 0;
            }
        }
        if(co==1){
            res.push(1);
        }
        return res;
    }

private:
    size_t cap;
    size_t len;
    word *data{};

    void push(word w){
        if (len==cap){
            cap*=2;
            word *data1= new word [cap]{};
            for(size_t i=0;i<len;++i){
                data[i]=data1[i];
            }
            delete[] data;
            data=data1;
        }
        data[len]=w;
        ++len;
    }
};