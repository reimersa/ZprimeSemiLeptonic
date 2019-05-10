{
  gStyle->SetOptStat(0);

  vector<TString> masses = {"500","1000","2000","4000"};
  vector<double> d_masses = {500, 2000, 4000, 6000};
  cout << "Normalized widths: " << endl;
  TLegend* leg = new TLegend(0.45,0.45,0.85,0.75);
  TCanvas* c = new TCanvas("c", "c", 800, 800);
  for(unsigned int i=0; i<masses.size(); i++){

    //Input files
    TFile* f1 = new TFile("/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/2017_Moriond19JEC_RightLumiweights_Puppi/NOMINAL/uhh2.AnalysisModuleRunner.MC.RSGluon_M" + masses[i] + ".root", "READ");

    //Histograms
    TH1D* h1 = (TH1D*)f1->Get("Chi2_General/M_Zprime_rebin2");

    //Normalize
    h1->Scale(1/h1->Integral());

    h1->SetLineWidth(2);
    h1->SetLineColor(i+2);

    if(i==0){
      h1->SetLineColor(kRed+1);
      h1->Draw("HIST");
      h1->GetXaxis()->SetTitle("M_{t#bar{t}}^{rec} [GeV]");
      h1->GetXaxis()->SetTitleSize(0.045);
      h1->GetYaxis()->SetTitle("event fraction");
      h1->GetYaxis()->SetTitleSize(0.044);
      h1->GetYaxis()->SetTitleOffset(1.19);
      h1->GetYaxis()->SetRangeUser(0., 0.40);
      h1->SetTitle("");
      leg->AddEntry(h1, "M_{g_{KK}} = 500 GeV", "l");
    }
    else h1->Draw("HIST SAME");
    if(i==1){
      h1->SetLineColor(kGreen+1);
      leg->AddEntry(h1, "M_{g_{KK}} = 1000 GeV", "l");
    }
    else if(i==2){
      h1->SetLineColor(kBlue+1);
      leg->AddEntry(h1, "M_{g_{KK}} = 2000 GeV", "l");
    }
    else if(i==3){
      h1->SetLineColor(kOrange+1);
      leg->AddEntry(h1, "M_{g_{KK}} = 4000 GeV", "l");
    }

    cout << masses[i] << " : " << h1->GetRMS() / d_masses[i] << endl;

  }
  leg->SetBorderSize(0);
  leg->Draw();


  TString cmstext = "CMS";
  TLatex *text2 = new TLatex(3.5, 24, cmstext);
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.15);
  text2->SetTextFont(62);
  text2->SetTextSize(0.062);
  text2->SetY(0.86);
  text2->Draw();

  TString supptext = "Simulation";
  TLatex *text4 = new TLatex(3.5, 24, supptext);
  text4->SetNDC();
  text4->SetTextAlign(13);
  text4->SetX(0.29);
  text4->SetTextFont(52);
  text4->SetTextSize(0.045);
  text4->SetY(0.85);
  text4->Draw();

  TString wiptext = "Work in Progress";
  TLatex *text5 = new TLatex(3.5, 24, wiptext);
  text5->SetNDC();
  text5->SetTextAlign(13);
  text5->SetX(0.15);
  text5->SetTextFont(52);
  text5->SetTextSize(0.045);
  text5->SetY(0.79);
  text5->Draw();




  c->SaveAs("NormalizedMttbar.eps");











}
