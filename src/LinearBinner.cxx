/** \file LinearBinner.cxx
    \brief Implementation of a linearly uniform interval binner.
*/

#include <cmath>

#include "evtbin/LinearBinner.h"

namespace evtbin {

  LinearBinner::LinearBinner(double interval_begin, double interval_end, double bin_size, const std::string & name):
    Binner(name),
    m_interval_begin(interval_begin),
    m_interval_end(interval_end),
    m_bin_size(bin_size),
    m_num_bins(long(ceil((interval_end - interval_begin)/bin_size))) {}

  auto LinearBinner::computeIndex(double value) const -> long {
    if (value < m_interval_begin || value >= m_interval_end) return -1;
    return long((value - m_interval_begin) / m_bin_size);
  }

  auto LinearBinner::getNumBins() const -> long { return m_num_bins; }

  auto LinearBinner::getInterval(long index) const -> Binner::Interval {
    // Check bounds, and handle endpoints explicitly to avoid any round-off:
    if (index < 0 || index >= m_num_bins)
      return Binner::Interval(0., 0.);
    else if (index == 0)
      return Binner::Interval(m_interval_begin, m_interval_begin + (1 + index) * m_bin_size);
    else if (index == m_num_bins - 1)
      return Binner::Interval(m_interval_begin + index * m_bin_size, m_interval_end);

    return Binner::Interval(
      m_interval_begin + index * m_bin_size,
      m_interval_begin + (1 + index) * m_bin_size
    );
  }

  auto LinearBinner::clone() const -> Binner * { return new LinearBinner(*this); }

}
