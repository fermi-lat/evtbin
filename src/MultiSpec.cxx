/** \file MultiSpec.cxx
    \brief Encapsulation of a single spectrum, with methods to read/write using tip.
    \author James Peachey, HEASARC
*/
#include <memory>
#include <string>

#include "evtbin/Binner.h"
#include "evtbin/MultiSpec.h"
#include "tip/IFileSvc.h"
#include "tip/Table.h"

namespace evtbin {

  MultiSpec::MultiSpec(const Binner & time_binner, const Binner & energy_binner): DataProduct(), m_hist(time_binner, energy_binner){
    m_hist_ptr = &m_hist;
  }

  MultiSpec::~MultiSpec() throw() {}

  void MultiSpec::writeOutput(const std::string & creator, const std::string & out_file) const {
    // Standard file creation from base class.
    createFile(creator, out_file, m_data_dir + "LatBinnedTemplate");

    // Open SPECTRUM extension of output PHA1 file. Use an auto_ptr so that the table object
    // will for sure be deleted, even if an exception is thrown.
    std::auto_ptr<tip::Table> output_table(tip::IFileSvc::instance().editTable(out_file, "SPECTRUM"));

    // Get number of bins in each dimension.
    long num_time_bins = m_hist.getBinners().at(0)->getNumBins();
    long num_energy_bins = m_hist.getBinners().at(1)->getNumBins();

    // Tweak the dimensionality of output table.
    // Need output table iterator.
    tip::Table::Iterator table_itor = output_table->begin();

    // Resize counts field: number of elements must be the same as the number of bins in the energy binner.
    (*table_itor)["CHANNEL"].setNumElements(num_energy_bins);
    (*table_itor)["COUNTS"].setNumElements(num_energy_bins);
    
    // Resize table: number of records in output file must == the number of bins in the time binner.
    output_table->setNumRecords(num_time_bins);

    long * channel = new long[num_energy_bins];
    for (long index = 0; index != num_energy_bins; ++index) channel[index] = index;

    // Iterate over bin number and output table iterator, writing fields in order.
    for (long index = 0; index != num_time_bins; ++index, ++table_itor) {
      // Channel of each bin.
      (*table_itor)["CHANNEL"].set(channel, channel + num_energy_bins, 0);

      // Number of counts in each bin, from the histogram.
      (*table_itor)["COUNTS"].set(&(m_hist[index][0]), &(m_hist[index][num_energy_bins]), 0);
    }

    delete [] channel;
  }

}