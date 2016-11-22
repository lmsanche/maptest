#ifndef TEST_H_
#define TEST_H_

#include "stdafx.h"
#include <map>
#include <unordered_map>
#include <chrono>
#include <random>
#include <iostream>
#include <utility>      // std::pair
#include <typeinfo>
#include <functional>
#include <string>
#include "sparsepp.h"

//#define DEBUG 
#define  MYHASH


#ifdef DEBUG
#define M_DebugLog( msg )  std::cout << __FILE__ << ":" << __LINE__ << ": " << __FUNCTION__ << ": "<< msg << std::endl;
#else
#define M_DebugLog( msg ) 
#endif
template<typename T>
inline std::string c2s(T v){
	std::string s (v);	
	return s;
}


//using mykey = int;
//using mydata = double;
//using userdatatype = std::pair<mykey, mydata>;

typedef int myfirst; 
typedef int mysecond; 
//typedef std::pair<myfirst, mysecond> mykey;
typedef std::pair<int, int> mykey;
typedef double mydata;
typedef std::pair<mykey, mydata> userdatatype ;



// https://acrocontext.wordpress.com/2014/01/30/c-hash-combine-example-for-hash-function-in-unordered_map/
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


#ifdef MYHASH

template<class T> class MyHash;
template<>
struct MyHash<mykey>
{
	size_t operator()(mykey const& v) const
    {
		myfirst f = v.first;
		mysecond s = v.second;
		size_t res = 0;
		hash_combine(res, f);	
		hash_combine(res, s);
		return res;  
	}
};	

#else

// http://stackoverflow.com/questions/32685540/c-unordered-map-with-pair-as-key-not-compiling
// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
namespace std
{
	template<>
	struct hash<mykey>
	{
		size_t operator()(mykey const& v) const
	    {
			// ... hash function here ...
			myfirst f = v.first;
			mysecond s = v.second;
			//auto h1 = hash_fn(f);
			//auto h2 = hash_fn(s);
			size_t res = 0;
			hash_combine(res, f);	
			hash_combine(res, s);
	        // Mainly for demonstration purposes, i.e. works but is overly simple
			// In the real world, use sth. like boost.hash_combine
			//res = h1 ^ h2;

			return res;  
		}
	};	
}
#endif

 


//no colision
template<typename T>
unsigned int testinsert0(T &m, const unsigned int min, const unsigned int max, const unsigned int minserts, std::vector<userdatatype> &v){


	M_DebugLog("BEGIN: testinsert0" + c2s( typeid(m).name()));
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, minserts+max);
	
	for(unsigned int i=0;i<minserts;++i){
		mykey   key = std::make_pair(dist(mt),dist(mt));
		mydata val = dist(mt); 
		userdatatype value = std::make_pair(key, val);
		v.push_back(value);
	}

	auto start = std::chrono::system_clock::now();
	for(unsigned int i=0;i<minserts;++i)
		m.insert(v[i]);	
	auto end = std::chrono::system_clock::now();

	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	M_DebugLog("END: testinsert0" + c2s( typeid(m).name()));
	return static_cast<unsigned int>(elapsed_time);
    
}

//no with colision
template<typename T>
unsigned int testinsert1(T &m, const unsigned int min, const unsigned int max, const unsigned int minserts, std::vector<userdatatype> &v){

	M_DebugLog("BEGIN: testinsert1" + c2s( typeid(m).name()));
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

	for(unsigned int i=0;i<minserts;++i){
		mykey   key = std::make_pair(dist(mt),dist(mt));
		mydata val = dist(mt); 
		userdatatype value = std::make_pair(key, val);
		v.push_back(value);
	}
	
	auto start = std::chrono::system_clock::now();
	for(unsigned int i=0;i<minserts;++i)
		m.insert(v[i]);
	auto end = std::chrono::system_clock::now();

	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	M_DebugLog("END: testinsert1" + c2s( typeid(m).name()));
	return static_cast<unsigned int>(elapsed_time);
    
}

//seq
template<typename T>
unsigned int testinsert2(T &m, const unsigned int min, const unsigned int max, const unsigned int minserts, std::vector<userdatatype> &v){

	M_DebugLog("BEGIN: testinsert2" + c2s( typeid(m).name()));
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
	
	for(unsigned int i=0;i<minserts;++i){
		mykey   key = std::make_pair(i,i);
		mydata val = i; 
		userdatatype value = std::make_pair(key, val);
		v.push_back(value);
	}

	auto start = std::chrono::system_clock::now();
	for(unsigned int i=0;i<minserts;++i)
		m.insert(v[i]);
	auto end = std::chrono::system_clock::now();

	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	M_DebugLog("END: testinsert2" + c2s( typeid(m).name()));
	return static_cast<unsigned int>(elapsed_time);
    
}

//same
template<typename T>
unsigned int testinsert3(T &m, const unsigned int min, const unsigned int max, const unsigned int minserts, std::vector<userdatatype> &v){

	M_DebugLog("BEGIN: testinsert3" + c2s( typeid(m).name()));
	for(unsigned int i=0;i<minserts;++i){
		mykey   key = std::make_pair(0,0);
		mydata val = 0; 
		userdatatype value = std::make_pair(key, val);
		v.push_back(value);
	}

	auto start = std::chrono::system_clock::now();
	for(unsigned int i=0;i<minserts;++i)
		m.insert(v[i]);
	auto end = std::chrono::system_clock::now();

	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	M_DebugLog("END: testinsert3" + c2s( typeid(m).name()));
	return static_cast<unsigned int>(elapsed_time);
}

/////////////////////////////////////////////////////////////////////////////////////

template<typename T>
unsigned int testfind0(const T &m, const std::vector<userdatatype> &v)  {

	M_DebugLog("BEGIN: testfind0" + c2s( typeid(m).name()));
	auto start = std::chrono::system_clock::now();
	for(unsigned int i=0; i<v.size(); ++i){
		if (m.end() == m.find(v[i].first)){
//			std::cout << "Err: " << v[i].first << std::endl;
			std::cout << "Err: " << typeid(m).name() << std::endl;	
//			std::cout << typeid(m).name() << std::endl;
			exit(-1);
		}
	}
	auto end = std::chrono::system_clock::now();

	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	M_DebugLog("END: testfind0" + c2s( typeid(m).name()));
	return static_cast<unsigned int>(elapsed_time);
}


template<typename T>
unsigned int testfind1(const T &m, const std::vector<userdatatype> &v)  {

	M_DebugLog("BEGIN: testfind1" + c2s( typeid(m).name()));
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, v.size()-1);

	auto start = std::chrono::system_clock::now();
	for(unsigned int i=0; i<v.size(); ++i){
		int idx = dist(mt);
		if (m.end() == m.find(v[idx].first)){
			//std::cout << "Err: " << v[idx].first << std::endl;
			std::cout << "Err: " << typeid(m).name() << std::endl;	
			exit(-1);
		}
	}
	auto end = std::chrono::system_clock::now();

	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	M_DebugLog("END: testfind1" + c2s( typeid(m).name()));
	return static_cast<unsigned int>(elapsed_time);
}


#endif //TEST_H_