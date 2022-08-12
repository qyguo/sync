#define hello_cxx
#include "hello.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <stdio.h>
#include <stdlib.h>
#include "./support_LepJet.h"
using namespace std;

void hello::Loop()
{
//   In a ROOT session, you can do:
//      root> .L hello.C
//      root> hello t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   FILE * fp;

   //fp = fopen ("file.txt", "w+");

   //if((fp=freopen(input_file.c_str(), "w" ,stdout))==NULL) {
   cout<<output_file.c_str()<<endl;
   const char *fp_name=output_file.c_str();
   //const char *fp_name="tmp___.txt";

   if((fp=freopen(fp_name, "w" ,stdout))==NULL) {
     printf("Cannot open file.\n");
     exit(1);
   }


   Long64_t nentries = fChain->GetEntriesFast();

   vector<int> order_index;
   vector<int> GENlep_order_index;
   Int_t lep_Hindex_[4]={-1,-1,-1,-1};
   Int_t GENlep_Hindex_[4]={-1,-1,-1,-1};
   TLorentzVector j1, j2, Higgs, hj, jj, hjj;
   TLorentzVector GENj1, GENj2, GENHiggs, GENhj, GENjj, GENhjj;
   float mjj(-1.0), deltajj(-1), dphijj(-1), pTHj(-1), pTHjj(-1), mHj(-1), mHjj(-1);
   float GENmjj(-1.0), GENdeltajj(-1), GENdphijj(-1), GENpTHj(-1), GENpTHjj(-1), GENmHj(-1), GENmHjj(-1);
   float ptj1(-1.0), etaj1(-1.0), phij1(-1.0), massj1(-1.0), ptj2(-1.0), etaj2(-1.0), phij2(-1.0), massj2(-1.0);
   float GEN_ptj1(-1.0), GEN_etaj1(-1.0), GEN_phij1(-1.0), GEN_massj1(-1.0), GEN_ptj2(-1.0), GEN_etaj2(-1.0), GEN_phij2(-1.0), GEN_massj2(-1.0);
   //Int_t *lep_Hindex_ = new Int_t[4];
   int Number_lep_S[5]={0,0,0,0,0};
   int Number_GENlep_S[5]={0,0,0,0,0};
   int Number_4e4mu2e2mu_A[3]={0,0,0};
   int Number_4e4mu2e2mu_B[3]={0,0,0};
   int Number_4e4mu2e2mu_A_4e_jet[3]={0,0,0};
   int Number_4e4mu2e2mu_A_4mu_jet[3]={0,0,0};
   int Number_4e4mu2e2mu_A_2e2mu_jet[3]={0,0,0};
   int Number_4e4mu2e2mu_B_4e_jet[3]={0,0,0};
   int Number_4e4mu2e2mu_B_4mu_jet[3]={0,0,0};
   int Number_4e4mu2e2mu_B_2e2mu_jet[3]={0,0,0};

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      order_index.clear();
      GENlep_order_index.clear();

      mjj = -1.0; deltajj = -1.0; dphijj = -1.0; pTHj = -1.0; pTHjj = -1.0; mHj = -1.0; mHjj = -1.0;
      GENmjj = -1.0; GENdeltajj = -1.0; GENdphijj = -1.0; GENpTHj = -1.0; GENpTHjj = -1.0; GENmHj = -1.0; GENmHjj = -1.0;
      ptj1 = -1.0; etaj1 = -1.0; phij1 = -1.0; massj1 = -1.0;
      ptj2 = -1.0; etaj2 = -1.0; phij2 = -1.0; massj2 = -1.0;
      GEN_ptj1 = -1.0; GEN_etaj1 = -1.0; GEN_phij1 = -1.0; GEN_massj1 = -1.0;
      GEN_ptj2 = -1.0; GEN_etaj2 = -1.0; GEN_phij2 = -1.0; GEN_massj2 = -1.0;

      printf("%llu:%llu:%llu:", Run, LumiSect, Event);

      if(passedFullSelection)
      {
          printf("%.4f:%.4f:%.4f:%.4f:", mass4l, eta4l, phi4l, pT4l);
          support_LepJet::order_Hindex(lep_pt, lep_Hindex, lep_Hindex_);
          //printf("%.4f:%.4f:%.4f:", (*lepFSR_pt)[lep_Hindex_[0]], (*lepFSR_eta)[lep_Hindex_[0]], (*lepFSR_phi)[lep_Hindex_[0]]);
          //printf("%.4f:%.4f:%.4f:", (*lepFSR_pt)[lep_Hindex_[1]], (*lepFSR_eta)[lep_Hindex_[1]], (*lepFSR_phi)[lep_Hindex_[1]]);
          //printf("%.4f:%.4f:%.4f:", (*lepFSR_pt)[lep_Hindex_[2]], (*lepFSR_eta)[lep_Hindex_[2]], (*lepFSR_phi)[lep_Hindex_[2]]);
          //printf("%.4f:%.4f:%.4f:", (*lepFSR_pt)[lep_Hindex_[3]], (*lepFSR_eta)[lep_Hindex_[3]], (*lepFSR_phi)[lep_Hindex_[3]]);
          printf("%.4f:%.4f:%.4f:", (*lep_pt)[lep_Hindex_[0]], (*lep_eta)[lep_Hindex_[0]], (*lep_phi)[lep_Hindex_[0]]);
          printf("%.4f:%.4f:%.4f:", (*lep_pt)[lep_Hindex_[1]], (*lep_eta)[lep_Hindex_[1]], (*lep_phi)[lep_Hindex_[1]]);
          printf("%.4f:%.4f:%.4f:", (*lep_pt)[lep_Hindex_[2]], (*lep_eta)[lep_Hindex_[2]], (*lep_phi)[lep_Hindex_[2]]);
          printf("%.4f:%.4f:%.4f:", (*lep_pt)[lep_Hindex_[3]], (*lep_eta)[lep_Hindex_[3]], (*lep_phi)[lep_Hindex_[3]]);
          //TLorentzVector l1,l2,l3,l4,Higgs;
          //l1.SetPtEtaPhiM((*lep_pt)[lep_Hindex_[0]], (*lep_eta)[lep_Hindex_[0]], (*lep_phi)[lep_Hindex_[0]], (*lep_mass)[lep_Hindex_[0]]);
          //l2.SetPtEtaPhiM((*lep_pt)[lep_Hindex_[1]], (*lep_eta)[lep_Hindex_[1]], (*lep_phi)[lep_Hindex_[1]], (*lep_mass)[lep_Hindex_[1]]);
          //l3.SetPtEtaPhiM((*lep_pt)[lep_Hindex_[2]], (*lep_eta)[lep_Hindex_[2]], (*lep_phi)[lep_Hindex_[2]], (*lep_mass)[lep_Hindex_[2]]);
          //l4.SetPtEtaPhiM((*lep_pt)[lep_Hindex_[3]], (*lep_eta)[lep_Hindex_[3]], (*lep_phi)[lep_Hindex_[3]], (*lep_mass)[lep_Hindex_[3]]);
          //Higgs=l1+l2+l3+l4;
          //printf("%.4f:", Higgs.M());
          //printf("%.2f:%.2f:%.2f:", mass4l,massZ1,massZ2);
          //printf("%.6f:%.6f:%.6f:%.6f:", lep_mva[lep_Hindex_[0]], lep_mva[lep_Hindex_[1]], lep_mva[lep_Hindex_[2]], lep_mva[lep_Hindex_[3]]);

          Higgs.SetPtEtaPhiM(pT4l, eta4l, phi4l, mass4l);

          if(njets_pt30_eta4p7>0)
          {
              j1.SetPtEtaPhiM((*jet_pt)[jet1index],(*jet_eta)[jet1index],(*jet_phi)[jet1index],(*jet_mass)[jet1index]);
              hj = j1 + Higgs;
              pTHj = hj.Pt();
              mHj = hj.M();

              ptj1 = j1.Pt();
              etaj1 = j1.Eta();
              phij1 = j1.Phi();
              massj1 = j1.M();
          }
          if(njets_pt30_eta4p7>1)
          {
              j2.SetPtEtaPhiM((*jet_pt)[jet2index],(*jet_eta)[jet2index],(*jet_phi)[jet2index],(*jet_mass)[jet2index]);
              jj = j1 + j2;
              hjj = jj + Higgs;

              mjj = jj.M();
              deltajj = j1.Eta()-j2.Eta();
              dphijj = j1.DeltaPhi(j2);
              pTHjj = hjj.Pt();
              mHjj = hjj.M();

              ptj2 = j2.Pt();
              etaj2 = j2.Eta();
              phij2 = j2.Phi();
              massj2 = j2.M();
          }
      }
      else if (!passedFullSelection)
      {
          printf("%.4f:%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0, -1.0);//4l
          printf("%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0);//l1
          printf("%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0);//l2
          printf("%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0);//l3
          printf("%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0);//l4
      }
      printf("%.4f:%.4f:%.4f:%.4f:%.4f:%.4f:%.4f:%.4f:", ptj1, etaj1, phij1, massj1, ptj2, etaj2, phij2, massj2);
      printf("%d:", njets_pt30_eta4p7);

      support_LepJet::order_pt(GENlep_pt, GENlep_order_index);
      if(passedFiducialSelection)
      {
          printf("%.4f:%.4f:%.4f:", GENmassZ1, GENmassZ2, GENmass4l);
          //support_LepJet::order_pt(GENlep_pt, GENlep_order_index);
          printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[0]], (*GENlep_eta)[GENlep_order_index[0]], (*GENlep_phi)[GENlep_order_index[0]], (*GENlep_mass)[GENlep_order_index[0]]);
          printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[1]], (*GENlep_eta)[GENlep_order_index[1]], (*GENlep_phi)[GENlep_order_index[1]], (*GENlep_mass)[GENlep_order_index[1]]);
          printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[2]], (*GENlep_eta)[GENlep_order_index[2]], (*GENlep_phi)[GENlep_order_index[2]], (*GENlep_mass)[GENlep_order_index[2]]);
          printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[3]], (*GENlep_eta)[GENlep_order_index[3]], (*GENlep_phi)[GENlep_order_index[3]], (*GENlep_mass)[GENlep_order_index[3]]);
          //support_LepJet::order_Hindex(GENlep_pt, GENlep_Hindex, GENlep_Hindex_);
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_Hindex_[0]], (*GENlep_eta)[GENlep_Hindex_[0]], (*GENlep_phi)[GENlep_Hindex_[0]], (*GENlep_mass)[GENlep_Hindex_[0]]);
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_Hindex_[1]], (*GENlep_eta)[GENlep_Hindex_[1]], (*GENlep_phi)[GENlep_Hindex_[1]], (*GENlep_mass)[GENlep_Hindex_[1]]);
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_Hindex_[2]], (*GENlep_eta)[GENlep_Hindex_[2]], (*GENlep_phi)[GENlep_Hindex_[2]], (*GENlep_mass)[GENlep_Hindex_[2]]);
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_Hindex_[3]], (*GENlep_eta)[GENlep_Hindex_[3]], (*GENlep_phi)[GENlep_Hindex_[3]], (*GENlep_mass)[GENlep_Hindex_[3]]);
          GENHiggs.SetPtEtaPhiM(GENpT4l, GENeta4l, GENphi4l, GENmass4l);
          support_LepJet::order_pt(GENjet_pt, order_index);

          if(GENnjets_pt30_eta4p7>0)
          {
              int GENjet1index = order_index[0];
              GENj1.SetPtEtaPhiM((*GENjet_pt)[GENjet1index],(*GENjet_eta)[GENjet1index],(*GENjet_phi)[GENjet1index],(*GENjet_mass)[GENjet1index]);
              GENhj = GENj1 + GENHiggs;
              GENpTHj = GENhj.Pt();
              GENmHj = GENhj.M();

              GEN_ptj1 = GENj1.Pt();
              GEN_etaj1 = GENj1.Eta();
              GEN_phij1 = GENj1.Phi();
              GEN_massj1 = GENj1.M();
          }
          if(GENnjets_pt30_eta4p7>1)
          {
              int GENjet2index = order_index[1];
              GENj2.SetPtEtaPhiM((*GENjet_pt)[GENjet2index],(*GENjet_eta)[GENjet2index],(*GENjet_phi)[GENjet2index],(*GENjet_mass)[GENjet2index]);
              GENjj = GENj1 + GENj2;
              GENhjj = GENjj + GENHiggs;

              GENmjj = GENjj.M();
              GENdeltajj = GENj1.Eta()-GENj2.Eta();
              GENdphijj = GENj1.DeltaPhi(GENj2);
              GENpTHjj = GENhjj.Pt();
              GENmHjj = GENhjj.M();

              GEN_ptj2 = GENj2.Pt();
              GEN_etaj2 = GENj2.Eta();
              GEN_phij2 = GENj2.Phi();
              GEN_massj2 = GENj2.M();
          }
      }
      else if(!passedFiducialSelection)
      {
          printf("%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0);//Z1 Z2 4l
          //printf("%.4f:%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0, -1.0);//l1
          //printf("%.4f:%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0, -1.0);//l2
          //printf("%.4f:%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0, -1.0);//l3
          //printf("%.4f:%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0, -1.0);//l4
          unsigned int i=0;
          for(; i<(*GENlep_pt).size(); i++)
          {
              if (i<4)
                  printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[i]], (*GENlep_eta)[GENlep_order_index[i]], (*GENlep_phi)[GENlep_order_index[i]], (*GENlep_mass)[GENlep_order_index[i]]);
          }
          while (i<4)
          {
              printf("%.4f:%.4f:%.4f:%.4f:", -1.0, -1.0, -1.0, -1.0);
              i++;
          }
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[0]], (*GENlep_eta)[GENlep_order_index[0]], (*GENlep_phi)[GENlep_order_index[0]], (*GENlep_mass)[GENlep_order_index[0]]);
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[1]], (*GENlep_eta)[GENlep_order_index[1]], (*GENlep_phi)[GENlep_order_index[1]], (*GENlep_mass)[GENlep_order_index[1]]);
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[2]], (*GENlep_eta)[GENlep_order_index[2]], (*GENlep_phi)[GENlep_order_index[2]], (*GENlep_mass)[GENlep_order_index[2]]);
          //printf("%.4f:%.4f:%.4f:%.4f:", (*GENlep_pt)[GENlep_order_index[3]], (*GENlep_eta)[GENlep_order_index[3]], (*GENlep_phi)[GENlep_order_index[3]], (*GENlep_mass)[GENlep_order_index[3]]);
      }
      printf("%.4f:%.4f:%.4f:%.4f:%.4f:%.4f:%.4f:%.4f:", GEN_ptj1, GEN_etaj1, GEN_phij1, GEN_massj1, GEN_ptj2, GEN_etaj2, GEN_phij2, GEN_massj2);
      printf("%d:", GENnjets_pt30_eta4p7);
      if(passedFiducialSelection)    printf("%d:", 1);
      else    printf("%d:", 0);
      printf("%.4f:", eventWeight);
      if (passedFullSelection)
      {
          printf("%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:", D_0m, D_CP, D_0hp, D_int, D_L1, D_L1Zg);
          //printf("%.3f:%.3f:", TauC_Inc_0j_EnergyWgt, TauB_Inc_0j_EnergyWgt);
          printf("%.3f:%.3f:", TauC_Inc_0j_EnergyWgt, TauB_Inc_0j_pTWgt);
      }
      else if (!passedFullSelection)
      {
          printf("%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:", -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0);
      }
      printf("%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:", mjj, deltajj, dphijj, pTHj, pTHjj, mHj, mHjj );
      if (passedFiducialSelection)
      {
          printf("%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:", GEND_0m, GEND_CP, GEND_0hp, GEND_int, GEND_L1, GEND_L1Zg);
          //printf("%.3f:%.3f:", GEN_TauC_Inc_0j_EnergyWgt, GEN_TauB_Inc_0j_EnergyWgt);
          printf("%.3f:%.3f:", GEN_TauC_Inc_0j_EnergyWgt, GEN_TauB_Inc_0j_pTWgt);
      }
      else if (!passedFiducialSelection)
      {
          printf("%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:", -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0);
      }
      printf("%.3f:%.3f:%.3f:%.3f:%.3f:%.3f:%.3f", GENmjj, GENdeltajj, GENdphijj, GENpTHj, GENpTHjj, GENmHj, GENmHjj );
      printf("\n");
      //cout<<endl;
   }
   fclose(fp);
   exit(0);
}
