/** \file Hist2D.h
    \brief Two dimensional histogram.
*/
#include <stdexcept>

#include "evtbin/Binner.h"
#include "evtbin/Hist2D.h"

namespace evtbin {

  Hist2D::Hist2D(const Binner & binner1, const Binner & binner2): m_data() {
    // Set initial size of data array:
    m_data.resize(binner1.getNumBins());
    for (Cont_t::iterator itor = m_data.begin(); itor != m_data.end(); ++itor) {
      itor->resize(binner2.getNumBins(), 0);
    }

    // Save binners:
    m_binners.resize(2);
    m_binners[0] = binner1.clone();
    m_binners[1] = binner2.clone();
  }

  Hist2D::~Hist2D() throw() {}

  void Hist2D::fillBin(const std::vector<double> & value, double weight) {
    fillBin(value[0], value[1], weight);
  }

  void Hist2D::fillBin(double value1, double value2, double weight) {
    // Use the binners to determine the indices for the data:
    long index1 = m_binners[0]->computeIndex(value1);
    long index2 = m_binners[1]->computeIndex(value2);

    // Make sure indices are valid:
    if (0 <= index1 && 0 <= index2) {
      // Increment the appropriate bin:
      m_data[index1][index2] += weight;
    }
  }

}
