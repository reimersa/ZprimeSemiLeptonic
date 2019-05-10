#include "../include/cosmetics.h"
#include "../include/Tools.h"
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TText.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

using namespace std;

void AnalysisTool::CalculateDNNOutputCuts(){

  // vector with all backgrounds
  vector<TString> bkgnames = {"TTbar", "QCD_Mu", "WJets", "DYJets", "ST"};
  TString signame = "RSGluon_M4000";

  // Get files
  vector<TFile*> bkgfiles;
  for(size_t i=0; i<bkgnames.size(); i++){
    TString infilename = AnalysisTool::base_path_puppi + "/NOMINAL/uhh2.AnalysisModuleRunner.MC." + bkgnames[i] + ".root";
    bkgfiles.emplace_back(new TFile(infilename, "READ"));
  }
  TString infilename_sig = AnalysisTool::base_path_puppi + "/NOMINAL/uhh2.AnalysisModuleRunner.MC." + signame + ".root";
  TFile* sigfile = new TFile(infilename_sig, "READ");

  // Define the order to apply the cuts (numbers correspond to nodes to cut on)
  // 0: QCD, 1: TTbar, 2: DYJets, 3: WJets, 4: SingleTop
  // All cuts are aiming at cutting away background, i.e. the SR is having values SMALLER than the indicated cut value.
  // Probably one should be careful with TTbar and SingleTop, because those are very signal-like
  vector<int> cutorder = {0, 3, 2, 4, 0, 3, 2, 4, 0, 3, 2, 4, 1, 0, 3, 2, 4, 1};

  vector<float> cutvalues = {}; // Contains the last (highest) bin to keep, fill be filled in the same order as 'cutorder'
  map<int, bool> cutdirections; // Contains whether or not to keep the left part of the cut, fill be filled in the same order as 'cutorder'
  vector<float> significances = {};
  vector<int> nodes_already_cut_on = {};

  for(unsigned int i=0; i<cutorder.size(); i++){
    int node = cutorder[i];

    bool node_already_cut_on = false;
    for(size_t j=0; j<nodes_already_cut_on.size(); j++){
      if(node == nodes_already_cut_on[j]) node_already_cut_on = true;
    }

    cout << "Now scanning for the best cut on node " << node << endl;
    for(size_t k=0; k<cutvalues.size(); k++){
      cout << "At cut no. " << k << ", keeping left side: " << cutdirections[cutorder[k]] << endl;
    }

    const int nbins = 100;
    vector<float> bincontents_bkg;
    vector<float> bincontents_sig;
    for(int j=0; j<nbins; j++){
      bincontents_bkg.emplace_back(0.);
      bincontents_sig.emplace_back(0.);
    }
    float stepsize = bincontents_bkg.size();
    stepsize = 1./stepsize;
    float sig_best = -1.;
    float bestvalue = -1;
    for(size_t j=0; j<bkgfiles.size(); j++){
      // Get relevant quantities from files, loop over events
      TTreeReader reader("AnalysisTree", bkgfiles[j]);
      TTreeReaderValue<vector<double>> reader_dnn_output(reader, "dnnoutput");
      TTreeReaderValue<float> reader_eventweight(reader, "eventweight");
      TTreeReaderValue<float> reader_chi2(reader, "chi2_zprime");
      while(reader.Next()) {

        //only consider events that pass the chi2 < 30 cut
        if(*reader_chi2 >= 30) continue;

        bool skip = false;
        vector<double> dnn_output = *reader_dnn_output;
        float eventweight = *reader_eventweight;
        
        //sort out events that have been cut out in an earlier iteration
        for(size_t k=0; k<cutvalues.size(); k++){
          if(cutdirections[cutorder[k]]){
            if(dnn_output[cutorder[k]] > cutvalues[k]) skip = true;
          }
          else{
            if(dnn_output[cutorder[k]] <= cutvalues[k]) skip = true;
          }
        }
        if(skip) continue;

        // Events at this point must be taken into account for the current cut (they passed all earlier cuts)
        int bin = dnn_output[node] * nbins;
        bincontents_bkg[bin] += eventweight;
      }
    }


    // Same for signal
    TTreeReader reader("AnalysisTree", sigfile);
    TTreeReaderValue<vector<double>> reader_dnn_output(reader, "dnnoutput");
    TTreeReaderValue<float> reader_eventweight(reader, "eventweight");
    TTreeReaderValue<float> reader_chi2(reader, "chi2_zprime");
    while(reader.Next()) {

      //only consider events that pass the chi2 < 30 cut
      if(*reader_chi2 >= 30) continue;

      vector<double> dnn_output = *reader_dnn_output;
      float eventweight = *reader_eventweight;
      //sort out events that have been cut out in an earlier iteration
      bool skip = false;
      for(size_t k=0; k<cutvalues.size(); k++){
        // cout << "Applying cut no. " << k << ", which requires: output of node " << cutorder[k] << " < " << cutvalues[k] << endl;
        if(cutdirections[cutorder[k]]){
          if(dnn_output[cutorder[k]] > cutvalues[k]) skip = true;
        }
        else{
          if(dnn_output[cutorder[k]] <= cutvalues[k]) skip = true;
        }
      }
      if(skip) continue;

      // Events at this point must be taken into account for the current cut (they passed all earlier cuts)
      float stepsize = bincontents_sig.size();
      stepsize = 1./stepsize;

      int bin = dnn_output[node] * nbins;
      bincontents_sig[bin] += eventweight;
    }

    bool keep_left_part = true;
    float B = 0., S = 0.;
    if(!node_already_cut_on || (node_already_cut_on && cutdirections[node])){
      // Now go through the vector containing the bkg and sig "bin"contents, look for bin with best significance
      for(size_t j=0; j<bincontents_bkg.size(); j++){
        B += bincontents_bkg[j];
        S += bincontents_sig[j];

        float sig = -1.;
        if(S+B > 0 && B > 0){
          sig = S / (sqrt(S+B));
        }
        else sig = 999999.;
        cout << "current cutvalue: " << (j+1)*0.01 << ", sig with this bin: " << sig << ", S = " << S <<", B = " << B << endl;
        if(sig > sig_best && sig < 999999.){
          sig_best = sig;
          bestvalue = (j+1)*stepsize;
          keep_left_part = true;
        }
      }
    }

    // Now go through the vector containing the bkg and sig "bin"contents, look for bin with best significance KEEPING EVERYTHING GREATER THAN THE GIVEN VALUE
    B = 0.;
    S = 0.;
    if(!node_already_cut_on || (node_already_cut_on && !cutdirections[node])){
      for(size_t j=0; j<bincontents_bkg.size(); j++){
        size_t idx = (bincontents_bkg.size()-1) - j;
        // cout << "idx: " << idx << endl;
        B += bincontents_bkg[idx];
        S += bincontents_sig[idx];

        float sig = -1.;
        if(S+B > 0 && B > 0){
          sig = S / (sqrt(S+B));
        }
        else sig = 999999.;
        cout << "current cutvalue: " << (idx)*0.01 << ", sig with this bin: " << sig << ", S = " << S <<", B = " << B << endl;
        if(sig > sig_best && sig < 999999.){
          sig_best = sig;
          bestvalue = (idx)*stepsize;
          keep_left_part = false;
        }
      }
    }

    // Set 'bestvalue' into the list of cutvalues
    cout << "best cutvalue: " << bestvalue << " with significance: " << sig_best << endl;
    cutvalues.emplace_back(bestvalue);
    significances.emplace_back(sig_best);
    if(!node_already_cut_on){
      cutdirections[node] = keep_left_part;
      cout << "Doing: cutdirections[" << node << "] = " << keep_left_part << endl;
    }
    nodes_already_cut_on.emplace_back(node);

  }

  cout << endl << "Suggested cut-order: " << endl;
  for(size_t i=0; i<cutorder.size(); i++){
    if(cutdirections[cutorder[i]]) cout << "Cut no. " << i+1 << ": Output of node " << cutorder[i] << " < " << cutvalues[i] << ", significance after this cut: " << significances[i] << endl;
    else cout << "Cut no. " << i+1 << ": Output of node " << cutorder[i] << " > " << cutvalues[i] << ", significance after this cut: " << significances[i] << endl;
  }

  delete sigfile;
  for(unsigned int i=0; i<bkgnames.size(); i++) delete bkgfiles[i];
}
