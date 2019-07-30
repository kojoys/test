void homework1()
{
	TFile* file = new TFile("Co60_Coin_1Vpp_0001.root","read");
	TTree* tree = (TTree*) file->Get("tree");

	ULong64_t event_number;
	Int_t waveform_length=240;
	Int_t waveform[waveform_length], waveformtime[waveform_length];

	tree->SetBranchAddress("event_number", &event_number);
	tree->SetBranchAddress("waveform_length", &waveform_length);
	tree->SetBranchAddress("waveform", waveform);
	tree->SetBranchAddress("waveformtime", waveformtime);

	Long64_t nEnt = tree->GetEntries();
	cout << nEnt << " entries." << endl;
	Long64_t Max_event_num = tree->GetMaximum("event_number");
	cout << Max_event_num << " events." << endl;

	TH1D* hist_event = new TH1D("hist_event", "", Max_event_num, 0, Max_event_num);
	TH2D* hist_waveform[4];
	TGraph* graph_waveform[4];

	for (Int_t i = 0; i < 4; i++)
	{
		hist_waveform[i] = new TH2D(Form("hist_waveform_%d", i), "", waveform_length, 0, waveform_length*2, 4096, 0, 4096);
		graph_waveform[i] = new TGraph();
	}
	



	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
		hist_event->Fill(event_number);
		if (event_number == 10)
		{
			for (Int_t inum = 0; inum < waveform_length; inum++)
			{
				hist_waveform[0]->Fill(waveformtime[inum], waveform[inum]);
				graph_waveform[0]->SetPoint(inum, waveformtime[inum], waveform[inum]);
			}
		}
		else if (event_number == 100)
		{
			for (Int_t inum = 0; inum < waveform_length; inum++)
			{
				hist_waveform[1]->Fill(waveformtime[inum], waveform[inum]);
				graph_waveform[1]->SetPoint(inum, waveformtime[inum], waveform[inum]);
			}
		}

		else if (event_number == 1000)
		{
			for (Int_t inum = 0; inum < waveform_length; inum++)
			{
				hist_waveform[2]->Fill(waveformtime[inum], waveform[inum]);
				graph_waveform[2]->SetPoint(inum, waveformtime[inum], waveform[inum]);
			}
		}

		else if (event_number == 10000)
		{
			for (Int_t inum = 0; inum < waveform_length; inum++)
			{
				hist_waveform[3]->Fill(waveformtime[inum], waveform[inum]);
				graph_waveform[3]->SetPoint(inum, waveformtime[inum], waveform[inum]);
			}
		}


	}

	TCanvas* cvs1  = new TCanvas("cvs1", "", 1000, 500);
	hist_event->Draw();

	TCanvas* cvs2 = new TCanvas("cvs2", "", 1000, 800);
	cvs2->Divide(2,2);
	cvs2->cd(1);
	hist_waveform[0]->Draw();
	cvs2->cd(2);
	hist_waveform[1]->Draw();
	cvs2->cd(3);
	hist_waveform[2]->Draw();
	cvs2->cd(4);
	hist_waveform[3]->Draw();

	TCanvas* cvs3 = new TCanvas("cvs3", "", 1000, 800);
	cvs3->Divide(2,2);
	cvs3->cd(1);
	graph_waveform[0]->Draw();
	graph_waveform[0]->SetMarkerStyle(20);
	graph_waveform[0]->SetLineStyle(0);
	cvs3->cd(2);
	graph_waveform[1]->Draw();
	graph_waveform[1]->SetMarkerStyle(20);
	graph_waveform[1]->SetLineStyle(0);
	cvs3->cd(3);
	graph_waveform[2]->Draw();
	graph_waveform[2]->SetMarkerStyle(20);
	graph_waveform[2]->SetLineStyle(0);
	cvs3->cd(4);
	graph_waveform[3]->Draw();
	graph_waveform[3]->SetMarkerStyle(20);
	graph_waveform[3]->SetLineStyle(0);







}
