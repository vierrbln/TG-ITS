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
@file scan.c
 *
@brief Include function for scanning cTSVP
 *
@version 1.0.0.0
 *
@author Robert Renner <A HREF="mailto:4r@sw-its.net">4r@sw-its.net</A>\n

Language: ANSI-C ISO/IEC9899:1990
 *
<b>History:</b>
- <b>02.12.04 R.Renner</b>
- Initial revision
- <b>07.07.05 R.Renner</b>
- FindPXIDevices -> insert new PAM module
- <b>05.11.08 R.Renner</b>
- Debugging of some functions

 ******************************************************************************
 *****************************************************************************/

/* INCLUDE FILES ************************************************************/
#include "main.h"
#include "rspam.h"
#include "rspfg.h"
#include "rspdft.h"
#include "rspsam.h"
#include "rspict.h"
#include "rsphdt.h"
#include "rspsm2.h"
#include "rspio2.h"
#include "rspsu.h"

/* GLOBAL CONSTANT DEFINITIONS **********************************************/

/* GLOBAL VARIABLE DEFINITIONS **********************************************/

/* LOCAL TYPE DEFINITIONS ***************************************************/

/* LOCAL CONSTANT DEFINITIONS ***********************************************/

/* LOCAL VARIABLE DEFINITIONS ***********************************************/

/* LOCAL MACRO DEFINITIONS **************************************************/

/* LOCAL FUNCTION DECLARATIONS **********************************************/

/* LOCAL FUNCTION DEFINITIONS ***********************************************/

/* GLOBAL FUNCTION DECLARATIONS *********************************************/

/* GLOABL FUNCTION DEFINITIONS **********************************************/

/* FUNCTION *****************************************************************/
/**
SearchForDevices
 *
@brief This function is the main search function and call all sub search
functions
 *
@param void
 *
@return void
 *****************************************************************************/
void SearchForDevices(void)
{
   int GlobalError;
   int iBuffer;
   int iConfirm;
   iDevicesFound = 0;
   GlobalError = 0;
   iSub1ID = 0; // for submenu-creation

   iNewDevAdded = 0; // for devices added manually, see AddPXIDevice in menu.c

   //Warning to update MAX before start scanning
   iConfirm = ConfirmPopup("TG-ITS", "Before you continue, all external devices should be activated.\nFor new DAQ-Devices you must update the NI Measurement &\nAutomation Explorer! Click \"No\" to abort!");
   if (!iConfirm)
   {
      return ;
   }
   InstallPopup(iScanPanelHandle);
   ScanBar = 0;
   SetCtrlAttribute(iMainPanelHandle, PANEL_STARTSCAN, ATTR_VISIBLE, 0);
   SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_LABEL_TEXT, "Scanning for PXI devices");
   SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_ON_COLOR, 0x00F5CC00); // yellow
   SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_VISIBLE, 1);
   SetCtrlVal(iMainPanelHandle, PANEL_PXI_LED, 1);
   ProcessDrawEvents();
   iBuffer = iDevicesFound;

   //Start scan for PXI devices
   iError = FindPXIDevices(&iDevicesFound);
   if (iError)
   {
      GlobalError = 1;
      SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_ON_COLOR, 0x00D10000); // red
      SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_LABEL_TEXT, "An error has occured");
   }
   else
   {
      SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_ON_COLOR, 0x0024CC02); // green
      if (iBuffer == iDevicesFound)
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_LABEL_TEXT, "No devices found");
      }
      else
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_PXI_LED, ATTR_LABEL_TEXT, "Done");
      }
   }

   SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_LABEL_TEXT, "Scanning for CAN devices");
   SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_ON_COLOR, 0x00F5CC00); // yellow
   SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_VISIBLE, 1);
   SetCtrlVal(iMainPanelHandle, PANEL_CAN_LED, 1);
   ProcessDrawEvents();
   iBuffer = iDevicesFound;

   //Start scan for CAN devices
   iError = FindCANDevices(&iDevicesFound);
   if (iError)
   {
      GlobalError = 1;
      SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_ON_COLOR, 0x00D10000); // red
      SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_LABEL_TEXT, "An error has occured");
   }
   else
   {
      SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_ON_COLOR, 0x0024CC02); // green
      if (iBuffer == iDevicesFound)
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_LABEL_TEXT, "No devices found");
      }
      else
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_CAN_LED, ATTR_LABEL_TEXT, "Done");
      }
   }

   SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_LABEL_TEXT, "Scanning for ASRL devices");
   SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_ON_COLOR, 0x00F5CC00); // yellow
   SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_VISIBLE, 1);
   SetCtrlVal(iMainPanelHandle, PANEL_ASRL_LED, 1);
   ProcessDrawEvents();
   iBuffer = iDevicesFound;

   //Start scan for ASR devices
   iError = FindASRDevices(&iDevicesFound);
   if (iError)
   {
      GlobalError = 1;
      SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_ON_COLOR, 0x00D10000); // red
      SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_LABEL_TEXT, "An error has occured");
   }
   else
   {
      SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_ON_COLOR, 0x0024CC02); // green
      ;
      if (iBuffer == iDevicesFound)
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_LABEL_TEXT, "No devices found");
      }
      else
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_ASRL_LED, ATTR_LABEL_TEXT, "Done");
      }
   }
   SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_LABEL_TEXT, "Scanning for GPIB devices");
   SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_ON_COLOR, 0x00F5CC00); // yellow
   SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_VISIBLE, 1);
   SetCtrlVal(iMainPanelHandle, PANEL_GPIB_LED, 1);
   ProcessDrawEvents();
   iBuffer = iDevicesFound;

   //Start scan for GPIB devices
   iError = FindGPIBDevices(&iDevicesFound);
   if (iError)
   {
      GlobalError = 1;
      SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_ON_COLOR, 0x00D10000); // red
      SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_LABEL_TEXT, "An error has occured");
   }
   else
   {
      SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_ON_COLOR, 0x0024CC02); // green
      ;
      if (iBuffer == iDevicesFound)
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_LABEL_TEXT, "No devices found");
      }
      else
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_GPIB_LED, ATTR_LABEL_TEXT, "Done");
      }
   }
   SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_LABEL_TEXT, "Scanning for DAQ devices");
   SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_ON_COLOR, 0x00F5CC00); // yellow
   SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_VISIBLE, 1);
   SetCtrlVal(iMainPanelHandle, PANEL_DAQ_LED, 1);
   ProcessDrawEvents();
   iBuffer = iDevicesFound;

   //Start scan for DAQ devices
   iError = FindDAQDevices(&iDevicesFound);
   if (iError)
   {
      GlobalError = 1;
      SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_ON_COLOR, 0x00D10000); // red
      SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_LABEL_TEXT, "An error has occured");
   }
   else
   {
      SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_ON_COLOR, 0x0024CC02); // green
      if (iBuffer == iDevicesFound)
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_LABEL_TEXT, "No devices found");
      }
      else
      {
         SetCtrlAttribute(iMainPanelHandle, PANEL_DAQ_LED, ATTR_LABEL_TEXT, "Done");
      }
   }

   //Final operations
   ApplyDefaultValuesRS(); //Set default parameters for R&S devices
   InsertMenuItems(); //Update menubar

   //Update UIR
   SetCtrlAttribute(iMainPanelHandle, PANEL_STARTEXPORT, ATTR_VISIBLE, 1);
   SetCtrlAttribute(iMainPanelHandle, PANEL_TEXTMSG_EXPORT, ATTR_VISIBLE, 1);
   SetCtrlAttribute(iMainPanelHandle, PANEL_CHECKBOX_PHYINI, ATTR_VISIBLE, 1);
   iWantPhyIni = 1;
   SetCtrlAttribute(iMainPanelHandle, PANEL_CHECKBOX_APPINI, ATTR_VISIBLE, 1);
   iWantAppIni = 1;
   SetCtrlAttribute(iMainPanelHandle, PANEL_CHECKBOX_TSTSEQ, ATTR_VISIBLE, 1);
   iWantTstSeq = 1;
   SetCtrlAttribute(iMainPanelHandle, PANEL_TEXTMSG, ATTR_VISIBLE, 1);
   SetMenuBarAttribute(iMenuHandle, MENU_FILE_OPENPHYSICAL, ATTR_DIMMED, 1);
   SetMenuBarAttribute(iMenuHandle, MENU_FILE_SAVEPHYS, ATTR_DIMMED, 0);
   SetMenuBarAttribute(iMenuHandle, MENU_EDIT_NEWSCAN, ATTR_DIMMED, 1);
   RemovePopup(iScanPanelHandle);

   if (iDevicesFound)
   {
      sprintf(cMsgText, "%i device(s) were found.\n", iDevicesFound);
      iMadeChanges = 1;
   }
   else
   {
      sprintf(cMsgText, "No devices were found.\n", iDevicesFound);
   }
   if (GlobalError)
   {
      strcat(cMsgText, "An Error has occured. Please check your system!");
   }
   else
   {
      strcat(cMsgText, "Scan process successfully terminated.");
   }
   MessagePopup("TG-ITS", cMsgText);
   SetActiveCtrl(iMainPanelHandle, PANEL_STARTEXPORT);
   return ;
}

/* FUNCTION *****************************************************************/
/**
FindPXIDevices
 *
@brief This function searches for installed PXI components.
 *
@param pFoundFlag: This value is TRUE if components were found.
 *
@return ErrorCode
 *****************************************************************************/
int FindPXIDevices(int* pFoundFlag)
{
   char cVendor[512];
   char cDevice[512];
   char cBenchName[32];
   short sType;
   int iSlot, iFrame;
   char* cSlot = NULL;
   ViSession CardSession;
   ViChar resourceDescriptor[VI_FIND_BUFLEN]; /* e.g: "PXI2::4::0::INSTR" */
   ViInt32 resourceCount;
   ViFindList resourceList = 0;
   ViUInt16 vendorID = 0;
   ViUInt16 deviceID = 0;
   int iHandle;
   double dPercent;
   int PICTavailable = 0;
   int PSAMavailable = 0;

   TypeQuantity.PMAquantity = 0;
   TypeQuantity.PSAMquantity = 0;
   TypeQuantity.PICTquantity = 0;
   TypeQuantity.PFGquantity = 0;
   TypeQuantity.PDFTquantity = 0;
   TypeQuantity.PAMquantity = 0;
   TypeQuantity.PHDTquantity = 0;
   TypeQuantity.PIO2quantity = 0;
   TypeQuantity.PSUquantity = 0;

   iError = 0;

   if ((iError = viFindRsrc(SessionDefRM, "PXI?*INSTR", &resourceList, & resourceCount, resourceDescriptor)))

   if (iError == VI_ERROR_RSRC_NFOUND)
   {
      iError = VI_SUCCESS;
   }
   else
   {
      HandleError("viFindRsrc", iError);
      return iError;
   }
   ScanBar = 3.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, "Search PXI devices");
   ProcessDrawEvents();
   dPercent = 17.0 / (double)resourceCount;

   while (resourceCount)
   {
      *pFoundFlag = * pFoundFlag + 1;
      iSlot =  - 1;
      sprintf(cMsgText, "Check %s", resourceDescriptor);
      SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
      ProcessDrawEvents();

      if (iError = viOpen(SessionDefRM, resourceDescriptor, VI_NULL, VI_NULL, & CardSession))
      {
         HandleError("viOpen(Device)", iError);
         return iError;
      }

      //10 -> VI_PXI_CFG_SPACE aus visa.h
      viIn16(CardSession, 10, 0x0, &vendorID); //Old value VI_ATTR_MANF_ID
      viIn16(CardSession, 10, 0x2, &deviceID); //Old value VI_ATTR_MODEL_CODE

      if (iError = viClose(CardSession))
      {
         HandleError("viClose(CardSession)", iError);
         return iError;
      }

      iError = CheckVendor(vendorID, cVendor);
      if (iError)
      {
         return iError;
      }

      if (vendorID == RS_VENDOR_ID)
      {
         switch (deviceID)
         {
            case RSPRL1_DEVICE_ID:
               sprintf(cMsgText, "PRL1 - %s - %s - %x", resourceDescriptor, cVendor, deviceID);
               break;
            case RSPMA_DEVICE_ID:
               TypeQuantity.PMAquantity++;
               sprintf(cMsgText, "PMA - %s - %s - %x", resourceDescriptor, cVendor, deviceID);
               if (TypeQuantity.PMAquantity <= 1)
               {
                  sprintf(cBenchName, "PMA");
               }
               else
               {
                  sprintf(cBenchName, "PMA_%d", iSlot);
               }
               break;
            case RSPSAM_DEVICE_ID:
               TypeQuantity.PSAMquantity++;
               rspsam_init(resourceDescriptor, VI_TRUE, VI_FALSE, &iHandle);
               rspsam_GetAttributeViInt32(iHandle, "", RSPSAM_ATTR_SLOT_NUMBER, & iSlot);
               rspsam_GetAttributeViInt32(iHandle, "", RSPSAM_ATTR_FRAME_NUMBER, & iFrame);
               rspsam_close(iHandle);
               sprintf(cMsgText, "PSAM - %s - %s - %x - Slot %d", resourceDescriptor, cVendor, deviceID, iSlot);
               if (TypeQuantity.PSAMquantity <= 1)
               {
                  sprintf(cBenchName, "PSAM");
               }
               else
               {
                  sprintf(cBenchName, "PSAM_%d", iSlot);
               }
               PSAMavailable = 1;
               break;
            case RSPICT_DEVICE_ID:
               TypeQuantity.PICTquantity++;
               rspict_init(resourceDescriptor, VI_TRUE, VI_FALSE, &iHandle);
               rspict_GetAttributeViInt32(iHandle, "", RSPICT_ATTR_SLOT_NUMBER, & iSlot);
               rspict_GetAttributeViInt32(iHandle, "", RSPICT_ATTR_FRAME_NUMBER, & iFrame);
               rspict_close(iHandle);
               sprintf(cMsgText, "PICT - %s - %s - %x - Slot %d", resourceDescriptor, cVendor, deviceID, iSlot);
               if (TypeQuantity.PICTquantity <= 1)
               {
                  sprintf(cBenchName, "PICT");
               }
               else
               {
                  sprintf(cBenchName, "PICT_%d", iSlot);
               }
               break;
               PICTavailable = 1;
            case RSPBAS_DEVICE_ID:
               sprintf(cMsgText, "PBAS - %s - %s - %x", resourceDescriptor, cVendor, deviceID);
               sprintf(cBenchName, "PBAS");
               break;
            case RSPFG_DEVICE_ID:
               TypeQuantity.PFGquantity++;
               rspfg_init(resourceDescriptor, VI_TRUE, VI_FALSE, &iHandle);
               rspfg_GetAttributeViInt32(iHandle, "", RSPFG_ATTR_SLOT_NUMBER, &iSlot);
               rspfg_GetAttributeViInt32(iHandle, "", RSPFG_ATTR_FRAME_NUMBER, &iFrame);
               rspfg_close(iHandle);
               sprintf(cMsgText, "PFG - %s - %s - %x - Slot %d", resourceDescriptor, cVendor, deviceID, iSlot);
               if (TypeQuantity.PFGquantity <= 1)
               {
                  sprintf(cBenchName, "PFG");
               }
               else
               {
                  sprintf(cBenchName, "PFG_%d", iSlot);
               }
               break;
            case RSPDFT_DEVICE_ID:
               TypeQuantity.PDFTquantity++;
               rspdft_init(resourceDescriptor, VI_TRUE, VI_FALSE, &iHandle);
               rspdft_GetAttributeViInt32(iHandle, "", RSPDFT_ATTR_SLOT_NUMBER, & iSlot);
               rspdft_GetAttributeViInt32(iHandle, "", RSPDFT_ATTR_FRAME_NUMBER, & iFrame);
               rspdft_close(iHandle);
               sprintf(cMsgText, "PDFT - %s - %s - %x - Slot %d", resourceDescriptor, cVendor, deviceID, iSlot);
               if (TypeQuantity.PDFTquantity <= 1)
               {
                  sprintf(cBenchName, "PDFT");
               }
               else
               {
                  sprintf(cBenchName, "PDFT_%d", iSlot);
               }
               break;
            case RSPAM_DEVICE_ID:
               TypeQuantity.PAMquantity++;
               rspam_init(resourceDescriptor, VI_TRUE, VI_FALSE, &iHandle);
               rspam_GetAttributeViInt32(iHandle, "", RSPAM_ATTR_SLOT_NUMBER, & iSlot);
               rspam_GetAttributeViInt32(iHandle, "", RSPAM_ATTR_FRAME_NUMBER, & iFrame);
               rspam_close(iHandle);
               sprintf(cMsgText, "PAM - %s - %s - %x - Slot %d", resourceDescriptor, cVendor, deviceID, iSlot);
               if (TypeQuantity.PAMquantity <= 1)
               {
                  sprintf(cBenchName, "PAM");
               }
               else
               {
                  sprintf(cBenchName, "PAM_%d", iSlot);
               }
               break;
            case RSPHDT_DEVICE_ID:
               TypeQuantity.PHDTquantity++;
               rsphdt_init(resourceDescriptor, VI_TRUE, VI_FALSE, &iHandle);
               rsphdt_GetAttributeViInt32(iHandle, "", RSPHDT_ATTR_SLOT_NUMBER, & iSlot);
               rsphdt_GetAttributeViInt32(iHandle, "", RSPHDT_ATTR_FRAME_NUMBER, & iFrame);
               rsphdt_close(iHandle);
               sprintf(cMsgText, "PHDT - %s - %s - %x - Slot %d", resourceDescriptor, cVendor, deviceID, iSlot);
               if (TypeQuantity.PHDTquantity <= 1)
               {
                  sprintf(cBenchName, "PHDT");
               }
               else
               {
                  sprintf(cBenchName, "PHDT_%d", iSlot);
               }
               break;

            default:
               sprintf(cMsgText, "Unknown - %s - %s - %x", resourceDescriptor, cVendor, deviceID);
               sprintf(cBenchName, "Unknown PXI");
               break;
         }
         InsertListItem(iMainPanelHandle, PANEL_PXIDEVICES,  - 1, cMsgText, *pFoundFlag);
      }
      else
      {
         sprintf(cBenchName, "TBD");
         sprintf(cMsgText, "%s - unknown device - %s - %x", cVendor, resourceDescriptor, deviceID);
         InsertListItem(iMainPanelHandle, PANEL_PXIDEVICES,  - 1, cMsgText, *pFoundFlag);
      }
      pFirstRessource = pAppendDevice(pFirstRessource, PXI, cBenchName, resourceDescriptor, * pFoundFlag, iSlot, iFrame);
      resourceCount--;
      if (resourceCount)
      {
         if (viFindNext(resourceList, resourceDescriptor))
         {
            HandleError("viClose(CardSession)", iError);
            return iError;
         }
      }
      ScanBar = ScanBar + dPercent;
      SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
      ProcessDrawEvents();
      Delay(0.1);

   }
   if (resourceList)
   {
      if (iError = viClose(resourceList))
      {
         HandleError("viClose(resourceList)", iError);
         return iError;
      }
   }

   ScanBar = 20.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   if (PICTavailable && !PSAMavailable)
   {
      MessagePopup("TG-ITS", "An ICT-module was detected, but no DMM.\nPlease add PSAM-device and rescan.\nOtherwise PICT cannot be set into operation properly.");
   }

   return iError;
}

/* FUNCTION *****************************************************************/
/**
FindCANDevices
 *
@brief This function searches for installed CAN components.
 *
@param pFoundFlag: This value is TRUE if components were found.
 *
@return ErrorCode
 *****************************************************************************/
int FindCANDevices(int* pFoundFlag)
{
   int i, j, iHandle, Length, iSlot, iFrame;
   int CANControllerHandle;
   char cBuffer[512];
   char cBenchName[32];
   char cResourceDescriptor[2048];
   int iResCount;
   double dPercent;

   TypeQuantity.PIO2quantity = 0;
   TypeQuantity.PSUquantity = 0;
   TypeQuantity.PMBquantity = 0;

   iResCount = 0;
   iError = 0;

   ScanBar = 23.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   sprintf(cMsgText, "Open CAN0::0::1::5");
   SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
   ProcessDrawEvents();

   /*iError = rscan_sysOpen("CAN0::0::1::5", &CANControllerHandle);
   if (iError)
   {
   sprintf(cMsgText, "");
   rscan_errorMessage(iError, cMsgText);
   HandleError(strcat(cMsgText, " (rscan_usrOpen)"), iError);
   return iError;
   } */

   sprintf(cMsgText, "Scanning CAN bus");
   SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
   ProcessDrawEvents();

   iError = rscan_sysScan("CAN0::0", cResourceDescriptor);
   if (iError)
   {
      sprintf(cMsgText, "");
      rscan_errorMessage(iError, cMsgText);
      HandleError(strcat(cMsgText, " (rscan_sysScan)"), iError);
      return iError;
   }

   Length = strlen(cResourceDescriptor);

   for (i = 0; i < Length; i++)
   if (cResourceDescriptor[i] == ',')
   {
      iResCount++;
   }
   if (iResCount)
   {
      iResCount++;
   }
   dPercent = 17.0 / (double)iResCount;

   i = 0;
   j = 0;

   while (5 < (Length - i))
   {
      while ((cResourceDescriptor[i] != '\0') && (cResourceDescriptor[i] != ','))
      {
         cBuffer[j] = cResourceDescriptor[i];
         i++;
         j++;
      }
      iSlot =  - 1;
      cBuffer[j] = '\0';
      j = 0;
      i++;
      sprintf(cMsgText, "Check %s", cBuffer);
      SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
      ProcessDrawEvents();

      if (cBuffer[0] == 'C')
      {
         iError = rspmb_InitWithOptions(cBuffer, VI_TRUE, VI_TRUE, "Simulate=0, RangeCheck=1, QueryInstrStatus=1, Cache=1", &iHandle);
         if (!iError)
         {
            TypeQuantity.PMBquantity++;
            iError = rspmb_GetAttributeViInt32(iHandle, "", RSPMB_ATTR_SLOT_NUMBER, &iSlot);
            iError = rspmb_GetAttributeViInt32(iHandle, "", RSPMB_ATTR_FRAME_NUMBER, &iFrame);
            rspmb_close(iHandle);
            //iSlot = GetSlotNumber(cBuffer);
            sprintf(cMsgText, "PMB - %s - Rohde & Schwarz GMBH & Co KG - Slot %d", cBuffer, iSlot);
            sprintf(cBenchName, "PMB_%d", iSlot);
         }
         if (iError)
         {
            iError = rspsm1_InitWithOptions(cBuffer, VI_TRUE, VI_TRUE, "Simulate=0, RangeCheck=1, QueryInstrStatus=1, Cache=1", &iHandle);
            if (!iError)
            {
               iError = rspsm1_GetAttributeViInt32(iHandle, "", RSPSM1_ATTR_SLOT_NUMBER, &iSlot);
               iError = rspsm1_GetAttributeViInt32(iHandle, "", RSPSM1_ATTR_FRAME_NUMBER, &iFrame);
               rspsm1_close(iHandle);
               //iSlot = GetSlotNumber(cBuffer);
               sprintf(cMsgText, "PSM1 - %s - Rohde & Schwarz GMBH & Co KG - Slot %d", cBuffer, iSlot);
               sprintf(cBenchName, "PSM1_%d", iSlot);
            }
         }
         if (iError)
         {
            iError = rspsm2_InitWithOptions(cBuffer, VI_TRUE, VI_TRUE, "Simulate=0, RangeCheck=1, QueryInstrStatus=1, Cache=1", &iHandle);
            if (!iError)
            {
               iError = rspsm2_GetAttributeViInt32(iHandle, "", RSPSM2_ATTR_SLOT_NUMBER, &iSlot);
               iError = rspsm2_GetAttributeViInt32(iHandle, "", RSPSM2_ATTR_FRAME_NUMBER, &iFrame);
               rspsm2_close(iHandle);
               //iSlot = GetSlotNumber(cBuffer);
               sprintf(cMsgText, "PSM2 - %s - Rohde & Schwarz GMBH & Co KG - Slot %d", cBuffer, iSlot);
               sprintf(cBenchName, "PSM2_%d", iSlot);
            }
         }
         if (iError)
         {
            iError = rspio2_InitWithOptions(cBuffer, VI_TRUE, VI_TRUE, "Simulate=0, RangeCheck=1, QueryInstrStatus=1, Cache=1", &iHandle);
            if (!iError)
            {
               TypeQuantity.PIO2quantity++;
               iError = rspio2_GetAttributeViInt32(iHandle, "", RSPIO2_ATTR_SLOT_NUMBER, &iSlot);
               iError = rspio2_GetAttributeViInt32(iHandle, "", RSPIO2_ATTR_FRAME_NUMBER, &iFrame);
               rspio2_close(iHandle);
               //iSlot = GetSlotNumber(cBuffer);
               sprintf(cMsgText, "PIO2 - %s - Rohde & Schwarz GMBH & Co KG - Slot %d", cBuffer, iSlot);
               sprintf(cBenchName, "PIO2_%d", iSlot);
            }
         }
         if (iError)
         {
            iError = rspsu_InitWithOptions(cBuffer, VI_TRUE, VI_TRUE, "Simulate=0, RangeCheck=1, QueryInstrStatus=1, Cache=1", &iHandle);
            if (!iError)
            {
               TypeQuantity.PSUquantity++;
               iError = rspsu_GetAttributeViInt32(iHandle, "", RSPSU_ATTR_SLOT_NUMBER, &iSlot);
               iError = rspsu_GetAttributeViInt32(iHandle, "", RSPSU_ATTR_FRAME_NUMBER, &iFrame);
               rspsu_close(iHandle);
               iSlot = GetSlotNumber(cBuffer);
               sprintf(cMsgText, "PSU - %s - Rohde & Schwarz GMBH & Co KG - Slot %d", cBuffer, iSlot);
               if (TypeQuantity.PSUquantity == 1)
               {
                  sprintf(cBenchName, "PSU");
               }
               else
               {
                  sprintf(cBenchName, "PSU_%d", iSlot);
               }
            }
         }
         if (iError)
         {
            iError = rspsys_InitWithOptions(cBuffer, VI_TRUE, VI_TRUE, "Simulate=0, RangeCheck=1, QueryInstrStatus=1, Cache=1", &iHandle);
            if (!iError)
            {
               iError = rspsys_GetAttributeViInt32(iHandle, "", RSPSYS_ATTR_SLOT_NUMBER, &iSlot);
               iError = rspsys_GetAttributeViInt32(iHandle, "", RSPSYS_ATTR_FRAME_NUMBER, &iFrame);
               rspsys_close(iHandle);
               sprintf(cMsgText, "PSYS1 - %s - Rohde & Schwarz GMBH & Co KG", cBuffer);
               sprintf(cBenchName, "PSYS1");
            }
         }

         if (iError)
         {
            sprintf(cMsgText, "Unknown device - %s", cBuffer);
            sprintf(cBenchName, "Unknown CAN");
         }
         *pFoundFlag = * pFoundFlag + 1;
         pFirstRessource = pAppendDevice(pFirstRessource, CAN, cBenchName, cBuffer, *pFoundFlag, iSlot, iFrame);
         InsertListItem(iMainPanelHandle, PANEL_CANDEVICES,  - 1, cMsgText, *pFoundFlag);
         ScanBar = ScanBar + dPercent;
         SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
         ProcessDrawEvents();
      }
   }

   sprintf(cMsgText, "Close CAN bus");
   SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
   ProcessDrawEvents();

   ScanBar = 40.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   //rscan_close(CANControllerHandle);
   return 0;

}

/* FUNCTION *****************************************************************/
/**
FindASRDevices
 *
@brief This function searches for installed serial or parallel interfaces
 *
@param pFoundFlag: This value is TRUE if components were found.
 *
@return ErrorCode
 *****************************************************************************/
int FindASRDevices(int* pFoundFlag)
{
   int iCount = 0;
   ViUInt16 InterfaceType;
   ViUInt16 InterfaceNumber;
   char cVendor[512];
   char cDevice[512];
   char cBenchName[32];
   ViSession CardSession;
   ViChar resourceDescriptor[VI_FIND_BUFLEN]; /* e.g: "PXI2::4::0::INSTR" */
   ViInt32 resourceCount;
   ViFindList resourceList = 0;

   double dPercent;

   iError = 0;

   ScanBar = 43.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   sprintf(cMsgText, "Scanning for serial interfaces");
   SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
   ProcessDrawEvents();

   if ((iError = viFindRsrc(SessionDefRM, "ASRL?*INSTR", &resourceList, & resourceCount, resourceDescriptor)))

   if (iError == VI_ERROR_RSRC_NFOUND)
   {
      iError = VI_SUCCESS;
   }
   else
   {
      HandleError("viFindRsrc", iError);
      return iError;
   }
   dPercent = 17.0 / (double)resourceCount;

   while (resourceCount)
   {
      iCount++;

      sprintf(cMsgText, "Check %s", resourceDescriptor);
      SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
      ProcessDrawEvents();

      viParseRsrc(SessionDefRM, resourceDescriptor, &InterfaceType, & InterfaceNumber);
      *pFoundFlag = * pFoundFlag + 1;
      if (InterfaceType)
      {
         switch (InterfaceType)
         {
            //RS232
            case 4:
               sprintf(cBenchName, "COM%i", InterfaceNumber);
               break;
            default:
               sprintf(cBenchName, "Unknown ASRL%i", InterfaceNumber);
               break;
         }
         InsertListItem(iMainPanelHandle, PANEL_ASRLDEVICES,  - 1, cBenchName, *pFoundFlag);
      }
      else
      {
         sprintf(cMsgText, "%s - unknown device - %s", cVendor, resourceDescriptor);
         InsertListItem(iMainPanelHandle, PANEL_ASRLDEVICES,  - 1, cBenchName, *pFoundFlag);
      }
      pFirstRessource = pAppendDevice(pFirstRessource, ASRL, cBenchName, cBenchName, * pFoundFlag,  - 1,  - 1);
      resourceCount--;

      if (resourceCount)
      {
         if (viFindNext(resourceList, resourceDescriptor))
         {
            HandleError("viClose(CardSession)", iError);
            return iError;
         }
      }
      ScanBar = ScanBar + dPercent;
      SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
      ProcessDrawEvents();
      Delay(0.07);
   }
   if (resourceList)
   {
      sprintf(cMsgText, "Close resource");
      SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
      ProcessDrawEvents();

      if (iError = viClose(resourceList))
      {
         HandleError("viClose(resourceList)", iError);
         return iError;
      }
   }

   ScanBar = 60.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   return iError;
}

/* FUNCTION *****************************************************************/
/**
FindGPIBDevices
 *
@brief This function searches for installed IEEE-488 components
 *
@param pFoundFlag: This value is TRUE if components were found.
 *
@return ErrorCode
 *****************************************************************************/
int FindGPIBDevices(int* pFoundFlag)
{
   int i, j;
   int iCount = 0;
   int iBoardIndex, iPrimAddress = 0;
   int iHandle;
   char cBuffer[512];
   char cReadBuffer[2];
   char cBenchName[32];
   ViChar resourceDescriptor[VI_FIND_BUFLEN]; /* e.g: "PXI2::4::0::INSTR" */
   ViInt32 resourceCount;
   ViFindList resourceList = 0;
   double dPercent;

   ScanBar = 63.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   iError = 0;

   sprintf(cMsgText, "Scanning GPIB interface");
   SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
   ProcessDrawEvents();

   if ((iError = viFindRsrc(SessionDefRM, "GPIB?*INSTR", &resourceList, & resourceCount, resourceDescriptor)))

   if (iError == VI_ERROR_RSRC_NFOUND)
   {
      iError = VI_SUCCESS;
   }
   else
   {
      HandleError("viFindRsrc", iError);
      return iError;
   }
   dPercent = 17.0 / (double)resourceCount;

   while (resourceCount)
   {

      sprintf(cMsgText, "Check %s", resourceDescriptor);
      SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
      ProcessDrawEvents();

      *pFoundFlag = * pFoundFlag + 1;
      iCount++;
      cBuffer[0] = resourceDescriptor[5];
      cBuffer[1] = '\0';
      iBoardIndex = atoi(cBuffer);
      i = 0;
      while (resourceDescriptor[i] != ':')
      {
         i++;
      }
      i++;
      i++;
      j = 0;
      while (resourceDescriptor[i] != ':')
      {
         cBuffer[j] = resourceDescriptor[i];
         i++;
         j++;
      }
      cBuffer[j] = '\0';
      iPrimAddress = atoi(cBuffer);
      iHandle = ibdev(iBoardIndex, iPrimAddress, GpibSAD, GpibTimeOut, GpibEosEnable, GpibEosSign);
      cBuffer[0] = '\0';
      ibwrt(iHandle, "*IDN?", strlen("*IDN?"));
      cBuffer[0] = '\0';

      ibrd(iHandle, cBuffer, 500);
      if (ibsta& ERR)
      {
         return iberr;
      }
      else
      {
         cBuffer[strlen(cBuffer) - 2] = '\0';
      }
      if (strlen(cBuffer) == 0)
      {
         sprintf(cMsgText, "Unknown GPIB-Device - %s", resourceDescriptor);
         sprintf(cBenchName, "Unknown GPIB");
      }
      else
      {
         sprintf(cMsgText, "%s - %s", cBuffer, resourceDescriptor);
         strncpy(cBenchName, cBuffer, 31);
      }
      InsertListItem(iMainPanelHandle, PANEL_GPIBDEVICES,  - 1, cMsgText, *pFoundFlag);
      pFirstRessource = pAppendDevice(pFirstRessource, GPIB, cBenchName, resourceDescriptor, * pFoundFlag,  - 1,  - 1);
      resourceCount--;

      if (resourceCount)
      {
         if (viFindNext(resourceList, resourceDescriptor))
         {
            HandleError("viClose(CardSession)", iError);
            return iError;
         }
      }
      ScanBar = ScanBar + dPercent;
      SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
      ProcessDrawEvents();
      Delay(0.05);
   }

   if (resourceList)
   {
      sprintf(cMsgText, "Close GPIB bus");
      SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
      ProcessDrawEvents();

      if (iError = viClose(resourceList))
      {
         HandleError("viClose(resourceList)", iError);
         return iError;
      }
   }

   ScanBar = 80.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   return iError;
}

/* FUNCTION *****************************************************************/
/**
FindDAQDevices
 *
@brief This function searches for installed NI-DAQ components
 *
@param pFoundFlag: This value is TRUE if components were found.
 *
@return ErrorCode
 *****************************************************************************/
int FindDAQDevices(int* pFoundFlag)
{
   int i, j, Information;
   int iStatus;
   short BoardCode;
   int iHandle;
   char cBenchName[32];
   ViChar resourceDescriptor[VI_FIND_BUFLEN]; /* e.g: "PXI2::4::0::INSTR" */
   double dPercent;
   dPercent = 1.0;
   ScanBar = 83.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();

   iError = 0;
   for (i = 1; i < 17; i++)
   {
      sprintf(cMsgText, "Check DAQ-Board %d", i);
      SetCtrlAttribute(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ATTR_LABEL_TEXT, cMsgText);
      ProcessDrawEvents();

      /*iStatus = Init_DA_Brds (i, &BoardCode);
      if (!iStatus)
      {
      sprintf(cBenchName, "Unknown DAQ-Board");
      if (BoardCode > 0)
      {
       *pFoundFlag =  *pFoundFlag + 1;
      iError = CheckNIBoards(BoardCode, cBenchName);
      if (iError)
      {
      return iError;
      }
      sprintf(resourceDescriptor, "DAQ0::%i", i);
      sprintf(cMsgText, "%s - %s", cBenchName, resourceDescriptor);
      InsertListItem(iMainPanelHandle, PANEL_DAQDEVICES,  - 1, cMsgText,
       *pFoundFlag);
      pFirstRessource = pAppendDevice(pFirstRessource, DAQ, cBenchName,
      resourceDescriptor,  *pFoundFlag,  - 1, -1);
      }
      }
      else
      {
      i = 16;									// get out of loop
      }  */

      i = 16;

      ScanBar = ScanBar + dPercent;
      SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
      ProcessDrawEvents();
      Delay(0.05);
   }

   ScanBar = 100.0;
   SetCtrlVal(iScanPanelHandle, PANEL_2_NUMERICSLIDE, ScanBar);
   ProcessDrawEvents();
   Delay(0.1);
   return iError;
}

/******************************************************************************/
// END OF FILE
