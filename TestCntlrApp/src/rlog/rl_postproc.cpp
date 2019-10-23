
/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C++ source file
     Desc:     This file contains logging framework implementation.
     File:     postproc.cpp
     Sid:      lf_postproc.cpp@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:57:02 2014
     Prg:      Total eNB
   Auth:    Vikram Korde, Aug 2013

*********************************************************************21*/
///////////////////////////////////////////////////////////////////////////////
// @ author : Vikram Korde  
// @ description: This is source file  contains the implementaion of binary log
// postprocessor and has ability to connect to remote node and print live logs. 
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <algorithm>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <getopt.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "rl_interface.h"
#include "rl_rlog.h"

#define TEST_MODE

namespace cmdlinearg {
int g_port = 0;
std::string g_sFileDb;  /* File DB */
std::string g_sLogDb;   /* Log DB */
std::string g_sOutFile; /* Output file */
std::string g_sBinLogFile; /* Input binary log file */
std::string g_ipAddr;
}

typedef struct
{
  int lineno;
  std::string modName;
  std::string file;
  std::string logStr;

} LOG_INFO;

static struct option long_options[] =
{
   {"port",   required_argument,   0, 'p'},
   {"logdb",   required_argument,   0, 'l'},
   {"ofile",  required_argument,   0, 'o'},
   {"blog",   required_argument,   0, 'b'},
   {"ipaddr",   required_argument,   0, 'i'},
   {0, 0, 0, 0}
};

std::map<unsigned short, std::string> g_mFileInfo;
std::map<LOGID, LOG_INFO> g_mLogInfo;
FILE* g_fp=stderr;
U32 g_ttiCount = 0;
time_t g_basetimeSec;

void readCmdLineArgs(int argc,char **argv);
void printLogTime(LOGTIME & ltime);
void loadLogDb();
void printUsage();
void logHexDump(ARGDATA & log);
bool invalidLogId(LOGID logId);
void openLogFile(const char* file);
void logLevN(LOGDATA & log, LOG_INFO & logInfo, const char* fmtStr, ...);
void logLevS(LOGDATA & log, LOG_INFO & logInfo, const char* fmtStr, const char *logStr);
void logString(ARGDATA & log);
void logIntArg(ARG4DATA* log);
void logArgSpl(SPL_ARGDATA* log);
void processLogs(int fd, bool (*fpReadLog)(int, ARGDATA &));

bool readRemoteLogs(int sockfd, ARGDATA & log);
bool readFileLogs(int fd, ARGDATA & log);
int openBinLogFile();
int connectToLogServer();

///////////////////////////////////////////////////////////////////////////////////////////////////
// @arg[in] argc  - Number of arguments
// @arg[in] argv - Command line arguments
// This is main functions, which calls a function to parse command line arguments. Then it loads
// log metadata into memory. And then based on if its remote logging or binary log file parsing
// passes apropriate function pointer to read and convert logs.
///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  readCmdLineArgs(argc, argv);
  loadLogDb();

  if( !cmdlinearg::g_sBinLogFile.empty() ) 
  {
    if( !cmdlinearg::g_sOutFile.empty() )
    {
      openLogFile(cmdlinearg::g_sOutFile.c_str());

      processLogs(openBinLogFile(), readFileLogs);
      fclose(g_fp);
    }
  }

  if( cmdlinearg::g_port != 0 ) {

    if( !cmdlinearg::g_sOutFile.empty() ) {
      openLogFile(cmdlinearg::g_sOutFile.c_str());
    }
      

    processLogs(connectToLogServer(), readRemoteLogs);

    fclose(g_fp);
  }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] file - Input log file name
// This function opens the log file in write mode.
///////////////////////////////////////////////////////////////////////////////////////////////////
void openLogFile(const char* file)
{
   g_fp = fopen(file, "w+");
   
  if( g_fp == NULL ) 
  {
      fprintf(stderr, "Failed to open log file %s\n", file);
      _exit(0);
   }

   fprintf(stderr, "Log Output will be written in %s\n", file);
}

uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}


unsigned long EndianSwap32(unsigned long x)
{
    unsigned long y=0;
    y += (x & 0x000000FF)<<24;
    y += (x & 0xFF000000)>>24;
    y += (x & 0x0000FF00)<<8;
    y += (x & 0x00FF0000)>>8;
    return y;
}

void print_hex(const char* str, const U8 *p, int len)
{
  fprintf(stderr, "%s HEX \n", str);
  for(int i=0; i<len; i++ ) fprintf(stderr, "%d ", p[i]);
  fprintf(stderr, "\n");

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This function open the log file in binary mode and checks if file header is correct or not.
// It also sets the environment variable for given time zone in log file, so that time information
// is converted to correct time zone times.
///////////////////////////////////////////////////////////////////////////////////////////////////
int openBinLogFile()
{
  int fd = open(cmdlinearg::g_sBinLogFile.c_str(), O_RDONLY );

  if( fd == -1) {
      fprintf(stderr, "Failed to open log file %s\n", cmdlinearg::g_sBinLogFile.c_str());
    _exit(0);
  }

  FILE_HEADER fileHdr;

  int len = read(fd, (void*)&fileHdr, sizeof(FILE_HEADER));

  if( fileHdr.END_MARKER != 0xFFFF ) {
    fprintf(stderr, "Invalid file header\n");
    _exit(0);
  }

  fprintf(stderr, "FILE ENDIAN: %s\n", fileHdr.endianType == big_endian ? "BIG ENDIAN" : "LITTLE ENDIAN");
  fprintf(stderr, "TIME ZONE: %s\n", fileHdr.szTimeZone);

  setenv("TZ", fileHdr.szTimeZone, 1);
  tzset();

  if( fileHdr.endianType == big_endian ) {
  }
  g_basetimeSec = fileHdr.time_sec;
  return fd;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This function connects to remote application which is using binary logging framework. If 
// connection is failed log application exits.
///////////////////////////////////////////////////////////////////////////////////////////////////
int connectToLogServer()
{
  int sockfd;
  struct addrinfo hints;
  struct addrinfo *res = NULL;
  struct addrinfo *result = NULL;
  int errcode;
  char addrstr[100];
  void *ptr = NULL;
  struct sockaddr_in serv_addr;
  struct sockaddr_in6 serv_addr6;
  void *sockServAddr = NULL;
  int ai_family = AF_UNSPEC;
  int size = 0;

  /* ccpu00147898 fixes */
  memset(&hints, 0, sizeof(hints));
  memset((void*)&serv_addr, 0, sizeof(serv_addr));
  memset((void*)&serv_addr6, 0, sizeof(serv_addr6));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags |= AI_CANONNAME;

  errcode = getaddrinfo(cmdlinearg::g_ipAddr.c_str(), NULL, &hints, &res);
  if(errcode != 0)
  {
    perror ("getaddrinfo");
    return -1;
  }

  result = res;
  while(res)
  {
    inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);

    switch(res->ai_family)
    {
      case AF_INET:
        ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
        serv_addr.sin_addr = ((struct sockaddr_in *) res->ai_addr)->sin_addr;
        sockServAddr = &serv_addr;
        ai_family = res->ai_family; 
        serv_addr.sin_family = res->ai_family;
        serv_addr.sin_port = htons(cmdlinearg::g_port);
        size =  sizeof(serv_addr);
        break;
      case AF_INET6:
        ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
        sockServAddr = &serv_addr6; 
        /* Copy IPv6 address(16bytes) into the destination */ 
        memcpy((unsigned char*)serv_addr6.sin6_addr.s6_addr, (unsigned char *)
         &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr, 16);
        ai_family = res->ai_family;
        serv_addr6.sin6_family = res->ai_family;
        serv_addr6.sin6_port = htons(cmdlinearg::g_port);
        size =  sizeof(serv_addr6);
        break;
      default:
        sockServAddr = NULL;
        break;
    }

    if(ptr != NULL)
    {
       inet_ntop(res->ai_family, ptr, addrstr, 100);
       printf ("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
             addrstr, res->ai_canonname);
    }
    res = res->ai_next;
  }
 
  if(sockServAddr == NULL || size == 0)
  {
     fprintf(stderr, "Not able to parse server address\n");
     _exit(0);
  }

  if( (sockfd = socket(ai_family, SOCK_STREAM,0)) < 0 ) {
    fprintf(stderr, "Failed to create socket\n");
    _exit(0);
  }
  
  if( connect(sockfd, (const sockaddr*)sockServAddr, size) < 0 ) {
    perror("ERROR Connecting");
    _exit(0);
  }

  if(result != NULL)
  {
    freeaddrinfo(result);
  }
  return sockfd;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] sockfd - Socket file descriptor
// @paramp[in] log  - Log data buffer
// This function reads the log header and remaining log from socket descriptor. Will return false
// if socket operation fails.
///////////////////////////////////////////////////////////////////////////////////////////////////
bool readRemoteLogs(int sockfd, ARGDATA & log)
{
  int len;

  while( (len = recv(sockfd, (void*)&log.logData, RLOG_FIXED_LENGTH_BUFFER_SIZE, MSG_WAITALL)) == 0 );
  if( len < 0 ) {
    return false;
  }


  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] fd - input file descriptor
// @param[out] log - Log header 
// This function will read the log header and returns success if able to read.
///////////////////////////////////////////////////////////////////////////////////////////////////
bool readFileLogs(int fd, ARGDATA & log)
{
  int len = read(fd, (void*)&log.logData, sizeof(LOGDATA));

  if( len <= 0 ) {
    return false;
  }

#ifdef RLOG_MULTI_CIRCULAR_BUFFER
  if( log.logData.len && read(fd, (void*)log.buf, log.logData.len) <= 0 ) {
    return false;
  }
#else
   U16 size = RLOG_FIXED_LENGTH_BUFFER_SIZE - sizeof(LOGDATA);
//  if( log.logData.len && read(fd, (void*)log.buf, size) <= 0 ) {
  if( read(fd, (void*)log.buf, size) <= 0 ) {
    return false;
  }
#endif

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log1 - LOG 
// @param[in] log2 - Second Log
// This function compares the TTI of two consecutive logs.
///////////////////////////////////////////////////////////////////////////////////////////////////
bool cmp_tti(ARGDATA & log1, ARGDATA & log2)
{
  return log2.logData.logTime.ms_tti > log1.logData.logTime.ms_tti ? true : false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - Log data
// This function calculates the time based on TTI & time reference associated with it. And thne 
// calls the function to print logs in aprpriate text format.
///////////////////////////////////////////////////////////////////////////////////////////////////
void printLog(ARGDATA & log)
{

  if( invalidLogId(log.logData.logId) )
    return;
  
  switch( log.logData.argType )
  {
    case LOG_ARG_INT:
      logIntArg((ARG4DATA*)&log);
      break;

    case  LOG_ARG_STR:
      logString(log);
      break;

    case LOG_ARG_HEX:
      logHexDump(log);
      break;

    case LOG_ARG_SPL:
      logArgSpl((SPL_ARGDATA*)&log);
      break;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] fd - File or socket descriptor
// @param[in] fpReadLog - Function pointer which reads either file or socket based log
// This function reads the binary log file and does sorting of logs based on TTI and then calls the
// function to print it
///////////////////////////////////////////////////////////////////////////////////////////////////
void processLogs(int fd, bool (*fpReadLog)(int, ARGDATA &))
{
  ARGDATA log;
  bool bSortingRequired = false, bStartBuffering = false;
  std::list<ARGDATA> logList;

  while((*fpReadLog)(fd, log)) 
  {
    if( log.logData.logId == L_TIME_DELIMITER ) 
    {
      bStartBuffering = (bStartBuffering == false) ? true : false;
      if( bStartBuffering == true ) {
        bSortingRequired = true;
        continue;
      }
    }

    if( bStartBuffering ) {
      logList.push_back(log);
      continue;
    }
  
    if( bSortingRequired ) {
      logList.sort(cmp_tti);  
      std::for_each(logList.begin(), logList.end(), printLog);
      logList.clear();
      bSortingRequired = false;
      bStartBuffering = false;
      continue;
    }

    printLog(log);
  }

  /* connection was closed due to some error, but we still have some logs */
  if( bStartBuffering && !logList.empty() ) 
  {
    logList.sort(cmp_tti);  
    std::for_each(logList.begin(), logList.end(), printLog);
  }

  close(fd);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - LOG Data
// This function convert binary log with integer data type into text format.
///////////////////////////////////////////////////////////////////////////////////////////////////
void logIntArg(ARG4DATA* log)
{
#ifdef TEST_MODE
//  printf("LOG ARG: INT, LEVEL: %s\n", g_logStr[log->logData.logLevel]);
#endif
  
  LOG_INFO & logInfo = g_mLogInfo[log->logData.logId];
  logLevN(log->logData,logInfo,logInfo.logStr.c_str(),log->arg1,log->arg2,log->arg3,log->arg4); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - LOG Data
// This function converts binary log containg string into text format.
///////////////////////////////////////////////////////////////////////////////////////////////////
void logString(ARGDATA & log)
{
#ifdef TEST_MODE
//  printf("LOG ID %ld LOG ARG STRING, LEVEL: %s\n", log.logData.logId, g_logStr[log.logData.logLevel]);
#endif
  
  LOG_INFO & logInfo = g_mLogInfo[log.logData.logId];
  logLevS(log.logData, logInfo, logInfo.logStr.c_str(), log.buf); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - LOG Data
// This function converts binary log containg hex dump into readable text format.
///////////////////////////////////////////////////////////////////////////////////////////////////
void logHexDump(ARGDATA & log)
{
#ifdef TEST_MODE
//  printf("LOG ARG HEX, LEVEL: %s\n", g_logStr[log.logData.logLevel]);
#endif
  
  LOG_INFO & logInfo = g_mLogInfo[log.logData.logId];

  char szHex[MAX_LOG_BUF_SIZE*3];
   hextostr(szHex, log.buf, log.logData.len);

  logLevN(log.logData, logInfo, logInfo.logStr.c_str(), szHex); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - LOG Data
// @param[in] logInfo - Log information structure reference
// @param[in] fmtStr - Formatted string
// This function prints log into console or log file.
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLevN(LOGDATA & log, LOG_INFO & logInfo, const char* fmtStr, ...)
{
   va_list argList;
  const char* file = logInfo.file.c_str();

  printLogTime(log.logTime);
   fprintf(g_fp, "[%s]%s:%d\n%s:", logInfo.modName.c_str(), file, logInfo.lineno, g_logStr[log.logLevel]);

   va_start(argList,fmtStr);
   vfprintf(g_fp, fmtStr, argList);
   va_end(argList);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - LOG Data
// @param[in] logInfo - Log information structure reference
// @param[in] fmtStr - Formatted string
// This function prints string log into console or log file.
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLevS(LOGDATA & log, LOG_INFO & logInfo, const char* fmtStr, const char* logStr)
{
   const char* file = logInfo.file.c_str();
   std::string argStr(logStr, log.len);
   printLogTime(log.logTime);
   fprintf(g_fp, "[%s]%s:%d\n%s:", logInfo.modName.c_str(), file, logInfo.lineno, g_logStr[log.logLevel]);
   fprintf(g_fp, fmtStr, argStr.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - LOG Data
// @param[in] logInfo - Log information structure reference
// @param[in] fmtStr - Formatted string
// This function prints log into console or log file.
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLevSpl(SPL_ARGDATA* log, LOG_INFO & logInfo, const char* fmtStr, ...)
{
   va_list argList;
  const char* file = logInfo.file.c_str();

  printLogTime(log->logData.logTime);
   fprintf(g_fp, "[%s]%s:%d\n%s:%s:%d:", logInfo.modName.c_str(), file, logInfo.lineno, g_logStr[log->logData.logLevel], g_splStr[log->splEnum], log->splArg);

   va_start(argList,fmtStr);
   vfprintf(g_fp, fmtStr, argList);
   va_end(argList);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] log - LOG Data
// This function converts binary log with special arguments into text format.
///////////////////////////////////////////////////////////////////////////////////////////////////
void logArgSpl(SPL_ARGDATA* log)
{
#ifdef TEST_MODE
//  printf("LOG ARG SPL, LEVEL: %s\n", g_logStr[log->logData.logLevel]);
#endif
  LOG_INFO & logInfo = g_mLogInfo[log->logData.logId];
  const char* file = logInfo.file.c_str();

  logLevSpl(log, logInfo, logInfo.logStr.c_str(),log->arg1, log->arg2, log->arg3, log->arg4);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] ltime - Log time
// This function prints log time using standard c formating function fprintf
///////////////////////////////////////////////////////////////////////////////////////////////////
void printLogTime(LOGTIME & ltime)
{
  struct tm* tm;
  time_t curTimeSec;
  U32 secElapsedFromBeg;
  U32 ttiNum; 
  U32 miliseconds;

  ttiNum = ltime.ms_tti;
  secElapsedFromBeg = ttiNum/1000;
  miliseconds = ttiNum%1000;
  curTimeSec   = g_basetimeSec + secElapsedFromBeg;

  /* Obtain the time of day, and convert it to a tm struct. --*/
  tm = localtime (&curTimeSec);

  if(NULL != tm) 
   {
      fprintf(g_fp,"[%d-%d-%d %d:%d:%d.%03d]", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900,
            tm->tm_hour, tm->tm_min,tm->tm_sec,miliseconds);
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] logId - Log id which is unique to each log
// This function checks if the given log id is valid based on the logdb information loaded into 
// memory.
///////////////////////////////////////////////////////////////////////////////////////////////////
bool invalidLogId(LOGID logId)
{
   /* if this is a time reference this is valid log */
   if( g_mLogInfo.find(logId) == g_mLogInfo.end() )
   {
      if(logId != L_TIME_REFERENCE)
      {
         fprintf(stderr, "Invalid log id %d\n",logId);
      }
      return true;
   }
   return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This function parse and reads the logdb file. Extracts the information and stores into map data
// structure.
///////////////////////////////////////////////////////////////////////////////////////////////////
void loadLogDb()
{
  std::ifstream logdb(cmdlinearg::g_sLogDb.c_str());

  if(logdb.is_open() == false) {
    fprintf(stderr, "Failed to open file %s\n", cmdlinearg::g_sLogDb.c_str());
    _exit(0);
  }

  LOGID logId; LOG_INFO logInfo;
  std::string line;
   std::string & lstr = logInfo.logStr;
  
  while( getline(logdb, line) )
  {
    std::istringstream iss(line);
    int pos = 0, newpos=0;

    logId = atol( line.substr(pos, newpos=line.find(';', pos)).c_str() );

    pos = newpos+1;
    logInfo.lineno = atol( line.substr(pos, (newpos=line.find(';', pos)) - pos).c_str() );

    pos = newpos+1;
    logInfo.modName = line.substr(pos, (newpos=line.find(';', pos)) - pos);

    pos = newpos+3;
    logInfo.file = line.substr(pos, (newpos=line.find('\"', pos)) - pos);

      pos=line.find('\"',newpos+1) + 1;
    logInfo.logStr = line.substr(pos, (newpos=line.find_last_of("\"", pos)) - pos);
      lstr.erase(std::remove(lstr.begin(),lstr.end(),'\"')++,lstr.end());


#ifdef TEST_MODE_0
    std::cout << "LOG Id:" << logId << " FILE:" << logInfo.file << " lineno:" << logInfo.lineno;
    std::cout << " MOD Name: " << logInfo.modName << std::endl;
    std::cout << "LOG STR:[" << logInfo.logStr << "]" <<  std::endl;
#endif

    logInfo.logStr+= "\n\n";

    g_mLogInfo[logId] = logInfo;
  }

  logdb.close();

  logInfo.file = "NULL";
  logInfo.lineno = 0;
  logInfo.modName = "RLOG";
  logInfo.logStr =  RLOG_SEGFAULT_STR; 
  g_mLogInfo[L_SIGSEGV] = logInfo;
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @arg[in] argc  - Number of arguments
// @arg[in] argv - Command line arguments
// This function parses the command line input parameters.
///////////////////////////////////////////////////////////////////////////////////////////////////
void readCmdLineArgs(int argc,char **argv)
{
  using namespace cmdlinearg;
   /* getopt_long stores the option index here */
   int c, option_index = 0;

   while(  (c = getopt_long(argc, argv, "p:f:l:o:b:i:", long_options,&option_index)) != -1 )
   {
      switch(c)
       {
           case 'p':
                std::cout<<"option -p with value = " << optarg << std::endl;
                cmdlinearg::g_port = atoi(optarg);
                break;
           case 'f':
                std::cout<<"option -f with value = "<< optarg << std::endl;
                cmdlinearg::g_sFileDb = optarg;
                break;
           case 'l':
                std::cout<<"option -l with value = "<< optarg << std::endl;
                cmdlinearg::g_sLogDb = optarg;
                break;
           case 'o': 
                std::cout<<"option -o with value = " << optarg << std::endl;
                cmdlinearg::g_sOutFile = optarg;
                break;
           case 'b': 
                std::cout<<"option -b with value = " << optarg << std::endl;
                cmdlinearg::g_sBinLogFile = optarg;
                break;
           case 'i': 
                std::cout<<"option -i with value = " << optarg << std::endl;
                cmdlinearg::g_ipAddr = optarg;
                break;
        defult:
          std::cout << "Invalid arguments" << std::endl;
          exit(0);
    }
  }

//  if( g_port == 0 && g_sBinLogFile.empty() )
//    printUsage();

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This functin prints the binary log application usage.
///////////////////////////////////////////////////////////////////////////////////////////////////
void printUsage()
{
  printf("Usage: postproc [-f <filedb> ] [-l <logdb>] [-b <binlog> | -p <port> ] [-o <outfile>] \n");
  printf("\t[--filedb | -p <input file db > ]\n");
  printf("\t[--logdb  | -l <input log db > ]\n");
  printf("\t[--binlog | -b <input binary log file> ]\n");
  printf("\t[--ofile  | -o <output text log file> ]\n");
  printf("\t[--port   | -p <port number> ]\n");
  _exit(0);
}

