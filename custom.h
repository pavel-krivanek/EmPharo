#define LSB_FIRST 1
#define DEBUG	0

#include <stdio.h>
#include "sq.h"

#define VM_LABEL(foo)


void logAssert(const char* fileName, const char* functionName, int line, char* msg) { }
sqInt clipboardSize(void) { return 0; }
sqInt clipboardReadIntoAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex) { return 0; }
sqInt clipboardWriteFromAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex) { return 0; }
void ioGetClockLogSizeUsecsIdxMsecsIdx(sqInt *runInNOutp, void **usecsp, sqInt *uip, void **msecsp, sqInt *mip) { }

unsigned volatile long long  ioUTCMicrosecondsNow() { return 0; }
unsigned volatile long long  ioUTCMicroseconds() { return 0; }
unsigned volatile long long  ioLocalMicrosecondsNow() { return 0; }
unsigned volatile long long  ioLocalMicroseconds() { return 0; }
unsigned          long long  ioUTCStartMicroseconds() { return 0; }

void  ioProfileStatus(sqInt *running, void **exestartpc, void **exelimitpc,
					  void **vmhst, long *nvmhbin, void **eahst, long *neahbin) { }
void  ioControlProfile(int on, void **vhp, long *nvb, void **ehp, long *neb) { };
long  ioControlNewProfile(int on, unsigned long buffer_size) { return 0; };
void  ioNewProfileStatus(sqInt *running, long *buffersize) { };
long  ioNewProfileSamplesInto(void *sampleBuffer) { return 0; };
void  ioClearProfile(void) { };

sqInt crashInThisOrAnotherThread(sqInt flags) { return 0; };

int   ioHeartbeatMilliseconds(void) {};
void  ioSetHeartbeatMilliseconds(int arg) {};
unsigned long ioHeartbeatFrequency(int arg) { return 0; };

int   ioGetMaxExtSemTableSize(void) { return 0; };
void  ioSetMaxExtSemTableSize(int arg) {};

long ioMSecs(void) {};
sqInt ioMicroMSecs(void) {};

void *ioLoadExternalFunctionOfLengthFromModuleOfLengthAccessorDepthInto
	(sqInt functionNameIndex, sqInt functionNameLength,
	 sqInt moduleNameIndex,   sqInt moduleNameLength, sqInt *accessorDepthPtr) {};
void  *ioLoadFunctionFrom(char *functionName, char *pluginName) {};

sqInt ioBeep(void) { return 0; }
sqInt ioExit(void) { return 0; }
sqInt ioExitWithErrorCode(int arg) { return 0; }
void  ioNoteDisplayChangedwidthheightdepth(void *bitsOrHandle, int w, int h, int d) {};
sqInt ioForceDisplayUpdate(void) { return 0; }
sqInt ioFormPrint(sqInt bitsAddr, sqInt width, sqInt height, sqInt depth,
		  double hScale, double vScale, sqInt landscapeFlag) { return 0; }
sqInt ioSetFullScreen(sqInt fullScreen) { return 0; }
double ioScreenScaleFactor(void) { return 0.0; }
sqInt ioScreenSize(void) { return 0; }
sqInt ioScreenDepth(void) { return 0; }
sqInt ioSeconds(void) { return 0; }
sqInt ioSecondsNow(void) { return 0; }
sqInt ioSetCursor(sqInt cursorBitsIndex, sqInt offsetX, sqInt offsetY) { return 0; }
sqInt ioSetCursorWithMask(sqInt cursorBitsIndex, sqInt cursorMaskIndex, sqInt offsetX, sqInt offsetY) { return 0; }
sqInt ioShowDisplay(sqInt dispBitsIndex, sqInt width, sqInt height, sqInt depth,
		    sqInt affectedL, sqInt affectedR, sqInt affectedT, sqInt affectedB) { return 0; }
sqInt ioHasDisplayDepth(sqInt depth);
sqInt ioSetDisplayMode(sqInt width, sqInt height, sqInt depth, sqInt fullscreenFlag) { return 0; }
char* ioGetLogDirectory(void) { return 0; }
sqInt ioSetLogDirectoryOfSize(void* lblIndex, sqInt sz) { return 0; }
char* ioGetWindowLabel(void) { return 0; }
sqInt ioSetWindowLabelOfSize(void *lblIndex, sqInt sz) { return 0; }
sqInt ioGetWindowWidth(void) { return 0; }
sqInt ioGetWindowHeight(void) { return 0; }
sqInt ioSetWindowWidthHeight(sqInt w, sqInt h) { return 0; }
sqInt ioIsWindowObscured(void) { return 0; }

sqInt doSignalExternalSemaphores(sqInt arg ) { return 0; }
void  ioInitHeartbeat(void) {};

sqInt ioDisablePowerManager(sqInt disableIfNonZero) { return 0; }

sqInt attributeSize(sqInt indexNumber) { return 0; }
sqInt getAttributeIntoLength(sqInt indexNumber, sqInt byteArrayIndex, sqInt length) { return 0; };
sqInt ioGetNextEvent(sqInputEvent *evt) { return 0; }
sqLong ioHighResClock(void) { return 0; }

char *getImageName(void) { return 0; }
sqInt imageNameGetLength(sqInt sqImageNameIndex, sqInt length) { return 0; }
sqInt imageNamePutLength(sqInt sqImageNameIndex, sqInt length) { return 0; }
sqInt imageNameSize(void) { return 0; }
sqInt vmPathSize(void) { return 0; }
sqInt vmPathGetLength(sqInt sqVMPathIndex, sqInt length) { return 0; }

sqInt ioSetInputSemaphore(sqInt semaIndex) { return 0; }

sqInt ioGetKeystroke(void) { return 0; }

sqInt ioGetButtonState(void) {}

sqInt ioMousePoint(void) {}
sqInt ioPeekKeystroke(void) {}

char  *ioListBuiltinModule(sqInt moduleIndex) { return 0; }
char  *ioListLoadedModule(sqInt moduleIndex) { return 0; }

sqInt ioRelinquishProcessorForMicroseconds(sqInt microSeconds) { return 0; }

sqInt ioHasDisplayDepth(sqInt depth) { return 0; }
sqInt  ioUnloadModuleOfLength(sqInt moduleNameIndex, sqInt moduleNameLength) { return 0; }
void	ioUpdateVMTimezone() {}
sqInt	ioLocalSecondsOffset() { return 0; }

void clearHeapMap(void) {}
int  heapMapAtWord(void *wordPointer) { return 0; }
void heapMapAtWordPut(void *wordPointer, int bit) {}

sqInt signalSemaphoreWithIndex(sqInt semaIndex)  { return 0; }
void sqDeallocateMemorySegmentAtOfSize(void *addr, sqInt sz)  {}

void *sqAllocateMemorySegmentOfSizeAboveAllocatedSizeInto(sqInt sz, void *minAddr, sqInt *asp) {return 0; }
void ioSynchronousCheckForEvents() {}
sqInt ioProcessEvents(void) {};
sqInt sqGetFilenameFromString(char * aCharBuffer, char * aFilenameString, sqInt filenameLength, sqInt aBoolean) { return 0; }
usqInt
sqAllocateMemory(usqInt minHeapSize, usqInt desiredHeapSize)  { return 0; }

struct VirtualMachine* sqGetInterpreterProxy(void) { return 0; };
char imageName[255];


int main() {
  printf("hello, world!\n");
  return 0;
}
