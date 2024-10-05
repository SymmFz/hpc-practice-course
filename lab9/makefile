OLD  := MMult0
# NEW  ?= MMult0
# NEW  ?= MMult1
# NEW  ?= pthread_gemm
# NEW  ?= openblas_gemm
# NEW  ?= openmp_gemm

# Task 1

# 1.调整 ijk 顺序
# NEW  ?= t1_ijk
# NEW  ?= t1_ikj
# NEW  ?= t1_jik
# NEW  ?= t1_jki
# NEW  ?= t1_kij
# NEW  ?= t1_kji

# 2.向量化 SIMD ! 启用为矩阵分配内存时，需使用 __mm_malloc() 函数，否则会报错
# https://blog.csdn.net/jin739738709/article/details/122201508
# NEW  ?= t1_SIMD
# NEW  ?= t1_SIMD_with_unroll4

# 3.矩阵分块
# https://blog.csdn.net/CQRuler/article/details/127812444
# https://renzibei.com/2021/06/30/optimize-gemm/
# NEW  ?= t1_MultiBlocks

# 4.矩阵数据重排
NEW  ?= t1_MultiBlocks_data_resort


CC         := gcc
LINKER     := $(CC) 

CFLAGS     := -Wall -Werror -Wno-unused-result -Wno-unused-value -Wno-unused-variable -g -fopenmp -mavx -DNEW=$(NEW)
LDFLAGS    := -lm -lpthread -fopenmp -lopenblas

DATA_DIR = _data
BUILD_DIR = _build
OBJS  := $(BUILD_DIR)/util.o $(BUILD_DIR)/REF_MMult.o $(BUILD_DIR)/test_MMult.o $(BUILD_DIR)/$(NEW).o

$(shell mkdir -p $(BUILD_DIR) $(DATA_DIR))

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@) && echo + CC $<
	$(CC) -std=gnu11 $(CFLAGS) -c $< -o $@ 


all:
	make clean;
	make $(BUILD_DIR)/test_MMult.x

$(BUILD_DIR)/test_MMult.x: $(OBJS) defs.h
	$(LINKER) $(OBJS) $(LDFLAGS) -o $@

export OMP_NUM_THREADS=16
export GOTO_NUM_THREADS=1

run:
	make all
	echo $$OMP_NUM_THREADS
	@echo "date = '`date`';" > $(DATA_DIR)/output_$(NEW).m
	@echo "version = '$(NEW)';" >> $(DATA_DIR)/output_$(NEW).m
	$(BUILD_DIR)/test_MMult.x >> $(DATA_DIR)/output_$(NEW).m
	@if [ ! -f $(DATA_DIR)/output_old.m ] || [ $(OLD) != $(NEW) ]; then \
        cp $(DATA_DIR)/output_$(OLD).m $(DATA_DIR)/output_old.m; \
    fi

	cp $(DATA_DIR)/output_$(NEW).m $(DATA_DIR)/output_new.m

clean:
	rm -rf _build *.jpg

cleanall:
	rm -rf _build _data *.jpg
