void analysis_alphaC_ch()
{



    Short_t adc,det,dch;

    auto file = new TFile("data/RUN511.ch.root","read");
    auto tree = (TTree*) file -> Get("channels");


    TCanvas *c1 = new TCanvas(); // 32행 3열 캔버스 만들기
    

    
    tree -> SetBranchAddress("adc",&adc);
    tree -> SetBranchAddress("det",&det); // 디텍터는 3개다.
    tree -> SetBranchAddress("dch",&dch); // 채널이다. 채널의 개수


    int entry = tree -> GetEntries();

    

    for(int k = 1; k < 33; k++){
    
        TH1D *hist_adc = new TH1D(Form("hist%i_%i",4,k),Form("Histo%i_%i",4,k),50,1450,1600); // 여기 있는 2는 detetor의 번호를 의미. 3,4로 바꿔서 돌려라.

        auto tree = (TTree*) file -> Get("channels");


        tree -> SetBranchAddress("adc",&adc);
        tree -> SetBranchAddress("det",&det); // 디텍터는 3개다.
        tree -> SetBranchAddress("dch",&dch); 

        int entry = tree -> GetEntries();

        for(int i = 0; i < entry ; i++){
                tree -> GetEntry(i);
                if(det ==4 && dch == k){    
                            
                    hist_adc -> Fill(adc);
                }
                

                    }

                auto fit1 = new TF1("fit1","gaus(0)",1450,1600);
                hist_adc -> Fit(fit1);

                hist_adc->Draw();         
                c1->SaveAs(Form("picture4_%i.png",k));


                    }
}            
