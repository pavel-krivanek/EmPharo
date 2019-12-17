set -e

COMPILER=emcc
ARGS="-DEMCC=1 -DLSB_FIRST=1 -DDEBUG=0 -I. -c -w -s USE_PTHREADS=1 -s TOTAL_MEMORY=536870912 -pthread -Wl,--no-check-features -s PTHREAD_POOL_SIZE=2"

rm -rf ./build
mkdir -p build

$COMPILER debug.c                $ARGS -o./build/debug.o
$COMPILER externalPrimitives.c   $ARGS -o./build/externalPrimitives.o
$COMPILER sqHeapMap.c            $ARGS -o./build/sqHeapMap.o
$COMPILER sqNamedPrims.c         $ARGS -o./build/sqNamedPrims.o
$COMPILER utils.c                $ARGS -o./build/utils.o
$COMPILER sqTicker.c             $ARGS -o./build/sqTicker.o
$COMPILER aio.c                  $ARGS -o./build/aio.o
$COMPILER sqUnixHeartbeat.c      $ARGS -o./build/sqUnixHeartbeat.o
$COMPILER debugUnix.c            $ARGS -o./build/debugUnix.o
$COMPILER memoryUnix.c           $ARGS -o./build/memoryUnix.o
$COMPILER unixMain.c             $ARGS -o./build/unixMain.o
$COMPILER gcc3x-interp.c         $ARGS -o./build/gcc3x-interp.o
$COMPILER nullDisplay.c          $ARGS -o./build/nullDisplay.o
$COMPILER sqExternalSemaphores.c $ARGS -o./build/sqExternalSemaphores.o
$COMPILER aioUnix.c              $ARGS -o./build/aioUnix.o
$COMPILER client.c               $ARGS -o./build/client.o
$COMPILER parameters.c           $ARGS -o./build/parameters.o
$COMPILER pathUtilities.c        $ARGS -o./build/pathUtilities.o
$COMPILER fileDialogUnix.c       $ARGS -o./build/fileDialogUnix.o
$COMPILER parameterVector.c      $ARGS -o./build/parameterVector.o
$COMPILER stringUtilities.c      $ARGS -o./build/stringUtilities.o
$COMPILER fileDialogCommon.c     $ARGS -o./build/fileDialogCommon.o
$COMPILER errorCode.c            $ARGS -o./build/errorCode.o
$COMPILER sqVirtualMachine.c     $ARGS -o./build/sqVirtualMachine.o

cd build

$COMPILER -o pharo.html aio.o externalPrimitives.o sqHeapMap.o sqUnixHeartbeat.o debug.o \
         gcc3x-interp.o sqNamedPrims.o unixMain.o debugUnix.o memoryUnix.o sqTicker.o \
         utils.o nullDisplay.o sqExternalSemaphores.o aioUnix.o client.o parameters.o \
         pathUtilities.o fileDialogUnix.o parameterVector.o stringUtilities.o \
         fileDialogCommon.o errorCode.o sqVirtualMachine.o \
         -lm -ldl -pthread

