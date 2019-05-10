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

void AnalysisTool::CalculateBackgroundComposition(){
  gStyle->SetOptStat(0);

  vector<TString> tmp = AnalysisTool::histnames;
  vector<TString> histnames;
  for(unsigned int i=0; i<tmp.size(); i++) if(!tmp[i].Contains("Match")) histnames.emplace_back(tmp[i]);
  vector<TString> processes = {"TTbar", "WJets", "QCD_Mu", "ST", "DYJets"};
  vector<Int_t> colors = {810, 814, 867, 613, 798};

  vector<vector<float>> nevts;
  for(unsigned int i=0; i<processes.size(); i++){
    TString proc = processes.at(i);

    vector<float> nevts_tmp;
    // Open file for this process
    TString infilename = "";
    if(AnalysisTool::do_puppi) infilename = AnalysisTool::base_path_puppi;
    else infilename = AnalysisTool::base_path_chs;
    infilename += "/NOMINAL/uhh2.AnalysisModuleRunner.MC.";
    infilename += proc;
    infilename += ".root";
    TFile* infile = new TFile(infilename, "READ");

    // Go through vector with histnames, store number of events in each 'histfolder' to vector
    for(unsigned int j=0; j<histnames.size(); j++){
      TString histname = histnames.at(j);
      histname += "_General/sum_event_weights";
      TH1F* h = (TH1F*)infile->Get(histname);
      nevts_tmp.emplace_back(h->GetBinContent(1));
      delete h;
    }

    nevts.emplace_back(nevts_tmp);
    delete infile;
  }

  // Histogram containing the relative fractions of each background after each step
  const unsigned int nbins = nevts[0].size();
  vector<TH1F*> h_fractions;

  for(unsigned int i=0; i<processes.size(); i++){

    TString tmpname = "h";
    tmpname += i;
    TH1F* h = new TH1F(tmpname, ";;Fraction of events", nbins, 0, nbins);
    for(unsigned int j=0; j<histnames.size(); j++){
      float sum = 0.;
      for(unsigned int k=0; k<processes.size(); k++) sum += nevts[k][j];
      float frac = nevts[i][j] / sum;
      h->Fill(histnames[j], frac);
    }
    HistCosmetics(h);
    h->SetLineColor(colors[i]);
    h->SetMarkerColor(colors[i]);
    if(i==0){
      h->SetMinimum(0.);
      h->SetMaximum(1.);
      h->GetXaxis()->SetLabelSize(20);
      h->GetXaxis()->SetLabelOffset(0.01);
      h->GetYaxis()->SetTitleSize(30);
      h->GetYaxis()->SetTitleOffset(0.9 );
      h->GetYaxis()->SetLabelSize(30);
      // h->LabelsOption("v", "X");
    }
    h_fractions.emplace_back(h);
  }

  TCanvas* c1 = new TCanvas("c1", "Fractions of backgrounds after each cut", 900, 600);
  gPad->SetTopMargin(0.05);
  gPad->SetBottomMargin(0.18);
  gPad->SetRightMargin(0.21);
  gPad->SetTicks(0,1);
  for(unsigned int i=0; i<h_fractions.size(); i++){
    if(i==0) h_fractions.at(i)->Draw("HIST V");
    else h_fractions.at(i)->Draw("HIST V SAME");
  }

  TLegend* leg1 = new TLegend(0.4,0.6,0.6,0.9);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  for(unsigned int i=0; i<h_fractions.size(); i++){
    TString legname = processes[i];
    if(legname == "QCD_Mu") legname = "QCD";
    else if(legname == "TTbar") legname = "t#bar{t}";
    else if(legname == "ST") legname = "Single t";
    else if(legname == "DYJets") legname = "DY + jets";
    else if(legname == "WJets") legname = "W + jets";
    leg1->AddEntry(h_fractions[i], legname, "L");
  }
  leg1->Draw();

  TString outfilename = "BackgroundComposition";
  TString outpath;
  if(AnalysisTool::do_puppi) outpath = AnalysisTool::base_path_puppi + "/NOMINAL/Plots/";
  else outpath = AnalysisTool::base_path_chs + "/NOMINAL/Plots/";
  outpath += outfilename;
  c1->SaveAs(outpath + ".eps");
  c1->SaveAs(outpath + ".pdf");
  c1->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".eps");
  c1->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".pdf");
  delete c1;


  // Now do cut-flow, just normalize differently!
  vector<TH1F*> h_cutflows;

  for(unsigned int i=0; i<processes.size(); i++){

    TString tmpname = "h_";
    tmpname += i;
    TH1F* h = new TH1F(tmpname, ";;Total selection efficiency", nbins, 0, nbins);
    float sum = nevts[i][0];
    for(unsigned int j=0; j<histnames.size(); j++){
      float frac = nevts[i][j] / sum;
      h->Fill(histnames[j], frac);
    }
    HistCosmetics(h);
    h->SetLineColor(colors[i]);
    h->SetMarkerColor(colors[i]);
    if(i==0){
      h->SetMinimum(1E-5);
      h->SetMaximum(1.);
      h->GetXaxis()->SetLabelSize(20);
      h->GetXaxis()->SetLabelOffset(0.01);
      h->GetYaxis()->SetTitleSize(30);
      h->GetYaxis()->SetTitleOffset(0.9 );
      h->GetYaxis()->SetLabelSize(30);
      // h->LabelsOption("v", "X");
    }
    h_cutflows.emplace_back(h);
  }

  TCanvas* c2 = new TCanvas("c2", "Selection efficiencies after each cut", 900, 600);
  gPad->SetTopMargin(0.05);
  gPad->SetBottomMargin(0.18);
  gPad->SetRightMargin(0.21);
  gPad->SetTicks(0,1);
  for(unsigned int i=0; i<h_cutflows.size(); i++){
    if(i==0) h_cutflows.at(i)->Draw("HIST V");
    else h_cutflows.at(i)->Draw("HIST V SAME");
  }

  TLegend* leg2 = new TLegend(0.55,0.6,0.75,0.9);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  for(unsigned int i=0; i<h_fractions.size(); i++){
    TString legname = processes[i];
    if(legname == "QCD_Mu") legname = "QCD";
    else if(legname == "TTbar") legname = "t#bar{t}";
    else if(legname == "ST") legname = "Single t";
    else if(legname == "DYJets") legname = "DY + jets";
    else if(legname == "WJets") legname = "W + jets";
    leg2->AddEntry(h_fractions[i], legname, "L");
  }
  leg2->Draw();

  outfilename = "CutFlow_LinY";
  if(AnalysisTool::do_puppi) outpath = AnalysisTool::base_path_puppi + "/NOMINAL/Plots/";
  else outpath = AnalysisTool::base_path_chs + "/NOMINAL/Plots/";
  outpath += outfilename;
  c2->SaveAs(outpath + ".eps");
  c2->SaveAs(outpath + ".pdf");
  c2->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".eps");
  c2->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".pdf");

  gPad->SetLogy();
  leg2->SetX1NDC(0.15);
  leg2->SetX2NDC(0.35);
  leg2->SetY1NDC(0.25);
  leg2->SetY2NDC(0.55);
  outfilename = "CutFlow_LogY";
  if(AnalysisTool::do_puppi) outpath = AnalysisTool::base_path_puppi + "/NOMINAL/Plots/";
  else outpath = AnalysisTool::base_path_chs + "/NOMINAL/Plots/";
  outpath += outfilename;
  c2->SaveAs(outpath + ".eps");
  c2->SaveAs(outpath + ".pdf");
  c2->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".eps");
  c2->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".pdf");

  delete c2;


}
