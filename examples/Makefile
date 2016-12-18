TTTBOOK = ../source/tttbook
PS2PDF = ps2pdf

.DEFAULT_GOAL := all
.PHONY: all
all: normal reverse

.PHONY: normal
normal:                     \
	normal_first_00.pdf \
	normal_first_01.pdf \
	normal_first_02.pdf \
	normal_first_10.pdf \
	normal_first_11.pdf \
	normal_first_12.pdf \
	normal_first_20.pdf \
	normal_first_21.pdf \
	normal_first_22.pdf \
	normal_second.pdf   \
	normal_best.pdf     \
	normal_modest.pdf   \
	normal_worst.pdf    \

normal_first_00.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 0,0          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_01.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 0,1          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_02.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 0,2          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_10.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 1,0          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_11.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 1,1          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_12.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 1,2          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_20.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 2,0          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_21.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 2,1          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_first_22.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --first 2,2          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_second.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

normal_best.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --marks             \
	  --best_weight 1.0   \
	  --modest_weight 0.0 \
	  --worst_weight 0.0  \
	  --select first      \
	  --speed slow        \
	  | $(PS2PDF) - $@

normal_modest.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.0   \
	  --modest_weight 1.0 \
	  --worst_weight 0.0  \
	  --select first      \
	  | $(PS2PDF) - $@

normal_worst.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --marks             \
	  --best_weight 0.0   \
	  --modest_weight 0.0 \
	  --worst_weight 1.0  \
	  --select random     \
	  | $(PS2PDF) - $@

.PHONY: reverse
reverse:                     \
	reverse_first_00.pdf \
	reverse_first_01.pdf \
	reverse_first_02.pdf \
	reverse_first_10.pdf \
	reverse_first_11.pdf \
	reverse_first_12.pdf \
	reverse_first_20.pdf \
	reverse_first_21.pdf \
	reverse_first_22.pdf \
	reverse_second.pdf   \
	reverse_best.pdf     \
	reverse_modest.pdf   \
	reverse_worst.pdf    \

reverse_first_00.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 0,0          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_01.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 0,1          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_02.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 0,2          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_10.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 1,0          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_11.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 1,1          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_12.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 1,2          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_20.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 2,0          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_21.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 2,1          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_first_22.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --first 2,2          \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_second.pdf: $(TTTBOOK)
	$(TTTBOOK)             \
	  --reverse            \
	  --last_move          \
	  --marks              \
	  --guaranteed_best 2  \
	  --best_weight 0.8    \
	  --modest_weight 0.15 \
	  --worst_weight 0.05  \
	  --select random      \
	  --speed fast         \
	  --shuffle 5          \
	  | $(PS2PDF) - $@

reverse_best.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --reverse           \
	  --marks             \
	  --best_weight 1.0   \
	  --modest_weight 0.0 \
	  --worst_weight 0.0  \
	  --select first      \
	  --speed slow        \
	  | $(PS2PDF) - $@

reverse_modest.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --reverse           \
	  --marks             \
	  --guaranteed_best 2 \
	  --best_weight 0.0   \
	  --modest_weight 1.0 \
	  --worst_weight 0.0  \
	  --select first      \
	  | $(PS2PDF) - $@

reverse_worst.pdf: $(TTTBOOK)
	$(TTTBOOK)            \
	  --reverse           \
	  --marks             \
	  --best_weight 0.0   \
	  --modest_weight 0.0 \
	  --worst_weight 1.0  \
	  --select random     \
	  | $(PS2PDF) - $@

.PHONY: clean
clean:
	rm -rf *.pdf

.SUFFIXES:
