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
	lowestbitmask(8),
	lowestbitmask(9),
	lowestbitmask(10),
	lowestbitmask(11),
	lowestbitmask(12),
	lowestbitmask(13),
	lowestbitmask(14),
	lowestbitmask(15),
	lowestbitmask(16),
	lowestbitmask(17),
	lowestbitmask(18),
	lowestbitmask(19),
	lowestbitmask(20),
	lowestbitmask(21),
	lowestbitmask(22),
	lowestbitmask(23),
	lowestbitmask(24),
	lowestbitmask(25),
	lowestbitmask(26),
	lowestbitmask(27),
	lowestbitmask(28),
	lowestbitmask(29),
	lowestbitmask(30),
	lowestbitmask(31),
	lowestbitmask(32),
	lowestbitmask(33),
	lowestbitmask(34),
	lowestbitmask(35),
	lowestbitmask(36),
	lowestbitmask(37),
	lowestbitmask(38),
	lowestbitmask(39),
	lowestbitmask(40),
	lowestbitmask(41),
	lowestbitmask(42),
	lowestbitmask(43),
	lowestbitmask(44),
	lowestbitmask(45),
	lowestbitmask(46),
	lowestbitmask(47),
	lowestbitmask(48),
	lowestbitmask(49),
	lowestbitmask(50),
	lowestbitmask(51),
	lowestbitmask(52),
	lowestbitmask(53),
	lowestbitmask(54),
	lowestbitmask(55),
	lowestbitmask(56),
	lowestbitmask(57),
	lowestbitmask(58),
	lowestbitmask(59),
	lowestbitmask(60),
	lowestbitmask(61),
	lowestbitmask(62),
	lowestbitmask(63)
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
	highestbitmask(8),
	highestbitmask(9),
	highestbitmask(10),
	highestbitmask(11),
	highestbitmask(12),
	highestbitmask(13),
	highestbitmask(14),
	highestbitmask(15),
	highestbitmask(16),
	highestbitmask(17),
	highestbitmask(18),
	highestbitmask(19),
	highestbitmask(20),
	highestbitmask(21),
	highestbitmask(22),
	highestbitmask(23),
	highestbitmask(24),
	highestbitmask(25),
	highestbitmask(26),
	highestbitmask(27),
	highestbitmask(28),
	highestbitmask(29),
	highestbitmask(30),
	highestbitmask(31),
	highestbitmask(32),
	highestbitmask(33),
	highestbitmask(34),
	highestbitmask(35),
	highestbitmask(36),
	highestbitmask(37),
	highestbitmask(38),
	highestbitmask(39),
	highestbitmask(40),
	highestbitmask(41),
	highestbitmask(42),
	highestbitmask(43),
	highestbitmask(44),
	highestbitmask(45),
	highestbitmask(46),
	highestbitmask(47),
	highestbitmask(48),
	highestbitmask(49),
	highestbitmask(50),
	highestbitmask(51),
	highestbitmask(52),
	highestbitmask(53),
	highestbitmask(54),
	highestbitmask(55),
	highestbitmask(56),
	highestbitmask(57),
	highestbitmask(58),
	highestbitmask(59),
	highestbitmask(60),
	highestbitmask(61),
	highestbitmask(62),
	highestbitmask(63)
};

size_t broadsearch_nonquantized(const uint64_t*const arr, const size_t cLength, const size_t cBitlength, const unsigned char pattern, size_t answer) {
    DCHECK_LE(cBitlength,63);
    DCHECK_GT(cBitlength,0);
    std::cout << "BROADWORD NONQUANT" << std::endl;


    const uint8_t wordpackedels = (sizeof(uint64_t)*8/cBitlength); // number of elements fitting into 64 bits
    uint8_t remainder = sizeof(uint64_t)*8 - wordpackedels*cBitlength; // number of bits of the element wrapping around a 64 bit block boundary, left hand side / highest bits of the current block `barr`
    uint8_t unchecked = 0; // unchecked: number of bits of the previous remainder that need to be checked. These are the first bits of the current block `barr`
    for(size_t i = 0; i < (cLength+wordpackedels-1)/wordpackedels; ++i) {

	const uint64_t bpattern = (lowestbitmaskarr[cBitlength] << unchecked) * pattern;
	const uint64_t barr = reinterpret_cast<const uint64_t*>(arr)[i];
	const uint64_t chunk = barr ^ bpattern; // now search for the 0 byte in chunk
	const uint64_t low = (lowestbitmaskarr[cBitlength] << unchecked); 
	uint64_t high = (highestbitmaskarr[cBitlength] << unchecked);

	const uint64_t test = ((chunk) - low) & (~chunk) & high;
	if(test != 0) {
	    const uint8_t matchposition = most_significant_bit(test & (-test));
	    size_t ret = ((sizeof(uint64_t)*8*i/cBitlength) + (matchposition +1-cBitlength-unchecked)/cBitlength );
	    if(unchecked > 0) ++ret;

	    if(ret < cLength) {
		std::cout << "Byte : " << i << " Pos " << most_significant_bit(test & (-test)) << std::endl;
		std::cout << "Found at : " << ret << std::endl;

		DCHECK_EQ(ret, answer);
		return ret;
	    }
	}

	DCHECK_LT(remainder, cBitlength);
	unchecked = cBitlength-remainder;
	if(unchecked == cBitlength) { unchecked = 0;}
	const uint8_t remainingbits = sizeof(uint64_t)*8 - unchecked;
	remainder = remainingbits - (remainingbits/cBitlength)*cBitlength;
    }
    uint8_t rem = sizeof(uint64_t)*8 - wordpackedels*cBitlength;
    for(size_t i = 0; i < (cLength+wordpackedels-1)/wordpackedels; ++i) {
	const uint64_t el = sdsl::bits::read_int(arr+i, 64-rem, cBitlength);
	rem = (64 - (cBitlength - rem)) % cBitlength;
	if(el == pattern) {
	    size_t ret = (sizeof(uint64_t)*8*(i+1)/cBitlength);
	    if(ret < cLength) {
		DCHECK_EQ(ret, answer);
		return ret;
	    } else {
		DCHECK_EQ(-1ULL, answer);
		return -1ULL;
	    }
	    //return (ret < cLength) ? ret : -1ULL;
	}

    }
    DCHECK_EQ(-1ULL, answer);
    return -1ULL;
}


// size_t broadsearch_nonquantized(const uint64_t*const arr, const size_t cLength, const size_t cBitlength, const unsigned char pattern, size_t answer) {
//     DCHECK_LE(cBitlength,63);
//     DCHECK_GT(cBitlength,0);
//     std::cout << "BROADWORD NONQUANT" << std::endl;
//
//
//     const uint8_t wordpackedels = (sizeof(uint64_t)*8/cBitlength); // number of elements fitting into 64 bits
//     uint8_t remainder = sizeof(uint64_t)*8 - wordpackedels*cBitlength; // number of bits of the element wrapping around a 64 bit block boundary, left hand side / highest bits of the current block `barr`
//     uint8_t unchecked = 0; // unchecked: number of bits of the previous remainder that need to be checked. These are the first bits of the current block `barr`
//     bool remainder_matches = false;
//     for(size_t i = 0; i < (cLength+wordpackedels-1)/wordpackedels; ++i) {
//
// 	const uint64_t bpattern = ((lowestbitmaskarr[cBitlength] << unchecked) * pattern) | (pattern >> (cBitlength-unchecked));
// 	const uint64_t barr = reinterpret_cast<const uint64_t*>(arr)[i];
// 	const uint64_t chunk = barr ^ bpattern; // now search for the 0 byte in chunk
// 	const uint64_t low = (lowestbitmaskarr[cBitlength] << unchecked) | 1ULL;
// 	uint64_t high = (highestbitmaskarr[cBitlength] << unchecked) | (1ULL<<63);
// 	if(unchecked > 0) high |= (1ULL<<(unchecked-1));
//
//
// 	uint64_t test = ((chunk) - low) & (~chunk) & high;
// 	if(test != 0) {
// 	    uint8_t matchposition = most_significant_bit(test & (-test));
// 	    if(matchposition >= wordpackedels*cBitlength) { // matching the remainder
// 		remainder_matches = true;
// 	    }
// 	    else {
// 		if(matchposition < unchecked) {
// 		    if(remainder_matches == true) {
// 			const size_t ret = (sizeof(uint64_t)*8*i/cBitlength);
// 			DCHECK_EQ(ret, answer);
// 			return (ret < cLength) ? ret : -1ULL;
// 		    }
// 		} 
// 	    }
// 	} else {
// 		remainder_matches = false;
// 	}
// 	test &= ((-1ULL)<<unchecked);
// 	if(test != 0) {
// 	    uint8_t matchposition = most_significant_bit(test & (-test));
// 	    if(matchposition < sizeof(uint64_t)*8 + unchecked - remainder) { // matching not the remainder
// 		remainder_matches = false;
//
// 		size_t ret = ((sizeof(uint64_t)*8*i/cBitlength) + (most_significant_bit(test & (-test))+1-cBitlength-unchecked)/cBitlength );
// 		if(unchecked > 0) ++ret;
//
// 		std::cout << "Byte : " << i << " Pos " << most_significant_bit(test & (-test)) << std::endl;
// 		std::cout << "Found at : " << ret << std::endl;
//
// 		DCHECK_EQ(ret, answer);
// 		return (ret < cLength) ? ret : -1ULL;
// 	    }
// 	}
//
// 	unchecked = cBitlength-remainder;
// 	const uint8_t remainingbits = sizeof(uint64_t)*8 - unchecked;
// 	remainder = remainingbits - (remainingbits/cBitlength)*cBitlength;
//
//     }
//     DCHECK_EQ(-1ULL, answer);
//     return -1ULL;
// }


size_t broadsearch_quantized(const uint64_t*const arr, const size_t cLength, const size_t cBitlength, const unsigned char pattern) {
    DCHECK_LE(cBitlength,63);
    DCHECK_EQ(64 % cBitlength, 0); // 64 must be divisible by cBitlength
    DCHECK_GT(cBitlength,0);
    std::cout << "BROADWORD QUANT" << std::endl;

    const size_t bpattern = lowestbitmaskarr[cBitlength] * pattern;

    const uint8_t wordpackedels = (sizeof(uint64_t)*8/cBitlength); // number of elements fitting into 64 bits
    for(size_t i = 0; i < (cLength+wordpackedels-1)/wordpackedels; ++i) {

	const size_t barr = reinterpret_cast<const uint64_t*>(arr)[i];
	const size_t chunk = barr ^ bpattern; // now search for the 0 byte in chunk

	const size_t test = ((chunk) - lowestbitmaskarr[cBitlength]) & (~chunk) & highestbitmaskarr[cBitlength];
	if(test != 0) {
	    const size_t ret = (i*wordpackedels + (most_significant_bit(test & (-test))+1-cBitlength)/cBitlength );

	    std::cout << "Byte : " << i << " Pos " << most_significant_bit(test & (-test)) << std::endl;
	    std::cout << "Found at : " << ret << std::endl;

	    return (ret < cLength) ? ret : -1ULL;
	}

    }
    return -1ULL;
}

size_t broadsearch(const uint64_t* arr, const size_t cLength, const size_t cBitlength, const unsigned char pattern) {
    DCHECK_LE(cBitlength,63);
    DCHECK_GT(cBitlength,0);
    std::cout << "BROADWORD" << std::endl;

	const size_t bpattern = lowestbitmaskarr[cBitlength] * pattern;

	uint8_t offset = 0;
	const uint8_t wordpackedels = (sizeof(uint64_t)*8/cBitlength); // number of elements fitting into 64 bits
	for(size_t i = 0; i < (cLength+wordpackedels-1)/wordpackedels; ++i) {

	    const size_t barr = sdsl::bits::read_int_and_move(arr, offset, wordpackedels*cBitlength);

	    // const size_t barr = reinterpret_cast<const size_t*>(arr)[i];
	    const size_t chunk = barr ^ bpattern; // now search for the 0 byte in chunk
	
		// for(size_t j = 0; j < 8; ++j) {
		// 	if( reinterpret_cast<const unsigned char*>(&chunk)[j] == 0) {
		//  	std::cout << "Found: " << (j+i*8) << std::endl;
		// 	}
		// }

	    const size_t test = ((chunk) - lowestbitmaskarr[cBitlength]) & (~chunk) & highestbitmaskarr[cBitlength];
	    // const size_t test = ((chunk) - 0x0101010101010101ULL) & (~chunk) & 0x8080808080808080ULL;
	    if(test != 0) {
		const size_t ret = (i*wordpackedels + (most_significant_bit(test & (-test))+1-cBitlength)/cBitlength );

		std::cout << "Byte : " << i << " Pos " << most_significant_bit(test & (-test)) << std::endl;
		std::cout << "Found at : " << ret << std::endl;

		return (ret < cLength) ? ret : -1ULL;
	    }

	}
	return -1ULL;
}

int main(int argc , char *argv[]) {

    while(1) 
    {
	for(size_t cBitlength = 1; cBitlength < 63; ++cBitlength) 
	{
    for(size_t cLength = 2; cLength < std::min(200ULL, 1ULL<<cBitlength); ++cLength) 
    {
    // size_t cLength = 30;
    // size_t cBitlength = 5;
    sdsl::int_vector<> arr(cLength, 0, cBitlength);

    for(size_t i = 0; i < cLength; ++i) {
	while(1) {
	    arr[i] = rand() % (1ULL<<cBitlength);
	    bool duplicate = false;
	    for(size_t j = 0; j < i; ++j) {
		if(arr[i] == arr[j]) {duplicate = true;}
	    }
	    if(!duplicate) break;
	}
    }

    for(size_t i = 0; i < cLength; ++i) {
	std::cout << i << " -> " << ((size_t)arr[i]) << " " << std::endl;
    }
    for(size_t iRound = 0; iRound < cLength; ++iRound) 
    {
    //    size_t iRound = 12;
	const unsigned char pattern = arr[iRound]; //strtoul(argv[1],NULL,10);
	std::cout << " == Pattern = " << ((size_t)pattern) << std::endl;
	const size_t nret = naivsearch(arr, pattern);
	const size_t bret = broadsearch_nonquantized(arr.data(), cLength, cBitlength, pattern, nret);
	DCHECK_EQ(nret, bret);
    }
}
}
}



    while(1) {
	for(size_t cBitlength = 1; cBitlength < 63; ++cBitlength) {
	    for(size_t cLength = 2; cLength < 20; ++cLength) {
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
		    if(64 % cBitlength == 0) {
		    // if(cBitlength == 48) {
			const size_t bqret = broadsearch_quantized(arr.data(), cLength, cBitlength, pattern);
			DCHECK_EQ(nret, bqret);
		    }
		    // for(size_t i = 0; i < nret.size(); ++i) {
		    // 	DCHECK_EQ(nret[i], bret[i]);
		    // }
		}
	    }
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



/*
 * __m256i _mm256_sub_epi64 (__m256i a, __m256i b)
 * a - b
 * 
 * __m256i _mm256_xor_si256 (__m256i a, __m256i b)
 * a ^ b  (becomes ^a when b = 111111)
 *
 * __m256i _mm256_andnot_si256 (__m256i a, __m256i b)
 * (^a) & b
 *
 * __m256i _mm256_and_si256 (__m256i a, __m256i b)
 * a & b
 *
 */
