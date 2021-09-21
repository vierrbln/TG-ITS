/****************************************************************************/
/**

Copyright 2007-2021 Robert Renner

This file is part of SW-ITS.

SW-ITS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SW-ITS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SW-ITS.  If not, see <http://www.gnu.org/licenses/>.

Diese Datei ist Teil von SW-ITS.

SW-ITS ist Freie Software: Sie können es unter den Bedingungen
der GNU General Public License, wie von der Free Software Foundation,
Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
veröffentlichten Version, weiter verteilen und/oder modifizieren.

SW-ITS wird in der Hoffnung, dass es nützlich sein wird, aber
OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
Siehe die GNU General Public License für weitere Details.

Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.

/****************************************************************************/
/**
@file main.h
 *
@brief Main header file (all include and defines)
 *
@version 1.0.0.0
 *
@author Robert Renner <A HREF="mailto:4r@sw-its.net">4r@sw-its.net</A>\n

Language: ANSI-C ISO/IEC9899:1990
 *
<b>History:</b>
- <b>06.12.04 R.Renner</b>
- Self test extensions implemented
- <b>02.12.04 R.Renner</b>
- Initial revision

 ******************************************************************************
 *****************************************************************************/

/* INCLUDE FILES ************************************************************/
//#include "nidaq.h"
#include <cvirte.h>
#include <userint.h>
#include <utility.h>
//#include <visa.h>
#include <formatio.h>
#include <ansi_c.h>
#include <gpib.h>
#include "toolbox.h"
#include "phy.h"
#include "Splash.h"
#include "rspsm1.h"
#include "rspsys.h"
#include "rspmb.h"
#include "rscan.h"

/* GLOBAL CONSTANT DEFINITIONS **********************************************/

#define VERSION "1.8.0.4"

//RS defines
#define RS_VENDOR_ID 0x162F
#define RSPRL1_DEVICE_ID 0x1111
#define RSPMA_DEVICE_ID 0x1112
#define RSPSAM_DEVICE_ID 0x1113
#define RSPBAS_DEVICE_ID 0x1114
#define RSPICT_DEVICE_ID 0x1115
#define RSPFG_DEVICE_ID 0x1116
#define RSPAM_DEVICE_ID 0x1117
#define RSPDFT_DEVICE_ID 0x1118
#define RSPHDT_DEVICE_ID 0x1119

//Internal Defines
#define PXI 1
#define CAN 2
#define ASRL 3
#define GPIB 4
#define DAQ 5

#define CARRIAGERETURN  10
#define LINEFEED 13

//defines for device
#define TSPBAS_DESCRIPTION "TS-PBAS"
#define TSPBAS_TYPE "PBAS"
#define TSPBAS_DRIVER "rspbas.dll"
#define TSPBAS_DRIVERPREFIX "rspbas"
#define TSPBAS_DRIVEROPTIONS ""
#define TSPBAS_SFTDLL ""
#define TSPBAS_SFTPREFIX ""

#define TSPDFT_DESCRIPTION "TS-PDFT, Digital Functional Test Module"
#define TSPDFT_TYPE "PDFT"
#define TSPDFT_DRIVER "rspdft.dll"
#define TSPDFT_DRIVERPREFIX "rspdft"
#define TSPDFT_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPDFT_SFTDLL "SFTMPDFT.DLL"
#define TSPDFT_SFTPREFIX "SFTMPDFT"

#define TSPFG_DESCRIPTION "TS-PFG, Arbitrary Function Generator Module"
#define TSPFG_TYPE "PFG"
#define TSPFG_DRIVER "rspfg.dll"
#define TSPFG_DRIVERPREFIX "rspfg"
#define TSPFG_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1, DriverSetup=ie1"
#define TSPFG_SFTDLL "SFTMPFG.DLL"
#define TSPFG_SFTPREFIX "SFTMPFG"

#define TSPMA_DESCRIPTION "TS-PMA, Matrix Module"
#define TSPMA_TYPE "PMA"
#define TSPMA_DRIVER "rspma.dll"
#define TSPMA_DRIVERPREFIX "rspma"
#define TSPMA_DRIVEROPTIONS "Simulate=0,RangeCheck=1,DriverSetup=MCR:3FFFFFF6 CRAuto:1 BusSel:0"
#define TSPMA_SFTDLL ""
#define TSPMA_SFTPREFIX ""

#define TSPMB_DESCRIPTION "TS-PMB, Matrix Module"
#define TSPMB_TYPE "PMB"
#define TSPMB_DRIVER "rspmb.dll"
#define TSPMB_DRIVERPREFIX "rspmb"
#define TSPMB_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPMB_SFTDLL "SFTMPMB.DLL"
#define TSPMB_SFTPREFIX "SFTMPMB"

#define TSPSM1_DESCRIPTION "TS-PSM1, Power Switch Module"
#define TSPSM1_TYPE "PSM1"
#define TSPSM1_DRIVER "rspsm1.dll"
#define TSPSM1_DRIVERPREFIX "rspsm1"
#define TSPSM1_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPSM1_SFTDLL "SFTMPSM1.DLL"
#define TSPSM1_SFTPREFIX "SFTMPSM1"

#define TSPSYS_DESCRIPTION "TS-PSYS1, System Module"
#define TSPSYS_TYPE "PSYS1"
#define TSPSYS_DRIVER "rspsys.dll"
#define TSPSYS_DRIVERPREFIX "rspsys"
#define TSPSYS_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPSYS_SFTDLL "SFTMPSYS.DLL"
#define TSPSYS_SFTPREFIX "SFTMPSYS"

#define TSPSAM_DESCRIPTION "TS-PSAM, Source and Measurement Module"
#define TSPSAM_TYPE "PSAM"
#define TSPSAM_DRIVER "rspsam.dll"
#define TSPSAM_DRIVERPREFIX "rspsam"
#define TSPSAM_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPSAM_SFTDLL "SFTMPSAM.DLL"
#define TSPSAM_SFTPREFIX "SFTMPSAM"

#define TSPAM_DESCRIPTION "TS-PAM, Signal Analyzer Module"
#define TSPAM_TYPE "PAM"
#define TSPAM_DRIVER "rspam.dll"
#define TSPAM_DRIVERPREFIX "rspam"
#define TSPAM_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPAM_SFTDLL "SFTMPAM.DLL"
#define TSPAM_SFTPREFIX "SFTMPAM"

#define TSPICT_DESCRIPTION "TS-PICT, In-Circuit Test Extension Module"
#define TSPICT_TYPE "PICT"
#define TSPICT_DRIVER "rspict.dll"
#define TSPICT_DRIVERPREFIX "rspict"
#define TSPICT_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPICT_SFTDLL "SFTMPICT.DLL"
#define TSPICT_SFTPREFIX "SFTMPICT"

#define TSPHDT_DESCRIPTION "TS-PHDT, High-Speed Digitaltest-Modul"
#define TSPHDT_TYPE "PHDT"
#define TSPHDT_DRIVER "rsphdt.dll"
#define TSPHDT_DRIVERPREFIX "rsphdt"
#define TSPHDT_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPHDT_SFTDLL "SFTMPHDT.DLL"
#define TSPHDT_SFTPREFIX "SFTMPHDT"

#define TSPSM2_DESCRIPTION "TS-PSM2, Multiplex/Schalt-Modul 2"
#define TSPSM2_TYPE "PSM2"
#define TSPSM2_DRIVER "rspsm2.dll"
#define TSPSM2_DRIVERPREFIX "rspsm2"
#define TSPSM2_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPSM2_SFTDLL "SFTMPSM2.DLL"
#define TSPSM2_SFTPREFIX "SFTMPSM2"

#define TSPIO2_DESCRIPTION "TS-PIO2, Analog/Digital-IO-Modul 2"
#define TSPIO2_TYPE "PIO2"
#define TSPIO2_DRIVER "rspio2.dll"
#define TSPIO2_DRIVERPREFIX "rspio2"
#define TSPIO2_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPIO2_SFTDLL "SFTMPIO2.DLL"
#define TSPIO2_SFTPREFIX "SFTMPIO2"

#define TSPSU_DESCRIPTION "TS-PSU, Stromversorgungs-/Last-Modul"
#define TSPSU_TYPE "PSU"
#define TSPSU_DRIVER "rspsu.dll"
#define TSPSU_DRIVERPREFIX "rspsu"
#define TSPSU_DRIVEROPTIONS "Simulate=0,RangeCheck=1,QueryInstrStatus=1,Cache=1"
#define TSPSU_SFTDLL "SFTMPSU.DLL"
#define TSPSU_SFTPREFIX "SFTMPSU"








/** @class ressource main.h "main.h"
 *  @brief Container of all resource information which are used in physical.ini
 */
typedef struct ressource
{
   int iInternalType;
   int iID;
   int menuID;
   int iMarkedForExport;
   char cBenchName[300];
   char cDescription[300];
   char cType[300];
   char cRessourceDesc[300];
   int iSlot;
   int iFrame;
   char cDriverDLL[300];
   char cDriverPrefix[300];
   char cDriverOption[300];
   char cSFTDll[300];
   char cSFTPrefix[300];
   int iBaudrate;
   char cParity[300];
   char cHandshake[300];
   int iDataBits;
   int iStopBits;
   struct ressource* next;
} ressource;

/** @class ressource main.h "main.h"
 *  @brief structure for recognizing devices with same type
 */
typedef struct deviceQuantity
{
   int PMAquantity;
   int PSAMquantity;
   int PICTquantity;
   int PFGquantity;
   int PDFTquantity;
   int PAMquantity;
   int PHDTquantity;
   int PSUquantity;
   int PIO2quantity;
   int PMBquantity;
} deviceQuantity;

deviceQuantity TypeQuantity;

/* GLOBAL VARIABLE DEFINITIONS **********************************************/
//Handles
int iMainPanelHandle; //Panel Handles
int iEditPanelHandle;
int iPhysExportPanelHandle;
int iScanPanelHandle;
int iSADPanelHandle;
int iMenuHandle;
int gSplash;
int iDevicesFound; //Count of found devices
int iShouldClose; //Flag to handle child panels
int iMadeChanges; //Is every thing changed this value is true
int iShouldQuitProgramm;
int iWantPhyIni;
int iWantAppIni;
int iWantTstSeq;
int iPSAMCheckWarning; // for message if there is no dmm checked in the list box
int iPMBCheckWarning;
int iPSAMcheckedOnList; // status in the ListBox
int iPMBcheckedOnList;
char cOriginalDeviceType[128];
int iSub1ID;
int iNewDevAdded;

short sDemoMode;


char cProjectDir[MAX_PATHNAME_LEN];
char cPhysicalIniPath[MAX_PATHNAME_LEN];
char cApplicationIniPath[MAX_PATHNAME_LEN];
char cTeststandSeqPath[MAX_PATHNAME_LEN];
char cLastFilePath[1000];
char cMsgText[512];

double ScanBar;
ressource* pFirstRessource;
ressource* pEditRessource;

ViStatus iError;
ViSession SessionDefRM;

int GpibSAD;
int GpibTimeOut;
int GpibEosEnable;
int GpibEosSign;

/* LOCAL TYPE DEFINITIONS ***************************************************/

/* LOCAL CONSTANT DEFINITIONS ***********************************************/

/* LOCAL VARIABLE DEFINITIONS ***********************************************/

/* LOCAL MACRO DEFINITIONS **************************************************/

/* LOCAL FUNCTION DECLARATIONS **********************************************/

/* LOCAL FUNCTION DEFINITIONS ***********************************************/

/* GLOBAL FUNCTION DECLARATIONS *********************************************/
//edit.c
ressource* FindID(int);
int SetValue(ressource*);
int ApplyValues(ressource*);
void ApplyDefaultValuesRS(void);
int DeleteDev(ressource*);

//menu.c
void CVICALLBACK EditRessource(int menuBar, int menuItem, void* callbackData, int panel);
void AddNewDev(int);


//scan.c
void SearchForDevices(void);
int FindPXIDevices(int*);
int FindCANDevices(int*);
int FindASRDevices(int*);
int FindGPIBDevices(int*);
int FindDAQDevices(int*);

//util.c
ressource* pAppendDevice(ressource* , int, char* , char* , int, int, int);
void HandleError(char* , ViStatus);
int CheckVendor(int, char*);
int CheckNIBoards(int, char*);
char* AppendSignsAndCR(char* , char*);
void InsertMenuItems(void);
FILE* MergeTextFile(FILE* , char*);
FILE* MergeEncodedTextFile(FILE* , char*); // NEW!!!
int CheckBenchNames(void);
int GetSlotNumber(char*);

//write.c
void StartExportPhysicalIni(void);
int WritePhysicalIni(int);
int WriteApplicationIni(void);
int WriteTeststandSeq(void);
FILE* WriteBench(FILE* , char* , int);
void WriteSystemChannels(char* , int);
void DoubleBackslash(char* , char*);


/* GLOBAL FUNCTION DEFINITIONS **********************************************/

/******************************************************************************/
// END OF FILE
