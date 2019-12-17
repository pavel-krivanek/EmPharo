set -e

COMPILER=emcc
ARGS="-DEMCC=1 -DLSB_FIRST=1 -DDEBUG=1 -I./src -c -w -s ALLOW_MEMORY_GROWTH=1 -s WASM_MEM_MAX=256MB -s USE_PTHREADS=1 -pthread -Wl,--no-check-features -s PTHREAD_POOL_SIZE=2"
#-s ALLOW_MEMORY_GROWTH=1 -s WASM_MEM_MAX=67108864 -s TOTAL_MEMORY=64MB

rm -rf ./build
mkdir -p build

cp image/*.image build/

$COMPILER ./src/debug.c                $ARGS -o./build/debug.o
$COMPILER ./src/externalPrimitives.c   $ARGS -o./build/externalPrimitives.o
$COMPILER ./src/sqHeapMap.c            $ARGS -o./build/sqHeapMap.o
$COMPILER ./src/sqNamedPrims.c         $ARGS -o./build/sqNamedPrims.o
$COMPILER ./src/utils.c                $ARGS -o./build/utils.o
$COMPILER ./src/sqTicker.c             $ARGS -o./build/sqTicker.o
$COMPILER ./src/aio.c                  $ARGS -o./build/aio.o
$COMPILER ./src/sqUnixHeartbeat.c      $ARGS -o./build/sqUnixHeartbeat.o
$COMPILER ./src/debugUnix.c            $ARGS -o./build/debugUnix.o
$COMPILER ./src/memoryUnix.c           $ARGS -o./build/memoryUnix.o
$COMPILER ./src/unixMain.c             $ARGS -o./build/unixMain.o
$COMPILER ./src/gcc3x-interp.c         $ARGS -o./build/gcc3x-interp.o
$COMPILER ./src/nullDisplay.c          $ARGS -o./build/nullDisplay.o
$COMPILER ./src/sqExternalSemaphores.c $ARGS -o./build/sqExternalSemaphores.o
$COMPILER ./src/aioUnix.c              $ARGS -o./build/aioUnix.o
$COMPILER ./src/client.c               $ARGS -o./build/client.o
$COMPILER ./src/parameters.c           $ARGS -o./build/parameters.o
$COMPILER ./src/pathUtilities.c        $ARGS -o./build/pathUtilities.o
$COMPILER ./src/fileDialogUnix.c       $ARGS -o./build/fileDialogUnix.o
$COMPILER ./src/parameterVector.c      $ARGS -o./build/parameterVector.o
$COMPILER ./src/stringUtilities.c      $ARGS -o./build/stringUtilities.o
$COMPILER ./src/fileDialogCommon.c     $ARGS -o./build/fileDialogCommon.o
$COMPILER ./src/errorCode.c            $ARGS -o./build/errorCode.o
$COMPILER ./src/sqVirtualMachine.c     $ARGS -o./build/sqVirtualMachine.o

cd build

$COMPILER -o pharo.html aio.o externalPrimitives.o sqHeapMap.o sqUnixHeartbeat.o debug.o \
         gcc3x-interp.o sqNamedPrims.o unixMain.o debugUnix.o memoryUnix.o sqTicker.o \
         utils.o nullDisplay.o sqExternalSemaphores.o aioUnix.o client.o parameters.o \
         pathUtilities.o fileDialogUnix.o parameterVector.o stringUtilities.o \
         fileDialogCommon.o errorCode.o sqVirtualMachine.o \
         -lm -ldl -pthread \
         -s ALLOW_MEMORY_GROWTH=1 -s WASM_MEM_MAX=256MB \
         --preload-file Pharo.image

#         -s ALLOW_MEMORY_GROWTH=1 -s WASM_MEM_MAX=256MB -s TOTAL_MEMORY=256MB \

