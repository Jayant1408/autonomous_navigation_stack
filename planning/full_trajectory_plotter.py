import json
import matplotlib.pyplot as plt

def plot_full_trajectory(json_path = "planning/full_trajectory.json"):
    with open(json_path, "r") as f:
        data = json.load(f)

    x_vals = [pt["x"] for pt in data]
    y_vals = [pt["y"] for pt in data]


    plt.figure(figsize = (10,6))
    plt.title("Full Trajectory Generated from FSM")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.plot(x_vals, y_vals, color="blue", linewidth=2, label="Trajectory")


    plt.scatter(x_vals[0], y_vals[0], color="green", s=60, label="Start")
    plt.scatter(x_vals[-1], y_vals[-1], color="red", s=60, label="End")

    plt.legend()
    plt.grid(True)
    plt.axis("equal")
    plt.tight_layout()
    plt.savefig("planning/trajectory_plot.png")
    plt.show()

if __name__ == "__main__":
    plot_full_trajectory()