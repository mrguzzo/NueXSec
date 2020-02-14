#include "../include/selection.h"

namespace xsecSelection {
// -----------------------------------------------------------------------------
void selection::Initialise( const char * mc_file,
                            const char * ext_file,
                            const char * data_file,
                            const char * dirt_file,
                            const char * variation_file,
                            const std::vector<double> _config,
                            bool _slim){
    
    std::cout << "\nInitialising..." << std::endl;
    if (_slim){
        std::cout << "\033[0;32m-------------------------------" << std::endl;
        std::cout << "     Running in Slim Mode!" << std::endl;
        std::cout << "-------------------------------\033[0m" << std::endl;
        slim = _slim;
    }

    // Initialise the histogram helper
    if (!_slim) histogram_helper_instance.Initialise();
    if (!_slim) histogram_helper_instance.InitHistograms();

    // Resize the selection cuts instance vector, one instance per type e.g MC, data, ..
    selection_cuts_instance.resize(histogram_helper::k_type_MAX);

    // Print the input files
    std::cout <<
    "MC   File Path:      " << mc_file        <<"\n" <<
    "Ext  File Path:      " << ext_file       <<"\n" <<
    "Data File Path:      " << data_file      <<"\n" <<
    "Dirt File Path:      " << dirt_file      <<"\n" <<
    "Variation File Path: " << variation_file <<"\n" <<
    std::endl;

    // Now get the files, if file isnt specified then set bool to skip
    bool_use_mc        = _utility_instance.GetFile(f_mc,        mc_file);
    bool_use_ext       = _utility_instance.GetFile(f_ext,       ext_file);
    bool_use_data      = _utility_instance.GetFile(f_data,      data_file);
    bool_use_dirt      = _utility_instance.GetFile(f_dirt,      dirt_file);
    bool_use_variation = _utility_instance.GetFile(f_variation, variation_file);

    // Configure the externally configurable cut parameters
    std::cout << "\n --- Configuring Parameters --- \n" << std::endl;

    // Get MC variables --------------------------------------------------------
    if (bool_use_mc){
        std::cout << "\nInitialising MC" << std::endl;
        // _utility_instance.GetTree(f_mc, mytree, "AnalyzeTPCO/tree");

        std::cout << "-------------------------------" << std::endl;
        std::cout << "Initialisation of MC Complete!" << std::endl;
        std::cout << "\033[0;31m-------------------------------\033[0m" << std::endl;
    } // End getting MC variables

    // Initialise Data specific ------------------------------------------------
    if (bool_use_data){
        std::cout << "\nInitialising Data" << std::endl;
        _utility_instance.GetTree(f_data, data_tree, "nuselection/NeutrinoSelectionFilter");
        
        // Initialise all the data slice container
        data_SC.Initialise(data_tree);
        
        data_tree_total_entries = data_tree->GetEntries();
        std::cout << "Total Data Events:         " << data_tree_total_entries << std::endl;


        std::cout << "-------------------------------" << std::endl;
        std::cout << "Initialisation of Data Complete!" << std::endl;
        std::cout << "\033[0;31m-------------------------------\033[0m" << std::endl;

    } // End intialisation of Data variables

    // Initialise EXT specific -------------------------------------------------
    if (bool_use_ext){
        std::cout << "\nInitialising EXT" << std::endl;

        std::cout << "-------------------------------" << std::endl;
        std::cout << "Initialisation of EXT Complete!" << std::endl;
        std::cout << "\033[0;31m-------------------------------\033[0m" << std::endl;

    } // End intialisation of ext variables

    // Initialise Dirt specific ------------------------------------------------
    if (bool_use_dirt){
        std::cout << "\nInitialising Dirt" << std::endl;

        std::cout << "-------------------------------" << std::endl;
        std::cout << "Initialisation of Dirt Complete!" << std::endl;
        std::cout << "\033[0;31m-------------------------------\033[0m" << std::endl;

    } // End intialisation of dirt variables
    
    // Invoke main selection function
    make_selection();

} // END Initialise function
// -----------------------------------------------------------------------------
// Main function for selection
void selection::make_selection(){
    std::cout << "Now Running the selection!"<< std::endl;
    
    // *************************************************************************
    //  ----- Loop over the TPC Objects and Apply the selection cuts -----------
    // *************************************************************************

    // MC ----------------------------------------------------------------------
    if (bool_use_mc){
        std::cout << "Starting Selection over MC" << std::endl;

        std::cout << std::endl;
        std::cout << "Ending Selection over MC" << std::endl;
    }
    // Data --------------------------------------------------------------------
    if (bool_use_data){
        std::cout << "Starting Selection over Data" << std::endl;

        for (int ievent = 0; ievent < data_tree_total_entries; ievent++){

            // Alert the user
            if (ievent % 100000 == 0) std::cout << "On entry " << ievent/100000.0 <<"00k " << std::endl;
        
            // Get the entry in the tree
            data_tree->GetEntry(ievent); // TPC Objects

            if (data_SC.slpdg > 0) std::cout << "run: " << data_SC.run << "  subrun: " << data_SC.sub << "  event: " << data_SC.evt << std::endl;
            if (data_SC.slpdg > 0) std::cout << "slpdg: " << data_SC.slpdg << "  topo score: " << data_SC.topological_score << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Ending Selection over Data" << std::endl;
    }
    // EXT ---------------------------------------------------------------------
    if (bool_use_ext){
        std::cout << "Starting Selection over EXT" << std::endl;
         
        std::cout << std::endl;
        std::cout << "Ending Selection over EXT" << std::endl;

    }
    // Dirt --------------------------------------------------------------------
    if (bool_use_dirt){
        std::cout << "Starting Selection over Dirt" << std::endl;
         
        std::cout << std::endl;
        std::cout << "Ending Selection over Dirt" << std::endl;

    }
    // -------------------------------------------------------------------------
    std::cout << "Finished running the selection!"<< std::endl;
    return;
} // End Selection
// -----------------------------------------------------------------------------
bool selection::ApplyCuts(){

    // *************************************************************************

    // *************************************************************************
    return true;

}
// -----------------------------------------------------------------------------
void selection::SavetoFile(){

    // // Now saving histograms to file
    // std::cout << "Now Saving Histograms to file" << std::endl;
    // if (bool_use_mc) {
    //     histogram_helper_instance.WriteMCTruth("MC");
    //     histogram_helper_instance.WriteOptical(histogram_helper::k_mc);
    //     histogram_helper_instance.WriteReco(histogram_helper::k_mc);
    // }
    // if (bool_use_data) {
    //     histogram_helper_instance.WriteOptical(histogram_helper::k_data);
    //     histogram_helper_instance.WriteReco(histogram_helper::k_data);
    // }
    // if (bool_use_ext) {
    //     histogram_helper_instance.WriteOptical(histogram_helper::k_ext);
    //     histogram_helper_instance.WriteReco(histogram_helper::k_ext);
    // }
    // if (bool_use_dirt) {
    //     histogram_helper_instance.WriteMCTruth("Dirt");
    //     histogram_helper_instance.WriteOptical(histogram_helper::k_dirt);
    //     histogram_helper_instance.WriteReco(histogram_helper::k_dirt);
    // }

    

} // End save to file
// -----------------------------------------------------------------------------
void selection::MakeHistograms(){
    std::cout << "Creating histograms and making plots" << std::endl;

    histogram_plotter histogram_plotter_instance;

    // Loop over the cuts and plot histograms by plot type
    for (unsigned int i = 0 ; i < histogram_helper::k_cuts_MAX; i++){
        
        // Create a set of strings for creating a dynamic directory
        // Directory structure that is created will take the form plots/<cut>/
        std::string a = "if [ ! -d \"plots/";
        std::string b = "\" ]; then echo \"\nPlots folder does not exist... creating\"; mkdir -p plots/";
        std::string c = "; fi";
        std::string command = a +histogram_helper_instance.cut_dirs.at(i) + b + histogram_helper_instance.cut_dirs.at(i) + c ;
        system(command.c_str()); 

        // Reco X
        histogram_plotter_instance.MakeStack("h_reco_vtx_x",histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Reco Vertex X [cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_vtx_x.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );
        
        // Reco Y
        histogram_plotter_instance.MakeStack("h_reco_vtx_y",histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Reco Vertex Y [cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_vtx_y.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Reco Z
        histogram_plotter_instance.MakeStack("h_reco_vtx_z",histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Reco Vertex Z [cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_vtx_z.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // dEdx
        histogram_plotter_instance.MakeStack("h_reco_dEdx",histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Collection Plane dEdx [MeV/cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_dEdx_collection.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );
   
        // Leading Shower Momentum
        histogram_plotter_instance.MakeStack("h_reco_leading_mom", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Momentum [MeV/c]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_mom.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // 2D distance largest flash to reco nu vertex
        histogram_plotter_instance.MakeStack("h_reco_flash_to_vtx_dist", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Flash to Vertex Distance [cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_flash_to_vtx_dist.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // 2D distance shower vertex to reco nu vertex
        histogram_plotter_instance.MakeStack("h_reco_shower_to_vtx_dist", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Shower to Vertex Distance [cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_shower_to_vtx_dist.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // 2D distance track vertex to reco nu vertex
        histogram_plotter_instance.MakeStack("h_reco_track_to_vtx_dist", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Track to Vertex Distance [cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_track_to_vtx_dist.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading Shower hits in all planes
        histogram_plotter_instance.MakeStack("h_reco_leading_shower_hits_all_planes", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Hits All Planes", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_shower_hits_all_planes.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading Shower hits in collection
        histogram_plotter_instance.MakeStack("h_reco_leading_shower_hits_collection_plane", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Hits Collection Plane", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_shower_hits_collection_plane.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading Shower opening angle
        histogram_plotter_instance.MakeStack("h_reco_leading_shower_open_angle", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Open Angle [degrees]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_shower_open_angle.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Secondary shower to vertex distance (for events with more than 1 shower)
        histogram_plotter_instance.MakeStack("h_reco_secondary_shower_to_vtx_dist", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Secondary Shower to Vertex Distance (>1 shower) [cm]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_secondary_shower_to_vtx_dist.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading Shower hits per length
        histogram_plotter_instance.MakeStack("h_reco_leading_shower_hits_per_length", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Hits / Length [cm^{-1}]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_shower_hits_per_length.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Longest track to leading shower length
        histogram_plotter_instance.MakeStack("h_reco_longest_track_leading_shower_length", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Longest Track Length / Leading Shower Length", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_longest_track_leading_shower_length.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Track Containment
        histogram_plotter_instance.MakeStack("h_reco_track_contained", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Contained Tracks", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_track_contained.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading shower phi
        histogram_plotter_instance.MakeStack("h_reco_leading_shower_phi", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Phi [degrees]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_shower_phi.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading shower theta
        histogram_plotter_instance.MakeStack("h_reco_leading_shower_theta", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Theta [degrees]", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_shower_theta.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading shower cos theta
        histogram_plotter_instance.MakeStack("h_reco_leading_shower_cos_theta", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Leading Shower Cos(#theta)", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_leading_shower_cos_theta.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading shower multiplicity
        histogram_plotter_instance.MakeStack("h_reco_shower_multiplicity", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Shower Multiplicty", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_shower_multiplicity.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );

        // Leading track multiplicity
        histogram_plotter_instance.MakeStack("h_reco_track_multiplicity", histogram_helper_instance.cut_dirs.at(i).c_str(),
                                           false,  false, "Track Multiplicty", data_scale_factor, 1.0, intime_scale_factor, dirt_scale_factor, 0.8, 0.98, 0.98, 0.50,
                                           Form("plots/%s/reco_track_multiplicity.pdf", histogram_helper_instance.cut_dirs.at(i).c_str()) );
   
    }
    

}
// -----------------------------------------------------------------------------
} // END NAMESPACE xsecSelection