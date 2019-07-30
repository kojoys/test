void height_edge(){

	TFile* file = new TFile("Co60_Coin_1Vpp_0001.root");
	TTree* tree = (TTree*) file -> Get("tree");

	ULong64_t event_number;
	Int_t waveform_length = 240;
	Int_t Channel;
	Int_t waveform[waveform_length];
	
	tree -> SetBranchAddress("event_number", &event_number);
	tree -> SetBranchAddress("Channel", &Channel);
	tree -> SetBranchAddress("waveform", &waveform);

	Long64_t nEnt = tree -> GetEntries();
	cout << nEnt << "entries."<< endl;

	Long64_t Max_event_num = tree->GetMaximum("event_number");
	cout << Max_event_num << "events." << endl;
	

	TH1D* hped1 = new TH1D("hped1", "pedestal histogram in Ch1; pedestal(ADC); n", 250 , 3920, 3969);
	TH1D* hped2 = new TH1D("hped2", "pedestal histogram in Ch2; pedestal(ADC); n", 250 , 3920, 3969);
	TH1D* height1 = new TH1D("height1", "Rising edge height histogram in Ch1; height(ADC); n", 1200, 0, 2500);
	TH1D* height2 = new TH1D("height2", "Rising edge height histogram in Ch2; height(ADC); n", 1200, 0, 2000);
	TH1D* sum1 = new TH1D("sum1", "QDC histogram in Ch1", 1250, 0, 40000);
	TH1D* sum2 = new TH1D("sum2", "QDC histogram in Ch2", 1250, 0, 40000);

	Double_t wave_avr1, wave_avr2, wave_top1, wave_top2, wave_height1, wave_height2, wave_sum1, wave_sum2;
	
	for (Long64_t ient=0; ient < Max_event_num; ient++){

		wave_avr1 = 0;
		wave_avr2 = 0;
		wave_sum1 = 0;
		wave_sum2 = 0;

		tree->GetEntry(ient);
		
		if (Channel == 0){

			for (Int_t inum = 0; inum < 50; inum++) {
			
				wave_avr1 = wave_avr1 + waveform[inum];

			}
	
			wave_avr1 = wave_avr1/50;
			wave_top1 = wave_avr1;
			
			for (Int_t jnum = 0; jnum < 240; jnum++) {
			
				if(waveform[jnum] < wave_top1){

					wave_top1 = waveform[jnum];

				}
			
			}

			wave_height1 = wave_avr1 - wave_top1;
			
			for (Int_t knum = 0; knum < 240; knum++) {
			
				wave_sum1 = wave_sum1 + wave_avr1 - waveform[knum];
			
			}
			
			hped1->Fill(wave_avr1);
			height1->Fill(wave_height1);
			sum1->Fill(wave_sum1);
		}

		if(Channel==1) {
		
			for (Int_t inu = 0; inu < 50; inu++) {
				
				wave_avr2 = wave_avr2 + waveform[inu];
			
			}
			
			wave_avr2 = wave_avr2/50;
			wave_top2 = wave_avr2;
			
			for (Int_t jnu = 0; jnu < 240; jnu++) {

				if(waveform[jnu] < wave_top2) {

					wave_top2 = waveform[jnu];

				}

			}
			
			wave_height2 = wave_avr2 - wave_top2;
			
			for (Int_t knu = 0; knu < 240; knu++) {
			
				wave_sum2 = wave_sum2 +wave_avr2 - waveform[knu];
			
			}
			
			hped2->Fill(wave_avr2);
			height2->Fill(wave_height2);
			sum2->Fill(wave_sum2);

		}

		
	}

	TCanvas* cvs = new TCanvas("cvs", "", 1500, 800);
	cvs -> Divide(3,2);
	cvs -> cd(1);
	hped1 -> Draw();
	cvs -> cd(4);
	hped2 -> Draw();
	cvs -> cd(2);
	height1 ->Draw();
	cvs -> cd(5);
	height2 -> Draw();
	cvs -> cd(3);
	sum1 -> Draw();
	cvs -> cd(6);
	sum2 -> Draw();

}
