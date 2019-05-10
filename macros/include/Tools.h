#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>

class AnalysisTool {

public:

  // Constructors, destructor
  AnalysisTool(bool do_puppi_);
  AnalysisTool(const AnalysisTool &) = default;
  AnalysisTool & operator = (const AnalysisTool &) = default;
  ~AnalysisTool() = default;

  // Main functions
  void CalculateReconstructionQuality();
  void CalculateChi2Values();
  void CompareCHSPuppi();
  void CompareShapes();
  void FitDistributions();
  void ExtrapolateData();
  void CalculateBackgroundComposition();
  void PlotLimits(bool draw_data = false);
  void PlotPostfitDistributions();
  void PlotPostfitParameters();
  void ProduceThetaHistograms();
  void ProduceThetaDNNHistograms();
  void CalculateDNNEfficiencies();
  void CalculateDNNOutputCuts();

private:
  bool do_puppi;
  TString tag, dnntag;
  TString base_path_puppi;
  TString base_path_chs;
  TString dnn_path_puppi;
  TString path_theta;
  std::vector<float> signalmasses;
  std::vector<TString> signalmasses_str;
  std::vector<TString> histnames;



};
