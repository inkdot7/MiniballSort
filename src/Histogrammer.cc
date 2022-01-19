#include "Histogrammer.hh"

Histogrammer::Histogrammer( Reaction *myreact, Settings *myset ){
	
	react = myreact;
	set = myset;
	
}

Histogrammer::~Histogrammer(){}


void Histogrammer::MakeHists() {
	
	std::string hname, htitle;
	std::string dirname;
	
	// Time difference plots
	dirname = "Timing";
	if( !output_file->GetDirectory( dirname.data() ) )
		output_file->mkdir( dirname.data() );
	output_file->cd( dirname.data() );
	
	ebis_td_gamma = new TH1F( "ebis_td_gamma", "Gamma-ray time with respect to EBIS;#Deltat;Counts per 20 #mus", 5e3, 0, 1e8  );
	ebis_td_particle = new TH1F( "ebis_td_particle", "Particle time with respect to EBIS;#Deltat;Counts per 20 #mus", 5e3, 0, 1e8  );
	
	hname = "gamma_particle_td";
	htitle = "Gamma-ray - Particle time difference;#Deltat;Counts";
	gamma_particle_td = new TH1F( hname.data(), htitle.data(),
								 1000, -1.0*set->GetEventWindow()-50, 1.0*set->GetEventWindow()+50 );

	hname = "gamma_gamma_td";
	htitle = "Gamma-ray - Gamma-ray time difference;#Deltat;Counts";
	gamma_gamma_td = new TH1F( hname.data(), htitle.data(),
							  1000, -1.0*set->GetEventWindow()-50, 1.0*set->GetEventWindow()+50 );
	
	hname = "particle_particle_td";
	htitle = "Particle - Particle time difference;#Deltat;Counts";
	particle_particle_td = new TH1F( hname.data(), htitle.data(),
								 1000, -1.0*set->GetEventWindow()-50, 1.0*set->GetEventWindow()+50 );

	// Gamma-ray singles histograms
	dirname = "GammaRaySingles";
	if( !output_file->GetDirectory( dirname.data() ) )
		output_file->mkdir( dirname.data() );
	output_file->cd( dirname.data() );
	
	hname = "gE_singles";
	htitle = "Gamma-ray energy singles;Energy [keV];Counts 0.5 keV";
	gE_singles = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );
	
	hname = "gE_singles_ebis";
	htitle = "Gamma-ray energy singles EBIS on-off;Energy [keV];Counts 0.5 keV";
	gE_singles_ebis = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );
	
	hname = "gE_singles_ebis_on";
	htitle = "Gamma-ray energy singles EBIS on;Energy [keV];Counts 0.5 keV";
	gE_singles_ebis_on = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );
	
	hname = "gE_singles_ebis_off";
	htitle = "Gamma-ray energy singles EBIS off;Energy [keV];Counts 0.5 keV";
	gE_singles_ebis_off = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );
	
	// Gamma-ray coincidence histograms
	dirname = "GammaRayMatrices";
	if( !output_file->GetDirectory( dirname.data() ) )
		output_file->mkdir( dirname.data() );
	output_file->cd( dirname.data() );
	
	hname = "gE_gE";
	htitle = "Gamma-ray coincidence matrix;Energy [keV];Energy [keV];Counts 0.5 keV";
	gE_gE = new TH2F( hname.data(), htitle.data(), GBIN, GMIN, GMAX, GBIN, GMIN, GMAX );
	
	hname = "gE_gE_ebis_on";
	htitle = "Gamma-ray coincidence matrix EBIS on;Energy [keV];Energy [keV];Counts 0.5 keV";
	gE_gE_ebis_on = new TH2F( hname.data(), htitle.data(), GBIN, GMIN, GMAX, GBIN, GMIN, GMAX );
	
	
	// CD singles histograms
	dirname = "ParticleSingles";
	if( !output_file->GetDirectory( dirname.data() ) )
		output_file->mkdir( dirname.data() );
	output_file->cd( dirname.data() );
	
	hname = "pE_theta";
	htitle = "Particle energy singles;Angle [deg];Energy [keV];Counts 0.5 keV";
	pE_theta = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), PBIN, PMIN, PMAX );
	
	hname = "pE_theta_coinc";
	htitle = "Particle energy in coincidence with a gamma ray;Angle [deg];Energy [keV];Counts 0.5 keV";
	pE_theta_coinc = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), PBIN, PMIN, PMAX );
	
	hname = "pE_theta_beam";
	htitle = "Particle energy singles, gated on beam;Angle [deg];Energy [keV];Counts 0.5 keV";
	pE_theta_beam = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), PBIN, PMIN, PMAX );
	
	hname = "pE_theta_target";
	htitle = "Particle energy singles, gated on target;Angle [deg];Energy [keV];Counts 0.5 keV";
	pE_theta_target = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), PBIN, PMIN, PMAX );
	
	// Gamma-particle coincidences
	dirname = "GammaRayParticleCoincidences";
	if( !output_file->GetDirectory( dirname.data() ) )
		output_file->mkdir( dirname.data() );
	output_file->cd( dirname.data() );
	
	hname = "gE_prompt";
	htitle = "Gamma-ray energy in prompt coincide with any particle;Energy [keV];Counts 0.5 keV";
	gE_prompt = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_prompt_1p";
	htitle = "Gamma-ray energy in prompt coincide with just 1 particle;Energy [keV];Counts 0.5 keV";
	gE_prompt_1p = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_prompt_2p";
	htitle = "Gamma-ray energy in prompt coincide with 2 particles;Energy [keV];Counts 0.5 keV";
	gE_prompt_2p = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_random";
	htitle = "Gamma-ray energy in random coincide with any particle;Energy [keV];Counts 0.5 keV";
	gE_random = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_prompt_1p";
	htitle = "Gamma-ray energy in random coincide with just 1 particle;Energy [keV];Counts 0.5 keV";
	gE_random_1p = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_prompt_2p";
	htitle = "Gamma-ray energy in random coincide with 2 particles;Energy [keV];Counts 0.5 keV";
	gE_random_2p = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_ejectile_dc_none";
	htitle = "Gamma-ray energy, gated on the ejectile with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_ejectile_dc_none = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_ejectile_dc_ejectile";
	htitle = "Gamma-ray energy, gated on the ejectile, Doppler corrected for the ejectile with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_ejectile_dc_ejectile = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_ejectile_dc_recoil";
	htitle = "Gamma-ray energy, gated on the ejectile, Doppler corrected for the recoil with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_ejectile_dc_recoil = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_recoil_dc_none";
	htitle = "Gamma-ray energy, gated on the recoil with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_recoil_dc_none = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_recoil_dc_ejectile";
	htitle = "Gamma-ray energy, gated on the recoil, Doppler corrected for the ejectile with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_recoil_dc_ejectile = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_recoil_dc_recoil";
	htitle = "Gamma-ray energy, gated on the recoil, Doppler corrected for the recoil with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_recoil_dc_recoil = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_2p_dc_none";
	htitle = "Gamma-ray energy, in coincidence with ejectile and recoil with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_2p_dc_none = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_2p_dc_ejectile";
	htitle = "Gamma-ray energy, in coincidence with ejectile and recoil, Doppler corrected for the ejectile with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_2p_dc_ejectile = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_2p_dc_recoil";
	htitle = "Gamma-ray energy, in coincidence with ejectile and recoil, Doppler corrected for the recoil with random subtraction;";
	htitle += "Energy [keV];Counts 0.5 keV";
	gE_2p_dc_recoil = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_ejectile_dc_none";
	htitle = "Gamma-ray energy, gated on the ejectile with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_ejectile_dc_none = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_ejectile_dc_ejectile";
	htitle = "Gamma-ray energy, gated on the ejectile, Doppler corrected for the ejectile with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_ejectile_dc_ejectile = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_ejectile_dc_recoil";
	htitle = "Gamma-ray energy, gated on the ejectile, Doppler corrected for the recoil with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_ejectile_dc_recoil = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_recoil_dc_none";
	htitle = "Gamma-ray energy, gated on the recoil with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_recoil_dc_none = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_recoil_dc_ejectile";
	htitle = "Gamma-ray energy, gated on the recoil, Doppler corrected for the ejectile with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_recoil_dc_ejectile = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_recoil_dc_recoil";
	htitle = "Gamma-ray energy, gated on the recoil, Doppler corrected for the recoil with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_recoil_dc_recoil = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_2p_dc_none";
	htitle = "Gamma-ray energy, in coincidence with ejectile and recoil with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_2p_dc_none = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_2p_dc_ejectile";
	htitle = "Gamma-ray energy, in coincidence with ejectile and recoil, Doppler corrected for the ejectile with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_2p_dc_ejectile = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );

	hname = "gE_vs_theta_2p_dc_recoil";
	htitle = "Gamma-ray energy, in coincidence with ejectile and recoil, Doppler corrected for the recoil with random subtraction;";
	htitle += "Theta [deg];Energy [keV];Counts 0.5 keV per strip";
	gE_vs_theta_2p_dc_recoil = new TH2F( hname.data(), htitle.data(), react->GetNumberOfParticleThetas(), react->GetParticleThetas(), GBIN, GMIN, GMAX );


	
	// Beam dump histograms
	dirname = "BeamDump";
	if( !output_file->GetDirectory( dirname.data() ) )
		output_file->mkdir( dirname.data() );
	output_file->cd( dirname.data() );
	
	hname = "bdE_singles";
	htitle = "Beam-dump gamma-ray energy singles;Energy [keV];Counts 0.5 keV";
	bdE_singles = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );
	
	hname = "bd_bd_td";
	htitle = "Beam-dump - Beam-dump time difference;#Deltat;Counts";
	bd_bd_td = new TH1F( hname.data(), htitle.data(),
						1000, -1.0*set->GetEventWindow()-50, 1.0*set->GetEventWindow()+50 );
	
	hname = "bdE_bdE";
	htitle = "Beam-dump gamma-ray coincidence matrix;Energy [keV];Energy [keV];Counts 0.5 keV";
	bdE_bdE = new TH2F( hname.data(), htitle.data(), GBIN, GMIN, GMAX, GBIN, GMIN, GMAX );
	
	bdE_singles_det.resize( set->GetNumberOfBeamDumpDetectors() );
	for( unsigned int i = 0; i < set->GetNumberOfBeamDumpDetectors(); ++i ){
		
		hname = "bdE_singles_det" + std::to_string(i);
		htitle  = "Beam-dump gamma-ray energy singles in detector ";
		htitle += std::to_string(i);
		htitle += ";Energy [keV];Counts 0.5 keV";
		bdE_singles_det[i] = new TH1F( hname.data(), htitle.data(), GBIN, GMIN, GMAX );
		
	}
	
	return;
	
}

// Particle-Gamma coincidences without addback
void Histogrammer::FillParticleGammaHists( GammaRayEvt *g ) {

	// Work out the weight if it's prompt or random
	bool prompt = false;
	bool random = false;
	float weight;
	if( PromptCoincidence( g, react->GetParticleTime() ) ) {
		prompt = true;
		weight = 1.0;
	}
	else if( RandomCoincidence( g, react->GetParticleTime() ) ){
		random = true;
		weight = -1.0 * react->GetParticleGammaFillRatio();
	}
	else return; // outside of either window, quit now
	
	// Plot the prompt and random gamma spectra
	if( prompt ) gE_prompt->Fill( g->GetEnergy() );
	else gE_random->Fill( g->GetEnergy() );
	
	// Same again but explicitly 1 particle events
	if( prompt && ( react->IsEjectileDetected() != react->IsRecoilDetected() ) )
		gE_prompt_1p->Fill( g->GetEnergy() );
	else if( react->IsEjectileDetected() != react->IsRecoilDetected() )
		gE_random_1p->Fill( g->GetEnergy() );

	// Ejectile-gated spectra
	if( react->IsEjectileDetected() ) {
		
		gE_ejectile_dc_none->Fill( g->GetEnergy(), weight );
		gE_ejectile_dc_ejectile->Fill( react->DopplerCorrection( g, true ), weight );
		gE_ejectile_dc_recoil->Fill( react->DopplerCorrection( g, false ), weight );

		gE_vs_theta_ejectile_dc_none->Fill( react->GetEjectile()->GetTheta(), g->GetEnergy(), weight );
		gE_vs_theta_ejectile_dc_ejectile->Fill( react->GetEjectile()->GetTheta(), react->DopplerCorrection( g, true ), weight );
		gE_vs_theta_ejectile_dc_recoil->Fill( react->GetEjectile()->GetTheta(), react->DopplerCorrection( g, false ), weight );

	}

	// Recoil-gated spectra
	if( react->IsRecoilDetected() ) {
		
		gE_recoil_dc_none->Fill( g->GetEnergy(), weight );
		gE_recoil_dc_ejectile->Fill( react->DopplerCorrection( g, true ), weight );
		gE_recoil_dc_recoil->Fill( react->DopplerCorrection( g, false ), weight );

		gE_vs_theta_recoil_dc_none->Fill( react->GetRecoil()->GetTheta(), g->GetEnergy(), weight );
		gE_vs_theta_recoil_dc_ejectile->Fill( react->GetRecoil()->GetTheta(), react->DopplerCorrection( g, true ), weight );
		gE_vs_theta_recoil_dc_recoil->Fill( react->GetRecoil()->GetTheta(), react->DopplerCorrection( g, false ), weight );

	}
	
	// Two particle spectra
	if( react->IsEjectileDetected() && react->IsRecoilDetected() ){
		
		// Prompt and random spectra
		if( prompt ) gE_prompt_2p->Fill( g->GetEnergy() );
		else gE_random_2p->Fill( g->GetEnergy() );

		gE_2p_dc_none->Fill( g->GetEnergy(), weight );
		gE_2p_dc_ejectile->Fill( react->DopplerCorrection( g, true ), weight );
		gE_2p_dc_recoil->Fill( react->DopplerCorrection( g, false ), weight );

		gE_vs_theta_2p_dc_none->Fill( react->GetRecoil()->GetTheta(), g->GetEnergy(), weight );
		gE_vs_theta_2p_dc_ejectile->Fill( react->GetRecoil()->GetTheta(), react->DopplerCorrection( g, true ), weight );
		gE_vs_theta_2p_dc_recoil->Fill( react->GetRecoil()->GetTheta(), react->DopplerCorrection( g, false ), weight );
		
	}
	
	return;

}

// Particle-Gamma coincidences with addback
void Histogrammer::FillParticleGammaHists( GammaRayAddbackEvt *g ) {

	// The addback spectra will basically be copy paste of no addback
	// Therefore this remains an empty function until we're happy

}

unsigned long Histogrammer::FillHists( unsigned long start_fill ) {
	
	/// Main function to fill the histograms
	n_entries = input_tree->GetEntries();
	
	std::cout << " Histogrammer: number of entries in event tree = ";
	std::cout << n_entries << std::endl;
	
	if( start_fill == n_entries ){
		
		std::cout << " Histogrammer: Nothing to do..." << std::endl;
		return n_entries;
		
	}
	else {
		
		std::cout << " Histogrammer: Start filling at event #";
		std::cout << std::to_string( start_fill ) << std::endl;
		
	}
	
	// ------------------------------------------------------------------------ //
	// Main loop over TTree to find events
	// ------------------------------------------------------------------------ //
	for( unsigned int i = start_fill; i < n_entries; ++i ){
		
		// Current event data
		input_tree->GetEntry(i);
		
		
		// ------------------------- //
		// Loop over particle events //
		// ------------------------- //
		for( unsigned int j = 0; j < read_evts->GetParticleMultiplicity(); ++j ){
			
			// Get particle event
			particle_evt = read_evts->GetParticleEvt(j);
			
			// EBIS time
			ebis_td_particle->Fill( (double)particle_evt->GetTime() - (double)read_evts->GetEBIS() );
			
			// Energy vs Angle plot no gates
			pE_theta->Fill( react->GetParticleTheta( particle_evt ), particle_evt->GetEnergy() );
			
			// Energy vs angle plot, after cuts
			if( EjectileCut( particle_evt ) )
				pE_theta_beam->Fill( react->GetParticleTheta( particle_evt ), particle_evt->GetEnergy() );
			
			if( RecoilCut( particle_evt ) )
				pE_theta_target->Fill( react->GetParticleTheta( particle_evt ), particle_evt->GetEnergy() );
			
			
			// Check for prompt coincidence with a gamma-ray
			for( unsigned int k = 0; k < read_evts->GetGammaRayMultiplicity(); ++k ){
				
				// Get gamma-ray event
				gamma_evt = read_evts->GetGammaRayEvt(k);
				
				// Time differences
				gamma_particle_td->Fill( (double)particle_evt->GetTime() - (double)gamma_evt->GetTime() );
				
				// Check for prompt coincidence
				if( PromptCoincidence( gamma_evt, particle_evt ) ){
					
					// Energy vs Angle plot with gamma-ray coincidence
					pE_theta_coinc->Fill( react->GetParticleTheta( particle_evt ), particle_evt->GetEnergy() );
					
				} // if prompt
				
			} // k: gammas
			
			// Check for prompt coincidence with another particle
			bool event_used = false;
			for( unsigned int k = j+1; k < read_evts->GetParticleMultiplicity(); ++k ){
				
				// Get second particle event
				particle_evt2 = read_evts->GetParticleEvt(j);

				// Time differences and fill symmetrically
				particle_particle_td->Fill( (double)particle_evt->GetTime() - (double)particle_evt2->GetTime() );
				particle_particle_td->Fill( (double)particle_evt2->GetTime() - (double)particle_evt->GetTime() );
				
				// Don't try to make more particle events
				// if we already got one?
				if( event_used ) continue;
				
				// Do a two-particle cut and check that they are coincident
				// particle_evt (k) is beam and particle_evt2 (l) is target
				else if( TwoParticleCut( particle_evt, particle_evt2 ) ){
					
					react->IdentifyEjectile( particle_evt );
					react->IdentifyRecoil( particle_evt2 );
					if( particle_evt->GetTime() < particle_evt2->GetTime() )
						react->SetParticleTime( particle_evt->GetTime() );
					else react->SetParticleTime( particle_evt2->GetTime() );
					event_used = true;

				} // 2-particle check
				
				// particle_evt2 (l) is beam and particle_evt (k) is target
				else if( TwoParticleCut( particle_evt2, particle_evt ) ){
					
					react->IdentifyEjectile( particle_evt2 );
					react->IdentifyRecoil( particle_evt );
					if( particle_evt->GetTime() < particle_evt2->GetTime() )
						react->SetParticleTime( particle_evt->GetTime() );
					else react->SetParticleTime( particle_evt2->GetTime() );
					event_used = true;
					
				} // 2-particle check

			} // k: second particle
			
			// If we found a particle and used it, then we need to
			// stop so we don't fill the gamma-spectra more than once
			if( event_used ) continue;

			// Otherwise we can build a one particle event
			else if( EjectileCut( particle_evt ) ) {
				
				react->IdentifyEjectile( particle_evt );
				react->CalculateRecoil();
				react->SetParticleTime( particle_evt->GetTime() );
				
			} // ejectile event

			else if( RecoilCut( particle_evt ) &&
			   PromptCoincidence( gamma_evt, particle_evt ) ) {
				
				react->IdentifyRecoil( particle_evt );
				react->CalculateEjectile();
				react->SetParticleTime( particle_evt->GetTime() );

			} // recoil event

		} // j: particles

		
		
		// ------------------------------------------ //
		// Loop over gamma-ray events without addback //
		// ------------------------------------------ //
		for( unsigned int j = 0; j < read_evts->GetGammaRayMultiplicity(); ++j ){
						
			// Get gamma-ray event
			gamma_evt = read_evts->GetGammaRayEvt(j);
			
			// Singles
			gE_singles->Fill( gamma_evt->GetEnergy() );
			
			// EBIS time
			ebis_td_gamma->Fill( (double)gamma_evt->GetTime() - (double)read_evts->GetEBIS() );
			
			// Check for events in the EBIS on-beam window
			if( OnBeam( gamma_evt ) ){
				
				gE_singles_ebis->Fill( gamma_evt->GetEnergy() );
				gE_singles_ebis_on->Fill( gamma_evt->GetEnergy() );
				
			} // ebis on
			
			else if( OffBeam( gamma_evt ) ){
				
				gE_singles_ebis->Fill( gamma_evt->GetEnergy(), -1.0 * react->GetEBISRatio() );
				gE_singles_ebis_off->Fill( gamma_evt->GetEnergy() );
				
			} // ebis off
			
			// Particle-gamma coincidence spectra
			FillParticleGammaHists( gamma_evt );

			// Loop over other gamma events
			for( unsigned int k = j+1; k < read_evts->GetGammaRayMultiplicity(); ++k ){
				
				// Get gamma-ray event
				gamma_evt2 = read_evts->GetGammaRayEvt(k);
				
				// Time differences - symmetrise
				gamma_gamma_td->Fill( (double)gamma_evt->GetTime() - (double)gamma_evt2->GetTime() );
				gamma_gamma_td->Fill( (double)gamma_evt2->GetTime() - (double)gamma_evt->GetTime() );
				
				// Check for prompt gamma-gamma coincidences
				if( PromptCoincidence( gamma_evt, gamma_evt2 ) ) {
					
					// Fill and symmetrise
					gE_gE->Fill( gamma_evt->GetEnergy(), gamma_evt2->GetEnergy() );
					gE_gE->Fill( gamma_evt2->GetEnergy(), gamma_evt->GetEnergy() );
					
					// Apply EBIS condition
					if( OnBeam( gamma_evt ) && OnBeam( gamma_evt2 ) ) {
						
						// Fill and symmetrise
						gE_gE_ebis_on->Fill( gamma_evt->GetEnergy(), gamma_evt2->GetEnergy() );
						gE_gE_ebis_on->Fill( gamma_evt2->GetEnergy(), gamma_evt->GetEnergy() );
						
					} // On Beam
					
				} // if prompt
				
			} // k: second gamma-ray
			
		} // j: gamma ray
		
		
		
		
		// -------------------------- //
		// Loop over beam dump events //
		// -------------------------- //
		for( unsigned int j = 0; j < read_evts->GetBeamDumpMultiplicity(); ++j ){
			
			// Get beam dump event
			bd_evt = read_evts->GetBeamDumpEvt(j);
			
			// Singles spectra
			bdE_singles->Fill( bd_evt->GetEnergy() );
			bdE_singles_det[bd_evt->GetDetector()]->Fill( bd_evt->GetEnergy() );
			
			// Check for coincidences in case we have multiple beam dump detectors
			for( unsigned int k = j+1; k < read_evts->GetBeamDumpMultiplicity(); ++k ){
				
				// Get second beam dump event
				bd_evt2 = read_evts->GetBeamDumpEvt(k);
				
				// Fill time differences symmetrically
				bd_bd_td->Fill( (double)bd_evt->GetTime() - (double)bd_evt2->GetTime() );
				bd_bd_td->Fill( (double)bd_evt2->GetTime() - (double)bd_evt->GetTime() );
				
				// Check for prompt coincidence
				if( PromptCoincidence( bd_evt, bd_evt2 ) ) {
					
					// Fill energies symmetrically
					bdE_bdE->Fill( bd_evt->GetEnergy(), bd_evt2->GetEnergy() );
					bdE_bdE->Fill( bd_evt2->GetEnergy(), bd_evt->GetEnergy() );
					
				} // if prompt
				
			} // k: second beam dump
			
		} // j: beam dump
		
		
		// Progress bar
		if( i % 10000 == 0 || i+1 == n_entries ) {
			
			std::cout << " " << std::setw(8) << std::setprecision(4);
			std::cout << (float)(i+1)*100.0/(float)n_entries << "%    \r";
			std::cout.flush();
			
		}
		
		
	} // all events
	
	output_file->Write();
	
	return n_entries;
	
}

void Histogrammer::Terminate() {
	
	// Close output file
	output_file->Close();
	
}

void Histogrammer::SetInputFile( std::vector<std::string> input_file_names ) {
	
	/// Overlaaded function for a single file or multiple files
	input_tree = new TChain( "evt_tree" );
	for( unsigned int i = 0; i < input_file_names.size(); i++ ) {
		
		input_tree->Add( input_file_names[i].data() );
		
	}
	input_tree->SetBranchAddress( "MiniballEvts", &read_evts );
	
	return;
	
}

void Histogrammer::SetInputFile( std::string input_file_name ) {
	
	/// Overloaded function for a single file or multiple files
	input_tree = new TChain( "evt_tree" );
	input_tree->Add( input_file_name.data() );
	input_tree->SetBranchAddress( "MiniballEvts", &read_evts );
	
	return;
	
}

void Histogrammer::SetInputTree( TTree *user_tree ){
	
	// Find the tree and set branch addresses
	input_tree = (TChain*)user_tree;
	input_tree->SetBranchAddress( "MiniballEvts", &read_evts );
	
	return;
	
}
