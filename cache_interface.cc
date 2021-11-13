#include "cache_interface.hpp"

#include <iostream> 

int slow_get_page(int key) { return key; }

int main() {
	
	Caches::LRUCache<int, int> lru{3};
	for (int i = 0; i < 6; i++) {
		std::cout << lru.lookup_update(i%3, slow_get_page) << std::endl;
	}
	
	return 0;
}