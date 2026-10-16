#include "GlastLatBinConfig.h"

namespace evtbin {

  void GlastLatBinConfig::load() {
    static GlastLatBinConfig s_prototype;
    s_config_cont.insert(std::make_pair("GLAST::LAT", &s_prototype));
    s_config_cont.insert(std::make_pair("FERMI::LAT", &s_prototype));
  }

  auto GlastLatBinConfig::clone() const -> GlastLatBinConfig * {
    return new GlastLatBinConfig(*this);
  }

}
