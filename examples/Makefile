TTTBOOK = ../source/tttbook
PS2PDF = ps2pdf

.DEFAULT_GOAL := all
.PHONY: all
all: $(TTTBOOK)
	$(TTTBOOK) --first 1,1 --gate 0.1 --shuffle 5 --select random --best_speed fast | $(PS2PDF) - first.pdf
	$(TTTBOOK) --second    --gate 0.1 --shuffle 5 --select random --best_speed fast | $(PS2PDF) - second.pdf
	$(TTTBOOK) --second    --gate 0.0             --select first  --best_speed fast | $(PS2PDF) - unbeatable.pdf

.PHONY: debug
debug: all

.PHONY: clean
clean:
	rm -rf *.pdf

.SUFFIXES:
