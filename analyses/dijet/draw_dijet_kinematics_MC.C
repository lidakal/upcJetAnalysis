#include "../../cms_palette.h"

void draw_dijet_kinematics_MC()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TString sample = "beamA_diffraction_pthat10";

    // ----- REF ----- //
    TString suffix_ref_wVM = "_ref_wVM";
    TFile *f_ref_wVM = new TFile("histos/"+sample+"_dijet_kinematics"+suffix_ref_wVM+".root");
    std::cout << "NO RG WITH SWAP: Loaded " << f_ref_wVM->GetName() << std::endl;
    TH1F *h_QT_ref_wVM = (TH1F*)f_ref_wVM->Get("h_QT")->Clone("h_QT_ref_wVM");
    TH1F *h_PT_ref_wVM = (TH1F*)f_ref_wVM->Get("h_PT")->Clone("h_PT_ref_wVM");
    TH1F *h_Minv_ref_wVM = (TH1F*)f_ref_wVM->Get("h_Minv")->Clone("h_Minv_ref_wVM");
    TH1F *h_y_ref_wVM = (TH1F*)f_ref_wVM->Get("h_y")->Clone("h_y_ref_wVM");
    TH1F *h_PHI_ref_wVM = (TH1F*)f_ref_wVM->Get("h_PHI")->Clone("h_PHI_ref_wVM");
    TH1F *h_PHI_signed_ref_wVM = (TH1F*)f_ref_wVM->Get("h_PHI_signed")->Clone("h_PHI_signed_ref_wVM");
    TH2F *h_cos2PHI_vs_QT_ref_wVM = (TH2F*)f_ref_wVM->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_ref_wVM");

    TString suffix_ref_noVM = "_ref_noVM";
    TFile *f_ref_noVM = new TFile("histos/"+sample+"_dijet_kinematics"+suffix_ref_noVM+".root");
    std::cout << "NO RG WITH SWAP: Loaded " << f_ref_noVM->GetName() << std::endl;
    TH1F *h_QT_ref_noVM = (TH1F*)f_ref_noVM->Get("h_QT")->Clone("h_QT_ref_noVM");
    TH1F *h_PT_ref_noVM = (TH1F*)f_ref_noVM->Get("h_PT")->Clone("h_PT_ref_noVM");
    TH1F *h_Minv_ref_noVM = (TH1F*)f_ref_noVM->Get("h_Minv")->Clone("h_Minv_ref_noVM");
    TH1F *h_y_ref_noVM = (TH1F*)f_ref_noVM->Get("h_y")->Clone("h_y_ref_noVM");
    TH1F *h_PHI_ref_noVM = (TH1F*)f_ref_noVM->Get("h_PHI")->Clone("h_PHI_ref_noVM");
    TH1F *h_PHI_signed_ref_noVM = (TH1F*)f_ref_noVM->Get("h_PHI_signed")->Clone("h_PHI_signed_ref_noVM");
    TH2F *h_cos2PHI_vs_QT_ref_noVM = (TH2F*)f_ref_noVM->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_ref_noVM");

    // ----- RECO ----- //
    TString suffix_noRG_wSwap = "_jetID_jetVM_noAbsY_noAddActCut_noRG";
    TFile *f_noRG_wSwap = new TFile("histos/"+sample+"_dijet_kinematics"+suffix_noRG_wSwap+".root");
    std::cout << "NO RG WITH SWAP: Loaded " << f_noRG_wSwap->GetName() << std::endl;
    TH1F *h_QT_noRG_wSwap = (TH1F*)f_noRG_wSwap->Get("h_QT")->Clone("h_QT_noRG_wSwap");
    TH1F *h_PT_noRG_wSwap = (TH1F*)f_noRG_wSwap->Get("h_PT")->Clone("h_PT_noRG_wSwap");
    TH1F *h_Minv_noRG_wSwap = (TH1F*)f_noRG_wSwap->Get("h_Minv")->Clone("h_Minv_noRG_wSwap");
    TH1F *h_y_noRG_wSwap = (TH1F*)f_noRG_wSwap->Get("h_y")->Clone("h_y_noRG_wSwap");
    TH1F *h_PHI_noRG_wSwap = (TH1F*)f_noRG_wSwap->Get("h_PHI")->Clone("h_PHI_noRG_wSwap");
    TH1F *h_PHI_signed_noRG_wSwap = (TH1F*)f_noRG_wSwap->Get("h_PHI_signed")->Clone("h_PHI_signed_noRG_wSwap");
    TH2F *h_cos2PHI_vs_QT_noRG_wSwap = (TH2F*)f_noRG_wSwap->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_noRG_wSwap");

    TString suffix_wRG_wSwap = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM_noAbsY";
    TFile *f_wRG_wSwap = new TFile("histos/"+sample+"_dijet_kinematics"+suffix_wRG_wSwap+".root");
    std::cout << "WITH RG WITH SWAP: Loaded " << f_wRG_wSwap->GetName() << std::endl;
    TH1F *h_QT_wRG_wSwap = (TH1F*)f_wRG_wSwap->Get("h_QT")->Clone("h_QT_wRG_wSwap");
    TH1F *h_PT_wRG_wSwap = (TH1F*)f_wRG_wSwap->Get("h_PT")->Clone("h_PT_wRG_wSwap");
    TH1F *h_Minv_wRG_wSwap = (TH1F*)f_wRG_wSwap->Get("h_Minv")->Clone("h_Minv_wRG_wSwap");
    TH1F *h_y_wRG_wSwap = (TH1F*)f_wRG_wSwap->Get("h_y")->Clone("h_y_wRG_wSwap");
    TH1F *h_PHI_wRG_wSwap = (TH1F*)f_wRG_wSwap->Get("h_PHI")->Clone("h_PHI_wRG_wSwap");
    TH1F *h_PHI_signed_wRG_wSwap = (TH1F*)f_wRG_wSwap->Get("h_PHI_signed")->Clone("h_PHI_signed_wRG_wSwap");
    TH2F *h_cos2PHI_vs_QT_wRG_wSwap = (TH2F*)f_wRG_wSwap->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_wRG_wSwap");

    TString suffix_noRG_noSwap = "_jetID_jetVM_noAddActCut_noRG_noSwap_noAbsY";
    TFile *f_noRG_noSwap = new TFile("histos/"+sample+"_dijet_kinematics"+suffix_noRG_noSwap+".root");
    std::cout << "NO RG NO SWAP: Loaded " << f_noRG_noSwap->GetName() << std::endl;
    TH1F *h_QT_noRG_noSwap = (TH1F*)f_noRG_noSwap->Get("h_QT")->Clone("h_QT_noRG_noSwap");
    TH1F *h_PT_noRG_noSwap = (TH1F*)f_noRG_noSwap->Get("h_PT")->Clone("h_PT_noRG_noSwap");
    TH1F *h_Minv_noRG_noSwap = (TH1F*)f_noRG_noSwap->Get("h_Minv")->Clone("h_Minv_noRG_noSwap");
    TH1F *h_y_noRG_noSwap = (TH1F*)f_noRG_noSwap->Get("h_y")->Clone("h_y_noRG_noSwap");
    TH1F *h_PHI_noRG_noSwap = (TH1F*)f_noRG_noSwap->Get("h_PHI")->Clone("h_PHI_noRG_noSwap");
    TH1F *h_PHI_signed_noRG_noSwap = (TH1F*)f_noRG_noSwap->Get("h_PHI_signed")->Clone("h_PHI_signed_noRG_noSwap");
    TH2F *h_cos2PHI_vs_QT_noRG_noSwap = (TH2F*)f_noRG_noSwap->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_noRG_noSwap");

    TString suffix_wRG_noSwap = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM_noSwap";
    TFile *f_wRG_noSwap = new TFile("histos/"+sample+"_dijet_kinematics"+suffix_wRG_noSwap+".root");
    std::cout << "WITH RG NO SWAP: Loaded " << f_wRG_noSwap->GetName() << std::endl;
    TH1F *h_QT_wRG_noSwap = (TH1F*)f_wRG_noSwap->Get("h_QT")->Clone("h_QT_wRG_noSwap");
    TH1F *h_PT_wRG_noSwap = (TH1F*)f_wRG_noSwap->Get("h_PT")->Clone("h_PT_wRG_noSwap");
    TH1F *h_Minv_wRG_noSwap = (TH1F*)f_wRG_noSwap->Get("h_Minv")->Clone("h_Minv_wRG_noSwap");
    TH1F *h_y_wRG_noSwap = (TH1F*)f_wRG_noSwap->Get("h_y")->Clone("h_y_wRG_noSwap");
    TH1F *h_PHI_wRG_noSwap = (TH1F*)f_wRG_noSwap->Get("h_PHI")->Clone("h_PHI_wRG_noSwap");
    TH1F *h_PHI_signed_wRG_noSwap = (TH1F*)f_wRG_noSwap->Get("h_PHI_signed")->Clone("h_PHI_signed_wRG_noSwap");
    TH2F *h_cos2PHI_vs_QT_wRG_noSwap = (TH2F*)f_wRG_noSwap->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_wRG_noSwap");

    // ------- REF vs RECO ----------//
    if (true) {
        // QT + PT, Minv, y
        TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
        c_kinematics->Divide(3,1);
        c_kinematics->cd(1)->SetLeftMargin(0.14);
        c_kinematics->cd(1)->SetRightMargin(0.03);
        c_kinematics->cd(2)->SetLeftMargin(0.14);
        c_kinematics->cd(2)->SetRightMargin(0.03);
        c_kinematics->cd(3)->SetLeftMargin(0.14);
        c_kinematics->cd(3)->SetRightMargin(0.03);

        c_kinematics->cd(1);
        h_QT_ref_wVM->SetLineColorAlpha(cmsViolet,1.);
        h_QT_ref_noVM->SetLineColorAlpha(cmsViolet,0.3);
        h_QT_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        h_PT_ref_wVM->SetLineColorAlpha(cmsRed,1.);
        h_PT_ref_noVM->SetLineColorAlpha(cmsRed,0.3);
        h_PT_noRG_noSwap->SetLineColorAlpha(cmsOrange,1.);

        for (auto h : {
            h_QT_ref_wVM, h_QT_ref_noVM, h_QT_noRG_noSwap,
            h_PT_ref_wVM, h_PT_ref_noVM, h_PT_noRG_noSwap
        })
        {
            h->Rebin(2);
            h->Scale(1/h->Integral());
            h->SetMarkerColor(h->GetLineColor());
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("QT or PT (GeV)");
            h->GetYaxis()->SetTitle("Normalized entries");
            h->GetYaxis()->SetRangeUser(0., 0.35);
            h->Draw("same");
        }

        TLegend *legend = new TLegend(0.18, 0.65, 0.87, 0.85);
        legend->SetBorderSize(0);
        legend->SetFillStyle(0);
        legend->SetNColumns(2);
        legend->SetMargin(0.2);
        legend->AddEntry(new TH1F(), "QT", "");
        legend->AddEntry(new TH1F(), "PT", "");
        legend->AddEntry(h_QT_ref_noVM, "REF w/o VM", "l");
        legend->AddEntry(h_PT_ref_noVM, "REF w/o VM", "l");
        legend->AddEntry(h_QT_ref_wVM, "REF w/ VM", "l");
        legend->AddEntry(h_PT_ref_wVM, "REF w/ VM", "l");
        legend->AddEntry(h_QT_noRG_noSwap, "RECO w/ VM", "l");
        legend->AddEntry(h_PT_noRG_noSwap, "RECO w/ VM", "l");
        legend->Draw();

        c_kinematics->cd(2);
        h_Minv_ref_wVM->SetLineColorAlpha(cmsViolet,1.);
        h_Minv_ref_noVM->SetLineColorAlpha(cmsViolet,0.3);
        h_Minv_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            h_Minv_ref_wVM, h_Minv_ref_noVM, h_Minv_noRG_noSwap,
        })
        {
            h->Rebin(2);
            h->Scale(1/h->Integral());
            h->SetMarkerColor(h->GetLineColor());
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
            h->GetYaxis()->SetTitle("Normalized entries");
            h->GetYaxis()->SetRangeUser(0., 0.2);
            h->Draw("same");
        }

        TLegend *legend_m = new TLegend(0.2, 0.7, 0.6, 0.85);
        legend_m->SetBorderSize(0);
        legend_m->SetFillStyle(0);
        legend_m->SetMargin(0.2);
        legend_m->AddEntry(h_Minv_ref_noVM, "REF w/o VM", "l");
        legend_m->AddEntry(h_Minv_ref_wVM, "REF w/ VM", "l");
        legend_m->AddEntry(h_Minv_noRG_noSwap, "RECO w/ VM", "l");
        legend_m->Draw();

        c_kinematics->cd(3);
        h_y_ref_wVM->SetLineColorAlpha(cmsViolet,1.);
        h_y_ref_noVM->SetLineColorAlpha(cmsViolet,0.3);
        h_y_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            h_y_ref_wVM, h_y_ref_noVM, h_y_noRG_noSwap,
        })
        {
            h->Rebin(2);
            h->Scale(1/h->Integral());
            h->SetMarkerColor(h->GetLineColor());
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("Dijet y");
            h->GetYaxis()->SetTitle("Normalized entries");
            h->GetYaxis()->SetRangeUser(0., 0.2);
            h->Draw("same");
        }

        TLegend *legend_y = new TLegend(0.2, 0.7, 0.6, 0.85);
        legend_y->SetBorderSize(0);
        legend_y->SetFillStyle(0);
        legend_y->SetMargin(0.2);
        legend_y->AddEntry(h_y_ref_noVM, "REF w/o VM", "l");
        legend_y->AddEntry(h_y_ref_wVM, "REF w/ VM", "l");
        legend_y->AddEntry(h_y_noRG_noSwap, "RECO w/ VM", "l");
        legend_y->Draw();

        c_kinematics->Print("plots/dijet_kinematics/"+sample+"_ref_vs_reco_dijet_kinematics.pdf");

        // dN/dPHI vs PHI, <cos(2PHI)> vs QT
        TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 1800, 800);
        c_observables->Divide(2,1);
        c_observables->cd(1)->SetLeftMargin(0.14);
        c_observables->cd(1)->SetRightMargin(0.03);
        c_observables->cd(2)->SetLeftMargin(0.14);
        c_observables->cd(2)->SetRightMargin(0.03);

        c_observables->cd(1);
        h_PHI_signed_ref_wVM->SetLineColorAlpha(cmsViolet,1.);
        h_PHI_signed_ref_noVM->SetLineColorAlpha(cmsViolet,0.3);
        h_PHI_signed_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            h_PHI_signed_ref_wVM, h_PHI_signed_ref_noVM, h_PHI_signed_noRG_noSwap,
        })
        {
            h->Rebin(5);
            h->Scale(1/h->Integral(),"width");
            h->SetMarkerColor(h->GetLineColor());
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("#Phi (radians)");
            h->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
            h->GetYaxis()->SetRangeUser(0., 0.5);
            h->Draw("same");
        }

        TLegend *legend_phi = (TLegend*) legend_m->Clone("legend_phi");
        legend_phi->Draw();

        c_observables->cd(2);
        TProfile *p_cos2PHI_vs_QT_noRG_noSwap = h_cos2PHI_vs_QT_noRG_noSwap->ProfileX();
        TProfile *p_cos2PHI_vs_QT_ref_wVM = h_cos2PHI_vs_QT_ref_wVM->ProfileX();
        TProfile *p_cos2PHI_vs_QT_ref_noVM = h_cos2PHI_vs_QT_ref_noVM->ProfileX();

        p_cos2PHI_vs_QT_ref_wVM->SetLineColorAlpha(cmsViolet,1.);
        p_cos2PHI_vs_QT_ref_noVM->SetLineColorAlpha(cmsViolet,0.3);
        p_cos2PHI_vs_QT_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            p_cos2PHI_vs_QT_ref_wVM, 
            p_cos2PHI_vs_QT_ref_noVM, 
            p_cos2PHI_vs_QT_noRG_noSwap,
        })
        {
            h->Rebin(5);
            // h->SetLineWidth(2);
            h->SetMarkerColor(h->GetLineColor());
            h->GetXaxis()->SetTitle("QT (GeV)");
            h->GetYaxis()->SetTitle("<cos(2#Phi)>");
            h->GetYaxis()->SetRangeUser(-0.5, 1.5);
            h->GetXaxis()->SetRangeUser(0., 40.);
            h->Draw("same");
        }
        legend_phi->Draw();

        c_observables->Print("plots/dijet_kinematics/"+sample+"_ref_vs_reco_observables.pdf");
    }


    // ------- RECO --------- // 
    if (false) {
        // QT + PT, Minv, y
        TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
        c_kinematics->Divide(3,1);
        c_kinematics->cd(1)->SetLeftMargin(0.14);
        c_kinematics->cd(1)->SetRightMargin(0.03);
        c_kinematics->cd(2)->SetLeftMargin(0.14);
        c_kinematics->cd(2)->SetRightMargin(0.03);
        c_kinematics->cd(3)->SetLeftMargin(0.14);
        c_kinematics->cd(3)->SetRightMargin(0.03);

        c_kinematics->cd(1);
        h_QT_wRG_wSwap->SetLineColorAlpha(cmsViolet,1.);
        h_QT_wRG_noSwap->SetLineColorAlpha(cmsViolet,0.3);
        h_QT_noRG_wSwap->SetLineColorAlpha(cmsBlue,0.3);
        h_QT_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        h_PT_wRG_wSwap->SetLineColorAlpha(cmsRed,1.);
        h_PT_wRG_noSwap->SetLineColorAlpha(cmsRed,0.3);
        h_PT_noRG_wSwap->SetLineColorAlpha(cmsOrange,0.3);
        h_PT_noRG_noSwap->SetLineColorAlpha(cmsOrange,1.);

        for (auto h : {
            h_QT_wRG_wSwap, h_QT_wRG_noSwap, h_QT_noRG_wSwap, h_QT_noRG_noSwap,
            h_PT_wRG_wSwap, h_PT_wRG_noSwap, h_PT_noRG_wSwap, h_PT_noRG_noSwap
        })
        {
            h->Rebin(2);
            h->Scale(1/h->Integral());
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("QT or PT (GeV)");
            h->GetYaxis()->SetTitle("Normalized entries");
            h->GetYaxis()->SetRangeUser(0., 0.35);
            h->Draw("hist same");
        }

        TLegend *legend = new TLegend(0.18, 0.65, 0.87, 0.85);
        legend->SetBorderSize(0);
        legend->SetFillStyle(0);
        legend->SetNColumns(2);
        legend->SetMargin(0.2);
        legend->AddEntry(new TH1F(), "QT", "");
        legend->AddEntry(new TH1F(), "PT", "");
        legend->AddEntry(h_QT_wRG_wSwap, "YES RG YES SWAP", "l");
        legend->AddEntry(h_PT_wRG_wSwap, "YES RG YES SWAP", "l");
        legend->AddEntry(h_QT_wRG_noSwap, "YES RG NO SWAP", "l");
        legend->AddEntry(h_PT_wRG_noSwap, "YES RG NO SWAP", "l");
        legend->AddEntry(h_QT_noRG_wSwap, "NO RG YES SWAP", "l");
        legend->AddEntry(h_PT_noRG_wSwap, "NO RG YES SWAP", "l");
        legend->AddEntry(h_QT_noRG_noSwap, "NO RG NO SWAP", "l");
        legend->AddEntry(h_PT_noRG_noSwap, "NO RG NO SWAP", "l");
        legend->Draw();

        c_kinematics->cd(2);
        h_Minv_wRG_wSwap->SetLineColorAlpha(cmsViolet,1.);
        h_Minv_wRG_noSwap->SetLineColorAlpha(cmsViolet,0.3);
        h_Minv_noRG_wSwap->SetLineColorAlpha(cmsBlue,0.3);
        h_Minv_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            h_Minv_wRG_wSwap, h_Minv_wRG_noSwap, h_Minv_noRG_wSwap, h_Minv_noRG_noSwap,
        })
        {
            h->Rebin(2);
            h->Scale(1/h->Integral());
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
            h->GetYaxis()->SetTitle("Normalized entries");
            h->GetYaxis()->SetRangeUser(0., 0.2);
            h->Draw("hist same");
        }

        TLegend *legend_m = new TLegend(0.2, 0.7, 0.6, 0.85);
        legend_m->SetBorderSize(0);
        legend_m->SetFillStyle(0);
        legend_m->SetMargin(0.2);
        legend_m->AddEntry(h_Minv_wRG_wSwap, "YES RG YES SWAP", "l");
        legend_m->AddEntry(h_Minv_wRG_noSwap, "YES RG NO SWAP", "l");
        legend_m->AddEntry(h_Minv_noRG_wSwap, "NO RG YES SWAP", "l");
        legend_m->AddEntry(h_Minv_noRG_noSwap, "NO RG NO SWAP", "l");
        legend_m->Draw();

        c_kinematics->cd(3);
        h_y_wRG_wSwap->SetLineColorAlpha(cmsViolet,1.);
        h_y_wRG_noSwap->SetLineColorAlpha(cmsViolet,0.3);
        h_y_noRG_wSwap->SetLineColorAlpha(cmsBlue,0.3);
        h_y_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            h_y_wRG_wSwap, h_y_wRG_noSwap, h_y_noRG_wSwap, h_y_noRG_noSwap,
        })
        {
            h->Rebin(2);
            h->Scale(1/h->Integral());
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("Dijet y");
            h->GetYaxis()->SetTitle("Normalized entries");
            h->GetYaxis()->SetRangeUser(0., 0.2);
            h->Draw("hist same");
        }

        TLegend *legend_y = new TLegend(0.2, 0.7, 0.6, 0.85);
        legend_y->SetBorderSize(0);
        legend_y->SetFillStyle(0);
        legend_y->SetMargin(0.2);
        legend_y->AddEntry(h_y_wRG_wSwap, "YES RG YES SWAP", "l");
        legend_y->AddEntry(h_y_wRG_noSwap, "YES RG NO SWAP", "l");
        legend_y->AddEntry(h_y_noRG_wSwap, "NO RG YES SWAP", "l");
        legend_y->AddEntry(h_y_noRG_noSwap, "NO RG NO SWAP", "l");
        legend_y->Draw();

        c_kinematics->Print("plots/dijet_kinematics/"+sample+"_noRG_wSwap_vs_wRG_wSwap_dijet_kinematics.pdf");

        // dN/dPHI vs PHI, <cos(2PHI)> vs QT
        TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 1800, 800);
        c_observables->Divide(2,1);
        c_observables->cd(1)->SetLeftMargin(0.14);
        c_observables->cd(1)->SetRightMargin(0.03);
        c_observables->cd(2)->SetLeftMargin(0.14);
        c_observables->cd(2)->SetRightMargin(0.03);

        c_observables->cd(1);
        h_PHI_signed_wRG_wSwap->SetLineColorAlpha(cmsViolet,1.);
        h_PHI_signed_wRG_noSwap->SetLineColorAlpha(cmsViolet,0.3);
        h_PHI_signed_noRG_wSwap->SetLineColorAlpha(cmsBlue,0.3);
        h_PHI_signed_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            h_PHI_signed_wRG_wSwap, h_PHI_signed_wRG_noSwap, h_PHI_signed_noRG_wSwap, h_PHI_signed_noRG_noSwap,
        })
        {
            h->Rebin(5);
            h->Scale(1/h->Integral(),"width");
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("#Phi (radians)");
            h->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
            h->GetYaxis()->SetRangeUser(0., 0.5);
            h->Draw("hist same");
        }

        TLegend *legend_phi = (TLegend*) legend_m->Clone("legend_phi");
        legend_phi->Draw();

        c_observables->cd(2);
        TProfile *p_cos2PHI_vs_QT_noRG_wSwap = h_cos2PHI_vs_QT_noRG_wSwap->ProfileX();
        TProfile *p_cos2PHI_vs_QT_wRG_wSwap = h_cos2PHI_vs_QT_wRG_wSwap->ProfileX();
        TProfile *p_cos2PHI_vs_QT_noRG_noSwap = h_cos2PHI_vs_QT_noRG_noSwap->ProfileX();
        TProfile *p_cos2PHI_vs_QT_wRG_noSwap = h_cos2PHI_vs_QT_wRG_noSwap->ProfileX();

        p_cos2PHI_vs_QT_wRG_wSwap->SetLineColorAlpha(cmsViolet,1.);
        p_cos2PHI_vs_QT_wRG_noSwap->SetLineColorAlpha(cmsViolet,0.3);
        p_cos2PHI_vs_QT_noRG_wSwap->SetLineColorAlpha(cmsBlue,0.3);
        p_cos2PHI_vs_QT_noRG_noSwap->SetLineColorAlpha(cmsBlue,1.);

        for (auto h : {
            p_cos2PHI_vs_QT_wRG_wSwap, 
            p_cos2PHI_vs_QT_wRG_noSwap, 
            p_cos2PHI_vs_QT_noRG_wSwap, 
            p_cos2PHI_vs_QT_noRG_noSwap,
        })
        {
            h->Rebin(5);
            // h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("QT (GeV)");
            h->GetYaxis()->SetTitle("<cos(2#Phi)>");
            h->GetYaxis()->SetRangeUser(-0.5, 1.5);
            h->GetXaxis()->SetRangeUser(0., 40.);
            h->Draw("hist same");
        }
        legend_phi->Draw();

        c_observables->Print("plots/dijet_kinematics/"+sample+"_noRG_vs_wRG_observables.pdf");
    }
}