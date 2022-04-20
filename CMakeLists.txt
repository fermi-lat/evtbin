##### Library ######
add_library(
  evtbin STATIC
  src/BayesianBinner.cxx
  src/BinConfig.cxx
  src/ConstSnBinner.cxx
  src/CountCube.cxx
  src/CountMap.cxx
  src/DataProduct.cxx
  src/GlastGbmBinConfig.cxx
  src/GlastLatBinConfig.cxx
  src/Gti.cxx
  src/HealpixBinner.cxx
  src/HealpixMap.cxx
  src/Hist.cxx
  src/Hist1D.cxx
  src/Hist2D.cxx
  src/Hist3D.cxx
  src/LightCurve.cxx
  src/LinearBinner.cxx
  src/LogBinner.cxx
  src/MultiSpec.cxx
  src/OrderedBinner.cxx
  src/RecordBinFiller.cxx
  src/SingleSpec.cxx
)

target_link_libraries(evtbin PUBLIC astro healpix st_app st_stream tip st_facilities)

target_include_directories(
  evtbin PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>
)

###### Executables ######
add_executable(gtbin src/gtbin/gtbin.cxx)
add_executable(gtbindef src/gtbindef/gtbindef.cxx)
target_link_libraries(gtbin PRIVATE evtbin)
target_link_libraries(gtbindef PRIVATE evtbin)

###### Tests ######
add_executable(test_evtbin src/test/test_evtbin.cxx)
target_link_libraries(test_evtbin PRIVATE evtbin)

###############################################################
# Installation
###############################################################
install(DIRECTORY evtbin DESTINATION ${FERMI_INSTALL_INCLUDEDIR})
install(DIRECTORY data/ DESTINATION ${FERMI_INSTALL_DATADIR})
install(DIRECTORY pfiles/ DESTINATION ${FERMI_INSTALL_PFILESDIR})

install(
  TARGETS evtbin gtbin gtbindef
  # EXPORT fermiTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
