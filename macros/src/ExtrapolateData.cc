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
#include <TFitResult.h>
#include <fstream>

using namespace std;

void Extrapolate(TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample);

void AnalysisTool::ExtrapolateData(){

  map<TString, TString> samplemap;
  samplemap["Data"] = "uhh2.AnalysisModuleRunner.DATA.DATA.root";
  samplemap["TTbar"] = "uhh2.AnalysisModuleRunner.MC.TTbar.root";
  samplemap["WJets"] = "uhh2.AnalysisModuleRunner.MC.WJets.root";
  samplemap["DYJets"] = "uhh2.AnalysisModuleRunner.MC.DYJets.root";
  samplemap["SingleTop"] = "uhh2.AnalysisModuleRunner.MC.ST.root";
  samplemap["QCD"] = "uhh2.AnalysisModuleRunner.MC.QCD_Mu.root";

  TString puppidir = AnalysisTool::dnn_path_puppi + "/NOMINAL/";
  TString outdir = puppidir + "Plots/SingleEPS/";

  Extrapolate(puppidir, outdir, samplemap, "QCD");

}


void Extrapolate(TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample){
  gStyle->SetOptStat(0);
  // gErrorIgnoreLevel = 2002;

  // Open Files
  // ==========
  vector<TFile*> infiles_minor;
  TFile *infile_major, *infile_data;
  for (map<TString,TString>::iterator it=samplemap.begin(); it!=samplemap.end(); ++it){
    TString thissample = it->first;
    TString thispath = it->second;
    TString infilename = puppidir + thispath;
    if(thissample == sample) infile_major = new TFile(infilename, "READ");
    else if (thissample == "Data") infile_data = new TFile(infilename, "READ");
    else infiles_minor.emplace_back(new TFile(infilename, "READ"));
    cout << "infilename: " << infilename << endl;
  }
  TString outfilename = puppidir + samplemap[sample];
  outfilename.ReplaceAll("uhh2.AnalysisModuleRunner.MC.", "uhh2.AnalysisModuleRunner.MC.FromData_");
  cout << "outfilename: " << outfilename << endl;
  TFile* outfile = new TFile(outfilename, "RECREATE");

  vector<TString> foldernames_to_take_data_from = {"DNN_node0_CR_reweighted_Chi2", "DNN_node0_CR_reweighted_TopTagReconstruction", "DNN_node0_CR_reweighted_NotTopTagReconstruction"};
  TString string_to_remove;
  if(sample == "QCD") string_to_remove = "DNN_node0_CR_reweighted_";


  // Loop through the entire file and subtract minor backgrounds from data in every single histogram in the "General"-folder (!)
  // ===========================================================================================================================

  // get list of foldernames
  infile_data->cd();
  vector<TString> foldernames;
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(cl->InheritsFrom("TDirectoryFile")){
      TString name = key->ReadObj()->GetName();
      if(name != "SFrame"){
        foldernames.emplace_back(name);
        outfile->mkdir(name);
        // cout << "made dir: " << name << endl;
      }
    }
  }

  vector<TString> replaced_folders = {};
  for(size_t i=0; i<foldernames.size(); i++){
    TString foldername = foldernames.at(i);
    cout << i << " / " << foldernames.size() << endl;

    // Create folder in outputfile

    infile_data->cd(foldername);
    dir = gDirectory;
    iter = dir->GetListOfKeys();

    // Loop over all objects in this dir
    // int idx = 0;
    while ((key = (TKey*)iter())) {
      TString myclass = "TH1F";
      TString myclass2 = "TH2F";

      // Consider only TH1F objects
      if(!(key->GetClassName() == myclass) && !(key->GetClassName() == myclass2)) continue;
      // idx++;
      TString histname = key->ReadObj()->GetName();
      // cout << "idx: " << idx-1 << ", histname: " << histname << endl;
      TString readoutname = foldername + "/" + histname;
      TH1F* h_data = (TH1F*)infile_data->Get(readoutname);
      TH1F* h_major = (TH1F*)infile_major->Get(readoutname);
      vector<TH1F*> h_minors;
      for(size_t j=0; j<infiles_minor.size(); j++) h_minors.emplace_back((TH1F*)infiles_minor[j]->Get(readoutname));
      // cout << "readoutname: " << readoutname << endl;

      // Add minor backgrounds
      TH1F* h_minor = (TH1F*)h_minors[0]->Clone();
      for(size_t j=1; j<h_minors.size(); j++) h_minor->Add(h_minors[j]);

      // Do the subtracting
      TH1F* h_out = (TH1F*)h_data->Clone();
      for(int j=1; j<h_out->GetNbinsX()+1; j++){
        float sf = 1.;
        if(h_minor->GetBinContent(j) + h_major->GetBinContent(j) > 0.) sf = h_out->GetBinContent(j) / (h_minor->GetBinContent(j) + h_major->GetBinContent(j));
        float target_binc = h_out->GetBinContent(j) - sf*h_minor->GetBinContent(j);
        float target_bine = sqrt(pow(h_out->GetBinError(j),2) + pow(sf*h_minor->GetBinError(j),2));
        h_out->SetBinContent(j, target_binc);
        h_out->SetBinError(j, target_bine);
      }

      // Write histogram into the correct folder in the outfile
      // outfile->Open();

      for(size_t j=0; j<foldernames_to_take_data_from.size(); j++){
        if(foldername.Contains(foldernames_to_take_data_from[j])){
          // cout << "Going to replace histograms from folder: " << foldername << endl;
          TString targetfoldername = foldername;
          targetfoldername.ReplaceAll(string_to_remove, "");
          // cout << "Putting them into folder: " << targetfoldername << endl;
          outfile->cd();
          outfile->cd(targetfoldername);
          h_out->Write();
          bool already_in_list = false;
          for(size_t k=0; k<replaced_folders.size(); k++){
            if(replaced_folders[k] == targetfoldername) already_in_list = true;
          }
          if(!already_in_list) replaced_folders.emplace_back(targetfoldername);
        }
      }

      bool write_in_this_folder = true;
      for(size_t j=0; j<replaced_folders.size(); j++){
        if(foldername == replaced_folders[j]){
          // cout << "Skipping folder: " << foldername << ", should have been replaced!" << endl;
          write_in_this_folder = false;
        }
      }
      if(write_in_this_folder){
        outfile->cd();
        outfile->cd(foldername);
        h_out->Write();
      }

      delete h_out;
      delete h_minor;
      delete h_major;
      delete h_data;
      for(size_t j=0; j<infiles_minor.size(); j++) delete h_minors[j];


    }
  }
  outfile->Close();
  delete outfile;
  delete infile_major;
  delete infile_data;
  for(size_t i=0; i<infiles_minor.size(); i++) delete infiles_minor[i];

}
