TTTBOOK = ../source/tttbook
PS2PDF = ps2pdf

.DEFAULT_GOAL := all
.PHONY: all
all: $(TTTBOOK)
	$(TTTBOOK) --first 0,0 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_00.pdf
	$(TTTBOOK) --first 0,1 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_01.pdf
	$(TTTBOOK) --first 0,2 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_02.pdf
	$(TTTBOOK) --first 1,0 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_10.pdf
	$(TTTBOOK) --first 1,1 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_11.pdf
	$(TTTBOOK) --first 1,2 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_12.pdf
	$(TTTBOOK) --first 2,0 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_20.pdf
	$(TTTBOOK) --first 2,1 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_21.pdf
	$(TTTBOOK) --first 2,2 --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - first_22.pdf
	$(TTTBOOK) --second    --last_move --marks --best_weight 0.9 --modest_weight 0.0 --worst_weight 0.1 --select random --best_speed fast --shuffle 5 | $(PS2PDF) - second.pdf
	$(TTTBOOK) --second                --marks --best_weight 0.0 --modest_weight 0.0 --worst_weight 1.0 --select random                               | $(PS2PDF) - stupid.pdf
	$(TTTBOOK) --second                --marks --best_weight 0.0 --modest_weight 1.0 --worst_weight 0.0 --select random                               | $(PS2PDF) - modest.pdf
	$(TTTBOOK) --second                --marks --best_weight 1.0 --modest_weight 0.0 --worst_weight 0.0 --select first  --best_speed fast             | $(PS2PDF) - unbeatable.pdf

.PHONY: debug
debug: all

.PHONY: clean
clean:
	rm -rf *.pdf

.SUFFIXES:
