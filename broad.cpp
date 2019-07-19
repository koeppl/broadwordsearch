#include <iostream>
#include <cstdlib>
#include "/scripts/code/dcheck.hpp"
#include <sdsl/bit_vectors.hpp>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <celero/Celero.h>

using namespace std;
using namespace google;
// using namespace sdsl;


//! returns the most significant bit
constexpr int most_significant_bit(const uint64_t& x) {
    return x == 0 ? -1 : (sizeof(uint64_t)*8-1) - __builtin_clzll(x);
}


size_t naivsearch(const unsigned char*const arr, const size_t cLength, const unsigned char pattern) {
	DVLOG(3) << "NAIV";

	for(size_t i = 0; i < cLength; ++i) {
		if(arr[i] == pattern) {
			return i;
		}
	}
	return -1ULL;
}

size_t naivsearch(const sdsl::int_vector<>& arr, const uint64_t pattern) {
	DVLOG(3) << "NAIV";

	for(size_t i = 0; i < arr.size(); ++i) {
		if(arr[i] == pattern) {
			return i;
		}
	}
	return -1ULL;
}

/**
 * We follow Knuth's book "Bitwise Tricks and Techniques", Page 19
 * lowestbitmask and highestbitmask are there defined as l and h
 * The difference is that our bitmasks are not byte-aligned, but `bitwidth` aligned.
 */


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
size_t broadsearch_shift(const uint64_t*const arr, const size_t cLength, const uint8_t cBitlength, const uint64_t pattern, size_t answer) {
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

/**
 * Scans the array by reading a bit chunk that is a multiple of the bitwidth of the pattern but at most 64 bit,
 * and matches the read bit chunk with the pattern broadcasted to an integer of the same bit size.
 * This broadcastet pattern is used for the entire match. However, reading the bit chunks of the array can be slow if the pattern bit width
 * is not a multiple of eight (then the access is not byte-aligned).
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

	    const size_t barr = sdsl::bits::read_int_and_move(arr, offset, wordpackedels*cBitlength);

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
	m_arr = sdsl::int_vector<>(m_length, 0, m_bitlength);

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
	
    const sdsl::int_vector<>& array() const {
	return m_arr;
    }

   private:
    sdsl::int_vector<> m_arr;
    const size_t m_length;
    const uint8_t m_bitlength;
};

template<int m_bitlength>
class ArrayFixture : public celero::TestFixture
{
public:
    ArrayFixture()
      : m_instance_length(std::min<size_t>(9, m_bitlength-1))
      , m_problemspace(m_instance_length,0)
      , m_instances( new ArrayInstance*[m_instance_length])
    
    {
        for(size_t i = 0; i < m_instance_length; i++)
        {
	   const size_t length = 2ULL<<i; 
	   m_problemspace[i] = {static_cast<int64_t>(i)};
	   m_instances[i] = new ArrayInstance(length, m_bitlength);
        }
    }


   virtual void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
      m_current_instance = experimentValue.Value;
      DCHECK_GE(m_instance_length, 0);
      DCHECK_LT(m_current_instance, static_cast<uint64_t>(m_instance_length));
   }
   virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override
   {
      return m_problemspace;
   }
   size_t instance_length() const {
      return m_instance_length;
   }

   const ArrayInstance& instance() const {
      return *m_instances[m_current_instance];
   }

   ~ArrayFixture() {
      for(size_t i = 0; i < m_instance_length; ++i) {
	delete m_instances[i];
      }
      delete [] m_instances;
   }

private:
   const size_t m_instance_length;

   std::vector<celero::TestFixture::ExperimentValue> m_problemspace;
   ArrayInstance**const m_instances = nullptr;

   size_t m_current_instance = 0;
};


TEST(BroadWord, Match) { 
   ArrayFixture<13> fixture;
   for(size_t i = 0; i < fixture.instance_length(); ++i) {
      fixture.setUp(i);
      const sdsl::int_vector<>& arr = fixture.instance().array();  
      for(size_t iRound = 0; iRound < arr.size(); ++iRound)   
      {  
	 const uint64_t pattern = arr[iRound];   
	 const size_t nret = naivsearch(arr, pattern);  
	 ASSERT_EQ(iRound, nret) << "Naive failed";  
	 const size_t bret = broadsearch(arr.data(), arr.size(), fixture.instance().bitlength(), pattern);  
	 ASSERT_EQ(iRound, bret) << "Broad failed";  
	 const size_t bqret = broadsearch_shift(arr.data(), arr.size(), fixture.instance().bitlength(), pattern, iRound);  
	 ASSERT_EQ(iRound, bqret) << "Shift failed";  
      }  
   }
}

TEST(BroadWord, LongTest) { 
   for(size_t reps = 0; reps < 5; ++reps) {
      for(size_t cBitlength = 1; cBitlength < 63; ++cBitlength) {
	 for(size_t cLength = 2; cLength < std::min(100ULL, 1ULL<<cBitlength); ++cLength) {
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
	       DVLOG(3) << i << " -> " << ((size_t)arr[i]) << " ";
	    }
	    for(size_t iRound = 0; iRound < cLength; ++iRound) {
	       const uint64_t pattern = arr[iRound]; 
	       DVLOG(3) << " == Pattern = " << ((size_t)pattern);
	       const size_t nret = naivsearch(arr, pattern);
	       ASSERT_EQ(nret, iRound);
	       const size_t bret = broadsearch(arr.data(), cLength, cBitlength, pattern);
	       ASSERT_EQ(iRound, bret);
	       const size_t bqret = broadsearch_shift(arr.data(), cLength, cBitlength, pattern, nret);
	       ASSERT_EQ(iRound, bqret);
	    }
	    for(size_t iRound = 0; iRound < cLength; ++iRound) {
		  const uint64_t pattern = rand() % (1ULL<<cBitlength);
		  DVLOG(3) << " == Pattern = " << ((size_t)pattern);
		  const size_t nret = naivsearch(arr, pattern);
		  const size_t bret = broadsearch(arr.data(), cLength, cBitlength, pattern);
		  ASSERT_EQ(nret, bret);
		  const size_t bqret = broadsearch_shift(arr.data(), cLength, cBitlength, pattern, nret);
		  ASSERT_EQ(nret, bqret);
	    }
	 }
      }
   }
}



#define GEN_BENCHMARK(BIT)  \
BASELINE_F(Bit_##BIT, Naiv, ArrayFixture<BIT>, 30, 50) {   \
    const sdsl::int_vector<>& arr = this->instance().array();   \
    for(size_t iRound = 0; iRound < arr.size(); ++iRound)    \
    {   \
	const uint64_t pattern = arr[iRound];    \
 	const size_t nret = naivsearch(arr, pattern);   \
	CHECK_EQ(iRound, nret) << "Naive failed";   \
    }   \
}   \
BENCHMARK_F(Bit_##BIT, Shift, ArrayFixture<BIT>, 30, 50) {   \
    const sdsl::int_vector<>& arr = this->instance().array();   \
    for(size_t iRound = 0; iRound < arr.size(); ++iRound)    \
    {   \
	const uint64_t pattern = arr[iRound];    \
	const size_t bret = broadsearch_shift(arr.data(), arr.size(), this->instance().bitlength(), pattern, iRound);   \
	CHECK_EQ(iRound, bret) << "Shift failed";   \
    }   \
}   \
BENCHMARK_F(Bit_##BIT, Broad, ArrayFixture<BIT>, 30, 50) {   \
    const sdsl::int_vector<>& arr = this->instance().array();   \
    for(size_t iRound = 0; iRound < arr.size(); ++iRound)    \
    {   \
	const uint64_t pattern = arr[iRound];    \
	const size_t bret = broadsearch(arr.data(), arr.size(), this->instance().bitlength(), pattern);   \
	CHECK_EQ(iRound, bret) << "Broad failed";   \
    }   \
}   \


GEN_BENCHMARK(2)
GEN_BENCHMARK(3)
GEN_BENCHMARK(4)
GEN_BENCHMARK(7)
GEN_BENCHMARK(8)

GEN_BENCHMARK(13)
GEN_BENCHMARK(16)
GEN_BENCHMARK(31)
GEN_BENCHMARK(32)


// CELERO_MAIN

int main(int argc, char **argv) {
     ::testing::InitGoogleTest(&argc, argv);
       return RUN_ALL_TESTS();
}

