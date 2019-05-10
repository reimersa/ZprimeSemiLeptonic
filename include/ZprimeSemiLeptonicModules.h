#pragma once

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/NtupleObjects.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/common/include/TTbarGen.h>



class ZprimeHandleBuilder : uhh2::AnalysisModule{

public:
  explicit ZprimeHandleBuilder(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< float > h_eventweight, h_pt_jet1, h_pt_jet2, h_pt_jet3, h_pt_jet4, h_pt_jet5, h_pt_jet6, h_pt_jet7, h_pt_jet8, h_pt_jet9, h_pt_jet10, h_px_jet1, h_px_jet2, h_px_jet3, h_px_jet4, h_px_jet5, h_px_jet6, h_px_jet7, h_px_jet8, h_px_jet9, h_px_jet10, h_py_jet1, h_py_jet2, h_py_jet3, h_py_jet4, h_py_jet5, h_py_jet6, h_py_jet7, h_py_jet8, h_py_jet9, h_py_jet10, h_pz_jet1, h_pz_jet2, h_pz_jet3, h_pz_jet4, h_pz_jet5, h_pz_jet6, h_pz_jet7, h_pz_jet8, h_pz_jet9, h_pz_jet10, h_e_jet1, h_e_jet2, h_e_jet3, h_e_jet4, h_e_jet5, h_e_jet6, h_e_jet7, h_e_jet8, h_e_jet9, h_e_jet10, h_eta_jet1, h_eta_jet2, h_eta_jet3, h_eta_jet4, h_eta_jet5, h_eta_jet6, h_eta_jet7, h_eta_jet8, h_eta_jet9, h_eta_jet10, h_phi_jet1, h_phi_jet2, h_phi_jet3, h_phi_jet4, h_phi_jet5, h_phi_jet6, h_phi_jet7, h_phi_jet8, h_phi_jet9, h_phi_jet10, h_m_jet1, h_m_jet2, h_m_jet3, h_m_jet4, h_m_jet5, h_m_jet6, h_m_jet7, h_m_jet8, h_m_jet9, h_m_jet10, h_csv_jet1, h_csv_jet2, h_csv_jet3, h_csv_jet4, h_csv_jet5, h_csv_jet6, h_csv_jet7, h_csv_jet8, h_csv_jet9, h_csv_jet10;
  uhh2::Event::Handle< float > h_pt_ak8jet1, h_pt_ak8jet2, h_pt_ak8jet3, h_pt_ak8jet4, h_pt_ak8jet5, h_pt_ak8jet6, h_pt_ak8jet7, h_pt_ak8jet8, h_pt_ak8jet9, h_pt_ak8jet10, h_px_ak8jet1, h_px_ak8jet2, h_px_ak8jet3, h_px_ak8jet4, h_px_ak8jet5, h_px_ak8jet6, h_px_ak8jet7, h_px_ak8jet8, h_px_ak8jet9, h_px_ak8jet10, h_py_ak8jet1, h_py_ak8jet2, h_py_ak8jet3, h_py_ak8jet4, h_py_ak8jet5, h_py_ak8jet6, h_py_ak8jet7, h_py_ak8jet8, h_py_ak8jet9, h_py_ak8jet10, h_pz_ak8jet1, h_pz_ak8jet2, h_pz_ak8jet3, h_pz_ak8jet4, h_pz_ak8jet5, h_pz_ak8jet6, h_pz_ak8jet7, h_pz_ak8jet8, h_pz_ak8jet9, h_pz_ak8jet10, h_e_ak8jet1, h_e_ak8jet2, h_e_ak8jet3, h_e_ak8jet4, h_e_ak8jet5, h_e_ak8jet6, h_e_ak8jet7, h_e_ak8jet8, h_e_ak8jet9, h_e_ak8jet10, h_eta_ak8jet1, h_eta_ak8jet2, h_eta_ak8jet3, h_eta_ak8jet4, h_eta_ak8jet5, h_eta_ak8jet6, h_eta_ak8jet7, h_eta_ak8jet8, h_eta_ak8jet9, h_eta_ak8jet10, h_phi_ak8jet1, h_phi_ak8jet2, h_phi_ak8jet3, h_phi_ak8jet4, h_phi_ak8jet5, h_phi_ak8jet6, h_phi_ak8jet7, h_phi_ak8jet8, h_phi_ak8jet9, h_phi_ak8jet10, h_msd_ak8jet1, h_msd_ak8jet2, h_msd_ak8jet3, h_msd_ak8jet4, h_msd_ak8jet5, h_msd_ak8jet6, h_msd_ak8jet7, h_msd_ak8jet8, h_msd_ak8jet9, h_msd_ak8jet10, h_tau1_ak8jet1, h_tau1_ak8jet2, h_tau1_ak8jet3, h_tau1_ak8jet4, h_tau1_ak8jet5, h_tau1_ak8jet6, h_tau1_ak8jet7, h_tau1_ak8jet8, h_tau1_ak8jet9, h_tau1_ak8jet10, h_tau2_ak8jet1, h_tau2_ak8jet2, h_tau2_ak8jet3, h_tau2_ak8jet4, h_tau2_ak8jet5, h_tau2_ak8jet6, h_tau2_ak8jet7, h_tau2_ak8jet8, h_tau2_ak8jet9, h_tau2_ak8jet10, h_tau3_ak8jet1, h_tau3_ak8jet2, h_tau3_ak8jet3, h_tau3_ak8jet4, h_tau3_ak8jet5, h_tau3_ak8jet6, h_tau3_ak8jet7, h_tau3_ak8jet8, h_tau3_ak8jet9, h_tau3_ak8jet10, h_tau21_ak8jet1, h_tau21_ak8jet2, h_tau21_ak8jet3, h_tau21_ak8jet4, h_tau21_ak8jet5, h_tau21_ak8jet6, h_tau21_ak8jet7, h_tau21_ak8jet8, h_tau21_ak8jet9, h_tau21_ak8jet10, h_tau32_ak8jet1, h_tau32_ak8jet2, h_tau32_ak8jet3, h_tau32_ak8jet4, h_tau32_ak8jet5, h_tau32_ak8jet6, h_tau32_ak8jet7, h_tau32_ak8jet8, h_tau32_ak8jet9, h_tau32_ak8jet10;
  uhh2::Event::Handle< float > h_px_mu1, h_py_mu1, h_pz_mu1, h_pt_mu1, h_eta_mu1, h_phi_mu1, h_e_mu1, h_reliso_mu1, h_drmin_mu1_jet, h_ptrel_mu1_jet;
  uhh2::Event::Handle< float > h_px_ele1, h_py_ele1, h_pz_ele1, h_pt_ele1, h_eta_ele1, h_phi_ele1, h_e_ele1, h_reliso_ele1, h_drmin_ele1_jet, h_ptrel_ele1_jet;
  uhh2::Event::Handle< float > h_met_px, h_met_py, h_met, h_stjets, h_stlep, h_st, h_mzprime, h_chi2zprime, h_s11, h_s12, h_s13, h_s22, h_s23, h_s33;
  uhh2::Event::Handle< int > h_n_jets, h_n_bjets_loose, h_n_bjets_med, h_n_bjets_tight, h_n_ak8jets, h_ndaughters_ak8jet1, h_ndaughters_ak8jet2, h_ndaughters_ak8jet3, h_ndaughters_ak8jet4, h_ndaughters_ak8jet5, h_ndaughters_ak8jet6, h_ndaughters_ak8jet7, h_ndaughters_ak8jet8, h_ndaughters_ak8jet9, h_ndaughters_ak8jet10, h_n_mu, h_n_ele, h_npv;


  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;

};

float inv_mass(const LorentzVector&);

class ZprimeCandidateBuilder : uhh2::AnalysisModule{

public:
  explicit ZprimeCandidateBuilder(uhh2::Context&, TString mode, float minDR = 1.2);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<ZprimeCandidate> > h_ZprimeCandidates_;
  uhh2::Event::Handle< std::vector<TopJet> > h_AK8TopTags;
  uhh2::Event::Handle< std::vector<const TopJet*> > h_AK8TopTagsPtr;

  float minDR_;
  TString mode_;

};

class ZprimeChi2Discriminator : uhh2::AnalysisModule{

public:
  explicit ZprimeChi2Discriminator(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<ZprimeCandidate> > h_ZprimeCandidates_;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestCandidate_;
  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_;
  float mtoplep_, mtoplep_ttag_;
  float sigmatoplep_, sigmatoplep_ttag_;
  float mtophad_, mtophad_ttag_;
  float sigmatophad_, sigmatophad_ttag_;

};

class ZprimeCorrectMatchDiscriminator : uhh2::AnalysisModule{

public:
  explicit ZprimeCorrectMatchDiscriminator(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<ZprimeCandidate> > h_ZprimeCandidates_;
  uhh2::Event::Handle<TTbarGen> h_ttbargen_;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestCandidate_;
  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_;

  bool is_mc;
  std::unique_ptr<TTbarGenProducer> ttgenprod;

};

class AK8PuppiTopTagger : public uhh2::AnalysisModule {

public:
  explicit AK8PuppiTopTagger(uhh2::Context&, int min_num_daughters = 2, float max_dR = 1., float min_mass = 105., float max_mass = 210., float max_tau32 = 0.65);
  virtual bool process(uhh2::Event&) override;

private:
  int min_num_daughters_ = 2;
  float max_dR_;
  float min_mass_;
  float max_mass_;
  float max_tau32_;
  uhh2::Event::Handle< std::vector<TopJet> > h_AK8PuppiTopTags_;
  uhh2::Event::Handle< std::vector<const TopJet*> > h_AK8PuppiTopTagsPtr_;
};

class JetLeptonDeltaRCleaner : public uhh2::AnalysisModule {

public:
  explicit JetLeptonDeltaRCleaner(float mindr=0.8): minDR_(mindr) {}
  virtual bool process(uhh2::Event&) override;

private:
  float minDR_;
};
////

class TopJetLeptonDeltaRCleaner : public uhh2::AnalysisModule {

public:
  explicit TopJetLeptonDeltaRCleaner(float mindr=0.8): minDR_(mindr) {}
  virtual bool process(uhh2::Event&) override;

private:
  float minDR_;
};
////

const Particle* leading_lepton(const uhh2::Event&);

float STlep(const uhh2::Event&);

float Muon_pfMINIIso    (const Muon&    , const uhh2::Event&, const std::string&);
float Electron_pfMINIIso(const Electron&, const uhh2::Event&, const std::string&);
////

bool trigger_bit(const uhh2::Event&, const std::string&);
////

class GENWToLNuFinder : public uhh2::AnalysisModule {

public:
  explicit GENWToLNuFinder(uhh2::Context&, const std::string&);
  virtual ~GENWToLNuFinder() {}

  virtual bool process(uhh2::Event&) override;

protected:
  uhh2::Event::Handle<GenParticle> h_genWln_W_;
  uhh2::Event::Handle<GenParticle> h_genWln_l_;
  uhh2::Event::Handle<GenParticle> h_genWln_n_;
};

class MEPartonFinder : public uhh2::AnalysisModule {

public:
  explicit MEPartonFinder(uhh2::Context&, const std::string&);
  virtual ~MEPartonFinder() {}

  virtual bool process(uhh2::Event&) override;

protected:
  uhh2::Event::Handle<std::vector<GenParticle> > h_meps_;
};
////
