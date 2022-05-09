const int Nads = 8;
int color[Nads]={kBlue, kBlue, kRed, kRed, kGreen-1, kGreen-1, kGreen-1, kGreen-1};

TGraphErrors* PointGraph(int iad, float mean_in_graph, float* rel_diff, float* rel_diff_error, int marker_type, float marker_size, int opt_color=0){
    TGraphErrors* gr_temp = new TGraphErrors();
    gr_temp->SetPoint(0,mean_in_graph,rel_diff[iad]);
    gr_temp->SetPointError(0,0,rel_diff_error[iad]);
    gr_temp->SetMarkerStyle(marker_type);
    gr_temp->SetMarkerColor(color[iad]);
    gr_temp->SetLineColor(color[iad]);
    if(opt_color!=0){
        gr_temp->SetMarkerColor(opt_color);
        gr_temp->SetLineColor(opt_color);
    }
    gr_temp->SetLineWidth(2);
    gr_temp->SetMarkerSize(marker_size);
    return gr_temp;
}

void ReadSource(FILE* m_file,float* mean, float* rel_diff, float* rel_diff_error){
    float temp_value;
    fscanf(m_file,"%*s %f",&temp_value);
    mean[0] = temp_value;
    for(int iad=0; iad<Nads; ++iad){
        fscanf(m_file,"%f",&temp_value);
        rel_diff[iad]=temp_value;
    }
    for(int iad=0; iad<Nads; ++iad){
        fscanf(m_file,"%f",&temp_value);
        rel_diff_error[iad]=temp_value;
    }
}

void RelEnPlot(bool isAdSimple = true){
    gStyle->SetLineWidth(1);
    gStyle->SetFrameLineWidth(1);
    
    float alpha_c_prompt_mean_in_plot[1]; //MeV
    float alpha_c_delayed_mean_in_plot[1]; //MeV
    float alpha_d_mean_in_plot[1]; //MeV
    float alpha_e_mean_in_plot[1];
    
    float alpha_c_prompt_mean[Nads];
    float alpha_c_prompt_sigma[Nads];
    float alpha_c_delayed_mean[Nads];
    float alpha_c_delayed_sigma[Nads];
    float alpha_d_mean[Nads];
    float alpha_d_sigma[Nads];
    float alpha_e_mean[Nads];
    float alpha_e_sigma[Nads];
    
    float k_mean_in_plot[1]; //MeV
    float tl_mean_in_plot[1];
    
    float k_mean[Nads];
    float k_sigma[Nads];
    float tl_mean[Nads];
    float tl_sigma[Nads];
    
    float ngd_mean_in_plot[1]; //MeV
    float nh_mean_in_plot[1]; //MeV
    
    float ngd_spn_mean[Nads];
    float ngd_spn_sigma[Nads];
    float nh_spn_mean[Nads];
    float nh_spn_sigma[Nads];
    float ngd_ibd_mean[Nads];
    float ngd_ibd_sigma[Nads];
    float nh_ibd_mean[Nads];
    float nh_ibd_sigma[Nads];
    
    float co_mean_in_plot[1]; //MeV
    
    float co_mean[Nads];
    float co_sigma[Nads];
    
    FILE* file_data;
    if(isAdSimple){
        file_data = fopen("./data_adsimple.txt","r");
    }
    else{
        //file_data = fopen("./data_adsimple_nl.txt","r");
        file_data = fopen("./data_adsimple_nl_ngd_alpha_corr.txt","r");
    }
    if(file_data==NULL){cout<<"There is no file"<<endl; return;}
    
    ReadSource(file_data,alpha_c_prompt_mean_in_plot,alpha_c_prompt_mean,alpha_c_prompt_sigma);
    ReadSource(file_data,alpha_c_delayed_mean_in_plot,alpha_c_delayed_mean,alpha_c_delayed_sigma);
    ReadSource(file_data,alpha_d_mean_in_plot,alpha_d_mean,alpha_d_sigma);
    ReadSource(file_data,alpha_e_mean_in_plot,alpha_e_mean,alpha_e_sigma);
    
    ReadSource(file_data,k_mean_in_plot,k_mean,k_sigma);
    ReadSource(file_data,tl_mean_in_plot,tl_mean,tl_sigma);
    
    ReadSource(file_data,nh_mean_in_plot,nh_spn_mean,nh_spn_sigma);
    ReadSource(file_data,nh_mean_in_plot,nh_ibd_mean,nh_ibd_sigma);
    ReadSource(file_data,ngd_mean_in_plot,ngd_spn_mean,ngd_spn_sigma);
    ReadSource(file_data,ngd_mean_in_plot,ngd_ibd_mean,ngd_ibd_sigma);
    
    ReadSource(file_data,co_mean_in_plot,co_mean,co_sigma);
    fclose(file_data);
    
    int color[Nads]={kBlue, kBlue, kRed, kRed, kGreen-1, kGreen-1, kGreen-1, kGreen-1};

    TGraphErrors* gr_alpha_c_prompt[Nads];
    TGraphErrors* gr_alpha_c_delayed[Nads];
    TGraphErrors* gr_alpha_d[Nads];
    TGraphErrors* gr_alpha_e[Nads];

    TGraphErrors* gr_k[Nads];
    TGraphErrors* gr_tl[Nads];

    TGraphErrors* gr_nh_spn[Nads];
    TGraphErrors* gr_ngd_spn[Nads];
    TGraphErrors* gr_ngd_ibd[Nads];
    TGraphErrors* gr_nh_ibd[Nads];

    TGraphErrors* gr_co[Nads];

    for(int iad=0; iad<Nads; ++iad){
        //alphas
        gr_alpha_c_prompt[iad] = (TGraphErrors*) PointGraph(iad,alpha_c_prompt_mean_in_plot[0],alpha_c_prompt_mean,alpha_c_prompt_sigma,22,1.);
        gr_alpha_c_delayed[iad]= (TGraphErrors*) PointGraph(iad,alpha_c_delayed_mean_in_plot[0],alpha_c_delayed_mean,alpha_c_delayed_sigma,22,1.);
        gr_alpha_d[iad]= (TGraphErrors*) PointGraph(iad,alpha_d_mean_in_plot[0],alpha_d_mean,alpha_d_sigma,22,1.);
        gr_alpha_e[iad]= (TGraphErrors*) PointGraph(iad,alpha_e_mean_in_plot[0],alpha_e_mean,alpha_e_sigma,22,1.);

        //---40K, 208Tl
        gr_k[iad]= (TGraphErrors*) PointGraph(iad,k_mean_in_plot[0],k_mean,k_sigma,33,1.2);
        gr_tl[iad]= (TGraphErrors*) PointGraph(iad,tl_mean_in_plot[0],tl_mean,tl_sigma,33,1.2);
	
        //---nGd, nH
        gr_nh_spn[iad]= (TGraphErrors*) PointGraph(iad,nh_mean_in_plot[0],nh_spn_mean,nh_spn_sigma,20,1.);
        gr_nh_ibd[iad]= (TGraphErrors*) PointGraph(iad,nh_mean_in_plot[0],nh_ibd_mean,nh_ibd_sigma,20,1.,kMagenta);
        gr_ngd_spn[iad]= (TGraphErrors*) PointGraph(iad,ngd_mean_in_plot[0],ngd_spn_mean,ngd_spn_sigma,20,1.);
        gr_ngd_ibd[iad]= (TGraphErrors*) PointGraph(iad,ngd_mean_in_plot[0],ngd_ibd_mean,ngd_ibd_sigma,20,1.);
        
        //60Co
        gr_co[iad]= (TGraphErrors*) PointGraph(iad,co_mean_in_plot[0],co_mean,co_sigma,21,1.,kMagenta);
    }

    TCanvas *c = new TCanvas("c", "c",600,500);
    c->cd();
    TPad* pad_plot = new TPad("pad_plot","pad_plot",0.,0.,1.,5./6.);
    pad_plot->Draw();
    pad_plot->cd();
    
    TBox* region[4];
    for(int ibox=0; ibox<4; ibox++){
        region[ibox]=new TBox(0.1,0.2*(ibox+1)-2./3.*0.1,0.9,0.2*(ibox+1)+2./3.*0.1);
        region[ibox]->SetFillColor(18);
        region[ibox]->Draw();
    }

    TLine* line0[4];
    for(int iline=0; iline<4; ++iline){
        line0[iline]=new TLine(0.1,0.2 + 0.2*iline,0.9, 0.2 + 0.2*iline);
        line0[iline]->SetLineStyle(2);
        line0[iline]->Draw();
    }

    pad_plot->Divide(4,4);
    TH2F* h_frame[16];
    for(int irow=0; irow<4; ++irow){
        for(int icolumn=0; icolumn<4; ++icolumn){
            pad_plot->cd(irow*4 + icolumn +1);
            float x_min, x_max, y_min, y_max;

            if(icolumn == 0){
                x_min = 0.05;
                x_max = 0.38;
            }
            else if(icolumn == 2){
                x_min = 0.5;
                x_max = 0.78;
            }
            else{
                x_min = 0.1 + 0.4*0.6875 + ((icolumn-1)%4)*0.2;
                x_max = 0.5 + ((icolumn-1)%4)*0.2;
            }

            if(irow!=3){
                y_min = 0.7 - 0.2*irow;
                y_max = 0.9 - 0.2*irow;
            }
            else{
                y_min = 0.05;
                y_max = 0.3;
            }

            gPad->SetPad(x_min, y_min, x_max, y_max);
            gPad->SetFillStyle(4000);
            gPad->SetFrameFillStyle(0);
            gPad->SetTopMargin(0.);
            if(irow!=3) gPad->SetBottomMargin(0.);
            if(irow==3) gPad->SetBottomMargin(0.2);
            if(icolumn!=0) gPad->SetLeftMargin(0.);
            if(icolumn==0) gPad->SetLeftMargin(0.151515);
            gPad->SetRightMargin(0.);

            if(icolumn%2==0){
                h_frame[irow*4 + icolumn]=(TH2F*)gPad->DrawFrame(0.501,-0.299,3.25,0.299);
                h_frame[irow*4 + icolumn]->SetFillStyle(3001);
                gPad->SetFillStyle(4000);
                gPad->Update();
                h_frame[irow*4 + icolumn]->GetYaxis()->SetLabelSize(0.15);
                h_frame[irow*4 + icolumn]->GetYaxis()->SetNdivisions(505);
                if(irow==3) h_frame[irow*4 + icolumn]->GetYaxis()->SetLabelSize(0.12);
                h_frame[irow*4 + icolumn]->GetXaxis()->SetLabelSize(0.12);

                gr_nh_spn[(irow*4 + icolumn)/2]->Draw("SAME P");
                TGraphErrors* gr_nh_spn_copy = (TGraphErrors*)gr_nh_spn[(irow*4 + icolumn)/2]->Clone();
                gr_nh_spn_copy->SetMarkerSize(0.6);
                gr_nh_spn_copy->SetMarkerColor(kWhite);
                gr_nh_spn_copy->Draw("SAME P");
                
                gr_nh_ibd[(irow*4 + icolumn -1)/2]->Draw("SAME P");
                
                gr_alpha_c_prompt[(irow*4 + icolumn)/2]->Draw("SAME P");
                TGraphErrors* gr_alpha_c_prompt_copy = (TGraphErrors*)gr_alpha_c_prompt[(irow*4 + icolumn)/2]->Clone(); //just ot have nice error bars
                gr_alpha_c_prompt_copy->SetMarkerSize(0.6);
                gr_alpha_c_prompt_copy->Draw("SAME P");
                gr_alpha_c_delayed[(irow*4 + icolumn)/2]->Draw("SAME P");
                gr_alpha_d[(irow*4 + icolumn)/2]->Draw("SAME P");
                gr_alpha_e[(irow*4 + icolumn)/2]->Draw("SAME P");
                
                gr_k[(irow*4 + icolumn)/2]->Draw("SAME P");
                TGraphErrors* gr_k_copy = (TGraphErrors*)gr_k[(irow*4 + icolumn)/2]->Clone();
                gr_k_copy->SetMarkerSize(0.6);
                gr_k_copy->SetMarkerColor(kWhite);
                gr_k_copy->Draw("SAME P");
                gr_tl[(irow*4 + icolumn)/2]->Draw("SAME P");
                TGraphErrors* gr_tl_copy = (TGraphErrors*)gr_tl[(irow*4 + icolumn)/2]->Clone();
                gr_tl_copy->SetMarkerSize(0.6);
                gr_tl_copy->SetMarkerColor(kWhite);
                gr_tl_copy->Draw("SAME P");
                
                gr_co[(irow*4 + icolumn)/2]->Draw("SAME P");
            }
            else{
                h_frame[irow*4 + icolumn]=(TH2F*)gPad->DrawFrame(7.25, -0.299, 8.499, 0.299);
                h_frame[irow*4 + icolumn]->GetXaxis()->SetLabelSize(0.153);
                h_frame[irow*4 + icolumn]->GetXaxis()->SetLabelOffset(-0.025);
                h_frame[irow*4 + icolumn]->GetXaxis()->SetNdivisions(503);
                //cout<<(irow*4 + icolumn -1)/2<<endl;

                gr_ngd_spn[(irow*4 + icolumn -1)/2]->Draw("SAME P");
                TGraphErrors* gr_ngd_spn_copy = (TGraphErrors*)gr_ngd_spn[(irow*4 + icolumn -1)/2]->Clone();
                gr_ngd_spn_copy->SetMarkerSize(0.6);
                gr_ngd_spn_copy->SetMarkerColor(kWhite);
                gr_ngd_spn_copy->Draw("SAME P");
                gr_ngd_ibd[(irow*4 + icolumn -1)/2]->Draw("SAME P");
            }
            h_frame[irow*4 + icolumn]->GetXaxis()->SetTickLength(0.08);
        }
    }

    pad_plot->cd();
    TPad* p_cover = new TPad("p_cover","p_cover",0.37,0.,0.3808,1.);
    p_cover->SetBorderMode(0);
    p_cover->SetFillColor(0);
    p_cover->Draw();

    TPad* p_cover2 = new TPad("p_cover","p_cover",0.77,0.,0.7808,1.);
    p_cover2->SetBorderMode(0);
    p_cover2->SetFillColor(0);
    p_cover2->Draw();

    float scl=1;
    TLine* line1[5];
    TLine* line2[5];
    TLine* line3[5];
    TLine* line4[5];

    for(int iline=0; iline<5; ++iline){
        line1[iline]=new TLine(0.37 - 0.005*scl,0.1 + 0.2*iline - 0.02*scl ,0.37+0.005*scl, 0.1 + 0.2*iline + 0.02*scl);
        line1[iline]->Draw();
        line2[iline]=new TLine(0.3808 - 0.005*scl,0.1 + 0.2*iline - 0.02*scl ,0.3808+0.005*scl, 0.1 + 0.2*iline + 0.02*scl);
        line2[iline]->Draw();

        line3[iline]=new TLine(0.77 - 0.005*scl,0.1 + 0.2*iline - 0.02*scl ,0.77+0.005*scl, 0.1 + 0.2*iline + 0.02*scl);
        line3[iline]->Draw();
        line4[iline]=new TLine(0.7808 - 0.005*scl,0.1 + 0.2*iline - 0.02*scl ,0.7808+0.005*scl, 0.1 + 0.2*iline + 0.02*scl);
        line4[iline]->Draw();
    }

    TText *label_x = new TText(0.5,0.05,"Reconstructed Energy (MeV)");
    label_x->SetTextAlign(22);
    label_x->SetTextSize(0.05);
    label_x->SetTextFont(42);
    label_x->Draw();
    TLatex *label_y = new TLatex(0.03,0.5,"(E_{AD} - #LTE_{AD}#GT)/#LTE_{AD}#GT (%)");
    label_y->SetTextAngle(90);
    label_y->SetTextAlign(22);
    label_y->SetTextSize(0.05);
    label_y->SetTextFont(42);
    label_y->Draw();
    
    c->cd();
    TPad* pad_legend = new TPad("pad_legend","pad_legend",0.,0.8,1.,0.95);
    pad_legend->SetBottomMargin(0.);
    pad_legend->Draw();
    
    pad_legend->cd();
    TLegend* leg=new TLegend(0.1,0.0,0.90,1.0);
    leg->SetColumnSeparation(0.0);
    leg->SetMargin(0.1);
    leg->AddEntry(gr_alpha_c_prompt[0],"Alpha from natural radioactivity","P");
    TGraphErrors* gr_k_for_leg = gr_k[0]->Clone();
    gr_k_for_leg->SetMarkerStyle(27);
    leg->AddEntry(gr_k_for_leg,"Gamma from natural radioactivity","P");
    TGraphErrors* gr_nh_spn_for_legend = gr_nh_spn[0]->Clone();
    gr_nh_spn_for_legend->SetMarkerStyle(24);
    leg->AddEntry(gr_nh_spn_for_legend,"Neutron from muon spallation","P");
    leg->AddEntry(gr_nh_ibd[0],"Neutron from IBD","P");
    leg->AddEntry(gr_co[0],"Gamma from calibration source","P");
    leg->SetNColumns(2);
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->Draw();

    if(isAdSimple) c->Print("./rel_en_adsimple.pdf");
    else c->Print("./rel_en_adsimple_nl.pdf");
}


