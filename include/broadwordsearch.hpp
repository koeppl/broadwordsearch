/**
 * We follow Knuth's book "Bitwise Tricks and Techniques", Page 19
 * lowestbitmask and highestbitmask are there defined as l and h
 * The difference is that our bitmasks are not byte-aligned, but `bitwidth` aligned.
 */

#include <iostream>
#include <cstdlib>
// #include <sdsl/bit_vectors.hpp>
#include <tudocomp/ds/IntVector.hpp>
#include <tudocomp/util/bits.hpp>
#include <glog/logging.h>

namespace broadwordsearch {

using namespace std;
using namespace google;

//! returns the most significant bit
constexpr int most_significant_bit(const uint64_t& x) {
    return x == 0 ? -1 : (sizeof(uint64_t)*8-1) - __builtin_clzll(x);
}


/**
 * Use the API of tdc::IntVector to search
 */ 
size_t api_search(const tdc::IntVector<tdc::dynamic_t>& arr, const uint64_t pattern) {
	DVLOG(3) << "API";
	for(size_t i = 0; i < arr.size(); ++i) {
		if(arr[i] == pattern) {
			return i;
		}
	}
	return -1ULL;
}

size_t naivsearch(const uint64_t* arr, const size_t cLength, const uint8_t cBitlength, const uint64_t pattern) {
	DVLOG(3) << "NAIV";

       uint8_t offset = 0;

       for(size_t i = 0; i < cLength; ++i) { // needed?
            const uint64_t read_key = tdc::tdc_sdsl::bits_impl<>::read_int_and_move(arr, offset, cBitlength);
	    DCHECK_EQ(read_key, arr[i]);
            if(read_key == pattern) {
                return i;
            }
        }
       return -1ULL;


}



/**
 *  Computes a bit vector of the shape 000100010001...
 *  A block 0001 has the bit-width `bitwidth` (in this example `bitwidth` = 4)
**/
constexpr uint64_t lowestbitmask(uint_fast8_t bitwidth) {
	uint64_t ret = 0;
	for(size_t i = 0; i < 64; ++i) {
		if(i % bitwidth == 0) ret |= (1ULL<<i);
	}
	return ret;
}

/**
 *  Computes a bit vector of the shape 100010001000...
 *  A block 1000 has the bit-width `bitwidth` (in this example `bitwidth` = 4)
**/
constexpr uint64_t highestbitmask(uint_fast8_t bitwidth) {
	uint64_t ret = 0;
	for(size_t i = 0; i < 64; ++i) {
		if((i+1) % bitwidth == 0) ret |= (1ULL<<i);
	}
	return ret;
}

/**
 * h for all possible bit widths (computed at compile time)
 */
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

/**
 * h for all possible bit widths (computed at compile time)
 */
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

/**
 * Scan the array in 64-bit blocks, matching a given pattern by broadcasting it to a broadword and shifting the broadword such that it matches the offset of the 64-bit block of the input array.
 * The shifting is not necessary if the bitwidth of the array divides 64. 
 * Otherwise, we need to match the pattern on the boundaries of the 64-bit blocks, which is done afterwards.
 *
 * If one needs this function for bitwidths = 2 or 4, it could be interesting to look at the AVX2 instruction sets:
 * __m256i _mm256_sub_epi64 (__m256i a, __m256i b) for a - b
 * 
 * __m256i _mm256_xor_si256 (__m256i a, __m256i b) for a ^ b  (this becomes ^a when b = 111111)
 *
 * __m256i _mm256_andnot_si256 (__m256i a, __m256i b) for  (^a) & b
 *
 * __m256i _mm256_and_si256 (__m256i a, __m256i b) for a & b
 *
 */
size_t broadsearch_shift(const uint64_t*const arr, const size_t cLength, const uint8_t cBitlength, const uint64_t pattern) {
   DCHECK(pattern == 0 || most_significant_bit(pattern) <= cBitlength);
    DCHECK_LE(cBitlength,63);
    DCHECK_GT(cBitlength,0);
    DVLOG(3) << "BROADWORD SHIFT";


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
		DVLOG(3) << "Byte : " << i << " Pos " << most_significant_bit(test & (-test));
		DVLOG(3) << "Found at : " << ret;

		// DCHECK_EQ(ret, answer);
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
	const uint64_t el = tdc::tdc_sdsl::bits::read_int(arr+i, 64-rem, cBitlength);
	rem = (64 - (cBitlength - rem)) % cBitlength;
	if(el == pattern) {
	    size_t ret = (sizeof(uint64_t)*8*(i+1)/cBitlength);
	    if(ret < cLength) {
		// DCHECK_EQ(ret, answer);
		return ret;
	    } else {
		// DCHECK_EQ(-1ULL, answer);
		return -1ULL;
	    }
	    //return (ret < cLength) ? ret : -1ULL;
	}

    }
    // DCHECK_EQ(-1ULL, answer);
    return -1ULL;
}

/**
 * Scans the array by reading a bit chunk that is a multiple of the bitwidth of the pattern but at most 64 bit,
 * and matches the read bit chunk with the pattern broadcasted to an integer of the same bit size.
 * This broadcastet pattern is used for the entire match. However, reading the bit chunks of the array can be slow if the pattern bit width
 * is not a multiple of eight (then the access is not byte-aligned).
 *
 * The search works as follows:
 * - create a broadword pattern by bpattern = pattern * l
 * - compute XOR of the read bit chunk with bpattern. If we look at a chunk of length `cBitlength` that is zeroed, then there is a match. Let x be the result of the XOR operation
 * - to obtain the match position, we write test <- h & (x-l) & (^x)  (this is Equation 90 in Knuth's book)
 * - now t contains a 1 where the match is, otherwise 0. It is left to take the most significant bit, and map it to a position.
 */
size_t broadsearch(const uint64_t* arr, const size_t cLength, const uint8_t cBitlength, const uint64_t pattern) {
   DCHECK(pattern == 0 || most_significant_bit(pattern) <= cBitlength);
    DCHECK_LE(cBitlength,63);
    DCHECK_GT(cBitlength,0);
    DVLOG(3) << "BROADWORD";

	const size_t bpattern = lowestbitmaskarr[cBitlength] * pattern;

	uint8_t offset = 0;
	const uint8_t wordpackedels = (sizeof(uint64_t)*8/cBitlength); // number of elements fitting into 64 bits
	for(size_t i = 0; i < (cLength+wordpackedels-1)/wordpackedels; ++i) {

	    const size_t barr = tdc::tdc_sdsl::bits::read_int_and_move(arr, offset, wordpackedels*cBitlength);

	    // const size_t barr = reinterpret_cast<const size_t*>(arr)[i];
	    const size_t chunk = barr ^ bpattern; // now search for the 0 byte in chunk
	
		// for(size_t j = 0; j < 8; ++j) {
		// 	if( reinterpret_cast<const unsigned char*>(&chunk)[j] == 0) {
		//  	DVLOG(3) << "Found: " << (j+i*8);
		// 	}
		// }

	    const size_t test = ((chunk) - lowestbitmaskarr[cBitlength]) & (~chunk) & highestbitmaskarr[cBitlength];
	    // const size_t test = ((chunk) - 0x0101010101010101ULL) & (~chunk) & 0x8080808080808080ULL;
	    if(test != 0) {
		const size_t ret = (i*wordpackedels + (most_significant_bit(test & (-test))+1-cBitlength)/cBitlength );

		DVLOG(3) << "Byte : " << i << " Pos " << most_significant_bit(test & (-test));
		DVLOG(3) << "Found at : " << ret;

		return (ret < cLength) ? ret : -1ULL;
	    }

	}
	return -1ULL;
}

/**
 * Test instance, storing random unique numbers
 */
class ArrayInstance {
   public:

   ArrayInstance(size_t length, uint8_t bitlength) 
      : m_length(std::min<size_t>(length, 1ULL<<bitlength)), m_bitlength(bitlength)
   { 
	m_arr = tdc::IntVector<tdc::dynamic_t>(m_length, 0, m_bitlength);

	for(size_t i = 0; i < m_length; ++i) {
	    while(1) {
		m_arr[i] = rand() % (1ULL<<m_bitlength);
		bool duplicate = false;
		for(size_t j = 0; j < i; ++j) {
		    if(m_arr[i] == m_arr[j]) {duplicate = true;}
		}
		if(!duplicate) break;
	    }
	}
   }

    size_t length() const {
	return m_length;
    }
    uint8_t bitlength() const {
	return m_bitlength;
    }
	
    const tdc::IntVector<tdc::dynamic_t>& array() const {
	return m_arr;
    }

   private:
    tdc::IntVector<tdc::dynamic_t> m_arr;
    const size_t m_length;
    const uint8_t m_bitlength;
};

}//ns
