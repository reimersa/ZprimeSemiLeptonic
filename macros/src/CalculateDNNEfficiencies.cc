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

using namespace std;


void DoEff(TString sample, TString path, TString dnntag, map<TString, TString> samplemap, int node, vector<TString> cuts);

void AnalysisTool::CalculateDNNEfficiencies(){

  // vector<TString> cuts = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09"};
  vector<TString> cuts = {"01", "03", "05", "07", "09"};
  vector<int> nodes = {0,1,2,3,4};
  // vector<int> nodes = {0};

  TString path = AnalysisTool::dnn_path_puppi + "/NOMINAL/";

  map<TString, TString> samplemap;
  samplemap["Data"] = "uhh2.AnalysisModuleRunner.DATA.DATA_blinded.root";
  samplemap["TTbar"] = "uhh2.AnalysisModuleRunner.MC.TTbar.root";
  samplemap["WJets"] = "uhh2.AnalysisModuleRunner.MC.WJets.root";
  samplemap["DYJets"] = "uhh2.AnalysisModuleRunner.MC.DYJets.root";
  samplemap["SingleTop"] = "uhh2.AnalysisModuleRunner.MC.ST.root";
  samplemap["QCD"] = "uhh2.AnalysisModuleRunner.MC.QCD_Mu.root";

  for(unsigned int i=0; i<nodes.size(); i++){
    DoEff("Data", path, AnalysisTool::dnntag, samplemap, nodes[i], cuts);
    DoEff("TTbar", path, AnalysisTool::dnntag, samplemap, nodes[i], cuts);
    DoEff("WJets", path, AnalysisTool::dnntag, samplemap, nodes[i], cuts);
    DoEff("DYJets", path, AnalysisTool::dnntag, samplemap, nodes[i], cuts);
    DoEff("SingleTop", path, AnalysisTool::dnntag, samplemap, nodes[i], cuts);
    DoEff("QCD", path, AnalysisTool::dnntag, samplemap, nodes[i], cuts);
  }
}

void DoEff(TString sample, TString path, TString dnntag, map<TString, TString> samplemap, int node, vector<TString> cuts){
  cout << "Hi, now calculating all efficiencies for '" << sample << "' cutting on node " << node << endl;
  gErrorIgnoreLevel=kError;


  cout << "Going to open: " << path+samplemap[sample] << endl;
  TFile* fin = new TFile(path+samplemap[sample], "READ");

  // Get list of folders
  // Folders must have exact same content histogram-wise
  // ===================================================

  fin->cd();
  vector<TString> foldernames;
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(cl->InheritsFrom("TDirectoryFile")){
      bool usethis = false;
      TString name = key->ReadObj()->GetName();
      TString targetfragment = "DNN_0";
      targetfragment += node;
      for(unsigned int i=0; i<cuts.size(); i++){
        TString this_targetfragment = targetfragment + "_" + cuts[i];
        if(name != "SFrame" && name.Contains("_General") && name.Contains(this_targetfragment)) usethis = true;
      }
      if(usethis) foldernames.emplace_back(name);
      // if(name != "SFrame" && name.Contains("_General") && name.Contains(targetfragment)) foldernames.emplace_back(name);
    }
  }

  for(unsigned int i=0; i<foldernames.size(); i++) cout << foldernames[i] << endl;

  TString foldername_baseline = "DNN_General";


  // Get histograms from folders, looping through all of them and getting 10 at a time
  // =================================================================================

  fin->cd(foldername_baseline);
  dir = gDirectory;
  iter = dir->GetListOfKeys();

  // Loop over all objects in this dir
  while ((key = (TKey*)iter())) {
    TString myclass = "TH1F";

    // Consider only TH1F objects
    if(key->GetClassName() == myclass){
      TString histname = key->ReadObj()->GetName();
      // cout << "histname: " << histname << endl;

      TString readoutname_denom = foldername_baseline + "/" + histname;
      TH1F* h_denom = (TH1F*)fin->Get(readoutname_denom);
      // cout << "Opened: " << readoutname_denom << ", binC(1): " << h_denom->GetBinContent(1) << endl;

      vector<TH1F*> h_nums;
      for(unsigned int i=0; i<foldernames.size(); i++){
        TString readoutname_num = foldernames[i] + "/" + histname;
        h_nums.emplace_back((TH1F*)fin->Get(readoutname_num)->Clone());
        // cout << "Opened: " << readoutname_num << ", binC(1): " << h_nums[i]->GetBinContent(1) << endl;
      }

      for(int j=1; j<h_denom->GetNbinsX()+1; j++){
        if(h_denom->GetBinContent(j) < 0) h_denom->SetBinContent(j, 0.00001);
        // cout << "Bincontent denom: " << j << " --> " << h_denom->GetBinContent(j) << endl;
        for(unsigned int k=0; k<h_nums.size(); k++){
          if(h_nums[k]->GetBinContent(j) > h_denom->GetBinContent(j)) h_nums[k]->SetBinContent(j, 0.);
          if(h_nums[k]->GetBinContent(j) > h_denom->GetBinContent(j)) cout << "ATTENTION: " << h_nums[k]->GetBinContent(j) << " > " <<  h_denom->GetBinContent(j) << endl;
        }
      }

      TGraphAsymmErrors* gr_unity = new TGraphAsymmErrors(h_denom, h_denom);
      vector<TGraphAsymmErrors*> gr_effs;
      for(unsigned int i=0; i<foldernames.size(); i++){
        gr_effs.emplace_back(new TGraphAsymmErrors(h_nums[i], h_denom));
        gr_effs[i]->SetMarkerSize(2);
        gr_effs[i]->SetLineWidth(2);
        if(i+1 < 5){ // skip ugly kYellow
          gr_effs[i]->SetLineColor(i+1);
          gr_effs[i]->SetMarkerColor(i+1);
        }
        else{
          gr_effs[i]->SetLineColor(i+2);
          gr_effs[i]->SetMarkerColor(i+2);
        }
      }

      TCanvas* c = new TCanvas("c", "c", 600, 600);
      gr_unity->GetHistogram()->GetYaxis()->SetRangeUser(0,1.55);
      gr_unity->GetHistogram()->GetXaxis()->SetTitle(h_denom->GetTitle());
      gr_unity->GetHistogram()->GetYaxis()->SetTitleOffset(1.);
      gr_unity->GetHistogram()->GetXaxis()->SetTitleOffset(1.05);
      gr_unity->GetHistogram()->GetXaxis()->SetTitleSize(0.045);
      gr_unity->GetHistogram()->GetYaxis()->SetTitleSize(0.045);
      gr_unity->GetHistogram()->GetYaxis()->SetTitle("Selection efficiency");
      gr_unity->GetHistogram()->Draw("AXIS");
      gPad->SetTopMargin(0.02);
      gPad->SetBottomMargin(0.11);
      gPad->SetRightMargin(0.02);
      // gr_unity->Draw("L SAME");
      c->Update();
      TLine *line =new TLine(c->GetUxmin(),1.0,c->GetUxmax(),1.0);
      line->SetLineColor(kBlack);
      line->SetLineWidth(2);
      line->SetLineStyle(9);
      line->Draw("SAME");
      for(unsigned int i=0; i<foldernames.size(); i++){
        gr_effs[i]->Draw("P SAME");
      }

      TLegend* leg = new TLegend(0.66, 0.76, 0.96, 0.96);
      for(unsigned int i=0; i<gr_effs.size(); i++){
        TString entrytitle = "Node ";
        entrytitle += node;
        entrytitle += " output > " + cuts[i];
        leg->AddEntry(gr_effs[i], entrytitle, "l");
      }
      leg->SetBorderSize(0);
      leg->SetTextSize(0.029);
      leg->Draw("SAME");

      TString infotext = "Simulated " + sample + " events";
      if(sample=="DATA") infotext = "Data";
      TLatex *text1 = new TLatex(3.5, 24, infotext);
      text1->SetNDC();
      // text1->SetTextAlign(33);
      text1->SetX(0.66);
      text1->SetTextSize(0.029);
      text1->SetY(0.72);
      text1->Draw();

      TString outname = "Plots/DNNEfficiencies/" + dnntag + "/";
      outname += histname + "_node";
      outname += node;
      outname += "_" + sample + ".eps";
      c->SaveAs(outname);

      for(unsigned int i=0; i<foldernames.size(); i++) delete gr_effs[i];
      delete gr_unity;
      for(unsigned int i=0; i<foldernames.size(); i++) delete h_nums[i];
      delete h_denom;
    }
  }

}
