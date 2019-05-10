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

void DoComparison(TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample);

void AnalysisTool::CompareShapes(){

  // if(!(sample == "QCD" || sample == "TTbar" || sample == "WJets" || sample == "DYJets" || sample == "SingleTop" || sample == "Data")) throw runtime_error("Invalid sample");

  map<TString, TString> samplemap;
  samplemap["Data"] = "uhh2.AnalysisModuleRunner.DATA.DATA_blinded.root";
  samplemap["TTbar"] = "uhh2.AnalysisModuleRunner.MC.TTbar.root";
  samplemap["WJets"] = "uhh2.AnalysisModuleRunner.MC.WJets.root";
  samplemap["DYJets"] = "uhh2.AnalysisModuleRunner.MC.DYJets.root";
  samplemap["SingleTop"] = "uhh2.AnalysisModuleRunner.MC.ST.root";
  samplemap["QCD"] = "uhh2.AnalysisModuleRunner.MC.QCD_Mu.root";

  TString puppidir = AnalysisTool::dnn_path_puppi + "/NOMINAL/";
  TString outdir = puppidir + "Plots/SingleEPS/";

  DoComparison(puppidir, outdir, samplemap, "QCD");

}


void DoComparison(TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample){
  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = 2002;

  // Open Files
  // ==========
  TString samplename = samplemap[sample];
  TString infilename_puppi = puppidir + samplename;
  cout << "infilename_puppi: " << infilename_puppi << endl;
  TFile* infile_puppi = new TFile(infilename_puppi, "READ");

  // Folders to compare
  TString CR_name = "";
  TString SR_name = "";
  if(sample == "QCD"){
    CR_name = "DNN_node0_CR_Chi2_General";
    SR_name = "Chi2_General";
  }
  else throw runtime_error("This function is not configured for this sample yet.");



  // Get histograms (only TH1), get corresponding histogram from infile_puppi, plot comparison and ratio, both normalized and un-normalized
  // ======================================================================================================================================

  infile_puppi->cd(SR_name);
  TDirectory* dir = gDirectory;
  TIter iter = dir->GetListOfKeys();
  TKey* key;

  // Loop over all objects in this dir
  while ((key = (TKey*)iter())) {
    TString myclass = "TH1F";

    // Consider only TH1F objects
    if(key->GetClassName() == myclass){
      TString histname = key->ReadObj()->GetName();
      cout << "histname: " << histname << endl;

      TString readoutname_cr = CR_name + "/" + histname;
      TString readoutname_sr = SR_name + "/" + histname;
      TH1F* h_sr = (TH1F*)infile_puppi->Get(readoutname_sr);
      if(h_sr->Integral() == 0.) continue;
      TH1F* h_cr = (TH1F*)infile_puppi->Get(readoutname_cr);
      TH1F* h_sr_norm = (TH1F*)h_sr->Clone();
      TH1F* h_cr_norm = (TH1F*)h_cr->Clone();
      h_cr_norm->Scale(1./h_cr_norm->Integral());
      h_sr_norm->Scale(1./h_sr_norm->Integral());

      // Now that we have both histograms: Compute ratio, normalized and also un-normalized
      // ==================================================================================

      TGraphAsymmErrors* g_ratio = new TGraphAsymmErrors(h_sr, h_cr, "pois");
      TGraphAsymmErrors* g_ratio_norm = new TGraphAsymmErrors(h_sr_norm, h_cr_norm, "pois");


      // Do cosmetics and plot!
      // =====================

      float maximum = 0.;
      for(int i=1; i<h_cr->GetNbinsX()+1; i++){
        if(maximum < h_cr->GetBinContent(i)) maximum = h_cr->GetBinContent(i);
        if(maximum < h_sr->GetBinContent(i)) maximum = h_sr->GetBinContent(i);
      }

      Int_t col_sr = kRed+1;
      Int_t col_cr = kBlack;
      h_cr->SetLineColor(col_cr);
      h_cr_norm->SetLineColor(col_cr);
      h_sr->SetLineColor(col_sr);
      h_sr_norm->SetLineColor(col_sr);
      g_ratio->SetLineColor(col_sr);
      g_ratio_norm->SetLineColor(col_sr);
      h_cr->GetYaxis()->SetRangeUser(5E-2, maximum*10);
      h_cr->GetYaxis()->SetTitle("Events / bin");
      h_cr_norm->GetYaxis()->SetRangeUser(5E-8, 5E+0);
      h_cr_norm->GetYaxis()->SetTitle("normalized entries");

      TH1F* h_axis = (TH1F*)h_cr->Clone();
      // h_axis->GetYaxis()->SetRangeUser(0.3, 1.7);
      h_axis->GetYaxis()->SetTitle("SR / CR");
      h_axis->GetYaxis()->SetLabelSize(12);
      h_axis->GetXaxis()->SetTitle(h_cr->GetTitle());
      HistCosmetics(h_axis, true);


      // First for un-normalized histograms
      // ==================================

      TCanvas* c_out = new TCanvas("c_out", "Comparison of SR and CR", 400, 400);
      TPad* pad_top = SetupRatioPadTop();
      TPad* pad_bot = SetupRatioPad();
      pad_top->Draw();
      pad_bot->Draw();
      pad_top->cd();
      HistCosmetics(h_cr, false);
      HistCosmetics(h_sr, false);
      h_cr->Draw("E");
      h_sr->Draw("E SAME");

      TLegend* leg1 = new TLegend(0.60, 0.65, 0.90, 0.90);
      leg1->SetFillStyle(0);
      leg1->SetLineWidth(0);
      leg1->AddEntry(h_cr, "CR", "l");
      leg1->AddEntry(h_sr, "SR", "l");
      leg1->Draw("SAME");
      pad_top->SetLogy();

      pad_bot->cd();
      h_axis->Draw("AXIS");
      HistCosmetics(g_ratio, true);
      g_ratio->Draw("EP SAME");

      TLine* line1 = new TLine(h_axis->GetBinLowEdge(1), 1, h_axis->GetBinLowEdge(h_axis->GetNbinsX()+1), 1);
      line1->SetLineWidth(2);
      line1->SetLineColor(kBlack);
      line1->SetLineStyle(2);
      line1->Draw("SAME");

      pad_top->cd();
      TString infotext = "41.5 fb^{-1} (13 TeV)";
      TLatex *text1 = new TLatex(3.5, 24, infotext);
      text1->SetNDC();
      text1->SetTextAlign(33);
      text1->SetX(0.94);
      text1->SetTextFont(43);
      text1->SetTextSize(16);
      text1->SetY(0.995);
      text1->Draw("SAME");

      TString sampletext = sample;
      TLatex *text2 = new TLatex(3.5, 24, sampletext);
      text2->SetNDC();
      text2->SetTextAlign(33);
      text2->SetX(0.3);
      text2->SetTextFont(43);
      text2->SetTextSize(16);
      text2->SetY(0.98);
      text2->Draw("SAME");

      c_out->SaveAs(outdir + "ShapeComparison_" + sample + "_" + histname + ".eps");
      c_out->SaveAs("Plots/ShapeComparison/ShapeComparison_" + sample + "_" + histname + ".eps");
      delete c_out;


      // Normalized histograms
      // =====================

      TCanvas* c_out2 = new TCanvas("c_out2", "Comparison of SR and CR", 400, 400);
      pad_top = SetupRatioPadTop();
      pad_bot = SetupRatioPad();
      pad_top->Draw();
      pad_bot->Draw();
      pad_top->cd();
      HistCosmetics(h_cr_norm, false);
      HistCosmetics(h_sr_norm, false);
      h_cr_norm->Draw("E");
      h_sr_norm->Draw("E SAME");

      TLegend* leg2 = new TLegend(0.60, 0.65, 0.90, 0.90);
      leg2->SetFillStyle(0);
      leg2->SetLineWidth(0);
      leg2->AddEntry(h_cr_norm, "CR", "l");
      leg2->AddEntry(h_sr_norm, "SR", "l");
      leg2->Draw("SAME");
      pad_top->SetLogy();

      pad_bot->cd();
      h_axis->Draw("AXIS");
      HistCosmetics(g_ratio_norm, true);
      g_ratio_norm->Draw("EP SAME");

      line1->Draw("SAME");

      pad_top->cd();
      text1->Draw("SAME");
      text2->Draw("SAME");



      c_out2->SaveAs(outdir + "ShapeComparison_" + sample + "_" + histname + "_norm.eps");
      c_out2->SaveAs("Plots/ShapeComparison/ShapeComparison_" + sample + "_" + histname + "_norm.eps");
      delete c_out2;


    }
  }




  delete infile_puppi;
}
