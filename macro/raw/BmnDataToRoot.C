#include "../run/bmnloadlibs.C"
#include "../../bmndata/BmnEnums.h"

//file: full path to raw-file
//nEvents: if 0 then decode all events
//doConvert: convert RAW --> ROOT before decoding or use file converted before

void BmnDataToRoot(TString file, Long_t nEvents = 0, Bool_t doConvert = kTRUE)
{
#if ROOT_VERSION_CODE < ROOT_VERSION(5,99,99)
	gROOT->LoadMacro("$VMCWORKDIR/macro/run/bmnloadlibs.C");
#endif
	bmnloadlibs(); // load BmnRoot libraries
	UInt_t period = 7;
	BmnSetup stp = kSRCSETUP; // use kSRCSETUP for Short-Range Correlation program and kBMNSETUP otherwise
	BmnRawDataDecoder* decoder = new BmnRawDataDecoder(file, nEvents, period);
	decoder->SetBmnSetup(stp);

	Bool_t setup[10]; //array of flags to determine BM@N setup
	//Just put "0" to exclude detector from decoding
	setup[0] = 1; // TRIGGERS
	setup[1] = 0; // MWPC
	setup[2] = 0; // SILICON
	setup[3] = 0; // GEM
	setup[4] = 1; // TOF-400
	setup[5] = 0; // TOF-700
	setup[6] = 0; // DCH
	setup[7] = 0; // ZDC
	setup[8] = 0; // ECAL
	setup[9] = 0; // LAND
	decoder->SetDetectorSetup(setup);

	TString PeriodSetupExt = Form("%d%s.txt", period, ((stp == kBMNSETUP) ? "" : ""));
	
	decoder	->	SetTrigPlaceMap	(TString("Trig_PlaceMap_Run7_SRC.txt"	));
	decoder	->	SetTrigDetMap	(TString("Trig_map_Run7_SRC.txt"	));
	decoder	->	SetTrigINLTQDC1	(TString("TQDC16VS-046F-0C75-TDC.ini"	));	// For TQDC at negative polarity
	decoder	->	SetTrigINLTQDC2	(TString("TQDC16VS-076D-3C3C-TDC.ini"	));	// For TQDC at positive polarity
	decoder	->	SetTrigINLTDC1	(TString("TDC72VHL-076D-16A8.ini"	));	// For TDC72
	decoder	->	SetTrigINLTDC2	(TString("TDC32VL_FFD.dat"		));	// For TDC32
	
	//decoder->SetSiliconMapping("SILICON_map_run7.txt");
	//decoder->SetGemMapping(TString("GEM_map_run") + PeriodSetupExt);
	//decoder->SetCSCMapping(TString("CSC_map_period") + PeriodSetupExt);
	// in case comment out the line decoder->SetTof400Mapping("...")  
	// the maps of TOF400 will be read from DB (only for JINR network)
	//decoder->SetTof700Mapping("TOF700_map_period_7.txt");
	//decoder->SetZDCMapping("ZDC_map_period_5.txt");
	//decoder->SetZDCCalibration("zdc_muon_calibration.txt");
	//decoder->SetECALMapping("ECAL_map_period_7.txt");
	//decoder->SetECALCalibration("");
	//decoder->SetMwpcMapping(TString("MWPC_map_period") + PeriodSetupExt);
	decoder->SetTof400Mapping(TString("TOF400_PlaceMap_RUN") +PeriodSetupExt, TString("TOF400_StripMap_RUN") +PeriodSetupExt);
	decoder->SetLANDMapping("land_mapping_jinr_triplex.txt");
	decoder->SetLANDPedestal("r0030_land_clock.hh");
	decoder->SetLANDTCal("r0030_land_tcal.hh");
	decoder->SetLANDDiffSync("r352_cosmic1.hh");
	decoder->SetLANDVScint("neuland_sync_2.txt");
	decoder->InitMaps();
	if (doConvert) decoder->ConvertRawToRoot(); // Convert raw data in .data format into adc-,tdc-, ..., sync-digits in .root format
	decoder->DecodeDataToDigi(); // Decode data into detector-digits using current mappings.

	delete decoder;
}
