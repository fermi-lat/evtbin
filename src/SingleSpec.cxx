/** \file SingleSpec.cxx
    \brief Encapsulation of a single spectrum, with methods to read/write using tip.
    \author James Peachey, HEASARC
*/
#include <memory>
#include <string>

#include "evtbin/Binner.h"
#include "evtbin/SingleSpec.h"
#include "tip/IFileSvc.h"
#include "tip/Table.h"

namespace evtbin {

  SingleSpec::SingleSpec(const Binner & binner): DataProduct(), m_hist(binner) { m_hist_ptr = &m_hist; }

  SingleSpec::~SingleSpec() throw() {}

  void SingleSpec::writeOutput(const std::string & creator, const std::string & out_file) const {
    // Standard file creation from base class.
    createFile(creator, out_file, m_data_dir + "LatSingleBinnedTemplate");

    // Open SPECTRUM extension of output PHA1 file. Use an auto_ptr so that the table object
    // will for sure be deleted, even if an exception is thrown.
    std::auto_ptr<tip::Table> output_table(tip::IFileSvc::instance().editTable(out_file, "SPECTRUM"));

    // The binner from the histogram will be used below.
    const Binner * binner = m_hist.getBinners().at(0);

    // Resize table: number of records in output file must == the number of bins in the binner.
    output_table->setNumRecords(binner->getNumBins());

    // Need output table iterator.
    tip::Table::Iterator table_itor = output_table->begin();

    // Iterate over bin number and output table iterator, writing fields in order.
    for (long index = 0; index != binner->getNumBins(); ++index, ++table_itor) {
      // Channel of each bin.
      (*table_itor)["CHANNEL"].set(index + 1);

      // Number of counts in each bin, from the histogram.
      (*table_itor)["COUNTS"].set(m_hist[index]);
    }
  }

}