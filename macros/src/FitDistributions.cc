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

void DoFits(TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample);

void AnalysisTool::FitDistributions(){

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

  // DoFits(puppidir, outdir, samplemap, "QCD");
  DoFits(puppidir, outdir, samplemap, "WJets");

}


void DoFits(TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample){
  gStyle->SetOptStat(0);
  // gErrorIgnoreLevel = 2002;

  // Open Files
  // ==========
  TString samplename = samplemap[sample];
  TString infilename_puppi = puppidir + samplename;
  cout << "infilename_puppi: " << infilename_puppi << endl;
  TFile* infile_puppi = new TFile(infilename_puppi, "READ");

  // Folders to compare
  TString CR_name = "";
  TString SR_name = "";
  TString histname = "";
  if(sample == "QCD"){
    CR_name = "DNN_node0_CR_Chi2_General";
    SR_name = "Chi2_General";
    histname = "M_Zprime_rebin3";
  }
  else if(sample == "WJets"){
    CR_name = "DNN_node3_CR_Chi2_General";
    SR_name = "Chi2_General";
    histname = "M_Zprime_rebin3";
  }
  else throw runtime_error("This function is not configured for this sample yet.");



  // Get histograms (only TH1), get corresponding histogram from infile_puppi, plot comparison and ratio, both normalized and un-normalized
  // ======================================================================================================================================


  TString readoutname_cr = CR_name + "/" + histname;
  TString readoutname_sr = SR_name + "/" + histname;
  TH1F* h_sr = (TH1F*)infile_puppi->Get(readoutname_sr);
  TH1F* h_cr = (TH1F*)infile_puppi->Get(readoutname_cr);
  // TH1F* h_sr_norm = (TH1F*)h_sr->Clone();
  // TH1F* h_cr_norm = (TH1F*)h_cr->Clone();
  // h_cr_norm->Scale(1./h_cr_norm->Integral());
  // h_sr_norm->Scale(1./h_sr_norm->Integral());

  if(sample == "QCD"){
    for(int i=1; i<h_cr->GetNbinsX()+1; i++){
      if(h_cr->GetBinCenter(i) > 4000.){
        h_cr->SetBinContent(i,0.);
        h_cr->SetBinError(i,0.);
        // h_cr->SetBinContent(i+1,0.);
        // h_cr->SetBinError(i+1,0.);
        // h_cr->SetBinContent(i+3,0.);
        // h_cr->SetBinError(i+3,0.);
        // h_cr->SetBinContent(i-4,0.);
        // h_cr->SetBinError(i-4,0.);
        break;
      }
    }
  }

  // Fit the two distributions
  // =========================

  float fit_min = 200.;
  float fit_max = 7000.;
  if(sample == "WJets") fit_max = 4600.;

  // TString formula = "((  [0]  * TMath::Landau(x,  [1]  ,  [2]  ,1) * (1-(1+TMath::Erf((x-  [3]  )/  [4]  ))/2))  +  ((1+TMath::Erf((x-  [3]  )/  [4]  ))/2 * (exp((  [5]  *x +  [6]  ) ))))";
  // TString formula = "(    (  [0]  * TMath::Landau(x,  [1]  ,  [2]  ,1) * (1-(1+TMath::Erf((x-  [3]  )/  [4]  ))/2))  +  ((1+TMath::Erf((x-  [3]  )/  [4]  ))/2 * (exp((  [5]  *x +  [6]  ) ))) * (1-(1+TMath::Erf((x-  [7]  )/  [8]  ))/2)  +  ((1+TMath::Erf((x-  [7]  )/  [8]  ))/2 * (exp((  [9]  *x +  [10]  ) )))           )";
  TString formula = "(    (  [0]  * TMath::Landau(x,  [1]  ,  [2]  ,1) * (1-(1+TMath::Erf((x-  [3]  )/  [4]  ))/2))  +  ((1+TMath::Erf((x-  [3]  )/  [4]  ))/2 * (exp((  [5]  *x +  [6]  ) )))            )";

  TF1 *f_sr  = new TF1("f_sr", formula, fit_min, fit_max);
  TF1 *f_cr = new TF1("f_cr", formula, fit_min, fit_max);

  if(sample == "QCD"){
    f_sr->SetParameter(0,5.76328e+08);
    f_sr->SetParameter(1,4.81414e+02);
    f_sr->SetParameter(2,8.82194e+01);
    f_sr->SetParameter(3,8.32948e+02);
    f_sr->SetParameter(4,1.06769e+03);
    f_sr->SetParameter(5,-2.27712e-03);
    f_sr->SetParameter(6,1.16702e+01);


    // Good for rebin2
    // f_cr->SetParameter(0,3.59621e+08);
    // f_cr->SetParameter(1,4.67744e+02);
    // f_cr->SetParameter(2,82);
    // f_cr->SetParameter(3,882);
    // f_cr->SetParameter(4,123);
    // f_cr->SetParameter(5,-0.00381);
    // f_cr->SetParameter(6,15.1);
    // f_cr->SetParameter(7,9000.);
    // f_cr->SetParameter(8,3400.);
    // f_cr->SetParameter(9,-0.0032);
    // f_cr->SetParameter(10,20.);

    // Good for rebin2
    // f_cr->SetParameter(0,3.59621e+08);
    // f_cr->SetParameter(1,4.67744e+02);
    // f_cr->SetParameter(2,82);
    // f_cr->SetParameter(3,882);
    // f_cr->SetParameter(4,123);
    // f_cr->SetParameter(5,-0.00381);
    // f_cr->SetParameter(6,15.1);

    // Good for rebin3
    f_cr->SetParameter(0,4.38394e+09);
    f_cr->SetParameter(1,5.06020e+02);
    f_cr->SetParameter(2,1.04981e+02);
    f_cr->SetParameter(3,-4.94520e+02);
    f_cr->SetParameter(4,1.61252e+03);
    f_cr->SetParameter(5,-2.20300e-03);
    f_cr->SetParameter(6,1.20315e+01);
  }
  else if(sample == "WJets"){
    f_cr->SetParameter(0,4.12836e+08);
    f_cr->SetParameter(1,581.201);
    f_cr->SetParameter(2,106.321);
    f_cr->SetParameter(3,-507.237);
    f_cr->SetParameter(4,1349.71);
    f_cr->SetParameter(5,-0.00248569);
    f_cr->SetParameter(6,11.0338);


    f_sr->SetParameter(0,4.12836e+06);
    f_sr->SetParameter(1,581.201);
    f_sr->SetParameter(2,106.321);
    f_sr->SetParameter(3,-507.237);
    f_sr->SetParameter(4,1349.71);
    f_sr->SetParameter(5,-0.00248569);
    f_sr->SetParameter(6,11.0338);

  }

  TFitResultPtr fit_cr_initial = h_cr->Fit(f_cr,"SR");
  fit_cr_initial->Print("V");
  TFitResultPtr fit_sr_initial = h_sr->Fit(f_sr,"SR");
  fit_sr_initial->Print("V");



  // Now that we have both histograms: Compute ratio, normalized and also un-normalized
  // ==================================================================================

  // TGraphAsymmErrors* g_ratio_norm = new TGraphAsymmErrors(h_sr_norm, h_cr_norm, "pois");


  // Do cosmetics and plot!
  // =====================

  float maximum = 0.;
  for(int i=1; i<h_cr->GetNbinsX()+1; i++){
    if(maximum < h_cr->GetBinContent(i)) maximum = h_cr->GetBinContent(i);
    if(maximum < h_sr->GetBinContent(i)) maximum = h_sr->GetBinContent(i);
  }

  h_cr->SetLineColor(kBlack);
  h_cr->SetMarkerColor(kBlack);
  h_sr->SetLineColor(kBlack);
  h_sr->SetMarkerColor(kBlack);
  h_cr->GetYaxis()->SetRangeUser(5E-4, maximum*10);
  h_cr->GetYaxis()->SetTitle("Events / bin");
  // h_cr_norm->GetYaxis()->SetRangeUser(5E-8, 5E+0);
  // h_cr_norm->GetYaxis()->SetTitle("normalized entries");

  TH1F* h_axis_cr = (TH1F*)h_cr->Clone();
  h_axis_cr->GetYaxis()->SetTitle("MC / fit");
  h_axis_cr->GetYaxis()->SetLabelSize(12);
  h_axis_cr->GetXaxis()->SetTitle(h_cr->GetTitle());
  HistCosmetics(h_axis_cr, true);

  TH1F* h_axis_sr = (TH1F*)h_cr->Clone();
  h_axis_sr->GetYaxis()->SetTitle("MC / fit");
  h_axis_sr->GetYaxis()->SetLabelSize(12);
  h_axis_sr->GetXaxis()->SetTitle(h_cr->GetTitle());
  HistCosmetics(h_axis_sr, true);


  // First for un-normalized histograms
  // ==================================


  HistCosmetics(h_cr, false);
  HistCosmetics(h_sr, false);
  vector<float> x_sr, y_sr, exl_sr, eyl_sr, exh_sr, eyh_sr;
  for(int i=1; i<h_sr->GetNbinsX()+1; i++){
    float num = h_sr->GetBinContent(i);
    float err =  h_sr->GetBinError(i);
    float x = h_sr->GetBinCenter(i);
    float xerr;
    if(i > 1) xerr = fabs(h_sr->GetBinCenter(i-1) - x) / 2.;
    else xerr = fabs(h_sr->GetBinCenter(i+1) - x) / 2.;
    float denom = f_sr->Eval(x);
    float ratio = num/denom;
    float ratio_err = err/denom;

    x_sr.emplace_back(x);
    y_sr.emplace_back(ratio);
    exl_sr.emplace_back(xerr);
    exh_sr.emplace_back(xerr);
    eyl_sr.emplace_back(ratio_err);
    eyh_sr.emplace_back(ratio_err);
  }

  vector<float> x_cr, y_cr, exl_cr, eyl_cr, exh_cr, eyh_cr;
  for(int i=1; i<h_cr->GetNbinsX()+1; i++){
    float num = h_cr->GetBinContent(i);
    float err =  h_cr->GetBinError(i);
    float x = h_cr->GetBinCenter(i);
    float xerr;
    if(i > 1) xerr = fabs(h_cr->GetBinCenter(i-1) - x) / 2.;
    else xerr = fabs(h_cr->GetBinCenter(i+1) - x) / 2.;
    float denom = f_cr->Eval(x);
    float ratio = num/denom;
    float ratio_err = err/denom;

    x_cr.emplace_back(x);
    y_cr.emplace_back(ratio);
    exl_cr.emplace_back(xerr);
    exh_cr.emplace_back(xerr);
    eyl_cr.emplace_back(ratio_err);
    eyh_cr.emplace_back(ratio_err);
  }

  TGraphAsymmErrors* g_ratio_sr = new TGraphAsymmErrors(x_sr.size(),&x_sr[0],&y_sr[0],&exl_sr[0],&exh_sr[0],&eyl_sr[0],&eyh_sr[0]);
  TGraphAsymmErrors* g_ratio_cr = new TGraphAsymmErrors(x_cr.size(),&x_cr[0],&y_cr[0],&exl_cr[0],&exh_cr[0],&eyl_cr[0],&eyh_cr[0]);
  HistCosmetics(g_ratio_sr, true);
  HistCosmetics(g_ratio_cr, true);

  TCanvas* c_out = new TCanvas("c_out", "Fit in CR", 400, 400);
  TPad* pad_top = SetupRatioPadTop();
  TPad* pad_bot = SetupRatioPad();
  pad_top->Draw();
  pad_bot->Draw();
  pad_top->cd();
  h_cr->Draw("E");
  pad_top->SetLogy();

  pad_bot->cd();
  h_axis_cr->Draw("AXIS");
  g_ratio_cr->Draw("P SAME");

  TLine* line1 = new TLine(h_axis_cr->GetBinLowEdge(1), 1, h_axis_cr->GetBinLowEdge(h_axis_cr->GetNbinsX()+1), 1);
  line1->SetLineWidth(2);
  line1->SetLineColor(kRed);
  line1->SetLineStyle(1);
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
  TLatex *text2 = new TLatex(3.5, 24, "control region, "+sampletext);
  text2->SetNDC();
  text2->SetTextAlign(33);
  text2->SetX(0.53);
  text2->SetTextFont(43);
  text2->SetTextSize(16);
  text2->SetY(0.98);
  text2->Draw("SAME");

  c_out->SaveAs(outdir + "FitDistributions_" + sample + "_CR_" + histname + ".eps");
  c_out->SaveAs("Plots/FitDistributions/FitDistributions_" + sample + "_CR_" + histname + ".eps");
  // delete c_out;

  TCanvas* c_out2 = new TCanvas("c_out2", "Fit in SR", 400, 400);
  pad_top = SetupRatioPadTop();
  pad_bot = SetupRatioPad();
  pad_top->Draw();
  pad_bot->Draw();
  pad_top->cd();
  h_sr->Draw("E SAME");
  pad_top->SetLogy();

  pad_bot->cd();
  h_axis_sr->Draw("AXIS");
  g_ratio_sr->Draw("P SAME");

  line1 = new TLine(h_axis_sr->GetBinLowEdge(1), 1, h_axis_sr->GetBinLowEdge(h_axis_sr->GetNbinsX()+1), 1);
  line1->SetLineWidth(2);
  line1->SetLineColor(kRed);
  line1->SetLineStyle(1);
  line1->Draw("SAME");

  pad_top->cd();
  text1->Draw("SAME");
  text2 = new TLatex(3.5, 24, "signal region, "+sampletext);
  text2->SetNDC();
  text2->SetTextAlign(33);
  text2->SetX(0.53);
  text2->SetTextFont(43);
  text2->SetTextSize(16);
  text2->SetY(0.98);
  text2->Draw("SAME");

  c_out2->SaveAs(outdir + "FitDistributions_" + sample + "_SR_" + histname + ".eps");
  c_out2->SaveAs("Plots/FitDistributions/FitDistributions_" + sample + "_SR_" + histname + ".eps");
  delete c_out;
  delete c_out2;


  // Calculate ratio of two fitfunctions
  // ===================================

  vector<float> x, alpha;
  for(int i=0; i<fit_max; i++){
    alpha.emplace_back(f_sr->Eval(i) / f_cr->Eval(i));
    x.emplace_back(i);
    // cout << "Mtt = " << i << ", alpha = " << alpha[i] << endl;
  }
  TGraph* g_alpha = new TGraph(alpha.size(), &x[0], &alpha[0]);
  TGraphAsymmErrors* g_ratio = new TGraphAsymmErrors(h_sr, h_cr, "pois");
  HistCosmetics(g_alpha);
  HistCosmetics(g_ratio);

  TCanvas* c_out3 = new TCanvas("c_out3", "Alpha", 400, 400);
  g_ratio->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
  g_ratio->GetYaxis()->SetTitle("SR / CR");
  g_alpha->SetMarkerColor(kRed+1);
  g_alpha->SetLineColor(kRed+1);
  g_ratio->Draw("AP");
  g_alpha->Draw("L SAME");

  TLegend* leg2 =  new TLegend(0.15, 0.8, .3, .9);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(10);
  leg2->SetLineColor(1);
  leg2->SetTextFont(43);
  leg2->SetTextSize(14);
  leg2->AddEntry(g_ratio, "SR / CR (MC)", "le");
  leg2->AddEntry(g_alpha, "Extrapolation function", "l");
  leg2->Draw("SAME");
  gPad->SetTopMargin(0.03);
  gPad->SetRightMargin(0.03);
  gPad->SetBottomMargin(0.15);
  c_out3->SaveAs("Plots/FitDistributions/Alpha_" + sample + "_" + histname + ".eps");
  delete c_out3;


  // Write extrapolation function to file to use
  // ===========================================

  TString outfilename = puppidir + "ExtrapolationFunction_" + sample + ".root";
  TFile* fout = new TFile(outfilename, "RECREATE");
  g_alpha->Write();
  fout->Close();
  delete fout;


  delete infile_puppi;
}
