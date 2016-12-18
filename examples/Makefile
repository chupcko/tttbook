TTTBOOK = ../source/tttbook
PS2PDF = ps2pdf

.DEFAULT_GOAL := all
.PHONY: all
all: first_00.pdf first_01.pdf first_02.pdf first_10.pdf first_11.pdf first_12.pdf first_20.pdf first_21.pdf first_22.pdf second.pdf best.pdf modest.pdf worst.pdf lose.pdf

first_00.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 0,0         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_00.pdf

first_01.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 0,1         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_01.pdf

first_02.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 0,2         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_02.pdf

first_10.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 1,0         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_10.pdf

first_11.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 1,1         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_11.pdf

first_12.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 1,2         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_12.pdf

first_20.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 2,0         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_20.pdf

first_21.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 2,1         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_21.pdf

first_22.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --first 2,2         \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - first_22.pdf

second.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --last_move         \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.9   \
	  --modest_weight 0.0 \
	  --worst_weight 0.1  \
	  --select random     \
	  --speed fast        \
	  --shuffle 5         \
	  | $(PS2PDF) - second.pdf

best.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --marks             \
	  --best_weight 1.0   \
	  --modest_weight 0.0 \
	  --worst_weight 0.0  \
	  --select first      \
	  --speed slow        \
	  | $(PS2PDF) - best.pdf

modest.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.0   \
	  --modest_weight 1.0 \
	  --worst_weight 0.0  \
	  --select first      \
	  | $(PS2PDF) - modest.pdf

worst.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --marks             \
	  --best_weight 0.0   \
	  --modest_weight 0.0 \
	  --worst_weight 1.0  \
	  --select random     \
	  | $(PS2PDF) - worst.pdf

lose.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --reverse           \
	  --marks             \
	  --best_weight 1.0   \
	  --modest_weight 0.0 \
	  --worst_weight 0.0  \
	  --select first      \
	  --speed slow        \
	  | $(PS2PDF) - lose.pdf

.PHONY: debug
debug: all

.PHONY: clean
clean:
	rm -rf *.pdf

.SUFFIXES:
