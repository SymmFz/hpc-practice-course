#!/bin/bash

# 定义所有 NEW 的值
new_values=("MMult1" 
            "t1_ijk" "t1_ikj" "t1_jik" "t1_jki" "t1_kij" "t1_kji" \
            "t1_SIMD" "t1_SIMD_with_unroll4" \
            "t1_MultiBlocks" "t1_MultiBlocks_data_resort")

# 遍历每个 NEW 值
for new in "${new_values[@]}"
do
    echo "========================================="
    echo "Running test with NEW=${new}"
    echo "========================================="

    # 将 NEW 传递给 make，编译并运行
    echo ":.Running version: $new"
    make run NEW=$new

    echo -e "\n\n"
done
