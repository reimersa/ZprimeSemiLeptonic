#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include "UHH2/common/include/PrintingModules.h"

#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include "UHH2/common/include/LuminosityHists.h"
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <UHH2/common/include/NeuralNetworkBase.hpp>
#include "TFile.h"
#include "TGraph.h"

using namespace std;
using namespace uhh2;


typedef std::vector < std::vector < double > > Matrix2D;

/*
██████  ███████ ███████ ██ ███    ██ ██ ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██ ████   ██ ██    ██    ██ ██    ██ ████   ██
██   ██ █████   █████   ██ ██ ██  ██ ██    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██ ██  ██ ██ ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████ ██      ██ ██   ████ ██    ██    ██  ██████  ██   ████
*/

class ZprimeDNNAnalysisModule : public ModuleBASE {

public:
  explicit ZprimeDNNAnalysisModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:

  // Scale Factors -- Systematics
  unique_ptr<MCMuonScaleFactor> MuonID_module, MuonTrigger_module;

  // AnalysisModules
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, CSVWeight_module, printer_genparticles, scale_module;

  // Taggers
  unique_ptr<AK8PuppiTopTagger> TopTaggerPuppi;

  // Mass reconstruction
  unique_ptr<ZprimeCandidateBuilder> CandidateBuilder;

  // Handle builder
  unique_ptr<ZprimeHandleBuilder> HandleBuilder_module;

  // Chi2 discriminator
  unique_ptr<ZprimeChi2Discriminator> Chi2DiscriminatorZprime;
  unique_ptr<ZprimeCorrectMatchDiscriminator> CorrectMatchDiscriminatorZprime;

  // Selections
  unique_ptr<Selection> TwoDCut_selection, Jet1_selection, Jet2_selection, STlepPlusMet_selection, Chi2_selection, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection, BlindData_selection;
  unique_ptr<Selection> DNN_QCDSel, DNN_DYJetsSel, DNN_WJetsSel;

  // Handles
  Event::Handle<bool> h_is_zprime_reconstructed_chi2, h_is_zprime_reconstructed_correctmatch;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;

  // DNN
  unique_ptr<NeuralNetworkBase> DNNClassifier;
  Event::Handle<vector<double>> h_dnnoutput;
  // Event::Handle<bool> h_is_dnn_predicted;

  // Data-driven background extrapolation functions
  std::unique_ptr<TFile> file_alpha_qcd, file_alpha_wjets;
  std::unique_ptr<TGraph> alpha_qcd, alpha_wjets;

  // Configuration
  bool isMC, ispuppi, islooserselection, do_scale_variation;
  string Sys_MuonID, Sys_MuonTrigger, Sys_PU, Sys_CSV;
  TString sample;
  int runnr_oldtriggers = 299368;

  vector<int> nodes;
  vector<TString> nodes_str;
  vector<double> outputcut;
  vector<TString> outputcut_str;
};

void ZprimeDNNAnalysisModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag + "_Skimming";
    // book_HFolder(mytag, new TTbarLJHistsSkimming(ctx,mytag));
    mytag = tag+"_General";
    book_HFolder(mytag, new ZprimeSemiLeptonicHists(ctx,mytag));
    mytag = tag+"_Muons";
    book_HFolder(mytag, new MuonHists(ctx,mytag));
    mytag = tag+"_Electrons";
    book_HFolder(mytag, new ElectronHists(ctx,mytag));
    mytag = tag+"_Jets";
    book_HFolder(mytag, new JetHists(ctx,mytag));
    mytag = tag+"_Event";
    book_HFolder(mytag, new EventHists(ctx,mytag));
    mytag = tag+"_Generator";
    book_HFolder(mytag, new ZprimeSemiLeptonicGeneratorHists(ctx,mytag));
  }
}

void ZprimeDNNAnalysisModule::fill_histograms(uhh2::Event& event, string tag){
  string mytag = tag + "_Skimming";
  // HFolder(mytag)->fill(event);
  mytag = tag+"_General";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Muons";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Electrons";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Jets";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Event";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Generator";
  HFolder(mytag)->fill(event);
}

/*
█  ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████
█ ██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█ ██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████
█ ██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█  ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

ZprimeDNNAnalysisModule::ZprimeDNNAnalysisModule(uhh2::Context& ctx){

  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  // Important selection values
  islooserselection = (ctx.get("is_looser_selection") == "true");
  double muon_pt(55.);
  double jet1_pt(150.);
  double jet2_pt(50.);
  double stlep_plus_met(150.);
  double chi2_max(30.);
  double mtt_blind(3000.);
  string trigger1 = "HLT_Mu50_v*";
  string trigger2 = "HLT_OldMu100_v*";
  string trigger3 = "HLT_TkMu100_v*";
  double TwoD_dr = 0.4, TwoD_ptrel = 25.;
  if(islooserselection){
    jet1_pt = 100.;
    TwoD_dr = 0.05;
    TwoD_ptrel = 3.;
    stlep_plus_met = 100.;
  }

  const MuonId muonID(PtEtaCut(muon_pt, 2.4));


  // Configuration
  isMC = (ctx.get("dataset_type") == "MC");
  ispuppi = (ctx.get("is_puppi") == "true");
  do_scale_variation       = (ctx.get("ScaleVariationMuR") == "up" || ctx.get("ScaleVariationMuR") == "down") || (ctx.get("ScaleVariationMuF") == "up" || ctx.get("ScaleVariationMuF") == "down");
  TString mode = "chs";
  if(ispuppi) mode = "puppi";
  string tmp = ctx.get("dataset_version");
  sample = tmp;
  Sys_MuonID = ctx.get("Sys_MuonID");
  Sys_MuonTrigger = ctx.get("Sys_MuonTrigger");
  Sys_PU = ctx.get("Sys_PU");
  Sys_CSV = ctx.get("Sys_CSV");

  // Modules
  MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/reimersa/CMSSW_9_4_1/src/UHH2/common/data/MuonID_94X_RunBCDEF_SF_ID.root", "NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta", 0., "HighPtID", true, Sys_MuonID));
  MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/reimersa/CMSSW_9_4_1/src/UHH2/common/data/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "Mu50_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger", true, Sys_MuonTrigger));
  scale_module.reset(new MCScaleVariation(ctx));


  file_alpha_qcd.reset(new TFile("/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/DNNSelection/2017_WithDNN_Fixed_Cuts_Puppi/NOMINAL/ExtrapolationFunction_QCD.root","READ"));
  file_alpha_wjets.reset(new TFile("/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/DNNSelection/2017_WithDNN_Fixed_Cuts_Puppi/NOMINAL/ExtrapolationFunction_WJets.root","READ"));
  alpha_qcd.reset((TGraph*)file_alpha_qcd->Get("Graph"));
  alpha_wjets.reset((TGraph*)file_alpha_wjets->Get("Graph"));

  // HandleBuilder_module.reset(new ZprimeHandleBuilder(ctx));
  // DNNClassifier.reset(new NeuralNetworkBase(ctx, "../DNNWeights"));
  h_dnnoutput = ctx.get_handle<vector<double>>("dnnoutput");
  // h_is_dnn_predicted = ctx.get_handle<bool>("is_dnn_predicted");
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");

  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  CSVWeight_module.reset(new MCCSVv2ShapeSystematic(ctx, "jets",Sys_CSV,"iterativefit","","MCCSVv2ShapeSystematic"));

  // Selection modules
  TwoDCut_selection.reset(new TwoDCut(TwoD_dr, TwoD_ptrel));
  Jet1_selection.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  Jet2_selection.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  STlepPlusMet_selection.reset(new STlepPlusMetCut(stlep_plus_met, -1.));
  Chi2_selection.reset(new Chi2Cut(ctx, 0., chi2_max));
  TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2CandidateMatched_selection.reset(new Chi2CandidateMatchedSelection(ctx));
  ZprimeTopTag_selection.reset(new ZprimeTopTagSelection(ctx));
  BlindData_selection.reset(new BlindDataSelection(ctx, mtt_blind));

  DNN_QCDSel.reset(new DNNSelection(ctx, 0, 0.5));
  DNN_WJetsSel.reset(new DNNSelection(ctx, 3, 0.5));
  DNN_DYJetsSel.reset(new DNNSelection(ctx, 2, 0.5));

  nodes = {0,1,2,3,4};
  nodes_str = {"00", "01", "02", "03", "04"};
  outputcut = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  outputcut_str = {"01", "02", "03", "04", "05", "06", "07", "08", "09"};


  // Taggers
  TopTaggerPuppi.reset(new AK8PuppiTopTagger(ctx));

  // Zprime candidate builder
  CandidateBuilder.reset(new ZprimeCandidateBuilder(ctx, mode));

  // Zprime discriminators
  Chi2DiscriminatorZprime.reset(new ZprimeChi2Discriminator(ctx));
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  CorrectMatchDiscriminatorZprime.reset(new ZprimeCorrectMatchDiscriminator(ctx));
  h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");

  // Book histograms
  // vector<string> histogram_tags = {"DNN", "QCD_CR", "QCD_CR_Chi2", "NotQCD_CR", "WJets_CR", "WJets_CR_Chi2", "NotWJets_CR", "DYJets_CR", "DYJets_CR_Chi2", "NotDYJets_CR", "Jet1", "Jet2", "STlepPlusMet", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction"};
  vector<string> histogram_tags = {"DNN"};
  // for(unsigned int node = 0; node < nodes.size(); node++){
  //   for(unsigned int cut = 0; cut < outputcut.size(); cut++){
  //     TString histname = "DNN_" + nodes_str[node] + "_" + outputcut_str[cut];
  //     histogram_tags.emplace_back((string)histname);
  //   }
  // }
  vector<string> additional_hists = {"DNN_node0_CR", "DNN_node0_CR_Chi2", "DNN_node0_CR_TopTagReconstruction", "DNN_node0_CR_NotTopTagReconstruction", "DNN_node0_CR_reweighted_Chi2", "DNN_node0_CR_reweighted_TopTagReconstruction", "DNN_node0_CR_reweighted_NotTopTagReconstruction", "DNN_node0_SR", "DNN_node3_CR", "DNN_node3_CR_Chi2", "DNN_node3_CR_TopTagReconstruction", "DNN_node3_CR_NotTopTagReconstruction", "DNN_node3_CR_reweighted_Chi2", "DNN_node3_CR_reweighted_TopTagReconstruction", "DNN_node3_CR_reweighted_NotTopTagReconstruction", "DNN_node3_SR", "DNN_node2_CR", "DNN_node2_CR_Chi2", "DNN_node2_CR_TopTagReconstruction", "DNN_node2_CR_NotTopTagReconstruction", "DNN_node2_SR", "DNN_node4_CR", "DNN_node4_CR_Chi2", "DNN_node4_CR_TopTagReconstruction", "DNN_node4_CR_NotTopTagReconstruction", "DNN_node4_SR", "DNN_node1_CR", "DNN_node1_CR_Chi2", "DNN_node1_CR_TopTagReconstruction", "DNN_node1_CR_NotTopTagReconstruction", "DNN_node1_SR", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction"};
  for(unsigned int i=0; i<additional_hists.size(); i++) histogram_tags.emplace_back(additional_hists[i]);
  book_histograms(ctx, histogram_tags);

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeDNNAnalysisModule::process(uhh2::Event& event){

  // Initialize reco flags with false
  event.set(h_is_zprime_reconstructed_chi2, false);
  event.set(h_is_zprime_reconstructed_correctmatch, false);
  vector<double> dnnoutput = event.get(h_dnnoutput);


  // Weight modules
  LumiWeight_module->process(event);
  PUWeight_module->process(event);
  CSVWeight_module->process(event);
  MuonID_module->process(event);
  MuonTrigger_module->process_onemuon(event, 0);


  // Run top-tagging
  TopTaggerPuppi->process(event);


  // Reconstruct Z'
  CandidateBuilder->process(event);
  Chi2DiscriminatorZprime->process(event);
  CorrectMatchDiscriminatorZprime->process(event);
  ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
  float Mreco = BestZprimeCandidate->Zprime_v4().M();


  // Blind data
  if(sample.Contains("_blinded")){
    if(!BlindData_selection->passes(event)) return false;
  }

  if(do_scale_variation){
    if( sample.Contains("TTbar") || sample.Contains("DYJets") || sample.Contains("SingleTop") || sample.Contains("WJets") || sample.Contains("ST_")){
      if(event.genInfo->systweights().size() < 10) cout << "SystWeight size: " << event.genInfo->systweights().size() << endl;
      else scale_module->process(event);
    }
  }

  fill_histograms(event, "DNN");


  //
  // // DNN efficiencies
  // for(unsigned int node = 0; node < nodes.size(); node++){
  //   for(unsigned int cut = 0; cut < outputcut.size(); cut++){
  //     if(dnnoutput[nodes[node]] >= outputcut[cut]){
  //       TString histname = "DNN_" + nodes_str[node] + "_" + outputcut_str[cut];
  //       fill_histograms(event, (string)histname);
  //     }
  //   }
  // }


  if(dnnoutput[0] >= 0.91){
    fill_histograms(event, "DNN_node0_CR");

    if(!Chi2_selection->passes(event)) return false;
    fill_histograms(event, "DNN_node0_CR_Chi2");

    if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "DNN_node0_CR_TopTagReconstruction");
    else fill_histograms(event, "DNN_node0_CR_NotTopTagReconstruction");

    // Apply extrapolation weights
    float original_weight = event.weight;
    float alpha = alpha_qcd->Eval(Mreco);
    event.weight *= alpha;

    fill_histograms(event, "DNN_node0_CR_reweighted_Chi2");
    if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "DNN_node0_CR_reweighted_TopTagReconstruction");
    else fill_histograms(event, "DNN_node0_CR_reweighted_NotTopTagReconstruction");

    event.weight = original_weight;

    return false;
  }
  fill_histograms(event, "DNN_node0_SR");

  if(dnnoutput[3] >= 0.46){
    fill_histograms(event, "DNN_node3_CR");

    if(!Chi2_selection->passes(event)) return false;
    fill_histograms(event, "DNN_node3_CR_Chi2");

    if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "DNN_node3_CR_TopTagReconstruction");
    else fill_histograms(event, "DNN_node3_CR_NotTopTagReconstruction");

    // Apply extrapolation weights
    float original_weight = event.weight;
    float alpha = alpha_wjets->Eval(Mreco);
    event.weight *= alpha;

    fill_histograms(event, "DNN_node3_CR_reweighted_Chi2");
    if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "DNN_node3_CR_reweighted_TopTagReconstruction");
    else fill_histograms(event, "DNN_node3_CR_reweighted_NotTopTagReconstruction");

    event.weight = original_weight;

    return false;
  }
  fill_histograms(event, "DNN_node3_SR");

  if(dnnoutput[2] >= 0.06){
    fill_histograms(event, "DNN_node2_CR");

    if(!Chi2_selection->passes(event)) return false;
    fill_histograms(event, "DNN_node2_CR_Chi2");

    if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "DNN_node2_CR_TopTagReconstruction");
    else fill_histograms(event, "DNN_node2_CR_NotTopTagReconstruction");
    return false;
  }
  fill_histograms(event, "DNN_node2_SR");

  if(dnnoutput[4] < 0.02){
    fill_histograms(event, "DNN_node4_CR");

    if(!Chi2_selection->passes(event)) return false;
    fill_histograms(event, "DNN_node4_CR_Chi2");

    if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "DNN_node4_CR_TopTagReconstruction");
    else fill_histograms(event, "DNN_node4_CR_NotTopTagReconstruction");
    return false;
  }
  fill_histograms(event, "DNN_node4_SR");

  if(dnnoutput[1] >= 0.84){
    fill_histograms(event, "DNN_node1_CR");

    if(!Chi2_selection->passes(event)) return false;
    fill_histograms(event, "DNN_node1_CR_Chi2");

    if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "DNN_node1_CR_TopTagReconstruction");
    else fill_histograms(event, "DNN_node1_CR_NotTopTagReconstruction");
    return false;
  }
  fill_histograms(event, "DNN_node1_SR");






  // CR selection

  // // Actually select the QCD CR
  // if(DNN_QCDSel->passes(event)){
  //   fill_histograms(event, "QCD_CR");
  //
  //   if(!Chi2_selection->passes(event)) return false;
  //   fill_histograms(event, "QCD_CR_Chi2");
  //
  //   return false;
  // }
  // else fill_histograms(event, "NotQCD_CR");
  //
  //
  // // Actually select the WJets CR
  // if(DNN_WJetsSel->passes(event)){
  //   fill_histograms(event, "WJets_CR");
  //
  //   if(!Chi2_selection->passes(event)) return false;
  //   fill_histograms(event, "WJets_CR_Chi2");
  //
  //   return false;
  // }
  // else fill_histograms(event, "NotWJets_CR");
  //
  //
  // // Actually select the DYJets CR
  // if(DNN_DYJetsSel->passes(event)){
  //   fill_histograms(event, "DYJets_CR");
  //
  //   if(!Chi2_selection->passes(event)) return false;
  //   fill_histograms(event, "DYJets_CR_Chi2");
  //
  //   return false;
  // }
  // else fill_histograms(event, "NotDYJets_CR");




  // Selection instead of DNN

  // if(!TwoDCut_selection->passes(event)) return false;
  // fill_histograms(event, "TwoDCut");
  //
  // if(!Jet1_selection->passes(event)) return false;
  // fill_histograms(event, "Jet1");
  //
  // if(!Jet2_selection->passes(event)) return false;
  // fill_histograms(event, "Jet2");
  //
  // if(!STlepPlusMet_selection->passes(event)) return false;
  // fill_histograms(event, "STlepPlusMet");


  // Relevant selection

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "MatchableBeforeChi2Cut");
  else fill_histograms(event, "NotMatchableBeforeChi2Cut");

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatchBeforeChi2Cut");
  else fill_histograms(event, "NotCorrectMatchBeforeChi2Cut");

  if(!Chi2_selection->passes(event)) return false;
  fill_histograms(event, "Chi2");

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "Matchable");
  else fill_histograms(event, "NotMatchable");

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatch");
  else fill_histograms(event, "NotCorrectMatch");

  if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "TopTagReconstruction");
  else fill_histograms(event, "NotTopTagReconstruction");







  return false;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeDNNAnalysisModule)
