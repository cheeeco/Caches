#pragma once

#include <list>
#include <unordered_map>
#include <iostream>
#include <functional>

namespace Caches {

template <typename T, typename KeyT = int> 
class AbstractCache {
	
	public:
	
	using F = std::function<T(KeyT)>;
	virtual bool lookup_update(KeyT key, F get_page) {
		auto tmp = get_page(key); // for time analytics of dummy cache
		return 0; // abstract cache is dummy cache
	}
	
	virtual bool full() const { 
		return 0;
	}

};

template <typename T, typename KeyT = int>
class LRUCache: AbstractCache<T, KeyT> {
	
	public:
	
	LRUCache(size_t size) : m_size(size) {}
	
	using F = std::function<T(KeyT)>;
	bool lookup_update(KeyT key, F get_page) {
		auto hit = m_hashtable.find(key);    //hashtable iterator, actually. not ListIt
		if (hit == m_hashtable.end()) {
			if (full()) {
				m_hashtable.erase(m_cache.back());
				m_cache.pop_back();
			} 
			m_cache.push_front(get_page(key));
			m_hashtable[key] = m_cache.begin();
			return false;
		}
		m_cache.splice(m_cache.begin(), m_cache, hit->second);
		return true;
		
	}
	
	bool full() const {
		return (m_cache.size() == m_size); 
	}
	
	private:
	
	size_t m_size;
	std::list<T> m_cache;
	
	using ListIt = typename std::list<T>::iterator;
	std::unordered_map<KeyT, ListIt> m_hashtable;
	
};

} // namespace Caches