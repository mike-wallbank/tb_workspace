{
  // constants                                                                                                                                            
  double c = 299792458;
  double mass_elec = 0.511;      // [MeV/c^2]                                                                                                             
  double mass_muon = 105.658;
  double mass_pion = 139.570;
  double mass_kaon = 493.677;
  double mass_prot = 938.272;
  double mass_deut = 1875.613;

  std::vector<double> path_length = { 9.70772, 13.15639 }; // [m]                                                                                         
  std::vector<double> momenta = { 1250., 1000., 750., 500. };

  for (std::vector<double>::const_iterator path = path_length.begin(); path != path_length.end(); ++path) {
    for (std::vector<double>::const_iterator mom = momenta.begin(); mom != momenta.end(); ++mom) {
      double tof_elec = (*path)/((*mom)*c)*sqrt(pow(mass_elec,2)+pow((*mom),2))*1e9;
      double tof_muon = (*path)/((*mom)*c)*sqrt(pow(mass_muon,2)+pow((*mom),2))*1e9;
      double tof_pion = (*path)/((*mom)*c)*sqrt(pow(mass_pion,2)+pow((*mom),2))*1e9;
      double tof_kaon = (*path)/((*mom)*c)*sqrt(pow(mass_kaon,2)+pow((*mom),2))*1e9;
      double tof_prot = (*path)/((*mom)*c)*sqrt(pow(mass_prot,2)+pow((*mom),2))*1e9;
      double tof_deut = (*path)/((*mom)*c)*sqrt(pow(mass_deut,2)+pow((*mom),2))*1e9;
      std::cout << "Path length " << *path << ", momentum " << *mom << " time of flights [ns]:" << std::endl
                << " Electron " << tof_elec << std::endl
                << " Muon " << tof_muon << std::endl
                << " Pion " << tof_pion << std::endl
                << " Kaon " << tof_kaon << std::endl
                << " Proton " << tof_prot << std::endl
                << " Deuterion " << tof_deut << std::endl << std::endl;
    }
  }

}
