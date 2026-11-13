# gamma-p diffraction (used as PbPb UPC diffraction approx.)
# gamma from Pb
# pomeron from p (pomeron from Pb currently not available in Pythia)

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
            'PDF:beamA2gamma = on', # have the photon coming from beam A
            'PDF:proton2gammaSet = 0',
            'PDF:pSetB = LHAPDF6:EPPS21nlo_CT18Anlo_Pb208', # add nuclear modifications to beam B
            'PDF:gammaFluxApprox2bMin = 13.272',
            'PDF:beam2gammaApprox = 2',
            'Photon:sampleQ2 = off',
            # set up the interactions
            'HardQCD:all = on',
            'PhaseSpace:pTHatMin = 10.',
            'PhotonParton:all = on',
            'MultipartonInteractions:pT0Ref = 3.0',
            'Photon:ProcessType = 3', # 0: mix, 1: res-res, 2: res-dir, 3: dir-res, 4: dir-dir
            # add diffraction
            'Diffraction:doHard = on',
            'Diffraction:sampleType = 4', # 1: diff+nondiff,wMPI; 2: diff+nondiff,noMPI; 3: diff,wMPI; 4: diff,noMPI
            'Diffraction:hardDiffSide = 1', # 0: mix, 1: diffraction on side A (res), 2: diffraction on side B (res+dir)
            'SigmaDiffractive:PomFlux = 7',
            'PDF:PomSet = 6'
        ),
        parameterSets = cms.vstring('pythia8CommonSettings',
                                    'processParameters')
    )
)