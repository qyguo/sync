#include <iostream>
#include <string>
#include <TMath.h>
#include <vector>
#include <algorithm>
#include "TLorentzVector.h"
namespace support_LepJet
{
    void order_pt(vector<float> *GENlep_pt, vector<int> &order_index)
    {

        vector<float> GENlep_pt_ordered;
        GENlep_pt_ordered.clear();
        order_index.clear();
        for(unsigned int i=0; i<GENlep_pt->size(); i++)
        {
            if(GENlep_pt_ordered.size()==0 || (*GENlep_pt)[i]<GENlep_pt_ordered[GENlep_pt_ordered.size()-1])
            {
                GENlep_pt_ordered.push_back((*GENlep_pt)[i]);
                order_index.push_back(i);
                continue;
            }
            for(unsigned int j=0; j<GENlep_pt_ordered.size(); j++)
            {
                if((*GENlep_pt)[i]>=GENlep_pt_ordered[j])
                {
                    GENlep_pt_ordered.insert(GENlep_pt_ordered.begin()+j,(*GENlep_pt)[i]);
                    order_index.insert(order_index.begin()+j, i);
                    break;
                }
            }
        }

    }


    void FourLept_order_pt(vector<float> *GENlep_pt, int &GENLep1, int &GENLep2, int &GENLep3, int &GENLep4)
    {
        GENLep1 =-1; GENLep2=-1; GENLep3=-1; GENLep4=-1;
        float GENLep_pt1(-9999), GENLep_pt2(-9999), GENLep_pt3(-9999), GENLep_pt4(-9999);
        for ( int jj=0; jj<(*GENlep_pt).size(); jj++)
        {
            float tmp_high_pt=(*GENlep_pt)[jj];
            if (tmp_high_pt>GENLep_pt1)
            {
                GENLep_pt4 = GENLep_pt3;    GENLep4 = GENLep3;
                GENLep_pt3 = GENLep_pt2;    GENLep3 = GENLep2;
                GENLep_pt2 = GENLep_pt1;    GENLep2 = GENLep1;
                GENLep_pt1 = tmp_high_pt;   GENLep1 = jj;
            }
            else if (tmp_high_pt>GENLep_pt2)
            {
                GENLep_pt4 = GENLep_pt3;    GENLep4 = GENLep3;
                GENLep_pt3 = GENLep_pt2;    GENLep3 = GENLep2;
                GENLep_pt2 = tmp_high_pt;   GENLep2 = jj;
            }
            else if (tmp_high_pt>GENLep_pt3)
            {
                GENLep_pt4 = GENLep_pt3;    GENLep4 = GENLep3;
                GENLep_pt3 = tmp_high_pt;   GENLep3 = jj;
            }
            else if (tmp_high_pt>GENLep_pt4)
            {
                GENLep_pt4 = tmp_high_pt;   GENLep4 = jj;
            }
        }
    }

    void order_Hindex( vector<float> *GENlep_pt, Int_t GENlep_Hindex[4], Int_t GENlep_Hindex_[4])
    {
        if ((*GENlep_pt)[GENlep_Hindex[0]]<(*GENlep_pt)[GENlep_Hindex[1]])
        {
            GENlep_Hindex_[0]=GENlep_Hindex[1];
            GENlep_Hindex_[1]=GENlep_Hindex[0];
        }
        else
        {
            GENlep_Hindex_[0]=GENlep_Hindex[0];
            GENlep_Hindex_[1]=GENlep_Hindex[1];
        }
        if ((*GENlep_pt)[GENlep_Hindex[2]]<(*GENlep_pt)[GENlep_Hindex[3]])
        {
            GENlep_Hindex_[2]=GENlep_Hindex[3];
            GENlep_Hindex_[3]=GENlep_Hindex[2];
        }
        else
        {
            GENlep_Hindex_[2]=GENlep_Hindex[2];
            GENlep_Hindex_[3]=GENlep_Hindex[3];
        }
    }

}
