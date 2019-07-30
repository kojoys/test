void filt_QDC() {

	TFile* file = new TFile("Co60_Coin_1Vpp_0001.root");
	TTree* tree = (TTree*) file -> Get("tree");

	ULong64_t event_number;
	Int_t waveform_length = 240;
	Int_t Channel;
	Int_t waveform[waveform_length];
	Int_t waveformtime[waveform_length];
	Int_t flt_len = 50;
	Double_t waveflt[240-flt_len];
	Double_t flt_co[flt_len];
	
	for (Int_t flt_num_co = 0; flt_num_co < flt_len; flt_num_co++){
		
		if (flt_num_co < flt_len/2) {

			flt_co[flt_num_co] = -1.0/flt_len;
		
		}
		
		else {

			flt_co[flt_num_co] = 1.0/flt_len;

		}
	
	}

	tree -> SetBranchAddress("event_number", &event_number);
	tree -> SetBranchAddress("Channel", &Channel);
	tree -> SetBranchAddress("waveform", &waveform);
	tree -> SetBranchAddress("waveformtime", &waveformtime);
	
	Long64_t nEnt = tree -> GetEntries();
	cout << nEnt << "entries."<< endl;

	Long64_t Max_event_num = tree->GetMaximum("event_number");
	cout << Max_event_num << "events." << endl;
	

//	TGraph* g1 = new Tgraph("filt1", "pulse with filter in Ch1; time(ns); ADC");
//	TGraph* g2 = new Tgraph("filt2", "pulse with filter in Ch2; time(ns); ADC");
	TH1D* height[6];

	height[0] = new TH1D("height1", "ADC histogram in Ch0", 1500, 0, 800);
	height[1] = new TH1D("height2", "ADC histogram in Ch0", 1800, 0, 1100);
	height[2] = new TH1D("height3", "ADC histogram in Ch0", 2440, 0, 400);
	height[3] = new TH1D("height4", "ADC histogram in Ch1", 1590, 0, 800);
	height[4] = new TH1D("height5", "ADC histogram in Ch1", 1800, 0, 1100);
	height[5] = new TH1D("height6", "ADC histogram in Ch1", 2440, 0, 400);

	Double_t wave_pedi, wave_pedf;
	Double_t wave_top1;
	Double_t wave_top2;
	Double_t wave_height1;
	Double_t wave_height2;
	Double_t wave_height3;
	
	for (Long64_t ient=0; ient < Max_event_num; ient++){
		
		tree->GetEntry(ient);

		for (Int_t flt_num = 0; flt_num < 240-flt_len; flt_num++){

			waveflt[flt_num] = 0;

			for (Int_t flt_N = flt_num; flt_N <flt_num + flt_len; flt_N++) {
				
				waveflt[flt_num] = waveflt[flt_num] + waveform[flt_N] * flt_co[flt_N - flt_num];
			
			}

		}
		
		if (Channel == 0){

			wave_pedi = 0;
			wave_pedf = 0;
			
			for (Int_t inum = 0; inum < 50; inum++) {
		
				wave_pedi = wave_pedi + waveflt[inum];
				wave_pedf = wave_pedf + waveflt[239-flt_len-inum];

			}
	
			wave_pedi = wave_pedi/50;
			wave_pedf = wave_pedf/50;
			wave_top1 = wave_pedi;
			wave_top2 = wave_pedi;

			for (Int_t jnum = 0; jnum < 240-flt_len; jnum++) {
		
				if(waveflt[jnum] < wave_top1){

					wave_top1 = waveflt[jnum];
	
				}

				if(waveflt[jnum] > wave_top2){
					
					wave_top2 = waveflt[jnum];	

				}


			}

			wave_height1 = wave_pedi - wave_top1;
			wave_height2 = wave_top2 - wave_top1;
			wave_height3 = wave_top2 - wave_pedf;
			
			height[0]->Fill(wave_height1);
			height[1]->Fill(wave_height2);
			height[2]->Fill(wave_height3);
						
		}

		if(Channel==1) {
		
			wave_pedi = 0;
			wave_pedf = 0;
	
			for (Int_t inu = 0; inu < 50; inu++) {
					
				wave_pedi = wave_pedi + waveflt[inu];
				wave_pedf = wave_pedf + waveflt[239-flt_len-inu];
			
			}
			
			wave_pedi = wave_pedi/50;
			wave_pedf = wave_pedf/50;
			wave_top1 = wave_pedi;
			wave_top2 = wave_pedf;

			for (Int_t jnu = 0; jnu < 240-flt_len; jnu++) {

				if(waveflt[jnu] < wave_top1) {
	
					wave_top1 = waveflt[jnu];

				}
	
				if(waveflt[jnu] > wave_top2) {

					wave_top2 = waveflt[jnu];

				}

			}
			
			wave_height1 = wave_pedi - wave_top1;
			wave_height2 = wave_top2 - wave_top1;
			wave_height3 = wave_top2 - wave_pedf;
		
			height[3]->Fill(wave_height1);
			height[4]->Fill(wave_height2);
			height[5]->Fill(wave_height3);
						
		}
	

		
	}
	
//	for (Int_t qwer = 0; qwer < 220; qwer++) { cout << waveflt[qwer] << endl;}
	
	TCanvas* cvs1 = new TCanvas("cvs1", "", 1500, 800);
//	TCanvas* cvs2 = new TCanvas("cvs2", "", 1500, 800);

	cvs1 -> Divide(3,2);
	cvs1 -> cd(1);
	height[0] -> Draw();
	cvs1 -> cd(2);
	height[1] -> Draw();
	cvs1 -> cd(3);
	height[2] ->Draw();
	cvs1 -> cd(4);
	height[3] -> Draw();
	cvs1 -> cd(5);
	height[4] -> Draw();
	cvs1 -> cd(6);
	height[5] -> Draw();


	TFile* fuck = new TFile("height_fit.root","recreate");
	height[0] ->Write();
	height[1] ->Write();
	height[2] ->Write();
	height[3] ->Write();
	height[4] ->Write();
	height[5] ->Write();

	fuck -> Close();


}
