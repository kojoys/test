void Fitting_height(){
	
	TFile* file = new TFile("height_hist.root");
	TH1D* height1 = (TH1D*) file -> Get("height1");
	TH1D* height2 = (TH1D*) file -> Get("height2");	

	TF1* full = new TF1("full", "gaus(0)+gaus(3)+gaus(6)+expo(9)+[11]*x", 470, 650);

	full->SetParameter(0,800.);
	full->SetParameter(1,490.);
	full->SetParameter(2,10.);
	full->SetParameter(3,1150.);
	full->SetParameter(4,530.);
	full->SetParameter(5,20.);
	full->SetParameter(6,850.);
	full->SetParameter(7,600.);
	full->SetParameter(8,20.);
//	full->SetParameter(9,1.);
//	full->SetParameter(10,2.);
//	full->SetParameter(11,3.);
//	full->SetParameter(12,4.);
//	full->SetParameter(13,5.);
//	full->SetParameter(14,5.);
	full->SetParLimits(1,480,500);
	full->SetParLimits(4,515,530);
	full->SetParLimits(7,590,610);
	height1 -> Fit(full,"M","", 470, 650);


	TF1* h1g1 = new TF1("h1g1", "gaus", 500, 555);
	h1g1->SetParameters(full->GetParameter(3),full->GetParameter(4),full->GetParameter(5));
	TF1* h1g2 = new TF1("h1g2", "gaus", 570, 630);
	h1g2->SetParameters(full->GetParameter(6),full->GetParameter(7),full->GetParameter(8));
	TF1* b1 = new TF1("b1", "gaus(0)+expo(3)+[5]*x", 480, 650);
	b1->SetParameters(full->GetParameter(0),full->GetParameter(1),full->GetParameter(2),full->GetParameter(9),full->GetParameter(10),full->GetParameter(11));//, full->GetParameter(12),full->GetParameter(13));//,full->GetParameter(14));


	TCanvas* cvs2 = new TCanvas("cvs2", "", 2000, 3000);
	height1->Draw("same");
	height1->SetLineColor(1);
	h1g1->Draw("same");
	h1g1->SetLineColor(4);
	h1g2->Draw("same");
	h1g2->SetLineColor(4);
	b1->Draw("same");
	b1->SetLineColor(3);

}
