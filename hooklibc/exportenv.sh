pw=$(pwd)
export LD_PRELOAD=$pw/hook.so
export MAP_PATH=$pw
export OUT_PATH=$pw/out/

echo $LD_PRELOAD
echo $MAP_PATH
echo $OUT_PATH
