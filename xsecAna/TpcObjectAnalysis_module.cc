////////////////////////////////////////////////////////////////////////
// Class:       TpcObjectAnalysis
// Module Type: analyzer
// File:        TpcObjectAnalysis_module.cc
//
// Generated at Wed Sep 13 14:53:48 2017 by Colton Hill using artmod
// from cetpkgsupport v1_12_02.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "larsim/MCCheater/BackTracker.h"
#include "lardataobj/RecoBase/OpFlash.h"


#include "TpcObjectContainer.h"
#include "ParticleContainer.h"
#include "UtilityFunctions.h"
#include "AnaHelper.h"
#include "MCGhost.h"
#include "PostMCCorrections.h"
#include "TPCObject.h"
#include "GeometryHelper.h"

#include <fstream>
#include <iostream>
#include <string>
#include <map>

namespace xsecAna {
class TpcObjectAnalysis;
}

class xsecAna::TpcObjectAnalysis : public art::EDAnalyzer {
public:
explicit TpcObjectAnalysis(fhicl::ParameterSet const & p);
// The destructor generated by the compiler is fine for classes
// without bare pointers or other resource use.

// Plugins should not be copied or assigned.
TpcObjectAnalysis(TpcObjectAnalysis const &) = delete;
TpcObjectAnalysis(TpcObjectAnalysis &&) = delete;
TpcObjectAnalysis & operator = (TpcObjectAnalysis const &) = delete;
TpcObjectAnalysis & operator = (TpcObjectAnalysis &&) = delete;

// Required functions.
void analyze(art::Event const & e) override;
void endSubRun(art::SubRun const &sr) override;


private:

// Declare member data here.

//these are used for the dQdx calculations
xsecAna::GeometryHelper geoHelper;
const double _dQdxRectangleLength = 4; //cm
const double _dQdxRectangleWidth = 1; //cm

//these should be art::InputTag
//but several pandora functions want strings!
std::string _pfp_producer;
std::string _mc_ghost_producer;
std::string _tpcobject_producer;

bool _debug;
bool _verbose;
bool _cosmic_only;
bool _save_truth_info;

bool isMC;
bool isData;

TTree * myTree;
std::vector<xsecAna::TPCObjectContainer> tpc_object_container_v;

int run;
int event;
itn subrun;

TTree * optical_tree;
int fEvent;
int fRun;
int fOpFlashPE;
double fOpFlashTime;
double fOpFlashWidthY;
double fOpFlashWidthZ;
double fOpFlashCenterY;
double fOpFlashCenterZ;

TTree * mcparticle_tree;
int fMcparticle_pdg = 0;
int fStatusCode = 0;
double fMCVtxX = 0.0;
double fMCVtxY = 0.0;
double fMCVtxZ = 0.0;
double fMCEnergy = 0.0;
double fMCMass = 0.0;
double fMCPx = 0.0;
double fMCPy = 0.0;
double fMCPz = 0.0;
int fMCParticleID = 0;
int fMCMother = -1;
int fMCOrigin = -1;

TTree * mctruth_counter_tree;
int mc_nue_cc_counter = 0;
int mc_numu_cc_counter = 0;
int mc_nue_nc_counter = 0;
int mc_numu_nc_counter = 0;

int mc_nue_cc_counter_bar = 0;
int mc_numu_cc_counter_bar = 0;
int mc_nue_nc_counter_bar = 0;
int mc_numu_nc_counter_bar = 0;

double fMCNuVtxX = -999;
double fMCNuVtxY = -999;
double fMCNuVtxZ = -999;
double fMCEleDirX = -999;
double fMCEleDirY = -999;
double fMCEleDirZ = -999;
double fMCNuEnergy = -1;
double fMCNuMomentum = -1;
double fMCEleEnergy = -1;
double fMCEleMomentum = -1;
int fMCNuID = -1;

double fMCNuDirX = -1;
double fMCNuDirY = -1;
double fMCNuDirZ = -1;

int fMCNumParticles = 0;
int fMCNumChargedParticles = 0;
bool has_pi0 = false;
double fMCNuTime = -1;

};


xsecAna::TpcObjectAnalysis::TpcObjectAnalysis(fhicl::ParameterSet const & p)
	:
	EDAnalyzer(p),
	_pfp_producer(p.get<std::string>("PFParticleProducer")),
	_mc_ghost_producer(p.get<std::string>("MCGhostProducer")),
	_tpcobject_producer(p.get<std::string>("TPCObjectProducer"))
// More initializers here.
{
	art::ServiceHandle<art::TFileService> fs;

	myTree = fs->make<TTree>("tree","");
	myTree->Branch("TpcObjectContainerV", &tpc_object_container_v);

	optical_tree = fs->make<TTree>("optical_tree", "optical_objects");
	optical_tree->Branch("Event",           &fEvent,                "fEvent/I");
	optical_tree->Branch("Run",             &fRun,                  "fRun/I");
	optical_tree->Branch("OpFlashPE",        &fOpFlashPE,           "fOpFlashPE/I");
	optical_tree->Branch("OpFlashTime",      &fOpFlashTime,         "fOpFlashTime/D");
	optical_tree->Branch("OpFlashWidhtY",    &fOpFlashWidthY,       "fOpFlashWidthY/D");
	optical_tree->Branch("OpFlashWidthZ",    &fOpFlashWidthZ,       "fOpFlashWidthZ/D");
	optical_tree->Branch("OpFlashCenterY",   &fOpFlashCenterY,      "fOpFlashCenterY/D");
	optical_tree->Branch("OpFlashCenterZ",   &fOpFlashCenterZ,      "fOpFlashCenterZ/D");

	mcparticle_tree = fs->make<TTree>("mcparticle_tree", "mcparticle_objects");
	mcparticle_tree->Branch("event", &event, "event/I");
	mcparticle_tree->Branch("run", &run, "run/I");
	mcparticle_tree->Branch("MC_ID", &fMCParticleID, "fMCParticleID/I");
	mcparticle_tree->Branch("MC_Mother", &fMCMother, "fMCMother/I");
	mcparticle_tree->Branch("MC_Origin", &fMCOrigin, "fMCOrigin/I");
	mcparticle_tree->Branch("StatusCode", &fStatusCode, "fStatusCode/I");
	mcparticle_tree->Branch("MC_PDG", &fMcparticle_pdg, "fMcparticle_pdg/I");
	mcparticle_tree->Branch("MCVtxX", &fMCVtxX, "fMCVtxX/D");
	mcparticle_tree->Branch("MCVtxY", &fMCVtxY, "fMCVtxY/D");
	mcparticle_tree->Branch("MCVtxZ", &fMCVtxZ, "fMCVtxZ/D");
	mcparticle_tree->Branch("MCEnergy", &fMCEnergy, "fMCEnergy/D");
	mcparticle_tree->Branch("MCMass", &fMCMass, "MCMass/D");
	mcparticle_tree->Branch("MCPx", &fMCPx, "MCPx/D");
	mcparticle_tree->Branch("MCPy", &fMCPy, "MCPy/D");
	mcparticle_tree->Branch("MCPz", &fMCPz, "MCPz/D");

	mctruth_counter_tree = fs->make<TTree>("mctruth_counter_tree", "mctruth_counter");
	mctruth_counter_tree->Branch("mc_nue_cc_counter", &mc_nue_cc_counter, "mc_nue_cc_counter/I");
	mctruth_counter_tree->Branch("mc_numu_cc_counter", &mc_numu_cc_counter, "mc_numu_cc_counter/I");
	mctruth_counter_tree->Branch("mc_nue_nc_counter", &mc_nue_nc_counter, "mc_nue_nc_counter/I");
	mctruth_counter_tree->Branch("mc_numu_nc_counter", &mc_numu_nc_counter, "mc_numu_nc_counter/I");

	mctruth_counter_tree->Branch("mc_nue_cc_counter_bar", &mc_nue_cc_counter_bar, "mc_nue_cc_counter/I");
	mctruth_counter_tree->Branch("mc_numu_cc_counter_bar", &mc_numu_cc_counter_bar, "mc_numu_cc_counter/I");
	mctruth_counter_tree->Branch("mc_nue_nc_counter_bar", &mc_nue_nc_counter_bar, "mc_nue_nc_counter_bar/I");
	mctruth_counter_tree->Branch("mc_numu_nc_counter_bar", &mc_numu_nc_counter_bar, "mc_numu_cc_counter/I");

	mctruth_counter_tree->Branch("fMCNuVtxX", &fMCNuVtxX, "fMCNuVtxX/D");
	mctruth_counter_tree->Branch("fMCNuVtxY", &fMCNuVtxY, "fMCNuVtxY/D");
	mctruth_counter_tree->Branch("fMCNuVtxZ", &fMCNuVtxZ, "fMCNuVtxZ/D");
	mctruth_counter_tree->Branch("fMCNuEnergy", &fMCNuEnergy, "fMCNuEnergy/D");
	mctruth_counter_tree->Branch("fMCNuMomentum", &fMCNuMomentum, "fMCNuMomentum/D");
	mctruth_counter_tree->Branch("fMCNuID", &fMCNuID, "fMCNuID/I");
	mctruth_counter_tree->Branch("fMCNuDirX", &fMCNuDirX, "fMCNuDirX/D");
	mctruth_counter_tree->Branch("fMCNuDirY", &fMCNuDirY, "fMCNuDirY/D");
	mctruth_counter_tree->Branch("fMCNuDirZ", &fMCNuDirZ, "fMCNuDirZ/D");
	mctruth_counter_tree->Branch("fMCEleDirX", &fMCEleDirX, "fMCEleDirX/D");
	mctruth_counter_tree->Branch("fMCEleDirY", &fMCEleDirY, "fMCEleDirY/D");
	mctruth_counter_tree->Branch("fMCEleDirZ", &fMCEleDirZ, "fMCEleDirZ/D");
	mctruth_counter_tree->Branch("fMCEleEnergy", &fMCEleEnergy, "fMCEleEnergy/D");
	mctruth_counter_tree->Branch("fMCEleMomentum", &fMCEleMomentum, "fMCEleMomentum/D");
	mctruth_counter_tree->Branch("fMCNumParticles", &fMCNumParticles, "fMCNumParticles/I");
	mctruth_counter_tree->Branch("fMCNumChargedParticles", &fMCNumChargedParticles, "fMCNumChargedParticles/I");
	mctruth_counter_tree->Branch("has_pi0", &has_pi0, "has_pi0/O");
	mctruth_counter_tree->Branch("fMCNuTime", &fMCNuTime, "fMCNuTime/D");

	_debug                          = p.get<bool>("Debug", false);
	_verbose                        = p.get<bool>("Verbose", false);
	_cosmic_only                    = p.get<bool>("CosmicOnly", false);
	//we set this to be false by default, as it severely inflates the size of
	//of the output file.
	//Instead we just count the most important truth events.
	_save_truth_info                = p.get<bool>("SaveTruthInfo", false);

}

void xsecAna::TpcObjectAnalysis::analyze(art::Event const & e)
{

	run = e.id().run();
	event = e.id().event();
	subrun = e.id().subRun();
	bool _is_data = e.isRealData();
	bool _is_mc = !_is_data;
	if(_cosmic_only == true) {std::cout << "[Analyze] Running in Cosmic Only Configuration! " << std::endl; }
	if(_is_mc == true)       {std::cout << "[Analyze] Running with Monte Carlo " << std::endl; }
	if(_is_data == true)     {std::cout << "[Analyze] Running with Data " << std::endl; }

	//maybe make them filled at the same place as the other - so it's a per event
	//this is getting the optical information
	std::string beam_flash_tag = "simpleFlashBeam";
	auto const & beam_opf = e.getValidHandle<std::vector < recob::OpFlash> >(beam_flash_tag);
	auto const & beam_opflashes(*beam_opf);
	std::cout << "[Analyze] [OPTICAL] " << beam_flash_tag << " in this event: " << beam_opflashes.size() << std::endl;

	//if there is no optical activity in this event then I don't care about it
	if(beam_opflashes.size() == 0) { std::cout << "[Analyze] [Optical] No Optical Activity in this Event!" << std::endl; return; }

	for(auto const & opflsh : beam_opflashes)
	{
		fEvent = event;
		fRun = run;
		fOpFlashPE   = opflsh.TotalPE();
		fOpFlashTime = opflsh.Time();
		fOpFlashWidthY  = opflsh.YWidth();
		fOpFlashWidthZ  = opflsh.ZWidth();
		fOpFlashCenterY = opflsh.YCenter();
		fOpFlashCenterZ =opflsh.ZCenter();
		optical_tree->Fill();
	}
	//there are so may mc particles -- why?
	//MC Particle Information
	art::ServiceHandle<cheat::BackTracker> bt;
	art::Handle < std::vector < simb::MCParticle > > MCParticleHandle;
	if(_is_mc == true)
	{
		e.getByLabel("largeant", MCParticleHandle);
		if(!MCParticleHandle.isValid() && _cosmic_only == false) {std::cout << "[Analyze] Handle is not valid" << std::endl; exit(1); }
	}

	//I need the MC Track for later - getting cosmic info from MCParticle->MCTrack
	//std::string mc_track_tag = "mcreco";
	//art::FindManyP<sim::MCTrack> mctracks_from_mcparticle(MCParticleHandle, e, mc_track_tag);
	//MCTrack association not there!

	if(_cosmic_only == false && _is_mc == true)
	{
		std::cout << "[Analyze] [MCPARTICLE] largeant in this event: " << MCParticleHandle->size() << std::endl;
		if(_save_truth_info == true)
		{
			std::cout << "[Analyze] [MCPARTICLE] Saving MC Truth Tree Configuration" << std::endl;
			std::cout << "[Analyze] [MCPARTICLE] This inflates the output file size!" << std::endl;
		}

		bool event_neutrino = false;
		int mc_num_particles = 0;
		int mc_num_charged_particles = 0;
		has_pi0 = false;

		for(auto const & mcparticle : (*MCParticleHandle) )
		{
			const art::Ptr<simb::MCTruth> mctruth = bt->TrackIDToMCTruth(mcparticle.TrackId());
			if(mctruth->Origin() == simb::kBeamNeutrino) {fMCOrigin = 0; }
			if(mctruth->Origin() == simb::kCosmicRay) {fMCOrigin = 1; }
			if(mctruth->Origin() == simb::kUnknown) {fMCOrigin = 2; }
			simb::MCNeutrino mc_nu = mctruth->GetNeutrino();
			bool fCCNC = mc_nu.CCNC(); //0 is CC, 1 is NC
			int fMCNuPdg = mc_nu.Nu().PdgCode();
			fMCParticleID = mcparticle.TrackId();
			fMCMother = mcparticle.Mother();
			fMcparticle_pdg = mcparticle.PdgCode();
			fStatusCode = mcparticle.StatusCode();
			fMCVtxX = mcparticle.Vx();
			fMCVtxY = mcparticle.Vy();
			fMCVtxZ = mcparticle.Vz();
			fMCEnergy = mcparticle.E();
			fMCMass = mcparticle.Mass();
			fMCPx = mcparticle.Px();
			fMCPy = mcparticle.Py();
			fMCPz = mcparticle.Pz();
			if(_save_truth_info == true) {mcparticle_tree->Fill(); }
			if(fMCMother == 0 && mctruth->Origin() == simb::kBeamNeutrino && event_neutrino == false)
			{
				//std::cout << fMCParticleID << '\t';
				//std::cout << fMCNuPdg << '\t';
				if(fMCNuPdg == 12  && fCCNC == 0) {mc_nue_cc_counter++;      fMCNuID = 1; }
				if(fMCNuPdg == 14  && fCCNC == 0) {mc_numu_cc_counter++;     fMCNuID = 2; }
				if(fMCNuPdg == 12  && fCCNC == 1) {mc_nue_nc_counter++;      fMCNuID = 3; }
				if(fMCNuPdg == 14  && fCCNC == 1) {mc_numu_nc_counter++;     fMCNuID = 4; }
				if(fMCNuPdg == -12 && fCCNC == 0) {mc_nue_cc_counter_bar++;  fMCNuID = 5; }
				if(fMCNuPdg == -14 && fCCNC == 0) {mc_numu_cc_counter_bar++; fMCNuID = 6; }
				if(fMCNuPdg == -12 && fCCNC == 1) {mc_nue_nc_counter_bar++;  fMCNuID = 7; }
				if(fMCNuPdg == -14 && fCCNC == 1) {mc_numu_nc_counter_bar++; fMCNuID = 8; }
				//this loop is only enerted once per event, assuming 1 nu event per event.
				//this way we get the neutrino vertex and energy per event and can use this
				//to calculate if it's in the FV in the future, during the selection.
				fMCNuVtxX     = mc_nu.Nu().Vx();
				fMCNuVtxY     = mc_nu.Nu().Vy();
				fMCNuVtxZ     = mc_nu.Nu().Vz();
				fMCNuEnergy   = mc_nu.Nu().E();
				fMCNuMomentum = mc_nu.Nu().P();
				fMCNuDirX     = (mc_nu.Nu().Px() / mc_nu.Nu().P());
				fMCNuDirY     = (mc_nu.Nu().Py() / mc_nu.Nu().P());
				fMCNuDirZ     = (mc_nu.Nu().Pz() / mc_nu.Nu().P());
				fMCEleDirX     = (mc_nu.Lepton().Px() / mc_nu.Lepton().P());
				fMCEleDirY     = (mc_nu.Lepton().Py() / mc_nu.Lepton().P());
				fMCEleDirZ     = (mc_nu.Lepton().Pz() / mc_nu.Lepton().P());
				fMCEleEnergy   = mc_nu.Lepton().E();
				fMCEleMomentum = mc_nu.Lepton().P();
				fMCNuTime      = mc_nu.Nu().Trajectory().T(0);
				event_neutrino = true;
			}
			//this should only give the stable final state particles
			if(fMCMother == 0 && mctruth->Origin() == simb::kBeamNeutrino && mcparticle.StatusCode() == 1)
			{
				mc_num_particles++;
				if(_verbose) {std::cout << " [MCTruth] Stable Final State Particles " << fMcparticle_pdg << std::endl; }
				if(fMcparticle_pdg == 111)
				{
					has_pi0 = true;
					if(_verbose) {std::cout << " [MCTruth] Event has Neutrino Induced Pi0" << std::endl; }
				}
				if(fMcparticle_pdg == 11  || fMcparticle_pdg == 13   || fMcparticle_pdg == -11  || fMcparticle_pdg == -13 ||
				   fMcparticle_pdg == 211 || fMcparticle_pdg == -211 || fMcparticle_pdg == 2212 || fMcparticle_pdg == 321 || fMcparticle_pdg == -321)
				{
					mc_num_charged_particles++;
				}
			}
		}//end loop mc particles
		fMCNumParticles = mc_num_particles;
		fMCNumChargedParticles = mc_num_charged_particles;
		std::cout << "MC Num Particles: " << mc_num_particles << std::endl;
		mctruth_counter_tree->Fill();
	}

	// Implementation of required member function here.

	if(!tpc_object_container_v.empty()) {tpc_object_container_v.clear(); }

	// Get PFP
	art::Handle<std::vector<recob::PFParticle> > pfp_h;
	e.getByLabel(_pfp_producer,pfp_h);
	if(!pfp_h.isValid())
	{
		std::cout << "[Analyze] PFP product " << _pfp_producer << " not found..." << std::endl;
		//throw std::exception();
	}
	if(pfp_h->empty())
	{
		std::cout << "[Analyze] PFP " << _pfp_producer << " is empty." << std::endl;
	}
	art::FindManyP<recob::Track> tracks_from_pfp(pfp_h, e, _pfp_producer);
	art::FindManyP<recob::Shower> showers_from_pfp(pfp_h, e, _pfp_producer);

	//Need to get clusters for dQ/dX
	art::Handle<std::vector<recob::Cluster > > cluster_h;
	e.getByLabel(_pfp_producer, cluster_h);
	if(!cluster_h.isValid()) {std::cout << "[Analyze] Cannot locate recob::Cluster. " << std::endl; }

	art::FindManyP<recob::Cluster> clusters_from_pfpart(pfp_h, e, _pfp_producer);
	art::FindManyP<recob::Hit> hits_from_clusters(cluster_h, e, _pfp_producer);
	//making a map of clusters to hit vectors
	std::map < art::Ptr< recob::Cluster>, std::vector<art::Ptr < recob::Hit> > > ClusterToHitsMap;
	std::vector<art::Ptr<recob::Cluster> > cluster_v;
	art::fill_ptr_vector(cluster_v, cluster_h);
	for(auto const cluster : cluster_v )
	{
		std::vector<art::Ptr<recob::Hit> > hits_v = hits_from_clusters.at(cluster.key());
		ClusterToHitsMap.insert(std::make_pair(cluster, hits_v));
	}

	// Get TPCObjects from the Event
	art::Handle<std::vector<xsecAna::TPCObject> > tpcobj_h;
	e.getByLabel(_tpcobject_producer, tpcobj_h);
	if (!tpcobj_h.isValid()) {std::cout << "[Analyze] Cannote locate xsecAna::TPCObject." << std::endl; }

	// Get Ghosts
	art::Handle<std::vector<xsecAna::MCGhost> > ghost_h;
	e.getByLabel(_mc_ghost_producer,ghost_h);
	if(!ghost_h.isValid()) {
		std::cout << "[Analyze] MCGhost product " << _mc_ghost_producer << " not found..." << std::endl;
		//throw std::exception();
	}
	art::FindManyP<xsecAna::MCGhost>   mcghost_from_pfp   (pfp_h,   e, _mc_ghost_producer);
	art::FindManyP<simb::MCParticle> mcpar_from_mcghost (ghost_h, e, _mc_ghost_producer);

	//art::FindManyP<xsecAna::FlashMatch> tpcobjToFlashMatchAssns(tpcobj_h, e, _neutrino_flash_match_producer);
	art::FindManyP<recob::Track>      tpcobjToTrackAssns(tpcobj_h, e, _tpcobject_producer);
	art::FindManyP<recob::Shower>     tpcobjToShowerAssns(tpcobj_h, e, _tpcobject_producer);
	art::FindManyP<recob::PFParticle> tpcobjToPFPAssns(tpcobj_h, e, _tpcobject_producer);

	if(_verbose) {std::cout << "[Analyze] TPC Objects in this Event: " << tpcobj_h->size() << std::endl; }
	//loop over all of the tpc objects!

	int tpc_object_counter = 0;
	for(size_t tpc_counter = 0; tpc_counter < tpcobj_h->size(); tpc_counter++)
	{
		if(_verbose) {std::cout << "[Analyze] TPC Object Number: " << tpc_counter << std::endl; }
		const xsecAna::TPCObject tpcobj = (*tpcobj_h)[tpc_counter];
		const int ntracks                   = tpcobj.GetNTracks();
		const int nshowers                  = tpcobj.GetNShowers();
		const int npfparticles              = tpcobj.GetNPFP();
		const simb::Origin_t tpcobj_origin  = tpcobj.GetOrigin();
		const std::vector<recob::PFParticle> pfp_v = tpcobj.GetPFPs();
		const std::vector<art::Ptr<recob::Track>  >  track_v  = tpcobj.GetTracks();
		const std::vector<art::Ptr<recob::Shower> > shower_v  = tpcobj.GetShowers();

		if(_verbose)
		{
			std::cout << "[Analyze] N PFPs   : " << npfparticles << std::endl;
			std::cout << "[Analyze] N Tracks : " << ntracks << std::endl;
			std::cout << "[Analyze] N Showers: " << nshowers << std::endl;
		}

		// Reco vertex
		double reco_nu_vtx[3];
		//set to default values
		reco_nu_vtx[0] = -999;
		reco_nu_vtx[1] = -999;
		reco_nu_vtx[2] = -999;
		recob::Vertex tpcobj_nu_vtx = tpcobj.GetVertex();
		tpcobj_nu_vtx.XYZ(reco_nu_vtx);
		const double pfp_nu_vtx_x = reco_nu_vtx[0];
		const double pfp_nu_vtx_y = reco_nu_vtx[1];
		const double pfp_nu_vtx_z = reco_nu_vtx[2];
		//_slc_nuvtx_fv[slice] = (UBXSecHelper::InFV(reco_nu_vtx) ? 1 : 0);

		int n_pfp_tracks = 0;
		int n_pfp_showers = 0;

		xsecAna::TPCObjectContainer tpc_object_container;
		tpc_object_container.SetpfpVtxX(pfp_nu_vtx_x);
		tpc_object_container.SetpfpVtxY(pfp_nu_vtx_y);
		tpc_object_container.SetpfpVtxZ(pfp_nu_vtx_z);
		tpc_object_container.SetRunNumber(run);
		tpc_object_container.SetIsData(_is_data);
		tpc_object_container.SetSubRunNumber(subrun);
		tpc_object_container.SetEventNumber(event);
		tpc_object_container.SetIndex(tpc_object_counter);
		//convert simb::Origin_t object to std::string
		std::string str_origin = "kUnset";
		if(tpcobj_origin == simb::kUnknown) {str_origin = "kUnknown"; }
		if(tpcobj_origin == simb::kBeamNeutrino) {str_origin = "kBeamNeutrino"; }
		if(tpcobj_origin == simb::kCosmicRay) {str_origin = "kCosmicRay"; }
		tpc_object_container.SetOrigin(str_origin);

		if(_verbose) {std::cout << "[Analyze] Number of PFP in this TPC Object: " << npfparticles << std::endl; }
		tpc_object_container.SetNumPFParticles(npfparticles);

		// Hits - we want the hits from both tracks and showers
		int nhits_u = 0;
		int nhits_v = 0;
		int nhits_w = 0;
		int total_nhits_u = 0;
		int total_nhits_v = 0;
		int total_nhits_w = 0;
		int total_nhits = 0;
		//need to sum all hits from both tracks and showers
		for(auto const track : track_v)
		{
			//art::Ptr<recob::Track> & _track = track;
			xsecAna::utility::GetNumberOfHitsPerPlane(e, _pfp_producer, track, nhits_u, nhits_v, nhits_w);
			total_nhits_u += nhits_u;
			total_nhits_v += nhits_v;
			total_nhits_w += nhits_w;
		}
		for(auto const shower : shower_v)
		{
			//art::Ptr<recob::Shower> & _shower = shower;
			xsecAna::utility::GetNumberOfHitsPerPlane(e, _pfp_producer, shower, nhits_u, nhits_v, nhits_w);
			total_nhits_u += nhits_u;
			total_nhits_v += nhits_v;
			total_nhits_w += nhits_w;
		}
		total_nhits = (total_nhits_u + total_nhits_v + total_nhits_w);

		tpc_object_container.SetNumPFPHits   (total_nhits);
		tpc_object_container.SetNumPFPHitsU  (total_nhits_u);
		tpc_object_container.SetNumPFPHitsV  (total_nhits_v);
		tpc_object_container.SetNumPFPHitsW  (total_nhits_w);

		int pfp_nu_counter = 0;
		//int pfpNuPdg = 0;//not set
		int pfpParentPdg = 0;
		int mode = -1;
		int ccnc = -1;
		int tpco_mc_pdg  = -1;
		int tpco_pfp_pdg = -1;
		bool is_neutrino = false;
		//bool is_primary = false; // not set

		//****************************************
		//loop over pfparticles in the tpc object
		//****************************************
		auto pfps_from_tpcobj = tpcobjToPFPAssns.at(tpc_object_counter);
		for(auto const pfp : pfps_from_tpcobj)
		//for(auto const pfp : pfp_v)
		{
			std::cout << "[Analyze] PFParticles " << std::endl;
			xsecAna::ParticleContainer particle_container;

			int mcPdg = 0;
			//int mcNuPdg = 0; // not set
			int mcParentPdg = 0;
			double pfp_dir_x = 0;
			double pfp_dir_y = 0;
			double pfp_dir_z = 0;
			double pfp_theta = 0;
			double pfp_phi = 0;
			double pfp_length = 0;
			double pfp_momentum = 0;
			int pfp_hits = 0;
			int pfp_hits_u = 0;
			int pfp_hits_v = 0;
			int pfp_hits_w = 0;
			double pfp_open_angle = 0;

			double mc_vtx_x = -999;
			double mc_vtx_y = -999;
			double mc_vtx_z = -999;
			double mc_dir_x = 0;
			double mc_dir_y = 0;
			double mc_dir_z = 0;
			double mc_theta = 0;
			double mc_phi = 0;
			double mcLength = 0;
			double mcEnergy = 0;
			double mcMomentum = 0;
			double mcNeutrinoEnergy = 0;
			int particle_mode = -1;
			int particle_is_cc = -1;
			//double mc_open_angle = 0; //unset
			std::vector<art::Ptr<recob::Cluster> > clusters = clusters_from_pfpart.at(pfp.key());
			const int num_clusters = clusters.size();
			std::vector < std::vector< double > > shower_cluster_dqdx;
			shower_cluster_dqdx.resize(num_clusters);
			for(int clust = 0; clust < num_clusters; clust++)
			{
				shower_cluster_dqdx.at(clust).resize(3);
				shower_cluster_dqdx.at(clust).at(0) = 0;
				shower_cluster_dqdx.at(clust).at(1) = 0;
				shower_cluster_dqdx.at(clust).at(2) = 0;
			}
			std::vector<double> shower_dEdx;
			shower_dEdx.resize(3);
			shower_dEdx.at(0) = 0;
			shower_dEdx.at(1) = 0;
			shower_dEdx.at(2) = 0;

			const int pfpPdg = pfp->PdgCode();
			//if(_verbose) {std::cout << "[Analyze] PFP PDG Code " << pfpPdg << std::endl; }
			const unsigned int pfpParent_id = pfp->Parent();
			int position = 0;
			int parent_position = -1;
			for(auto const parent_search : pfps_from_tpcobj)
			{
				if(parent_search->Self() == pfpParent_id ) {parent_position = position; }
				position++;
			}
			if(parent_position != -1)
			{
				try
				{
					auto const pfpParent_obj = pfps_from_tpcobj.at(parent_position);
					pfpParentPdg = pfpParent_obj->PdgCode();
				}
				catch(...) {std::cout << "[Analyze] [EXCEPTION] No Parent Found!" << std::endl; }
			}
			//if(_verbose) {std::cout << "[Analyze] PFP Parent PDG Code " << pfpParentPdg << std::endl; }
			particle_container.SetpfpPdgCode(pfpPdg);
			//particle_container.SetpfpNuPdgCode(pfpParentPdg); //this will sometimes be a neutrino and sometimes not!
			particle_container.SetpfpParentPdgCode(pfpParentPdg);
			const int index = pfp->Self();
			particle_container.SetIndex(index);
			simb::Origin_t mcOrigin = simb::kUnknown;

			if(pfpPdg == 12 || pfpPdg == 14) {
				if(_verbose) {std::cout << "[Analyze] PFP Neutrino with PDG Code: " << pfpPdg << std::endl; }
				is_neutrino = true;
				tpco_pfp_pdg = pfpPdg;
				pfp_nu_counter++;
			}
			particle_container.SetIsNeutrino(is_neutrino);

			// Reco vertex
			lar_pandora::VertexVector vertexVector;
			lar_pandora::PFParticlesToVertices particlesToVertices;
			lar_pandora::LArPandoraHelper::CollectVertices(e, _pfp_producer, vertexVector, particlesToVertices);

			auto iter = particlesToVertices.find(pfp);
			//auto iter = pfParticleToVertexMap.find(pfp);
			double pfp_vtx_x = -999;
			double pfp_vtx_y = -999;
			double pfp_vtx_z = -999;
			if (iter != particlesToVertices.end())
			{
				lar_pandora::VertexVector vertex_v = particlesToVertices.find(pfp)->second;
				double reco_vtx[3];
				vertex_v[0]->XYZ(reco_vtx);
				pfp_vtx_x = reco_vtx[0];
				pfp_vtx_y = reco_vtx[1];
				pfp_vtx_z = reco_vtx[2];
			}
			particle_container.SetpfpVtxX(pfp_vtx_x);
			particle_container.SetpfpVtxY(pfp_vtx_y);
			particle_container.SetpfpVtxZ(pfp_vtx_z);

			//mcghosts do accounting for pfp to mcghost to mc particle
			const std::vector<art::Ptr<MCGhost> > mcghost = mcghost_from_pfp.at(pfp.key());
			std::vector<art::Ptr<simb::MCParticle> > mcpart;
			if(mcghost.size() == 0) {std::cout << "[Analyze] No matched MC Ghost to PFP!" << std::endl; }
			//we don't want to just throw these events out!
			if(mcghost.size() > 1)
			{
				if(_verbose) {std::cout << "[Analyze] Too many matched MC Ghost to PFP!" << std::endl; }
			}//end if 2+ MC Ghost
			if(mcghost.size() >= 1)
			{
				if(_verbose) {std::cout << "[Analyze] One MC Ghost Found!" << std::endl; }
				mcpart = mcpar_from_mcghost.at(mcghost[0].key());
				const art::Ptr<simb::MCParticle> the_mcpart = mcpart.at(0);
				const art::Ptr<simb::MCTruth> mctruth = bt->TrackIDToMCTruth(the_mcpart->TrackId());
				simb::MCNeutrino mc_nu;
				if(!mctruth) {std::cout << "[Analyze] MCTruth Pointer Not Valid!" << std::endl; }
				else
				{
					mc_nu = mctruth->GetNeutrino();
					mcOrigin = mctruth->Origin();
				}
				if(mcOrigin != simb::kCosmicRay)
				{
					mode = mc_nu.Mode();
					ccnc = mc_nu.CCNC();
					mcParentPdg = mc_nu.Nu().PdgCode();
					mcNeutrinoEnergy = mc_nu.Nu().E();
					mc_vtx_x = the_mcpart->Vx();
					mc_vtx_y = the_mcpart->Vy();
					mc_vtx_z = the_mcpart->Vz();
				}
				//if(mcOrigin == simb::kCosmicRay)
				//{
				//std::vector<art::Ptr<sim::MCTrack> > mc_tracks = mctracks_from_mcparticle.at(the_mcpart.key());
				//if(mc_tracks.size() == 1)
				//{
				//	mc_vtx_x = mc_tracks.at(0)->Start().X();
				//	mc_vtx_y = mc_tracks.at(0)->Start().Y();
				//	mc_vtx_z = mc_tracks.at(0)->Start().Z();
				//	//I can include the length and directions here!
				//}
				//}
				particle_mode = mode;
				particle_is_cc = ccnc;
				mcPdg = the_mcpart->PdgCode();
				if(is_neutrino == true) {tpco_mc_pdg = mcPdg; }
				mcMomentum = the_mcpart->P();
				mc_dir_x = the_mcpart->Px() / mcMomentum;
				mc_dir_y = the_mcpart->Py() / mcMomentum;
				mc_dir_z = the_mcpart->Pz() / mcMomentum;
				mc_theta = acos(mc_dir_z) * (180 / 3.1415);
				mc_phi = atan2(mc_dir_y, mc_dir_x) * (180 / 3.1415);
				const double mc_length_x = the_mcpart->Position().X() - the_mcpart->EndPosition().X();
				const double mc_length_y = the_mcpart->Position().Y() - the_mcpart->EndPosition().Y();
				const double mc_length_z = the_mcpart->Position().Z() - the_mcpart->EndPosition().Z();
				mcLength = sqrt((mc_length_x * mc_length_x) + (mc_length_y * mc_length_y) + (mc_length_z * mc_length_z));
				mcEnergy = the_mcpart->E();


			}//end mcghost == 1
			particle_container.SetmcPdgCode(mcPdg);
			//convert simb::Origin_t to std::string
			std::string str_mcorigin;
			if(mcOrigin == simb::kUnknown) {str_mcorigin = "kUnknown"; }
			if(mcOrigin == simb::kBeamNeutrino) {str_mcorigin = "kBeamNeutrino"; }
			if(mcOrigin == simb::kCosmicRay) {str_mcorigin = "kCosmicRay"; }
			particle_container.SetOrigin(str_mcorigin);
			particle_container.SetmcPdgCode(mcPdg);
			particle_container.SetmcParentPdgCode(mcParentPdg);
			particle_container.SetmcNeutrinoEnergy(mcNeutrinoEnergy);
			particle_container.SetmcVtxX(mc_vtx_x);
			particle_container.SetmcVtxY(mc_vtx_y);
			particle_container.SetmcVtxZ(mc_vtx_z);
			particle_container.SetmcDirX(mc_dir_x);
			particle_container.SetmcDirY(mc_dir_y);
			particle_container.SetmcDirZ(mc_dir_z);
			particle_container.SetmcTheta(mc_theta);
			particle_container.SetmcPhi(mc_phi);
			particle_container.SetmcLength(mcLength);
			particle_container.SetmcEnergy(mcEnergy);
			particle_container.SetmcMomentum(mcMomentum);
			particle_container.SetMode(particle_mode);
			particle_container.SetCCNC(particle_is_cc);

			//pfp tracks
			if(pfpPdg == 13)
			{
				std::vector<art::Ptr<recob::Track> > tracks = tracks_from_pfp.at(pfp.key());
				if(_verbose) {std::cout << "[Analyze] \t\t n tracks ass to this pfp: " << tracks.size() << std::endl; }
				//we want to take the first association, right?
				if(tracks.size() != 0)
				{
					const art::Ptr<recob::Track> this_track = tracks.at(0);
					pfp_dir_x = this_track->VertexDirection().X();
					pfp_dir_y = this_track->VertexDirection().Y();
					pfp_dir_z = this_track->VertexDirection().Z();
					pfp_theta = acos(pfp_dir_z) * (180 / 3.1415);
					pfp_phi = atan2(pfp_dir_y, pfp_dir_x) * (180 / 3.1415);
					pfp_length = this_track->Length();
					pfp_momentum = this_track->StartMomentum();

					xsecAna::utility::GetNumberOfHitsPerPlane(e, _pfp_producer, this_track, pfp_hits_u, pfp_hits_v, pfp_hits_w);
					pfp_hits = (pfp_hits_u + pfp_hits_v + pfp_hits_w);
					n_pfp_tracks++;
				}
			}//end pfp tracks

			//pfp showers
			if(pfpPdg == 11)
			{
				std::vector<art::Ptr<recob::Shower> > showers = showers_from_pfp.at(pfp.key());
				if(_verbose) {std::cout << "[Analyze] \t\t n showers ass to this pfp: " << showers.size() << std::endl; }
				//we want to take the first association, right?
				if(showers.size() != 0)
				{
					const art::Ptr<recob::Shower> this_shower = showers.at(0);
					pfp_dir_x = this_shower->Direction().X();
					pfp_dir_y = this_shower->Direction().Y();
					pfp_dir_z = this_shower->Direction().Z();
					pfp_theta = acos(pfp_dir_z) * (180 / 3.1415);
					pfp_phi = atan2(pfp_dir_y, pfp_dir_x) * (180 / 3.1415);
					pfp_length = this_shower->Length();
					pfp_momentum = this_shower->Energy().at(this_shower->best_plane());
					pfp_open_angle = this_shower->OpenAngle();

					xsecAna::utility::GetNumberOfHitsPerPlane(e, _pfp_producer, this_shower, pfp_hits_u, pfp_hits_v, pfp_hits_w);
					pfp_hits = (pfp_hits_u + pfp_hits_v + pfp_hits_w);

					//trying to do dqdx!
					xsecAna::utility::ConstructShowerdQdX(geoHelper, isData, ClusterToHitsMap, clusters,
					                                      _dQdxRectangleLength,_dQdxRectangleWidth, this_shower, shower_cluster_dqdx, _verbose);
					//then dEdx!
					xsecAna::utility::ConvertdEdX(shower_cluster_dqdx, shower_dEdx);
					for(auto const cluster_dqdx : shower_cluster_dqdx)
					{
						//cluster dqdx is size 3 - one for each plane
						if(_verbose) {std::cout << "[Analyze] [dQdx] Plane 0: " << cluster_dqdx.at(0) << std::endl; }
						if(_verbose) {std::cout << "[Analyze] [dQdx] Plane 1: " << cluster_dqdx.at(1) << std::endl; }
						if(_verbose) {std::cout << "[Analyze] [dQdx] Collection Plane: " << cluster_dqdx.at(2) << std::endl; }
					}
					if(_verbose) {std::cout << "[Analyze] [dEdx] Plane 0: " << shower_dEdx.at(0) << std::endl; }
					if(_verbose) {std::cout << "[Analyze] [dEdx] Plane 1: " << shower_dEdx.at(1) << std::endl; }
					if(_verbose) {std::cout << "[Analyze] [dEdx] Plane 2: " << shower_dEdx.at(2) << std::endl; }
					n_pfp_showers++;
				}
			}//end pfp showers

			if(_verbose) {std::cout << "[Analyze] Filling Particle Container Objects" << std::endl; }

			particle_container.SetpfpDirX(pfp_dir_x);
			particle_container.SetpfpDirY(pfp_dir_y);
			particle_container.SetpfpDirZ(pfp_dir_z);
			particle_container.SetpfpTheta(pfp_theta);
			particle_container.SetpfpPhi(pfp_phi);
			particle_container.SetpfpLength(pfp_length);
			particle_container.SetpfpMomentum(pfp_momentum);
			particle_container.SetpfpOpenAngle(pfp_open_angle);
			particle_container.SetNumPFPHits(pfp_hits);
			particle_container.SetNumPFPHitsU(pfp_hits_u);
			particle_container.SetNumPFPHitsV(pfp_hits_v);
			particle_container.SetNumPFPHitsW(pfp_hits_w);
			particle_container.SetPfpClusterdQdx(shower_cluster_dqdx);
			particle_container.SetPfpdEdx(shower_dEdx);

			tpc_object_container.AddParticle(particle_container);

		}//end loop over pfp in tpcobject
		tpc_object_container.SetNumPFPNeutrinos(pfp_nu_counter);
		tpc_object_container.SetMode(mode);
		tpc_object_container.SetCCNC(ccnc);
		tpc_object_container.SetmcPdgCode(tpco_mc_pdg);
		tpc_object_container.SetpfpPdgCode(tpco_pfp_pdg);
		tpc_object_container.SetNPfpTracks(n_pfp_tracks);
		tpc_object_container.SetNPfpShowers(n_pfp_showers);
		//tpc_object_container.SetmcPdgCode();

		tpc_object_container_v.push_back(tpc_object_container);
		tpc_object_counter++;
	}//end loop tpc objects

	//fill root tree per event
	std::cout << "[Analyze] Fill Root Tree" << std::endl;
	myTree->Fill();


}

void xsecAna::TpcObjectAnalysis::endSubRun(art::SubRun const & sr) {
	//probably want to fill the tree here
	std::cout << "[Analyze] End Running" << std::endl;
}

DEFINE_ART_MODULE(xsecAna::TpcObjectAnalysis)
