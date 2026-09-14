#include "../../cms_palette.h"

void draw_header() 
{
    TLatex *cms = new TLatex();
    cms->SetNDC();
    cms->SetTextAlign(11);
    cms->SetTextSize(28);
    cms->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Internal}");

    TLatex *data = new TLatex();
    data->SetNDC();
    data->SetTextAlign(31);
    data->SetTextSize(28);
    data->DrawLatex(0.95, 0.92, "2023 PbPb (5.36 TeV)");
}

void draw_PF_distribution_per_region()
{
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    // std::vector<TString> regions = {"HF"};
    std::vector<TString> regions = {"BB", "EC1", "EC2", "HF"};

    TString sample = "beamA_diffraction_pthat10";
    // TString sample = "hiemptybx_2024rereco";
    // TString sample = "hiforwardAll_2024rereco";

    TFile *fin = new TFile("histos/"+sample+"_pf_distribution_noRG_jetID_jetVM.root"); // requires plot_PF_distribution_v2.C

    for (auto region : regions) {
        TH3F *h_PF_plus_Emax = (TH3F *) fin->Get("h_PF_plus_"+region+"_Emax");
        TH3F *h_PF_minus_Emax = (TH3F *) fin->Get("h_PF_minus_"+region+"_Emax");

        // Make projections
        TH1F *h_PF_plus_Emax_E = (TH1F *) h_PF_plus_Emax->ProjectionZ("h_PF_plus_"+region+"_Emax_E");
        TH1F *h_PF_minus_Emax_E = (TH1F *) h_PF_minus_Emax->ProjectionZ("h_PF_minus_"+region+"Emax_E");
    
        // Normalize over whole range
        for (auto h : {h_PF_plus_Emax_E, h_PF_minus_Emax_E}) {
            h->Scale(1/h->Integral(1,h->GetNbinsX()+1));
        }

        // Format
        int color_plus = cmsOrange;
        int color_minus = cmsBlue;
        h_PF_plus_Emax_E->SetLineWidth(2);
        h_PF_plus_Emax_E->SetLineColor(color_plus);
        h_PF_plus_Emax_E->SetFillColorAlpha(color_plus, 0.5);
        h_PF_plus_Emax_E->SetFillStyle(3004);

        h_PF_minus_Emax_E->SetLineWidth(2);
        h_PF_minus_Emax_E->SetLineColor(color_minus);
        h_PF_minus_Emax_E->SetFillColorAlpha(color_minus, 0.5);
        h_PF_minus_Emax_E->SetFillStyle(3005);

        // Legend
        TLegend *leg_E = new TLegend(0.7, 0.7, 0.85, 0.85);
        leg_E->SetBorderSize(0);
        leg_E->SetFillStyle(0);
        if (sample.Contains("hiemptybx")) leg_E->SetHeader("Empty BX (data)");
        if (sample.Contains("beam")) leg_E->SetHeader("Signal events (MC)");
        if (sample.Contains("hiforward")) leg_E->SetHeader("Dijet events (data)");
        leg_E->AddEntry(h_PF_plus_Emax_E, region+"+", "f");
        leg_E->AddEntry(h_PF_minus_Emax_E, region+"-", "f");
        
        // Draw
        TCanvas *c_E = new TCanvas("c_E_"+region, "", 800, 700);
        c_E->SetTopMargin(0.1);
        c_E->SetBottomMargin(0.1);
        c_E->SetLeftMargin(0.15);
        c_E->SetRightMargin(0.05);
        
        h_PF_plus_Emax_E->GetXaxis()->SetTitle("PF E^{max}");
        h_PF_plus_Emax_E->GetYaxis()->SetTitle("Normalized distribution");
        if (sample.Contains("hiemptybx")) h_PF_plus_Emax_E->GetXaxis()->SetRangeUser(0.,20.);
        h_PF_plus_Emax_E->GetYaxis()->SetRangeUser(1e-6, 1.);
        h_PF_plus_Emax_E->Draw("hist");
        h_PF_minus_Emax_E->Draw("hist same");
        c_E->SetLogy();
        leg_E->Draw();
        draw_header();

        c_E->Print("plots/pf_distributions/"+sample+"_pf_distribution_"+region+".pdf");

        // Cumulative distribution 
        TH1F *h_PF_plus_Emax_Ecum = (TH1F *) h_PF_plus_Emax_E->Clone("h_PF_plus_"+region+"_Emax_Ecum");
        TH1F *h_PF_minus_Emax_Ecum = (TH1F *) h_PF_minus_Emax_E->Clone("h_PF_minus_"+region+"_Emax_Ecum");
        for (Int_t ibin=0; ibin<h_PF_plus_Emax_Ecum->GetNbinsX(); ibin++) {
            h_PF_plus_Emax_Ecum->SetBinContent(ibin, h_PF_plus_Emax_E->Integral(ibin, h_PF_plus_Emax_E->GetNbinsX()+1));
            h_PF_minus_Emax_Ecum->SetBinContent(ibin, h_PF_minus_Emax_E->Integral(ibin, h_PF_minus_Emax_E->GetNbinsX()+1));
        }

        // Draw
        TCanvas *c_Ecum = new TCanvas("c_Ecum_"+region, "", 800, 700);
        c_Ecum->SetTopMargin(0.1);
        c_Ecum->SetBottomMargin(0.1);
        c_Ecum->SetLeftMargin(0.15);
        c_Ecum->SetRightMargin(0.05);
        
        double ymin_Ecum = 1e-6;
        double ymax_Ecum = 5.;
        h_PF_plus_Emax_Ecum->GetXaxis()->SetTitle("PF E^{max}");
        h_PF_plus_Emax_Ecum->GetYaxis()->SetTitle("Cumulative distribution");
        if (sample.Contains("hiemptybx")) h_PF_plus_Emax_Ecum->GetXaxis()->SetRangeUser(0.,20.);
        h_PF_plus_Emax_Ecum->GetYaxis()->SetRangeUser(1e-6, 5.);
        h_PF_plus_Emax_Ecum->Draw("hist");
        h_PF_minus_Emax_Ecum->Draw("hist same");
        c_Ecum->SetLogy();
        leg_E->Draw();
        draw_header();

        // Find bin for <1% of noise events in empty BX
        if (sample.Contains("hiemptybx")) {
            double thr = 0.01;
            bool found_plus = false;
            bool found_minus = false;
            for (Int_t ibin=1; ibin<=h_PF_plus_Emax_Ecum->GetNbinsX(); ibin++) {
                double content_plus = h_PF_plus_Emax_Ecum->GetBinContent(ibin);
                if ((!found_plus) && (content_plus < thr)) {
                    double Ethr = h_PF_plus_Emax_Ecum->GetXaxis()->GetBinLowEdge(ibin);
                    TLine *line_plus = new TLine(Ethr, ymin_Ecum, Ethr, ymax_Ecum);
                    line_plus->SetLineColor(color_plus);
                    line_plus->Draw();
                    found_plus = true;
                }

                double content_minus = h_PF_minus_Emax_Ecum->GetBinContent(ibin);
                if ((!found_minus) && (content_minus < thr)) {
                    double Ethr = h_PF_minus_Emax_Ecum->GetXaxis()->GetBinLowEdge(ibin);
                    TLine *line_minus = new TLine(Ethr, ymin_Ecum, Ethr, ymax_Ecum);
                    line_minus->SetLineColor(color_minus);
                    line_minus->Draw();
                    found_minus = true;
                }

                if (found_plus && found_minus) break;
            }
        }

        c_Ecum->Print("plots/pf_distributions/"+sample+"_pf_cumulative_distribution_"+region+".pdf");
    }
    

    

}