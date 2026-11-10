"""Figures 22-27 of lesson 3.1 (recursion): they replace ASCII sketches of the notes. Run: python3 scripts/figures/fig_3_1.py"""
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, FancyBboxPatch, FancyArrowPatch

OUT = "src/assets/notes/3-1-backtracking/"
INK, GREY, Y, B, P, R = "#1f2933", "#7b8794", "#ffd166", "#8ecae6", "#cdb4f6", "#d1495b"

def canvas(w, h, title):
    fig, ax = plt.subplots(figsize=(w, h))
    ax.set_xlim(0, w * 100); ax.set_ylim(0, h * 100); ax.axis("off")
    ax.text(15, h * 100 - 28, title, fontsize=13, fontweight="bold", color=INK, va="center")
    return fig, ax

def box(ax, x, y, w, h, text, fc=B, tc=INK, fs=11, bold=False):
    ax.add_patch(FancyBboxPatch((x, y), w, h, boxstyle="round,pad=0,rounding_size=8", fc=fc, ec=GREY, lw=1.6))
    ax.text(x + w / 2, y + h / 2, text, ha="center", va="center", fontsize=fs, color=tc, fontweight="bold" if bold else "normal")

def arrow(ax, x1, y1, x2, y2):
    ax.add_patch(FancyArrowPatch((x1, y1), (x2, y2), arrowstyle="-|>", mutation_scale=14, color=GREY, lw=1.6))

def save(fig, name):
    fig.savefig(OUT + name, dpi=130, bbox_inches="tight", facecolor="white"); plt.close(fig)

# fig22: the four uses of recursion
fig, ax = canvas(9, 3.2, "Recursion is used in four ways")
box(ax, 20, 130, 150, 60, "Recursion", fc=Y, bold=True, fs=13)
for i, (t, c) in enumerate([("Divide and conquer", "#e5e7eb"), ("Backtracking", B), ("k-th element", B), ("Fractals", B)]):
    x = 230 + i * 165
    box(ax, x, 130, 150, 60, t, fc=c); arrow(ax, 170, 160, x, 160)
ax.text(230, 85, "Divide and conquer: split the problem in half, solve both halves, merge.", fontsize=10, color=GREY)
ax.text(230, 55, "The other three are the topics of this lesson.", fontsize=10, color=GREY)
save(fig, "fig22_recursion_uses.png")

# fig23: Hanoi split into three steps
fig, ax = canvas(10.5, 3.6, "Tower of Hanoi with n discs, from peg A to peg C using peg B")
def pegs(x0, label, stacks):
    for k, name in enumerate("ABC"):
        px = x0 + 40 + k * 100
        ax.plot([px, px], [90, 250], color=GREY, lw=3)
        ax.text(px, 70, name, ha="center", fontsize=11, color=GREY)
        for lvl, (w, t, col) in enumerate(stacks[k]):
            ax.add_patch(Rectangle((px - w / 2, 92 + lvl * 34), w, 30, fc=col, ec=GREY, lw=1.5, zorder=3))
            ax.text(px, 107 + lvl * 34, t, ha="center", va="center", fontsize=8, zorder=4)
    ax.plot([x0 + 5, x0 + 275], [90, 90], color=INK, lw=2)
    ax.text(x0 + 140, 285, label, ha="center", fontsize=11, fontweight="bold", color=INK)
small = [(60, "n-1 discs", B), (60, "", B)]
pegs(15, "start", [[(88, "n-th disc", P), (58, "n-1 discs", B)], [], []])
pegs(365, "after the first call", [[(88, "n-th disc", P)], [(58, "n-1 discs", B)], []])
pegs(715, "after the move, then the second call", [[], [], [(88, "n-th disc", P), (58, "n-1 discs", B)]])
ax.text(15, 25, "First call: move the n-1 discs from A to B (using C). Then move the n-th disc from A to C. Then move the n-1 discs from B to C (using A).", fontsize=9.5, color=GREY)
save(fig, "fig23_hanoi_split.png")

# fig24: the four problems
fig, ax = canvas(8, 3.4, "The four problems to learn: backtracking for each of these")
ax.text(300, 230, "distinct elements", ha="center", fontsize=11, fontweight="bold", color=INK)
ax.text(560, 230, "non-distinct elements", ha="center", fontsize=11, fontweight="bold", color=INK)
for r, name in enumerate(["Permutation", "Subset"]):
    y = 140 - r * 80
    ax.text(25, y + 25, name, fontsize=12, fontweight="bold", color=INK, va="center")
    for c in range(2):
        box(ax, 190 + c * 260, y, 220, 50, ["1", "2", "3", "4"][r * 2 + c], fc=[Y, B][c], bold=True, fs=15)
save(fig, "fig24_four_problems.png")

# fig25: levels of the N-Queens search for n = 4, no check applied
fig, ax = canvas(8, 4.8, "N-Queens, n = 4: one level per row, every level tries the columns 0 to 3")
for lv in range(4):
    y = 330 - lv * 70
    box(ax, 60, y, 150, 50, f"level {lv}", fc=P, bold=True)
    for col in range(4):
        box(ax, 260 + col * 70, y, 60, 50, str(col), fc=Y if col == 0 else "#f3f4f6")
    ax.text(560, y + 25, "[" + " ".join(["0"] * (lv + 1) + ["_"] * (3 - lv)) + "]", fontsize=10, color=GREY, va="center")
    arrow(ax, 135, y, 135, y - 20)
box(ax, 60, 50, 150, 50, "level 4: base", fc=B, bold=True, fs=10)
ax.text(260, 75, "all rows decided: count the answer", fontsize=10, color=GREY, va="center")
ax.text(260, 20, "Shown with no check. With the check, the second 0 is rejected at level 1 and the whole subtree below it is skipped.", fontsize=9, color=GREY)
save(fig, "fig25_nqueens_levels.png")

# fig26: two queens on one diagonal
fig, ax = canvas(7.4, 4.2, "Two queens attack along a diagonal when the row gap equals the column gap")
cell, ox, oy = 50, 40, 20
for r in range(5):
    for c in range(5):
        ax.add_patch(Rectangle((ox + c * cell, oy + (4 - r) * cell), cell, cell, fc="#f3f4f6" if (r + c) % 2 else "white", ec="#d0d4da"))
def q(r, c, t, col):
    ax.add_patch(plt.Circle((ox + c * cell + cell / 2, oy + (4 - r) * cell + cell / 2 - 4), 15, fc=col, ec=GREY, lw=1.6))
    ax.text(ox + c * cell + cell / 2, oy + (4 - r) * cell + cell / 2 - 4, t, ha="center", va="center", fontsize=9, fontweight="bold")
q(1, 1, "q1", Y); q(3, 3, "q2", R)
ax.plot([ox + 1.5 * cell, ox + 3.5 * cell], [oy + 3.5 * cell - 4, oy + 1.5 * cell - 4], color=R, lw=2, ls="--")
ax.text(340, 190, "q1 = (prev_row, prev_col) = (1, 1)", fontsize=10, color=INK)
ax.text(340, 165, "q2 = (curr_row, curr_col) = (3, 3)", fontsize=10, color=INK)
ax.text(340, 130, "slope = (prev_col - curr_col) / (prev_row - curr_row) = ±1", fontsize=10, color=INK)
ax.text(340, 105, "so abs(prev_col - curr_col) = abs(prev_row - curr_row)", fontsize=10, color=INK)
ax.text(340, 70, "here: abs(1 - 3) = 2 = abs(1 - 3), they attack", fontsize=10, color=R)
save(fig, "fig26_diagonal_slope.png")

# fig27: subset slots
fig, ax = canvas(7.6, 3.2, "Subsets of [3, 1, 2, 5]: each element is taken or not taken")
for i, v in enumerate([3, 1, 2, 5]):
    x = 80 + i * 150
    box(ax, x, 150, 100, 55, str(v), fc=Y, bold=True, fs=14)
    box(ax, x - 18, 70, 66, 40, "take", fc=B, fs=10); box(ax, x + 52, 70, 66, 40, "not take", fc="#f3f4f6", fs=10)
    arrow(ax, x + 50, 150, x + 15, 112); arrow(ax, x + 50, 150, x + 85, 112)
ax.text(80, 25, "Level = the element position. Choices = take or not take. Both are tried one after the other, so 2^4 = 16 subsets.", fontsize=9.5, color=GREY)
save(fig, "fig27_take_slots.png")
print("6 figures written")
