#include <TString.h>
#include <TFile.h>

#include "../include/Tools.h"

AnalysisTool::AnalysisTool(bool do_puppi_) : do_puppi(do_puppi_)
{
  tag = "2017_WithDNN_Fixed";
  dnntag = "2017_WithDNN_Fixed_Cuts";
  base_path_puppi = "/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/" + tag + "_Puppi";
  base_path_chs = "/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/" + tag;
  dnn_path_puppi = "/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/DNNSelection/" + dnntag + "_Puppi";
  path_theta = "/nfs/dust/cms/user/reimersa/theta_Zprime/utils2/2017_WithDNN_Fixed_Cuts_Puppi/";
  signalmasses = {500, 750, 1000, 1250, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000};
  for(unsigned int i=0; i<signalmasses.size(); i++){
    TString t = "";
    t += signalmasses[i];
    signalmasses_str.emplace_back(t);
  }

  histnames = {"Weights", "Muon1", "Trigger", "Muon2", "Electron1", "TwoDCut", "Jet1", "Jet2", "STlepPlusMet", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction"};
}
