# gamma-gamma to qqbar
# Pb photon flux

import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8PhotonFluxSettings_cfi import PhotonFlux_PbPb

generator = cms.EDFilter("Pythia8ConcurrentGeneratorFilter",
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(5362.),
    PhotonFlux = PhotonFlux_PbPb,
    PythiaParameters = cms.PSet(
        pythia8CommonSettingsBlock,
        processParameters = cms.vstring(
            # set up the beams
            'PDF:beamA2gamma = on', 
            'PDF:beamB2gamma = on', 
            'PDF:proton2gammaSet = 0',
            'PDF:gammaFluxApprox2bMin = 13.272',
            'PDF:beam2gammaApprox = 2',
            'Photon:sampleQ2 = off',
            # set up the interactions
            'Photon:ProcessType = 1',
            'HardQCD:all = on',
            'PhaseSpace:pTHatMin = 10.',
            'PhotonParton:all = on',
            'PhotonCollision:gmgm2qqbar = on',
            'PhotonCollision:gmgm2ccbar = on',
            'PhotonCollision:gmgm2bbbar = on',
            'MultipartonInteractions:pT0Ref = 3.0',
        ),
        parameterSets = cms.vstring('pythia8CommonSettings',
                                    'processParameters')
    )
)