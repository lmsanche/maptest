// MapEvaluation.cpp : Defines the entry point for the console application.
//

#include "test.h"


//
//template<unsigned int N>
int testing(const unsigned int n, const unsigned int m, const int min, const int max, const int maxinserts) {

	//std::unordered_map<int, int>	_umap;
	//std::map<int,int>				_map;	
	//spp::sparse_hash_map<int,int>	_gmap;

	std::map<mykey, mydata>				_map;	
#ifdef MYHASH
	std::unordered_map<mykey, mydata, MyHash<mykey>>	_umap;	
	spp::sparse_hash_map<mykey, mydata, MyHash<mykey>>	_gmap;
#else
	std::unordered_map<mykey, mydata>	_umap;	
	spp::sparse_hash_map<mykey, mydata>	_gmap;
#endif


	std::vector<userdatatype> _v1,_v2,_v3;

	//std::pair<BBVA_DATE,BBVA_DATE>, BBVA_DOUBLE>
	_v1.reserve(maxinserts);
	_v2.reserve(maxinserts);
	_v3.reserve(maxinserts);

	unsigned int t1, t2, t3;
	std::string s;


	switch(n){	
	case 0:
		t1 = testinsert0<decltype(_map)> ( _map, min, max, maxinserts, _v1);	
		t2 = testinsert0<decltype(_umap)>(_umap, min, max, maxinserts, _v2);
		t3 = testinsert0<decltype(_gmap)>(_gmap, min, max, maxinserts, _v3);
		s = "test (insert rnd with collision)";
		break;
	case 1:
		t1 = testinsert1<decltype(_map)> ( _map, min, max, maxinserts, _v1);	
		t2 = testinsert1<decltype(_umap)>(_umap, min, max, maxinserts, _v2);
		t3 = testinsert1<decltype(_gmap)>(_gmap, min, max, maxinserts, _v3);
		s = "test (insert rnd wout collision)";
		break;
	case 2:
		t1 = testinsert2<decltype(_map)> ( _map, min, max, maxinserts, _v1);	
		t2 = testinsert2<decltype(_umap)>(_umap, min, max, maxinserts, _v2);
		t3 = testinsert2<decltype(_gmap)>(_gmap, min, max, maxinserts, _v3);
		s = "test (insert sequential        )";
		break;
	case 3:
		t1 = testinsert3<decltype(_map)> ( _map, min, max, maxinserts, _v1);	
		t2 = testinsert3<decltype(_umap)>(_umap, min, max, maxinserts, _v2);
		t3 = testinsert3<decltype(_gmap)>(_gmap, min, max, maxinserts, _v3);
		s = "test (insert same value        )";
		break;
	default:
		t1 = t2 = t3 = 0;
	}
	std::cout << s << "  map " << t1 << " ms." << std::endl;	
	std::cout << s << " umap " << t2 << " ms." << std::endl;
	std::cout << s << " gmap " << t3 << " ms." << std::endl;

	switch(m){	
	case 0:
		t1 = testfind0<decltype(_map)> ( _map, _v1);	
		t2 = testfind0<decltype(_umap)>(_umap, _v2);
		t3 = testfind0<decltype(_gmap)>(_gmap, _v3);
		s = "test (find seq                 )";
		break;		
	case 1:
		t1 = testfind1<decltype(_map)> ( _map, _v1);	
		t2 = testfind1<decltype(_umap)>(_umap, _v2);
		t3 = testfind1<decltype(_gmap)>(_gmap, _v3);		
		s = "test (find rnd                 )";
		break;
		
	default:
		t1 = t2 = t3 = 0;
	}
	std::cout << s << "  map " << t1 << " ms." << std::endl;	
	std::cout << s << " umap " << t2 << " ms." << std::endl;
	std::cout << s << " gmap " << t3 << " ms." << std::endl;	
	
	
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int maxinserts = 200000;
	const int min =1, max= 100000; 

	//const int maxinserts = 20000;
	//const int min =1, max= 10000; 

	for (auto i=0; i<4; ++i){
		testing(i, 0, min, max, maxinserts);
	}
	for (auto i=0; i<3; ++i){
		testing(i, 1, min, max, maxinserts);
	}
	return 0;
}
