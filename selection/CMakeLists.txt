# use cmake 2.8 or later
cmake_minimum_required (VERSION 3.2)

project(novasoft)

# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
if (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
endif()

set(CMAKE_MODULE_PATH $ENV{CANVAS_DIR}/Modules
                      $ENV{CETBUILDTOOLS_DIR}/Modules
                      ${CMAKE_MODULE_PATH})

include(CetCMakeEnv)
cet_cmake_env()

set_install_root()

cet_set_compiler_flags(DIAGS CAUTIOUS
  #WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -Wno-pedantic -Wno-unused-local-typedefs -Wno-narrowing -Wno-deprecated-declarations -Wno-unused-variable -Wno-missing-braces -Wno-undefined-var-template
  EXTRA_CXX_FLAGS
)

cet_enable_asserts()

# issue 5589: if we are not in a debugging build, disable the dispatch of debug messages in messagefacility
string(TOUPPER ${CMAKE_BUILD_TYPE} BTYPE_UC )
if( ${BTYPE_UC} STREQUAL "OPT" OR
    ${BTYPE_UC} STREQUAL "PROF" OR
    ${BTYPE_UC} STREQUAL "RELEASE" OR
    ${BTYPE_UC} STREQUAL "MINSIZEREL" )
  message ( STATUS "Disabling MF_LOG_DEBUG from messagefacility library" )
  add_definitions(-DML_NDEBUG)
endif()

add_definitions( -DNOVACMAKE )
add_definitions( -D_REENTRANT ) # needed for stan_math v4

cet_report_compiler_flags()

# these are minimum required versions, not the actual product versions
# put products in this list that you want to have set up with
# their environment by ups
find_ups_product( cetbuildtools  v4_07_03    )
find_ups_product( cafanacore     v01.00      )
find_ups_product( castxml        v0_00_00_f1 )
find_ups_product( dk2nudata      v01_06_00 )
find_ups_product( dk2nugenie     v01_06_00 )
find_ups_product( eigen          v3.3.5    )
find_ups_product( gcc            v4_9_3    )
find_ups_product( genie          v2_10_00  )
find_ups_product( gsl            v1_16     )
find_ups_product( libwda         v2_20_1   )
find_ups_product( novadaq        v10_00_00 )
find_ups_product( novarwgt       v00.13    )
find_ups_product( nuevdb         v1_00_00  )
find_ups_product( nutools        v1_21_00  )
find_ups_product( nugen          v1_02_00  )
find_ups_product( nug4           v1_02_00  )
find_ups_product( opencv         v3_4_2    )
find_ups_product( ppfx           v01_09    )
find_ups_product( pygccxml       v1_9_1    )
find_ups_product( osclib         v00.03    )
find_ups_product( protobuf       v3_11_2   )
find_ups_product( stan           v2.18.0   )
find_ups_product( stan_math      v2.18.0   )
find_ups_product( sundials       v5_6_1a   )
find_ups_product( tensorflow     v1_3_0b   )

find_ups_root( root v5_00_00 )

# macros for artdaq_dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

#============== OPTIONS for which packages to build============
# Should probably make BUILDCAFANA and BUILDHDF5MAKER check BUILDCMFONLY first
option(BUILDCAFANA    "Build libraries dependent on CAFAna" off)
option(BUILDHDF5MAKER "Build HDF5 Maker"                    off)
option(BUILDCMFONLY   "Build CovarianceMatrixFit only"      on )
option(BUILDTESTBEAM  "Build TestBeam libraries"            off)
#===============================================================

#============ Check for the existance of NOVADAQ_INC============
if( DEFINED ENV{NOVADAQ_INC} )
  MESSAGE("NOVADAQ_INC is set to $ENV{NOVADAQ_INC}")
else()
  SET(ENV{NOVADAQ_INC} "${CMAKE_BINARY_DIR}/novadaq") 
  MESSAGE("SETTING NOVADAQ_INC to ${CMAKE_BINARY_DIR}/novadaq $ENV{NOVADAQ_INC}")
endif()
#===============================================================

#=============Set some include directors that are needed by many packages
include_directories( $ENV{OPENCV_INC}/opencv4 )
include_directories( $ENV{NOVADAQ_INC} )
include_directories( $ENV{LIBWDA_FQ_DIR}/include )
include_directories( $ENV{GENIE_INC}/GENIE )
include_directories( $ENV{NOVARWGT_INC} )
include_directories( $ENV{OSCLIB_INC} )
include_directories( $ENV{NUGEN_INC} )
#===============================================================

#=============== Find libraries needed by many packages=========
cet_find_library( OSCLIB       NAMES OscLib       PATHS ENV OSCLIB_LIB   NO_DEFAULT_PATH)
cet_find_library( NOVARWGT     NAMES NOvARwgt     PATHS ENV NOVARWGT_LIB NO_DEFAULT_PATH)

cet_find_library( GFWMSG       NAMES GFwMsg       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWREG       NAMES GFwReg       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWALG       NAMES GFwAlg       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWINT       NAMES GFwInt       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWGHEP      NAMES GFwGHEP      PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWNUM       NAMES GFwNum       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWUTL       NAMES GFwUtl       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWPARDAT    NAMES GFwParDat    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWEG        NAMES GFwEG        PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GFWNTP       NAMES GFwNtp       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHXSIG      NAMES GPhXSIg      PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHPDF       NAMES GPhPDF       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHNUCLST    NAMES GPhNuclSt    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHCMN       NAMES GPhCmn       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHDCY       NAMES GPhDcy       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHHADTRANSP NAMES GPhHadTransp PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHHADNZ     NAMES GPhHadnz     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHDEEX      NAMES GPhDeEx      PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHAMNGXS    NAMES GPhAMNGXS    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHAMNGEG    NAMES GPhAMNGEG    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHCHMXS     NAMES GPhChmXS     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHCOHXS     NAMES GPhCohXS     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHCOHEG     NAMES GPhCohEG     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHDISXS     NAMES GPhDISXS     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHDISEG     NAMES GPhDISEG     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHDFRCXS    NAMES GPhDfrcXS    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHDFRCEG    NAMES GPhDfrcEG    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHGLWRESXS  NAMES GPhGlwResXS  PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHGLWRESEG  NAMES GPhGlwResEG  PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHIBDXS     NAMES GPhIBDXS     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHIBDEG     NAMES GPhIBDEG     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHMNUCXS    NAMES GPhMNucXS    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHMNUCEG    NAMES GPhMNucEG    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHMEL       NAMES GPhMEL       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHNUELXS    NAMES GPhNuElXS    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHNUELEG    NAMES GPhNuElEG    PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHQELXS     NAMES GPhQELXS     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHQELEG     NAMES GPhQELEG     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHRESXS     NAMES GPhResXS     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHRESEG     NAMES GPhResEG     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHSTRXS     NAMES GPhStrXS     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHSTREG     NAMES GPhStrEG     PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GPHNDCY      NAMES GPhNDcy      PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GTLGEO       NAMES GTlGeo       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GTLFLX       NAMES GTlFlx       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )

# if GENIE's Reweight gets spun into separate product
# then the following must change for GENIE_LIB to ? GENIERW_LIB
cet_find_library( GRWFWK       NAMES GRwFwk       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GRWIO        NAMES GRwIO        PATHS ENV GENIE_LIB NO_DEFAULT_PATH )
cet_find_library( GRWCLC       NAMES GRwClc       PATHS ENV GENIE_LIB NO_DEFAULT_PATH )

# GENIE pre-R-3 used GSL via ROOT's Math libs, now makes direct call not available via that route
cet_find_library( GSL NAMES gsl PATHS ENV GSL_LIB NO_DEFAULT_PATH )

# this is the order that GENIE "recommends"
# genie-config --libs
#   -lGFwMsg -lGFwReg -lGFwAlg -lGFwInt -lGFwGHEP -lGFwNum -lGFwUtl -lGFwParDat
#   -lGFwEG -lGFwNtp -lGPhXSIg -lGPhPDF -lGPhNuclSt -lGPhCmn -lGPhDcy -lGPhHadTransp
#   -lGPhHadnz -lGPhDeEx -lGPhAMNGXS -lGPhAMNGEG -lGPhChmXS -lGPhCohXS -lGPhCohEG
#   -lGPhDISXS -lGPhDISEG -lGPhDfrcXS -lGPhDfrcEG -lGPhGlwResXS -lGPhGlwResEG
#   -lGPhIBDXS -lGPhIBDEG -lGPhMNucXS -lGPhMNucEG -lGPhMEL -lGPhNuElXS -lGPhNuElEG
#   -lGPhQELXS -lGPhQELEG -lGPhResXS -lGPhResEG -lGPhStrXS
#   -lGPhStrEG -lGPhNDcy -lGTlGeo -lGTlFlx -lGTlRew

set (GENIE_LIB_LIST ${GFWMSG}
        ${GFWREG}
        ${GFWALG}
        ${GFWINT}
        ${GFWGHEP}
        ${GFWNUM}
        ${GSL}  # FWNUM relies on GSL
        ${GFWUTL}
        ${GFWPARDAT}
        ${GFWEG}
        ${GFWNTP}
        ${GPHXSIG}
        ${GPHPDF}
        ${GPHNUCLST}
        ${GPHCMN}
        ${GPHDCY}
        ${GPHHADTRANSP}
        ${GPHHADNZ}
        ${GPHDEEX}
        ${GPHAMNGXS}
        ${GPHAMNGEG}
        ${GPHCHMXS}
        ${GPHCOHXS}
        ${GPHCOHEG}
        ${GPHDISXS}
        ${GPHDISEG}
        ${GPHDFRCXS}
        ${GPHDFRCEG}
        ${GPHGLWRESXS}
        ${GPHGLWRESEG}
        ${GPHIBDXS}
        ${GPHIBDEG}
        ${GPHMNUCXS}
        ${GPHMNUCEG}
        ${GPHMEL}
        ${GPHNUELXS}
        ${GPHNUELEG}
        ${GPHQELXS}
        ${GPHQELEG}
        ${GPHRESXS}
        ${GPHRESEG}
        ${GPHSTRXS}
        ${GPHSTREG}
        ${GPHNDCY}
        ${GTLGEO}
        ${GTLFLX}
        ${GRWFWK}
        ${GRWIO}
        ${GRWCLC}
        )
#===============================================================

#========Source code to build, check options defined above======
IF( ${BUILDCMFONLY} )
  add_subdirectory(CovarianceMatrixFit)
ELSE()
  IF( ${BUILDTESTBEAM} )
    add_subdirectory(CAFMaker)
    add_subdirectory(TestBeam)
    add_subdirectory(TestBeamAna)
    add_subdirectory(TestBeamCommissioning)
    add_subdirectory(TestBeamReco)
    add_subdirectory(TestBeamSim)
    add_subdirectory(TestBeamUtils)
  ENDIF()
  add_subdirectory(Alignment)
  add_subdirectory(BeamlineReco)
  add_subdirectory(BeamlineRecoBase)
  add_subdirectory(BeamlineUtils)
  add_subdirectory(BreakPointFitter)
  add_subdirectory(BremShowerFilter)
  add_subdirectory(CalHit)
  add_subdirectory(Calibration)
  add_subdirectory(CalibrationDataProducts)
  add_subdirectory(CalibrationUtils)
  add_subdirectory(Calibrator)
  add_subdirectory(CelestialLocator)
  add_subdirectory(ChannelInfo)
  add_subdirectory(ClusterMakerSS)
  add_subdirectory(CMap)
  add_subdirectory(Commissioning)
  add_subdirectory(CosmicExposureInfo) 
  add_subdirectory(CosmicRayVertex)
  add_subdirectory(CosmicStudies)
  add_subdirectory(CosRej)
  add_subdirectory(CovarianceMatrixFit)
  add_subdirectory(CVN)
  add_subdirectory(DAQ2RawDigit)
  add_subdirectory(Database)
  add_subdirectory(DataQuality)
  add_subdirectory(Demo)
  add_subdirectory(DetectorPerformance) 
  add_subdirectory(DiFShowerFinder)
  add_subdirectory(DiscreteTracker)
  add_subdirectory(DQSpillFlags)
  add_subdirectory(DSOResultPlotter)
  add_subdirectory(ElasticArms)
  add_subdirectory(EliminateBeamSpills)
  add_subdirectory(EventDisplay)
  add_subdirectory(EventDisplayServices)
  add_subdirectory(EventGenerator)
  add_subdirectory(EventSummary)
  add_subdirectory(Filter)
  add_subdirectory(FlatMaker)
  add_subdirectory(FuzzyKVertex)
  add_subdirectory(g4nova)
  #add_subdirectory(GenieSNova)
  add_subdirectory(Geometry)
  add_subdirectory(GeometryObjects)
  add_subdirectory(HoughTransform)
  add_subdirectory(HoughVertex)
  add_subdirectory(IFDBSpillInfo)
  add_subdirectory(LEM)
  add_subdirectory(MCCheater)
  add_subdirectory(MCCheckOut)
  add_subdirectory(MCReweight)
  add_subdirectory(MEFinder)
  add_subdirectory(Metadata)
  add_subdirectory(MockDataDAQ)
  add_subdirectory(MuonID)
  add_subdirectory(MuonRemove)
  add_subdirectory(NCID)
  add_subdirectory(NDReco)
  add_subdirectory(NDRockMuon)
  add_subdirectory(NeutronMCAna)
  #add_subdirectory(NovaGridUtils)
  #add_subdirectory(novaproduction)
  add_subdirectory(NovaSimMixer)
  #add_subdirectory(NovaT2K)
  add_subdirectory(NueSandbox)
  add_subdirectory(NumuEnergy)
  add_subdirectory(NumuSandbox)
  add_subdirectory(NusSandbox)
  add_subdirectory(OnlineMonitoring)
  #add_subdirectory(PandAna)
  add_subdirectory(PhotonTransport)
  add_subdirectory(Preselection) 
  add_subdirectory(ProductMorgue) 
  add_subdirectory(QEEventFinder) 
  add_subdirectory(RawData)
  add_subdirectory(ReadoutSim)
  add_subdirectory(RecoBase)
  add_subdirectory(RecoBaseHit)
  add_subdirectory(RecoJMShower)
  add_subdirectory(RecVarPID)
  add_subdirectory(ReMId)
  add_subdirectory(RunHistory)
  add_subdirectory(setup)
  add_subdirectory(ShowerE)
  add_subdirectory(ShowerLID)
  add_subdirectory(Simulation)
  add_subdirectory(SliceLID)
  add_subdirectory(Slicer)
  add_subdirectory(StandardRecord)
  add_subdirectory(SummaryData)
  add_subdirectory(Supernova)
  add_subdirectory(SupernovaUtilities)
  add_subdirectory(TBSpillReco)
  add_subdirectory(TDSlicer)
  add_subdirectory(TensorFlowEvaluator)
  add_subdirectory(TensorFlowHandler)
  add_subdirectory(TensorFlowProducts)
  add_subdirectory(TimingFit)
  add_subdirectory(TrackFit)
  add_subdirectory(TrackInfo)
  add_subdirectory(Tridents)
  add_subdirectory(TriggerMonitoring)
  add_subdirectory(Utilities)
  add_subdirectory(Validation)
  add_subdirectory(VertexFinder)
  add_subdirectory(XnuePID)
  add_subdirectory(XSecReco)
  #add_subdirectory(XsecTuningAna) - # no libraries made, only executables

  IF( ${BUILDCAFANA} )
    include_directories( $ENV{CAFANACORE_INC} )

    # add in cet_find_library calls as CAFAna libraries move to a ups product
    cet_find_library( CAFANACOREEXT NAMES CAFAnaCoreExt  PATHS ENV CAFANACORE_LIB NO_DEFAULT_PATH )
  
    # update this list to include anything in the cet_find_library calls above
    set (CAFANA_BASIC_LIB_LIST ${CAFANACOREEXT} )
  
    #MESSAGE(STATUS "CAFANACORE_INC is $ENV{CAFANACORE_INC}")
    #MESSAGE(STATUS "CAFANA_BASIC_LIB_LIST is ${CAFANA_BASIC_LIB_LIST}")
    
    #add_subdirectory(CAFReweight)
    add_subdirectory(3FlavorAna)
    add_subdirectory(CAFAna)
    add_subdirectory(CellHitTimeAna)
    add_subdirectory(LSTME)
    #add_subdirectory(NDAna)
    add_subdirectory(NuXAna)
    add_subdirectory(RecoValidation)
  ELSE()
    MESSAGE(WARNING "CAFAna related code is removed from build")
  ENDIF()

  IF( ${BUILDHDF5MAKER} )
    if( ${BTYPE_UC} STREQUAL "DEBUG" )
      MESSAGE(WARNING "Currently no hep_hpc debug qualified product, do not set it or hdf5 up, HDF5Maker is removed from build" )
    else()
      message ( STATUS "Setting up hdf5 and hep_hpc to build HDF5Maker" )
      find_ups_product( hdf5           v1_10_3a  )
      find_ups_product( hep_hpc        v0_11_00  )
      
      add_subdirectory(HDF5Maker)
    endif()
  ELSE()
    MESSAGE( STATUS "HDF5Maker is removed from build" )
  ENDIF()

ENDIF()
#===============================================================

# DDT related packages
#add_subdirectory(AirShower)
#add_subdirectory(DDTAnalysis)
#add_subdirectory(DDTConverters)
#add_subdirectory(DDTMonopole)
#add_subdirectory(DDTTools)
#add_subdirectory(Eval)
#add_subdirectory(Monopole)
#add_subdirectory(MonopoleMC)

# packages that could be removed
#add_subdirectory(EMShowerAna) #user package, not official
#add_subdirectory(EnergyBB) #old, prob can remove from repo
#add_subdirectory(EWCosmicAnalyzer) #no activity over a year, Dubna code
#add_subdirectory(G4StandAlone) #never use this for anything...just leave be uncompiled?
#add_subdirectory(HoughTrack) #alternative HT, not official
#add_subdirectory(NNbar) #user code, not official
#add_subdirectory(NumuNeutronAna) #user code, not official
#add_subdirectory(QEVertexRegion) #another candidate for removal
#add_subdirectory(RecoInt) - not used anywhere
#add_subdirectory(WrongSignNumu) # believe it's old (can ask #3flavor)

# ups - table and config files
add_subdirectory(ups)

# packaging utility
include(UseCPack)

