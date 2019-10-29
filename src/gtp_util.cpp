/*  Copyright (C) 2013  Nithin Nellikunnu, nithin.nn@gmail.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */  

// Utility functions for gtp
#include <stdlib.h>
#include <list>
#include <arpa/inet.h>

#include "types.hpp"
#include "logger.hpp"
#include "macros.hpp"
#include "gtp_macro.hpp"
#include "gtp_types.hpp"
#include "gtp_util.hpp"

S8 g_gtpMsgName[GTPC_MSG_TYPE_MAX][GTP_MSG_NAME_LEN] = 
{
   "",
   "Echo Req",
   "Echo Rsp",
   "Version Not Supported Ind",
   "",
   "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "", "", "", "", "",
   "Create Sessn Req",
   "Create Sessn Rsp",
   "Modify Bearer Req",
   "Modify Bearer Rsp",
   "Delete Sessn Req",
   "Delete Sessn Rsp",
   "Change Notif Req",
   "Change Notif Rsp",
   "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "",
   "Modify Bearer Cmd",
   "Moidfy Bearer Fail Ind",
   "Delete Bearer Cmd",
   "Delete Bearer Fail Ind",
   "Bearer Res Cmd",
   "Bearer Res Fail Ind",
   "DL Data Notif Fail Ind"
   "Trace Sessn Activation",
   "Trace Sessn Deactivation",
   "Stop Paging Ind",
   "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "",
   "Create Bearer Req",
   "Create Bearer Rsp",
   "Update Bearer Req",
   "Update Bearer Rsp",
   "Delete Bearer Req",
   "Delete Bearer Rsp",
   "Delete PDN Conn Set Req",
   "Delete PDN Conn Set Rsp",
   "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "",
   "Identification Req",
   "Identification Rsp",
   "Cntxt Req",
   "Cntxt Rsp",
   "Cntxt Ack",
   "Fwd Reloc Req",
   "Fwd Reloc Rsp",
   "Fwd Reloc Compl Notif",
   "Fwd Reloc Compl Ack",
   "Fwd Access Cntxt Notif",
   "Fwd Access Cntxt Ack",
   "Reloc Cancel Req",
   "Reloc Cancel Rsp",
   "Cfg Transfer Tun",
   "", "", "", "", "", "", "",
   "Detach Notif",
   "Detach Ack",
   "CS Paging Ind",
   "RAN Info Relay",
   "Alert MME Notif",
   "Alert MME Ack",
   "UE Activity Notif",
   "UE Activity Ack",
   "", "", "",
   "Create Fwding Tun Req",
   "Create Fwding Tun Rsp",
   "Suspend Notif",
   "Suspend Ack",
   "Resume Notif",
   "Resume Ack",
   "Create IDF Tun Req",
   "Create IDF Tun Rsp",
   "Delete IDF Tun Req",
   "Delete IDF Tun Rsp",
   "Rel Access Bearers Req",
   "Rel Access Bearers Rsp",
   "", "", "", "",
   "DL Data Notif",
   "DL Data Notif Ack",
   "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "", "",
   "", "",
   "Update PDN Conn Set Req",
   "Update PDN Conn Set Rsp",
   "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "",
   "MBMS Sessn Start Req",
   "MBMS Sessn Start Rsp",
   "MBMS Sessn Update Req",
   "MBMS Sessn Update Rsp",
   "MBMS Sessn Stop Req",
   "MBMS Sessn Stop Rsp"
};


GtpMsgCategory_t g_gtpMsgCat[GTPC_MSG_TYPE_MAX] = 
{
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_CMD,
   GTP_MSG_CAT_CMD_FAIL,
   GTP_MSG_CAT_CMD,
   GTP_MSG_CAT_CMD_FAIL,
   GTP_MSG_CAT_CMD,
   GTP_MSG_CAT_CMD_FAIL,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_IND,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_NOTIF,
   GTP_MSG_CAT_ACK,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_INV,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP,
   GTP_MSG_CAT_REQ,
   GTP_MSG_CAT_RSP
};

S8 g_gtpIeName[GTP_IE_MAX][GTP_IE_NAME_LEN] = \
{
   "reserved",
   "imsi",
   "cause",
   "recovery",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "stn_sr",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "apn",
   "ambr",
   "ebi",
   "ip_addr",
   "mei",
   "msisdn",
   "indication",
   "pco",
   "paa",
   "bearer_qos",
   "flow_qos",
   "rat_type",
   "serving_network",
   "eps_bearer_tft",
   "tad",
   "uli",
   "fteid",
   "tmsi",
   "global_cn_id",
   "s103pdf",
   "s1udf",
   "delay",
   "bcontext",
   "charging_id",
   "charging_char",
   "trace_info",
   "bearer_flags",
   "reserved",
   "pdn_type",
   "pti",
   "drx_param",
   "ue_network_cap",
   "mm_context_gsm_key_trip",
   "mm_context_umts_key_used_cipher_quint",
   "mm_context_gsm_key_used_cipher_quint",
   "mm_context_umts_key_quint",
   "mm_context_eps_sec_context_quadr_quint",
   "mm_context_umts_key_quadr_quint",
   "pdn_connection",
   "pdu_numbers",
   "ptmsi",
   "ptmsi_signature",
   "hop_counter",
   "ue_time_zone",
   "trace_reference",
   "complete_request_message",
   "guti",
   "fcontainer",
   "fcause",
   "selected_plmn_id",
   "target_id",
   "reserved",
   "packet_flow_id",
   "rab_context",
   "source_rnc_pdcp_context_info",
   "udp_source_port_number",
   "apn_restriction",
   "selection_mode",
   "source_id",
   "reserved",
   "change_reporting_action",
   "fqcsid",
   "channel_needed",
   "emlpp_priority",
   "node_type",
   "fqdn",
   "ti",
   "mbms_session_duration",
   "mbms_service_area",
   "mbms_session_id",
   "mbms_flow_id",
   "mbms_ip_multicast_distribution",
   "mbms_distribution_acknowledge",
   "rfsp_index",
   "uci",
   "csg_info_reporting_action",
   "csg_id",
   "cmi",
   "service_indicator",
   "detach_type",
   "ldn",
   "reserved",
   "mbms_time_to_data_transfer",
   "reserved",
   "reserved",
   "reserved",
   "reserved",
   "tmgi",
   "additional_mm_context_for_srvcc",
   "additional_flags_for_srvcc",
   "reserved",
   "reserved",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare",
   "spare"
};

S8 g_gtpMsgXmlTag[GTPC_MSG_TYPE_MAX][GTP_MSG_XML_TAG_MAX_LEN] = \
{
   "",
   "ereq",
   "ersp",
   "vnsind",
   "",
   "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "", "", "", "", "",
   "csreq",
   "csrsp",
   "mbreq",
   "mbrsp",
   "dsreq",
   "dsrsp",
   "cnreq",
   "cnrsp"
   "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "",
   "mbcmd",
   "mbcmdfind",
   "dbcmd",
   "dbcmdfind",
   "brcmd",
   "brcmdfind",
   "tsact",
   "tsdact",
   "spind",
   "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "",
   "cbreq",
   "cbrsp",
   "ubreq",
   "ubrsp",
   "dbreq",
   "dbrsp",
   "dpcsreq",
   "dpcsrsp",
   "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "",
   "idreq",
   "idrsp",
   "creq",
   "crsp",
   "cack",
   "frreq",
   "frrsp",
   "frcnotif",
   "frcack",
   "facnotif",
   "facack",
   "rcreq",
   "rcrsp",
   "cttun",
   "", "", "", "", "", "", "",
   "dnotif",
   "dack",
   "cspind",
   "rirelay",
   "amnotif",
   "amack",
   "uanotif",
   "uaack",
   "", "", "",
   "cftreq",
   "cftrsp",
   "snotif",
   "sack",
   "rnotif",
   "rack",
   "citreq",
   "citrsp",
   "ditreq",
   "ditrsp",
   "rabreq",
   "rabrsp",
   "", "", "", "",
   "dldnotif",
   "dldnotifack",
   "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "", "",
   "", "",
   "upcsreq",
   "upcsrsp",
   "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "", "",
   "", "", "", "", "", "", "", "", "",
   "mssreq",
   "mssrsp",
   "msureq",
   "msursp",
   "msstreq",
   "msstrsp"
};

S8* gtpGetMsgName(GtpMsgType_t msgType)
{
   S8 *pMsgName = NULL;

   if (msgType <= GTPC_MSG_TYPE_MAX)
   {
      if (STRCMP(g_gtpMsgName[msgType], "") != 0)
      {
         pMsgName = g_gtpMsgName[msgType];
      }
   }

   return pMsgName;
}

GtpIeType_t gtpGetIeType(const S8   *pIeName)
{
   for (U32 ieType = GTP_IE_RESERVED; ieType < GTP_IE_MAX; ieType++)
   {
      if (strcasecmp(g_gtpIeName[ieType], pIeName) == 0)
      {
         return (GtpIeType_t)ieType;
      }
   }

   return GTP_IE_MAX;
}

GtpMsgType_t gtpGetMsgType(const S8 *pXmlMsgTag)
{
   for (U32 msgType = GTPC_MSG_TYPE_INVALID; msgType < GTPC_MSG_TYPE_MAX;
         msgType++)
   {
      if (strcasecmp(g_gtpMsgXmlTag[msgType], pXmlMsgTag) == 0)
      {
         return (GtpMsgType_t)msgType;
      }
   }

   return GTPC_MSG_TYPE_INVALID;
}

GtpMsgCategory_t gtpGetMsgCategory(GtpMsgType_t msgType)
{
   LOG_ENTERFN();

   GtpMsgCategory_t msgCat = GTP_MSG_CAT_INV;
   if (msgType <= GTPC_MSG_TYPE_MAX)
   {
      msgCat = g_gtpMsgCat[msgType]; 
   }

   LOG_EXITFN(msgCat);
}

PUBLIC U8 gtpCharToHex(U8 c)
{
   LOG_ENTERFN();

   U8 h = 0;
   switch (c)
   {
      case 'a':
         h = 0xa;
         break;
      case 'b':
         h = 0xb;
         break;
      case 'c':
         h = 0xc;
         break;
      case 'd':
         h = 0xd;
         break;
      case 'e':
         h = 0xe;
         break;
      case 'f':
         h = 0xf;
         break;
      default:
         h = GSIM_CHAR_TO_DIGIT(c);
         break;
   }
   
   LOG_EXITFN(h);
}

GtpLength_t gtpConvStrToHex(const Buffer *pBuf, U8 *pDst)
{
   LOG_ENTERFN();

   U32 begin = 0;
   U32 indx = 0;

   /* hex buffer string has odd len, so the first byte of hex buffer
    * will have 0 as High nibble
    */
   if (GSIM_IS_ODD(pBuf->len))
   {
      pDst[indx++] = 0x0f & gtpCharToHex(pBuf->pVal[0]);
      begin++;
   }

   for (U32 i = begin; i < pBuf->len; i += 2)               
   {                                                        
      U8 HNibble = gtpCharToHex(pBuf->pVal[i]); 
      U8 LNibble = gtpCharToHex(pBuf->pVal[i + 1]);     
      pDst[indx++] = (HNibble << 4) | (LNibble);
   }                                                        
                                                            
   LOG_EXITFN(indx);
}

GtpLength_t gtpConvStrToHex(const HexString *value, U8 *pDst)
{
   LOG_ENTERFN();

   U32 begin = 0;
   U32 indx = 0;

   /* hex buffer string has odd len, so the first byte of hex buffer
    * will have 0 as High nibble
    */
   const char* str = value->c_str();
   if (GSIM_IS_ODD(value->size()))
   {
      pDst[indx++] = 0x0f & gtpCharToHex(str[0]);
      begin++;
   }

   for (U32 i = begin; i < value->size(); i += 2)               
   {                                                        
      U8 HNibble = gtpCharToHex(str[i]); 
      U8 LNibble = gtpCharToHex(str[i + 1]);     
      pDst[indx++] = (HNibble << 4) | (LNibble);
   }                                                        
                                                            
   LOG_EXITFN(indx);
}

PUBLIC U32 gtpConvStrToU32(const S8 *pVal, U32 len)
{
   LOG_ENTERFN();

   S8 *tmp = NULL;
   S8 buf[GSIM_SIZE_32] = {'\0'};

   MEMCPY(buf, pVal, len);
   U32 v = strtoul(buf, &tmp, 10);

   LOG_EXITFN(v);
}

GtpIfType_t gtpConvStrToIfType(const S8 *pVal, U32 len)
{
   LOG_ENTERFN();
   
   GtpIfType_t ifType = (GtpIfType_t)gtpConvStrToU32(pVal, len);
   if (ifType >= GTP_IF_INF_INV)
   {
      ifType = GTP_IF_INF_INV;
      LOG_ERROR("Unrecognized Interface type string [%s]", pVal);
   }

   LOG_EXITFN(ifType);
}

IpAddr convIpStrToIpAddr(const S8* pIp, U32 len)
{
   LOG_ENTERFN();

   IpAddr ipAddr;
   S8     ip[GSIM_SIZE_32] = {'\0'};
   MEMCPY(ip, pIp, len);

   ipAddr.ipAddrType = IP_ADDR_TYPE_INV;
   if (STRFIND(ip, ":") != NULL)
   {
      RETVAL ret = inet_pton(AF_INET6, ip, (VOID *)(ipAddr.u.ipv6Addr.addr));
      if (0 == ret)
      {
         LOG_FATAL("Invalid IPv6 Address");
      }
      else
      {
         ipAddr.u.ipv6Addr.len = STRLEN(ip);
         ipAddr.ipAddrType = IP_ADDR_TYPE_V6;
      }
   }
   else
   {
      RETVAL ret = inet_pton(AF_INET, ip, (VOID *)&(ipAddr.u.ipv4Addr.addr));
      if (0 == ret)
      {
         LOG_FATAL("Invalid IPv4 Address");
      }
      else
      {
         ipAddr.u.ipv4Addr.addr = ntohl(ipAddr.u.ipv4Addr.addr);
         ipAddr.ipAddrType = IP_ADDR_TYPE_V4;
      }
   }

   LOG_EXITFN(ipAddr);
}

VOID decIeHdr(U8 *pBuf, GtpIeHdr *pHdr)
{
   LOG_ENTERFN();

   MEMSET((VOID *)pHdr, 0, sizeof(GtpIeHdr));
   GTP_DEC_IE_TYPE(pBuf, pHdr->ieType);
   GTP_DEC_IE_LEN(pBuf, pHdr->len);
   GTP_DEC_IE_INSTANCE(pBuf, pHdr->instance);

   LOG_EXITVOID();
}

PUBLIC VOID numericStrIncriment(S8 *pStr, U32 len)
{
   LOG_ENTERFN();

   U32 d = 0;
   U32 carry = 1;

   for (S32 i = len - 1; i >= 0; i--)
   {
      d = GSIM_CHAR_TO_DIGIT(pStr[i]) + carry;
      if (d > 9)
      {
         pStr[i] = GSIM_DIGIT_TO_CHAR(d % 10);
         carry = 1;
      }
      else
      {
         pStr[i] = GSIM_DIGIT_TO_CHAR(d);
         carry = 0;
      }
   }

   LOG_EXITVOID();
}

U32 encodeImsi(S8 *pImsiStr, U32 imsiStrLen, U8 *pBuf)
{
   LOG_ENTERFN();

   U32      indx = 0;
   U32      len = 0;

   /* Enocde even number of digits into hex buffer */
   for (indx = 0; indx < (imsiStrLen - 1); indx += 2)
   {
      pBuf[len++] = GSIM_CHAR_TO_DIGIT(pImsiStr[indx]) | \
            GSIM_CHAR_TO_DIGIT(pImsiStr[indx + 1]) << 4;
   }

   /* Encode the last digit into hex buffer */
   if (GSIM_IS_ODD(imsiStrLen))
   {
      pBuf[len] = GSIM_CHAR_TO_DIGIT(pImsiStr[imsiStrLen - 1]) | 0xf0;
      len++;
   }

   LOG_EXITFN(len);
}


/**
 * @brief 
 *    returns the pointer to imsi ie in GTP message buffer
 *
 * @return 
 *    returns the pointer to imsi ie in GTP message buffer
 */
PUBLIC U8* getImsiBufPtr(Buffer *pGtpcBuf)
{
   LOG_ENTERFN();

   U8          *pImsi = NULL;
   GtpIeHdr    ieHdr;
   GtpLength_t len = pGtpcBuf->len;
   U8          *pBuf = pGtpcBuf->pVal;

   if (GTP_CHK_T_BIT_PRESENT(pBuf))
   {
      len -= GTP_MSG_HDR_LEN;
      pBuf += GTP_MSG_HDR_LEN;
   }
   else
   {
      len -= GTP_MSG_HDR_LEN_WITHOUT_TEID;
      pBuf += GTP_MSG_HDR_LEN_WITHOUT_TEID;
   }

   while (len)
   {
      decIeHdr(pBuf, &ieHdr);
      if (ieHdr.ieType == GTP_IE_IMSI)
      {
         pImsi = pBuf;
         break;
      }

      len -= (ieHdr.len + GTP_IE_HDR_LEN);
      pBuf += (ieHdr.len + GTP_IE_HDR_LEN);
   }

   LOG_EXITFN(pImsi);
}

/**
 * @brief encodes PLMN ID into buffer based on encoding PLMN ID encoding
 *        in 23.003
 *
 * @param pPlmnId
 * @param pBuf
 *
 * @return 
 */
PUBLIC VOID gtpUtlEncPlmnId(GtpPlmnId_t *pPlmnId, U8* pBuf)
{
   LOG_ENTERFN();

   pBuf[0] = (pPlmnId->mcc[1] << 4) | pPlmnId->mcc[0];    

   if (pPlmnId->numMncDigits == 2)                                         
   {                                                              
      pBuf[1] = (0xf0 | pPlmnId->mcc[2]);                 
   }                                                              
   else                                                           
   {                                                              
      pBuf[1] = ((pPlmnId->mnc[2] << 4) | pPlmnId->mcc[2]);
   }                                                              

   pBuf[2] = ((pPlmnId->mnc[1] << 4) | pPlmnId->mnc[0]);   

   LOG_EXITVOID();
}

/**
 * @brief
 *    Returns name of IE string based on IE Type
 *
 * @param ieType
 *
 * @return 
 */
PUBLIC S8 *gtpGetIeName(GtpIeType_t ieType)
{
   return g_gtpIeName[ieType];
}
