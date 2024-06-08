#include "DetectorConstruction.hh"
#include "G4SimpleRunge.hh"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // Material definition 
  G4NistManager *nistManager = G4NistManager::Instance(); 
  
  // Kapton defined using NIST Manager
  G4Material* Membrane  = nistManager->FindOrBuildMaterial("G4_KAPTON");
  
  // Air defined using NIST Manager
  G4Material* air = nistManager->FindOrBuildMaterial("G4_Galactic");

  // IonChamber defined using NIST Manager
  G4Material* IonChamber = nistManager->FindOrBuildMaterial("G4_AIR");

  // Electrode defined using NIST Manager
  G4Material* Electrode  = nistManager->FindOrBuildMaterial("G4_Au");

  G4double worldLength = 2*cm;
  
  // ==== World
  G4Box* worldS
    = new G4Box("worldS",worldLength/2*cm,worldLength/2*cm,worldLength/2*cm);
  G4LogicalVolume* worldLV  
    = new G4LogicalVolume(worldS,air,"World");
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,
                        G4ThreeVector(),
                        worldLV,"World",
                        0, false, 1, true);  
  // ======================================================================================================
  //                                        DETECTOR CONSTRUCTION
  // ======================================================================================================
  G4double EGap = 15.0*mm;     //Electrodes Gap
  G4double TM   = 1.5e-3*mm;   //Thickness Membrane 1.5um
  G4double TE   = 5.0e-5*mm;   //Thickness Electrode 50nm
  G4int    nS   = 32;          //Number of Electrode strips 32
  G4double nSd  = nS*1.0;      //
  G4double SE   = 70.0*mm;     //Sides length of Electrode
  G4double EO   = 6.0/32.0*mm; //Offset of each lateral Anode ideally = 0 
  G4double BiasV= 100*volt;  //Electrode Bias Voltage

  G4Box* Membrane_1S
    = new G4Box("Membrane_1",SE/2, SE/2, TM/2);
  G4LogicalVolume* Membrane_1LV  
    = new G4LogicalVolume(Membrane_1S,Membrane,"Membrane_1");
  G4VPhysicalVolume* Membrane_1PV
        = new G4PVPlacement(0, G4ThreeVector(0,0,-EGap/2-TM-TE-EGap-TE-TM/2),
                            Membrane_1LV,"Membrane_1",
                            worldLV, false, 1, true);
  G4Box* Electrode_1S
    = new G4Box("Electrode_1",SE/2, SE/2, TE/2);
  G4LogicalVolume* Electrode_1LV  
    = new G4LogicalVolume(Electrode_1S,Electrode,"Electrode_1");
  G4VPhysicalVolume* Electrode_1PV
        = new G4PVPlacement(0, G4ThreeVector(0,0,-EGap/2-TM-TE-EGap-TE/2),
                            Electrode_1LV,"Electrode_1",
                            worldLV, false, 1, true);      
  G4Box* IonChamber_1S
    = new G4Box("IonChamber_1",SE/2, SE/nS/2, EGap/2);
  G4LogicalVolume* IonChamber_1LV  
    = new G4LogicalVolume(IonChamber_1S,IonChamber,"IonChamber_1");
  
  G4Box* Electrode_2S
    = new G4Box("Electrode_2",SE/2, SE/nS/2-EO/2, TE/2);
  G4LogicalVolume* Electrode_2LV  
    = new G4LogicalVolume(Electrode_2S,Electrode,"Electrode_2");
  
  G4Box* Membrane_2S
    = new G4Box("Membrane_2",SE/2, SE/2, TM/2);
  G4LogicalVolume* Membrane_2LV  
    = new G4LogicalVolume(Membrane_2S,Membrane,"Membrane_2");
  G4VPhysicalVolume* Membrane_2PV
        = new G4PVPlacement(0, G4ThreeVector(0,0,-EGap/2-TM/2),
                            Membrane_2LV,"Membrane_2",
                            worldLV, false, 1, true);
  G4Box* Membrane_3S
    = new G4Box("Membrane_3",SE/2, SE/2, TM/2);
  G4LogicalVolume* Membrane_3LV  
    = new G4LogicalVolume(Membrane_3S,Membrane,"Membrane_3");
  G4VPhysicalVolume* Membrane_3PV
        = new G4PVPlacement(0, G4ThreeVector(0,0,EGap/2+TM/2),
                            Membrane_3LV,"Membrane_3",
                            worldLV, false, 1, true);
  G4Box* Electrode_3S
    = new G4Box("Electrode_3",SE/nS/2-EO/2, SE/2, TE/2);
  G4LogicalVolume* Electrode_3LV  
    = new G4LogicalVolume(Electrode_3S,Electrode,"Electrode_3");
  
  G4Box* IonChamber_2S
    = new G4Box("IonChamber_2",SE/nS/2, SE/2, EGap/2);
  G4LogicalVolume* IonChamber_2LV  
    = new G4LogicalVolume(IonChamber_2S,IonChamber,"IonChamber_2");
  
  G4Box* Electrode_4S
    = new G4Box("Electrode_4",SE/2, SE/2, TE/2);
  G4LogicalVolume* Electrode_4LV  
    = new G4LogicalVolume(Electrode_4S,Electrode,"Electrode_4");
  G4VPhysicalVolume* Electrode_4PV
        = new G4PVPlacement(0, G4ThreeVector(0,0,EGap/2+TM+TE+EGap+TE/2),
                            Electrode_4LV,"Electrode_4",
                            worldLV, false, 1, true);
  G4Box* Membrane_4S
    = new G4Box("Membrane_4",SE/2, SE/2, TM/2);
  G4LogicalVolume* Membrane_4LV  
    = new G4LogicalVolume(Membrane_4S,Membrane,"Membrane_4");
  G4VPhysicalVolume* Membrane_4PV
        = new G4PVPlacement(0, G4ThreeVector(0,0,EGap/2+TM+TE+EGap+TE+TM/2),
                            Membrane_4LV,"Membrane_4",
                            worldLV, false, 1, true);
  for(G4int i=0; i<nS; i++)
  { 
    G4VPhysicalVolume* IonChamber_1PV
        = new G4PVPlacement(0, G4ThreeVector(0,
                                             SE/2 + SE/nS*(-1.0/2.0 - i),
                                             -EGap/2-TM-TE-EGap/2),
                            IonChamber_1LV,"IonChamber_1",
                            worldLV, false, i + 1, true);
                              
    G4VPhysicalVolume* IonChamber_2PV
        = new G4PVPlacement(0, G4ThreeVector(SE/2 + SE/nS*(-1.0/2.0 - i),
                                             0,
                                             EGap/2+TM+TE+EGap/2),
                            IonChamber_2LV,"IonChamber_2",
                            worldLV, false, i + 1, true);
    
    G4VPhysicalVolume* Electrode_2PV
        = new G4PVPlacement(0, G4ThreeVector(0,
                                             SE/2 + SE/nS*(-1.0/2.0 - i),
                                             -EGap/2-TM-TE/2),
                            Electrode_2LV,"Electrode_2",
                            worldLV, false, i + 1, true);  
    G4VPhysicalVolume* Electrode_3PV
        = new G4PVPlacement(0, G4ThreeVector(SE/2 + SE/nS*(-1.0/2.0 - i),
                                             0,
                                             EGap/2+TM+TE/2),
                            Electrode_3LV,"Electrode_3",
                            worldLV, false, i + 1, true);      

  };
  
  FieldDetector.push_back(IonChamber_1LV);
  EField.push_back(G4ThreeVector(0.0, 0.0,  BiasV/EGap));
  FieldDetector.push_back(IonChamber_2LV);
  EField.push_back(G4ThreeVector(0.0, 0.0, -BiasV/EGap));
  
  LogicDetector.push_back(Electrode_2LV);
  noReplica.push_back(nS);
  LogicDetector.push_back(Electrode_3LV);
  noReplica.push_back(nS);  
  LogicDetector.push_back(IonChamber_1LV);
  noReplica.push_back(nS);
  LogicDetector.push_back(IonChamber_2LV);
  noReplica.push_back(nS);  
  return worldPV; 
}

void DetectorConstruction::ConstructSDandField()
{ 
  //---------------------------------------------------------
  fEMfield_1  = new G4UniformElectricField(EField[0]);
  fEquation_1 = new G4EqMagElectricField(fEMfield_1);
  fMinStep_1  = 0.001*mm ;
  G4int nvar1 = 8;
  fStepper_1  = new G4SimpleRunge(fEquation_1,nvar1);

  auto localFieldMgr_1 = new G4FieldManager(fEMfield_1);
  FieldDetector[0]->SetFieldManager(localFieldMgr_1,true);

  auto fIntgrDriver_1  = new G4MagInt_Driver(fMinStep_1,fStepper_1,fStepper_1->GetNumberOfVariables());
  fChordFinder_1       = new G4ChordFinder(fIntgrDriver_1);
  localFieldMgr_1->SetChordFinder(fChordFinder_1);
  
  //---------------------------------------------------------
  fEMfield_2  = new G4UniformElectricField(EField[1]);
  fEquation_2 = new G4EqMagElectricField(fEMfield_2);
  fMinStep_2  = 0.001*mm;
  G4int nvar2 = 8;
  fStepper_2  = new G4SimpleRunge(fEquation_2,nvar2);

  auto localFieldMgr_2 = new G4FieldManager(fEMfield_2);
  FieldDetector[1]->SetFieldManager(localFieldMgr_2,true);

  auto fIntgrDriver_2  = new G4MagInt_Driver(fMinStep_2,fStepper_2,fStepper_2->GetNumberOfVariables());
  fChordFinder_2       = new G4ChordFinder(fIntgrDriver_2);
  localFieldMgr_2->SetChordFinder(fChordFinder_2);
  /*
  //----------------------------------------------------------
  fEMfield_WORLD  = new G4UniformElectricField(G4ThreeVector(0.0, 0.0, 0.0));
  fEquation_WORLD = new G4EqMagElectricField(fEMfield_WORLD);
  fMinStep_WORLD  = 1.0*mm;
  G4int nvar3     = 8;
  fStepper_WORLD  = new G4SimpleRunge(fEquation_WORLD,nvar3);

  auto fFieldManager      = G4TransportationManager::GetTransportationManager()->GetFieldManager();
  fFieldManager->SetDetectorField(fEMfield_WORLD);

  auto fIntgrDriver_WORLD = new G4MagInt_Driver(fMinStep_WORLD,fStepper_WORLD,fStepper_WORLD->GetNumberOfVariables());
  fChordFinder_WORLD      = new G4ChordFinder(fIntgrDriver_WORLD);
  fFieldManager->SetChordFinder(fChordFinder_WORLD);
  */
  // --------------------------------------------------------
  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  for (G4int i = 0; i < LogicDetector.size(); i++)
  {
    G4LogicalVolume *SD = LogicDetector[i];  
    G4int copyNo        = noReplica[i];
    
    SensitiveDetector *SDetector = new SensitiveDetector(SD->GetName(),copyNo);
    SDName.push_back(SD->GetName());
    
    SD    -> SetSensitiveDetector(SDetector);
    SDMan -> AddNewDetector(SDetector);
  }

}




























