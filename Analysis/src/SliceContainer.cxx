#include "../include/SliceContainer.h"

// -----------------------------------------------------------------------------
void SliceContainer::Initialise(TTree *tree){

    std::cout << "Initalising Slice Container" << std::endl;

    tree->SetBranchAddress("selected", &selected);
    tree->SetBranchAddress("run", &run);
    tree->SetBranchAddress("sub", &sub);
    tree->SetBranchAddress("evt", &evt);
    
    tree->SetBranchAddress("shr_energy_tot", &shr_energy_tot);
    tree->SetBranchAddress("shr_energy", &shr_energy);
    tree->SetBranchAddress("shr_energy_tot_cali", &shr_energy_tot_cali);
    tree->SetBranchAddress("shr_energy_cali", &shr_energy_cali);
    tree->SetBranchAddress("shr_theta", &shr_theta);
    tree->SetBranchAddress("shr_phi", &shr_phi);
    tree->SetBranchAddress("shr_pca_0", &shr_pca_0);
    tree->SetBranchAddress("shr_pca_1", &shr_pca_1);
    tree->SetBranchAddress("shr_pca_2", &shr_pca_2);
    tree->SetBranchAddress("shr_px", &shr_px);
    tree->SetBranchAddress("shr_py", &shr_py);
    tree->SetBranchAddress("shr_pz", &shr_pz);
    tree->SetBranchAddress("shr_openangle", &shr_openangle);
    tree->SetBranchAddress("shr_tkfit_start_x", &shr_tkfit_start_x);
    tree->SetBranchAddress("shr_tkfit_start_y", &shr_tkfit_start_y);
    tree->SetBranchAddress("shr_tkfit_start_z", &shr_tkfit_start_z);
    tree->SetBranchAddress("shr_tkfit_theta", &shr_tkfit_theta);
    tree->SetBranchAddress("shr_tkfit_phi", &shr_tkfit_phi);
    tree->SetBranchAddress("shr_start_x", &shr_start_x);
    tree->SetBranchAddress("shr_start_y", &shr_start_y);
    tree->SetBranchAddress("shr_start_z", &shr_start_z);
    tree->SetBranchAddress("shr_dedx_Y", &shr_dedx_Y);
    tree->SetBranchAddress("shr_dedx_V", &shr_dedx_V);
    tree->SetBranchAddress("shr_dedx_U", &shr_dedx_U);
    tree->SetBranchAddress("shr_dedx_Y_cali", &shr_dedx_Y_cali);
    tree->SetBranchAddress("shr_dedx_V_cali", &shr_dedx_V_cali);
    tree->SetBranchAddress("shr_dedx_U_cali", &shr_dedx_U_cali);
    tree->SetBranchAddress("shr_tkfit_dedx_Y", &shr_tkfit_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_dedx_V", &shr_tkfit_dedx_V);
    tree->SetBranchAddress("shr_tkfit_dedx_U", &shr_tkfit_dedx_U);
    // tree->SetBranchAddress("shr_tkfit_nhits_Y", &shr_tkfit_nhits_Y);
    // tree->SetBranchAddress("shr_tkfit_nhits_V", &shr_tkfit_nhits_V);
    // tree->SetBranchAddress("shr_tkfit_nhits_U", &shr_tkfit_nhits_U);
    tree->SetBranchAddress("shr_tkfit_dedx_Y_alt", &shr_tkfit_dedx_Y_alt);
    tree->SetBranchAddress("shr_tkfit_dedx_V_alt", &shr_tkfit_dedx_V_alt);
    tree->SetBranchAddress("shr_tkfit_dedx_U_alt", &shr_tkfit_dedx_U_alt);
    // tree->SetBranchAddress("shr_tkfit_nhits_Y_alt", &shr_tkfit_nhits_Y_alt);
    // tree->SetBranchAddress("shr_tkfit_nhits_V_alt", &shr_tkfit_nhits_V_alt);
    // tree->SetBranchAddress("shr_tkfit_nhits_U_alt", &shr_tkfit_nhits_U_alt);
    tree->SetBranchAddress("shr_trkfitmedangle", &shr_trkfitmedangle);
    tree->SetBranchAddress("shrmoliereavg", &shrmoliereavg);
    tree->SetBranchAddress("shrmoliererms", &shrmoliererms);
    
    tree->SetBranchAddress("ismerged",       &ismerged);
    tree->SetBranchAddress("merge_bestdot",  &merge_bestdot);
    tree->SetBranchAddress("merge_bestdist", &merge_bestdist);
    tree->SetBranchAddress("merge_vtx_x",    &merge_vtx_x);
    tree->SetBranchAddress("merge_vtx_y",    &merge_vtx_y);
    tree->SetBranchAddress("merge_vtx_z",    &merge_vtx_z);
    // tree->SetBranchAddress("merge_tk_ipfp", &merge_tk_ipfp);
    
    tree->SetBranchAddress("shr_tkfit_2cm_dedx_Y",    &shr_tkfit_2cm_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_2cm_dedx_V",    &shr_tkfit_2cm_dedx_V);
    tree->SetBranchAddress("shr_tkfit_2cm_dedx_U",    &shr_tkfit_2cm_dedx_U);
    tree->SetBranchAddress("shr_tkfit_2cm_nhits_Y",   &shr_tkfit_2cm_nhits_Y  );
    tree->SetBranchAddress("shr_tkfit_2cm_nhits_V",   &shr_tkfit_2cm_nhits_V  );
    tree->SetBranchAddress("shr_tkfit_2cm_nhits_U",   &shr_tkfit_2cm_nhits_U  );
    tree->SetBranchAddress("shr_tkfit_gap05_dedx_Y",  &shr_tkfit_gap05_dedx_Y );
    tree->SetBranchAddress("shr_tkfit_gap05_dedx_V",  &shr_tkfit_gap05_dedx_V );
    tree->SetBranchAddress("shr_tkfit_gap05_dedx_U",  &shr_tkfit_gap05_dedx_U );
    tree->SetBranchAddress("shr_tkfit_gap05_nhits_Y", &shr_tkfit_gap05_nhits_Y );
    tree->SetBranchAddress("shr_tkfit_gap05_nhits_V", &shr_tkfit_gap05_nhits_V );
    tree->SetBranchAddress("shr_tkfit_gap05_nhits_U", &shr_tkfit_gap05_nhits_U );
    tree->SetBranchAddress("shr_tkfit_gap10_dedx_Y",  &shr_tkfit_gap10_dedx_Y );
    tree->SetBranchAddress("shr_tkfit_gap10_dedx_V",  &shr_tkfit_gap10_dedx_V );
    tree->SetBranchAddress("shr_tkfit_gap10_dedx_U",  &shr_tkfit_gap10_dedx_U );
    tree->SetBranchAddress("shr_tkfit_gap10_nhits_Y", &shr_tkfit_gap10_nhits_Y );
    tree->SetBranchAddress("shr_tkfit_gap10_nhits_V", &shr_tkfit_gap10_nhits_V );
    tree->SetBranchAddress("shr_tkfit_gap10_nhits_U", &shr_tkfit_gap10_nhits_U );
    tree->SetBranchAddress("shr_chipr",      &shr_chipr);
    tree->SetBranchAddress("shr_chimu",      &shr_chimu);
    tree->SetBranchAddress("shr_bragg_p",    &shr_bragg_p);
    tree->SetBranchAddress("shr_bragg_mu",   &shr_bragg_mu);
    tree->SetBranchAddress("shr_bragg_mip",  &shr_bragg_mip);
    tree->SetBranchAddress("shr_bragg_kaon", &shr_bragg_kaon);
    tree->SetBranchAddress("shr_bragg_pion", &shr_bragg_pion);
    
    tree->SetBranchAddress("tksh_distance", &tksh_distance);
    tree->SetBranchAddress("tksh_angle",    &tksh_angle);
    
    tree->SetBranchAddress("shr_distance", &shr_distance);
    tree->SetBranchAddress("shr_score", &shr_score);
    tree->SetBranchAddress("shr_bkt_pdg", &shr_bkt_pdg);
    tree->SetBranchAddress("shr_bkt_purity", &shr_bkt_purity);
    tree->SetBranchAddress("shr_bkt_completeness", &shr_bkt_completeness);
    tree->SetBranchAddress("shr_bkt_E", &shr_bkt_E);
    
    tree->SetBranchAddress("trk_len", &trk_len);
    tree->SetBranchAddress("trk_theta", &trk_theta);
    tree->SetBranchAddress("trk_phi", &trk_phi);
    tree->SetBranchAddress("trk_energy", &trk_energy);
    tree->SetBranchAddress("trk_energy_muon", &trk_energy_muon);
    tree->SetBranchAddress("trk_energy_muon_mcs", &trk_energy_muon_mcs);
    tree->SetBranchAddress("trk_energy_tot", &trk_energy_tot);
    tree->SetBranchAddress("trk_energy_muon_tot", &trk_energy_muon_tot);
    tree->SetBranchAddress("trk_distance", &trk_distance);
    tree->SetBranchAddress("trk_score", &trk_score);
    tree->SetBranchAddress("trk_bkt_pdg", &trk_bkt_pdg);
    tree->SetBranchAddress("trk_bkt_purity", &trk_bkt_purity);
    tree->SetBranchAddress("trk_bkt_completeness", &trk_bkt_completeness);
    tree->SetBranchAddress("trk_bkt_E", &trk_bkt_E);
    tree->SetBranchAddress("trk_chipr_best", &trk_chipr_best);
    tree->SetBranchAddress("trk_chipr_worst", &trk_chipr_worst);
    tree->SetBranchAddress("trk_chimu_best", &trk_chimu_best);
    tree->SetBranchAddress("trk_chimu_worst", &trk_chimu_worst);
    tree->SetBranchAddress("trk_chipr", &trk_chipr);
    tree->SetBranchAddress("trk_chimu", &trk_chimu);
    tree->SetBranchAddress("trk_pida", &trk_pida);
    tree->SetBranchAddress("trk_bragg_p", &trk_bragg_p);
    tree->SetBranchAddress("trk_bragg_mu", &trk_bragg_mu);
    tree->SetBranchAddress("trk_bragg_mip", &trk_bragg_mip);
    tree->SetBranchAddress("trk_bragg_kaon", &trk_bragg_kaon);
    tree->SetBranchAddress("trk_bragg_pion", &trk_bragg_pion);
    // tree->SetBranchAddress("trk_hits_max", &trk_hits_max);
    // tree->SetBranchAddress("shr_hits_max", &shr_hits_max);
    tree->SetBranchAddress("trkshrhitdist0", &trkshrhitdist0);
    tree->SetBranchAddress("trkshrhitdist1", &trkshrhitdist1);
    tree->SetBranchAddress("trkshrhitdist2", &trkshrhitdist2);
    // tree->SetBranchAddress("total_hits_y", &total_hits_y);
    tree->SetBranchAddress("extra_energy_y", &extra_energy_y);
    tree->SetBranchAddress("trk_energy_hits_tot", &trk_energy_hits_tot);
    // tree->SetBranchAddress("shrsubclusters0", &shrsubclusters0);
    // tree->SetBranchAddress("shrsubclusters1", &shrsubclusters1);
    // tree->SetBranchAddress("shrsubclusters2", &shrsubclusters2);
    
    tree->SetBranchAddress("shrclusfrac0", &shrclusfrac0);
    tree->SetBranchAddress("shrclusfrac1", &shrclusfrac1);
    tree->SetBranchAddress("shrclusfrac2", &shrclusfrac2);
    tree->SetBranchAddress("shrclusdir0", &shrclusdir0);
    tree->SetBranchAddress("shrclusdir1", &shrclusdir1);
    tree->SetBranchAddress("shrclusdir2", &shrclusdir2);
    // tree->SetBranchAddress("shr_hits_tot", &shr_hits_tot);
    // tree->SetBranchAddress("shr_hits_y_tot", &shr_hits_y_tot);
    // tree->SetBranchAddress("shr_hits_u_tot", &shr_hits_u_tot);
    // tree->SetBranchAddress("shr_hits_v_tot", &shr_hits_v_tot);
    // tree->SetBranchAddress("trk_hits_tot", &trk_hits_tot);
    // tree->SetBranchAddress("trk_hits_y_tot", &trk_hits_y_tot);
    // tree->SetBranchAddress("trk_hits_u_tot", &trk_hits_u_tot);
    // tree->SetBranchAddress("trk_hits_v_tot", &trk_hits_v_tot);
    // tree->SetBranchAddress("elecclusters_U_charge", &elecclusters_U_charge);
    // tree->SetBranchAddress("elecclusters_V_charge", &elecclusters_V_charge);
    // tree->SetBranchAddress("elecclusters_Y_charge", &elecclusters_Y_charge);
    // tree->SetBranchAddress("elecclusters_U_N", &elecclusters_U_N);
    // tree->SetBranchAddress("elecclusters_V_N", &elecclusters_V_N);
    // tree->SetBranchAddress("elecclusters_Y_N", &elecclusters_Y_N);
    // tree->SetBranchAddress("n_tracks_contained", &n_tracks_contained);
    // tree->SetBranchAddress("n_showers_contained", &n_showers_contained);
    
    tree->SetBranchAddress("matched_E", &matched_E);
    tree->SetBranchAddress("hits_ratio", &hits_ratio);
    tree->SetBranchAddress("contained_fraction", &contained_fraction);
    tree->SetBranchAddress("sps_contained_fraction", &sps_contained_fraction);
    tree->SetBranchAddress("pt", &pt);
    tree->SetBranchAddress("p", &p);
    tree->SetBranchAddress("pt_assume_muon", &pt_assume_muon);
    tree->SetBranchAddress("p_assume_muon", &p_assume_muon);
    tree->SetBranchAddress("dvtx", &dvtx);
    tree->SetBranchAddress("dtrk", &dtrk);
    tree->SetBranchAddress("contained_sps_ratio", &contained_sps_ratio);
    tree->SetBranchAddress("CosmicIP", &CosmicIP);
    tree->SetBranchAddress("CosmicIPAll3D", &CosmicIPAll3D);
    tree->SetBranchAddress("CosmicDirAll3D", &CosmicDirAll3D);
    tree->SetBranchAddress("CosmicIPAll2DEnds", &CosmicIPAll2DEnds);
    tree->SetBranchAddress("CosmicDirAll2DEnds", &CosmicDirAll2DEnds);
    tree->SetBranchAddress("CosmicIPAll2DOvlp", &CosmicIPAll2DOvlp);
    tree->SetBranchAddress("CosmicDirAll2DOvlp", &CosmicDirAll2DOvlp);
    tree->SetBranchAddress("leeweight", &leeweight);
    tree->SetBranchAddress("true_pt", &true_pt);
    tree->SetBranchAddress("true_pt_visible", &true_pt_visible);
    tree->SetBranchAddress("true_p", &true_p);
    tree->SetBranchAddress("true_p_visible", &true_p_visible);
    tree->SetBranchAddress("true_e_visible", &true_e_visible);
    
    // tree->SetBranchAddress("opfilter_pe_beam", &opfilter_pe_beam);
    // tree->SetBranchAddress("opfilter_pe_veto", &opfilter_pe_veto);
    
    tree->SetBranchAddress("nu_pdg", &nu_pdg);
    tree->SetBranchAddress("ccnc",   &ccnc);
    tree->SetBranchAddress("interaction", &interaction);
    tree->SetBranchAddress("nu_e",   &nu_e);
    tree->SetBranchAddress("nu_pt",  &nu_pt);
    tree->SetBranchAddress("theta",  &theta);
    tree->SetBranchAddress("isVtxInFiducial",  &isVtxInFiducial);
    tree->SetBranchAddress("truthFiducial",    &truthFiducial);
    
    tree->SetBranchAddress("true_nu_vtx_t", &true_nu_vtx_t);
    tree->SetBranchAddress("true_nu_vtx_x", &true_nu_vtx_x);
    tree->SetBranchAddress("true_nu_vtx_y", &true_nu_vtx_y);
    tree->SetBranchAddress("true_nu_vtx_z", &true_nu_vtx_z);
    tree->SetBranchAddress("true_nu_vtx_sce_x", &true_nu_vtx_sce_x);
    tree->SetBranchAddress("true_nu_vtx_sce_y", &true_nu_vtx_sce_y);
    tree->SetBranchAddress("true_nu_vtx_sce_z", &true_nu_vtx_sce_z);
    
    tree->SetBranchAddress("reco_nu_vtx_x", &reco_nu_vtx_x);
    tree->SetBranchAddress("reco_nu_vtx_y", &reco_nu_vtx_y);
    tree->SetBranchAddress("reco_nu_vtx_z", &reco_nu_vtx_z);
    tree->SetBranchAddress("reco_nu_vtx_sce_x", &reco_nu_vtx_sce_x);
    tree->SetBranchAddress("reco_nu_vtx_sce_y", &reco_nu_vtx_sce_y);
    tree->SetBranchAddress("reco_nu_vtx_sce_z", &reco_nu_vtx_sce_z);
    
    tree->SetBranchAddress("nmuon", &nmuon);
    tree->SetBranchAddress("muon_e", &muon_e);
    tree->SetBranchAddress("muon_c", &muon_c);
    tree->SetBranchAddress("muon_p", &muon_p);
    tree->SetBranchAddress("nelec", &nelec);
    
    tree->SetBranchAddress("elec_e", &elec_e);
    tree->SetBranchAddress("elec_c", &elec_c);
    tree->SetBranchAddress("elec_p", &elec_p);
    tree->SetBranchAddress("elec_vx", &elec_vx);
    tree->SetBranchAddress("elec_vy", &elec_vy);
    tree->SetBranchAddress("elec_vz", &elec_vz);
    tree->SetBranchAddress("elec_px", &elec_px);
    tree->SetBranchAddress("elec_py", &elec_py);
    tree->SetBranchAddress("elec_pz", &elec_pz);
    
    tree->SetBranchAddress("npi0", &npi0);
    tree->SetBranchAddress("pi0_e", &pi0_e);
    tree->SetBranchAddress("pi0_c", &pi0_c);
    tree->SetBranchAddress("pi0_p", &pi0_p);
    tree->SetBranchAddress("nneutron", &nneutron);
    tree->SetBranchAddress("nproton", &nproton);
    
    tree->SetBranchAddress("proton_e", &proton_e);
    tree->SetBranchAddress("proton_c", &proton_c);
    tree->SetBranchAddress("proton_p", &proton_p);
    
    tree->SetBranchAddress("npion", &npion);
    tree->SetBranchAddress("pion_e", &pion_e);
    tree->SetBranchAddress("pion_c", &pion_c);
    tree->SetBranchAddress("pion_p", &pion_p);
    tree->SetBranchAddress("nslice", &nslice);
    tree->SetBranchAddress("crtveto", &crtveto);
    tree->SetBranchAddress("crthitpe", &crthitpe);
    tree->SetBranchAddress("category", &category);
    tree->SetBranchAddress("lep_e", &lep_e);
    tree->SetBranchAddress("pass", &pass);
    tree->SetBranchAddress("swtrig", &swtrig);
    tree->SetBranchAddress("evnhits", &evnhits);
    tree->SetBranchAddress("slpdg", &slpdg);
    tree->SetBranchAddress("slnhits", &slnhits);
    tree->SetBranchAddress("n_pfps", &n_pfps);
    tree->SetBranchAddress("n_tracks", &n_tracks);
    tree->SetBranchAddress("n_showers", &n_showers);
    
    // tree->SetBranchAddress("hits_u", &hits_u);
    // tree->SetBranchAddress("hits_v", &hits_v);
    // tree->SetBranchAddress("hits_y", &hits_y);
    
    tree->SetBranchAddress("topological_score", &topological_score);
    tree->SetBranchAddress("slclustfrac", &slclustfrac);
    tree->SetBranchAddress("endmuonmichel", &endmuonmichel);
    tree->SetBranchAddress("filter_antibdt", &filter_antibdt);
    tree->SetBranchAddress("filter_ncpi0", &filter_ncpi0);
    tree->SetBranchAddress("filter_pi0", &filter_pi0);
    tree->SetBranchAddress("filter_ccinclusive", &filter_ccinclusive);
    tree->SetBranchAddress("flash_pe", &flash_pe);
    tree->SetBranchAddress("flash_time", &flash_time);
    tree->SetBranchAddress("nu_flashmatch_score", &nu_flashmatch_score);
    tree->SetBranchAddress("best_cosmic_flashmatch_score", &best_cosmic_flashmatch_score);
    
    tree->SetBranchAddress("NeutrinoEnergy0", &NeutrinoEnergy0);
    tree->SetBranchAddress("NeutrinoEnergy1", &NeutrinoEnergy1);
    tree->SetBranchAddress("NeutrinoEnergy2", &NeutrinoEnergy2);
    
    tree->SetBranchAddress("SliceCaloEnergy0", &SliceCaloEnergy0);
    tree->SetBranchAddress("SliceCaloEnergy1", &SliceCaloEnergy1);
    tree->SetBranchAddress("SliceCaloEnergy2", &SliceCaloEnergy2);
    
    tree->SetBranchAddress("nnoise_pl1", &nnoise_pl1);
    tree->SetBranchAddress("nslhits_pl1", &nslhits_pl1);
    tree->SetBranchAddress("nslnoise_pl1", &nslnoise_pl1);
    tree->SetBranchAddress("nhits_pl1", &nhits_pl1);
    tree->SetBranchAddress("frac_slnoise_pl1", &frac_slnoise_pl1);
    
    tree->SetBranchAddress("secondshower_U_charge", &secondshower_U_charge);
    tree->SetBranchAddress("secondshower_U_nhit", &secondshower_U_nhit);
    tree->SetBranchAddress("secondshower_U_vtxdist", &secondshower_U_vtxdist);
    tree->SetBranchAddress("secondshower_U_eigenratio", &secondshower_U_eigenratio);
    tree->SetBranchAddress("secondshower_U_dot", &secondshower_U_dot);
    tree->SetBranchAddress("secondshower_U_dir", &secondshower_U_dir);
    tree->SetBranchAddress("secondshower_V_charge", &secondshower_V_charge);
    tree->SetBranchAddress("secondshower_V_nhit", &secondshower_V_nhit);
    tree->SetBranchAddress("secondshower_V_vtxdist", &secondshower_V_vtxdist);
    tree->SetBranchAddress("secondshower_V_eigenratio", &secondshower_V_eigenratio);
    tree->SetBranchAddress("secondshower_V_dot", &secondshower_V_dot);
    tree->SetBranchAddress("secondshower_V_dir", &secondshower_V_dir);
    tree->SetBranchAddress("secondshower_Y_charge", &secondshower_Y_charge);
    tree->SetBranchAddress("secondshower_Y_nhit", &secondshower_Y_nhit);
    tree->SetBranchAddress("secondshower_Y_vtxdist", &secondshower_Y_vtxdist);
    tree->SetBranchAddress("secondshower_Y_eigenratio", &secondshower_Y_eigenratio);
    tree->SetBranchAddress("secondshower_Y_dot", &secondshower_Y_dot);
    tree->SetBranchAddress("secondshower_Y_dir", &secondshower_Y_dir);
    
    tree->SetBranchAddress("evnunhits", &evnunhits);
    tree->SetBranchAddress("evlepnhits", &evlepnhits);
    tree->SetBranchAddress("evpronhits", &evpronhits);
    tree->SetBranchAddress("evpi1nhits", &evpi1nhits);
    tree->SetBranchAddress("evpi0nhits", &evpi0nhits);
    tree->SetBranchAddress("evneunhits", &evneunhits);
    tree->SetBranchAddress("evgamnhits", &evgamnhits);
    tree->SetBranchAddress("evothnhits", &evothnhits);
    
    tree->SetBranchAddress("slnunhits", &slnunhits);
    tree->SetBranchAddress("sllepnhits", &sllepnhits);
    tree->SetBranchAddress("slpronhits", &slpronhits);
    tree->SetBranchAddress("slpi1nhits", &slpi1nhits);
    tree->SetBranchAddress("slpi0nhits", &slpi0nhits);
    tree->SetBranchAddress("slneunhits", &slneunhits);
    tree->SetBranchAddress("slgamnhits", &slgamnhits);
    tree->SetBranchAddress("slothnhits", &slothnhits);
    
    tree->SetBranchAddress("nu_completeness_from_pfp", &nu_completeness_from_pfp);
    tree->SetBranchAddress("nu_purity_from_pfp", &nu_purity_from_pfp);
    // tree->SetBranchAddress("n_tracks_pandora", &n_tracks_pandora);
    
    // tree->SetBranchAddress("vtx_fit_pandora_x", &vtx_fit_pandora_x);
    // tree->SetBranchAddress("vtx_fit_pandora_y", &vtx_fit_pandora_y);
    // tree->SetBranchAddress("vtx_fit_pandora_z", &vtx_fit_pandora_z);
    
    // tree->SetBranchAddress("n_tracks_tkfit", &n_tracks_tkfit);
    // tree->SetBranchAddress("vtx_fit_tkfit_x", &vtx_fit_tkfit_x);
    // tree->SetBranchAddress("vtx_fit_tkfit_y", &vtx_fit_tkfit_y);
    // tree->SetBranchAddress("vtx_fit_tkfit_z", &vtx_fit_tkfit_z);
    
    tree->SetBranchAddress("bdt_nuNCpi0", &bdt_nuNCpi0);
    tree->SetBranchAddress("bdt_numuCCpi0", &bdt_numuCCpi0);
    tree->SetBranchAddress("bdt_numuCC", &bdt_numuCC);
    tree->SetBranchAddress("bdt_ext",    &bdt_ext);
    tree->SetBranchAddress("bdt_cosmic", &bdt_cosmic);
    tree->SetBranchAddress("bdt_global", &bdt_global);

}
// -----------------------------------------------------------------------------
std::pair<std::string, int> SliceContainer::SliceClassifier(int type){
    
    // MC Specific classsifications
    if (type == _util.k_mc){

        // Out of Fiducial Volume Event
        if (!isVtxInFiducial) return std::make_pair("nu_out_fv",_util.k_nu_out_fv);

        // Charged Current 
        if (ccnc == _util.k_CC){

            // NuMu CC
            if (nu_pdg == 14 || nu_pdg == -14){
                
                if (npi0 > 0) return std::make_pair("numu_cc_pi0", _util.k_numu_cc_pi0); // has a pi0
                else return std::make_pair("numu_cc",_util.k_numu_cc);

            }
            // Nue CC
            else if (nu_pdg == 12 || nu_pdg == -12){

                // Check if the neutrino has a purity > 50%
                if (nu_purity_from_pfp > 0.5) return std::make_pair("nue_cc",_util.k_nue_cc);
               
                // Classify as a cosmic
                else return std::make_pair("cosmic",_util.k_cosmic);

            }
            // Unknown Neutrino Type
            else {
                std::cout << "Unknown Neutrino Type..." << std::endl;
                return std::make_pair("unmatched",_util.k_unmatched);
            }

        }
        // Neutral Current
        else {
            if (npi0 > 0) return std::make_pair("nc_pi0",_util.k_nc_pi0);
            else return std::make_pair("nc",_util.k_nc);
        }

    }
    // Data
    else if (type == _util.k_data){
        return std::make_pair("data",_util.k_leg_data);
    }
    // EXT
    else if (type == _util.k_ext){
        return std::make_pair("ext",_util.k_leg_ext);
        
    }
    // Dirt
    else if (type == _util.k_dirt){
        return std::make_pair("dirt",_util.k_leg_dirt);
    }
    // What is this type?
    else return std::make_pair("unmatched",_util.k_unmatched);
    
}
// -----------------------------------------------------------------------------
std::string SliceContainer::SliceCategory(){

    if (category == _util.k_pandora_nu_e_other) {
        return "nue_other";

    }
    else if (category == _util.k_pandora_nu_e_cc0pi0p ) {
        return "nu_e_cc0pi0p";

    }
    else if (category == _util.k_pandora_nu_e_cc0pinp ) {
        return "nu_e_cc0pinp";

    }
    else if (category == _util.k_pandora_nu_mu_other) {
        return "nu_mu_other";

    }
    else if (category == _util.k_pandora_nu_mu_pi0 ) {
        return "nu_mu_pi0";

    }
    else if (category == _util.k_pandora_nc) {
        return "nc";

    }
    else if (category == _util.k_pandora_nc_pi0 ) {
        return "nc_pi0";

    }
    else if (category == _util.k_pandora_cosmic) {
        return "cosmic";

    }
    else if (category == _util.k_pandora_outfv) {
        return "outfv";

    }
    else if (category == _util.k_pandora_other) {
        return "other";

    }
    else if (category == _util.k_pandora_data) {
        return "data";
    }
    else {
        std::cout << "Unknown Category type"<< std::endl;
        return "unknown";
    }
}
// -----------------------------------------------------------------------------
std::string SliceContainer::SliceInteractionType(int type){

    // Only do this for mc, otherwise return data type
    if (type == _util.k_mc || type == _util.k_dirt){
        std::string nu;
        std::string CCNC;

        // Get the nu flavour
        if (nu_pdg == 14 ){
            nu = "numu_";
        }
        else if (nu_pdg == -14){
            nu = "numu_bar_";
        }
        else if (nu_pdg == 12){
            nu = "nue_";
        }
        else if (nu_pdg == -12){
            nu = "nue_bar_";
        }
        else {
            nu = "unknown_";
        }

        // The interaction type
        if (ccnc == _util.k_CC){
            CCNC = "cc_";
        }
        else CCNC = "nc_";


        if (interaction == _util.k_qe) {
            return nu + CCNC + "qe";

        }
        else if (interaction == _util.k_res ) {
            return nu + CCNC + "res";

        }
        else if (interaction == _util.k_dis ) {
            return nu + CCNC + "dis";

        }
        else if (interaction == _util.k_coh) {
            return nu + CCNC + "coh";

        }
        else if (interaction == _util.k_mec) {
            return nu + CCNC + "mec";

        }
    }
    else return "data";


}
// -----------------------------------------------------------------------------