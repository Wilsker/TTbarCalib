#include "TTbarEventAnalysis.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

void TTbarEventAnalysis::prepareOutput(TString outFile)
{

  //prepare output file
  outF_=TFile::Open(outFile,"RECREATE");

  //Initialise KIN tree. Variables here are being created so name as you please, just be consistent in code that depends on these outputs.
  kinTree_=new TTree("kin","kinematics analysis");
  kinTree_->SetDirectory(outF_);
  kinTree_->Branch("EventInfo",    eventInfo_,         "EventInfo[3]/I");
  kinTree_->Branch("ttbar_chan",    &ttbar_chan_,      "ttbar_chan/I");
  kinTree_->Branch("npvn",    &npv_,      "npv/I");
  kinTree_->Branch("flavour",        jetFlavour_,      "flavour/I");
  kinTree_->Branch("jetmult",       &jetmult_,         "jetmult/I");
  kinTree_->Branch("jetpt",          jetPt_,           "jetpt/F");
  kinTree_->Branch("jeteta",         jetEta_,          "jeteta/F");
  kinTree_->Branch("jetrank",       &jetrank_,          "jetrank/I");
  kinTree_->Branch("close_mlj",      close_mlj_,       "close_mlj[5]/F");
  kinTree_->Branch("close_deta",    &close_deta_,      "close_deta/F");
  kinTree_->Branch("close_dphi",    &close_dphi_,      "close_dphi/F");
  kinTree_->Branch("close_ptrel",   &close_ptrel_,     "close_ptrel/F");
  kinTree_->Branch("close_lj2ll_deta",    &close_lj2ll_deta_,      "close_lj2ll_deta/F");
  kinTree_->Branch("close_lj2ll_dphi",    &close_lj2ll_dphi_,      "close_lj2ll_dphi/F");
  kinTree_->Branch("far_mlj",       &far_mlj_,         "far_mlj/F");
  kinTree_->Branch("far_deta",      &far_deta_,        "far_deta/F");
  kinTree_->Branch("far_dphi",      &far_dphi_,        "far_dphi/F");
  kinTree_->Branch("far_ptrel",     &far_ptrel_,       "far_ptrel/F");
  kinTree_->Branch("far_lj2ll_deta",    &far_lj2ll_deta_,      "far_lj2ll_deta/F");
  kinTree_->Branch("far_lj2ll_dphi",    &far_lj2ll_dphi_,      "far_lj2ll_dphi/F");
  kinTree_->Branch("j2ll_deta",     &j2ll_deta_,       "j2ll_deta/F");
  kinTree_->Branch("j2ll_dphi",     &j2ll_dphi_,       "j2ll_dphi/F");
  kinTree_->Branch("kindisc",        kinDisc_,         "kindisc[5]/F");
  kinTree_->Branch("jp",             &(jp_[0]),              "jp/F");
  kinTree_->Branch("svhe",           &(svhe_[0]),            "svhe/F");
  kinTree_->Branch("csv",            &(csv_[0]),             "csv/F");

  kinTree_->Branch("DeepCSVb",               &(DeepCSVb_[0]),        "DeepCSVb/F");
  kinTree_->Branch("DeepCSVc",               &(DeepCSVc_[0]),        "DeepCSVc/F");
  kinTree_->Branch("DeepCSVl",               &(DeepCSVl_[0]),        "DeepCSVl/F");
  kinTree_->Branch("DeepCSVbb",               &(DeepCSVbb_[0]),        "DeepCSVbb/F");
  kinTree_->Branch("DeepCSVcc",               &(DeepCSVcc_[0]),        "DeepCSVcc/F");
  kinTree_->Branch("DeepCSVbN",               &(DeepCSVbN_[0]),        "DeepCSVbN/F");
  kinTree_->Branch("DeepCSVcN",               &(DeepCSVcN_[0]),        "DeepCSVcN/F");
  kinTree_->Branch("DeepCSVlN",               &(DeepCSVlN_[0]),        "DeepCSVlN/F");
  kinTree_->Branch("DeepCSVbbN",               &(DeepCSVbbN_[0]),        "DeepCSVbbN/F");
  kinTree_->Branch("DeepCSVccN",               &(DeepCSVccN_[0]),        "DeepCSVccN/F");
  kinTree_->Branch("DeepCSVbP",               &(DeepCSVbP_[0]),        "DeepCSVbP/F");
  kinTree_->Branch("DeepCSVcP",               &(DeepCSVcP_[0]),        "DeepCSVcP/F");
  kinTree_->Branch("DeepCSVlP",               &(DeepCSVlP_[0]),        "DeepCSVlP/F");
  kinTree_->Branch("DeepCSVbbP",               &(DeepCSVbbP_[0]),        "DeepCSVbbP/F");
  kinTree_->Branch("DeepCSVccP",               &(DeepCSVccP_[0]),        "DeepCSVccP/F");
  kinTree_->Branch("DeepCSVBDisc",               &(DeepCSVBDisc_[0]),        "DeepCSVBDisc/F");
  kinTree_->Branch("DeepCSVBDiscN",               &(DeepCSVBDiscN_[0]),        "DeepCSVBDiscN/F");
  kinTree_->Branch("DeepCSVBDiscP",               &(DeepCSVb_[0]),        "DeepCSVb/F");
  kinTree_->Branch("DeepCSVCvsLDisc",               &(DeepCSVCvsLDisc_[0]),        "DeepCSVCvsLDisc/F");
  kinTree_->Branch("DeepCSVCvsLDiscN",               &(DeepCSVCvsLDiscN_[0]),        "DeepCSVCvsLDiscN/F");
  kinTree_->Branch("DeepCSVCvsLDiscP",               &(DeepCSVCvsLDiscP_[0]),        "DeepCSVCvsLDiscP/F");
  kinTree_->Branch("DeepCSVCvsBDisc",               &(DeepCSVCvsBDisc_[0]),        "DeepCSVCvsBDisc/F");
  kinTree_->Branch("DeepCSVCvsBDiscN",               &(DeepCSVCvsBDiscN_[0]),        "DeepCSVCvsBDiscN/F");
  kinTree_->Branch("DeepCSVCvsBDiscP",               &(DeepCSVCvsBDiscP_[0]),        "DeepCSVCvsBDiscP/F");
  kinTree_->Branch("DeepFlavourBDisc",            &(DeepFlavourBDisc_[0]),           "DeepFlavourBDisc/F");
  kinTree_->Branch("DeepFlavourCvsLDisc",            &(DeepFlavourCvsLDisc_[0]),           "DeepFlavourCvsLDisc/F");
  kinTree_->Branch("DeepFlavourCvsBDisc",            &(DeepFlavourCvsBDisc_[0]),           "DeepFlavourCvsBDisc/F");
  kinTree_->Branch("DeepFlavourB",            &(DeepFlavourB_[0]),           "DeepFlavourB/F");
  kinTree_->Branch("DeepFlavourBB",            &(DeepFlavourBB_[0]),           "DeepFlavourBB/F");
  kinTree_->Branch("DeepFlavourLEPB",            &(DeepFlavourLEPB_[0]),           "DeepFlavourLEPB/F");
  kinTree_->Branch("weight",         weight_,          "weight[30]/F");

  ftmTree_=new TTree("ftm","flavour tag matching");
  ftmTree_->SetDirectory(outF_);
  ftmTree_->Branch("EventInfo",      eventInfo_,  "EventInfo[3]/I");
  ftmTree_->Branch("ttbar_chan",    &ttbar_chan_, "ttbar_chan/I");
  ftmTree_->Branch("jetmult",       &jetmult_,    "jetmult/I");
  ftmTree_->Branch("flavour",        jetFlavour_, "flavour[2]/I");
  ftmTree_->Branch("jetpt",          jetPt_,      "jetpt[2]/F");
  ftmTree_->Branch("jeteta",         jetEta_,     "jeteta[2]/F");
  ftmTree_->Branch("jp",             jp_,         "jp[2]/F");
  ftmTree_->Branch("svhe",           svhe_,       "svhe[2]/F");
  ftmTree_->Branch("csv",            csv_,        "csv[2]/F");

  ftmTree_->Branch("DeepCSVb",               DeepCSVb_,        "DeepCSVb[2]/F");
  ftmTree_->Branch("DeepCSVc",               DeepCSVc_,        "DeepCSVc[2]/F");
  ftmTree_->Branch("DeepCSVl",               DeepCSVl_,        "DeepCSVl[2]/F");
  ftmTree_->Branch("DeepCSVbb",               DeepCSVbb_,        "DeepCSVbb[2]/F");
  ftmTree_->Branch("DeepCSVcc",               DeepCSVcc_,        "DeepCSVcc[2]/F");
  ftmTree_->Branch("DeepCSVbN",               DeepCSVbN_,        "DeepCSVbN[2]/F");
  ftmTree_->Branch("DeepCSVcN",               DeepCSVcN_,        "DeepCSVcN[2]/F");
  ftmTree_->Branch("DeepCSVlN",               DeepCSVlN_,        "DeepCSVlN[2]/F");
  ftmTree_->Branch("DeepCSVbbN",               DeepCSVbbN_,        "DeepCSVbbN[2]/F");
  ftmTree_->Branch("DeepCSVccN",               DeepCSVccN_,        "DeepCSVccN[2]/F");
  ftmTree_->Branch("DeepCSVbP",               DeepCSVbP_,        "DeepCSVbP[2]/F");
  ftmTree_->Branch("DeepCSVcP",               DeepCSVcP_,        "DeepCSVcP[2]/F");
  ftmTree_->Branch("DeepCSVlP",               DeepCSVlP_,        "DeepCSVlP[2]/F");
  ftmTree_->Branch("DeepCSVbbP",               DeepCSVbbP_,        "DeepCSVbbP[2]/F");
  ftmTree_->Branch("DeepCSVccP",               DeepCSVccP_,        "DeepCSVccP[2]/F");

  ftmTree_->Branch("DeepCSVBDisc",               DeepCSVBDisc_,        "DeepCSVBDisc[2]/F");
  ftmTree_->Branch("DeepCSVBDiscN",               DeepCSVBDiscN_,        "DeepCSVBDiscN[2]/F");
  ftmTree_->Branch("DeepCSVBDiscP",               DeepCSVBDiscP_,        "DeepCSVBDiscP[2]/F");
  ftmTree_->Branch("DeepCSVCvsLDisc",               DeepCSVCvsLDisc_,        "DeepCSVCvsLDisc[2]/F");
  ftmTree_->Branch("DeepCSVCvsLDiscN",               DeepCSVCvsLDiscN_,        "DeepCSVCvsLDiscN[2]/F");
  ftmTree_->Branch("DeepCSVCvsLDiscP",               DeepCSVCvsLDiscP_,        "DeepCSVCvsLDiscP[2]/F");
  ftmTree_->Branch("DeepCSVCvsBDisc",               DeepCSVCvsBDisc_,        "DeepCSVCvsBDisc[2]/F");
  ftmTree_->Branch("DeepCSVCvsBDiscN",               DeepCSVCvsBDiscN_,        "DeepCSVCvsBDiscN[2]/F");
  ftmTree_->Branch("DeepCSVCvsBDiscP",               DeepCSVCvsBDiscP_,        "DeepCSVCvsBDiscP[2]/F");
  ftmTree_->Branch("kindisc",        kinDisc_,    "kindisc[2]/F");
  ftmTree_->Branch("weight",         weight_,     "weight[30]/F");

  // Preparing the histograms: The naming convention here can again be as you decide as you will fill them with the variables you create later.
  std::map<TString,TH1F *> baseHistos;
  baseHistos["npvinc" ]  = new TH1F("npvinc", ";nPV_{incl.};Events",              50, 0, 50);
  baseHistos["npv"    ]  = new TH1F("npv",    ";nPV;Events",              50, 0, 50);
  baseHistos["rho"    ]  = new TH1F("rho",    ";#rho [GeV];Events",                      50, 0, 30);
  baseHistos["mll"    ]  = new TH1F("mll",    ";Dilepton invariant mass [GeV];Events",   20, 0, 300);
  baseHistos["mllinc" ]  = new TH1F("mllinc", ";Dilepton invariant mass [GeV];Events",   20, 0, 300);
  baseHistos["precut_met"]  = new TH1F("precut_met",    ";Missing transverse energy (pre MET cut) [GeV];Events", 15, 0, 300);
  baseHistos["met"    ]  = new TH1F("met",    ";Missing transverse energy [GeV];Events", 15, 0, 300);
  baseHistos["njets"  ]  = new TH1F("njets",  ";Jet multiplicity;Events;",               6,  2, 8);
  baseHistos["leadjpt"]  = new TH1F("leadjpt",";Leading jet p_{T} [GeV];Events;",        14,30,300);
  baseHistos["leadlpt"]  = new TH1F("leadlpt",";Leading lepton p_{T} [GeV];Events;",     9,20,200);
  baseHistos["trailjpt"] = new TH1F("trailjpt",";Trailing jet p_{T} [GeV];Events;",      14,30,300);
  baseHistos["traillpt"] = new TH1F("traillpt",";Trailing lepton p_{T} [GeV];Events;",   9,20,200);
  baseHistos["leadjeta"]    = new TH1F("leadjeta",    ";Pseudo-rapidity; Jets",              25, 0, 3.0);
  baseHistos["trailjeta"]   = new TH1F("trailjeta",    ";Pseudo-rapidity; Jets",              25, 0, 3.0);
  baseHistos["evsel"]    = new TH1F("evsel",   ";Event selection;Events;",               13,0,13);
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(1,"pre-sel");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(2,"Trigger");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(3,"2l_2jet");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(4,"emu");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(5,"Mll");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(6,"lepPts");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(7,"lepEtas");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(8,"Jet Sel");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(9,"MET");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(10,"#geq 2j");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(11,"=2j");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(12,"=3j");
  baseHistos["evsel"]->GetXaxis()->SetBinLabel(13,"=4j");
  baseHistos["jp"]=new TH1F("jp",";Jet probability;Jets",50,0,3);
  baseHistos["svhe"]=new TH1F("svhe",";Simple secondary vertex (HE);Jets",50,0,6);
  baseHistos["csv"]=new TH1F("csv",";Combined secondary vertex (IVF);Jets",50,0,1.1);
  baseHistos["tche"]=new TH1F("tche",";Track Counting High Efficiency;Jets",50,-20,50);
  baseHistos["jetseltrk"]=new TH1F("jetseltrk",";Selected track multiplicity;Jets",15,0,15);
  baseHistos["jp_leadkin"]=new TH1F("jp_leadkin",";Jet probability;Jets",50,0,3);
  baseHistos["svhe_leadkin"]=new TH1F("svhe_leadkin",";Simple secondary vertex (HE);Jets",50,0,6);
  baseHistos["csv_leadkin"]=new TH1F("csv_leadkin",";Combined secondary vertex (IVF);Jets",50,0,1.1);
  baseHistos["DeepCSVb"]=new TH1F("DeepCSVb",";DeepCSV b ;Jets",50,0,1.10);
  baseHistos["DeepCSVc"]=new TH1F("DeepCSVc",";DeepCSV c;Jets",50,0,1.10);
  baseHistos["DeepCSVl"]=new TH1F("DeepCSVl",";DeepCSV l;Jets",50,0,1.10);
  baseHistos["DeepCSVbb"]=new TH1F("DeepCSVbb",";DeepCSV bb;Jets",50,0,1.10);
  baseHistos["DeepCSVcc"]=new TH1F("DeepCSVcc",";DeepCSV cc;Jets",50,0,1.10);
  baseHistos["DeepCSVbN"]=new TH1F("DeepCSVbN",";DeepCSV bN;Jets",50,0,1.10);
  baseHistos["DeepCSVcN"]=new TH1F("DeepCSVcN",";DeepCSV cN;Jets",50,0,1.10);
  baseHistos["DeepCSVlN"]=new TH1F("DeepCSVlN",";DeepCSV lN;Jets",50,0,1.10);
  baseHistos["DeepCSVbbN"]=new TH1F("DeepCSVbbN",";DeepCSV bbN;Jets",50,0,1.10);
  baseHistos["DeepCSVccN"]=new TH1F("DeepCSVccN",";DeepCSV ccN;Jets",50,0,1.10);
  baseHistos["DeepCSVbP"]=new TH1F("DeepCSVbP",";DeepCSV bP;Jets",50,0,1.10);
  baseHistos["DeepCSVcP"]=new TH1F("DeepCSVcP",";DeepCSV cP;Jets",50,0,1.10);
  baseHistos["DeepCSVlP"]=new TH1F("DeepCSVlP",";DeepCSV lP;Jets",50,0,1.10);
  baseHistos["DeepCSVbbP"]=new TH1F("DeepCSVbbP",";DeepCSV bbP;Jets",50,0,1.10);
  baseHistos["DeepCSVccP"]=new TH1F("DeepCSVccP",";DeepCSV ccP;Jets",50,0,1.10);
  baseHistos["DeepCSVBDisc"]=new TH1F("DeepCSVBDisc",";DeepCSV B Disc. ;Jets",50,0,1.10);
  baseHistos["DeepCSVBDiscN"]=new TH1F("DeepCSVBDiscN",";DeepCSV B Disc. N ;Jets",50,0,1.10);
  baseHistos["DeepCSVBDiscP"]=new TH1F("DeepCSVBDiscP",";DeepCSV B Disc. P ;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsLDisc"]=new TH1F("DeepCSVCvsLDisc",";DeepCSV CvsL Disc. ;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsLDiscN"]=new TH1F("DeepCSVCvsLDiscN",";DeepCSV CvsL Disc. N ;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsLDiscP"]=new TH1F("DeepCSVCvsLDiscP",";DeepCSV CvsL Disc. P ;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsBDisc"]=new TH1F("DeepCSVCvsBDisc",";DeepCSV CvsB Disc. ;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsBDiscN"]=new TH1F("DeepCSVCvsBDiscN",";DeepCSV CvsB Disc. N ;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsBDiscP"]=new TH1F("DeepCSVCvsBDiscP",";DeepCSV CvsB Disc. P ;Jets",50,0,1.10);
  baseHistos["DeepCSVb_leadkin"]=new TH1F("DeepCSVb_leadkin",";DeepCSV b leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVc_leadkin"]=new TH1F("DeepCSVc_leadkin",";DeepCSV c leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVl_leadkin"]=new TH1F("DeepCSVl_leadkin",";DeepCSV l leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVbb_leadkin"]=new TH1F("DeepCSVbb_leadkin",";DeepCSV bb leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVcc_leadkin"]=new TH1F("DeepCSVcc_leadkin",";DeepCSV cc leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVbN_leadkin"]=new TH1F("DeepCSVbN_leadkin",";DeepCSV b N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVcN_leadkin"]=new TH1F("DeepCSVcN_leadkin",";DeepCSV c N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVlN_leadkin"]=new TH1F("DeepCSVlN_leadkin",";DeepCSV l N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVbbN_leadkin"]=new TH1F("DeepCSVbbN_leadkin",";DeepCSV bb N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVccN_leadkin"]=new TH1F("DeepCSVccN_leadkin",";DeepCSV cc N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVbP_leadkin"]=new TH1F("DeepCSVbP_leadkin",";DeepCSV b P leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVcP_leadkin"]=new TH1F("DeepCSVcP_leadkin",";DeepCSV c P leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVlP_leadkin"]=new TH1F("DeepCSVlP_leadkin",";DeepCSV l P leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVbbP_leadkin"]=new TH1F("DeepCSVbbP_leadkin",";DeepCSV bb P leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVccP_leadkin"]=new TH1F("DeepCSVccP_leadkin",";DeepCSV cc P leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVBDisc_leadkin"]=new TH1F("DeepCSVBDisc_leadkin",";DeepCSV B Disc. leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVBDiscN_leadkin"]=new TH1F("DeepCSVBDiscN_leadkin",";DeepCSV B Disc. N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVBDiscP_leadkin"]=new TH1F("DeepCSVBDiscP_leadkin",";DeepCSV B Disc. P leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsLDisc_leadkin"]=new TH1F("DeepCSVCvsLDisc_leadkin",";DeepCSV CvsL Disc. leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsLDiscN_leadkin"]=new TH1F("DeepCSVCvsLDiscN_leadkin",";DeepCSV CvsL Disc. N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsLDiscP_leadkin"]=new TH1F("DeepCSVCvsLDiscP_leadkin",";DeepCSV CvsL Disc. P leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsBDisc_leadkin"]=new TH1F("DeepCSVCvsBDisc_leadkin",";DeepCSV CvsB Disc. leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsBDiscN_leadkin"]=new TH1F("DeepCSVCvsBDiscN_leadkin",";DeepCSV CvsB Disc. N leadkin;Jets",50,0,1.10);
  baseHistos["DeepCSVCvsBDiscP_leadkin"]=new TH1F("DeepCSVCvsBDiscP_leadkin",";DeepCSV CvsB Disc. P leadkin;Jets",50,0,1.10);
  baseHistos["DeepFlavourBDisc"]=new TH1F("DeepFlavourBDisc",";DeepFlavour B Disc. ;Jets",50,0,1.10);
  baseHistos["DeepFlavourCvsLDisc"]=new TH1F("DeepFlavourCvsLDisc",";DeepFlavour CvsL Disc. ;Jets",50,0,1.10);
  baseHistos["DeepFlavourCvsBDisc"]=new TH1F("DeepFlavourCvsBDisc",";DeepFlavour CvsB Disc. ;Jets",50,0,1.10);
  baseHistos["DeepFlavourB"]=new TH1F("DeepFlavourB",";DeepFlavourB ;Jets",50,0,1.10);
  baseHistos["DeepFlavourBB"]=new TH1F("DeepFlavourBB",";DeepFlavourBB ;Jets",50,0,1.10);
  baseHistos["DeepFlavourLEPB"]=new TH1F("DeepFlavourLEPB",";DeepFlavourLEPB ;Jets",50,0,1.10);
  baseHistos["DeepFlavourBDisc_leadkin"]=new TH1F("DeepFlavourBDisc_leadkin",";DeepFlavour B Disc. leadkin;Jets",50,0,1.10);
  baseHistos["DeepFlavourCvsLDisc_leadkin"]=new TH1F("DeepFlavourCvsLDisc_leadkin",";DeepFlavour CvsL Disc. leadkin;Jets",50,0,1.10);
  baseHistos["DeepFlavourCvsBDisc_leadkin"]=new TH1F("DeepFlavourCvsBDisc_leadkin",";DeepFlavour CvsB Disc. leadkin;Jets",50,0,1.10);
  baseHistos["DeepFlavourB_leadkin"]=new TH1F("DeepFlavourB_leadkin",";DeepFlavourB leadkin;Jets",50,0,1.10);
  baseHistos["DeepFlavourBB_leadkin"]=new TH1F("DeepFlavourBB_leadkin",";DeepFlavourBB leadkin;Jets",50,0,1.10);
  baseHistos["DeepFlavourLEPB_leadkin"]=new TH1F("DeepFlavourLEPB_leadkin",";DeepFlavourLEPB leadkin;Jets",50,0,1.10);
  baseHistos["tche_leadkin"]=new TH1F("tche_leadkin",";Track Counting High Efficiency;Jets",50,-20,50);
  baseHistos["jetseltrk_leadkin"]=new TH1F("jetseltrk_leadkin",";Selected track multiplicity;Jets",15,0,15);
  baseHistos["flavour"] = new TH1F("flavour",     ";Jet flavour;Jets",                   4,  0, 4 );
  baseHistos["flavour"]->GetXaxis()->SetBinLabel(1,"unmatched");
  baseHistos["flavour"]->GetXaxis()->SetBinLabel(2,"udsg");
  baseHistos["flavour"]->GetXaxis()->SetBinLabel(3,"c");
  baseHistos["flavour"]->GetXaxis()->SetBinLabel(4,"b");
  baseHistos["close_mlj"]   = new TH1F("close_mlj",   ";M(lepton,jet) [GeV]; Jets",          50, 0, 250);
  baseHistos["close_deta"]  = new TH1F("close_deta",  ";#Delta#eta(lepton,jet); Jets",       50, 0, 4);
  baseHistos["close_dphi"]  = new TH1F("close_dphi",  ";#Delta#phi(lepton,jet) [rad]; Jets", 50, 0, 3.15);
  baseHistos["close_ptrel"] = new TH1F("close_ptrel", ";p_{T}^{rel}(lepton,jet) [GeV];Jets", 50, 0, 1);
  baseHistos["close_lj2ll_deta"] = new TH1F("close_lj2ll_deta",  ";#Delta#eta(lj,ll); Jets",       50, 0, 4);
  baseHistos["close_lj2ll_dphi"]  = new TH1F("close_l2jll_dphi",  ";#Delta#phi(lj,ll) [rad]; Jets", 50, 0, 3.15);
  baseHistos["far_mlj"]     = new TH1F("far_mlj",     ";M(lepton,jet) [GeV]; Jets",          50, 0, 250);
  baseHistos["far_deta"]    = new TH1F("far_deta",    ";#Delta#eta(lepton,jet); Jets",       50, 0, 4);
  baseHistos["far_dphi"]    = new TH1F("far_dphi",    ";#Delta#phi(lepton,jet) [rad]; Jets", 50, 0, 3.15);
  baseHistos["far_ptrel"]   = new TH1F("far_ptrel",   ";p_{T}^{rel}(lepton,jet) [GeV];Jets", 50, 0, 1);
  baseHistos["far_lj2ll_deta"] = new TH1F("far_lj2ll_deta",  ";#Delta#eta(lepton+jet,ll); Jets",       50, 0, 4);
  baseHistos["far_lj2ll_dphi"]  = new TH1F("far_l2jll_dphi",  ";#Delta#phi(lj,ll) [rad]; Jets", 50, 0, 3.15);
  baseHistos["j2ll_deta"]    = new TH1F("j2ll_deta",    ";#Delta#eta(ll,jet); Jets",       50, 0, 4);
  baseHistos["j2ll_dphi"]    = new TH1F("j2ll_dphi",    ";#Delta#phi(lll,jet) [rad]; Jets", 50, 0, 3.15);
  baseHistos["kindisc"]     = new TH1F("kindisc",     ";Kinematics discriminator;Jets",      100, -1, 1);

  //replicate histos per channel
  TString ch[]={"emu","ee","mumu"};
  for(size_t i=0; i<sizeof(ch)/sizeof(TString); i++)
  {
    for(std::map<TString,TH1F *>::iterator it=baseHistos.begin(); it!=baseHistos.end(); it++)
    {
      TString tag=ch[i]+"_"+it->first;
      histos_[tag]=(TH1F *)it->second->Clone(tag);
      histos_[tag]->Sumw2();
      histos_[tag]->SetDirectory(outF_);
    }
  }

  histos_["puwgtnorm"] = new TH1F("puwgtnorm", ";puwgtnorm;Events",              4, 0, 4);
  histos_["puwgtnorm"]->Sumw2();
  histos_["puwgtnorm"]->SetDirectory(outF_);
}

Int_t TTbarEventAnalysis::checkFile(TString inFile)
{
  //loop over events
  TFile *inF=TFile::Open(inFile);
  TTree *tree=(TTree *)inF->Get("btagana/ttree");
  Int_t nentries=tree->GetEntriesFast();
  if (nentries == 0){
    cout << "Check file found " << nentries << " entries to run" << endl;
    inF->Close();
    return 0;
  }
  else{
    return 1;
  }
}

template<typename Map>
void PrintMap(Map& m)
{
    cout << "[ ";
    for (auto &item : m) {
        cout << item.first << ":" << item.second << " ";
    }
    cout << "]\n";
}

//
Int_t TTbarEventAnalysis::processFile(TString inFile, TH1F *normWgt, Bool_t isData)
{
  //loop over events
  TFile *inF=TFile::Open(inFile);
  TTree *tree=(TTree *)inF->Get("btagana/ttree");
  Int_t nentries=tree->GetEntriesFast();
  std::cout << "...opening " << inFile << " -> analysing " << nentries << " events -> " << outF_->GetName();
  std::cout << std::endl;

  /*map<string, double> XS_map = {{"MC13TeV_TTJets_DL_training", 72.6983,},
                                {"MC13TeV_TTJets_AH_training", 316.466,},
                                {"MC13TeV_TTJets_SL_training", 303.358,},
                                {"MC13TeV_DY_M-10to50-MG", 15810.0,},
                                {"MC13TeV_DY_M-50-MG", 6077.22,},
                                {"MC13TeV_atW_noFullHad", 34.91,},
                                {"MC13TeV_tW_noFullHad", 34.91,},
                                {"MC13TeV_WW", 75.8,},
                                {"MC13TeV_WZ", 27.6,},
                                {"MC13TeV_ZZ", 12.14,},
                                {"MC13TeV_WJetsToLNu", 52850.0,},
                                {"MC13TeV_W1JetsToLNu", 8873.0,},
                                {"MC13TeV_W2JetsToLNu", 2793.0,}};
  PrintMap(XS_map);*/

  if (nentries == 0){
    inF->Close();
    return 0;
  }

  //prepare reader
  std::vector<Float_t> tmvaVars( tmvaVarNames_.size(), 0. );
  if(weightsDir_!=""){
    tmvaReader_= new TMVA::Reader( "!Color:!Silent" );
    for(size_t ivar=0; ivar<tmvaVarNames_.size(); ivar++){
      tmvaReader_->AddVariable( tmvaVarNames_[ivar], &tmvaVars[ivar] );
    }
    // Book 3 seperate MVAs from chosen MVA directory
    TString jranks[]={"leading",  "others",  "subleading" };
    for(size_t i=0; i<sizeof(jranks)/sizeof(TString); i++){
      tmvaReader_->BookMVA("BDT_"+jranks[i], weightsDir_+"/"+jranks[i]+"/TMVAClassification_BDT.weights.xml");
      //tmvaReader_->BookMVA("BDT_"+jranks[i], weightsDir_+"/"+jranks[i]+"/TMVAClassification_BDTD.weights.xml");
      //tmvaReader_->BookMVA("BDT_"+jranks[i], weightsDir_+"/"+jranks[i]+"/TMVAClassification_BDTG.weights.xml");
    }
  }

  typedef struct MyEventInfoBranches_t
  {
    Int_t Run,Evt,LumiBlock,nPV,nSV,nTrack,Jet_nseltracks[100],Jet_SV_multi[100],Jet_nFirstSV[100],Jet_nLastSV[100],Jet_nFirstTrack[10000],Jet_nLastTrack[10000];
    Int_t   ttbar_chan, ttbar_trigWord, ttbar_metfilterWord;
    Int_t   ttbar_nl, ttbar_lid[10], ttbar_lgid[10], ttbar_lch[10];
    Float_t ttbar_lpt[10], ttbar_leta[10], ttbar_lphi[10], ttbar_lm[10];
    Float_t ttbar_metpt,ttbar_metphi, ttbar_ptweight;
    Int_t   ttbar_nw;
    Int_t nPU;
    Float_t nPUtrue;
    Float_t ttbar_w[1095];
    Int_t nJet;
    Float_t rho;
    Float_t Jet_pt[100],Jet_genpt[100],Jet_area[100],Jet_jes[100],Jet_eta[100],Jet_phi[100],Jet_mass[100];
    Float_t Jet_Svx[100],Jet_CombIVF[100],Jet_Proba[100],Jet_Ip2P[100];
    Float_t Jet_DeepCSVb[100], Jet_DeepCSVc[100], Jet_DeepCSVl[100], Jet_DeepCSVbN[100], Jet_DeepCSVcN[100], Jet_DeepCSVlN[100];
    Float_t Jet_DeepCSVBDisc[100],Jet_DeepCSVBDiscN[100],Jet_DeepCSVCvsLDisc[100],Jet_DeepCSVCvsLDiscN[100],Jet_DeepCSVCvsBDisc[100],Jet_DeepCSVCvsBDiscN[100];
    Float_t Jet_DeepFlavourBDisc[100], Jet_DeepFlavourCvsLDisc[100], Jet_DeepFlavourCvsBDisc[100];
    Float_t Jet_DeepFlavourB[100];
    Int_t Jet_flavour[100];
    Float_t Track_pt[10000];
    Float_t Jet_SoftMuN[1000],Jet_SoftMu[1000],Jet_CombIVF_N[100];
  } evinit;
  MyEventInfoBranches_t ev;
  // Set the address for the branches you want to extract from the input ttree. The naming convention must match that used in the original ttree.
  tree->SetBranchAddress("Run"        , &ev.Run        );
  tree->SetBranchAddress("Evt"        , &ev.Evt        );
  tree->SetBranchAddress("rho"        , &ev.rho        );
  tree->SetBranchAddress("LumiBlock"  , &ev.LumiBlock  );
  tree->SetBranchAddress("nPV"        , &ev.nPV        );
  tree->SetBranchAddress("nPU"        , &ev.nPU        );
  tree->SetBranchAddress("nPUtrue",     &ev.nPUtrue );
  tree->SetBranchAddress("ttbar_chan" , &ev.ttbar_chan);
  tree->SetBranchAddress("ttbar_metfilterWord", &ev.ttbar_metfilterWord);
  tree->SetBranchAddress("ttbar_trigWord", &ev.ttbar_trigWord);
  tree->SetBranchAddress("ttbar_nl"   ,  &ev.ttbar_nl);
  tree->SetBranchAddress("ttbar_lpt"  ,   ev.ttbar_lpt);
  tree->SetBranchAddress("ttbar_leta" ,   ev.ttbar_leta);
  tree->SetBranchAddress("ttbar_lphi" ,   ev.ttbar_lphi);
  tree->SetBranchAddress("ttbar_lm"   ,   ev.ttbar_lm);
  tree->SetBranchAddress("ttbar_lid"  ,   ev.ttbar_lid);
  tree->SetBranchAddress("ttbar_lgid" ,   ev.ttbar_lgid);
  tree->SetBranchAddress("ttbar_lch"  ,   ev.ttbar_lch);
  tree->SetBranchAddress("ttbar_metpt",  &ev.ttbar_metpt);
  tree->SetBranchAddress("ttbar_metphi", &ev.ttbar_metphi);
  tree->SetBranchAddress("ttbar_ptweight", &ev.ttbar_ptweight);
  tree->SetBranchAddress("ttbar_nw",     &ev.ttbar_nw);
  tree->SetBranchAddress("ttbar_w",      ev.ttbar_w);
  tree->SetBranchAddress("nJet",            &ev.nJet);
  tree->SetBranchAddress("Jet_pt",          ev.Jet_pt);
  if(!isData){
    tree->SetBranchAddress("Jet_genpt",       ev.Jet_genpt);
  }
  tree->SetBranchAddress("Jet_area",        ev.Jet_area);
  tree->SetBranchAddress("Jet_jes",         ev.Jet_jes);
  tree->SetBranchAddress("Jet_eta",         ev.Jet_eta);
  tree->SetBranchAddress("Jet_phi",         ev.Jet_phi);
  tree->SetBranchAddress("Jet_mass",        ev.Jet_mass);
  tree->SetBranchAddress("Jet_Svx",         ev.Jet_Svx);
  tree->SetBranchAddress("Jet_CombIVF",     ev.Jet_CombIVF);
  tree->SetBranchAddress("Jet_CombIVF_N",     ev.Jet_CombIVF_N);
  tree->SetBranchAddress("Jet_SV_multi",         ev.Jet_SV_multi);
  tree->SetBranchAddress("Jet_nFirstSV",         ev.Jet_nFirstSV);
  tree->SetBranchAddress("Jet_nLastSV",         ev.Jet_nLastSV);
  tree->SetBranchAddress("Jet_nFirstTrack",         ev.Jet_nFirstTrack);
  tree->SetBranchAddress("Jet_nLastTrack",         ev.Jet_nLastTrack);
  tree->SetBranchAddress("Jet_SoftMuN",     ev.Jet_SoftMuN);
  tree->SetBranchAddress("Jet_SoftMu",     ev.Jet_SoftMu);
  tree->SetBranchAddress("Jet_Proba",       ev.Jet_Proba);
  tree->SetBranchAddress("Jet_Ip2P",        ev.Jet_Ip2P);
  tree->SetBranchAddress("Jet_nseltracks",  ev.Jet_nseltracks);
  tree->SetBranchAddress("Jet_flavour",     ev.Jet_flavour);
  tree->SetBranchAddress("Jet_DeepCSVb",  ev.Jet_DeepCSVb);
  tree->SetBranchAddress("Jet_DeepCSVc",  ev.Jet_DeepCSVc);
  tree->SetBranchAddress("Jet_DeepCSVl",  ev.Jet_DeepCSVl);
  tree->SetBranchAddress("Jet_DeepCSVbN",  ev.Jet_DeepCSVbN);
  tree->SetBranchAddress("Jet_DeepCSVcN",  ev.Jet_DeepCSVcN);
  tree->SetBranchAddress("Jet_DeepCSVlN",  ev.Jet_DeepCSVlN);
  tree->SetBranchAddress("Jet_DeepCSVBDisc", ev.Jet_DeepCSVBDisc);
  tree->SetBranchAddress("Jet_DeepCSVBDiscN", ev.Jet_DeepCSVBDiscN);
  tree->SetBranchAddress("Jet_DeepCSVCvsLDisc", ev.Jet_DeepCSVCvsLDisc);
  tree->SetBranchAddress("Jet_DeepCSVCvsLDiscN", ev.Jet_DeepCSVCvsLDiscN);
  tree->SetBranchAddress("Jet_DeepCSVCvsBDisc", ev.Jet_DeepCSVCvsBDisc);
  tree->SetBranchAddress("Jet_DeepCSVCvsBDiscN", ev.Jet_DeepCSVCvsBDiscN);
  tree->SetBranchAddress("Jet_DeepFlavourBDisc", ev.Jet_DeepFlavourBDisc);
  tree->SetBranchAddress("Jet_DeepFlavourCvsLDisc", ev.Jet_DeepFlavourCvsLDisc);
  tree->SetBranchAddress("Jet_DeepFlavourCvsBDisc", ev.Jet_DeepFlavourCvsBDisc);
  tree->SetBranchAddress("Jet_DeepFlavourB", ev.Jet_DeepFlavourB);

  //pileup weights
  Float_t puWgtLo(1.0), puWgtNom(1.0), puWgtHi(1.0);
  std::stringstream inFileSS( ( std::string(inFile) ) );
  std::string token;
  char delim = '/';
  std::vector<string> cont;
  std::size_t current, previous = 0;
  current = std::string(inFile).find(delim);
  while (current != std::string::npos) {
      std::string inFile_substring = std::string(inFile).substr(previous, current - previous);
      if(inFile_substring.find("MC13TeV_") != std::string::npos){
          cont.push_back(inFile_substring);
      }
      previous = current + 1;
      current = std::string(inFile).find(delim, previous);
  }
  cont.push_back(std::string(inFile).substr(previous, current - previous));
  std::string filenickname = cont.at(0);
  if(!isData){
    //SetPUWeightTarget("pileup_weights/pileupWgts2016.root",filenickname);
    SetPUWeightTarget("pileup_weights/pileupWgts2016_preVFP.root",filenickname);
  }

  int Event_i = 0;

  //nentries=100;
  for(Int_t i=Event_i; i<nentries; i++){
    tree->GetEntry(i);
    if(!isData){
      // From the pileup weights histogram made before running this code,
      // get the Data/MC pileup wgt using the integer number of pileup vertices .
      if(puWgtGr_)     {puWgtNom = puWgtGr_->Eval(ev.nPU);}
      if(puWgtDownGr_) {puWgtLo  = puWgtDownGr_->Eval(ev.nPU);}
      if(puWgtUpGr_)   {puWgtHi  = puWgtUpGr_->Eval(ev.nPU);}
      if(puWgtNom<0)   {puWgtNom = 0;}
      if(puWgtLo <0)   {puWgtLo  = 0;}
      if(puWgtHi <0)   {puWgtHi  = 0;}
    }
    histos_["puwgtnorm" ]->Fill(0.,1.0);
    histos_["puwgtnorm" ]->Fill(1.,puWgtNom);
    histos_["puwgtnorm" ]->Fill(2.,puWgtLo);
    histos_["puwgtnorm" ]->Fill(3.,puWgtHi);
    //=== Generator weights ===
    // genWgt = nominal LHE event weight
    // Each entry in ttbar_w corresponds to a LHE weight variation
    // Multiplying each event by the mcweight should remove dependence on generator XS i.e. any scale dependence on # generated events
    // This is because we are also going to scale each event by 1/sum(weights), where this value is taken from the storeTools.py script
    Double_t genWgt = ev.ttbar_nw==0 ? 1.0 : ev.ttbar_w[0];
    //if(genWgt>73.){cout << "genWgt: " << genWgt << endl;}
    //cout << "genWgt: " << genWgt << endl;

    Float_t qcdScaleLo(1.0),qcdScaleHi(1.0),hdampLo(1.0),hdampHi(1.0);
    double isrRedHi=1;
    double fsrRedHi=1;
    double isrRedLo=1;
    double fsrRedLo=1;
    double isrDefHi=1;
    double fsrDefHi=1;
    double isrDefLo=1;
    double fsrDefLo=1;
    double isrConHi=1;
    double fsrConHi=1;
    double isrConLo=1;
    double fsrConLo=1;
    if(readTTJetsGenWeights_ && ev.ttbar_nw>17){
      // Weight * [1/sum(weights for given systematic)] / [1/sum(weights nominal)]
      // will divide later by genWgt as appropriate
      // N.B. for GetBinContent(X) 'X' must be weight index + 1 due to way histogram is filled (0th bin always underflow).
      qcdScaleLo=(ev.ttbar_w[9]) * (normWgt->GetBinContent(10)/normWgt->GetBinContent(1));
      qcdScaleHi=(ev.ttbar_w[5]) * (normWgt->GetBinContent(6)/normWgt->GetBinContent(1));
      hdampLo=(ev.ttbar_w[ev.ttbar_nw-17]) * (normWgt->GetBinContent(ev.ttbar_nw-17+1)/normWgt->GetBinContent(1));
      hdampHi=(ev.ttbar_w[ev.ttbar_nw-9]) * (normWgt->GetBinContent(ev.ttbar_nw-9+1)/normWgt->GetBinContent(1));

      // >>> PSWeights <<<
      // Vector of weight to be used instead of old ISR/FSR varied alternative samples.
      // First weight (weightID= 1081) corresponds to central ME weight value.
      // The remaining 12 values (weightIDs = 1082 to 1093) correspond to the PS weights in the following order (ISR up, FSR up, ISR down, FSR down) x 3 sets, i.e.
      // 1082 = isrRedHi isr:muRfac=0.707, 1083 = fsrRedHi fsr:muRfac=0.707, 1084 = isrRedLo isr:muRfac=1.414, 1085 = fsrRedLo fsr:muRfac=1.414,
      // 1086 = isrDefHi isr:muRfac=0.5,   1087 = fsrDefHi fsr:muRfac=0.5,   1088 = isrDefLo isr:muRfac=2.0,   1089 = fsrDefLo fsr:muRfac=2.0,
      // 1090 = isrConHi isr:muRfac=0.25,  1091 = fsrConHi fsr:muRfac=0.25,  1092 = isrConLo isr:muRfac=4.0,   1093 = fsrConLo fsr:muRfac=4.0

      isrRedHi = (ev.ttbar_w[1082]) * (normWgt->GetBinContent(1083)/normWgt->GetBinContent(1));
      fsrRedHi = (ev.ttbar_w[1083]) * (normWgt->GetBinContent(1084)/normWgt->GetBinContent(1));
      isrRedLo = (ev.ttbar_w[1084]) * (normWgt->GetBinContent(1085)/normWgt->GetBinContent(1));
      fsrRedLo = (ev.ttbar_w[1085]) * (normWgt->GetBinContent(1086)/normWgt->GetBinContent(1));
      isrDefHi = (ev.ttbar_w[1086]) * (normWgt->GetBinContent(1087)/normWgt->GetBinContent(1));
      fsrDefHi = (ev.ttbar_w[1087]) * (normWgt->GetBinContent(1088)/normWgt->GetBinContent(1));
      isrDefLo = (ev.ttbar_w[1088]) * (normWgt->GetBinContent(1089)/normWgt->GetBinContent(1));
      fsrDefLo = (ev.ttbar_w[1089]) * (normWgt->GetBinContent(1090)/normWgt->GetBinContent(1));
      isrConHi = (ev.ttbar_w[1090]) * (normWgt->GetBinContent(1091)/normWgt->GetBinContent(1));
      fsrConHi = (ev.ttbar_w[1091]) * (normWgt->GetBinContent(1092)/normWgt->GetBinContent(1));
      isrConLo = (ev.ttbar_w[1092]) * (normWgt->GetBinContent(1093)/normWgt->GetBinContent(1));
      fsrConLo = (ev.ttbar_w[1093]) * (normWgt->GetBinContent(1094)/normWgt->GetBinContent(1));
    }

    //
    //CHANNEL ASSIGNMENT
    //
    ev.ttbar_chan=ev.ttbar_lid[0]*ev.ttbar_lch[0]*ev.ttbar_lid[1]*ev.ttbar_lch[1];
    std::string ch("");
    if(ev.ttbar_chan==-11*13) ch="emu";
    if(ev.ttbar_chan==-11*11) ch="ee";
    if(ev.ttbar_chan==-13*13) ch="mumu";

    // TRIGGER
    bool hasTrigger( triggerBits_.size()==0  ? true : false);
    Float_t trigWgtLo(1.0), trigWgtNom(1.0), trigWgtHi(1.0);
    for(size_t ibit=0; ibit<triggerBits_.size(); ibit++){
      // Only accept triggers valid for the assigned decay channel
      // Currently only use eµ cross-triggers
      if(triggerBits_[ibit].second!=ev.ttbar_chan) {
        continue;
      }
      if(triggerBits_[ibit].first > 2){
        continue;
      }

      //Trigger efficiency weight
      if(!isData){
        double leading_lep_pt;
        double subleading_lep_pt;
        if (ev.ttbar_lpt[0]>ev.ttbar_lpt[1]){
            leading_lep_pt = ev.ttbar_lpt[0];
            subleading_lep_pt = ev.ttbar_lpt[1];
        }
        else{
          leading_lep_pt = ev.ttbar_lpt[1];
          subleading_lep_pt = ev.ttbar_lpt[0];
        }
        std::pair<float,float> trigSF=getTriggerScaleFactor(leading_lep_pt, subleading_lep_pt, ev.ttbar_chan, triggerBits_[ibit].first);
        trigWgtLo=trigSF.first-trigSF.second;
        trigWgtNom=trigSF.first;
        trigWgtHi=trigSF.first+trigSF.second;
      }

      hasTrigger |= ( (ev.ttbar_trigWord>>triggerBits_[ibit].first) & 1);

    }

    //Lepton selection efficiency
    Float_t lepIDSFLo(1.0), lepIDSFNom(1.0), lepIDSFHi(1.0);
    Float_t ele1RecoSFLo(1.0), ele1RecoSFNom(1.0), ele1RecoSFHi(1.0);
    Float_t ele2RecoSFLo(1.0), ele2RecoSFNom(1.0), ele2RecoSFHi(1.0);
    Float_t eleRecoSFLo(1.0), eleRecoSFNom(1.0), eleRecoSFHi(1.0);
    Float_t mu1ISOSFLo(1.0), mu1ISOSFNom(1.0), mu1ISOSFHi(1.0);
    Float_t mu2ISOSFLo(1.0), mu2ISOSFNom(1.0), mu2ISOSFHi(1.0);
    Float_t muISOSFLo(1.0), muISOSFNom(1.0), muISOSFHi(1.0);
    if(!isData){
      std::pair<float,float> lepIDSF(1.0,0.0);
      std::pair<float,float> eleRecoSF_lep1(1.0,0.0);
      std::pair<float,float> eleRecoSF_lep2(1.0,0.0);
      std::pair<float,float> muISOSF_lep1(1.0,0.0);
      std::pair<float,float> muISOSF_lep2(1.0,0.0);

      for(size_t il=0; il<2; il++){
        lepIDSF = getLeptonIDScaleFactor(ev.ttbar_lid[il],ev.ttbar_lpt[il],ev.ttbar_leta[il]);
        lepIDSFLo  *= (lepIDSF.first-lepIDSF.second);
        lepIDSFNom *= lepIDSF.first;
        lepIDSFHi  *= (lepIDSF.first+lepIDSF.second);
      }
      eleRecoSF_lep1 = getElectronRECOScaleFactor(ev.ttbar_lid[0],ev.ttbar_lpt[0],ev.ttbar_leta[0]);
      eleRecoSF_lep2 = getElectronRECOScaleFactor(ev.ttbar_lid[1],ev.ttbar_lpt[1],ev.ttbar_leta[1]);
      ele1RecoSFLo  *= (eleRecoSF_lep1.first-eleRecoSF_lep1.second);
      ele1RecoSFNom *= eleRecoSF_lep1.first;
      ele1RecoSFHi  *= (eleRecoSF_lep1.first+eleRecoSF_lep1.second);
      ele2RecoSFLo  *= (eleRecoSF_lep2.first-eleRecoSF_lep2.second);
      ele2RecoSFNom *= eleRecoSF_lep2.first;
      ele2RecoSFHi  *= (eleRecoSF_lep2.first+eleRecoSF_lep2.second);
      eleRecoSFLo = ele1RecoSFLo * ele2RecoSFLo;
      eleRecoSFNom = ele1RecoSFNom * ele2RecoSFNom;
      eleRecoSFHi = ele1RecoSFHi * ele2RecoSFHi;

      muISOSF_lep1 = getMuonISOScaleFactor(ev.ttbar_lid[0],ev.ttbar_lpt[0],ev.ttbar_leta[0]);
      muISOSF_lep2 = getMuonISOScaleFactor(ev.ttbar_lid[1],ev.ttbar_lpt[1],ev.ttbar_leta[1]);

      mu1ISOSFLo  *= (muISOSF_lep1.first-muISOSF_lep1.second);
      mu1ISOSFNom *= muISOSF_lep1.first;
      mu1ISOSFHi  *= (muISOSF_lep1.first+muISOSF_lep1.second);

      mu2ISOSFLo  *= (muISOSF_lep2.first-muISOSF_lep2.second);
      mu2ISOSFNom *= muISOSF_lep2.first;
      mu2ISOSFHi  *= (muISOSF_lep2.first+muISOSF_lep2.second);

      muISOSFLo  *= mu1ISOSFLo*mu2ISOSFLo;
      muISOSFNom *= mu1ISOSFNom*mu2ISOSFNom;
      muISOSFHi  *= mu1ISOSFHi*mu2ISOSFHi;
    }

    //(Di)Lepton cuts
    std::vector<TLorentzVector> lp4;
    for(Int_t il=0; il<ev.ttbar_nl; il++){
      lp4.push_back( TLorentzVector(0,0,0,0) );
      lp4[il].SetPtEtaPhiM(ev.ttbar_lpt[il],ev.ttbar_leta[il],ev.ttbar_lphi[il],0.);
    }

    TLorentzVector dilepton(lp4[0]+lp4[1]);
    Float_t mll=dilepton.M();

    // Calculate nominal event weight
    // Cross-section & luminosity scaling left out here
    // Applied later in plotting macro to allow faster turn-around incase values change
    // Not needed in training and overall normalisation doesn't affect the fit

    Float_t presel_evwgt(1.0);
    Float_t evWgt(1.0);
    Float_t inverse_sumgenwgt(1.0);
    if(!isData){
      evWgt *= genWgt*puWgtNom*trigWgtNom*lepIDSFNom*eleRecoSFNom*muISOSFNom;
      evWgt *= 0.7;
      presel_evwgt *= genWgt*puWgtNom*trigWgtNom;
      if(std::string(inFile).find("_TTJets_") != std::string::npos){
        evWgt *= ev.ttbar_ptweight;
        presel_evwgt *= ev.ttbar_ptweight;
      }
      if(normWgt) {
        inverse_sumgenwgt = normWgt->GetBinContent(1);
        evWgt *= inverse_sumgenwgt; // 1 / sum(wgts)
        presel_evwgt *= inverse_sumgenwgt;
        string outfname( outF_->GetName() );
      }
    }

    histos_[ch+"_evsel"]->Fill("pre-sel",presel_evwgt);
    histos_[ch+"_npvinc"]->Fill(ev.nPV-1,presel_evwgt);
    npv_=ev.nPV;

    //#########################
    // JET/MET SELECTION
    //#########################
    Int_t jetCount[5]={0,0,0,0,0};
    std::vector<Int_t> selJets;
    std::vector<std::vector<Float_t> > selJetsKINDisc;
    std::vector< std::vector<TLorentzVector> > selJetsP4;
    std::vector< std::vector< std::vector<LJKinematics_t> > > selJetsLJKinematics;
    //cout << "Event index " << i << endl;
    //cout << "# jets (all jets) = " << ev.nJet << endl;
    for(Int_t ij=0; ij<ev.nJet; ij++){
      //cout << "Jet " << ij << endl;
      //convert to P4
      TLorentzVector jp4(0,0,0,0);
      jp4.SetPtEtaPhiM(ev.Jet_pt[ij],ev.Jet_eta[ij],ev.Jet_phi[ij],ev.Jet_mass[ij]);

      // pT/eta selection of jets set in ttbar selection producer and performed by BTA.
      // Implement any additional jet selection here.
      float jet_minptcut = 30.;
      if(jp4.Pt()<jet_minptcut){continue;}

      // Cross clean jets wrt to leptons
      Float_t minDRlj(9999.);
      for(size_t il=0; il<2; il++) minDRlj = TMath::Min( (Float_t)minDRlj, (Float_t)lp4[il].DeltaR(jp4) );
      if(minDRlj<0.4) continue;
      //cout << "Jet passed selection" << endl;

      // Add JES+JER uncertainties for this jet.
      // By default, the jets from BTagAnalyzer are corrected for PU effects
      // (PF charged hadron subtraction+L1FastJet correction) and up to the L2-L3 JEC levels.
      // The L2L3 residual corrections are applied to the data only.
      std::vector<float> jesSF(3,1.0);
      jecUnc_->setJetEta(fabs(jp4.Eta()));
      jecUnc_->setJetPt(jp4.Pt());
      float unc = jecUnc_->getUncertainty(true);
      jesSF[1]=(1.+fabs(unc));
      jesSF[2]=(1.-fabs(unc));

      TLorentzVector oldjp4(jp4);
      std::vector<float> jerSF(3,1.0);

      if (!isData){
        Float_t genjpt=ev.Jet_genpt[ij];
        Float_t corrected_reco_pt = jp4.Pt();
        JME::JetParameters parameters_res = {{JME::Binning::JetPt, corrected_reco_pt}, {JME::Binning::JetEta, jp4.Eta()}};
        JME::JetParameters parameters_SF = { {JME::Binning::JetEta, jp4.Eta()}, {JME::Binning::Rho, ev.rho} };
        //resolution->dump();// check resolution
        // Get relative (sigma_pT_MC/pT) jet pT resolution
        //float JER_mc = resolution->getResolution({ {JME::Binning::JetPt, jp4.Pt()}, {JME::Binning::JetEta, jp4.Eta()}, {JME::Binning::Rho, ev.rho} });
        float JER_sf = resolution_sf->getScaleFactor(parameters_SF);
        float JER_sf_up = resolution_sf->getScaleFactor(parameters_SF, Variation::UP);
        float JER_sf_down = resolution_sf->getScaleFactor(parameters_SF, Variation::DOWN);
        jerSF[1] = (JER_sf_up);
        jerSF[2] = (JER_sf_down);
      }
      else{
        jerSF[0] = 1.;
        jerSF[1] = 1.;
        jerSF[2] = 1.;
      }
      // Apply energy shifts according to systematic variation
      std::vector<TLorentzVector> varjp4;//vector of TLorentzVectors. Entry fo each systematic variation.
      std::vector<Float_t> varkindisc;
      std::vector< std::vector<LJKinematics_t> > varLJKinematics;
      for(Int_t iSystVar=0; iSystVar<5; iSystVar++){
        varjp4.push_back( jp4 );
        if(iSystVar==1) varjp4[iSystVar] *= jesSF[1]/jesSF[0];
        if(iSystVar==2) varjp4[iSystVar] *= jesSF[2]/jesSF[0];
        if(iSystVar==3) varjp4[iSystVar] *= jerSF[1]/jerSF[0];
        if(iSystVar==4) varjp4[iSystVar] *= jerSF[2]/jerSF[0];

        // Fill kinematic variables -> MVA input variables
        // Stored in LJKinematics object
        std::vector< LJKinematics_t > ljkinematics;
        for(Int_t il=0; il<2; il++){
          LJKinematics_t iljkin;
          iljkin.dr         = lp4[il].DeltaR(varjp4[iSystVar]);
          iljkin.dphi       = fabs(lp4[il].DeltaPhi(varjp4[iSystVar]));
          iljkin.deta       = fabs(lp4[il].Eta()-varjp4[iSystVar].Eta());
          iljkin.ptrel      = ROOT::Math::VectorUtil::Perp(lp4[il].Vect(),varjp4[iSystVar].Vect().Unit())/lp4[il].P();
          TLorentzVector ljP4(lp4[il]+varjp4[iSystVar]);
          iljkin.mlj        = ljP4.M();
          iljkin.lj2ll_deta = fabs(ljP4.Eta()-dilepton.Eta());
          iljkin.lj2ll_dphi = fabs(ljP4.DeltaPhi(dilepton));
          ljkinematics.push_back(iljkin);
        }
        sort(ljkinematics.begin(),ljkinematics.end(),sortLJKinematicsByDR);

        // Store one LJKinematics object per JEC systematic variation
        varLJKinematics.push_back(ljkinematics);

        // Evaluate the MVA
        Float_t kindisc(0.0);
        if(tmvaReader_){
          for(size_t ivar=0; ivar<tmvaVarNames_.size(); ivar++){
            if( tmvaVarNames_[ivar].Contains("j2ll_") ){
              if(tmvaVarNames_[ivar]=="j2ll_deta") tmvaVars[ivar]=fabs(varjp4[iSystVar].Eta()-dilepton.Eta());
              if(tmvaVarNames_[ivar]=="j2ll_phi")  tmvaVars[ivar]=fabs(varjp4[iSystVar].DeltaPhi(dilepton));
            }
            else{
              int ljidx( tmvaVarNames_[ivar].Contains("close") ? 0 : 1);
              if(tmvaVarNames_[ivar].Contains("_dr"))    tmvaVars[ivar]=ljkinematics[ljidx].dr;
              if(tmvaVarNames_[ivar].Contains("_dphi")){
                if(tmvaVarNames_[ivar].Contains("lj2ll_")) tmvaVars[ivar]=ljkinematics[ljidx].lj2ll_dphi;
                else                                       tmvaVars[ivar]=ljkinematics[ljidx].dphi;
              }
              if(tmvaVarNames_[ivar].Contains("_deta")){
                if(tmvaVarNames_[ivar].Contains("lj2ll_")) tmvaVars[ivar]=ljkinematics[ljidx].lj2ll_deta;
                else                                       tmvaVars[ivar]=ljkinematics[ljidx].deta;
              }
              if(tmvaVarNames_[ivar].Contains("_ptrel")) tmvaVars[ivar]=ljkinematics[ljidx].ptrel;
              if(tmvaVarNames_[ivar].Contains("_mlj"))   tmvaVars[ivar]=ljkinematics[ljidx].mlj;
            }
          }
          // Evaluate kinematic discriminant
          TString methodPFix("_others");
          if(selJetsP4.size()==0) methodPFix="_leading";
          else if(selJetsP4.size()==1) methodPFix="_subleading";
          //cout << "Evaluate using BDT" << methodPFix << endl;
          varkindisc.push_back( tmvaReader_->EvaluateMVA("BDT"+methodPFix) );
        }
        // Count jets passing selection for each jet energy variation.
        jetCount[iSystVar]++;
      }
      // Nominal jets
      //cout << "Jet_DeepFlavourBDisc for ij " << ij << " = " << ev.Jet_DeepFlavourBDisc[ij] << endl;
      selJets.push_back(ij);
      selJetsP4.push_back(varjp4);// vector of entries for each jet. Each jet has vector of nominal/systematic variations of TLorentzVectors.
      selJetsLJKinematics.push_back( varLJKinematics );
      if(tmvaReader_) selJetsKINDisc.push_back(varkindisc);
    }//#End of jet loop

    bool zCand(TMath::Abs(mll-91.)>15. ? true : false );
    bool passMet(ev.ttbar_metpt>40 ?  true : false);
    bool passJets(selJetsP4.size()>=2 ? true : false);

    if(!hasTrigger){
      continue;
    }
    histos_[ch+"_evsel"]->Fill("Trigger",presel_evwgt);
    if(ev.ttbar_nl<2 || ev.nJet<2){
      continue;
    }
    histos_[ch+"_evsel"]->Fill("2l_2jet",presel_evwgt);
    if(ch!="emu"){
      continue;
    }
    histos_[ch+"_evsel"]->Fill("emu",presel_evwgt);
    if(mll<90){
      continue;
    }
    histos_[ch+"_evsel"]->Fill("Mll",evWgt);
    if(lp4[0].Pt()<25 || lp4[1].Pt()<25){
      continue;
    }
    histos_[ch+"_evsel"]->Fill("lepPts",evWgt);
    if(lp4[0].Eta()>2.4 || lp4[1].Eta()>2.4){
      continue;
    }
    //if( (* ch.find("ee")>0 || *ch.Contains("mumu")>0 ) && !zCand ){continue;}
    histos_[ch+"_evsel"]->Fill("lepEtas",evWgt);
    if(!passJets){
      continue;
    }
    histos_[ch+"_mllinc"]->Fill(mll,evWgt);
    histos_[ch+"_precut_met"]->Fill(ev.ttbar_metpt,evWgt);
    histos_[ch+"_evsel"]->Fill("Jet Sel",evWgt);
    if(!passMet) {
      continue;
    }
    histos_[ch+"_evsel"]->Fill("MET",evWgt);
    histos_[ch+"_met"]->Fill(ev.ttbar_metpt,evWgt);

    if(selJetsP4.size()>=2){histos_[ch+"_evsel"]->Fill("#geq 2j",evWgt);}
    if(selJetsP4.size()==2){histos_[ch+"_evsel"]->Fill("=2j",evWgt);}
    if(selJetsP4.size()==3){histos_[ch+"_evsel"]->Fill("=3j",evWgt);}
    if(selJetsP4.size()==4){histos_[ch+"_evsel"]->Fill("=4j",evWgt);}

    histos_[ch+"_npv"]->Fill(ev.nPV-1,evWgt);
    histos_[ch+"_mll"]->Fill(mll,evWgt);
    histos_[ch+"_njets"]->Fill(selJetsP4.size(),evWgt);
    histos_[ch+"_leadjpt"]->Fill(selJetsP4[0][0].Pt(),evWgt);
    histos_[ch+"_leadjeta"]->Fill((selJetsP4[0][0].Eta()),evWgt);
    histos_[ch+"_leadlpt"]->Fill(lp4[0].Pt(),evWgt);
    histos_[ch+"_trailjpt"]->Fill(selJetsP4[1][0].Pt(),evWgt);
    histos_[ch+"_trailjeta"]->Fill(fabs(selJetsP4[1][0].Eta()),evWgt);
    histos_[ch+"_traillpt"]->Fill(lp4[1].Pt(),evWgt);

    std::vector<float> leadingkindisc(2,-9999);
    std::vector<int> leadingkindiscIdx(2,-1);
    for(size_t ij=0; ij<selJetsP4.size(); ij++){
      histos_[ch+"_close_mlj"]->Fill(selJetsLJKinematics[ij][0][0].mlj,evWgt);
      histos_[ch+"_close_deta"]->Fill(selJetsLJKinematics[ij][0][0].deta,evWgt);
      histos_[ch+"_close_dphi"]->Fill(selJetsLJKinematics[ij][0][0].dphi,evWgt);
      histos_[ch+"_close_ptrel"]->Fill(selJetsLJKinematics[ij][0][0].ptrel,evWgt);
      histos_[ch+"_close_lj2ll_deta"]->Fill(selJetsLJKinematics[ij][0][0].lj2ll_deta,evWgt);
      histos_[ch+"_close_lj2ll_dphi"]->Fill(selJetsLJKinematics[ij][0][0].lj2ll_dphi,evWgt);
      histos_[ch+"_far_mlj"]->Fill(selJetsLJKinematics[ij][0][1].mlj,evWgt);
      histos_[ch+"_far_deta"]->Fill(selJetsLJKinematics[ij][0][1].deta,evWgt);
      histos_[ch+"_far_dphi"]->Fill(selJetsLJKinematics[ij][0][1].dphi,evWgt);
      histos_[ch+"_far_ptrel"]->Fill(selJetsLJKinematics[ij][0][1].ptrel,evWgt);
      histos_[ch+"_far_lj2ll_deta"]->Fill(selJetsLJKinematics[ij][0][1].lj2ll_deta,evWgt);
      histos_[ch+"_far_lj2ll_dphi"]->Fill(selJetsLJKinematics[ij][0][1].lj2ll_dphi,evWgt);
      histos_[ch+"_j2ll_deta"]->Fill(fabs(selJetsP4[ij][0].Eta()-dilepton.Eta()),evWgt);
      histos_[ch+"_j2ll_dphi"]->Fill(fabs(selJetsP4[ij][0].DeltaPhi(dilepton)),evWgt);
      if(tmvaReader_) histos_[ch+"_kindisc"]->Fill(selJetsKINDisc[ij][0],evWgt);
      // The event info object not filled per jet and contains more than just the
      // selected jets. Therefore need to get info for selected jets only.
      //cout << "Jet_DeepFlavourBDisc for jidx " << jetIdx << " = " << ev.Jet_DeepFlavourBDisc[jetIdx] << endl;
      Int_t jetIdx(selJets[ij]);
      histos_[ch+"_jp"]->Fill(ev.Jet_Proba[jetIdx],evWgt);
      histos_[ch+"_svhe"]->Fill(ev.Jet_Svx[jetIdx],evWgt);
      histos_[ch+"_csv"]->Fill(ev.Jet_CombIVF[jetIdx],evWgt);
      histos_[ch+"_tche"]->Fill(ev.Jet_Ip2P[jetIdx],evWgt);
      histos_[ch+"_jetseltrk"]->Fill(ev.Jet_nseltracks[jetIdx],evWgt);
      histos_[ch+"_DeepCSVb"]->Fill(ev.Jet_DeepCSVb[jetIdx],evWgt);
      histos_[ch+"_DeepCSVc"]->Fill(ev.Jet_DeepCSVc[jetIdx],evWgt);
      histos_[ch+"_DeepCSVl"]->Fill(ev.Jet_DeepCSVl[jetIdx],evWgt);
      histos_[ch+"_DeepCSVbN"]->Fill(ev.Jet_DeepCSVbN[jetIdx],evWgt);
      histos_[ch+"_DeepCSVcN"]->Fill(ev.Jet_DeepCSVcN[jetIdx],evWgt);
      histos_[ch+"_DeepCSVlN"]->Fill(ev.Jet_DeepCSVlN[jetIdx],evWgt);
      histos_[ch+"_DeepCSVBDisc"]->Fill(ev.Jet_DeepCSVBDisc[jetIdx],evWgt);
      histos_[ch+"_DeepCSVBDiscN"]->Fill(ev.Jet_DeepCSVBDiscN[jetIdx],evWgt);
      histos_[ch+"_DeepCSVCvsLDisc"]->Fill(ev.Jet_DeepCSVCvsLDisc[jetIdx],evWgt);
      histos_[ch+"_DeepCSVCvsLDiscN"]->Fill(ev.Jet_DeepCSVCvsLDiscN[jetIdx],evWgt);
      histos_[ch+"_DeepCSVCvsBDisc"]->Fill(ev.Jet_DeepCSVCvsBDisc[jetIdx],evWgt);
      histos_[ch+"_DeepCSVCvsBDiscN"]->Fill(ev.Jet_DeepCSVCvsBDiscN[jetIdx],evWgt);
      histos_[ch+"_DeepFlavourBDisc"]->Fill(ev.Jet_DeepFlavourBDisc[jetIdx],evWgt);
      histos_[ch+"_DeepFlavourCvsLDisc"]->Fill(ev.Jet_DeepFlavourCvsLDisc[jetIdx],evWgt);
      histos_[ch+"_DeepFlavourCvsBDisc"]->Fill(ev.Jet_DeepFlavourCvsBDisc[jetIdx],evWgt);
      histos_[ch+"_DeepFlavourB"]->Fill(ev.Jet_DeepFlavourB[jetIdx],evWgt);

      Int_t flavBin(0),partonFlav(abs(ev.Jet_flavour[jetIdx]));
      if(partonFlav==21 || (partonFlav>0 && partonFlav<4)) flavBin=1;
      if(partonFlav==4) flavBin=2;
      if(partonFlav==5) flavBin=3;
      histos_[ch+"_flavour"]->Fill(flavBin,evWgt);

      // Rank jets by kinematics discriminator
      if(tmvaReader_)
      {
        if(selJetsKINDisc[ij][0]>leadingkindisc[0])
        {
          leadingkindisc[1]=leadingkindisc[0];     leadingkindiscIdx[1]=leadingkindiscIdx[0];
          leadingkindisc[0]=selJetsKINDisc[ij][0]; leadingkindiscIdx[0]=jetIdx;
        }
        else if(selJetsKINDisc[ij][0]>leadingkindisc[1])
        {
          leadingkindisc[1]=selJetsKINDisc[ij][0]; leadingkindiscIdx[1]=jetIdx;
        }
      }
    }

    //control b-tagging quantities for the most promising jets in the KIN discriminator
    if(tmvaReader_){
      for(size_t ij=0; ij<2; ij++){
        size_t jetIdx=leadingkindiscIdx[ij];
        histos_[ch+"_jp_leadkin"]->Fill(ev.Jet_Proba[jetIdx],evWgt);
        histos_[ch+"_svhe_leadkin"]->Fill(ev.Jet_Svx[jetIdx],evWgt);
        histos_[ch+"_csv_leadkin"]->Fill(ev.Jet_CombIVF[jetIdx],evWgt);
        histos_[ch+"_tche_leadkin"]->Fill(ev.Jet_Ip2P[jetIdx],evWgt);
        histos_[ch+"_jetseltrk_leadkin"]->Fill(ev.Jet_nseltracks[jetIdx],evWgt);
        histos_[ch+"_DeepCSVb_leadkin"]->Fill(ev.Jet_DeepCSVb[jetIdx],evWgt);
        histos_[ch+"_DeepCSVc_leadkin"]->Fill(ev.Jet_DeepCSVc[jetIdx],evWgt);
        histos_[ch+"_DeepCSVl_leadkin"]->Fill(ev.Jet_DeepCSVl[jetIdx],evWgt);
        histos_[ch+"_DeepCSVbN_leadkin"]->Fill(ev.Jet_DeepCSVbN[jetIdx],evWgt);
        histos_[ch+"_DeepCSVcN_leadkin"]->Fill(ev.Jet_DeepCSVcN[jetIdx],evWgt);
        histos_[ch+"_DeepCSVlN_leadkin"]->Fill(ev.Jet_DeepCSVlN[jetIdx],evWgt);
        histos_[ch+"_DeepCSVBDisc_leadkin"]->Fill(ev.Jet_DeepCSVBDisc[jetIdx],evWgt);
        histos_[ch+"_DeepCSVBDiscN_leadkin"]->Fill(ev.Jet_DeepCSVBDiscN[jetIdx],evWgt);
        histos_[ch+"_DeepCSVCvsLDisc_leadkin"]->Fill(ev.Jet_DeepCSVCvsLDisc[jetIdx],evWgt);
        histos_[ch+"_DeepCSVCvsLDiscN_leadkin"]->Fill(ev.Jet_DeepCSVCvsLDiscN[jetIdx],evWgt);
        histos_[ch+"_DeepCSVCvsBDisc_leadkin"]->Fill(ev.Jet_DeepCSVCvsBDisc[jetIdx],evWgt);
        histos_[ch+"_DeepCSVCvsBDiscN_leadkin"]->Fill(ev.Jet_DeepCSVCvsBDiscN[jetIdx],evWgt);
        histos_[ch+"_DeepFlavourBDisc_leadkin"]->Fill(ev.Jet_DeepFlavourBDisc[jetIdx],evWgt);
        histos_[ch+"_DeepFlavourCvsLDisc_leadkin"]->Fill(ev.Jet_DeepFlavourCvsLDisc[jetIdx],evWgt);
        histos_[ch+"_DeepFlavourCvsBDisc_leadkin"]->Fill(ev.Jet_DeepFlavourCvsBDisc[jetIdx],evWgt);
        histos_[ch+"_DeepFlavourB_leadkin"]->Fill(ev.Jet_DeepFlavourB[jetIdx],evWgt);
      }
    }

    //
    //prepare to store trees
    //
    eventInfo_[0]=ev.Run;
    eventInfo_[1]=ev.Evt;
    eventInfo_[2]=ev.LumiBlock;

    jetmult_=selJetsP4.size();
    ttbar_chan_=ev.ttbar_chan;

    //weights for systematic uncertainties
    for(Int_t iSystVar=0; iSystVar<5; iSystVar++)
    {
      Float_t selWeight(jetCount[iSystVar]>=2 ? 1.0 : 0.0);
      weight_[iSystVar]=evWgt*selWeight;
    }
    weight_[5] = puWgtNom>0 ? evWgt*puWgtLo/puWgtNom : evWgt;
    weight_[6] = puWgtLo>0  ? evWgt*puWgtHi/puWgtNom : evWgt;
    weight_[7] = evWgt*trigWgtLo/trigWgtNom;
    weight_[8] = evWgt*trigWgtHi/trigWgtNom;
    weight_[9] = evWgt*lepIDSFLo/lepIDSFNom;
    weight_[10]= evWgt*lepIDSFHi/lepIDSFNom;
    weight_[11]= evWgt*qcdScaleLo/genWgt;
    weight_[12]= evWgt*qcdScaleHi/genWgt;
    weight_[13]= evWgt*hdampLo/genWgt;
    weight_[14]= evWgt*hdampHi/genWgt;
    weight_[15]= evWgt*isrRedLo/genWgt;
    weight_[16]= evWgt*isrRedHi/genWgt;
    weight_[17]= evWgt*fsrRedLo/genWgt;
    weight_[18]= evWgt*fsrRedHi/genWgt;
    weight_[19]= evWgt*isrDefLo/genWgt;
    weight_[20]= evWgt*isrDefHi/genWgt;
    weight_[21]= evWgt*fsrDefLo/genWgt;
    weight_[22]= evWgt*fsrDefHi/genWgt;
    weight_[23]= evWgt*isrConLo/genWgt;
    weight_[24]= evWgt*isrConHi/genWgt;
    weight_[25]= evWgt*fsrConLo/genWgt;
    weight_[26]= evWgt*fsrConHi/genWgt;
    weight_[27] = evWgt*muISOSFLo/muISOSFNom;
    weight_[28]= evWgt*muISOSFHi/muISOSFNom;
    weight_[29] = evWgt*eleRecoSFLo/eleRecoSFNom;
    weight_[30]= evWgt*eleRecoSFHi/eleRecoSFNom;

    // Fill trees
    // Jets are pT ordered 0(highest)->Nj(lowest)
    // kinTree branches are filled with multiple entries, one for each jet in the event
    for(size_t ij=0; ij<selJetsP4.size(); ij++){
      Int_t jetIdx(selJets[ij]);
      jetrank_ = ij;
      jetFlavour_[0] = ev.Jet_flavour[jetIdx];
      jetPt_[0]      = selJetsP4[ij][0].Pt();
      jetEta_[0]     = selJetsP4[ij][0].Eta();

      for(size_t iSystVar=0; iSystVar<5; iSystVar++){
        close_mlj_[iSystVar] = selJetsLJKinematics[ij][iSystVar][0].mlj;
        if(tmvaReader_) kinDisc_[iSystVar] = selJetsKINDisc[ij][iSystVar];
        else            kinDisc_[iSystVar] = -999;
      }
      close_deta_ =selJetsLJKinematics[ij][0][0].deta;
      close_dphi_ =selJetsLJKinematics[ij][0][0].dphi;
      close_ptrel_=selJetsLJKinematics[ij][0][0].ptrel;
      close_lj2ll_deta_ = selJetsLJKinematics[ij][0][0].lj2ll_deta;
      close_lj2ll_dphi_ = selJetsLJKinematics[ij][0][0].lj2ll_dphi;
      far_mlj_    =selJetsLJKinematics[ij][0][1].mlj;
      far_deta_   =selJetsLJKinematics[ij][0][1].deta;
      far_dphi_   =selJetsLJKinematics[ij][0][1].dphi;
      far_ptrel_  =selJetsLJKinematics[ij][0][1].ptrel;
      far_lj2ll_deta_ = selJetsLJKinematics[ij][0][1].lj2ll_deta;
      far_lj2ll_dphi_ = selJetsLJKinematics[ij][0][1].lj2ll_dphi;
      j2ll_deta_  =fabs(selJetsP4[ij][0].Eta()-dilepton.Eta());
      j2ll_dphi_  =fabs(selJetsP4[ij][0].DeltaPhi( dilepton ));
      jp_[0]=ev.Jet_Proba[jetIdx];
      svhe_[0]=ev.Jet_Svx[jetIdx];
      csv_[0]=ev.Jet_CombIVF[jetIdx];
      DeepCSVb_[0]=ev.Jet_DeepCSVb[jetIdx];
      DeepCSVc_[0]=ev.Jet_DeepCSVc[jetIdx];
      DeepCSVl_[0]=ev.Jet_DeepCSVl[jetIdx];
      DeepCSVbN_[0]=ev.Jet_DeepCSVbN[jetIdx];
      DeepCSVcN_[0]=ev.Jet_DeepCSVcN[jetIdx];
      DeepCSVlN_[0]=ev.Jet_DeepCSVlN[jetIdx];
      DeepCSVBDisc_[0]=ev.Jet_DeepCSVBDisc[jetIdx];
      DeepCSVBDiscN_[0]=ev.Jet_DeepCSVBDiscN[jetIdx];
      DeepCSVCvsLDisc_[0]=ev.Jet_DeepCSVCvsLDisc[jetIdx];
      DeepCSVCvsLDiscN_[0]=ev.Jet_DeepCSVCvsLDiscN[jetIdx];
      DeepCSVCvsBDisc_[0]=ev.Jet_DeepCSVCvsBDisc[jetIdx];
      DeepCSVCvsBDiscN_[0]=ev.Jet_DeepCSVCvsBDiscN[jetIdx];
      DeepFlavourBDisc_[0]=ev.Jet_DeepFlavourBDisc[jetIdx];
      DeepFlavourCvsLDisc_[0]=ev.Jet_DeepFlavourCvsLDisc[jetIdx];
      DeepFlavourCvsBDisc_[0]=ev.Jet_DeepFlavourCvsBDisc[jetIdx];
      DeepFlavourB_[0]=ev.Jet_DeepFlavourB[jetIdx];
      kinTree_->Fill();
    }
    //cout << "=== jetFlavour_[0]: " << jetFlavour_[0] << endl;

    //FtM tree is filled with the two leading jets in the KIN discriminator
    if(tmvaReader_){
      for(size_t ij=0; ij<2; ij++){
        size_t jetIdx=leadingkindiscIdx[ij];
        jetFlavour_[ij] = ev.Jet_flavour[jetIdx];
        jetPt_[ij]      = ev.Jet_pt[jetIdx];
        jetEta_[ij]     = ev.Jet_eta[jetIdx];
        jp_[ij]         = ev.Jet_Proba[jetIdx];
        svhe_[ij]       = ev.Jet_Svx[jetIdx];
        csv_[ij]        = ev.Jet_CombIVF[jetIdx];
        kinDisc_[ij]    = leadingkindisc[ij];
        DeepCSVb_[ij] = ev.Jet_DeepCSVb[jetIdx];
        DeepCSVc_[ij] = ev.Jet_DeepCSVc[jetIdx];
        DeepCSVl_[ij] = ev.Jet_DeepCSVl[jetIdx];
        DeepCSVbN_[ij] = ev.Jet_DeepCSVbN[jetIdx];
        DeepCSVcN_[ij] = ev.Jet_DeepCSVcN[jetIdx];
        DeepCSVlN_[ij] = ev.Jet_DeepCSVlN[jetIdx];
        DeepCSVBDisc_[ij] = ev.Jet_DeepCSVBDisc[jetIdx];
        DeepCSVBDiscN_[ij] = ev.Jet_DeepCSVBDiscN[jetIdx];
        DeepCSVCvsLDisc_[ij] = ev.Jet_DeepCSVCvsLDisc[jetIdx];
        DeepCSVCvsLDiscN_[ij] = ev.Jet_DeepCSVCvsLDiscN[jetIdx];
        DeepCSVCvsBDisc_[ij] = ev.Jet_DeepCSVCvsBDisc[jetIdx];
        DeepCSVCvsBDiscN_[ij] = ev.Jet_DeepCSVCvsBDiscN[jetIdx];
        DeepFlavourBDisc_[ij] = ev.Jet_DeepFlavourBDisc[jetIdx];
        DeepFlavourCvsLDisc_[ij] = ev.Jet_DeepFlavourCvsLDisc[jetIdx];
        DeepFlavourCvsBDisc_[ij] = ev.Jet_DeepFlavourCvsBDisc[jetIdx];
        DeepFlavourB_[ij] = ev.Jet_DeepFlavourB[jetIdx];
      }
      ftmTree_->Fill();
    }
    ev = evinit();
  }
  delete tmvaReader_;
  //all done with this file
  inF->Close();
  return 1;
}

std::pair<float,float> TTbarEventAnalysis::getTriggerEfficiency(int id1,float pt1,float eta1,int id2,float pt2,float eta2,int ch)
{
  std::pair<float,float>res(1.0,0.0);
  if(ch==-11*13) { res.first=1.0; res.second=0.05; }
  if(ch==-11*11) { res.first=1.0; res.second=0.05; }
  if(ch==-13*13) { res.first=1.0; res.second=0.05; }
 return res;
}

// eµ channel trigger scale factors.
std::pair<float,float> TTbarEventAnalysis::getTriggerScaleFactor(float pt1, float pt2, int ch, int trigger_index)
{
  std::pair<float,float>res(1.0,0.0);
  // eµ cross-triggers
  if(ch==-11*13 && trigger_index <= 2) {
    if(20.000 < pt1 < 40.000){
      if(15.000 < pt2 < 30.000){res.first=0.99337; res.second=0.01311;}
      if(30.000 < pt2 < 45.000){res.first=1.00016; res.second=0.02094;}
      if(45.000 < pt2 < 60.000){res.first=1.00000; res.second=0.00000;}
      if(60.000 < pt2 < 80.000){res.first=1.00000; res.second=0.00000;}
      if(80.000 < pt2 < 100.000){res.first=1.00000; res.second=0.00000;}
      if(100.000 < pt2 < 150.000){res.first=1.00000; res.second=0.00000;}
      if(150.000 < pt2 < 200.000){res.first=1.00000; res.second=0.00000;}
    }
    if(40.000 < pt1 < 60.000){
      if(15.000 < pt2 < 30.000){res.first=0.99469; res.second=0.01272;}
      if(30.000 < pt2 < 45.000){res.first=0.99636; res.second=0.01099;}
      if(45.000 < pt2 < 60.000){res.first=0.99725; res.second=0.01331;}
      if(60.000 < pt2 < 80.000){res.first=1.00000; res.second=0.00000;}
      if(80.000 < pt2 < 100.000){res.first=1.00000; res.second=0.00000;}
      if(100.000 < pt2 < 150.000){res.first=1.00000; res.second=0.00000;}
      if(150.000 < pt2 < 200.000){res.first=1.00000; res.second=0.00000;}
    }
    if(60.000 < pt1 < 80.000){
      if(15.000 < pt2 < 30.000){res.first=0.98931; res.second=0.01529;}
      if(30.000 < pt2 < 45.000){res.first=0.99984; res.second=0.01049;}
      if(45.000 < pt2 < 60.000){res.first=0.99942; res.second=0.01070;}
      if(60.000 < pt2 < 80.000){res.first=0.99965; res.second=0.01134;}
      if(80.000 < pt2 < 100.000){res.first=1.00000; res.second=0.00000;}
      if(100.000 < pt2 < 150.000){res.first=1.00000; res.second=0.00000;}
      if(150.000 < pt2 < 200.000){res.first=1.00000; res.second=0.00000;}
    }
    if(80.000 < pt1 < 100.000){
      if(15.000 < pt2 < 30.000){res.first=0.98898; res.second=0.02347;}
      if(30.000 < pt2 < 45.000){res.first=0.99689; res.second=0.01625;}
      if(45.000 < pt2 < 60.000){res.first=0.99809; res.second=0.01305;}
      if(60.000 < pt2 < 80.000){res.first=0.99969; res.second=0.01141;}
      if(80.000 < pt2 < 100.000){res.first=0.99418; res.second=0.01539;}
      if(100.000 < pt2 < 150.000){res.first=1.00000; res.second=0.00000;}
      if(150.000 < pt2 < 200.000){res.first=1.00000; res.second=0.00000;}
    }
    if(100.000 < pt1 < 150.000){
      if(15.000 < pt2 < 30.000){res.first=0.99423; res.second=0.03267;}
      if(30.000 < pt2 < 45.000){res.first=0.99641; res.second=0.01130;}
      if(45.000 < pt2 < 60.000){res.first=0.99959; res.second=0.01025;}
      if(60.000 < pt2 < 80.000){res.first=0.99988; res.second=0.01020;}
      if(80.000 < pt2 < 100.000){res.first=0.99918; res.second=0.01695;}
      if(100.000 < pt2 < 150.000){res.first=0.99983; res.second=0.01088;}
      if(150.000 < pt2 < 200.000){res.first=1.00000; res.second=0.00000;}
    }
    if(150.000 < pt1 < 200.000){
      if(15.000 < pt2 < 30.000){res.first=0.98106; res.second=0.03084;}
      if(30.000 < pt2 < 45.000){res.first=0.99543; res.second=0.01638;}
      if(45.000 < pt2 < 60.000){res.first=0.99783; res.second=0.01458;}
      if(60.000 < pt2 < 80.000){res.first=0.99664; res.second=0.01323;}
      if(80.000 < pt2 < 100.000){res.first=0.99361; res.second=0.01080;}
      if(100.000 < pt2 < 150.000){res.first=0.99859; res.second=0.01033;}
      if(150.000 < pt2 < 200.000){res.first=0.99502; res.second=0.01114;}
    }
  }
  //Single muon triggers
  if(ch==-11*13 && (trigger_index == 3 || trigger_index == 4)) {

  }
  //Single electron triggers
  if(ch==-11*13 && (trigger_index == 5 || trigger_index == 6)) {

  }
  return res;
}

// Lepton ID SF's
std::pair<float,float> TTbarEventAnalysis::getLeptonIDScaleFactor(int id,float pt,float eta)
{
  std::pair<float,float>res(1.0,0.0);
  if(abs(id)==11){
    if(-2.500 < eta < -2.000){
if(10.000 < pt < 20.000){res.first=1.03971; res.second=0.01511;}
if(20.000 < pt < 35.000){res.first=1.01590; res.second=0.01629;}
if(35.000 < pt < 50.000){res.first=1.00884; res.second=0.00422;}
if(50.000 < pt < 100.000){res.first=1.00361; res.second=0.00472;}
if(100.000 < pt < 500.000){res.first=1.02709; res.second=0.02213;}
}
if(-2.000 < eta < -1.566){
if(10.000 < pt < 20.000){res.first=1.02044; res.second=0.02424;}
if(20.000 < pt < 35.000){res.first=0.99732; res.second=0.01245;}
if(35.000 < pt < 50.000){res.first=1.00120; res.second=0.00305;}
if(50.000 < pt < 100.000){res.first=1.00348; res.second=0.00421;}
if(100.000 < pt < 500.000){res.first=1.02461; res.second=0.01406;}
}
if(-1.566 < eta < -1.444){
if(10.000 < pt < 20.000){res.first=1.00000; res.second=1.00000;}
if(20.000 < pt < 35.000){res.first=1.00000; res.second=1.00000;}
if(35.000 < pt < 50.000){res.first=1.00000; res.second=1.00000;}
if(50.000 < pt < 100.000){res.first=1.00000; res.second=1.00000;}
if(100.000 < pt < 500.000){res.first=1.00000; res.second=1.00000;}
}
if(-1.444 < eta < -0.800){
if(10.000 < pt < 20.000){res.first=1.00361; res.second=0.02878;}
if(20.000 < pt < 35.000){res.first=0.98319; res.second=0.01444;}
if(35.000 < pt < 50.000){res.first=0.98221; res.second=0.00404;}
if(50.000 < pt < 100.000){res.first=0.98286; res.second=0.00525;}
if(100.000 < pt < 500.000){res.first=1.00110; res.second=0.00979;}
}
if(-0.800 < eta < 0.000){
if(10.000 < pt < 20.000){res.first=0.95841; res.second=0.02270;}
if(20.000 < pt < 35.000){res.first=0.96477; res.second=0.01379;}
if(35.000 < pt < 50.000){res.first=0.97316; res.second=0.00262;}
if(50.000 < pt < 100.000){res.first=0.97194; res.second=0.00232;}
if(100.000 < pt < 500.000){res.first=1.00329; res.second=0.00818;}
}
if(0.000 < eta < 0.800){
if(10.000 < pt < 20.000){res.first=0.96552; res.second=0.02270;}
if(20.000 < pt < 35.000){res.first=0.98505; res.second=0.01379;}
if(35.000 < pt < 50.000){res.first=0.98593; res.second=0.00262;}
if(50.000 < pt < 100.000){res.first=0.98309; res.second=0.00232;}
if(100.000 < pt < 500.000){res.first=1.00993; res.second=0.00818;}
}
if(0.800 < eta < 1.444){
if(10.000 < pt < 20.000){res.first=1.00000; res.second=0.02845;}
if(20.000 < pt < 35.000){res.first=0.98590; res.second=0.01444;}
if(35.000 < pt < 50.000){res.first=0.98804; res.second=0.00404;}
if(50.000 < pt < 100.000){res.first=0.98624; res.second=0.00525;}
if(100.000 < pt < 500.000){res.first=1.01004; res.second=0.00979;}
}
if(1.444 < eta < 1.566){
if(10.000 < pt < 20.000){res.first=1.00000; res.second=1.00000;}
if(20.000 < pt < 35.000){res.first=1.00000; res.second=1.00000;}
if(35.000 < pt < 50.000){res.first=1.00000; res.second=1.00000;}
if(50.000 < pt < 100.000){res.first=1.00000; res.second=1.00000;}
if(100.000 < pt < 500.000){res.first=1.00000; res.second=1.00000;}
}
if(1.566 < eta < 2.000){
if(10.000 < pt < 20.000){res.first=1.02426; res.second=0.02424;}
if(20.000 < pt < 35.000){res.first=0.98780; res.second=0.01245;}
if(35.000 < pt < 50.000){res.first=0.99522; res.second=0.00305;}
if(50.000 < pt < 100.000){res.first=0.99191; res.second=0.00421;}
if(100.000 < pt < 500.000){res.first=0.99453; res.second=0.01389;}
}
if(2.000 < eta < 2.500){
if(10.000 < pt < 20.000){res.first=1.02269; res.second=0.01511;}
if(20.000 < pt < 35.000){res.first=1.01143; res.second=0.01629;}
if(35.000 < pt < 50.000){res.first=0.99624; res.second=0.00422;}
if(50.000 < pt < 100.000){res.first=0.98808; res.second=0.00472;}
if(100.000 < pt < 500.000){res.first=1.00676; res.second=0.02196;}
}
  }
  // Muons SFs
  else if (abs(id)==13){
    if(0.000 < fabs(eta) < 0.900){
if(15.000 < pt < 20.000){res.first=0.98943; res.second=0.00482;}
if(20.000 < pt < 25.000){res.first=0.98763; res.second=0.00312;}
if(25.000 < pt < 30.000){res.first=0.98792; res.second=0.00323;}
if(30.000 < pt < 40.000){res.first=0.98650; res.second=0.00299;}
if(40.000 < pt < 50.000){res.first=0.98673; res.second=0.00310;}
if(50.000 < pt < 60.000){res.first=0.98517; res.second=0.00318;}
if(60.000 < pt < 120.000){res.first=0.98463; res.second=0.00250;}
}
if(0.900 < fabs(eta) < 1.200){
if(15.000 < pt < 20.000){res.first=0.97899; res.second=0.00509;}
if(20.000 < pt < 25.000){res.first=0.97658; res.second=0.00496;}
if(25.000 < pt < 30.000){res.first=0.98151; res.second=0.00474;}
if(30.000 < pt < 40.000){res.first=0.97872; res.second=0.00398;}
if(40.000 < pt < 50.000){res.first=0.97925; res.second=0.00325;}
if(50.000 < pt < 60.000){res.first=0.97903; res.second=0.00302;}
if(60.000 < pt < 120.000){res.first=0.97832; res.second=0.00230;}
}
if(1.200 < fabs(eta) < 2.100){
if(15.000 < pt < 20.000){res.first=0.99012; res.second=0.00532;}
if(20.000 < pt < 25.000){res.first=0.98945; res.second=0.00414;}
if(25.000 < pt < 30.000){res.first=0.99097; res.second=0.00433;}
if(30.000 < pt < 40.000){res.first=0.99050; res.second=0.00392;}
if(40.000 < pt < 50.000){res.first=0.99152; res.second=0.00306;}
if(50.000 < pt < 60.000){res.first=0.99063; res.second=0.00302;}
if(60.000 < pt < 120.000){res.first=0.99049; res.second=0.00322;}
}
if(2.100 < fabs(eta) < 2.400){
if(15.000 < pt < 20.000){res.first=0.97577; res.second=0.00702;}
if(20.000 < pt < 25.000){res.first=0.97531; res.second=0.00562;}
if(25.000 < pt < 30.000){res.first=0.97610; res.second=0.00553;}
if(30.000 < pt < 40.000){res.first=0.97594; res.second=0.00475;}
if(40.000 < pt < 50.000){res.first=0.97642; res.second=0.00412;}
if(50.000 < pt < 60.000){res.first=0.97201; res.second=0.00717;}
if(60.000 < pt < 120.000){res.first=0.96955; res.second=0.01196;}
}
  }
  else{
    cout << "[getLeptonIDScaleFactor] Warning: Lepton neither electron nor muon!" << endl;
  }
  return res;
}

// Electron Reco SF's
std::pair<float,float> TTbarEventAnalysis::getElectronRECOScaleFactor(int id,float pt,float eta){
  std::pair<float,float>res(1.0,0.0);
  if(-2.500 < eta < -2.000){
if(20.000 < pt < 45.000){res.first=0.99679; res.second=0.00338;}
if(45.000 < pt < 75.000){res.first=0.99159; res.second=0.00606;}
if(75.000 < pt < 100.000){res.first=0.98837; res.second=0.01406;}
if(100.000 < pt < 500.000){res.first=1.00958; res.second=0.01756;}
}
if(-2.000 < eta < -1.566){
if(20.000 < pt < 45.000){res.first=0.99272; res.second=0.00315;}
if(45.000 < pt < 75.000){res.first=0.99277; res.second=0.00218;}
if(75.000 < pt < 100.000){res.first=0.98463; res.second=0.02270;}
if(100.000 < pt < 500.000){res.first=1.01638; res.second=0.00862;}
}
if(-1.566 < eta < -1.444){
if(20.000 < pt < 45.000){res.first=0.95760; res.second=0.01777;}
if(45.000 < pt < 75.000){res.first=0.96216; res.second=0.00619;}
if(75.000 < pt < 100.000){res.first=1.01213; res.second=0.03077;}
if(100.000 < pt < 500.000){res.first=1.01438; res.second=0.02680;}
}
if(-1.444 < eta < -1.000){
if(20.000 < pt < 45.000){res.first=0.98560; res.second=0.00224;}
if(45.000 < pt < 75.000){res.first=0.98672; res.second=0.00210;}
if(75.000 < pt < 100.000){res.first=0.98278; res.second=0.00934;}
if(100.000 < pt < 500.000){res.first=0.97982; res.second=0.00597;}
}
if(-1.000 < eta < -0.500){
if(20.000 < pt < 45.000){res.first=0.97945; res.second=0.00262;}
if(45.000 < pt < 75.000){res.first=0.98161; res.second=0.00310;}
if(75.000 < pt < 100.000){res.first=0.97660; res.second=0.01485;}
if(100.000 < pt < 500.000){res.first=0.98486; res.second=0.00677;}
}
if(-0.500 < eta < 0.000){
if(20.000 < pt < 45.000){res.first=0.97526; res.second=0.00258;}
if(45.000 < pt < 75.000){res.first=0.97953; res.second=0.00393;}
if(75.000 < pt < 100.000){res.first=0.98774; res.second=0.00722;}
if(100.000 < pt < 500.000){res.first=0.98987; res.second=0.00687;}
}
if(0.000 < eta < 0.500){
if(20.000 < pt < 45.000){res.first=0.98660; res.second=0.00258;}
if(45.000 < pt < 75.000){res.first=0.98772; res.second=0.00393;}
if(75.000 < pt < 100.000){res.first=0.98774; res.second=0.00722;}
if(100.000 < pt < 500.000){res.first=0.98987; res.second=0.00687;}
}
if(0.500 < eta < 1.000){
if(20.000 < pt < 45.000){res.first=0.98770; res.second=0.00262;}
if(45.000 < pt < 75.000){res.first=0.98778; res.second=0.00310;}
if(75.000 < pt < 100.000){res.first=0.97660; res.second=0.01485;}
if(100.000 < pt < 500.000){res.first=0.98486; res.second=0.00677;}
}
if(1.000 < eta < 1.444){
if(20.000 < pt < 45.000){res.first=0.98972; res.second=0.00224;}
if(45.000 < pt < 75.000){res.first=0.98878; res.second=0.00210;}
if(75.000 < pt < 100.000){res.first=0.98278; res.second=0.00934;}
if(100.000 < pt < 500.000){res.first=0.97982; res.second=0.00597;}
}
if(1.444 < eta < 1.566){
if(20.000 < pt < 45.000){res.first=0.97156; res.second=0.01777;}
if(45.000 < pt < 75.000){res.first=0.97514; res.second=0.00619;}
if(75.000 < pt < 100.000){res.first=1.01213; res.second=0.03077;}
if(100.000 < pt < 500.000){res.first=1.01438; res.second=0.02680;}
}
if(1.566 < eta < 2.000){
if(20.000 < pt < 45.000){res.first=0.99380; res.second=0.00315;}
if(45.000 < pt < 75.000){res.first=0.99076; res.second=0.00218;}
if(75.000 < pt < 100.000){res.first=0.98463; res.second=0.02270;}
if(100.000 < pt < 500.000){res.first=1.01638; res.second=0.00862;}
}
if(2.000 < eta < 2.500){
if(20.000 < pt < 45.000){res.first=1.00000; res.second=0.00338;}
if(45.000 < pt < 75.000){res.first=0.99254; res.second=0.00606;}
if(75.000 < pt < 100.000){res.first=0.98837; res.second=0.01406;}
if(100.000 < pt < 500.000){res.first=1.00958; res.second=0.01756;}
}
  return res;
}

// Muon Isolation SF's
std::pair<float,float> TTbarEventAnalysis::getMuonISOScaleFactor(int id,float pt,float eta){
  std::pair<float,float>res(1.0,0.0);
  if(abs(id)==13){
    if(0.000 < fabs(eta) < 0.900){
if(15.000 < pt < 20.000){res.first=0.98966; res.second=0.01192;}
if(20.000 < pt < 25.000){res.first=0.99483; res.second=0.01022;}
if(25.000 < pt < 30.000){res.first=0.99151; res.second=0.00601;}
if(30.000 < pt < 40.000){res.first=0.99560; res.second=0.00089;}
if(40.000 < pt < 50.000){res.first=0.99698; res.second=0.00043;}
if(50.000 < pt < 60.000){res.first=0.99720; res.second=0.00048;}
if(60.000 < pt < 120.000){res.first=0.99902; res.second=0.00055;}
}
if(0.900 < fabs(eta) < 1.200){
if(15.000 < pt < 20.000){res.first=1.00199; res.second=0.01143;}
if(20.000 < pt < 25.000){res.first=1.00037; res.second=0.00814;}
if(25.000 < pt < 30.000){res.first=1.00337; res.second=0.00717;}
if(30.000 < pt < 40.000){res.first=1.00055; res.second=0.00084;}
if(40.000 < pt < 50.000){res.first=0.99795; res.second=0.00041;}
if(50.000 < pt < 60.000){res.first=0.99961; res.second=0.00105;}
if(60.000 < pt < 120.000){res.first=1.00004; res.second=0.00099;}
}
if(1.200 < fabs(eta) < 2.100){
if(15.000 < pt < 20.000){res.first=1.00330; res.second=0.00679;}
if(20.000 < pt < 25.000){res.first=1.00705; res.second=0.00581;}
if(25.000 < pt < 30.000){res.first=1.00517; res.second=0.00428;}
if(30.000 < pt < 40.000){res.first=1.00159; res.second=0.00116;}
if(40.000 < pt < 50.000){res.first=0.99983; res.second=0.00019;}
if(50.000 < pt < 60.000){res.first=0.99887; res.second=0.00047;}
if(60.000 < pt < 120.000){res.first=0.99988; res.second=0.00054;}
}
if(2.100 < fabs(eta) < 2.400){
if(15.000 < pt < 20.000){res.first=1.01378; res.second=0.00593;}
if(20.000 < pt < 25.000){res.first=1.01079; res.second=0.00433;}
if(25.000 < pt < 30.000){res.first=1.00428; res.second=0.00296;}
if(30.000 < pt < 40.000){res.first=1.00315; res.second=0.00091;}
if(40.000 < pt < 50.000){res.first=1.00109; res.second=0.00051;}
if(50.000 < pt < 60.000){res.first=1.00107; res.second=0.00122;}
if(60.000 < pt < 120.000){res.first=1.00079; res.second=0.00128;}
}
  }
  return res;
}

void TTbarEventAnalysis::finalizeOutput(TH1F *normWgt)
{
  outF_->cd();
  for(std::map<TString,TH1F *>::iterator it = histos_.begin(); it != histos_.end(); it++){
    it->second->Write();
  }
  kinTree_->Write();
  if(ftmTree_) ftmTree_->Write();
  outF_->Close();
}
