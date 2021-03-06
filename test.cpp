#include "broadwordsearch.hpp"
#include <gtest/gtest.h>

using namespace broadwordsearch;

TEST(BroadWord, Match) { 
   ArrayInstance instance(200,13);
   for(size_t i = 0; i < instance.length(); ++i) {
      const tdc::IntVector<tdc::dynamic_t>& arr = instance.array();  
      for(size_t iRound = 0; iRound < arr.size(); ++iRound)   
      {  
	 const uint64_t pattern = arr[iRound];   

	 const size_t aret = api_search(arr, pattern);  
	 ASSERT_EQ(iRound, aret) << "API failed";  
	 const size_t nret = naivsearch(arr.data(), arr.size(), instance.bitlength(), pattern);
	 ASSERT_EQ(iRound, nret) << "Naive failed";  
	 const size_t bret = broadsearch(arr.data(), arr.size(), instance.bitlength(), pattern);  
	 ASSERT_EQ(iRound, bret) << "Broad failed";  
	 const size_t bqret = broadsearch_shift(arr.data(), arr.size(), instance.bitlength(), pattern);  
	 ASSERT_EQ(iRound, bqret) << "Shift failed";  
      }  
   }
}

TEST(BroadWord, LongTest) { 
   for(size_t reps = 0; reps < 5; ++reps) {
      for(size_t cBitlength = 1; cBitlength < 63; ++cBitlength) {
	 for(size_t cLength = 2; cLength < std::min(100ULL, 1ULL<<cBitlength); ++cLength) {
	    tdc::IntVector<tdc::dynamic_t> arr(cLength, 0, cBitlength);
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
	       const size_t aret = api_search(arr, pattern);
	       ASSERT_EQ(aret, iRound);
	       const size_t nret = naivsearch(arr.data(), cLength, cBitlength, pattern);
	       ASSERT_EQ(nret, iRound);
	       const size_t bret = broadsearch(arr.data(), cLength, cBitlength, pattern);
	       ASSERT_EQ(iRound, bret);
	       const size_t bqret = broadsearch_shift(arr.data(), cLength, cBitlength, pattern);
	       ASSERT_EQ(iRound, bqret);
	    }
	    for(size_t iRound = 0; iRound < cLength; ++iRound) {
		  const uint64_t pattern = rand() % (1ULL<<cBitlength);
		  DVLOG(3) << " == Pattern = " << ((size_t)pattern);
		  const size_t aret = api_search(arr, pattern);
		  const size_t nret = naivsearch(arr.data(), cLength, cBitlength, pattern);
		  ASSERT_EQ(nret, aret);
		  const size_t bret = broadsearch(arr.data(), cLength, cBitlength, pattern);
		  ASSERT_EQ(nret, bret);
		  const size_t bqret = broadsearch_shift(arr.data(), cLength, cBitlength, pattern);
		  ASSERT_EQ(nret, bqret);
	    }
	 }
      }
   }
}

int main(int argc, char **argv) {
     ::testing::InitGoogleTest(&argc, argv);
       return RUN_ALL_TESTS();
}

