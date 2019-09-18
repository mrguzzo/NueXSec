#ifndef SELECTION_h
#define SELECTION_h

#include "utility.h"
#include "selection_cuts.h"
#include "histogram_helper.h"
#include "histogram_plotter.h"


/* 
Class is the main controller of the selection. Main.cxx will invoke the intilalisation
of this class. After the initialisation, the make_selection() function will be
run.

*/


namespace xsecSelection {

    class selection {

        private:
    
            // Scale factors
            const double data_scale_factor   = 0.1301; // v6 value - 0.12758;
            const double intime_scale_factor = 1.0154;
            const double dirt_scale_factor   = 0.16411;

            // Bools
            bool bool_use_mc{false};
            bool bool_use_ext{false};
            bool bool_use_data{false};
            bool bool_use_dirt{false};
            bool bool_use_variation{false};
            bool slim{false};               // Flag to decide whether to make, fill and plot histograms

            // TFiles
            TFile * f_mc;        // The MC file
            TFile * f_data;      // The data file
            TFile * f_ext;       // The ext file
            TFile * f_dirt;      // The dirt file
            TFile * f_variation; // The variation file

            // TTrees
            TTree * mytree; // MC TPC Object Tree
            TTree * optree; // MC Optical Tree
            TTree * mctree; // MC Tree
            TTree * mctruth_counter_tree; // Tree with counts for MC variables

            TTree * data_tree;   // Data TPC Object Tree
            TTree * data_optree; // Data Optical Tree

            TTree * ext_tree;    // EXT TPC Object Tree
            TTree * ext_optree;  // EXT Optical Tree

            TTree * dirt_tree;   // Dirt TPC Object Tree
            TTree * dirt_optree; // Dirt Optical Tree

            // Class Instances
            utilityNS::utility _utility_instance;
            std::vector<selection_cuts> selection_cuts_instance; // One for each type e.g MC, Data, EXT..
            histogram_helper  histogram_helper_instance;
            // histogram_plotter histogram_plotter_instance;

            // Variables -------------------------------------------------------

            // Selection Cut Values
            double _x1;
            double _x2;
            double _y1;
            double _y2;
            double _z1;
            double _z2;
            double flash_pe_threshold;
            double flash_time_start;
            double flash_time_end;
            double tolerance;
            double shwr_nue_tolerance;
            double trk_nue_tolerance;
            double shwr_hit_threshold;
            double shwr_hit_threshold_collection;
            double tolerance_open_angle_min;
            double tolerance_open_angle_max;
            double tolerance_dedx_min;
            double tolerance_dedx_max;
            double dist_tolerance;
            double pfp_hits_length_tolerance;
            double ratio_tolerance;
            bool   detector_variations;
            std::vector<double> fv_boundary_v;

            // Vector containing the cut names
            std::vector<std::string> cut_names = {
                "Pandora Output",                           // The output TPC Objects from Pandora
                "Flash PE and In Time",                     // Flash PE and In time flash
                "Has Pandora Nue",                          // Pandora Nue 
                "In FV",                                    // Fiducial volume
                "Vertex to Flash",                          // Vertex to flash
                "Shower to Nue Dist",                       // Distance between pfp shower and nue object
                "Track to Nue Dist",                        // Distance between pfp track and nue object
                "Shower Hit_Threshold",                     // Hit threshold for at least one shower
                "Shower Hit Threshold Collection Plane",    // Hit threshold for at least one shower on collection plane
                "Shower Open Angle",                        // Tolerance for leading shower open angle
                "Shower dEdx",                              // Tolerance for dedx of leading shower
                "Dist Nue Vtx Secondary Showers",           // Tolerance for distance from the reco nue vtx for TPCO w/ >3 showers
                "Hits per Length",                          // Tolerance for hits/length
                "Longest Track over Leading Shower Length", // Tolerance for longest track length / leading shower length
                "Track Is Contained"                        // Contained Tracks
            };

            // TPC Object Containers
            std::vector<xsecAna::TPCObjectContainer> * tpc_object_container_v       = nullptr;  // MC
            std::vector<xsecAna::TPCObjectContainer> * data_tpc_object_container_v  = nullptr;  // Data
            std::vector<xsecAna::TPCObjectContainer> * ext_tpc_object_container_v   = nullptr;  // EXT
            std::vector<xsecAna::TPCObjectContainer> * dirt_tpc_object_container_v  = nullptr;  // Dirt

            // Optical Containers
            std::vector<std::vector<double>> mc_largest_flash_v_v;    // MC container for largest flashes
            std::vector<std::vector<double>> data_largest_flash_v_v;  // Data container for largest flashes
            std::vector<std::vector<double>> ext_largest_flash_v_v;   // EXT container for largest flashes
            std::vector<std::vector<double>> dirt_largest_flash_v_v;  // Dirt container for largest flashes

            std::vector<std::vector<int>> mc_optical_list_pe_v;       // MC container for optical flash PE
            std::vector<std::vector<int>> data_optical_list_pe_v;     // Data container for optical flash PE
            std::vector<std::vector<int>> ext_optical_list_pe_v;      // EXT container for optical flash PE
            std::vector<std::vector<int>> dirt_optical_list_pe_v;     // Dirt container for optical flash PE

            std::vector<std::vector<double>> mc_optical_list_flash_time_v;   // MC container for optical flash time
            std::vector<std::vector<double>> data_optical_list_flash_time_v; // Data container for optical flash time
            std::vector<std::vector<double>> ext_optical_list_flash_time_v;  // EXT container for optical flash time
            std::vector<std::vector<double>> dirt_optical_list_flash_time_v; // Dirt container for optical flash time


            // Passed Containers
            std::vector<Passed_Container> mc_passed_v;   // MC Passed Container
            std::vector<Passed_Container> data_passed_v; // Data Passed Container
            std::vector<Passed_Container> ext_passed_v;  // EXT Passed Container
            std::vector<Passed_Container> dirt_passed_v; // Dirt Passed Container
            
            // Counter Containers
            std::vector<std::vector<double>> mc_counter_v;
            std::vector<std::vector<double>> data_counter_v;
            std::vector<std::vector<double>> ext_counter_v;
            std::vector<std::vector<double>> dirt_counter_v;

            // Counter variables
            int tree_total_entries;       // MC
            int data_tree_total_entries;  // Data
            int ext_tree_total_entries;   // EXT
            int dirt_tree_total_entries;  // Dirt

            // MC Truth Counter Tree Variables
            int    mc_nue_cc_counter      = 0;
            int    mc_nue_nc_counter      = 0;
            int    mc_numu_cc_counter     = 0;
            int    mc_numu_nc_counter     = 0;
            int    mc_nue_cc_counter_bar  = 0;
            int    mc_numu_cc_counter_bar = 0;
            int    mc_nue_nc_counter_bar  = 0;
            int    mc_numu_nc_counter_bar = 0;
            double mc_nu_energy           = 0;
            double mc_nu_momentum         = 0;
            int    mc_nu_id               = -1;
            double mc_nu_vtx_x            = -999;
            double mc_nu_vtx_y            = -999;
            double mc_nu_vtx_z            = -999;
            double mc_nu_dir_x            = -999;
            double mc_nu_dir_y            = -999;
            double mc_nu_dir_z            = -999;
            double mc_ele_dir_x           = -999;
            double mc_ele_dir_y           = -999;
            double mc_ele_dir_z           = -999;
            double mc_ele_energy          = 0;
            double mc_ele_momentum        = 0;
            bool   has_pi0                = false;
            double mc_nu_time             = -1;

            int mc_nu_num_particles         = 0;
            int mc_nu_num_charged_particles = 0;

            // Nue Counter Variables
            int _mc_nue_cc_counter      = 0;
            int _mc_nue_cc_counter_bar  = 0;
            int _mc_numu_cc_counter     = 0;
            int _mc_numu_cc_counter_bar = 0;
            int _mc_nue_nc_counter      = 0;
            int _mc_nue_nc_counter_bar  = 0;
            int _mc_numu_nc_counter     = 0;
            int _mc_numu_nc_counter_bar = 0;
            
            // Vector to check if in TPC
            std::vector<bool> true_in_tpc_v;
            
            int total_mc_entries_inFV_nue         = 0;
            int total_mc_entries_inFV_nue_bar     = 0;
            int total_mc_entries_inFV_numu_cc     = 0;
            int total_mc_entries_inFV_nue_nc      = 0;
            int total_mc_entries_inFV_numu_nc     = 0;
            int total_mc_entries_inFV_numu_cc_bar = 0;
            int total_mc_entries_inFV_nue_nc_bar  = 0;
            int total_mc_entries_inFV_numu_nc_bar = 0;
            int total_mc_entries_inFV             = 0;



        public:
            // -----------------------------------------------------------------
            // Allow the utility class to modify the private member data of this class
            friend class utilityNS::utility;
            // -----------------------------------------------------------------
            // Function to Initialise the selection class ----------------------
            void Initialise( const char * mc_file,
                             const char * ext_file,
                             const char * data_file,
                             const char * dirt_file,
                             const char * variation_file,
                             const std::vector<double> _config,
                             bool _slim);
            // -----------------------------------------------------------------
            // Main function for selection
            void make_selection();
            // -----------------------------------------------------------------
            // Template code to apply selection cuts
            bool ApplyCuts(int type, int event, const xsecAna::TPCObjectContainer &tpc_obj,
                           std::vector<std::vector<double>> &largest_flash_v_v,
                           std::vector<std::vector<int>>    &optical_list_pe_v,
                           std::vector<std::vector<double>> &optical_list_flash_time_v,
                           std::vector<std::vector<double>> &counter_v,
                           std::vector<Passed_Container>    &passed_v);
            // -----------------------------------------------------------------
            // Function to save all written histograms to file
            void SavetoFile();
            // -----------------------------------------------------------------
            // Make final histogram plots
            void MakeHistograms();
            // -----------------------------------------------------------------

    }; // END Class

} // END NAMESPACE xsecSelection
#endif