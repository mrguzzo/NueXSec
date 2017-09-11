#ifndef TPCOBJECTANALYSIS_H
#define TPCOBJECTANALYSIS_H

#include "AnaHelper.h"
#include "RecoTrueHelper.h"
#include "MCGhost.h"
#include "PostMCCorrections.h"
#include "TPCObject.h"
#include "TpcObjectHelper.h"
#include "TpcObjectContainer.h"
#include "ParticleContainer.h"
#include "UtilityFunctions.h"

namespace xsec_ana {

class NueXSec;

class NueXSec : public art::EDAnalyzer {
public:
explicit NueXSec(fhicl::ParameterSet const & p);
// The compiler-generated destructor is fine for non-base
// classes without bare pointers or other resource use.

// Plugins should not be copied or assigned.
NueXSec(NueXSec const &) = delete;
NueXSec(NueXSec &&) = delete;
NueXSec & operator = (NueXSec const &) = delete;
NueXSec & operator = (NueXSec &&) = delete;

// Required functions.
void reconfigure(fhicl::ParameterSet const &p) override;
void analyze(art::Event const & e) override;
void endSubRun(const art::SubRun &sr) override;


private:

xsec_ana::recotruehelper _recotruehelper_instance;

TTree * myTree;
bool isMC;
bool isData;

std::string _pfp_producer;
std::string _hitfinderLabel;
std::string _geantModuleLabel;
std::string _spacepointLabel;
std::string _neutrino_flash_match_producer;
std::string _cosmic_flash_match_producer;
std::string _opflash_producer_beam;
std::string _tpcobject_producer;
std::string _potsum_producer;
std::string _potsum_instance;
std::string _particle_id_producer;
std::string _mc_ghost_producer;

std::string _vertexLabel;
std::string _trackLabel;
std::string _showerLabel;

bool _use_genie_info;
int _minimumHitRequirement;

double _beam_spill_start;
double _beam_spill_end;

bool _debug;
bool _verbose;

std::vector<xsec_ana::TpcObjectContainer> tpc_object_container_v;


int run;
int event;
int index;
int nMCParticles;
int nMCNeutrinos;
int nPFPartilcles;
int nPFPNeutrinos;
int mcPdg;
int mcNuPdg;
int mcNuIndex;
int mcParentPdg;
bool mcIsNeutirno;
bool mcIsPrimary;
int mcMode;
int mcOrigin;
bool mcIsCC;
int pfpPdg;
int pfpNuPdg;
int pfpNuIndex;
int pfpIndex;
int pfpParentPdg;
bool pfpIsNeutrino;

double mcVtxX;
double mcVtxY;
double mcVtxZ;
double pfpVtxX;
double pfpVtxY;
double pfpVtxZ;

double mcDirX;
double mcDirY;
double mcDirZ;
double pfpDirX;
double pfpDirY;
double pfpDirZ;

double mcTheta;
double mcPhi;
double pfpTheta;
double pfpPhi;

double mcLength;
double pfpLength;

double mcEnergy;
double mcMomentum;
//double pfpEnergy;
double pfpMomentum;

double completeness;
double purity;

int nMCHits;
int nMCHitsU;
int nMCHitsV;
int nMCHitsY;
int nPFPHits;
int nPFPHitsU;
int nPFPHitsV;
int nPFPHitsY;
int nMatchedHits;
int nMatchedHitsU;
int nMatchedHitsV;
int nMatchedHitsY;

double mcOpenAngle;
double pfpOpenAngle;

};

}//end namespace

#endif
