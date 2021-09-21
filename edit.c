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
@file edit.c
 *
@brief Include all functions to edit parameters of each device (bench) entry
in physical.ini
 *
@version 1.0.0.0
 *
@author Robert Renner <A HREF="mailto:4r@sw-its.net">4r@sw-its.net</A>\n

Language: ANSI-C ISO/IEC9899:1990
 *
<b>History:</b>
- <b>07.07.05 R.Renner</b>
- TS-PAM module implemented
- <b>06.12.04 R.Renner</b>
- Self test extensions implemented
- <b>02.12.04 R.Renner</b>
- Initial revision

 ******************************************************************************
 *****************************************************************************/

/* INCLUDE FILES ************************************************************/
#include "main.h"

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
FindID
 *
@brief This function search for a resource pointer to a selected device
 *
@param *iDeviceID: Value of selected list box item
 *
@return ressource pointer
 *****************************************************************************/
ressource* FindID(int iDeviceID)
{
   ressource* ptr;
   ptr = pFirstRessource;
   while (ptr)
   {
      if (ptr->iID == iDeviceID)
      {
         break;
      }
      ptr = ptr->next;
   }
   return ptr;
}

/* FUNCTION *****************************************************************/
/**
SetValue
 *
@brief This function copy all parameters of a selected device into resources
of EditPanel
 *
@param *ptr: Pointer to an element of device list
 *
@return ErrorCode
 *****************************************************************************/
int SetValue(ressource* ptr)
{

   SetCtrlVal(iEditPanelHandle, EDIT_BENCHNAME, ptr->cBenchName);
   SetCtrlVal(iEditPanelHandle, EDIT_DESCRIPTION, ptr->cDescription);
   SetCtrlVal(iEditPanelHandle, EDIT_TYPE, ptr->cType);

   sprintf(cOriginalDeviceType, ptr->cType);

   SetCtrlVal(iEditPanelHandle, EDIT_RESSOURCE, ptr->cRessourceDesc);
   SetCtrlVal(iEditPanelHandle, EDIT_DRIVERDLL, ptr->cDriverDLL);
   SetCtrlVal(iEditPanelHandle, EDIT_DRIVERPREFIX, ptr->cDriverPrefix);
   SetCtrlVal(iEditPanelHandle, EDIT_DRIVEROPTION, ptr->cDriverOption);
   SetCtrlVal(iEditPanelHandle, EDIT_SFTDLL, ptr->cSFTDll);
   SetCtrlVal(iEditPanelHandle, EDIT_SFTPREFIX, ptr->cSFTPrefix);
   SetCtrlVal(iEditPanelHandle, EDIT_BAUDRATE, ptr->iBaudrate);
   SetCtrlVal(iEditPanelHandle, EDIT_PARITY, ptr->cParity);
   SetCtrlVal(iEditPanelHandle, EDIT_HANDSHAKE, ptr->cHandshake);
   SetCtrlVal(iEditPanelHandle, EDIT_DATABITS, ptr->iDataBits);
   SetCtrlVal(iEditPanelHandle, EDIT_STOPBITS, ptr->iStopBits);
   if (ptr->iInternalType == ASRL)
   {
      SetCtrlAttribute(iEditPanelHandle, EDIT_BAUDRATE, ATTR_DIMMED, 0);
      SetCtrlAttribute(iEditPanelHandle, EDIT_PARITY, ATTR_DIMMED, 0);
      SetCtrlAttribute(iEditPanelHandle, EDIT_HANDSHAKE, ATTR_DIMMED, 0);
      SetCtrlAttribute(iEditPanelHandle, EDIT_DATABITS, ATTR_DIMMED, 0);
      SetCtrlAttribute(iEditPanelHandle, EDIT_STOPBITS, ATTR_DIMMED, 0);
   }
   else
   {
      SetCtrlAttribute(iEditPanelHandle, EDIT_BAUDRATE, ATTR_DIMMED, 1);
      SetCtrlAttribute(iEditPanelHandle, EDIT_PARITY, ATTR_DIMMED, 1);
      SetCtrlAttribute(iEditPanelHandle, EDIT_HANDSHAKE, ATTR_DIMMED, 1);
      SetCtrlAttribute(iEditPanelHandle, EDIT_DATABITS, ATTR_DIMMED, 1);
      SetCtrlAttribute(iEditPanelHandle, EDIT_STOPBITS, ATTR_DIMMED, 1);
   }
   sprintf(cMsgText, "Edit -> %s (%s)", ptr->cBenchName, ptr->cRessourceDesc);
   SetPanelAttribute(iEditPanelHandle, ATTR_TITLE, cMsgText);

   if (ptr->iSlot)
   {
      SetCtrlAttribute(iEditPanelHandle, EDIT_DELETEDEV, ATTR_VISIBLE, 0);
      SetCtrlAttribute(iEditPanelHandle, EDIT_TEXTMADDED, ATTR_VISIBLE, 0);
   }
   else
   {
      SetCtrlAttribute(iEditPanelHandle, EDIT_DELETEDEV, ATTR_VISIBLE, 1);
      SetCtrlAttribute(iEditPanelHandle, EDIT_TEXTMADDED, ATTR_VISIBLE, 1);
      SetCtrlVal(iEditPanelHandle, EDIT_DELETEDEV, 0);
   }

   return 0;
}

/* FUNCTION *****************************************************************/
/**
ApplyValues
 *
@brief This function copy all (changed) values from EditPanel to selected
device parameters in the device list
 *
@param *ptr: Pointer to an element of device list
 *
@return ErrorCode
 *****************************************************************************/
int ApplyValues(ressource* ptr)
{
   int iIndex;
   int iResource;
   int iDelete;
   char cDevName[300];



   GetCtrlVal(iEditPanelHandle, EDIT_DELETEDEV, &iDelete);

   if (iDelete)
   {
      sprintf(cDevName, "This device was added manually.\nDo you want to delete %s ?", ptr->cBenchName);
      iShouldClose = 1;
      if (ConfirmPopup("TG-ITS", cDevName))
      {
         DeleteDev(ptr);
         SetCtrlVal(iEditPanelHandle, EDIT_DELETEDEV, 0);
         return 0;
      }
      SetCtrlVal(iEditPanelHandle, EDIT_DELETEDEV, 0);
   }

   if (ptr->iInternalType == ASRL)
   {
      GetCtrlVal(iEditPanelHandle, EDIT_BAUDRATE, &ptr->iBaudrate);
      GetCtrlVal(iEditPanelHandle, EDIT_PARITY, ptr->cParity);
      GetCtrlVal(iEditPanelHandle, EDIT_HANDSHAKE, ptr->cHandshake);
      GetCtrlVal(iEditPanelHandle, EDIT_DATABITS, &ptr->iDataBits);
      GetCtrlVal(iEditPanelHandle, EDIT_STOPBITS, &ptr->iStopBits);
   }
   GetCtrlVal(iEditPanelHandle, EDIT_BENCHNAME, ptr->cBenchName);
   GetCtrlVal(iEditPanelHandle, EDIT_DESCRIPTION, ptr->cDescription);
   GetCtrlVal(iEditPanelHandle, EDIT_TYPE, ptr->cType);
   GetCtrlVal(iEditPanelHandle, EDIT_RESSOURCE, ptr->cRessourceDesc);
   GetCtrlVal(iEditPanelHandle, EDIT_DRIVERDLL, ptr->cDriverDLL);
   GetCtrlVal(iEditPanelHandle, EDIT_DRIVERPREFIX, ptr->cDriverPrefix);
   GetCtrlVal(iEditPanelHandle, EDIT_DRIVEROPTION, ptr->cDriverOption);
   GetCtrlVal(iEditPanelHandle, EDIT_SFTDLL, ptr->cSFTDll);
   GetCtrlVal(iEditPanelHandle, EDIT_SFTPREFIX, ptr->cSFTPrefix);

   if (strcmp(ptr->cType, cOriginalDeviceType) != 0)
   {
      // decrease the amount of original device

      if (strcmp(cOriginalDeviceType, "PMA") == 0)
      {
         TypeQuantity.PMAquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PSAM") == 0)
      {
         TypeQuantity.PSAMquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PICT") == 0)
      {
         TypeQuantity.PICTquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PFG") == 0)
      {
         TypeQuantity.PFGquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PDFT") == 0)
      {
         TypeQuantity.PDFTquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PAM") == 0)
      {
         TypeQuantity.PAMquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PHDT") == 0)
      {
         TypeQuantity.PHDTquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PSU") == 0)
      {
         TypeQuantity.PSUquantity--;
      }
      if (strcmp(cOriginalDeviceType, "PIO2") == 0)
      {
         TypeQuantity.PIO2quantity--;
      }
      if (strcmp(cOriginalDeviceType, "PMB") == 0)
      {
         TypeQuantity.PMBquantity--;
      }

      // increase the amount of changed device

      if (strcmp(ptr->cType, "PMA") == 0)
      {
         TypeQuantity.PMAquantity++;
      }
      if (strcmp(ptr->cType, "PSAM") == 0)
      {
         TypeQuantity.PSAMquantity++;
      }
      if (strcmp(ptr->cType, "PICT") == 0)
      {
         TypeQuantity.PICTquantity++;
      }
      if (strcmp(ptr->cType, "PFG") == 0)
      {
         TypeQuantity.PFGquantity++;
      }
      if (strcmp(ptr->cType, "PDFT") == 0)
      {
         TypeQuantity.PDFTquantity++;
      }
      if (strcmp(ptr->cType, "PAM") == 0)
      {
         TypeQuantity.PAMquantity++;
      }
      if (strcmp(ptr->cType, "PHDT") == 0)
      {
         TypeQuantity.PHDTquantity++;
      }
      if (strcmp(ptr->cType, "PSU") == 0)
      {
         TypeQuantity.PSUquantity++;
      }
      if (strcmp(ptr->cType, "PIO2") == 0)
      {
         TypeQuantity.PIO2quantity++;
      }
      if (strcmp(ptr->cType, "PMB") == 0)
      {
         TypeQuantity.PMBquantity++;
      }
   }
   iResource = PANEL_PXIDEVICES;
   switch (ptr->iInternalType)
   {
      case PXI:
         iResource = PANEL_PXIDEVICES;
         break;
      case CAN:
         iResource = PANEL_CANDEVICES;
         break;
      case ASRL:
         iResource = PANEL_ASRLDEVICES;
         break;
      case GPIB:
         iResource = PANEL_GPIBDEVICES;
         break;
      case DAQ:
         iResource = PANEL_DAQDEVICES;
         break;

   }
   sprintf(cMsgText, "%s - %s", ptr->cBenchName, ptr->cRessourceDesc);
   GetIndexFromValue(iMainPanelHandle, iResource, &iIndex, ptr->iID);
   ReplaceListItem(iMainPanelHandle, iResource, iIndex, cMsgText, ptr->iID);
   InsertMenuItems();
   return 0;

}

/* FUNCTION *****************************************************************/
/**
ApplyDefaultValuesRS
 *
@brief This function set the default parameters for all R&S standard devices
 *
@param void
 *
@return void
 *****************************************************************************/
void ApplyDefaultValuesRS(void)
{
   int psm1or2;
   char cName[4];
   ressource* ptr;

   ptr = pFirstRessource;
   while (ptr)
   {
      cName[0] = ptr->cBenchName[0];
      cName[1] = ptr->cBenchName[1];
      cName[2] = ptr->cBenchName[2];
      cName[3] = '\0';
      if (strcmp(cName, "PBA") == 0)
      {
         sprintf(ptr->cDescription, TSPBAS_DESCRIPTION);
         sprintf(ptr->cType, TSPBAS_TYPE);
         sprintf(ptr->cDriverDLL, TSPBAS_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPBAS_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPBAS_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPBAS_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPBAS_SFTPREFIX);
      }
      else if (strcmp(cName, "PDF") == 0)
      {
         sprintf(ptr->cDescription, TSPDFT_DESCRIPTION);
         sprintf(ptr->cType, TSPDFT_TYPE);
         sprintf(ptr->cDriverDLL, TSPDFT_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPDFT_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPDFT_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPDFT_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPDFT_SFTPREFIX);
      }
      else if (strcmp(cName, "PFG") == 0)
      {
         sprintf(ptr->cDescription, TSPFG_DESCRIPTION);
         sprintf(ptr->cType, TSPFG_TYPE);
         sprintf(ptr->cDriverDLL, TSPFG_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPFG_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPFG_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPFG_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPFG_SFTPREFIX);
      }
      else if (strcmp(cName, "PMA") == 0)
      {
         sprintf(ptr->cDescription, TSPMA_DESCRIPTION);
         sprintf(ptr->cType, TSPMA_TYPE);
         sprintf(ptr->cDriverDLL, TSPMA_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPMA_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPMA_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPMA_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPMA_SFTPREFIX);
      }
      else if (strcmp(cName, "PMB") == 0)
      {
         sprintf(ptr->cDescription, TSPMB_DESCRIPTION);
         sprintf(ptr->cType, TSPMB_TYPE);
         sprintf(ptr->cDriverDLL, TSPMB_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPMB_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPMB_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPMB_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPMB_SFTPREFIX);
      }
      else if (strcmp(cName, "PSM") == 0)
      {
         psm1or2 = ptr->cBenchName[3]; /*checks 4th letter of device*/
         if (psm1or2 == '1')
         {
            sprintf(ptr->cDescription, TSPSM1_DESCRIPTION);
            sprintf(ptr->cType, TSPSM1_TYPE);
            sprintf(ptr->cDriverDLL, TSPSM1_DRIVER);
            sprintf(ptr->cDriverPrefix, TSPSM1_DRIVERPREFIX);
            sprintf(ptr->cDriverOption, TSPSM1_DRIVEROPTIONS);
            sprintf(ptr->cSFTDll, TSPSM1_SFTDLL);
            sprintf(ptr->cSFTPrefix, TSPSM1_SFTPREFIX);
         }
         else if (psm1or2 == '2')
         {
            sprintf(ptr->cDescription, TSPSM2_DESCRIPTION);
            sprintf(ptr->cType, TSPSM2_TYPE);
            sprintf(ptr->cDriverDLL, TSPSM2_DRIVER);
            sprintf(ptr->cDriverPrefix, TSPSM2_DRIVERPREFIX);
            sprintf(ptr->cDriverOption, TSPSM2_DRIVEROPTIONS);
            sprintf(ptr->cSFTDll, TSPSM2_SFTDLL);
            sprintf(ptr->cSFTPrefix, TSPSM2_SFTPREFIX);
         }
      }
      else if (strcmp(cName, "PSY") == 0)
      {
         sprintf(ptr->cDescription, TSPSYS_DESCRIPTION);
         sprintf(ptr->cType, TSPSYS_TYPE);
         sprintf(ptr->cDriverDLL, TSPSYS_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPSYS_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPSYS_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPSYS_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPSYS_SFTPREFIX);
      }
      else if (strcmp(cName, "PSA") == 0)
      {
         sprintf(ptr->cDescription, TSPSAM_DESCRIPTION);
         sprintf(ptr->cType, TSPSAM_TYPE);
         sprintf(ptr->cDriverDLL, TSPSAM_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPSAM_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPSAM_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPSAM_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPSAM_SFTPREFIX);
      }
      else if (strcmp(cName, "PIC") == 0)
      {
         sprintf(ptr->cDescription, TSPICT_DESCRIPTION);
         sprintf(ptr->cType, TSPICT_TYPE);
         sprintf(ptr->cDriverDLL, TSPICT_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPICT_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPICT_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPICT_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPICT_SFTPREFIX);
      }
      else if (strcmp(cName, "PAM") == 0)
      {
         sprintf(ptr->cDescription, TSPAM_DESCRIPTION);
         sprintf(ptr->cType, TSPAM_TYPE);
         sprintf(ptr->cDriverDLL, TSPAM_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPAM_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPAM_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPAM_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPAM_SFTPREFIX);
      }
      else if (strcmp(cName, "PSU") == 0)
      {
         sprintf(ptr->cDescription, TSPSU_DESCRIPTION);
         sprintf(ptr->cType, TSPSU_TYPE);
         sprintf(ptr->cDriverDLL, TSPSU_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPSU_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPSU_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPSU_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPSU_SFTPREFIX);
      }
      else if (strcmp(cName, "PIO") == 0)
      {
         sprintf(ptr->cDescription, TSPIO2_DESCRIPTION);
         sprintf(ptr->cType, TSPIO2_TYPE);
         sprintf(ptr->cDriverDLL, TSPIO2_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPIO2_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPIO2_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPIO2_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPIO2_SFTPREFIX);
      }
      else if (strcmp(cName, "PHD") == 0)
      {
         sprintf(ptr->cDescription, TSPHDT_DESCRIPTION);
         sprintf(ptr->cType, TSPHDT_TYPE);
         sprintf(ptr->cDriverDLL, TSPHDT_DRIVER);
         sprintf(ptr->cDriverPrefix, TSPHDT_DRIVERPREFIX);
         sprintf(ptr->cDriverOption, TSPHDT_DRIVEROPTIONS);
         sprintf(ptr->cSFTDll, TSPHDT_SFTDLL);
         sprintf(ptr->cSFTPrefix, TSPHDT_SFTPREFIX);
      }

      ptr = ptr->next;
   }
   return ;
}

/* FUNCTION *****************************************************************/
/**
DeleteDev
 *
@brief deletes a device from list
 *
@param *ptr: Pointer to an element of device list
 *
@return ErrorCode
 *****************************************************************************/
int DeleteDev(ressource* ptr)
{
   ressource* pTMPprev;
   ressource* pTMPkill;
   int iControlID;
   int iIndex;

   pTMPkill = ptr;

   pTMPprev = pFirstRessource;
   if (strcmp(pTMPprev->cBenchName, pTMPkill->cBenchName) != 0)
   {
      while ((strcmp(pTMPprev->next->cBenchName, pTMPkill->cBenchName) != 0) && (pTMPprev->next != NULL))
      {
         pTMPprev = pTMPprev->next;
      }
   }
   else
   {
      // ?


   }
   iControlID = 3;
   switch (pTMPkill->iInternalType)
   {
      case PXI:
         iControlID = 3;
         break;
      case CAN:
         iControlID = 4;
         break;
      case ASRL:
         iControlID = 5;
         break;
      case GPIB:
         iControlID = 6;
         break;
      case DAQ:
         iControlID = 7;
         break;
   }

   if (strcmp(pTMPkill->cType, "PAM") == 0)
   {
      TypeQuantity.PMAquantity--;
   }
   if (strcmp(pTMPkill->cType, "PSAM") == 0)
   {
      TypeQuantity.PSAMquantity--;
   }
   if (strcmp(pTMPkill->cType, "PFG") == 0)
   {
      TypeQuantity.PFGquantity--;
   }
   if (strcmp(pTMPkill->cType, "PDFT") == 0)
   {
      TypeQuantity.PDFTquantity--;
   }
   if (strcmp(pTMPkill->cType, "PAM") == 0)
   {
      TypeQuantity.PAMquantity--;
   }
   if (strcmp(pTMPkill->cType, "PHDT") == 0)
   {
      TypeQuantity.PHDTquantity--;
   }
   if (strcmp(pTMPkill->cType, "PSU") == 0)
   {
      TypeQuantity.PSUquantity--;
   }
   if (strcmp(pTMPkill->cType, "PIO2") == 0)
   {
      TypeQuantity.PIO2quantity--;
   }
   if (strcmp(pTMPkill->cType, "PMB") == 0)
   {
      TypeQuantity.PMBquantity--;
   }

   GetIndexFromValue(iMainPanelHandle, iControlID, &iIndex, pTMPkill->iID);

   DeleteListItem(iMainPanelHandle, iControlID, iIndex, 1);

   if (strcmp(pTMPprev->cBenchName, pTMPkill->cBenchName) != 0)
   {
      pTMPprev->next = pTMPkill->next;
   }
   else
   {
      pFirstRessource = pTMPkill->next;
   }

   free(pTMPkill);

   InsertMenuItems();

   iNewDevAdded--;
   iDevicesFound--;

   return 0;
}

/******************************************************************************/
// END OF FILE
