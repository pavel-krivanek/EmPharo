/* Automatically generated by
	CCodeGeneratorGlobalStructure * VMMaker-CompatibleUserName.1576136511 uuid: 7fe4520d-ff42-5b35-8fb7-af4cf07830a5
 */

#define VM_PROXY_MAJOR 1
#define VM_PROXY_MINOR 15

#define SQ_VI_BYTES_PER_WORD 8

#define BaseHeaderSize 8
#define BytesPerOop 8
#define BytesPerWord 8

#define PrimErrGenericFailure 1
#define PrimErrBadReceiver 2
#define PrimErrBadArgument 3
#define PrimErrBadIndex 4
#define PrimErrBadNumArgs 5
#define PrimErrInappropriate 6
#define PrimErrUnsupported 7
#define PrimErrNoModification 8
#define PrimErrNoMemory 9
#define PrimErrNoCMemory 10
#define PrimErrNotFound 11
#define PrimErrBadMethod 12
#define PrimErrNamedInternal 13
#define PrimErrObjectMayMove 14
#define PrimErrLimitExceeded 15
#define PrimErrObjectIsPinned 16
#define PrimErrWritePastObject 17
#define PrimErrObjectMoved 18
#define PrimErrObjectNotPinned 19
#define PrimErrCallbackError 20
#define PrimErrOSError 21
#define PrimErrFFIException 22
#define PrimErrNeedCompaction 23
#define PrimErrOperationFailed 24

#define MinSmallInteger -1152921504606846976
#define MaxSmallInteger 1152921504606846975
#define NumSmallIntegerTagBits 3

#define MULTIPLEBYTECODESETS 1
#if !defined(IMMUTABILITY) /* Allow this to be overridden on the compiler command line */
# define IMMUTABILITY 1
#endif

#define STACKVM 1
#define SPURVM 1
#define DisownVMLockOutFullGC 8
#define DisownVMForFFICall 16
#define DisownVMForThreading 32
