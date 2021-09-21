/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  EDIT                             1       /* callback function: HideOwnPanel */
#define  EDIT_BENCHNAME                   2       /* control type: string, callback function: (none) */
#define  EDIT_DESCRIPTION                 3       /* control type: string, callback function: (none) */
#define  EDIT_TYPE                        4       /* control type: string, callback function: (none) */
#define  EDIT_RESSOURCE                   5       /* control type: string, callback function: (none) */
#define  EDIT_DRIVERDLL                   6       /* control type: string, callback function: (none) */
#define  EDIT_SELECTDRIVER                7       /* control type: command, callback function: SelectDriver */
#define  EDIT_DRIVERPREFIX                8       /* control type: string, callback function: (none) */
#define  EDIT_DRIVEROPTION                9       /* control type: string, callback function: (none) */
#define  EDIT_SFTDLL                      10      /* control type: string, callback function: (none) */
#define  EDIT_SFTPREFIX                   11      /* control type: string, callback function: (none) */
#define  EDIT_BAUDRATE                    12      /* control type: ring, callback function: (none) */
#define  EDIT_PARITY                      13      /* control type: ring, callback function: (none) */
#define  EDIT_HANDSHAKE                   14      /* control type: ring, callback function: (none) */
#define  EDIT_DATABITS                    15      /* control type: ring, callback function: (none) */
#define  EDIT_STOPBITS                    16      /* control type: ring, callback function: (none) */
#define  EDIT_HIDE                        17      /* control type: radioButton, callback function: ChangeHide */
#define  EDIT_OK                          18      /* control type: command, callback function: ApplyChanges */
#define  EDIT_ECS                         19      /* control type: command, callback function: QuitWithoutSaving */
#define  EDIT_DELETEDEV                   20      /* control type: radioButton, callback function: (none) */
#define  EDIT_TEXTMADDED                  21      /* control type: textMsg, callback function: (none) */

#define  EXPORT                           2       /* callback function: HideOwnPanel */
#define  EXPORT_EXPORTDEV                 2       /* control type: listBox, callback function: DevListBox */
#define  EXPORT_EXPORTSYSCH               3       /* control type: radioButton, callback function: (none) */
#define  EXPORT_EXPORTABUS                4       /* control type: radioButton, callback function: DimmSysChExp */
#define  EXPORT_EXPORTALLCH               5       /* control type: radioButton, callback function: (none) */
#define  EXPORT_AUTOCOUPLING              6       /* control type: radioButton, callback function: (none) */
#define  EXPORT_EXPORT                    7       /* control type: command, callback function: ExportPhysical */
#define  EXPORT_DISCARD                   8       /* control type: command, callback function: Discard */
#define  EXPORT_BENCHNAME                 9       /* control type: string, callback function: (none) */

#define  PANEL                            3       /* callback function: PanelCallback */
#define  PANEL_STARTSCAN                  2       /* control type: command, callback function: StartScan */
#define  PANEL_PXIDEVICES                 3       /* control type: listBox, callback function: ChangeValues */
#define  PANEL_CANDEVICES                 4       /* control type: listBox, callback function: ChangeValues */
#define  PANEL_ASRLDEVICES                5       /* control type: listBox, callback function: ChangeValues */
#define  PANEL_GPIBDEVICES                6       /* control type: listBox, callback function: ChangeValues */
#define  PANEL_DAQDEVICES                 7       /* control type: listBox, callback function: ChangeValues */
#define  PANEL_STARTEXPORT                8       /* control type: command, callback function: StartExport */
#define  PANEL_PXI_LED                    9       /* control type: LED, callback function: (none) */
#define  PANEL_CAN_LED                    10      /* control type: LED, callback function: (none) */
#define  PANEL_ASRL_LED                   11      /* control type: LED, callback function: (none) */
#define  PANEL_GPIB_LED                   12      /* control type: LED, callback function: (none) */
#define  PANEL_DAQ_LED                    13      /* control type: LED, callback function: (none) */
#define  PANEL_CHECKBOX_PHYINI            14      /* control type: radioButton, callback function: WantPhyIni */
#define  PANEL_CHECKBOX_APPINI            15      /* control type: radioButton, callback function: WantAppIni */
#define  PANEL_TEXTMSG_EXPORT             16      /* control type: textMsg, callback function: (none) */
#define  PANEL_CHECKBOX_TSTSEQ            17      /* control type: radioButton, callback function: WantTstSeq */
#define  PANEL_STATUS                     18      /* control type: textMsg, callback function: (none) */
#define  PANEL_STATUS_2                   19      /* control type: textMsg, callback function: (none) */
#define  PANEL_STATUS_3                   20      /* control type: textMsg, callback function: (none) */
#define  PANEL_STATUS_4                   21      /* control type: textMsg, callback function: (none) */
#define  PANEL_STATUS_5                   22      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG                    23      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  24      /* control type: textMsg, callback function: (none) */
#define  PANEL_TITEL2                     25      /* control type: textMsg, callback function: (none) */

#define  PANEL_2                          4
#define  PANEL_2_NUMERICSLIDE             2       /* control type: scale, callback function: (none) */

#define  PANEL_3                          5
#define  PANEL_3_TOGGLEBUTTON             2       /* control type: textButton, callback function: EnableSAD */
#define  PANEL_3_NUMERICKNOB              3       /* control type: scale, callback function: (none) */
#define  PANEL_3_COMMANDBUTTON            4       /* control type: command, callback function: CloseSAD */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENU                             1
#define  MENU_FILE                        2
#define  MENU_FILE_OPENPHYSICAL           3       /* callback function: OpenPhysicalIni */
#define  MENU_FILE_SAVEPHYS               4       /* callback function: SavePhysicalIni */
#define  MENU_FILE_SEPARATOR              5
#define  MENU_FILE_QUIT                   6       /* callback function: QuitProgramm */
#define  MENU_EDIT                        7
#define  MENU_EDIT_NEWSCAN                8       /* callback function: NewScan */
#define  MENU_EDIT_SEPARATOR_3            9
#define  MENU_EDIT_EDIT                   10
#define  MENU_EDIT_ADDDEV                 11
#define  MENU_EDIT_ADDDEV_SUBMENU         12
#define  MENU_EDIT_ADDDEV_ADDPXI          13      /* callback function: AddPXIDevice */
#define  MENU_EDIT_ADDDEV_ADDCAN          14      /* callback function: AddCANDevice */
#define  MENU_EDIT_ADDDEV_ADDASRL         15      /* callback function: AddASRLDevice */
#define  MENU_EDIT_ADDDEV_ADDGPIB         16      /* callback function: AddGPIBDevice */
#define  MENU_EDIT_ADDDEV_ADDDAQ          17      /* callback function: AddDAQdevice */
#define  MENU_EDIT_ADDDEV_DELALLMANADDDEV 18      /* callback function: DeleteAllManullayAddedDev */
#define  MENU_OPTIONS                     19
#define  MENU_OPTIONS_GIBPSAD             20      /* callback function: ChangeSecAdress */
#define  MENU_OPTIONS_GIBPEOS             21
#define  MENU_OPTIONS_GIBPEOS_SUBMENU     22
#define  MENU_OPTIONS_GIBPEOS_CR          23      /* callback function: ChangeEOS */
#define  MENU_OPTIONS_GIBPEOS_LF          24      /* callback function: ChangeEOS */
#define  MENU_OPTIONS_GIBPEOS_NONE        25      /* callback function: ChangeEOS */
#define  MENU_OPTIONS_GIBPTIMEOUT         26
#define  MENU_OPTIONS_GIBPTIMEOUT_SUBMENU 27
#define  MENU_OPTIONS_GIBPTIMEOUT_NOLIMIT 28      /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB10USEC 29     /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB30USEC 30     /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB100USEC 31    /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB300USEC 32    /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB1MSEC 33      /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB3MSEC 34      /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB10MSEC 35     /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB30MSEC 36     /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB100MSEC 37    /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB300MSEC 38    /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB1SEC  39      /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB3SEC  40      /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB10SEC 41      /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB30SEC 42      /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB100SEC 43     /* callback function: ChangeTimeOut */
#define  MENU_OPTIONS_GIBPTIMEOUT_IB300SEC 44     /* callback function: ChangeTimeOut */
#define  MENU_HELP                        45
#define  MENU_HELP_HELP                   46      /* callback function: OpenHelp */
#define  MENU_HELP_SEPARATOR_2            47
#define  MENU_HELP_ABOUT                  48      /* callback function: OpenSplash */


     /* Callback Prototypes: */

void CVICALLBACK AddASRLDevice(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK AddCANDevice(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK AddDAQdevice(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK AddGPIBDevice(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK AddPXIDevice(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ApplyChanges(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK ChangeEOS(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ChangeHide(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK ChangeSecAdress(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK ChangeTimeOut(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ChangeValues(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CloseSAD(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK DeleteAllManullayAddedDev(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK DevListBox(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DimmSysChExp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Discard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EnableSAD(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExportPhysical(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK HideOwnPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK NewScan(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OpenHelp(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OpenPhysicalIni(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OpenSplash(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK PanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK QuitProgramm(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK QuitWithoutSaving(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK SavePhysicalIni(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK SelectDriver(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartExport(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartScan(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WantAppIni(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WantPhyIni(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WantTstSeq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
