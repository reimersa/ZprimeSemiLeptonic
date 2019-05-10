#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

using namespace std;
using namespace uhh2;


ZprimeHandleBuilder::ZprimeHandleBuilder(uhh2::Context& ctx){
  h_eventweight   = ctx.declare_event_output< float >("eventweight");
  h_n_jets        = ctx.declare_event_output< int   >("n_jets");
  h_px_jet1       = ctx.declare_event_output< float >("px_jet1");
  h_px_jet2       = ctx.declare_event_output< float >("px_jet2");
  h_px_jet3       = ctx.declare_event_output< float >("px_jet3");
  h_px_jet4       = ctx.declare_event_output< float >("px_jet4");
  h_px_jet5       = ctx.declare_event_output< float >("px_jet5");
  h_px_jet6       = ctx.declare_event_output< float >("px_jet6");
  h_px_jet7       = ctx.declare_event_output< float >("px_jet7");
  h_px_jet8       = ctx.declare_event_output< float >("px_jet8");
  h_px_jet9       = ctx.declare_event_output< float >("px_jet9");
  h_px_jet10      = ctx.declare_event_output< float >("px_jet10");
  h_py_jet1       = ctx.declare_event_output< float >("py_jet1");
  h_py_jet2       = ctx.declare_event_output< float >("py_jet2");
  h_py_jet3       = ctx.declare_event_output< float >("py_jet3");
  h_py_jet4       = ctx.declare_event_output< float >("py_jet4");
  h_py_jet5       = ctx.declare_event_output< float >("py_jet5");
  h_py_jet6       = ctx.declare_event_output< float >("py_jet6");
  h_py_jet7       = ctx.declare_event_output< float >("py_jet7");
  h_py_jet8       = ctx.declare_event_output< float >("py_jet8");
  h_py_jet9       = ctx.declare_event_output< float >("py_jet9");
  h_py_jet10      = ctx.declare_event_output< float >("py_jet10");
  h_pz_jet1       = ctx.declare_event_output< float >("pz_jet1");
  h_pz_jet2       = ctx.declare_event_output< float >("pz_jet2");
  h_pz_jet3       = ctx.declare_event_output< float >("pz_jet3");
  h_pz_jet4       = ctx.declare_event_output< float >("pz_jet4");
  h_pz_jet5       = ctx.declare_event_output< float >("pz_jet5");
  h_pz_jet6       = ctx.declare_event_output< float >("pz_jet6");
  h_pz_jet7       = ctx.declare_event_output< float >("pz_jet7");
  h_pz_jet8       = ctx.declare_event_output< float >("pz_jet8");
  h_pz_jet9       = ctx.declare_event_output< float >("pz_jet9");
  h_pz_jet10      = ctx.declare_event_output< float >("pz_jet10");
  h_e_jet1       = ctx.declare_event_output< float >("e_jet1");
  h_e_jet2       = ctx.declare_event_output< float >("e_jet2");
  h_e_jet3       = ctx.declare_event_output< float >("e_jet3");
  h_e_jet4       = ctx.declare_event_output< float >("e_jet4");
  h_e_jet5       = ctx.declare_event_output< float >("e_jet5");
  h_e_jet6       = ctx.declare_event_output< float >("e_jet6");
  h_e_jet7       = ctx.declare_event_output< float >("e_jet7");
  h_e_jet8       = ctx.declare_event_output< float >("e_jet8");
  h_e_jet9       = ctx.declare_event_output< float >("e_jet9");
  h_e_jet10      = ctx.declare_event_output< float >("e_jet10");

  h_pt_jet1       = ctx.declare_event_output< float >("pt_jet1");
  h_pt_jet2       = ctx.declare_event_output< float >("pt_jet2");
  h_pt_jet3       = ctx.declare_event_output< float >("pt_jet3");
  h_pt_jet4       = ctx.declare_event_output< float >("pt_jet4");
  h_pt_jet5       = ctx.declare_event_output< float >("pt_jet5");
  h_pt_jet6       = ctx.declare_event_output< float >("pt_jet6");
  h_pt_jet7       = ctx.declare_event_output< float >("pt_jet7");
  h_pt_jet8       = ctx.declare_event_output< float >("pt_jet8");
  h_pt_jet9       = ctx.declare_event_output< float >("pt_jet9");
  h_pt_jet10      = ctx.declare_event_output< float >("pt_jet10");
  h_eta_jet1      = ctx.declare_event_output< float >("eta_jet1");
  h_eta_jet2      = ctx.declare_event_output< float >("eta_jet2");
  h_eta_jet3      = ctx.declare_event_output< float >("eta_jet3");
  h_eta_jet4      = ctx.declare_event_output< float >("eta_jet4");
  h_eta_jet5      = ctx.declare_event_output< float >("eta_jet5");
  h_eta_jet6      = ctx.declare_event_output< float >("eta_jet6");
  h_eta_jet7      = ctx.declare_event_output< float >("eta_jet7");
  h_eta_jet8      = ctx.declare_event_output< float >("eta_jet8");
  h_eta_jet9      = ctx.declare_event_output< float >("eta_jet9");
  h_eta_jet10     = ctx.declare_event_output< float >("eta_jet10");
  h_phi_jet1      = ctx.declare_event_output< float >("phi_jet1");
  h_phi_jet2      = ctx.declare_event_output< float >("phi_jet2");
  h_phi_jet3      = ctx.declare_event_output< float >("phi_jet3");
  h_phi_jet4      = ctx.declare_event_output< float >("phi_jet4");
  h_phi_jet5      = ctx.declare_event_output< float >("phi_jet5");
  h_phi_jet6      = ctx.declare_event_output< float >("phi_jet6");
  h_phi_jet7      = ctx.declare_event_output< float >("phi_jet7");
  h_phi_jet8      = ctx.declare_event_output< float >("phi_jet8");
  h_phi_jet9      = ctx.declare_event_output< float >("phi_jet9");
  h_phi_jet10     = ctx.declare_event_output< float >("phi_jet10");
  h_m_jet1        = ctx.declare_event_output< float >("m_jet1");
  h_m_jet2        = ctx.declare_event_output< float >("m_jet2");
  h_m_jet3        = ctx.declare_event_output< float >("m_jet3");
  h_m_jet4        = ctx.declare_event_output< float >("m_jet4");
  h_m_jet5        = ctx.declare_event_output< float >("m_jet5");
  h_m_jet6        = ctx.declare_event_output< float >("m_jet6");
  h_m_jet7        = ctx.declare_event_output< float >("m_jet7");
  h_m_jet8        = ctx.declare_event_output< float >("m_jet8");
  h_m_jet9        = ctx.declare_event_output< float >("m_jet9");
  h_m_jet10        = ctx.declare_event_output< float >("m_jet10");
  h_csv_jet1      = ctx.declare_event_output< float >("csv_jet1");
  h_csv_jet2      = ctx.declare_event_output< float >("csv_jet2");
  h_csv_jet3      = ctx.declare_event_output< float >("csv_jet3");
  h_csv_jet4      = ctx.declare_event_output< float >("csv_jet4");
  h_csv_jet5      = ctx.declare_event_output< float >("csv_jet5");
  h_csv_jet6      = ctx.declare_event_output< float >("csv_jet6");
  h_csv_jet7      = ctx.declare_event_output< float >("csv_jet7");
  h_csv_jet8      = ctx.declare_event_output< float >("csv_jet8");
  h_csv_jet9      = ctx.declare_event_output< float >("csv_jet9");
  h_csv_jet10      = ctx.declare_event_output< float >("csv_jet10");
  h_n_bjets_loose = ctx.declare_event_output< int   >("N_bJets_loose");
  h_n_bjets_med   = ctx.declare_event_output< int   >("N_bJets_med");
  h_n_bjets_tight = ctx.declare_event_output< int   >("N_bJets_tight");

  h_n_ak8jets        = ctx.declare_event_output< int   >("n_ak8jets");
  h_px_ak8jet1       = ctx.declare_event_output< float >("px_ak8jet1");
  h_px_ak8jet2       = ctx.declare_event_output< float >("px_ak8jet2");
  h_px_ak8jet3       = ctx.declare_event_output< float >("px_ak8jet3");
  h_px_ak8jet4       = ctx.declare_event_output< float >("px_ak8jet4");
  h_px_ak8jet5       = ctx.declare_event_output< float >("px_ak8jet5");
  h_px_ak8jet6       = ctx.declare_event_output< float >("px_ak8jet6");
  h_px_ak8jet7       = ctx.declare_event_output< float >("px_ak8jet7");
  h_px_ak8jet8       = ctx.declare_event_output< float >("px_ak8jet8");
  h_px_ak8jet9       = ctx.declare_event_output< float >("px_ak8jet9");
  h_px_ak8jet10      = ctx.declare_event_output< float >("px_ak8jet10");
  h_py_ak8jet1       = ctx.declare_event_output< float >("py_ak8jet1");
  h_py_ak8jet2       = ctx.declare_event_output< float >("py_ak8jet2");
  h_py_ak8jet3       = ctx.declare_event_output< float >("py_ak8jet3");
  h_py_ak8jet4       = ctx.declare_event_output< float >("py_ak8jet4");
  h_py_ak8jet5       = ctx.declare_event_output< float >("py_ak8jet5");
  h_py_ak8jet6       = ctx.declare_event_output< float >("py_ak8jet6");
  h_py_ak8jet7       = ctx.declare_event_output< float >("py_ak8jet7");
  h_py_ak8jet8       = ctx.declare_event_output< float >("py_ak8jet8");
  h_py_ak8jet9       = ctx.declare_event_output< float >("py_ak8jet9");
  h_py_ak8jet10      = ctx.declare_event_output< float >("py_ak8jet10");
  h_pz_ak8jet1       = ctx.declare_event_output< float >("pz_ak8jet1");
  h_pz_ak8jet2       = ctx.declare_event_output< float >("pz_ak8jet2");
  h_pz_ak8jet3       = ctx.declare_event_output< float >("pz_ak8jet3");
  h_pz_ak8jet4       = ctx.declare_event_output< float >("pz_ak8jet4");
  h_pz_ak8jet5       = ctx.declare_event_output< float >("pz_ak8jet5");
  h_pz_ak8jet6       = ctx.declare_event_output< float >("pz_ak8jet6");
  h_pz_ak8jet7       = ctx.declare_event_output< float >("pz_ak8jet7");
  h_pz_ak8jet8       = ctx.declare_event_output< float >("pz_ak8jet8");
  h_pz_ak8jet9       = ctx.declare_event_output< float >("pz_ak8jet9");
  h_pz_ak8jet10      = ctx.declare_event_output< float >("pz_ak8jet10");
  h_e_ak8jet1       = ctx.declare_event_output< float >("e_ak8jet1");
  h_e_ak8jet2       = ctx.declare_event_output< float >("e_ak8jet2");
  h_e_ak8jet3       = ctx.declare_event_output< float >("e_ak8jet3");
  h_e_ak8jet4       = ctx.declare_event_output< float >("e_ak8jet4");
  h_e_ak8jet5       = ctx.declare_event_output< float >("e_ak8jet5");
  h_e_ak8jet6       = ctx.declare_event_output< float >("e_ak8jet6");
  h_e_ak8jet7       = ctx.declare_event_output< float >("e_ak8jet7");
  h_e_ak8jet8       = ctx.declare_event_output< float >("e_ak8jet8");
  h_e_ak8jet9       = ctx.declare_event_output< float >("e_ak8jet9");
  h_e_ak8jet10      = ctx.declare_event_output< float >("e_ak8jet10");

  h_pt_ak8jet1       = ctx.declare_event_output< float >("pt_ak8jet1");
  h_pt_ak8jet2       = ctx.declare_event_output< float >("pt_ak8jet2");
  h_pt_ak8jet3       = ctx.declare_event_output< float >("pt_ak8jet3");
  h_pt_ak8jet4       = ctx.declare_event_output< float >("pt_ak8jet4");
  h_pt_ak8jet5       = ctx.declare_event_output< float >("pt_ak8jet5");
  h_pt_ak8jet6       = ctx.declare_event_output< float >("pt_ak8jet6");
  h_pt_ak8jet7       = ctx.declare_event_output< float >("pt_ak8jet7");
  h_pt_ak8jet8       = ctx.declare_event_output< float >("pt_ak8jet8");
  h_pt_ak8jet9       = ctx.declare_event_output< float >("pt_ak8jet9");
  h_pt_ak8jet10      = ctx.declare_event_output< float >("pt_ak8jet10");
  h_eta_ak8jet1      = ctx.declare_event_output< float >("eta_ak8jet1");
  h_eta_ak8jet2      = ctx.declare_event_output< float >("eta_ak8jet2");
  h_eta_ak8jet3      = ctx.declare_event_output< float >("eta_ak8jet3");
  h_eta_ak8jet4      = ctx.declare_event_output< float >("eta_ak8jet4");
  h_eta_ak8jet5      = ctx.declare_event_output< float >("eta_ak8jet5");
  h_eta_ak8jet6      = ctx.declare_event_output< float >("eta_ak8jet6");
  h_eta_ak8jet7      = ctx.declare_event_output< float >("eta_ak8jet7");
  h_eta_ak8jet8      = ctx.declare_event_output< float >("eta_ak8jet8");
  h_eta_ak8jet9      = ctx.declare_event_output< float >("eta_ak8jet9");
  h_eta_ak8jet10     = ctx.declare_event_output< float >("eta_ak8jet10");
  h_phi_ak8jet1      = ctx.declare_event_output< float >("phi_ak8jet1");
  h_phi_ak8jet2      = ctx.declare_event_output< float >("phi_ak8jet2");
  h_phi_ak8jet3      = ctx.declare_event_output< float >("phi_ak8jet3");
  h_phi_ak8jet4      = ctx.declare_event_output< float >("phi_ak8jet4");
  h_phi_ak8jet5      = ctx.declare_event_output< float >("phi_ak8jet5");
  h_phi_ak8jet6      = ctx.declare_event_output< float >("phi_ak8jet6");
  h_phi_ak8jet7      = ctx.declare_event_output< float >("phi_ak8jet7");
  h_phi_ak8jet8      = ctx.declare_event_output< float >("phi_ak8jet8");
  h_phi_ak8jet9      = ctx.declare_event_output< float >("phi_ak8jet9");
  h_phi_ak8jet10     = ctx.declare_event_output< float >("phi_ak8jet10");
  h_msd_ak8jet1      = ctx.declare_event_output< float >("msd_ak8jet1");
  h_msd_ak8jet2      = ctx.declare_event_output< float >("msd_ak8jet2");
  h_msd_ak8jet3      = ctx.declare_event_output< float >("msd_ak8jet3");
  h_msd_ak8jet4      = ctx.declare_event_output< float >("msd_ak8jet4");
  h_msd_ak8jet5      = ctx.declare_event_output< float >("msd_ak8jet5");
  h_msd_ak8jet6      = ctx.declare_event_output< float >("msd_ak8jet6");
  h_msd_ak8jet7      = ctx.declare_event_output< float >("msd_ak8jet7");
  h_msd_ak8jet8      = ctx.declare_event_output< float >("msd_ak8jet8");
  h_msd_ak8jet9      = ctx.declare_event_output< float >("msd_ak8jet9");
  h_msd_ak8jet10     = ctx.declare_event_output< float >("msd_ak8jet10");
  h_ndaughters_ak8jet1 = ctx.declare_event_output< int >("ndaughters_ak8jet1");
  h_ndaughters_ak8jet2 = ctx.declare_event_output< int >("ndaughters_ak8jet2");
  h_ndaughters_ak8jet3 = ctx.declare_event_output< int >("ndaughters_ak8jet3");
  h_ndaughters_ak8jet4 = ctx.declare_event_output< int >("ndaughters_ak8jet4");
  h_ndaughters_ak8jet5 = ctx.declare_event_output< int >("ndaughters_ak8jet5");
  h_ndaughters_ak8jet6 = ctx.declare_event_output< int >("ndaughters_ak8jet6");
  h_ndaughters_ak8jet7 = ctx.declare_event_output< int >("ndaughters_ak8jet7");
  h_ndaughters_ak8jet8 = ctx.declare_event_output< int >("ndaughters_ak8jet8");
  h_ndaughters_ak8jet9 = ctx.declare_event_output< int >("ndaughters_ak8jet9");
  h_ndaughters_ak8jet10= ctx.declare_event_output< int >("ndaughters_ak8jet10");
  h_tau1_ak8jet1 = ctx.declare_event_output< float >("tau1_ak8jet1");
  h_tau1_ak8jet2 = ctx.declare_event_output< float >("tau1_ak8jet2");
  h_tau1_ak8jet3 = ctx.declare_event_output< float >("tau1_ak8jet3");
  h_tau1_ak8jet4 = ctx.declare_event_output< float >("tau1_ak8jet4");
  h_tau1_ak8jet5 = ctx.declare_event_output< float >("tau1_ak8jet5");
  h_tau1_ak8jet6 = ctx.declare_event_output< float >("tau1_ak8jet6");
  h_tau1_ak8jet7 = ctx.declare_event_output< float >("tau1_ak8jet7");
  h_tau1_ak8jet8 = ctx.declare_event_output< float >("tau1_ak8jet8");
  h_tau1_ak8jet9 = ctx.declare_event_output< float >("tau1_ak8jet9");
  h_tau1_ak8jet10= ctx.declare_event_output< float >("tau1_ak8jet10");
  h_tau2_ak8jet1 = ctx.declare_event_output< float >("tau2_ak8jet1");
  h_tau2_ak8jet2 = ctx.declare_event_output< float >("tau2_ak8jet2");
  h_tau2_ak8jet3 = ctx.declare_event_output< float >("tau2_ak8jet3");
  h_tau2_ak8jet4 = ctx.declare_event_output< float >("tau2_ak8jet4");
  h_tau2_ak8jet5 = ctx.declare_event_output< float >("tau2_ak8jet5");
  h_tau2_ak8jet6 = ctx.declare_event_output< float >("tau2_ak8jet6");
  h_tau2_ak8jet7 = ctx.declare_event_output< float >("tau2_ak8jet7");
  h_tau2_ak8jet8 = ctx.declare_event_output< float >("tau2_ak8jet8");
  h_tau2_ak8jet9 = ctx.declare_event_output< float >("tau2_ak8jet9");
  h_tau2_ak8jet10= ctx.declare_event_output< float >("tau2_ak8jet10");
  h_tau3_ak8jet1 = ctx.declare_event_output< float >("tau3_ak8jet1");
  h_tau3_ak8jet2 = ctx.declare_event_output< float >("tau3_ak8jet2");
  h_tau3_ak8jet3 = ctx.declare_event_output< float >("tau3_ak8jet3");
  h_tau3_ak8jet4 = ctx.declare_event_output< float >("tau3_ak8jet4");
  h_tau3_ak8jet5 = ctx.declare_event_output< float >("tau3_ak8jet5");
  h_tau3_ak8jet6 = ctx.declare_event_output< float >("tau3_ak8jet6");
  h_tau3_ak8jet7 = ctx.declare_event_output< float >("tau3_ak8jet7");
  h_tau3_ak8jet8 = ctx.declare_event_output< float >("tau3_ak8jet8");
  h_tau3_ak8jet9 = ctx.declare_event_output< float >("tau3_ak8jet9");
  h_tau3_ak8jet10= ctx.declare_event_output< float >("tau3_ak8jet10");
  h_tau21_ak8jet1 = ctx.declare_event_output< float >("tau21_ak8jet1");
  h_tau21_ak8jet2 = ctx.declare_event_output< float >("tau21_ak8jet2");
  h_tau21_ak8jet3 = ctx.declare_event_output< float >("tau21_ak8jet3");
  h_tau21_ak8jet4 = ctx.declare_event_output< float >("tau21_ak8jet4");
  h_tau21_ak8jet5 = ctx.declare_event_output< float >("tau21_ak8jet5");
  h_tau21_ak8jet6 = ctx.declare_event_output< float >("tau21_ak8jet6");
  h_tau21_ak8jet7 = ctx.declare_event_output< float >("tau21_ak8jet7");
  h_tau21_ak8jet8 = ctx.declare_event_output< float >("tau21_ak8jet8");
  h_tau21_ak8jet9 = ctx.declare_event_output< float >("tau21_ak8jet9");
  h_tau21_ak8jet10= ctx.declare_event_output< float >("tau21_ak8jet10");
  h_tau32_ak8jet1 = ctx.declare_event_output< float >("tau32_ak8jet1");
  h_tau32_ak8jet2 = ctx.declare_event_output< float >("tau32_ak8jet2");
  h_tau32_ak8jet3 = ctx.declare_event_output< float >("tau32_ak8jet3");
  h_tau32_ak8jet4 = ctx.declare_event_output< float >("tau32_ak8jet4");
  h_tau32_ak8jet5 = ctx.declare_event_output< float >("tau32_ak8jet5");
  h_tau32_ak8jet6 = ctx.declare_event_output< float >("tau32_ak8jet6");
  h_tau32_ak8jet7 = ctx.declare_event_output< float >("tau32_ak8jet7");
  h_tau32_ak8jet8 = ctx.declare_event_output< float >("tau32_ak8jet8");
  h_tau32_ak8jet9 = ctx.declare_event_output< float >("tau32_ak8jet9");
  h_tau32_ak8jet10= ctx.declare_event_output< float >("tau32_ak8jet10");


  h_n_mu           = ctx.declare_event_output< int   >("n_mu");
  h_px_mu1         = ctx.declare_event_output< float >("px_mu1");
  h_py_mu1         = ctx.declare_event_output< float >("py_mu1");
  h_pz_mu1         = ctx.declare_event_output< float >("pz_mu1");
  h_pt_mu1         = ctx.declare_event_output< float >("pt_mu1");
  h_eta_mu1        = ctx.declare_event_output< float >("eta_mu1");
  h_phi_mu1        = ctx.declare_event_output< float >("phi_mu1");
  h_e_mu1          = ctx.declare_event_output< float >("e_mu1");
  h_reliso_mu1     = ctx.declare_event_output< float >("reliso_mu1");
  h_drmin_mu1_jet  = ctx.declare_event_output< float >("drmin_mu1_jet");
  h_ptrel_mu1_jet  = ctx.declare_event_output< float >("ptrel_mu1_jet");

  h_n_ele           = ctx.declare_event_output< int   >("n_ele");
  h_px_ele1         = ctx.declare_event_output< float >("px_ele1");
  h_py_ele1         = ctx.declare_event_output< float >("py_ele1");
  h_pz_ele1         = ctx.declare_event_output< float >("pz_ele1");
  h_pt_ele1         = ctx.declare_event_output< float >("pt_ele1");
  h_eta_ele1        = ctx.declare_event_output< float >("eta_ele1");
  h_phi_ele1        = ctx.declare_event_output< float >("phi_ele1");
  h_e_ele1          = ctx.declare_event_output< float >("e_ele1");
  h_reliso_ele1     = ctx.declare_event_output< float >("reliso_ele1");
  h_drmin_ele1_jet  = ctx.declare_event_output< float >("drmin_ele1_jet");
  h_ptrel_ele1_jet  = ctx.declare_event_output< float >("ptrel_ele1_jet");

  h_npv           = ctx.declare_event_output< int   >("npv");
  h_met_px        = ctx.declare_event_output< float >("met_px");
  h_met_py        = ctx.declare_event_output< float >("met_py");
  h_met           = ctx.declare_event_output< float >("met");
  h_stjets        = ctx.declare_event_output< float >("stjets");
  h_stlep         = ctx.declare_event_output< float >("stlep");
  h_st            = ctx.declare_event_output< float >("st");
  h_mzprime       = ctx.declare_event_output< float >("m_zprime");
  h_chi2zprime    = ctx.declare_event_output< float >("chi2_zprime");
  h_s11           = ctx.declare_event_output< float >("s11");
  h_s12           = ctx.declare_event_output< float >("s12");
  h_s13           = ctx.declare_event_output< float >("s13");
  h_s22           = ctx.declare_event_output< float >("s22");
  h_s23           = ctx.declare_event_output< float >("s23");
  h_s33           = ctx.declare_event_output< float >("s33");


  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
}

bool ZprimeHandleBuilder::process(uhh2::Event& event){

  /*
  █      ██ ███████ ████████ ███████
  █      ██ ██         ██    ██
  █      ██ █████      ██    ███████
  █ ██   ██ ██         ██         ██
  █  █████  ███████    ██    ███████
  */

  vector<Jet>* jets = event.jets;
  event.set(h_eventweight, event.weight);
  event.set(h_n_jets, jets->size());

  if(jets->size() >= 1){
    event.set(h_px_jet1,  jets->at(0).v4().px());
    event.set(h_py_jet1,  jets->at(0).v4().py());
    event.set(h_pz_jet1,  jets->at(0).v4().pz());
    event.set(h_e_jet1,  jets->at(0).v4().e());
    event.set(h_pt_jet1,  jets->at(0).pt());
    event.set(h_eta_jet1, jets->at(0).eta());
    event.set(h_phi_jet1, jets->at(0).phi());
    event.set(h_m_jet1,   jets->at(0).v4().M());
    event.set(h_csv_jet1, jets->at(0).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet1,  0.);
    event.set(h_py_jet1,  0.);
    event.set(h_pz_jet1,  0.);
    event.set(h_e_jet1,  0.);
    event.set(h_pt_jet1,  0.);
    event.set(h_eta_jet1, 0.);
    event.set(h_phi_jet1, 0.);
    event.set(h_m_jet1,   0.);
    event.set(h_csv_jet1, 0.);
  }
  if(jets->size() >= 2){
    event.set(h_px_jet2,  jets->at(1).v4().px());
    event.set(h_py_jet2,  jets->at(1).v4().py());
    event.set(h_pz_jet2,  jets->at(1).v4().pz());
    event.set(h_e_jet2,  jets->at(1).v4().e());
    event.set(h_pt_jet2,  jets->at(1).pt());
    event.set(h_eta_jet2, jets->at(1).eta());
    event.set(h_phi_jet2, jets->at(1).phi());
    event.set(h_m_jet2,   jets->at(1).v4().M());
    event.set(h_csv_jet2, jets->at(1).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet2,  0.);
    event.set(h_py_jet2,  0.);
    event.set(h_pz_jet2,  0.);
    event.set(h_e_jet2,  0.);
    event.set(h_pt_jet2,  0.);
    event.set(h_eta_jet2, 0.);
    event.set(h_phi_jet2, 0.);
    event.set(h_m_jet2,   0.);
    event.set(h_csv_jet2, 0.);
  }
  if(jets->size() >= 3){
    event.set(h_px_jet3,  jets->at(2).v4().px());
    event.set(h_py_jet3,  jets->at(2).v4().py());
    event.set(h_pz_jet3,  jets->at(2).v4().pz());
    event.set(h_e_jet3,  jets->at(2).v4().e());
    event.set(h_pt_jet3,  jets->at(2).pt());
    event.set(h_eta_jet3, jets->at(2).eta());
    event.set(h_phi_jet3, jets->at(2).phi());
    event.set(h_m_jet3,   jets->at(2).v4().M());
    event.set(h_csv_jet3, jets->at(2).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet3,  0.);
    event.set(h_py_jet3,  0.);
    event.set(h_pz_jet3,  0.);
    event.set(h_e_jet3,  0.);
    event.set(h_pt_jet3,  0.);
    event.set(h_eta_jet3, 0.);
    event.set(h_phi_jet3, 0.);
    event.set(h_m_jet3,   0.);
    event.set(h_csv_jet3, 0.);
  }
  if(jets->size() >= 4){
    event.set(h_px_jet4,  jets->at(3).v4().px());
    event.set(h_py_jet4,  jets->at(3).v4().py());
    event.set(h_pz_jet4,  jets->at(3).v4().pz());
    event.set(h_e_jet4,  jets->at(3).v4().e());
    event.set(h_pt_jet4,  jets->at(3).pt());
    event.set(h_eta_jet4, jets->at(3).eta());
    event.set(h_phi_jet4, jets->at(3).phi());
    event.set(h_m_jet4,   jets->at(3).v4().M());
    event.set(h_csv_jet4, jets->at(3).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet4,  0.);
    event.set(h_py_jet4,  0.);
    event.set(h_pz_jet4,  0.);
    event.set(h_e_jet4,  0.);
    event.set(h_pt_jet4,  0.);
    event.set(h_eta_jet4, 0.);
    event.set(h_phi_jet4, 0.);
    event.set(h_m_jet4,   0.);
    event.set(h_csv_jet4, 0.);
  }
  if(jets->size() >= 5){
    event.set(h_px_jet5,  jets->at(4).v4().px());
    event.set(h_py_jet5,  jets->at(4).v4().py());
    event.set(h_pz_jet5,  jets->at(4).v4().pz());
    event.set(h_e_jet5,  jets->at(4).v4().e());
    event.set(h_pt_jet5,  jets->at(4).pt());
    event.set(h_eta_jet5, jets->at(4).eta());
    event.set(h_phi_jet5, jets->at(4).phi());
    event.set(h_m_jet5,   jets->at(4).v4().M());
    event.set(h_csv_jet5, jets->at(4).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet5,  0.);
    event.set(h_py_jet5,  0.);
    event.set(h_pz_jet5,  0.);
    event.set(h_e_jet5,  0.);
    event.set(h_pt_jet5,  0.);
    event.set(h_eta_jet5, 0.);
    event.set(h_phi_jet5, 0.);
    event.set(h_m_jet5,   0.);
    event.set(h_csv_jet5, 0.);
  }
  if(jets->size() >= 6){
    event.set(h_px_jet6,  jets->at(5).v4().px());
    event.set(h_py_jet6,  jets->at(5).v4().py());
    event.set(h_pz_jet6,  jets->at(5).v4().pz());
    event.set(h_e_jet6,  jets->at(5).v4().e());
    event.set(h_pt_jet6,  jets->at(5).pt());
    event.set(h_eta_jet6, jets->at(5).eta());
    event.set(h_phi_jet6, jets->at(5).phi());
    event.set(h_m_jet6,   jets->at(5).v4().M());
    event.set(h_csv_jet6, jets->at(5).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet6,  0.);
    event.set(h_py_jet6,  0.);
    event.set(h_pz_jet6,  0.);
    event.set(h_e_jet6,  0.);
    event.set(h_pt_jet6,  0.);
    event.set(h_eta_jet6, 0.);
    event.set(h_phi_jet6, 0.);
    event.set(h_m_jet6,   0.);
    event.set(h_csv_jet6, 0.);
  }
  if(jets->size() >= 7){
    event.set(h_px_jet7,  jets->at(6).v4().px());
    event.set(h_py_jet7,  jets->at(6).v4().py());
    event.set(h_pz_jet7,  jets->at(6).v4().pz());
    event.set(h_e_jet7,  jets->at(6).v4().e());
    event.set(h_pt_jet7,  jets->at(6).pt());
    event.set(h_eta_jet7, jets->at(6).eta());
    event.set(h_phi_jet7, jets->at(6).phi());
    event.set(h_m_jet7,   jets->at(6).v4().M());
    event.set(h_csv_jet7, jets->at(6).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet7,  0.);
    event.set(h_py_jet7,  0.);
    event.set(h_pz_jet7,  0.);
    event.set(h_e_jet7,  0.);
    event.set(h_pt_jet7,  0.);
    event.set(h_eta_jet7, 0.);
    event.set(h_phi_jet7, 0.);
    event.set(h_m_jet7,   0.);
    event.set(h_csv_jet7, 0.);
  }
  if(jets->size() >= 8){
    event.set(h_px_jet8,  jets->at(7).v4().px());
    event.set(h_py_jet8,  jets->at(7).v4().py());
    event.set(h_pz_jet8,  jets->at(7).v4().pz());
    event.set(h_e_jet8,  jets->at(7).v4().e());
    event.set(h_pt_jet8,  jets->at(7).pt());
    event.set(h_eta_jet8, jets->at(7).eta());
    event.set(h_phi_jet8, jets->at(7).phi());
    event.set(h_m_jet8,   jets->at(7).v4().M());
    event.set(h_csv_jet8, jets->at(7).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet8,  0.);
    event.set(h_py_jet8,  0.);
    event.set(h_pz_jet8,  0.);
    event.set(h_e_jet8,  0.);
    event.set(h_pt_jet8,  0.);
    event.set(h_eta_jet8, 0.);
    event.set(h_phi_jet8, 0.);
    event.set(h_m_jet8,   0.);
    event.set(h_csv_jet8, 0.);
  }
  if(jets->size() >= 9){
    event.set(h_px_jet9,  jets->at(8).v4().px());
    event.set(h_py_jet9,  jets->at(8).v4().py());
    event.set(h_pz_jet9,  jets->at(8).v4().pz());
    event.set(h_e_jet9,  jets->at(8).v4().e());
    event.set(h_pt_jet9,  jets->at(8).pt());
    event.set(h_eta_jet9, jets->at(8).eta());
    event.set(h_phi_jet9, jets->at(8).phi());
    event.set(h_m_jet9,   jets->at(8).v4().M());
    event.set(h_csv_jet9, jets->at(8).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet9,  0.);
    event.set(h_py_jet9,  0.);
    event.set(h_pz_jet9,  0.);
    event.set(h_e_jet9,  0.);
    event.set(h_pt_jet9,  0.);
    event.set(h_eta_jet9, 0.);
    event.set(h_phi_jet9, 0.);
    event.set(h_m_jet9,   0.);
    event.set(h_csv_jet9, 0.);
  }
  if(jets->size() >= 10){
    event.set(h_px_jet10,  jets->at(9).v4().px());
    event.set(h_py_jet10,  jets->at(9).v4().py());
    event.set(h_pz_jet10,  jets->at(9).v4().pz());
    event.set(h_e_jet10,  jets->at(9).v4().e());
    event.set(h_pt_jet10,  jets->at(9).pt());
    event.set(h_eta_jet10, jets->at(9).eta());
    event.set(h_phi_jet10, jets->at(9).phi());
    event.set(h_m_jet10,   jets->at(9).v4().M());
    event.set(h_csv_jet10, jets->at(9).btag_combinedSecondaryVertex());
  }
  else{
    event.set(h_px_jet10,  0.);
    event.set(h_py_jet10,  0.);
    event.set(h_pz_jet10,  0.);
    event.set(h_e_jet10,   0.);
    event.set(h_pt_jet10,  0.);
    event.set(h_eta_jet10, 0.);
    event.set(h_phi_jet10, 0.);
    event.set(h_m_jet10,   0.);
    event.set(h_csv_jet10, 0.);
  }

  int Nbjets_loose = 0, Nbjets_medium = 0, Nbjets_tight = 0;
  CSVBTag Btag_loose = CSVBTag(CSVBTag::WP_LOOSE);
  CSVBTag Btag_medium = CSVBTag(CSVBTag::WP_MEDIUM);
  CSVBTag Btag_tight = CSVBTag(CSVBTag::WP_TIGHT);
  for (unsigned int i=0; i<jets->size(); i++) {
    if(Btag_loose(jets->at(i),event))  Nbjets_loose++;
    if(Btag_medium(jets->at(i),event)) Nbjets_medium++;
    if(Btag_tight(jets->at(i),event))  Nbjets_tight++;
  }
  event.set(h_n_bjets_loose, Nbjets_loose);
  event.set(h_n_bjets_med, Nbjets_medium);
  event.set(h_n_bjets_tight, Nbjets_tight);

  /*
  █  █████  ██   ██  █████       ██ ███████ ████████ ███████
  █ ██   ██ ██  ██  ██   ██      ██ ██         ██    ██
  █ ███████ █████    █████       ██ █████      ██    ███████
  █ ██   ██ ██  ██  ██   ██ ██   ██ ██         ██         ██
  █ ██   ██ ██   ██  █████   █████  ███████    ██    ███████
  */

  vector<TopJet>* ak8jets = event.toppuppijets;
  event.set(h_n_ak8jets, ak8jets->size());

  if(ak8jets->size() >= 1){
    event.set(h_px_ak8jet1,  ak8jets->at(0).v4().px());
    event.set(h_py_ak8jet1,  ak8jets->at(0).v4().py());
    event.set(h_pz_ak8jet1,  ak8jets->at(0).v4().pz());
    event.set(h_e_ak8jet1,  ak8jets->at(0).v4().e());
    event.set(h_pt_ak8jet1,  ak8jets->at(0).pt());
    event.set(h_eta_ak8jet1, ak8jets->at(0).eta());
    event.set(h_phi_ak8jet1, ak8jets->at(0).phi());
    event.set(h_msd_ak8jet1, ak8jets->at(0).softdropmass());
    event.set(h_ndaughters_ak8jet1, ak8jets->at(0).numberOfDaughters());
    event.set(h_tau1_ak8jet1, ak8jets->at(0).tau1());
    event.set(h_tau2_ak8jet1, ak8jets->at(0).tau2());
    event.set(h_tau3_ak8jet1, ak8jets->at(0).tau3());
    event.set(h_tau21_ak8jet1, ak8jets->at(0).tau2()/ak8jets->at(0).tau1());
    event.set(h_tau32_ak8jet1, ak8jets->at(0).tau3()/ak8jets->at(0).tau2());
  }
  else{
    event.set(h_px_ak8jet1,  0.);
    event.set(h_py_ak8jet1,  0.);
    event.set(h_pz_ak8jet1,  0.);
    event.set(h_e_ak8jet1,  0.);
    event.set(h_pt_ak8jet1,  0.);
    event.set(h_eta_ak8jet1, 0.);
    event.set(h_phi_ak8jet1, 0.);
    event.set(h_msd_ak8jet1, 0.);
    event.set(h_ndaughters_ak8jet1, 0.);
    event.set(h_tau1_ak8jet1, 0.);
    event.set(h_tau2_ak8jet1, 0.);
    event.set(h_tau3_ak8jet1, 0.);
    event.set(h_tau21_ak8jet1, 0.);
    event.set(h_tau32_ak8jet1, 0.);
  }
  if(ak8jets->size() >= 2){
    event.set(h_px_ak8jet2,  ak8jets->at(1).v4().px());
    event.set(h_py_ak8jet2,  ak8jets->at(1).v4().py());
    event.set(h_pz_ak8jet2,  ak8jets->at(1).v4().pz());
    event.set(h_e_ak8jet2,  ak8jets->at(1).v4().e());
    event.set(h_pt_ak8jet2,  ak8jets->at(1).pt());
    event.set(h_eta_ak8jet2, ak8jets->at(1).eta());
    event.set(h_phi_ak8jet2, ak8jets->at(1).phi());
    event.set(h_msd_ak8jet2, ak8jets->at(1).softdropmass());
    event.set(h_ndaughters_ak8jet2, ak8jets->at(1).numberOfDaughters());
    event.set(h_tau1_ak8jet2, ak8jets->at(1).tau1());
    event.set(h_tau2_ak8jet2, ak8jets->at(1).tau2());
    event.set(h_tau3_ak8jet2, ak8jets->at(1).tau3());
    event.set(h_tau21_ak8jet2, ak8jets->at(1).tau2()/ak8jets->at(1).tau1());
    event.set(h_tau32_ak8jet2, ak8jets->at(1).tau3()/ak8jets->at(1).tau2());
  }
  else{
    event.set(h_px_ak8jet2,  0.);
    event.set(h_py_ak8jet2,  0.);
    event.set(h_pz_ak8jet2,  0.);
    event.set(h_e_ak8jet2,  0.);
    event.set(h_pt_ak8jet2,  0.);
    event.set(h_eta_ak8jet2, 0.);
    event.set(h_phi_ak8jet2, 0.);
    event.set(h_msd_ak8jet2, 0.);
    event.set(h_ndaughters_ak8jet2, 0.);
    event.set(h_tau1_ak8jet2, 0.);
    event.set(h_tau2_ak8jet2, 0.);
    event.set(h_tau3_ak8jet2, 0.);
    event.set(h_tau21_ak8jet2, 0.);
    event.set(h_tau32_ak8jet2, 0.);
  }
  if(ak8jets->size() >= 3){
    event.set(h_px_ak8jet3,  ak8jets->at(2).v4().px());
    event.set(h_py_ak8jet3,  ak8jets->at(2).v4().py());
    event.set(h_pz_ak8jet3,  ak8jets->at(2).v4().pz());
    event.set(h_e_ak8jet3,  ak8jets->at(2).v4().e());
    event.set(h_pt_ak8jet3,  ak8jets->at(2).pt());
    event.set(h_eta_ak8jet3, ak8jets->at(2).eta());
    event.set(h_phi_ak8jet3, ak8jets->at(2).phi());
    event.set(h_msd_ak8jet3, ak8jets->at(2).softdropmass());
    event.set(h_ndaughters_ak8jet3, ak8jets->at(2).numberOfDaughters());
    event.set(h_tau1_ak8jet3, ak8jets->at(2).tau1());
    event.set(h_tau2_ak8jet3, ak8jets->at(2).tau2());
    event.set(h_tau3_ak8jet3, ak8jets->at(2).tau3());
    event.set(h_tau21_ak8jet3, ak8jets->at(2).tau2()/ak8jets->at(2).tau1());
    event.set(h_tau32_ak8jet3, ak8jets->at(2).tau3()/ak8jets->at(2).tau2());
  }
  else{
    event.set(h_px_ak8jet3,  0.);
    event.set(h_py_ak8jet3,  0.);
    event.set(h_pz_ak8jet3,  0.);
    event.set(h_e_ak8jet3,  0.);
    event.set(h_pt_ak8jet3,  0.);
    event.set(h_eta_ak8jet3, 0.);
    event.set(h_phi_ak8jet3, 0.);
    event.set(h_msd_ak8jet3, 0.);
    event.set(h_ndaughters_ak8jet3, 0.);
    event.set(h_tau1_ak8jet3, 0.);
    event.set(h_tau2_ak8jet3, 0.);
    event.set(h_tau3_ak8jet3, 0.);
    event.set(h_tau21_ak8jet3, 0.);
    event.set(h_tau32_ak8jet3, 0.);
  }
  if(ak8jets->size() >= 4){
    event.set(h_px_ak8jet4,  ak8jets->at(3).v4().px());
    event.set(h_py_ak8jet4,  ak8jets->at(3).v4().py());
    event.set(h_pz_ak8jet4,  ak8jets->at(3).v4().pz());
    event.set(h_e_ak8jet4,  ak8jets->at(3).v4().e());
    event.set(h_pt_ak8jet4,  ak8jets->at(3).pt());
    event.set(h_eta_ak8jet4, ak8jets->at(3).eta());
    event.set(h_phi_ak8jet4, ak8jets->at(3).phi());
    event.set(h_msd_ak8jet4, ak8jets->at(3).softdropmass());
    event.set(h_ndaughters_ak8jet4, ak8jets->at(3).numberOfDaughters());
    event.set(h_tau1_ak8jet4, ak8jets->at(3).tau1());
    event.set(h_tau2_ak8jet4, ak8jets->at(3).tau2());
    event.set(h_tau3_ak8jet4, ak8jets->at(3).tau3());
    event.set(h_tau21_ak8jet4, ak8jets->at(3).tau2()/ak8jets->at(3).tau1());
    event.set(h_tau32_ak8jet4, ak8jets->at(3).tau3()/ak8jets->at(3).tau2());
  }
  else{
    event.set(h_px_ak8jet4,  0.);
    event.set(h_py_ak8jet4,  0.);
    event.set(h_pz_ak8jet4,  0.);
    event.set(h_e_ak8jet4,  0.);
    event.set(h_pt_ak8jet4,  0.);
    event.set(h_eta_ak8jet4, 0.);
    event.set(h_phi_ak8jet4, 0.);
    event.set(h_msd_ak8jet4, 0.);
    event.set(h_ndaughters_ak8jet4, 0.);
    event.set(h_tau1_ak8jet4, 0.);
    event.set(h_tau2_ak8jet4, 0.);
    event.set(h_tau3_ak8jet4, 0.);
    event.set(h_tau21_ak8jet4, 0.);
    event.set(h_tau32_ak8jet4, 0.);
  }
  if(ak8jets->size() >= 5){
    event.set(h_px_ak8jet5,  ak8jets->at(4).v4().px());
    event.set(h_py_ak8jet5,  ak8jets->at(4).v4().py());
    event.set(h_pz_ak8jet5,  ak8jets->at(4).v4().pz());
    event.set(h_e_ak8jet5,  ak8jets->at(4).v4().e());
    event.set(h_pt_ak8jet5,  ak8jets->at(4).pt());
    event.set(h_eta_ak8jet5, ak8jets->at(4).eta());
    event.set(h_phi_ak8jet5, ak8jets->at(4).phi());
    event.set(h_msd_ak8jet5, ak8jets->at(4).softdropmass());
    event.set(h_ndaughters_ak8jet5, ak8jets->at(4).numberOfDaughters());
    event.set(h_tau1_ak8jet5, ak8jets->at(4).tau1());
    event.set(h_tau2_ak8jet5, ak8jets->at(4).tau2());
    event.set(h_tau3_ak8jet5, ak8jets->at(4).tau3());
    event.set(h_tau21_ak8jet5, ak8jets->at(4).tau2()/ak8jets->at(4).tau1());
    event.set(h_tau32_ak8jet5, ak8jets->at(4).tau3()/ak8jets->at(4).tau2());
  }
  else{
    event.set(h_px_ak8jet5,  0.);
    event.set(h_py_ak8jet5,  0.);
    event.set(h_pz_ak8jet5,  0.);
    event.set(h_e_ak8jet5,  0.);
    event.set(h_pt_ak8jet5,  0.);
    event.set(h_eta_ak8jet5, 0.);
    event.set(h_phi_ak8jet5, 0.);
    event.set(h_msd_ak8jet5, 0.);
    event.set(h_ndaughters_ak8jet5, 0.);
    event.set(h_tau1_ak8jet5, 0.);
    event.set(h_tau2_ak8jet5, 0.);
    event.set(h_tau3_ak8jet5, 0.);
    event.set(h_tau21_ak8jet5, 0.);
    event.set(h_tau32_ak8jet5, 0.);
  }
  if(ak8jets->size() >= 6){
    event.set(h_px_ak8jet6,  ak8jets->at(5).v4().px());
    event.set(h_py_ak8jet6,  ak8jets->at(5).v4().py());
    event.set(h_pz_ak8jet6,  ak8jets->at(5).v4().pz());
    event.set(h_e_ak8jet6,  ak8jets->at(5).v4().e());
    event.set(h_pt_ak8jet6,  ak8jets->at(5).pt());
    event.set(h_eta_ak8jet6, ak8jets->at(5).eta());
    event.set(h_phi_ak8jet6, ak8jets->at(5).phi());
    event.set(h_msd_ak8jet6, ak8jets->at(5).softdropmass());
    event.set(h_ndaughters_ak8jet6, ak8jets->at(5).numberOfDaughters());
    event.set(h_tau1_ak8jet6, ak8jets->at(5).tau1());
    event.set(h_tau2_ak8jet6, ak8jets->at(5).tau2());
    event.set(h_tau3_ak8jet6, ak8jets->at(5).tau3());
    event.set(h_tau21_ak8jet6, ak8jets->at(5).tau2()/ak8jets->at(5).tau1());
    event.set(h_tau32_ak8jet6, ak8jets->at(5).tau3()/ak8jets->at(5).tau2());
  }
  else{
    event.set(h_px_ak8jet6,  0.);
    event.set(h_py_ak8jet6,  0.);
    event.set(h_pz_ak8jet6,  0.);
    event.set(h_e_ak8jet6,  0.);
    event.set(h_pt_ak8jet6,  0.);
    event.set(h_eta_ak8jet6, 0.);
    event.set(h_phi_ak8jet6, 0.);
    event.set(h_msd_ak8jet6, 0.);
    event.set(h_ndaughters_ak8jet6, 0.);
    event.set(h_tau1_ak8jet6, 0.);
    event.set(h_tau2_ak8jet6, 0.);
    event.set(h_tau3_ak8jet6, 0.);
    event.set(h_tau21_ak8jet6, 0.);
    event.set(h_tau32_ak8jet6, 0.);
  }
  if(ak8jets->size() >= 7){
    event.set(h_px_ak8jet7,  ak8jets->at(6).v4().px());
    event.set(h_py_ak8jet7,  ak8jets->at(6).v4().py());
    event.set(h_pz_ak8jet7,  ak8jets->at(6).v4().pz());
    event.set(h_e_ak8jet7,  ak8jets->at(6).v4().e());
    event.set(h_pt_ak8jet7,  ak8jets->at(6).pt());
    event.set(h_eta_ak8jet7, ak8jets->at(6).eta());
    event.set(h_phi_ak8jet7, ak8jets->at(6).phi());
    event.set(h_msd_ak8jet7, ak8jets->at(6).softdropmass());
    event.set(h_ndaughters_ak8jet7, ak8jets->at(6).numberOfDaughters());
    event.set(h_tau1_ak8jet7, ak8jets->at(6).tau1());
    event.set(h_tau2_ak8jet7, ak8jets->at(6).tau2());
    event.set(h_tau3_ak8jet7, ak8jets->at(6).tau3());
    event.set(h_tau21_ak8jet7, ak8jets->at(6).tau2()/ak8jets->at(6).tau1());
    event.set(h_tau32_ak8jet7, ak8jets->at(6).tau3()/ak8jets->at(6).tau2());
  }
  else{
    event.set(h_px_ak8jet7,  0.);
    event.set(h_py_ak8jet7,  0.);
    event.set(h_pz_ak8jet7,  0.);
    event.set(h_e_ak8jet7,  0.);
    event.set(h_pt_ak8jet7,  0.);
    event.set(h_eta_ak8jet7, 0.);
    event.set(h_phi_ak8jet7, 0.);
    event.set(h_msd_ak8jet7, 0.);
    event.set(h_ndaughters_ak8jet7, 0.);
    event.set(h_tau1_ak8jet7, 0.);
    event.set(h_tau2_ak8jet7, 0.);
    event.set(h_tau3_ak8jet7, 0.);
    event.set(h_tau21_ak8jet7, 0.);
    event.set(h_tau32_ak8jet7, 0.);
  }
  if(ak8jets->size() >= 8){
    event.set(h_px_ak8jet8,  ak8jets->at(7).v4().px());
    event.set(h_py_ak8jet8,  ak8jets->at(7).v4().py());
    event.set(h_pz_ak8jet8,  ak8jets->at(7).v4().pz());
    event.set(h_e_ak8jet8,  ak8jets->at(7).v4().e());
    event.set(h_pt_ak8jet8,  ak8jets->at(7).pt());
    event.set(h_eta_ak8jet8, ak8jets->at(7).eta());
    event.set(h_phi_ak8jet8, ak8jets->at(7).phi());
    event.set(h_msd_ak8jet8, ak8jets->at(7).softdropmass());
    event.set(h_ndaughters_ak8jet8, ak8jets->at(7).numberOfDaughters());
    event.set(h_tau1_ak8jet8, ak8jets->at(7).tau1());
    event.set(h_tau2_ak8jet8, ak8jets->at(7).tau2());
    event.set(h_tau3_ak8jet8, ak8jets->at(7).tau3());
    event.set(h_tau21_ak8jet8, ak8jets->at(7).tau2()/ak8jets->at(7).tau1());
    event.set(h_tau32_ak8jet8, ak8jets->at(7).tau3()/ak8jets->at(7).tau2());
  }
  else{
    event.set(h_px_ak8jet8,  0.);
    event.set(h_py_ak8jet8,  0.);
    event.set(h_pz_ak8jet8,  0.);
    event.set(h_e_ak8jet8,  0.);
    event.set(h_pt_ak8jet8,  0.);
    event.set(h_eta_ak8jet8, 0.);
    event.set(h_phi_ak8jet8, 0.);
    event.set(h_msd_ak8jet8, 0.);
    event.set(h_ndaughters_ak8jet8, 0.);
    event.set(h_tau1_ak8jet8, 0.);
    event.set(h_tau2_ak8jet8, 0.);
    event.set(h_tau3_ak8jet8, 0.);
    event.set(h_tau21_ak8jet8, 0.);
    event.set(h_tau32_ak8jet8, 0.);
  }
  if(ak8jets->size() >= 9){
    event.set(h_px_ak8jet9,  ak8jets->at(8).v4().px());
    event.set(h_py_ak8jet9,  ak8jets->at(8).v4().py());
    event.set(h_pz_ak8jet9,  ak8jets->at(8).v4().pz());
    event.set(h_e_ak8jet9,  ak8jets->at(8).v4().e());
    event.set(h_pt_ak8jet9,  ak8jets->at(8).pt());
    event.set(h_eta_ak8jet9, ak8jets->at(8).eta());
    event.set(h_phi_ak8jet9, ak8jets->at(8).phi());
    event.set(h_msd_ak8jet9, ak8jets->at(8).softdropmass());
    event.set(h_ndaughters_ak8jet9, ak8jets->at(8).numberOfDaughters());
    event.set(h_tau1_ak8jet9, ak8jets->at(8).tau1());
    event.set(h_tau2_ak8jet9, ak8jets->at(8).tau2());
    event.set(h_tau3_ak8jet9, ak8jets->at(8).tau3());
    event.set(h_tau21_ak8jet9, ak8jets->at(8).tau2()/ak8jets->at(8).tau1());
    event.set(h_tau32_ak8jet9, ak8jets->at(8).tau3()/ak8jets->at(8).tau2());
  }
  else{
    event.set(h_px_ak8jet9,  0.);
    event.set(h_py_ak8jet9,  0.);
    event.set(h_pz_ak8jet9,  0.);
    event.set(h_e_ak8jet9,  0.);
    event.set(h_pt_ak8jet9,  0.);
    event.set(h_eta_ak8jet9, 0.);
    event.set(h_phi_ak8jet9, 0.);
    event.set(h_msd_ak8jet9, 0.);
    event.set(h_ndaughters_ak8jet9, 0.);
    event.set(h_tau1_ak8jet9, 0.);
    event.set(h_tau2_ak8jet9, 0.);
    event.set(h_tau3_ak8jet9, 0.);
    event.set(h_tau21_ak8jet9, 0.);
    event.set(h_tau32_ak8jet9, 0.);
  }
  if(ak8jets->size() >= 10){
    event.set(h_px_ak8jet10,  ak8jets->at(9).v4().px());
    event.set(h_py_ak8jet10,  ak8jets->at(9).v4().py());
    event.set(h_pz_ak8jet10,  ak8jets->at(9).v4().pz());
    event.set(h_e_ak8jet10,  ak8jets->at(9).v4().e());
    event.set(h_pt_ak8jet10,  ak8jets->at(9).pt());
    event.set(h_eta_ak8jet10, ak8jets->at(9).eta());
    event.set(h_phi_ak8jet10, ak8jets->at(9).phi());
    event.set(h_msd_ak8jet10, ak8jets->at(9).softdropmass());
    event.set(h_ndaughters_ak8jet10, ak8jets->at(9).numberOfDaughters());
    event.set(h_tau1_ak8jet10, ak8jets->at(9).tau1());
    event.set(h_tau2_ak8jet10, ak8jets->at(9).tau2());
    event.set(h_tau3_ak8jet10, ak8jets->at(9).tau3());
    event.set(h_tau21_ak8jet10, ak8jets->at(9).tau2()/ak8jets->at(9).tau1());
    event.set(h_tau32_ak8jet10, ak8jets->at(9).tau3()/ak8jets->at(9).tau2());
  }
  else{
    event.set(h_px_ak8jet10,  0.);
    event.set(h_py_ak8jet10,  0.);
    event.set(h_pz_ak8jet10,  0.);
    event.set(h_e_ak8jet10,  0.);
    event.set(h_pt_ak8jet10,  0.);
    event.set(h_eta_ak8jet10, 0.);
    event.set(h_phi_ak8jet10, 0.);
    event.set(h_msd_ak8jet10, 0.);
    event.set(h_ndaughters_ak8jet10, 0.);
    event.set(h_tau1_ak8jet10, 0.);
    event.set(h_tau2_ak8jet10, 0.);
    event.set(h_tau3_ak8jet10, 0.);
    event.set(h_tau21_ak8jet10, 0.);
    event.set(h_tau32_ak8jet10, 0.);
  }


  /*
  █  ██████  ███████ ███    ██ ███████ ██████   █████  ██
  █ ██       ██      ████   ██ ██      ██   ██ ██   ██ ██
  █ ██   ███ █████   ██ ██  ██ █████   ██████  ███████ ██
  █ ██    ██ ██      ██  ██ ██ ██      ██   ██ ██   ██ ██
  █  ██████  ███████ ██   ████ ███████ ██   ██ ██   ██ ███████
  */

  vector<Muon>* muons = event.muons;
  event.set(h_n_mu, muons->size());
  if(muons->size() > 0){
    event.set(h_px_mu1, muons->at(0).v4().px());
    event.set(h_py_mu1, muons->at(0).v4().py());
    event.set(h_pz_mu1, muons->at(0).v4().pz());
    event.set(h_pt_mu1, muons->at(0).pt());
    event.set(h_eta_mu1, muons->at(0).eta());
    event.set(h_phi_mu1, muons->at(0).phi());
    event.set(h_e_mu1, muons->at(0).energy());
    event.set(h_reliso_mu1, muons->at(0).relIso());
    event.set(h_drmin_mu1_jet, muons->at(0).get_tag(Muon::twodcut_dRmin));
    event.set(h_ptrel_mu1_jet, muons->at(0).get_tag(Muon::twodcut_pTrel));
  }
  else{
    event.set(h_px_mu1, 0.);
    event.set(h_py_mu1, 0.);
    event.set(h_pz_mu1, 0.);
    event.set(h_pt_mu1, 0.);
    event.set(h_eta_mu1, 0.);
    event.set(h_phi_mu1, 0.);
    event.set(h_e_mu1, 0.);
    event.set(h_reliso_mu1, 0.);
    event.set(h_drmin_mu1_jet, 0.);
    event.set(h_ptrel_mu1_jet, 0.);
  }

  vector<Electron>* electrons = event.electrons;
  event.set(h_n_ele, electrons->size());
  if(electrons->size() > 0){
    event.set(h_px_ele1, electrons->at(0).v4().px());
    event.set(h_py_ele1, electrons->at(0).v4().py());
    event.set(h_pz_ele1, electrons->at(0).v4().pz());
    event.set(h_pt_ele1, electrons->at(0).pt());
    event.set(h_eta_ele1, electrons->at(0).eta());
    event.set(h_phi_ele1, electrons->at(0).phi());
    event.set(h_e_ele1, electrons->at(0).energy());
    event.set(h_reliso_ele1, electrons->at(0).relIso());
    event.set(h_drmin_ele1_jet, electrons->at(0).get_tag(Electron::twodcut_dRmin));
    event.set(h_ptrel_ele1_jet, electrons->at(0).get_tag(Electron::twodcut_pTrel));
  }
  else{
    event.set(h_px_ele1, 0.);
    event.set(h_py_ele1, 0.);
    event.set(h_pz_ele1, 0.);
    event.set(h_pt_ele1, 0.);
    event.set(h_eta_ele1, 0.);
    event.set(h_phi_ele1, 0.);
    event.set(h_e_ele1, 0.);
    event.set(h_reliso_ele1, 0.);
    event.set(h_drmin_ele1_jet, 0.);
    event.set(h_ptrel_ele1_jet, 0.);
  }

  float met = event.met->pt();
  double st = 0., stjets = 0., stlep = 0.;
  for(const auto & jet : *jets)           stjets += jet.pt();
  for(const auto & electron : *electrons) stlep += electron.pt();
  for(const auto & muon : *muons)         stlep += muon.pt();
  st = stjets + stlep + met;

  event.set(h_npv, event.pvs->size());
  event.set(h_met, met);
  event.set(h_met_px, event.met->v4().px());
  event.set(h_met_py, event.met->v4().py());
  event.set(h_stjets, stjets);
  event.set(h_stlep, stlep);
  event.set(h_st, st);

  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  if(is_zprime_reconstructed_chi2){
    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
    float mreco = BestZprimeCandidate->Zprime_v4().M();
    float chi2 = BestZprimeCandidate->discriminator("chi2_total");

    event.set(h_mzprime, mreco);
    event.set(h_chi2zprime, chi2);
  }
  else{
    event.set(h_mzprime, 0.);
    event.set(h_chi2zprime, 0.);
  }

  // Sphericity tensor
  double s11 = 0., s12 = 0., s13 = 0., s22 = 0., s23 = 0., s33 = 0., mag = 0.;
  for(const Jet jet : *event.jets){
    mag += (jet.v4().Px()*jet.v4().Px()+jet.v4().Py()*jet.v4().Py()+jet.v4().Pz()*jet.v4().Pz());
    s11 += jet.v4().Px()*jet.v4().Px();
    s12 += jet.v4().Px()*jet.v4().Py();
    s13 += jet.v4().Px()*jet.v4().Pz();
    s22 += jet.v4().Py()*jet.v4().Py();
    s23 += jet.v4().Py()*jet.v4().Pz();
    s33 += jet.v4().Pz()*jet.v4().Pz();
  }
  if(mag > 0){
    s11 = s11 / mag;
    s12 = s12 / mag;
    s13 = s13 / mag;
    s22 = s22 / mag;
    s23 = s23 / mag;
    s33 = s33 / mag;
  }
  else{
    s11 = 0.;
    s12 = 0.;
    s13 = 0.;
    s22 = 0.;
    s23 = 0.;
    s33 = 0.;
  }

  event.set(h_s11, s11);
  event.set(h_s12, s12);
  event.set(h_s13, s13);
  event.set(h_s22, s22);
  event.set(h_s23, s23);
  event.set(h_s33, s33);

  return true;
}


float inv_mass(const LorentzVector& p4){ return p4.isTimelike() ? p4.mass() : -sqrt(-p4.mass2()); }

FlavorParticle find_primary_lepton(uhh2::Event & event) {
  assert(event.muons || event.electrons);
  FlavorParticle primlep;
  float ptmax = 0.;
  if(event.electrons) {
    for(const auto & ele : *event.electrons) {
      if(ele.pt() > ptmax) {
        ptmax = ele.pt();
        primlep = ele;
      }
    }
  }
  if(event.muons) {
    for(const auto & mu : *event.muons) {
      if(mu.pt() > ptmax) {
        ptmax = mu.pt();
        primlep = mu;
      }
    }
  }
  return primlep;
}

vector<LorentzVector> reconstruct_neutrino(const LorentzVector & lepton, const LorentzVector & met) {
  TVector3 lepton_pT = toVector(lepton);
  lepton_pT.SetZ(0);
  TVector3 neutrino_pT = toVector(met);
  neutrino_pT.SetZ(0);
  constexpr float mass_w = 80.399f;
  float mu = mass_w * mass_w / 2 + lepton_pT * neutrino_pT;
  float A = - (lepton_pT * lepton_pT);
  float B = mu * lepton.pz();
  float C = mu * mu - lepton.e() * lepton.e() * (neutrino_pT * neutrino_pT);
  float discriminant = B * B - A * C;
  std::vector<LorentzVector> solutions;
  if (0 >= discriminant) {
    // Take only real part of the solution for pz:
    LorentzVectorXYZE solution (met.Px(),met.Py(),-B / A,0);
    solution.SetE(solution.P());
    solutions.emplace_back(toPtEtaPhi(solution));
  }
  else {
    discriminant = sqrt(discriminant);
    LorentzVectorXYZE solution (met.Px(),met.Py(),(-B - discriminant) / A,0);
    solution.SetE(solution.P());
    solutions.emplace_back(toPtEtaPhi(solution));

    LorentzVectorXYZE solution2 (met.Px(),met.Py(),(-B + discriminant) / A,0);
    solution2.SetE(solution2.P());
    solutions.emplace_back(toPtEtaPhi(solution2));
  }
  return solutions;
}

ZprimeCandidateBuilder::ZprimeCandidateBuilder(uhh2::Context& ctx, TString mode, float minDR) : minDR_(minDR), mode_(mode){

  h_ZprimeCandidates_ = ctx.get_handle< vector<ZprimeCandidate> >("ZprimeCandidates");
  h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("AK8PuppiTopTags");
  h_AK8TopTagsPtr = ctx.get_handle<std::vector<const TopJet*>>("AK8PuppiTopTagsPtr");

  if(mode_ != "chs" && mode_ != "puppi") throw runtime_error("In ZprimeCandidateBuilder::ZprimeCandidateBuilder(): 'mode' must be 'chs' or 'puppi'");

}

bool ZprimeCandidateBuilder::process(uhh2::Event& event){
  assert(event.jets);
  assert(event.muons || event.electrons);
  assert(event.met);


  // Declare output
  vector<ZprimeCandidate> candidates;

  // Find primary lepton
  FlavorParticle lepton = find_primary_lepton(event);

  // Reconstruct neutrino
  vector<LorentzVector> neutrinos = reconstruct_neutrino(lepton.v4(), event.met->v4());
  unsigned int neutrinoidx = 0;

  // Build all necessary loops
  vector<TopJet> TopTags = event.get(h_AK8TopTags);
  vector<const TopJet*> TopTagsPtr = event.get(h_AK8TopTagsPtr);
  if((event.muons->size() < 1 && event.electrons->size() < 1)) throw runtime_error("Event content did not allow reconstructing the Zprime: Leptons");
  if((event.jets->size() < 2 && TopTags.size() == 0)) throw runtime_error("Event content did not allow reconstructing the Zprime: AK4");
  if((event.jets->size() < 1 && TopTags.size() >= 1)) throw runtime_error("Event content did not allow reconstructing the Zprime: Top-tag");

  vector<bool> matches_chs;
  vector<vector<TopJet>> chs_matched;
  if(mode_ == "chs"){
    // Check if top-tag reconstruction is possible
    for(const TopJet & toptag : TopTags){
      bool match = false;
      vector<TopJet> matches_this;
      for(const TopJet & chsjet : *event.topjets){
        double dR = uhh2::deltaR(chsjet, toptag);
        if(dR < 1.0){
          match = true;
          matches_this.emplace_back(chsjet);
        }
      }
      matches_chs.emplace_back(match);
      chs_matched.emplace_back(matches_this);
    }
  }

  // Must have at least one AK4 jet with dR > 1.2
  vector<bool> has_separated_jet;
  for(unsigned int i=0; i<TopTags.size(); i++){
    bool is_sep = false;
    if(mode_ == "chs"){
      for(unsigned int j=0; j<chs_matched[i].size(); j++){
        for(unsigned int k = 0; k < event.jets->size(); k++){
          if(deltaR(event.jets->at(k), chs_matched[i][j]) > 1.2) is_sep = true;
        }
      }
    }
    else{
      for(unsigned int k = 0; k < event.jets->size(); k++){
        if(deltaR(event.jets->at(k), TopTags[i]) > 1.2) is_sep = true;
      }
    }
    has_separated_jet.emplace_back(is_sep);
  }


  vector<bool> overlap_with_lepton;
  if(mode_ == "puppi"){
    for(const TopJet & toptag : TopTags){
      bool overlap = true;
      if(deltaR(lepton, toptag) > 0.8) overlap = false;
      overlap_with_lepton.emplace_back(overlap);
    }
  }
  else{
    for(unsigned int i=0; i<TopTags.size(); i++){
      bool overlap = true;
      for(unsigned int j=0; j<chs_matched[i].size(); j++){
        if(deltaR(lepton, chs_matched[i][j]) > 0.8) overlap = false;
      }
      overlap_with_lepton.emplace_back(overlap);
    }
  }

  bool do_toptag_reco = false;
  if(TopTags.size() >= 1){
    for(unsigned int i=0; i<TopTags.size(); i++){
      if(mode_ == "chs"){
        if(matches_chs[i] && has_separated_jet[i] &&  !overlap_with_lepton[i]) do_toptag_reco = true;
      }
      else if(mode_ == "puppi"){
        // cout << "Number of toptags: " << TopTags.size() << endl;
        // cout << "At " << i << " of " << has_separated_jet.size() << " and " << overlap_with_lepton.size() << endl;
        if(has_separated_jet[i] &&  !overlap_with_lepton[i]) do_toptag_reco = true;
      }
    }
  }

  if(!do_toptag_reco){ // AK4 reconstruction

    unsigned int njets = event.jets->size();
    if(njets > 7) njets = 7;

    unsigned int jetiters = pow(3, njets);
    for(const auto & neutrino_v4 : neutrinos) {
      for (unsigned int j=0; j < jetiters; j++) {

        LorentzVector tophadv4;
        vector<Particle> tophadjets;
        LorentzVector toplepv4 = lepton.v4() + neutrino_v4;
        vector<Particle> toplepjets;
        int num = j;
        ZprimeCandidate candidate;
        candidate.set_is_toptag_reconstruction(false);
        candidate.set_is_puppi_reconstruction(false);

        for (unsigned int k=0; k<njets; k++) {
          if(num%3==0){
            tophadv4 = tophadv4 + event.jets->at(k).v4();
            tophadjets.emplace_back(event.jets->at(k));
          }
          if(num%3==1){
            toplepv4 = toplepv4 + event.jets->at(k).v4();
            toplepjets.emplace_back(event.jets->at(k));
          }
          num /= 3;
        }

        if(tophadjets.size() < 1 || toplepjets.size() < 1) continue;

        // Set all member variables of the candidate
        candidate.set_Zprime_v4(tophadv4 + toplepv4);
        candidate.set_top_hadronic_v4(tophadv4);
        candidate.set_top_leptonic_v4(toplepv4);
        candidate.set_jets_hadronic(tophadjets);
        candidate.set_jets_leptonic(toplepjets);
        candidate.set_lepton(lepton);
        candidate.set_neutrino_v4(neutrino_v4);
        candidate.set_neutrinoindex(neutrinoidx);
        candidates.emplace_back(move(candidate));
      }
      neutrinoidx++;
    }
  }
  else{ // TopTag reconstruction
    for(const auto & neutrino_v4 : neutrinos) {
      for (unsigned int j=0; j < TopTags.size(); j++) {
        if(mode_ == "chs"){
          if(!(matches_chs[j] && has_separated_jet[j] &&  !overlap_with_lepton[j])) continue;

          // Find matched AK8CHS jet
          TopJet chsjet_matched;
          const TopJet* chsjet_matched_ptr;
          for(const TopJet & chsjet : *event.topjets){
            double dR = uhh2::deltaR(chsjet, TopTags.at(j));
            chsjet_matched = chsjet;
            chsjet_matched_ptr = &chsjet;
            if(!(dR < 1.0)) continue;

            //only consider CHS jets not overlapping with the primary lepton
            if(!(deltaR(lepton, chsjet) > 0.8)) continue;

            // Only consider well-separated AK4 jets
            vector<Jet> separated_jets;
            for(unsigned int k = 0; k < event.jets->size(); k++){
              if(deltaR(event.jets->at(k), chsjet_matched) > minDR_) separated_jets.emplace_back(event.jets->at(k));
            }
            unsigned int njets = separated_jets.size();
            if(njets < 1) throw runtime_error("In TopTagReco (CHS): This toptag does not have >= 1 well-separated AK4 jet. This should have been caught by earlier messages. There is a logic error.");
            if(njets > 7) njets = 7;

            unsigned int jetiters = pow(2, njets);
            for (unsigned int k=0; k < jetiters; k++) {

              LorentzVector tophadv4 = chsjet_matched.v4();
              vector<Particle> tophadjets;
              tophadjets.emplace_back(chsjet_matched);
              LorentzVector toplepv4 = lepton.v4() + neutrino_v4;
              vector<Particle> toplepjets;
              int num = k;
              ZprimeCandidate candidate;
              candidate.set_is_toptag_reconstruction(true);
              candidate.set_is_puppi_reconstruction(false);

              for (unsigned int l=0; l<njets; l++) {
                if(num%2==0){
                  toplepv4 = toplepv4 + separated_jets.at(l).v4();
                  toplepjets.emplace_back(separated_jets.at(l));
                }
                num /= 2;
              }

              if(tophadjets.size() < 1 || toplepjets.size() < 1 || separated_jets.size() < 1) continue;

              // Set all member variables of the candidate
              candidate.set_Zprime_v4(tophadv4 + toplepv4);
              candidate.set_top_hadronic_v4(tophadv4);
              candidate.set_top_leptonic_v4(toplepv4);
              candidate.set_jets_hadronic(tophadjets);
              candidate.set_jets_leptonic(toplepjets);
              candidate.set_tophad_topjet_ptr(chsjet_matched_ptr);
              candidate.set_lepton(lepton);
              candidate.set_neutrinoindex(neutrinoidx);
              candidate.set_neutrino_v4(neutrino_v4);
              candidates.emplace_back(candidate);

            }
          }
        }
        else if(mode_ == "puppi"){
          if(!(has_separated_jet[j] &&  !overlap_with_lepton[j])) continue;

          TopJet toptag = TopTags.at(j);
          const TopJet* toptag_ptr = TopTagsPtr.at(j);

          // Only consider well-separated AK4 jets
          vector<Jet> separated_jets;
          for(unsigned int k = 0; k < event.jets->size(); k++){
            if(deltaR(event.jets->at(k), toptag) > minDR_) separated_jets.emplace_back(event.jets->at(k));
          }
          unsigned int njets = separated_jets.size();
          if(njets < 1) throw runtime_error("In TopTagReco (PUPPI): This toptag does not have >= 1 well-separated AK4 jet. This should have been caught by earlier messages. There is a logic error.");
          if(njets > 7) njets = 7;

          unsigned int jetiters = pow(2, njets);
          for (unsigned int k=0; k < jetiters; k++) {

            LorentzVector tophadv4 = toptag.v4();
            vector<Particle> tophadjets;
            tophadjets.emplace_back(toptag);
            LorentzVector toplepv4 = lepton.v4() + neutrino_v4;
            vector<Particle> toplepjets;
            int num = k;
            ZprimeCandidate candidate;
            candidate.set_is_toptag_reconstruction(true);
            candidate.set_is_puppi_reconstruction(true);

            for (unsigned int l=0; l<njets; l++) {
              if(num%2==0){
                toplepv4 = toplepv4 + separated_jets.at(l).v4();
                toplepjets.emplace_back(separated_jets.at(l));
              }
              num /= 2;
            }

            if(tophadjets.size() < 1 || toplepjets.size() < 1 || separated_jets.size() < 1) continue;

            // Set all member variables of the candidate
            candidate.set_Zprime_v4(tophadv4 + toplepv4);
            candidate.set_top_hadronic_v4(tophadv4);
            candidate.set_top_leptonic_v4(toplepv4);
            candidate.set_jets_hadronic(tophadjets);
            candidate.set_jets_leptonic(toplepjets);
            candidate.set_tophad_topjet_ptr(toptag_ptr);
            candidate.set_lepton(lepton);
            candidate.set_neutrinoindex(neutrinoidx);
            candidate.set_neutrino_v4(neutrino_v4);
            candidates.emplace_back(candidate);

          }

        }
      }
      neutrinoidx++;
    }
  }
  // Set the handle with all candidates
  event.set(h_ZprimeCandidates_, candidates);

  return true;
}


ZprimeChi2Discriminator::ZprimeChi2Discriminator(uhh2::Context& ctx){

  h_ZprimeCandidates_ = ctx.get_handle< std::vector<ZprimeCandidate> >("ZprimeCandidates");
  h_is_zprime_reconstructed_ = ctx.get_handle< bool >("is_zprime_reconstructed_chi2");
  h_BestCandidate_ = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");

  mtophad_ = 175.;
  mtophad_ttag_ = 177.;
  sigmatophad_ = 20.;
  sigmatophad_ttag_ = 17.;
  mtoplep_ = 173.;
  mtoplep_ttag_ = 173.;
  sigmatoplep_ = 29.;
  sigmatoplep_ttag_ = 29.;
}

bool ZprimeChi2Discriminator::process(uhh2::Event& event){

  vector<ZprimeCandidate>& candidates = event.get(h_ZprimeCandidates_);
  if(candidates.size() < 1) return false;

  float chi2_best = 99999999;
  ZprimeCandidate* bestCand = &candidates.at(0);
  for(unsigned int i=0; i<candidates.size(); i++){
    bool is_toptag_reconstruction = candidates.at(i).is_toptag_reconstruction();

    float chi2_had = 0.;
    float chi2_lep = 0.;
    float mhad = 0.;
    float mlep = 0.;
    if(is_toptag_reconstruction){

      if(!candidates.at(i).is_puppi_reconstruction()) mhad = candidates.at(i).tophad_topjet_ptr()->softdropmass();
      else{
        LorentzVector SumSubjets(0.,0.,0.,0.);
        for(unsigned int k=0; k<candidates.at(i).tophad_topjet_ptr()->subjets().size(); k++) SumSubjets = SumSubjets + candidates.at(i).tophad_topjet_ptr()->subjets().at(k).v4();
        mhad = inv_mass(SumSubjets);
      }
      mlep = inv_mass(candidates.at(i).top_leptonic_v4());
      chi2_had = pow((mhad - mtophad_ttag_) / sigmatophad_ttag_,2);
      chi2_lep = pow((mlep - mtoplep_ttag_) / sigmatoplep_ttag_,2);
    }
    else{
      mhad = inv_mass(candidates.at(i).top_hadronic_v4());
      mlep = inv_mass(candidates.at(i).top_leptonic_v4());
      chi2_had = pow((mhad - mtophad_) / sigmatophad_,2);
      chi2_lep = pow((mlep - mtoplep_) / sigmatoplep_,2);
    }


    float chi2 = chi2_had + chi2_lep;

    candidates.at(i).set_discriminators("chi2_hadronic", chi2_had);
    candidates.at(i).set_discriminators("chi2_leptonic", chi2_lep);
    candidates.at(i).set_discriminators("chi2_total", chi2);

    if(chi2 < chi2_best){
      chi2_best = chi2;
      bestCand = &candidates.at(i);
    }
  }
  event.set(h_BestCandidate_, bestCand);
  event.set(h_is_zprime_reconstructed_, true);
  return true;
}

// match particle p to one of the jets (Delta R < 0.3); return the deltaR
// of the match.
template<typename T> // T should inherit from Particle
float match_dr(const Particle & p, const std::vector<T> & jets, int& index){
  float mindr = 999999;
  index = -1;
  for(unsigned int i=0; i<jets.size(); ++i){
    float dR = deltaR(p, jets.at(i));
    if( dR <0.3 && dR<mindr) {
      mindr=dR;
      index=i;
    }
  }
  return mindr;
}

ZprimeCorrectMatchDiscriminator::ZprimeCorrectMatchDiscriminator(uhh2::Context& ctx){

  h_ZprimeCandidates_ = ctx.get_handle< std::vector<ZprimeCandidate> >("ZprimeCandidates");
  h_ttbargen_ = ctx.get_handle<TTbarGen>("ttbargen");
  h_is_zprime_reconstructed_ = ctx.get_handle< bool >("is_zprime_reconstructed_correctmatch");
  h_BestCandidate_ = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestCorrectMatch");

  is_mc = ctx.get("dataset_type") == "MC";
  if(is_mc) ttgenprod.reset(new TTbarGenProducer(ctx));
}

bool ZprimeCorrectMatchDiscriminator::process(uhh2::Event& event){

  if(!is_mc) return false;

  // Check if event contains == 2 top quarks
  assert(event.genparticles);
  int n_top = 0, n_antitop = 0;
  for(const auto & gp : *event.genparticles){
    if(gp.pdgId() == 6) n_top++;
    else if(gp.pdgId() == -6) n_antitop++;
  }
  if(n_top != 1 || n_antitop != 1) return false;
  ttgenprod->process(event);

  vector<ZprimeCandidate>& candidates = event.get(h_ZprimeCandidates_);
  if(candidates.size() < 1) return false;

  float dr_best = 99999999; // This number should be larger than the largest possible value from above, just so there is always a 'bestCand' set
  ZprimeCandidate* bestCand = &candidates.at(0);
  TTbarGen ttbargen = event.get(h_ttbargen_);
  for(unsigned int i=0; i<candidates.size(); i++){

    bool is_toptag_reconstruction = candidates.at(i).is_toptag_reconstruction();

    // Gen-Lvl ttbar has to decay semileptonically
    if(ttbargen.DecayChannel() != TTbarGen::e_muhad && ttbargen.DecayChannel() != TTbarGen::e_ehad){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not semileptonic decay" << endl;
      continue;
    }

    vector<Particle> jets_had = candidates.at(i).jets_hadronic();
    vector<Particle> jets_lep = candidates.at(i).jets_leptonic();

    if(jets_lep.size() != 1){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not ==1 leptonic jet" << endl;
      continue;
    }

    if((!is_toptag_reconstruction && jets_had.size() > 3) || (is_toptag_reconstruction && jets_had.size() != 1)){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not right amount of hadronic jets" << endl;
      continue;
    }

    float correct_dr = 0.;
    int idx;

    // Match leptonic b-quark
    float dr = match_dr(ttbargen.BLep(), jets_lep, idx);
    if(dr > 0.3){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not leptonic b-quark matched" << endl;
      continue;
    }
    correct_dr += dr;

    if(!is_toptag_reconstruction){

      unsigned int n_matched = 0;

      // Match hadronic b-quark
      dr = match_dr(ttbargen.BHad(), jets_had, idx);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic b-quark matched (AK4)" << endl;
        continue;
      }
      correct_dr += dr;
      if(idx >= 0) n_matched++;

      //match quarks from W decays to jets
      // First
      dr = match_dr(ttbargen.Q1(), jets_had, idx);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not had Q1 matched (AK4)" << endl;
        continue;
      }
      correct_dr += dr;
      if(idx >= 0) n_matched++;

      // Second
      dr = match_dr(ttbargen.Q2(), jets_had, idx);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not had Q2 matched (AK4)" << endl;
        continue;
      }
      correct_dr += dr;
      if(idx >= 0) n_matched++;

      if(n_matched != jets_had.size()){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not number of jets and matched equal" << endl;
        continue;
      }
    }
    else{
      const TopJet* topjet = candidates.at(i).tophad_topjet_ptr();

      // Match b-quark
      float dr = deltaR(ttbargen.BHad(), *topjet);
      if(dr > 0.8){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic b-quark matched (TTAG)" << endl;
        continue;
      }
      correct_dr += dr;

      //match quarks from W decays to jets
      // First
      dr = deltaR(ttbargen.Q1(), *topjet);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic Q1 matched (TTAG)" << endl;
        continue;
      }
      correct_dr += dr;

      // Second
      dr = deltaR(ttbargen.Q2(), *topjet);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic Q2 matched (TTAG)" << endl;
        continue;
      }
      correct_dr += dr;
    }

    correct_dr += deltaR(ttbargen.Neutrino(), candidates.at(i).neutrino_v4());
    candidates.at(i).set_discriminators("correct_match", correct_dr);

    if(correct_dr < dr_best){
      dr_best = correct_dr;
      bestCand = &candidates.at(i);
    }
  }

  if(dr_best > 10.) return false;
  event.set(h_BestCandidate_, bestCand);
  event.set(h_is_zprime_reconstructed_, true);
  return true;
}

AK8PuppiTopTagger::AK8PuppiTopTagger(uhh2::Context& ctx, int min_num_daughters, float max_dR, float min_mass, float max_mass, float max_tau32) : min_num_daughters_(min_num_daughters), max_dR_(max_dR), min_mass_(min_mass), max_mass_(max_mass), max_tau32_(max_tau32) {

  h_AK8PuppiTopTags_ = ctx.get_handle< std::vector<TopJet> >("AK8PuppiTopTags");
  h_AK8PuppiTopTagsPtr_ = ctx.get_handle< std::vector<const TopJet*> >("AK8PuppiTopTagsPtr");

}

bool AK8PuppiTopTagger::process(uhh2::Event& event){

  std::vector<TopJet> toptags;
  vector<const TopJet*> toptags_ptr;
  for(const TopJet & puppijet : *event.toppuppijets){

    // 1) Jet should have at least two daughters
    int n_constit = 0;
    // Loop over subjets' constituents
    for(unsigned int i=0; i<puppijet.subjets().size(); i++){
      n_constit += puppijet.subjets().at(i).numberOfDaughters();
    }
    if(puppijet.numberOfDaughters() > (int)puppijet.subjets().size()){
      n_constit += (puppijet.numberOfDaughters() - puppijet.subjets().size());
    }

    if(n_constit<min_num_daughters_){
      continue;
    }

    // 3) Cut on SD mass
    LorentzVector SumSubjets(0.,0.,0.,0.);
    for(unsigned int k=0; k<puppijet.subjets().size(); k++) SumSubjets = SumSubjets + puppijet.subjets().at(k).v4();
    float mSD = SumSubjets.M();
    if(!(min_mass_ < mSD && mSD < max_mass_)) continue;

    // 4) Cut on tau 3/2
    if(!((puppijet.tau3() / puppijet.tau2()) < max_tau32_)) continue;

    // All jets at this point are top-tagged
    toptags.emplace_back(puppijet);
    toptags_ptr.emplace_back(&puppijet);
  }
  event.set(h_AK8PuppiTopTags_, toptags);
  event.set(h_AK8PuppiTopTagsPtr_, toptags_ptr);
  return (toptags.size() >= 1);
}

bool JetLeptonDeltaRCleaner::process(uhh2::Event& event){

  assert(event.jets);
  std::vector<Jet> cleaned_jets;

  for(const auto & tjet : *event.jets){
    bool skip_tjet(false);

    if(event.muons){
      for(const auto & muo : *event.muons)
      if(uhh2::deltaR(tjet, muo) < minDR_) skip_tjet = true;
    }

    if(skip_tjet) continue;

    if(event.electrons){
      for(const auto & ele : *event.electrons)
      if(uhh2::deltaR(tjet, ele) < minDR_) skip_tjet = true;
    }

    if(!skip_tjet) cleaned_jets.push_back(tjet);
  }

  event.jets->clear();
  event.jets->reserve(cleaned_jets.size());
  for(const auto& j : cleaned_jets) event.jets->push_back(j);

  return true;
}
////

bool TopJetLeptonDeltaRCleaner::process(uhh2::Event& event){

  assert(event.topjets);
  std::vector<TopJet> cleaned_topjets;

  for(const auto & tjet : *event.topjets){
    bool skip_tjet(false);

    if(event.muons){
      for(const auto & muo : *event.muons)
      if(uhh2::deltaR(tjet, muo) < minDR_) skip_tjet = true;
    }

    if(skip_tjet) continue;

    if(event.electrons){
      for(const auto & ele : *event.electrons)
      if(uhh2::deltaR(tjet, ele) < minDR_) skip_tjet = true;
    }

    if(!skip_tjet) cleaned_topjets.push_back(tjet);
  }

  event.topjets->clear();
  event.topjets->reserve(cleaned_topjets.size());
  for(const auto& j : cleaned_topjets) event.topjets->push_back(j);

  return true;
}
////

const Particle* leading_lepton(const uhh2::Event& event){

  const Particle* lep(0);

  float ptL_max(0.);
  if(event.muons)    { for(const auto& mu : *event.muons)    { if(mu.pt() > ptL_max){ ptL_max = mu.pt(); lep = &mu; } } }
  if(event.electrons){ for(const auto& el : *event.electrons){ if(el.pt() > ptL_max){ ptL_max = el.pt(); lep = &el; } } }

  if(!lep) throw std::runtime_error("leading_lepton -- pt-leading lepton not found");

  return lep;
}

float STlep(const uhh2::Event& event){

  assert((event.muons || event.electrons));

  double stlep = 0.;
  for(const Electron & ele : *event.electrons) stlep += ele.pt();
  for(const Muon & mu : *event.muons)          stlep += mu.pt();

  return stlep;
}

float Muon_pfMINIIso(const Muon& muo, const uhh2::Event&, const std::string& iso_key_){

  float iso(-1.);

  if(!muo.pt()) throw std::runtime_error("Muon_pfMINIIso -- null muon transverse momentum: failed to calculate relative MINI-Isolation");

  if     (iso_key_ == "uncorrected") iso = (muo.pfMINIIso_CH() + muo.pfMINIIso_NH() + muo.pfMINIIso_Ph())/muo.pt();
  else if(iso_key_ == "delta-beta")  iso = (muo.pfMINIIso_CH() + std::max(0., muo.pfMINIIso_NH() + muo.pfMINIIso_Ph() - .5*muo.pfMINIIso_PU()))/muo.pt();
  else if(iso_key_ == "pf-weight")   iso = (muo.pfMINIIso_CH() + muo.pfMINIIso_NH_pfwgt() + muo.pfMINIIso_Ph_pfwgt())/muo.pt();
  else throw std::runtime_error("Muon_pfMINIIso -- invalid key for MINI-Isolation pileup correction: "+iso_key_);

  return iso;
}

float Electron_pfMINIIso(const Electron& ele, const uhh2::Event&, const std::string& iso_key_){

  float iso(-1.);

  if(!ele.pt()) throw std::runtime_error("Electron_pfMINIIso -- null muon transverse momentum: failed to calculate relative MINI-Isolation");

  if     (iso_key_ == "uncorrected") iso = (ele.pfMINIIso_CH() + ele.pfMINIIso_NH() + ele.pfMINIIso_Ph())/ele.pt();
  else if(iso_key_ == "delta-beta")  iso = (ele.pfMINIIso_CH() + std::max(0., ele.pfMINIIso_NH() + ele.pfMINIIso_Ph() - .5*ele.pfMINIIso_PU()))/ele.pt();
  else if(iso_key_ == "pf-weight")   iso = (ele.pfMINIIso_CH() + ele.pfMINIIso_NH_pfwgt() + ele.pfMINIIso_Ph_pfwgt())/ele.pt();
  else throw std::runtime_error("Electron_pfMINIIso -- invalid key for MINI-Isolation pileup correction: "+iso_key_);

  return iso;
}
////

bool trigger_bit(const uhh2::Event& evt_, const std::string& hlt_key_){

  uhh2::Event::TriggerIndex trg_index = evt_.get_trigger_index(hlt_key_);

  return bool(evt_.passes_trigger(trg_index));
}
////

GENWToLNuFinder::GENWToLNuFinder(uhh2::Context& ctx, const std::string& label){

  h_genWln_W_ = ctx.declare_event_output<GenParticle>(label+"_W");
  h_genWln_l_ = ctx.declare_event_output<GenParticle>(label+"_l");
  h_genWln_n_ = ctx.declare_event_output<GenParticle>(label+"_n");
}

bool GENWToLNuFinder::process(uhh2::Event& evt){

  const GenParticle *genW(0), *genW_lep(0), *genW_neu(0); {

    int genwN(0);

    assert(evt.genparticles);
    for(const auto& genp : *evt.genparticles){

      if(genwN > 1) throw std::runtime_error("GENWToLNuFinder::process -- logic error: more than 1 W->lnu decay found at GEN level");

      // gen-W
      const bool is_me = (20 <= genp.status() && genp.status() <= 30);
      if(!is_me) continue;

      const int is_w = (std::abs(genp.pdgId()) == 24);
      if(!is_w) continue;

      genW = &genp;

      // gen-W daughters
      const GenParticle* dau1 = genp.daughter(evt.genparticles, 1);
      const GenParticle* dau2 = genp.daughter(evt.genparticles, 2);

      if(dau1 && dau2){

        const int id1 = std::abs(dau1->pdgId());
        const int id2 = std::abs(dau2->pdgId());

        if((id1 == 11 || id1 == 13 || id1 == 15) &&
        (id2 == 12 || id2 == 14 || id2 == 16) ){ genW_lep = dau1; genW_neu = dau2; ++genwN; }

        if((id2 == 11 || id2 == 13 || id2 == 15) &&
        (id1 == 12 || id1 == 14 || id1 == 16) ){ genW_lep = dau2; genW_neu = dau1; ++genwN; }
      }
    }
  }

  //  if(!genW || !genW_lep || !genW_neu){
  //
  //    std::cout << std::endl;
  //    for(const auto& p : *evt.genparticles){
  //
  //      std::cout <<  " i=" << p.index()    ;
  //      std::cout << " m1=" << p.mother1()  ;
  //      std::cout << " m2=" << p.mother2()  ;
  //      std::cout << " d1=" << p.daughter1();
  //      std::cout << " d2=" << p.daughter2();
  //      std::cout << " ID=" << p.pdgId()    ;
  //      std::cout << " px=" << p.v4().Px()  ;
  //      std::cout << " py=" << p.v4().Py()  ;
  //      std::cout << " pz=" << p.v4().Pz()  ;
  //      std::cout << std::endl;
  //    }
  //  }

  evt.set(h_genWln_W_, genW     ? GenParticle(*genW)     : GenParticle());
  evt.set(h_genWln_l_, genW_lep ? GenParticle(*genW_lep) : GenParticle());
  evt.set(h_genWln_n_, genW_neu ? GenParticle(*genW_neu) : GenParticle());

  return true;
}
////

MEPartonFinder::MEPartonFinder(uhh2::Context& ctx, const std::string& label){

  h_meps_ = ctx.declare_event_output<std::vector<GenParticle> >(label);
}

bool MEPartonFinder::process(uhh2::Event& evt){

  std::vector<GenParticle> mep_refs;

  assert(evt.genparticles);
  for(const auto& genp : *evt.genparticles){

    const bool is_me = (20 <= genp.status() && genp.status() <= 30);
    if(!is_me) continue;

    const bool has_mo1 = (genp.mother1() != (unsigned short)(-1));
    if(!has_mo1) continue;

    const bool has_mo2 = (genp.mother2() != (unsigned short)(-1));
    if(!has_mo2) continue;

    const int abs_id = std::abs(genp.pdgId());
    const bool is_parton = (((1<=abs_id) && (abs_id<=5)) || (abs_id == 21));
    if(!is_parton) continue;

    mep_refs.push_back(genp);
  }

  evt.set(h_meps_, std::move(mep_refs));

  return true;
}
////
