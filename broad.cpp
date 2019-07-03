#include <iostream>
#include <cstdlib>
#include "/scripts/code/dcheck.hpp"
#include <sdsl/bit_vectors.hpp>

using namespace std;
// using namespace sdsl;

// https://graphics.stanford.edu/~seander/bithacks.html
// Determine if a word has a zero byte
// Determine if a word has a byte equal to n
//
//
//


//! returns the most significant bit
constexpr int most_significant_bit(const uint64_t& x) {
    return x == 0 ? -1 : (sizeof(uint64_t)*8-1) - __builtin_clzll(x);
}


size_t naivsearch(const unsigned char*const arr, const size_t cLength, const unsigned char pattern) {
	std::cout << "NAIV" << std::endl;

	for(size_t i = 0; i < cLength; ++i) {
		if(arr[i] == pattern) {
			return i;
		}
	}
	return -1ULL;
}

size_t naivsearch(const sdsl::int_vector<>& arr, const unsigned char pattern) {
	std::cout << "NAIV" << std::endl;

	for(size_t i = 0; i < arr.size(); ++i) {
		if(arr[i] == pattern) {
			return i;
		}
	}
	return -1ULL;
}


constexpr uint64_t lowestbitmask(uint_fast8_t bitwidth) {
	uint64_t ret = 0;
	for(size_t i = 0; i < 64; ++i) {
		if(i % bitwidth == 0) ret |= (1ULL<<i);
	}
	return ret;
}
constexpr uint64_t highestbitmask(uint_fast8_t bitwidth) {
	uint64_t ret = 0;
	for(size_t i = 0; i < 64; ++i) {
		if((i+1) % bitwidth == 0) ret |= (1ULL<<i);
	}
	return ret;
}
constexpr uint64_t lowestbitmaskarr[]  = { 
	0,
	lowestbitmask(1),
	lowestbitmask(2),
	lowestbitmask(3), 
	lowestbitmask(4),
	lowestbitmask(5), 
	lowestbitmask(6),
	lowestbitmask(7),
	lowestbitmask(8) 
};
constexpr uint64_t highestbitmaskarr[] = { 
	0,
	highestbitmask(1),
	highestbitmask(2),
	highestbitmask(3), 
	highestbitmask(4),
	highestbitmask(5), 
	highestbitmask(6),
	highestbitmask(7),
	highestbitmask(8) 
};


size_t broadsearch(const uint64_t*const arr, const size_t cLength, const size_t cBitlength, const unsigned char pattern) {
	std::cout << "BROADWORD" << std::endl;

	const size_t bpattern = lowestbitmaskarr[cBitlength] * pattern;

	for(size_t i = 0; i < (cLength+cBitlength-1)/cBitlength; ++i) {

		const size_t barr = reinterpret_cast<const size_t*>(arr)[i];
		const size_t chunk = barr ^ bpattern; // now search for the 0 byte in chunk
	
		// for(size_t j = 0; j < 8; ++j) {
		// 	if( reinterpret_cast<const unsigned char*>(&chunk)[j] == 0) {
		//  	std::cout << "Found: " << (j+i*8) << std::endl;
		// 	}
		// }

		const size_t test = ((chunk) - lowestbitmaskarr[cBitlength]) & (~chunk) & highestbitmaskarr[cBitlength];
		// const size_t test = ((chunk) - 0x0101010101010101ULL) & (~chunk) & 0x8080808080808080ULL;
		if(test != 0) {
			std::cout << "Byte : " << i << " Pos " << most_significant_bit(test & (-test)) << std::endl;
			std::cout << "Found: " << (i*cBitlength + (most_significant_bit(test & (-test))+1-cBitlength)/cBitlength ) << std::endl;
			const size_t ret = (i*cBitlength + (most_significant_bit(test & (-test))+1-cBitlength)/cBitlength );
			return (ret < cLength) ? ret : -1ULL;
		}

	}
	return -1ULL;
}

int main(int argc , char *argv[]) {
	while(1) {
		constexpr size_t cBitlength = 7;
		constexpr size_t cLength = 13;
		sdsl::int_vector<> arr(cLength, 0, cBitlength);

		for(size_t i = 0; i < cLength; ++i) {
			arr[i] = rand() % (1ULL<<cBitlength);
		}

		for(size_t i = 0; i < cLength; ++i) {
			std::cout << i << " -> " << ((size_t)arr[i]) << " " << std::endl;
		}
		for(size_t iRound = 0; iRound < cLength; ++iRound) {
			const unsigned char pattern = arr[iRound]; //strtoul(argv[1],NULL,10);
			std::cout << " == Pattern = " << ((size_t)pattern) << std::endl;
			const size_t nret = naivsearch(arr, pattern);
			const size_t bret = broadsearch(arr.data(), cLength, cBitlength, pattern);
			DCHECK_EQ(nret, bret);
			// for(size_t i = 0; i < nret.size(); ++i) {
			// 	DCHECK_EQ(nret[i], bret[i]);
			// }
		}

	}


	while(1) {
		constexpr size_t cLength = 13;
		unsigned char arr[cLength];

		for(size_t i = 0; i < cLength; ++i) {
			arr[i] = rand() % 254;
		}

		for(size_t i = 0; i < cLength; ++i) {
			std::cout << i << " -> " << ((size_t)arr[i]) << " " << std::endl;
		}
		for(size_t iRound = 0; iRound < cLength; ++iRound) {
			const unsigned char pattern = arr[iRound]; //strtoul(argv[1],NULL,10);
			std::cout << " == Pattern = " << ((size_t)pattern) << std::endl;
			const size_t nret = naivsearch(arr, cLength, pattern);
			const size_t bret = broadsearch((uint64_t*)arr, cLength, 8, pattern);
			DCHECK_EQ(nret, bret);
			// for(size_t i = 0; i < nret.size(); ++i) {
			// 	DCHECK_EQ(nret[i], bret[i]);
			// }
		}

	}

	return 0;
}
