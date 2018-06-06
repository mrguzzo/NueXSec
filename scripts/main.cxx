#include "main.h"

int main(int argc, char *argv[]){

	const char * file1 = argv[1];//mc
	const char * file2 = argv[2];//ext
	const char * file3 = argv[3];//on-beam data
	const char * input_config_file_name;

	bool using_default_config = true;
	bool using_slim_version = false;

	//start after name of .exe
	for(int i =1; i < argc; i++)
	{
		auto const arg = argv[i];
		std::cout << arg << std::endl; //this is for debugging
		if(strcmp(arg, "--slim") == 0)
		{
			using_slim_version = true;
			std::cout << " *** \t Running with Slimmed Selection \t *** " << std::endl;
		}
		if(strcmp(arg, "-c") == 0)
		{
			using_default_config = false;
			input_config_file_name = argv[i+1];
			//break; //is the break necessary?
		}
	}

	std::cout << "INPUT FORMAT: MC_FILE INTIME_FILE DATA_FILE" << std::endl;
	if(argc < 2 )  { std::cout << " \n Please inclue the input file path \n " << std::endl; exit(1); }

	std::vector<double> config;
	std::vector<double> input_config;

	xsecSelection::selection _selection_instance;
	xsecSelection::selection_slim _selection_slim_instance;

	std::vector<double> default_config = utility::configure_cuts(
	        _x1, _x2, _y1, _y2, _z1, _z2,
	        flash_pe_threshold,
	        flash_time_start,
	        flash_time_end,
	        tolerance,
	        shwr_nue_tolerance,
	        trk_nue_tolerance,
	        shwr_hit_threshold,
	        shwr_hit_threshold_collection,
	        tolerance_open_angle_min,
	        tolerance_open_angle_max,
	        tolerance_dedx_min,
	        tolerance_dedx_max,
	        dist_tolerance,
	        pfp_hits_length_tolerance,
	        ratio_tolerance
	        );

	std::ifstream input_config_file;
	//check if string for input file is empty -
	//if not empty try to open file
	if(using_default_config == false)
	{
		input_config_file.open(input_config_file_name);
		if(!input_config_file.is_open())
		{
			std::cout << "*** \t File did not open! \t ***" << std::endl;
			using_default_config = true;
		}
		if(input_config_file.is_open())
		{
			std::cout << "*** \t File Opened \t *** " << std::endl;
			std::string line;
			while (!input_config_file.eof())
			{
				std::getline (input_config_file, line);
				if(!line.empty())
				{
					input_config.push_back(std::stof(line));
				}
			}
			input_config_file.close();
			std::cout << "*** \t File Closed \t *** " << std::endl;
		}
	}

	if(using_default_config == true)  {config = default_config; }
	if(using_default_config == false) {config = input_config; }

	std::vector<std::tuple<double, double, std::string> > * results_v = new std::vector<std::tuple<double, double, std::string> >;

	double _argc = argc;
	if(using_slim_version == true)    {_argc = _argc - 1; }//this is to account for the "--slim"
	if(using_default_config == false) {_argc = _argc - 2; }//this is to account for the "-c" and "config_file"

	if(_argc == 2)
	{
		std::cout << "Running without in-time cosmics " << std::endl;
		std::cout << "Running without data" << std::endl;
		if(using_slim_version == false) {_selection_instance.xsecSelection::selection::make_selection(file1, "empty", "empty", config, results_v); }
		if(using_slim_version == true)  {_selection_slim_instance.xsecSelection::selection_slim::make_selection_slim(file1, "empty", "empty", config, results_v); }
	}
	if(_argc == 3)
	{
		std::cout << "Running without data " << std::endl;
		if(using_slim_version == false) {_selection_instance.xsecSelection::selection::make_selection(file1, file2, "empty", config, results_v); }
		if(using_slim_version == true)  {_selection_slim_instance.xsecSelection::selection_slim::make_selection_slim(file1, file2, "empty", config, results_v); }
	}
	if(_argc == 4)
	{
		std::cout << "Running with MC, EXT, and Data" << std::endl;
		if(using_slim_version == false) {_selection_instance.xsecSelection::selection::make_selection(file1, file2, file3, config, results_v); }
		if(using_slim_version == true)  {_selection_slim_instance.xsecSelection::selection_slim::make_selection_slim(file1, file2, file3, config, results_v); }
	}


	//write results from selection to output file
	//python script does most of the file managing, since script needs to be contained
	std::ofstream output_file;
	const char * output_file_name = "selection_output.txt"; //I'll expand this to also come from the python script
	output_file.open(output_file_name, std::ios_base::app); //Only append to this file
	if(!output_file.is_open())
	{
		std::cout << "*** \t Output File did not open! \t ***" << std::endl;
	}
	if(output_file.is_open())
	{
		std::cout << "*** \t Output File Opened \t *** " << std::endl;

		for(auto const results : * results_v)
		{
			output_file << std::get<2>(results) << ", "
			            << std::get<0>(results) << ", "
			            << std::get<1>(results) << "\n";
		}
		input_config_file.close();
		std::cout << "*** \t Output File Closed \t *** " << std::endl;
	}

	std::cout << "*** \t Exiting C++ Code... \t *** " << std::endl;
	return 0;
}
