#include <cstring>
#include <functional>
#include <cstdint>
template<class T,class ...Args>
struct addr_set{
	T* fir;
	addr_set<Args...> els;
	addr_set():fir(nullptr),els(){}
	template<class TT>
	addr_set(const TT &x):fir(nullptr),els(x){}
	addr_set(const T &x):els(){
		fir=new T(x);
	}
	addr_set(const addr_set<T,Args...> &x):fir(nullptr),els(x.els){
		if(x.fir!=nullptr)
			fir=new T(*x.fir);
	}
	~addr_set(){
		if(fir!=nullptr)
			delete fir;
	}
	template<class TT>
	addr_set operator=(const TT &x){
		els=x;
		return *this;
	}
	addr_set operator=(const T &x){
		if(fir==nullptr)
			fir=new T(x);
		else
			*fir=x;
		return *this;
	}
	addr_set operator=(const addr_set<T,Args...> &x){
		if(x.fir==nullptr)
			if(fir==nullptr);
			else{
				delete fir;
				fir=nullptr;
			}
		else
			if(fir==nullptr)
				fir=new T(*x.fir);
			else
				*fir=*x.fir;
		els=x.els;
		return *this;
	}
	
	bool operator<(const addr_set<T,Args...> &x) const{
		int tmp=fir==nullptr||x.fir==nullptr?fir-x.fir:memcmp(fir,x.fir,T::siz);
		return tmp?tmp<0:els<x.els;
	}
	bool operator>(const addr_set<T,Args...> &x) const{
		int tmp=fir==nullptr||x.fir==nullptr?fir-x.fir:memcmp(fir,x.fir,T::siz);
		return tmp?tmp>0:els>x.els;
	}
	bool operator==(const addr_set<T,Args...> &x) const{
		return (fir==nullptr||x.fir==nullptr?fir==x.fir:memcmp(fir,x.fir,T::siz)==0)&&els==x.els;
	}
	bool operator!=(const addr_set<T,Args...> &x) const{
		return (fir==nullptr||x.fir==nullptr?fir!=x.fir:memcmp(fir,x.fir,T::siz)!=0)||els!=x.els;
	}
	template<class TT>
	explicit operator TT() const{
		return TT(els);
	}
	explicit operator T() const{
		return *fir;
	}
	template<class TT>
	bool match(const TT &x){
		return els.match(x);
	}
	bool match(const T &x){
		return memcmp(fir,&x,T::siz)==0;
	}
};
template<class T>
struct addr_set<T>{
	T* fir;
	addr_set():fir(nullptr){}
	addr_set(const T &x){
		fir=new T(x);
	}
	addr_set(const addr_set<T> &x):fir(nullptr){
		if(x.fir!=nullptr)
			fir=new T(*x.fir);
	}
	~addr_set(){
		if(fir!=nullptr)
			delete fir;
	}
	addr_set operator=(const T &x){
		if(fir==nullptr)
			fir=new T(x);
		else
			*fir=x;
		return *this;
	}
	addr_set operator=(const addr_set<T> &x){
		if(x.fir==nullptr)
			if(fir==nullptr);
			else{
				delete fir;
				fir=nullptr;
			}
		else
			if(fir==nullptr)
				fir=new T(*x.fir);
			else
				*fir=*x.fir;
		return *this;
	}
	bool operator<(const addr_set<T> &x) const{
		if(fir==nullptr||x.fir==nullptr)
			return x.fir!=nullptr;
		return memcmp(fir,x.fir,T::siz)<0;
	}
	bool operator>(const addr_set<T> &x) const{
		if(fir==nullptr||x.fir==nullptr)
			return fir!=nullptr;
		return memcmp(fir,x.fir,T::siz)>0;
	}
	bool operator==(const addr_set<T> &x) const{
		if(fir==nullptr||x.fir==nullptr)
			return fir==x.fir;
		return memcmp(fir,x.fir,T::siz)==0;
	}
	bool operator!=(const addr_set<T> &x) const{
		if(fir==nullptr||x.fir==nullptr)
			return fir!=x.fir;
		return memcmp(fir,x.fir,T::siz)!=0;
	}
	explicit operator T() const{
		return *fir;
	}
	bool match(const T &x){
		return memcmp(fir,&x,T::siz)==0;
	}
};
namespace std{
	template<class T,class ...Args>
	struct hash<addr_set<T,Args...>>{
		size_t operator()(const addr_set<T,Args...> &x) const{
			constexpr uint64_t prime=0x100000001B3;
        	uint64_t result=hash<addr_set<Args...>>()(x.els);
        	if(x.fir!=nullptr)
    	    	for(int i=0;i<T::siz;i++)
        			result=result*prime^i[(uint8_t*)x.fir];
        	return result;
		}
	};
	template<class T>
	struct hash<addr_set<T>>{
		size_t operator()(const addr_set<T> &x) const{
			constexpr uint64_t prime=0x100000001B3;
        	uint64_t result=0xcbf29ce484222325;
        	if(x.fir!=nullptr)
        		for(int i=0;i<T::siz;i++)
        			result=result*prime^i[(uint8_t*)x.fir];
        	return result;
		}
	};
}