#include "pharovm/pharo.h"
#include <sys/stat.h>

#ifndef WIN64
#include <libgen.h>
#include <sys/param.h>

#else
#include <Windows.h>
#endif

#include <signal.h>

char vmName[FILENAME_MAX] = {0};
char imageName[FILENAME_MAX] = {0};
char vmFullPath[FILENAME_MAX] = {0};
char vmPath[FILENAME_MAX] = {0};

#if __APPLE__
	void fillApplicationDirectory(char* vmPath);
#endif

#ifdef WIN64
BOOL fIsConsole = 1;
#endif


void *os_exports[][3]=
{
    { 0, 0, 0 }
};

static const char* systemSearchPaths[] = {
#ifdef WIN64
#endif
#if defined(__linux__) || defined(unix) || defined(__APPLE__)
	"./",
	"/usr/local/lib/",
    "/usr/lib/",
    "/lib/",
#   if defined(__linux__)
#       if defined(__i386__)
    "/usr/local/lib/i386-linux-gnu/",
    "/usr/lib/i386-linux-gnu/",
    "/lib/i386-linux-gnu/",
#       elif defined(__x86_64__)
    "/usr/local/lib/x86_64-linux-gnu/",
    "/usr/lib/x86_64-linux-gnu/",
    "/lib/x86_64-linux-gnu/",
#       endif
#   endif
#endif
    NULL
};

char** pluginPaths = NULL;
char* emptyPaths[] = {NULL};


EXPORT(char*) getSourceVersion(){
	return VM_BUILD_SOURCE_STRING;
}

EXPORT(char*) getVMVersion(){
	return VM_BUILD_STRING;
}

char * GetAttributeString(sqInt id)
{
    if (id < 0)	/* VM argument */
    {
        if (-id  < getVMArgumentCount()){
        	return getVMArgument(-id);
        }
        success(false);
        return "";
    }

    switch (id)
    {
    case 0:
        return vmFullPath;
    case 1:
        return getImageName();
    case 1001:
        /* OS type: "unix", "win32", "mac", ... */
        return OS_TYPE;
    case 1002:
        /* OS name: e.g. "solaris2.5" on unix, "win95" on win32, ... */
        return VM_TARGET_OS;
    case 1003:
        /* processor architecture: e.g. "68k", "x86", "PowerPC", ...  */
        return VM_TARGET_CPU;
    case 1004:
        /* Interpreter version string */
        return  (char *)interpreterVersion;
    case 1006:
        /* vm build string */
        return getVMVersion();
#if STACKVM
    case 1007: { /* interpreter build info */
        extern char *__interpBuildInfo;
        return __interpBuildInfo;
    }
# if COGVM
    case 1008: { /* cogit build info */
        extern char *__cogitBuildInfo;
        return __cogitBuildInfo;
    }
# endif
#endif

    case 1009: /* source tree version info */
        return getSourceVersion();

    default:
        if ((id - 2) < getImageArgumentCount())
            return getImageArgument(id - 2);
    }
    success(false);
    return "";
}

sqInt attributeSize(sqInt id)
{
    return strlen(GetAttributeString(id));
}

sqInt getAttributeIntoLength(sqInt id, sqInt byteArrayIndex, sqInt length)
{
    if (length > 0)
        strncpy(pointerForOop(byteArrayIndex), GetAttributeString(id), length);
    return 0;
}

/**
 * Returns the VM Name
 */
EXPORT(char*) getVMName(){
	return vmName;
}

/**
 * Sets the VMName.
 * It copies the parameter to internal storage.
 */
void setVMName(const char* name){
	strcpy(vmName, name);
}

char* getImageName(){
	return imageName;
}

/**
 * Sets the ImageName.
 * It copies the parameter to internal storage.
 */
void setImageName(const char* name){
	strcpy(imageName, name);
}

/**
 * Sets the Full VM Path.
 * It copies the parameter to internal storage.
 */
EXPORT(void) setVMPath(const char* name){
	strcpy(vmFullPath, name);

	int bufferSize = strlen(name) + 1;
	char* tmpBasedir = alloca(bufferSize);

#if __APPLE__
	fillApplicationDirectory(vmPath);

#else
	getBasePath(name, tmpBasedir, bufferSize);

	strcpy(vmPath, tmpBasedir);
#endif
}

sqInt vmPathSize(void){
    return strlen(vmPath);
}

sqInt vmPathGetLength(sqInt sqVMPathIndex, sqInt length){
    char *stVMPath= pointerForOop(sqVMPathIndex);
    int count;

    count = strlen(vmPath);
    count = (length < count) ? length : count;

    /* copy the file name into the Squeak string */
    memcpy(stVMPath, vmPath, count);

    return count;
}

sqInt imageNameGetLength(sqInt sqImageNameIndex, sqInt length){
    char *sqImageName = pointerForOop(sqImageNameIndex);
    int count;

    count= strlen(imageName);
    count= (length < count) ? length : count;

    /* copy the file name into the Squeak string */
    memcpy(sqImageName, imageName, count);

    return count;
}

sqInt imageNamePutLength(sqInt sqImageNameIndex, sqInt length){
    char *sqImageName= pointerForOop(sqImageNameIndex);
    int count;

    count = (length >= sizeof(imageName)) ? sizeof(imageName) - 1 : length;

    /* copy the file name into a null-terminated C string */
    memcpy(imageName, sqImageName, count);
    imageName[count] = 0;

    return count;
}

sqInt
imageNameSize(void)
{
    return strlen(imageName);
}

int vmParamsCount = 0;
int imageParamsCount = 0;

char** vmParams = NULL;
char** imageParams = NULL;

int getVMArgumentCount(){
	return vmParamsCount;
}

char* getVMArgument(int index){
	if(vmParamsCount <= index)
		return NULL;

	return vmParams[index];
}

int getImageArgumentCount(){
	return imageParamsCount;
}

char* getImageArgument(int index){
	if(imageParamsCount <= index)
		return NULL;

	return imageParams[index];
}

static void
copyParams(int newCount, const char** new, int* oldCount, char*** old){

	//Releasing the old params
	if(*oldCount > 0){
		for(int i=0; i < *oldCount; i++){
			free((*old)[i]);
		}
		free(*old);
		*oldCount = 0;
	}

	if(newCount==0) return;

	*oldCount = newCount;
	*old = (char**)malloc(sizeof(char*) * newCount);

	for(int i=0; i < newCount; i++){
		(*old)[i] = malloc(strlen(new[i])+1);
		strcpy((*old)[i], new[i]);
	}
}

void
setPharoCommandLineParameters(const char** newVMParams, int newVMParamsCount, const char** newImageParams, int newImageParamsCount){
	copyParams(newVMParamsCount, newVMParams, &vmParamsCount, &vmParams);
	copyParams(newImageParamsCount, newImageParams, &imageParamsCount, &imageParams);
}


char** getSystemSearchPaths(){
	return (char**)systemSearchPaths;
}

char** getPluginPaths(){
	if(pluginPaths == NULL) {
		return (char**) emptyPaths;
	}
	return (char**) pluginPaths;
}

sqInt
ioExitWithErrorCode(int errorCode)
{
    exit(errorCode);
}

/* New filename converting function; used by the interpreterProxy function
  ioFilenamefromStringofLengthresolveAliases. Most platforms can ignore the
  resolveAlias boolean - it seems to only be of use by OSX but is crucial there.
*/
sqInt
sqGetFilenameFromString(char * aCharBuffer, char * aFilenameString, sqInt filenameLength, sqInt resolveAlias)
{
    int numLinks= 0;
    struct stat st;

    memcpy(aCharBuffer, aFilenameString, filenameLength);
    aCharBuffer[filenameLength]= 0;

#ifndef WIN64
    if (resolveAlias)
    {
        for (;;)	/* aCharBuffer might refer to link or alias */
        {
            if (!lstat(aCharBuffer, &st) && S_ISLNK(st.st_mode))	/* symlink */
            {
                char linkbuf[PATH_MAX+1];
                if (++numLinks > MAXSYMLINKS)
                    return -1;	/* too many levels of indirection */

	            filenameLength= readlink(aCharBuffer, linkbuf, PATH_MAX);
	            if ((filenameLength < 0) || (filenameLength >= PATH_MAX))
                    return -1;	/* link unavailable or path too long */

	            linkbuf[filenameLength]= 0;

	            if (filenameLength > 0 && *linkbuf == '/') /* absolute */
	               strcpy(aCharBuffer, linkbuf);
	            else {
                    char *lastSeparator = strrchr(aCharBuffer,'/');
                    char *append = lastSeparator ? lastSeparator + 1 : aCharBuffer;
                    if (append - aCharBuffer + strlen(linkbuf) > PATH_MAX)
                        return -1; /* path too long */
                    strcpy(append,linkbuf);
	            }
                continue;
            }

	#if defined(DARWIN)
            if (isMacAlias(aCharBuffer))
            {
                if ((++numLinks > MAXSYMLINKS) || !resolveMacAlias(aCharBuffer, aCharBuffer, PATH_MAX))
                    return -1;		/* too many levels or bad alias */
                continue;
            }
	#endif

	        break;			/* target is no longer a symlink or alias */
        }
    }
#endif
    return 0;
}

#ifdef DARWIN
#include macAlias.c
#endif


#ifndef bzero

//We have to provide a bzero implementation for windows as the Cog code depends on it.
void bzero(void *s, size_t n){
	memset(s, 0, n);
}
#endif

#ifdef COGVM
/*
 * Cog has already captured CStackPointer  before calling this routine.  Record
 * the original value, capture the pointers again and determine if CFramePointer
 * lies between the two stack pointers and hence is likely in use.  This is
 * necessary since optimizing C compilers for x86 may use %ebp as a general-
 * purpose register, in which case it must not be captured.
 */
int
isCFramePointerInUse()
{
	extern unsigned long CStackPointer, CFramePointer;
	extern void (*ceCaptureCStackPointers)(void);
	unsigned long currentCSP = CStackPointer;

	currentCSP = CStackPointer;
	ceCaptureCStackPointers();
	assert(CStackPointer < currentCSP);
	return CFramePointer >= CStackPointer && CFramePointer <= currentCSP;
}
#endif // COGVM

/* Answer an approximation of the size of the redzone (if any).  Do so by
 * sending a signal to the process and computing the difference between the
 * stack pointer in the signal handler and that in the caller. Assumes stacks
 * descend.
 */

static char * volatile p = 0;


#ifdef siginfo_t
	static void sighandler(int sig, siginfo_t *info, void *uap) { p = (char *)&sig; }
#else
	static void sighandler(int sig) { p = (char *)&sig; }
#endif

#ifndef WIN64
static sqInt min(int x, int y) { return (x < y) ? x : y; }
static sqInt max(int x, int y) { return (x > y) ? x : y; }
#endif

static int getRedzoneSize()
{
#if defined(SIGPROF) /* cygwin */
	struct sigaction handler_action, old;
	handler_action.sa_sigaction = sighandler;
	handler_action.sa_flags = SA_NODEFER | SA_SIGINFO;
	sigemptyset(&handler_action.sa_mask);
	(void)sigaction(SIGPROF, &handler_action, &old);

	do kill(getpid(),SIGPROF); while (!p);
	(void)sigaction(SIGPROF, &old, 0);
	return (int)min((usqInt)&old,(usqInt)&handler_action) - sizeof(struct sigaction) - (int)p;
#else /* cygwin */
	void (*old)(int) = signal(SIGBREAK, sighandler);

	do raise(SIGBREAK); while (!p);
	return (char *)&old - p;
#endif /* cygwin */
}

sqInt reportStackHeadroom;
static int stackPageHeadroom;

/* Answer the redzone size plus space for any signal handlers to run in.
 * N.B. Space for signal handers may include space for the dynamic linker to
 * run in since signal handlers may reference other functions, and linking may
 * be lazy.  The reportheadroom switch can be used to check empirically that
 * there is sufficient headroom.
 */
int
osCogStackPageHeadroom()
{
	if (!stackPageHeadroom)
		stackPageHeadroom = getRedzoneSize() + 1024;
	return stackPageHeadroom;
}


/****************************************************************************/
/* Helper to pop up a message box with a message formatted from the         */
/*   printf() format string and arguments                                   */
/****************************************************************************/
#ifdef WIN64
EXPORT(int) __cdecl sqMessageBox(DWORD dwFlags, const char *titleString, const char* fmt, ...)
{ TCHAR *buf;
  va_list args;
  DWORD result;

  buf = (TCHAR*) calloc(sizeof(TCHAR), 4096);
  va_start(args, fmt);
  vsnprintf(buf, 4096-1, fmt, args);
  va_end(args);

  result = MessageBox(NULL,buf,titleString,dwFlags|MB_SETFOREGROUND);
  free(buf);
  return result;
}

EXPORT(void) printLastError(const TCHAR *prefix) { LPVOID lpMsgBuf;
  DWORD lastError;

  lastError = GetLastError();
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |  FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf, 0, NULL );
  wprintf(TEXT("%s (%ld) -- %s\n"), prefix, lastError, (unsigned short*)lpMsgBuf);
  LocalFree( lpMsgBuf );
}

EXPORT(int) __cdecl abortMessage(TCHAR *fmt, ...)
{ TCHAR *buf;
	va_list args;

	va_start(args, fmt);
	if (fIsConsole) {
		vfwprintf(stderr, fmt, args);
		exit(-1);
	}
	buf = (TCHAR*) calloc(sizeof(TCHAR), 4096);

	wvsprintf(buf, fmt, args);

	va_end(args);

	MessageBox(NULL,buf,TEXT(VM_NAME) TEXT("!"),MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
	free(buf);
	exit(-1);
	return 0;
}

#endif


int fileExists(const char *aPath){
	struct stat st;

	return stat(aPath, &st) == 0;
}

EXPORT(char*) getFullPath(char const *relativePath, char* fullPath, int fullPathSize){
#ifdef WIN64

	int requiredSize = MultiByteToWideChar(CP_UTF8, 0, relativePath, -1, NULL, 0);
	LPWSTR relativePathWide = (LPWSTR)alloca(sizeof(WCHAR) * (requiredSize + 1));
	LPWSTR fullPathWide = (LPWSTR)alloca(sizeof(WCHAR)* fullPathSize);

	MultiByteToWideChar(CP_UTF8, 0, relativePath, -1, relativePathWide, requiredSize);

	if(GetFullPathNameW(relativePathWide, fullPathSize, fullPathWide, NULL) == 0){
		return NULL;
	}

	WideCharToMultiByte(CP_UTF8, 0, fullPathWide, -1, fullPath, fullPathSize, NULL, 0);

	return fullPath;

#else

	//If the path is relative everything is fine.
	if(relativePath[0] == '/' || relativePath[0] == '.'){
		return realpath(relativePath, fullPath);
	}

	//If the path is not relative we have to add the './' in the beginning.
	char* tmpPath = (char*)alloca(fullPathSize);
	strcpy(tmpPath, "./");
	strcat(tmpPath, relativePath);

	return realpath(tmpPath, fullPath);
#endif
}

EXPORT(void) getBasePath(char const *path, char* basePath, int basePathSize){
#ifdef WIN64

	int requiredSize = MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0);

	LPWSTR pathWide = (LPWSTR)alloca(sizeof(WCHAR) * (requiredSize + 1));
	LPWSTR basePathWide = (LPWSTR)alloca(sizeof(WCHAR)* basePathSize);
	LPWSTR finalBasePathWide = (LPWSTR)alloca(sizeof(WCHAR)* basePathSize);
	LPWSTR driveWide = (LPWSTR)alloca(sizeof(WCHAR)* (2 + 1));

	MultiByteToWideChar(CP_UTF8, 0, path, -1, pathWide, requiredSize);

	int error = _wsplitpath_s(pathWide, driveWide, 3, basePathWide, basePathSize, NULL, 0, NULL,0);

	if(error != 0){
		logError("Could not extract basepath: %s", path);
		strcpy(basePath, "");
		return;
	}

	wcscpy(finalBasePathWide, driveWide);
	wcscat(finalBasePathWide, basePathWide);

	WideCharToMultiByte(CP_UTF8, 0, finalBasePathWide, -1, basePath, basePathSize, NULL, 0);

#else
	strcpy(basePath, dirname(path));
#endif
}

int vmProcessArgumentCount = 0;
const char ** vmProcessArgumentVector = NULL;
const char ** vmProcessEnvironmentVector = NULL;

EXPORT(void) setProcessArguments(int count, const char** args){
	vmProcessArgumentCount = count;
	vmProcessArgumentVector = args;
}

EXPORT(void) setProcessEnvironmentVector(const char** environment){
	vmProcessEnvironmentVector = environment;
}

EXPORT(int) getProcessArgumentCount(){
	return vmProcessArgumentCount;
}

EXPORT(const char**) getProcessArgumentVector(){
	return vmProcessArgumentVector;
}

EXPORT(const char **) getProcessEnvironmentVector(){
	return vmProcessEnvironmentVector;
}
