// MapEvaluation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <unordered_map>
#include <chrono>
#include <random>
#include <iostream>
#include <utility>      // std::pair
#include "spp_utils.h"
#include "sparsepp.h"


template<typename T>
int test0(T &m, const int min, const int max, const int minserts){


	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, minserts+max);
	
	auto start = std::chrono::system_clock::now();
	for(auto i=0;i<minserts;++i)
		m.insert(std::make_pair(dist(mt),dist(mt)));
	auto end = std::chrono::system_clock::now();

	int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	return elapsed_time;
    
}

template<typename T>
int test1(T &m, const int min, const int max, const int minserts){


	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
	
	auto start = std::chrono::system_clock::now();
	for(auto i=0;i<minserts;++i)
		m.insert(std::make_pair(dist(mt),dist(mt)));
	auto end = std::chrono::system_clock::now();

	int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	return elapsed_time;
    
}


template<typename T>
int test2(T &m, const int min, const int max, const int minserts){

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
	
	auto start = std::chrono::system_clock::now();
	for(auto i=0;i<minserts;++i)
		m.insert(std::make_pair(i,i));
	auto end = std::chrono::system_clock::now();

	int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	return elapsed_time;
    
}


template<typename T>
int test3(T &m, const int min, const int max, const int minserts){

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
	
	auto start = std::chrono::system_clock::now();
	for(auto i=0;i<minserts;++i)
		m.insert(std::make_pair(0,0));
	auto end = std::chrono::system_clock::now();

	int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
	return elapsed_time;
    
}



int _tmain(int argc, _TCHAR* argv[])
{
	const int maxinserts = 2000000;
	const int min =1, max= 100000; 
	std::unordered_map<int, int> _umap;
	std::map<int,int>			 _map;	
	SPP_NAMESPACE::sparse_hash_map<int,int> _gmap;
/*
	test0: map 37716 ms.
	test0: umap 45362 ms.
	test0: gmap 14668 ms.

	test1: map 35126 ms.
	test1: umap 30068 ms.
	test1: gmap 6937 ms.
	
	test2: map 32512 ms.
	test2: umap 28378 ms.
	test2: gmap 6866 ms.
	
	test3: map 31314 ms.
	test3: umap 26168 ms.
	test3: gmap 4286 ms.
*/


	auto t1 = test0<decltype(_map)> ( _map, min, max, maxinserts) ;	
	auto t2 = test0<decltype(_umap)>(_umap, min, max, maxinserts) ;
	auto t3 = test0<decltype(_gmap)>(_gmap, min, max, maxinserts) ;
	
	std::cout << "test0: map "  << t1 << " ms." << std::endl;
	std::cout << "test0: umap " << t2 << " ms." << std::endl;
	std::cout << "test0: gmap " << t3 << " ms." << std::endl;
	

	t1 = test1<decltype(_map)> ( _map, min, max, maxinserts) ;	
	t2 = test1<decltype(_umap)>(_umap, min, max, maxinserts) ;
	t3 = test1<decltype(_gmap)>(_gmap, min, max, maxinserts) ;

	std::cout << "test1: map "  << t1 << " ms." << std::endl;
	std::cout << "test1: umap " << t2 << " ms." << std::endl;
	std::cout << "test1: gmap " << t3 << " ms." << std::endl;


	t1 = test2<decltype(_map)> ( _map, min, max, maxinserts) ;	
	t2 = test2<decltype(_umap)>(_umap, min, max, maxinserts) ;
	t3 = test2<decltype(_gmap)>(_gmap, min, max, maxinserts) ;

	std::cout << "test2: map "  << t1 << " ms." << std::endl;
	std::cout << "test2: umap " << t2 << " ms." << std::endl;
	std::cout << "test2: gmap " << t3 << " ms." << std::endl;

	t1 = test3<decltype(_map)> ( _map, min, max, maxinserts) ;	
	t2 = test3<decltype(_umap)>(_umap, min, max, maxinserts) ;
	t3 = test3<decltype(_gmap)>(_gmap, min, max, maxinserts) ;

	std::cout << "test3: map "  << t1 << " ms." << std::endl;
	std::cout << "test3: umap " << t2 << " ms." << std::endl;
	std::cout << "test3: gmap " << t3 << " ms." << std::endl;


	return 0;
}

