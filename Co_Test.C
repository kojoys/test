#include "TFile.h" 
#include "TTree.h" 
#include "TCanvas.h" 
#include "TH1D.h" 
#include "TH2D.h" 
#include "TF1.h"

void Co_Test()
{
  TFile* file = new TFile("Co60_Coin_1Vpp_0001.root","read");/////////사용할 root파일을 file이란 이름으로 불러온다.
  TTree* tree = (TTree*)file -> Get("tree");/////////가져온 루트파일에서(현재 file이라 불러온것)에서 tree라는 구조를 가져온다. 
  /////////////////////////////////////////////////////////////////	
  const int Mbin = 240;	
  int waveform_length;
  int waveform[Mbin];
  int waveformtime[Mbin];
  ULong64_t event_number;

  tree -> SetBranchAddress("event_number",&event_number);///////불러온 tree라는 구조에서 우리가 원하는 정보를 가진 brench를 불러온다.
  tree -> SetBranchAddress("waveform_length",&waveform_length);///////불러온 tree라는 구조에서 우리가 원하는 정보를 가진 brench를 불러온다.
  tree -> SetBranchAddress("waveform",waveform);///////불러온 tree라는 구조에서 우리가 원하는 정보를 가진 brench를 불러온다.
  tree -> SetBranchAddress("waveformtime",waveformtime);///////불러온 tree라는 구조에서 우리가 원하는 정보를 가진 brench를 불러온다.

  ULong64_t Mevent = tree -> GetMaximum("event_number");
  ULong64_t events = tree -> GetEntries();


  ///////////////////////////////////////////////////////////////

  //TH1D* event = new TH1D("event","Events vs count",Mevent,0,Mevent);

  TH2D* waveformF[4];  
  TH1D* waveformS[4];  
  TH1D* wavetimeS[4];  
  for(int i = 0 ; i < 4 ;i++)
  {
	waveformF[i] = new TH2D(Form("waveformF%i",i),Form("waveform ampliltude VS time 10^%i using Fill",i+1),Mbin,0,Mbin*2,4096,0,4096);
	waveformS[i] = new TH1D(Form("waveformS%i",i),Form("waveform amplitude VS sampling numb from event 10^%i using SetBin",i+1),240,0,240);
	wavetimeS[i] = new TH1D(Form("wavetimeS%i",i),Form("time VS sampling numb from event 10^%i using SetBin",i+1),240,0,240);
  }

  TCanvas* can[3];
  for(int j = 0 ; j < 3 ; j++ )
  {
	can[j] = new TCanvas(Form("can%i",j),"",1000,1000);
	can[j] -> Divide(2,2);
  }
  //TCanvas* pan = new TCanvas("pan","",1000,1000);
  ///////////////////////////////////////////////////////////////////////

  for(Long64_t iEntry = 0 ; iEntry < events ; iEntry++)
  {
	tree -> GetEntry(iEntry);
	//event -> Fill(event_number);

	for(int n = 1; n < 5 ; n++)
	{
	  if(iEntry == TMath::Power(10,n))
	  {
		for(int bin = 0 ; bin < waveform_length ; bin++)////여기서 wavrform_length의 최대값 즉, 240 이라는건 500(480)ns의 게이트 안에서 2ns마다 샘플링을 한 지점 수를 의미한다.
		{	
		  waveformS[n-1] -> SetBinContent(bin,waveform[bin]);////////////240개의 지점(x축)마다 1~4096(12bit) 사이의 값(해당 샘플링 지점에서 읽은 아날로그신호의 크기를 양자화 시킨 결과)(y축)을 저장시킨다.
		  wavetimeS[n-1] -> SetBinContent(bin,waveformtime[bin]);////////////240개의 지점(x축)을 2ns(y축)마다 찍는다. (그래프의 y 축은 실제시간을 의미 -> 1차 그래프형태임을 볼 수 있다.)
		  
		  waveformF[n-1] -> Fill(waveformtime[bin],waveform[bin]);//////////240번의 샘플링에 의한 시간(x축) 그때마다의 읽은 값(y축)을 2차원으로 해당 지점에 포인트를 찍는다.
		}	
	  }
	}
  }
  /////////////////////////////////////////////////////////////// 
  //pan -> cd();
  //event-> Draw();

  for(int i = 0 ; i < 4 ; i++) 
  {
	can[0] -> cd(i+1);
	waveformF[i]-> Draw();

	can[1] -> cd(i+1);
	waveformS[i]-> Draw();

	can[2] -> cd(i+1);
	wavetimeS[i]-> Draw();
  }
}	
