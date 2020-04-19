#include "../include/TreeHelper.h"

// -----------------------------------------------------------------------------
void TreeHelper::Initialise(int type, const char* run_period, std::string file_out, int weight_cfg ){

    std::cout << "Initalising Tree Helper..." << std::endl;

    std::string file_out_str = file_out;

    std::string file_name;

    if (type == _util.k_mc){

        // If the file name is empty then we use the default file name
        if (file_out_str == "empty") file_name = Form("files/trees/nuexsec_selected_tree_mc_run%s.root", run_period);
        else file_name = "files/trees/" + file_out_str;
        
        // File not already open, open the file
        if (!gROOT->GetListOfFiles()->FindObject( file_name.c_str() ) ) {
            f_nuexsec = new TFile( file_name.c_str(), "UPDATE");
        }

        // Create the TTree
        tree      = new TTree("mc_tree",         "mc_tree");
        eff_tree  = new TTree("mc_eff_tree",     "mc_eff_tree");
        dedx_tree = new TTree("mc_dedx_tree",    "mc_dedx_tree");
    }
    else if (type == _util.k_data){
        
        // If the file name is empty then we use the default file name
        if (file_out_str == "empty") file_name = Form("files/trees/nuexsec_selected_tree_data_run%s.root", run_period);
        else file_name = "files/trees/" + file_out_str;

        // File not already open, open the file
        if (!gROOT->GetListOfFiles()->FindObject(file_name.c_str()) ) {
            f_nuexsec = new TFile(file_name.c_str(), "UPDATE");
        }

        // Create the TTree
        tree      = new TTree("data_tree",     "data_tree");
        dedx_tree = new TTree("data_dedx_tree","data_dedx_tree");

    }
    else if (type == _util.k_ext){

        // If the file name is empty then we use the default file name
        if (file_out_str == "empty") file_name = Form("files/trees/nuexsec_selected_tree_ext_run%s.root", run_period);
        else file_name = "files/trees/" + file_out_str;
        
        // File not already open, open the file
        if (!gROOT->GetListOfFiles()->FindObject(file_name.c_str()) ) {
            f_nuexsec = new TFile(file_name.c_str(), "UPDATE");
        }

        // Create the TTree
        tree      = new TTree("ext_tree",     "ext_tree");
        dedx_tree = new TTree("ext_dedx_tree","ext_dedx_tree");

    }
    else if (type == _util.k_dirt){
        
        // If the file name is empty then we use the default file name
        if (file_out_str == "empty") file_name = Form("files/trees/nuexsec_selected_tree_dirt_run%s.root", run_period);
        else file_name = "files/trees/" + file_out_str;

        // File not already open, open the file
        if (!gROOT->GetListOfFiles()->FindObject(file_name.c_str()) ) {
            f_nuexsec = new TFile(file_name.c_str(), "UPDATE");
        }

        // Create the TTree
        tree      = new TTree("dirt_tree",     "dirt_tree");
        dedx_tree = new TTree("dirt_dedx_tree","dirt_dedx_tree");

    }
    else {
        std::cout << "Unknown input type!! "<<  __PRETTY_FUNCTION__ << std::endl;
        exit(1);
    }

    // Set the type
    _type = type;
    
    // Set the weight settings
    if (weight_cfg == 0){
        weight_tune = false;
        weight_ppfx = false;
    }
    else if (weight_cfg == 1){
        weight_tune = true;
        weight_ppfx = true;
    }
    else if (weight_cfg == 2){
        weight_tune = true;
        weight_ppfx = false;
    }
    else if (weight_cfg == 3){
        weight_tune = false;
        weight_ppfx = true;
    }
    else {
        std::cout << "Unknown weight setting specified, using defaults" << std::endl;
    }

    // Set the tree branches
    tree->Branch("run",    &run,    "run/I");
    tree->Branch("subrun", &subrun, "subrun/I");
    tree->Branch("event",  &event,  "event/I");
    tree->Branch("gen",    &gen,    "gen/O");
    tree->Branch("weight", &weight, "weight/D");
    tree->Branch("classifcation",   &classifcation);

    if (type == _util.k_mc){
        eff_tree->Branch("efficiency", &efficiency, "efficiency/D");
        eff_tree->Branch("purity", &purity, "purity/D");
    }

    dedx_tree->Branch("shr_dedx_Y_cali", &shr_dedx_Y_cali, "shr_dedx_Y_cali/F");
    dedx_tree->Branch("shr_dedx_V_cali", &shr_dedx_V_cali, "shr_dedx_V_cali/F");
    dedx_tree->Branch("shr_dedx_U_cali", &shr_dedx_U_cali, "shr_dedx_U_cali/F");
    
    dedx_tree->Branch("shr_tkfit_dedx_Y", &shr_tkfit_dedx_Y, "shr_tkfit_dedx_Y/F");
    dedx_tree->Branch("shr_tkfit_dedx_V", &shr_tkfit_dedx_V, "shr_tkfit_dedx_V/F");
    dedx_tree->Branch("shr_tkfit_dedx_U", &shr_tkfit_dedx_U, "shr_tkfit_dedx_U/F");
    
    dedx_tree->Branch("shr_tkfit_dedx_Y_alt", &shr_tkfit_dedx_Y_alt, "shr_tkfit_dedx_Y_alt/F");
    dedx_tree->Branch("shr_tkfit_dedx_V_alt", &shr_tkfit_dedx_V_alt, "shr_tkfit_dedx_V_alt/F");
    dedx_tree->Branch("shr_tkfit_dedx_U_alt", &shr_tkfit_dedx_U_alt, "shr_tkfit_dedx_U_alt/F");
    
    dedx_tree->Branch("shr_tkfit_2cm_dedx_Y", &shr_tkfit_2cm_dedx_Y, "shr_tkfit_2cm_dedx_Y/F");
    dedx_tree->Branch("shr_tkfit_2cm_dedx_V", &shr_tkfit_2cm_dedx_V, "shr_tkfit_2cm_dedx_V/F");
    dedx_tree->Branch("shr_tkfit_2cm_dedx_U", &shr_tkfit_2cm_dedx_U, "shr_tkfit_2cm_dedx_U/F");
    
    dedx_tree->Branch("shr_tkfit_gap05_dedx_Y", &shr_tkfit_gap05_dedx_Y, "shr_tkfit_gap05_dedx_Y/F");
    dedx_tree->Branch("shr_tkfit_gap05_dedx_V", &shr_tkfit_gap05_dedx_V, "shr_tkfit_gap05_dedx_V/F");
    dedx_tree->Branch("shr_tkfit_gap05_dedx_U", &shr_tkfit_gap05_dedx_U, "shr_tkfit_gap05_dedx_U/F");
    
    dedx_tree->Branch("shr_tkfit_gap10_dedx_Y", &shr_tkfit_gap10_dedx_Y, "shr_tkfit_gap10_dedx_Y/F");
    dedx_tree->Branch("shr_tkfit_gap10_dedx_V", &shr_tkfit_gap10_dedx_V, "shr_tkfit_gap10_dedx_V/F");
    dedx_tree->Branch("shr_tkfit_gap10_dedx_U", &shr_tkfit_gap10_dedx_U, "shr_tkfit_gap10_dedx_U/F");

    dedx_tree->Branch("weight",          &weight,       "weight/D");
    dedx_tree->Branch("classifcation",   &classifcation);
    dedx_tree->Branch("shr_distance",    &shr_distance, "shr_distance/F");
    dedx_tree->Branch("shr_theta",       &shr_theta,    "shr_theta/F");
    dedx_tree->Branch("cut", &cut);

    std::cout << "Finished Initalising the Tree Helper..."<< std::endl;

}
// -----------------------------------------------------------------------------
void TreeHelper::FillVars(SliceContainer &SC, std::pair<std::string, int> _classification, bool _gen, double _weight){

    f_nuexsec->cd();

    run    = SC.run;
    subrun = SC.sub;
    event  = SC.evt;
    gen    = _gen;
    classifcation = _classification.first;
    weight = _weight;

    tree->Fill();

}
// -----------------------------------------------------------------------------
void TreeHelper::FillEff(double _efficiency, double _purity){

    efficiency = _efficiency;
    purity     = _purity;

    eff_tree->Fill();

}
// -----------------------------------------------------------------------------
void TreeHelper::Fill_dedxVars(SliceContainer &SC, std::pair<std::string, int> _classification, std::string _cut, double _weight){

    f_nuexsec->cd();

    classifcation = _classification.first;
    weight = _weight;
    cut    = _cut;


    shr_dedx_Y_cali        = SC.shr_dedx_Y_cali;
    shr_dedx_V_cali        = SC.shr_dedx_V_cali;
    shr_dedx_U_cali        = SC.shr_dedx_U_cali;
    shr_tkfit_dedx_Y       = SC.shr_tkfit_dedx_Y;
    shr_tkfit_dedx_V       = SC.shr_tkfit_dedx_V;
    shr_tkfit_dedx_U       = SC.shr_tkfit_dedx_U;
    shr_tkfit_dedx_Y_alt   = SC.shr_tkfit_dedx_Y_alt;
    shr_tkfit_dedx_V_alt   = SC.shr_tkfit_dedx_V_alt;
    shr_tkfit_dedx_U_alt   = SC.shr_tkfit_dedx_U_alt;
    shr_tkfit_2cm_dedx_Y   = SC.shr_tkfit_2cm_dedx_Y;
    shr_tkfit_2cm_dedx_V   = SC.shr_tkfit_2cm_dedx_V;
    shr_tkfit_2cm_dedx_U   = SC.shr_tkfit_2cm_dedx_U;
    shr_tkfit_gap05_dedx_Y = SC.shr_tkfit_gap05_dedx_Y;
    shr_tkfit_gap05_dedx_V = SC.shr_tkfit_gap05_dedx_V;
    shr_tkfit_gap05_dedx_U = SC.shr_tkfit_gap05_dedx_U;
    shr_tkfit_gap10_dedx_Y = SC.shr_tkfit_gap10_dedx_Y;
    shr_tkfit_gap10_dedx_V = SC.shr_tkfit_gap10_dedx_V;
    shr_tkfit_gap10_dedx_U = SC.shr_tkfit_gap10_dedx_U;
    shr_distance           = SC.shr_distance;
    shr_theta              = SC.shr_theta;

    dedx_tree->Fill();

}
// -----------------------------------------------------------------------------
void TreeHelper::WriteTree(int type){

    f_nuexsec->cd();

    tree->Write("",TObject::kOverwrite);

    // Write the efficiency tree only if its MC
    if (type == _util.k_mc) eff_tree->Write("",TObject::kOverwrite);

    dedx_tree->Write("",TObject::kOverwrite);

}
// -----------------------------------------------------------------------------