import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, Circle

violet = "#a00963"
orange = "#f09f02"

def add_jet(ax, x, y, label, s=1300, color=orange):
    ax.scatter(x, y, s=s, color=color, alpha=0.3, zorder=3, linewidth=0)
    ax.text(x, y, label, ha="center", va="center", fontsize=10, zorder=4, color=color)

def make_rapidity_gap_schema(output_path="rapidity_gap_schema.png"):
    eta_min, eta_max = -5.2, 5.2
    transition_eta = [-3, -2.5, -1.3, 0, 1.3, 2.5, 3]
    regions = [
        ((eta_min, -3), "HF-"),
        ((-3, -2.5), "EC2-"),
        ((-2.5, -1.3), "EC1-"),
        ((-1.3, 0), "BB-"),
        ((0, 1.3), "BB+"),
        ((1.3, 2.5), "EC1+"),
        ((2.5, 3), "EC2+"),
        ((3, eta_max), "HF+"),
    ]
    ymin, ymax = 0., 5.;

    fig, ax = plt.subplots(figsize=(10, 3.5))
    ax.set_aspect('equal')

    rect = Rectangle((eta_min, ymin), eta_max - eta_min, ymax - ymin, fill=False, edgecolor=violet, linewidth=2)
    ax.add_patch(rect)

    add_jet(ax, -2, 0.6*ymax, "jet 1")   
    add_jet(ax, -1.1, 0.2*ymax, "jet 2")

    for eta in transition_eta:
        ax.axvline(eta, ymin=ymin, ymax=ymax, color="black", linewidth=1.4, alpha=0.1)

    for (x0, x1), label in regions:
        ax.text((x0 + x1) / 2, ymax-0.5, label, ha="center", va="bottom", fontsize=8, alpha=0.1)

    ax.set_xlim(eta_min, eta_max)
    ax.set_ylim(ymin, ymax)
    ax.set_xlabel(r"$\eta$")
    ax.set_xticks([-5.2, -3, -2.5, -1.3, 0, 1.3, 2.5, 3, 5.2])
    ax.set_xticklabels([r"-5.2", r"-3", r"-2.5", r"-1.3", r"0", r"1.3", r"2.5", r"3", r"5.2"])
    ax.set_yticks([])

    for spine in ["top", "right", "left", "bottom"]:
        ax.spines[spine].set_visible(False)

    plt.tight_layout()
    plt.savefig(output_path, dpi=300, bbox_inches="tight")
    plt.show()


if __name__ == "__main__":
    make_rapidity_gap_schema()
