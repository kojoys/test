void pedstal_hist2(){
	TFile* file = new TFile("Co60_Coin_1Vpp_0001.root");
	TTree* tree = (TTree*) file->Get("tree");

	ULong64_t event_number;
	Int_t waveform_length=240;
	Int_t Channel;
	Int_t waveform[waveform_length];
	
	tree->SetBranchAddress("event_number", &event_number);
	tree->SetBranchAddress("Channel", &Channel);
	tree->SetBranchAddress("waveform", &waveform);

	Long64_t nEnt = tree->GetEntries();
	cout << nEnt << "entries."<<endl;
	Long64_t Max_event_num = tree->GetMaximum("event_number");
	cout << Max_event_num << "events." << endl;
	

	TH1D* hped1 = new TH1D("hped1", "", 250 , 3920, 3969);
	TH1D* hped2 = new TH1D("hped2", "", 250 , 3920, 3969);
	Double_t wave_avr1, wave_avr2 ;

	for (Long64_t ient=0; ient < Max_event_num; ient++){
		wave_avr1=0;
		wave_avr2=0;
		tree->GetEntry(ient);

		if (Channel==0){
			for (Int_t inum =0; inum < 50; inum++) {
			
				wave_avr1 = wave_avr1 + waveform[inum];
				
			}
		
		wave_avr1 = wave_avr1/50;
		hped1->Fill(wave_avr1);
		}
		if(Channel==1) {
		
			for(Int_t inu = 0; inu < 50; inu++) {
				wave_avr2 = wave_avr2 + waveform[inu];
			}
		wave_avr2 = wave_avr2/50;
		hped2->Fill(wave_avr2);
			
		}

		
	}



			
	TCanvas* cvs = new TCanvas("cvs", "", 1000, 800);
	cvs->Divide(1,2);
	cvs->cd(1);
	hped1->Draw();
	cvs->cd(2);
	hped2->Draw();
}
