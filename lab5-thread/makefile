OLD  := MMult0
NEW  := MultiThreadMMult


CC         := gcc
LINKER     := $(CC) 

CFLAGS     := -Wall -Werror -Wno-unused-result -Wno-unused-value -Wno-unused-variable -g
LDFLAGS    := -lm -lpthread

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

export OMP_NUM_THREADS=1
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
