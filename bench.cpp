#include "broadword.hpp"
#include <celero/Celero.h>

/**
 * Fixture for Celero
 */
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


CELERO_MAIN


